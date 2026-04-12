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
        leg->ONorOFF = 1;
        leg->walkingData.cycleProgress = owner.currentGait->cycleOffsets[i] * _points;

        // Force legs into walking state when robot enters walk state
        if (leg->walkingData.t < leg->walkingData.pushFraction)
            leg->stateMachine.ChangeState(&leg->pushing);
        else
            leg->stateMachine.ChangeState(&leg->lifting);
    }
}

void RobotWalkState::Update()
{
    const RC_TransmitterData& transmitterData = owner.transmitter.GetData();  
    
    // ricorda di definire logica di cambio stato
    //Serial.print(" owner.transmitter.isJ2Clicked(): ");Serial.println(owner.transmitter.isJ2Clicked());
    if (owner.transmitter.isJ2Clicked()) {
        stateMachine.ChangeState(&owner.sleepState);
        return;
    }


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
    
    
    _forwardAmount = _leftJoystickCurrentMagnitude;
    _turnAmount = _rightJoystickCurrentVector.x;
    
    float progressChangeAmount = max(_forwardAmount, abs(_turnAmount)) * owner.currentGait->cycleSpeedMultiplier * globalSpeedMultiplier;
    
    for (int i = 0; i < NUM_LEGS; i++) {
        Leg* leg = owner.getLeg(i);
        
        // Incrementa il progresso
        leg->walkingData.cycleProgress += progressChangeAmount;

        // Reset del ciclo se supera il limite (es. 1000 punti)
        if (leg->walkingData.cycleProgress >= _points) {
            leg->walkingData.cycleProgress -= _points;
            // Importante: qui dovresti anche aggiornare cycleStartPoint con la posizione attuale
        }

        leg->walkingData.t = (float)leg->walkingData.cycleProgress / _points;
        leg->Update();
    }

    for (int i = 0; i < NUM_LEGS; i++) {
        Leg* leg = owner.getLeg(i);
        
        leg->MoveToPosition(getGaitPoint(leg, leg->walkingData.pushFraction)); // Can remove parameter from function and just access to pushfraction from leg in the function (to change)
    }


    // REMEMBER WHEN UPDATING THE WALK CYCLE VARIABLES, ONCE THE WALK CYCLE ENDED, TO UPDATE THE GAIT DATA 
    // (so that the gait can only effectively change once the walk cycle ended)
}

void RobotWalkState::Exit()
{
}

