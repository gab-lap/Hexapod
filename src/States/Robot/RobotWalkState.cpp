#include "RobotWalkState.h"
#include "RC_receiver.h"
#include "Robot.h"
#include "vectors.h"
#include "Leg.h"
#include "utils.h"

//RobotLegs legs;

void RobotWalkState::Enter()
{
    Serial.println("Robot Walking\n");

    // Inizialize the cycle progress array {0.0f, 0.5f, ...} dependeing on the current Gait
    for (int i = 0; i < NUM_LEGS; i++) {
        Leg* leg = owner.getLeg(i);
        leg->walkingData.cycleProgress = owner.currentGait->cycleOffsets[i] * _points;
    }
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

    _leftJoystickCurrentVector = lerp(_leftJoystickCurrentVector, _leftJoystickTargetVector, 0.04);
    _leftJoystickCurrentMagnitude = lerp(_leftJoystickCurrentMagnitude, _leftJoystickTargetMagnitude, 0.04);
    
    _rightJoystickCurrentVector = lerp(_rightJoystickCurrentVector, _rightJoystickTargetVector, 0.06);
    _rightJoystickCurrentMagnitude = lerp(_rightJoystickCurrentMagnitude, _rightJoystickTargetMagnitude, 0.06);


    for (int i = 0; i < NUM_LEGS; i++) {
        Leg* leg = owner.getLeg(i);
        leg->walkingData.t = (float) leg->walkingData.cycleProgress / _points;
    }

    _forwardAmount = _leftJoystickCurrentMagnitude;
    _turnAmount = _rightJoystickCurrentVector.x;


    // REMEMBER WHEN UPDATING THE WALK CYCLE VARIABLES, ONCE THE WALK CYCLE ENDED, TO UPDATE THE GAIT DATA 
    // (so that the gait can only effectively change once the walk cycle ended)
}

void RobotWalkState::Exit()
{
}

Vector3 RobotWalkState::getGaitPoint(Leg *leg, float pushFraction)
{
    // Normalize right joystick
    float normRxJoystickX = _rightJoystickCurrentVector.x / 100.0f;
    // Exponential mapping
    float expoRxJoyX = (normRxJoystickX >= 0 ? 1 : -1) * (normRxJoystickX * normRxJoystickX);
    // Apply exponential mapping
    float rotationLength = owner.currentGait->maxRotationLength * expoRxJoyX;


    // Normalizing each left joystick axis
    float normLxJoystickX = _leftJoystickCurrentVector.x / 100.f;
    float normLxJoystickY = _leftJoystickCurrentVector.y / 100.f;
    // Exponential mapping of each axis
    float expoLxJoyX = (normLxJoystickX >= 0 ? 1 : -1) * (normLxJoystickX * normLxJoystickX);
    float expoLxJoyY = (normLxJoystickY >= 0 ? 1 : -1) * (normLxJoystickY * normLxJoystickY);
    // Resulting exponential vector to apply
    Vector2 expo = Vector2(expoLxJoyX, expoLxJoyY);
    // Applying the exponential vector
    Vector2 stepLength = expo * owner.currentGait->maxStepLength;
    // Constrain the result
    stepLength.y = constrain(stepLength.y, -owner.currentGait->maxStepLength/2, owner.currentGait->maxStepLength/2);
    stepLength.x = constrain(stepLength.x, -owner.currentGait->maxStepLength, owner.currentGait->maxStepLength);


    float t = leg->walkingData.t;
    Vector3 finalPoint;
    
    if (t < pushFraction) {
        // Map the pushFraction to be a range from 0.0 to 1.0
        float localT = mapFloat(t, 0, pushFraction, 0, 1);

        float targetStepX = stepLength.x * leg->physicalData.position_multiplier;
        float targetStepY = stepLength.y * leg->physicalData.position_multiplier;

        Vector3 stepControlPoints[2];
        stepControlPoints[0] = leg->walkingData.cycleStartPoint;
        stepControlPoints[1] = Vector3(
                                       targetStepX,
                                      -targetStepY + leg->walkingData.distanceFromCenter, // targetStepY is negated because a leg, to make the body move forward, has to push the opposite way
                                       owner.physicalData.distanceFromGround                                        
                                      ).rotateZ(leg->physicalData.globalLegMountAngle, Vector3(0, leg->walkingData.distanceFromCenter, 0));

        Vector3 stepPoint = GetPointOnBezierCurve(stepControlPoints, 2, localT);


        Vector3 rotationControlPoints[3];
        rotationControlPoints[0] = leg->walkingData.cycleStartPoint;
        rotationControlPoints[1] = Vector3(
                                           0,
                                           leg->walkingData.distanceFromCenter,
                                           owner.physicalData.distanceFromGround
                                          );
        rotationControlPoints[2] = Vector3(
                                           rotationLength,
                                           leg->walkingData.distanceFromCenter,
                                           owner.physicalData.distanceFromGround
                                          );
                                        
        Vector3 rotationPoint = GetPointOnBezierCurve(rotationControlPoints, 3, localT);

        float stepMag = abs(expoLxJoyX) + abs(expoLxJoyY); // Forza del joystick movimento
        float rotationMag = abs(expoRxJoyX);                  // Forza del joystick rotazione
        float totalMag = stepMag + rotationMag;

        if (totalMag > 0.01f) {
            finalPoint = (stepPoint * stepMag + rotationPoint * rotationMag) / totalMag;
        } else {
            // not moving
            finalPoint = leg->walkingData.cycleStartPoint;
        }

    }
    else {

    }




    return Vector3();
}
