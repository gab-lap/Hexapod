#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "Leg.h"
#include "PinServo.h"
#include "DriverServo.h"
#include "config.h"
#include "utils.h"
#include "models.h"
#include "RC_Receiver.h"


RC_Transmitter controller;
// Servo driver
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();

// Global pointers
Leg* allLegs[6];
Leg *frontRightLeg, *midRightLeg, *backRightLeg;
Leg *frontLeftLeg, *midLeftLeg, *backLeftLeg;


void setup() {
    Serial.begin(115200);
    while (!Serial);
    delay(1000); 

    Serial.println("--- HEXAPOD SYSTEM BOOTING ---");

    pca.begin();
    pca.setOscillatorFrequency(27000000);
    pca.setPWMFreq(50);

    // Leg objects
    midRightLeg   = new Leg(new DriverServo(&pca, 0), new DriverServo(&pca, 1), new DriverServo(&pca, 2), LegPhysicalData(110.0f, 0.0f));
    frontRightLeg = new Leg(new DriverServo(&pca, 3), new DriverServo(&pca, 4), new DriverServo(&pca, 5), LegPhysicalData(130.0f, 50.0f));
    frontLeftLeg  = new Leg(new DriverServo(&pca, 6), new DriverServo(&pca, 7), new DriverServo(&pca, 8), LegPhysicalData(130.0f, 130.0f));
    midLeftLeg    = new Leg(new DriverServo(&pca, 9), new DriverServo(&pca, 10), new DriverServo(&pca, 11), LegPhysicalData(110.0f, 180.0f));
    backLeftLeg   = new Leg(new DriverServo(&pca, 12), new DriverServo(&pca, 13), new DriverServo(&pca, 14), LegPhysicalData(130.0f, 230.0f));
    backRightLeg  = new Leg(new DriverServo(&pca, 15), new PinServo(BR2_GPIO_PIN), new PinServo(BR3_GPIO_PIN), LegPhysicalData(130.0f, 310.0f));
    
    // Controller begin
    controller.Begin();

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
    for (int i = 0; i < 6; i++) {
        allLegs[i]->Update();
    }
    
    controller.Update();
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
    }

    // Run only if someone typed something
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.length() > 0) {
            // Trigger the state change
            int height = 0;
            if (input == "1")
                height = 1;

            for (int i = 0; i < 6; i++) {
                allLegs[i]->legHeight = height;
            }
            Serial.println("Input received! Changing states...");
        }
    }
}