Vector3 RobotWalkState::getGaitPoint(Leg *leg, float pushFraction)
{
    if (_leftJoystickCurrentMagnitude < 0.5f && abs(_rightJoystickCurrentVector.x) < 0.5f) {
        return leg->walkingData.currentLegPosition; 
    }

    // Normalize right joystick
    float normRxJoystickX = _rightJoystickCurrentVector.x / 100.0f;
    // Exponential mapping
    float expoRxJoyX = normRxJoystickX; //(normRxJoystickX >= 0 ? 1 : -1) * (normRxJoystickX * normRxJoystickX); // Remember to remove or change exponential mapping also forthis
    // Apply exponential mapping
    float rotationLength = owner.currentGait->maxRotationLength * expoRxJoyX;


    // Normalizing each left joystick axis
    float normLxJoystickX = _leftJoystickCurrentVector.x / 100.f;
    float normLxJoystickY = _leftJoystickCurrentVector.y / 100.f;
    // Exponential mapping of each axis
    float expoLxJoyX = normLxJoystickX;//(normLxJoystickX >= 0 ? 1 : -1) * (normLxJoystickX * normLxJoystickX);
    float expoLxJoyY = normLxJoystickY;//(normLxJoystickY >= 0 ? 1 : -1) * (normLxJoystickY * normLxJoystickY);
    // Resulting exponential vector to apply
    Vector2 expo = Vector2(expoLxJoyX, expoLxJoyY);
    // Applying the exponential vector
    Vector2 stepLength = expo * owner.currentGait->maxStepLength * owner.currentGait->stepLengthMultiplier;
    // Constrain the result
    stepLength.x = constrain(stepLength.x, -owner.currentGait->maxStepLength, owner.currentGait->maxStepLength);
    stepLength.y = constrain(stepLength.y, -owner.currentGait->maxStepLength/2, owner.currentGait->maxStepLength/2);


    float t = leg->walkingData.t;
    float stepMag = abs(expoLxJoyX) + abs(expoLxJoyY); // Left Joystick force
    float rotationMag = abs(expoRxJoyX);                // Right Joystick force
    float totalMag = stepMag + rotationMag;             // total force
    if (totalMag < 0.0001f) 
        totalMag = 0.0001f;
    
    // LEG PUSHING
    if (t < pushFraction) {
        // Map the pushFraction to be a range from 0.0 to 1.0
        float localT = mapFloat(t, 0, pushFraction, 0, 1);

        // -------------------- DRAG STEP --------------------

        // Array containing the control points for stepping in a straight line
        Vector3 stepControlPoints[2];
        // First Control Point
        stepControlPoints[0] = leg->walkingData.cycleStartPoint;
        // Second Control Point
        float targetStepX = stepLength.y * leg->physicalData.position_multiplier;
        float targetStepY = stepLength.x * leg->physicalData.position_multiplier;

        stepControlPoints[1] = Vector3(
                                        targetStepX,
                                       -targetStepY + leg->walkingData.distanceFromCenter, // targetStepY is negated because a leg, to make the body move forward, has to push the opposite way
                                        owner.physicalData.distanceFromGround                                        
                                    ).rotateZ(/*leg->physicalData.globalLegMountAngle*/55.0 * leg->physicalData.rotation_multiplier, Vector3(0, leg->walkingData.distanceFromCenter, 0));
        
        // Resulting Vector for Stepping in a straight line
        Vector3 stepPoint = GetPointOnBezierCurve(stepControlPoints, 2, localT);

        // -------------------- DRAG ROTATE --------------------

        // Array containing the control points for rotation
        Vector3 rotationControlPoints[3];
        // First Control Point
        rotationControlPoints[0] = leg->walkingData.cycleStartPoint;
        // Second Control Point
        rotationControlPoints[1] = Vector3(
                                            0,
                                            leg->walkingData.distanceFromCenter,
                                            owner.physicalData.distanceFromGround
                                        );
        // Third Control Point
        rotationControlPoints[2] = Vector3(
                                            rotationLength,
                                            leg->walkingData.distanceFromCenter,
                                            owner.physicalData.distanceFromGround
                                        );
        // Resulting Vector for Rotating                                
        Vector3 rotationPoint = GetPointOnBezierCurve(rotationControlPoints, 3, localT);

        // If any joystick is being moved return the weighted average of the two points
        // else return the start point of the cycle

        //if (totalMag > 0.01f) 
        return (stepPoint * stepMag + rotationPoint * rotationMag) / totalMag;
        //else 
        //    return leg->walkingData.cycleStartPoint;
    }
    // LEG LIFTING
    else {
        float localT = mapFloat(t, pushFraction, 1, 0, 1);
        float liftHeight = owner.currentGait->liftHeight; 
        float landHeight = 15.0f; // Sostituisci con la variabile reale del tuo robot, es: owner.physicalData.legLandHeight

        // -------------------- LIFT STEP --------------------

        // Array containing the control points for stepping
        Vector3 strafeControlPoints[4];
        // First Control Point
        strafeControlPoints[0] = leg->walkingData.cycleStartPoint;
        // Second Control Point
        strafeControlPoints[1] = leg->walkingData.cycleStartPoint + Vector3(0, 0, liftHeight);
        // Third Control Point
        strafeControlPoints[2] = Vector3(
                                        -stepLength.y * leg->physicalData.position_multiplier,
                                        stepLength.x * leg->physicalData.position_multiplier + leg->walkingData.distanceFromCenter,
                                        owner.physicalData.distanceFromGround + landHeight
                                    ).rotateZ(/*leg->physicalData.globalLegMountAngle*/55.0 * leg->physicalData.rotation_multiplier, Vector3(0, leg->walkingData.distanceFromCenter, 0));
        // Fourth Control Point
        strafeControlPoints[3] = Vector3(
                                        -stepLength.y * leg->physicalData.position_multiplier,
                                        stepLength.x * leg->physicalData.position_multiplier + leg->walkingData.distanceFromCenter,
                                        owner.physicalData.distanceFromGround
                                    ).rotateZ(/*leg->physicalData.globalLegMountAngle*/55.0 * leg->physicalData.rotation_multiplier, Vector3(0, leg->walkingData.distanceFromCenter, 0));
        // Resulting Vector for Stepping
        Vector3 straightPoint = GetPointOnBezierCurve(strafeControlPoints, 4, localT);

        // -------------------- LIFT ROTATE --------------------

        // Array containing the control points for rotating
        Vector3 rotateControlPoints[5];
        // First Control Point
        rotateControlPoints[0] = leg->walkingData.cycleStartPoint;
        // Second Control Point
        rotateControlPoints[1] = leg->walkingData.cycleStartPoint + Vector3(0, 0, liftHeight);
        // Third Control Point
        rotateControlPoints[2] = Vector3(
            0,
            leg->walkingData.distanceFromCenter,
            owner.physicalData.distanceFromGround + liftHeight
        );
        // Fourth Control Point
        rotateControlPoints[3] = Vector3(
            -rotationLength,
            leg->walkingData.distanceFromCenter,
            owner.physicalData.distanceFromGround + landHeight
        );
        // Fifth Control Point
        rotateControlPoints[4] = Vector3(
            -rotationLength,
            leg->walkingData.distanceFromCenter,
            owner.physicalData.distanceFromGround
        );
        // Resulting Vector for Rotating
        Vector3 rotatePoint = GetPointOnBezierCurve(rotateControlPoints, 5, localT);

        //if (totalMag > 0.01f)
        return (straightPoint * stepMag + rotatePoint * rotationMag) / totalMag;
        //else
            // Se fermo, torna dolcemente alla posizione neutra (0, distCenter, Ground)
        //    return GetPointOnBezierCurve(strafeControlPoints, 4, localT);
    }
}
