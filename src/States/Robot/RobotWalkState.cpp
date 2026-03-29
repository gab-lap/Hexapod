#include "RobotWalkState.h"
#include "RC_receiver.h"
#include "Robot.h"
#include "vectors.h"

void RobotWalkState::Enter()
{
    Serial.println("Robot Walking\n");
}

void RobotWalkState::Update()
{
    // ricorda di definire logica di cambio stato

    const RC_TransmitterData& transmitterData = owner.transmitter.GetData();  

    int rawLeftJoystickX = transmitterData.j1x;
    int rawLeftJoystickY = transmitterData.j1y;
    int rawRightJoystickX = transmitterData.j2x;
    int rawRightJoystickY = transmitterData.j2y;

    int leftJoystickX = map(transmitterData.j1x, 0, 254, -100, 100);
    int leftJoystickY = map(transmitterData.j1y, 0, 254, -100, 100);
    int rightJoystickX = map(transmitterData.j2x, 0, 254, -100, 100);
    int rightJoystickY = map(transmitterData.j2y, 0, 254, -100, 100);


    if(!owner.transmitter.isConnected()) {
        Serial.println("!!! WARNING: Controller Disconnected !!!");
    }
    /*
    else {
        Serial.print("J1 X:"); Serial.print(leftJoystickX);
        Serial.print(" Y:");   Serial.print(leftJoystickY);
        Serial.print("  |  "); 
        Serial.print("J2 X:"); Serial.print(rightJoystickX);
        Serial.print(" Y:");   Serial.print(rightJoystickY);
        
        Serial.print("       Raw Readings ->");
        Serial.print("J1 X:"); Serial.print(rawLeftJoystickX);
        Serial.print(" Y:");   Serial.print(rawLeftJoystickY);
        Serial.print("  |  "); 
        Serial.print("J2 X:"); Serial.print(rawRightJoystickX);
        Serial.print(" Y:");   Serial.println(rawRightJoystickY);
    }*/
    
    _leftJoystickTargetVector = Vector2(leftJoystickX, leftJoystickY);
    _leftJoystickTargetMagnitude = constrain(_leftJoystickTargetVector.magnitude(), 0 , 100);
    
    _rightJoystickTargetVector = Vector2(rightJoystickX, rightJoystickY);
    _rightJoystickTargetMagnitude = constrain(_rightJoystickTargetVector.magnitude(), 0, 100);
    


}

void RobotWalkState::Exit()
{
}
