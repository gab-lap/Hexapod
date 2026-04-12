#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "Leg.h"
#include "PinServo.h"
#include "DriverServo.h"
#include "config.h"
#include "utils.h"
#include "models.h"
#include "RC_Receiver.h"
#include "Robot.h"
#include "Wire.h"


// Servo driver
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);

// Global pointers
Leg* allLegs[6];
Leg *frontRightLeg, *midRightLeg, *backRightLeg;
Leg *frontLeftLeg, *midLeftLeg, *backLeftLeg;

Robot *robot;



void setup() {
    Serial.begin(115200);
    while (!Serial);
    delay(1000); 

    Serial.println("--- HEXAPOD SYSTEM BOOTING ---");

    Wire.begin(SDA_PIN, SCL_PIN);
    pca.begin();
    pca.setOscillatorFrequency(27000000);
    pca.setPWMFreq(50);

    // Leg objects
    midRightLeg   = new Leg(new DriverServo(&pca, 0), new DriverServo(&pca, 1), new DriverServo(&pca, 2), LegPhysicalData(98.0f, 0.0f, 1, 0));
    frontRightLeg = new Leg(new DriverServo(&pca, 3), new DriverServo(&pca, 4), new DriverServo(&pca, 5), LegPhysicalData(110.0f, 50.0f, 1, 1));
    frontLeftLeg  = new Leg(new DriverServo(&pca, 6), new DriverServo(&pca, 7), new DriverServo(&pca, 8), LegPhysicalData(110.0f, 130.0f, -1, -1));
    midLeftLeg    = new Leg(new DriverServo(&pca, 9), new DriverServo(&pca, 10), new DriverServo(&pca, 11), LegPhysicalData(98.0f, 180.0f, -1, 0));
    backLeftLeg   = new Leg(new DriverServo(&pca, 12), new DriverServo(&pca, 13), new DriverServo(&pca, 14), LegPhysicalData(110.0f, 230.0f, -1, 1));
    backRightLeg  = new Leg(new DriverServo(&pca, 15), new PinServo(BR2_GPIO_PIN), new PinServo(BR3_GPIO_PIN), LegPhysicalData(110.0f, 310.0f, 1, -1));

    //midRightLeg->joint1->SetMicroseconds(620, 2500); midRightLeg->joint2->SetMicroseconds(500, 2400); midRightLeg->joint3->SetMicroseconds(450, 2400);
    //frontRightLeg->joint1->SetMicroseconds(600, 2420); frontRightLeg->joint2->SetMicroseconds(500, 2500); frontRightLeg->joint3->SetMicroseconds(500, 2500);
    //frontLeftLeg->joint1->SetMicroseconds(500, 2500); frontLeftLeg->joint2->SetMicroseconds(500, 2500); frontLeftLeg->joint3->SetMicroseconds(500, 2500);
    //midLeftLeg->joint1->SetMicroseconds(500, 2400); midLeftLeg->joint2->SetMicroseconds(500, 2400); midLeftLeg->joint3->SetMicroseconds(500, 2500);
    //backLeftLeg->joint1->SetMicroseconds(500, 2500); backLeftLeg->joint2->SetMicroseconds(500, 2500); backLeftLeg->joint3->SetMicroseconds(500, 2500);
    //backRightLeg->joint1->SetMicroseconds(500, 2400); backRightLeg->joint2->SetMicroseconds(500, 2500); backRightLeg->joint3->SetMicroseconds(500, 2500);
    
    // Remember to Robot begin
    robot = new Robot(RobotPhysicalData(), RobotLegs(midRightLeg, frontRightLeg, frontLeftLeg, midLeftLeg, backLeftLeg, backRightLeg));
    robot->Begin();
    Serial.print("DEBUG: Size of RC_TransmitterData: ");
    Serial.println(sizeof(RC_TransmitterData));

    // Map to array
    allLegs[0] = frontRightLeg; allLegs[1] = midRightLeg; allLegs[2] = backRightLeg;
    allLegs[3] = frontLeftLeg;  allLegs[4] = midLeftLeg;   allLegs[5] = backLeftLeg;

    for (int i = 0; i < 6; i++) {
        if(allLegs[i]) allLegs[i]->Begin();
    }

    Serial.println("All legs initialized.");

    
}
void loop() {
    // Legs keep updating/moving
    /*
    for (int i = 0; i < 6; i++) {
        allLegs[i]->Update();
    }*/
    
    robot->Update();     // REMOVE COMMENT HERE TO START ROBOT

    /*
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        input.toUpperCase();

        if (input.length() > 0) {
            // Dividiamo la stringa: ID_GAMBA X Y Z
            // Esempio: "MR 0 120 40" o "ALL 0 150 0"
            char buf[64];
            input.toCharArray(buf, 64);
            
            char* partId = strtok(buf, " ");
            char* partX  = strtok(NULL, " ");
            char* partY  = strtok(NULL, " ");
            char* partZ  = strtok(NULL, " ");

            if (partId && partX && partY && partZ) {
                float targetX = atof(partX);
                float targetY = atof(partY);
                float targetZ = atof(partZ);
                Vector3 targetVec(targetX, targetY, targetZ);

                String id = String(partId);
                bool found = false;

                // Definizione puntatori per facilità
                Leg* targetLeg = nullptr;
                if      (id == "FR")  targetLeg = frontRightLeg;
                else if (id == "MR")  targetLeg = midRightLeg;
                else if (id == "BR")  targetLeg = backRightLeg;
                else if (id == "FL")  targetLeg = frontLeftLeg;
                else if (id == "ML")  targetLeg = midLeftLeg;
                else if (id == "BL")  targetLeg = backLeftLeg;

                if (id == "ALL") {
                    Serial.print("Moving ALL legs to: "); Serial.println(targetVec.toString());
                    for (int i = 0; i < 6; i++) allLegs[i]->MoveToPosition(targetVec);
                    found = true;
                } else if (targetLeg) {
                    Serial.print("Moving " + id + " to: "); Serial.println(targetVec.toString());
                    targetLeg->MoveToPosition(targetVec);
                    found = true;
                }

                if (!found) {
                    Serial.println("Invalid Leg ID! Use: FR, MR, BR, FL, ML, BL or ALL");
                }
            } else {
                Serial.println("Invalid Format! Use: ID X Y Z (e.g., MR 0 120 50)");
            }
        }
    }*/
    

    /*controller.Update();
    const RC_TransmitterData& joy = controller.GetData();

    every(100) {
        Serial.print("J1 X:"); Serial.print(joy.j1x);
        Serial.print(" Y:");   Serial.print(joy.j1y);
        Serial.print("  |  ");
        Serial.print("J2 X:"); Serial.print(joy.j2x);
        Serial.print(" Y:");   Serial.println(joy.j2y);
        
        if(!controller.isConnected()) {
            Serial.println("!!! WARNING: Controller Disconnected !!!");
        }
    }*/

   
    // Run only if someone typed something
    
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.length() > 0) {
            if (input.toFloat() >= 0.0 && input.toFloat() <= 1.5) {
                robot->currentGait->cycleSpeedMultiplier = input.toFloat();
            }
            
            // Trigger the state change
            /*int switch_var = 0;
            if (input == "1")
                switch_var = 1;

            for (int i = 0; i < 6; i++) {
                allLegs[i]->ONorOFF = switch_var;
            }
            Serial.println("Input received! Changing states...");*/
        }
    }
}
