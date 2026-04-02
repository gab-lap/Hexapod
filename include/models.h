#ifndef MODELS_H
#define MODELS_H

#include <Arduino.h>
#include "vectors.h"

class Leg;

struct LegAngles {
    float angleJ1 = 0.0f;
    float angleJ2 = 0.0f;
    float angleJ3 = 0.0f;
    bool valid = false;

    LegAngles(float j1 = 0, float j2 = 0, float j3 = 0, bool v = false) 
        : angleJ1(j1), angleJ2(j2), angleJ3(j3), valid(v) {}

    bool isSafe() const {
        return (angleJ1 >= 30 && angleJ1 <= 150) && (angleJ3 >= 0 && angleJ3 <= 130);
    }

    bool isValid() const {
        return valid;
    }
};

struct LegPhysicalData {
    const float coxaLength = 46.4f; // R
    const float femurLength = 115.0f;
    const float tibiaLength = 200.0f;
    // If leg on the right set to 1, else to -1
    int position_multiplier = 0;
    // 1 for Front, 0 for Mid, -1 for Back
    int rotation_multiplier = 0;

    float coxaToRobotCenter = 0.0f;
    float globalLegMountAngle = 0.0f;
    float bearingCapToPatternBasePlate = 10.1f;

    LegPhysicalData(float initCoxaToRobotCenter, float initGlobalLegMountAngle, float initPositionMultiplier, float rotationMultiplier)
        : coxaToRobotCenter(initCoxaToRobotCenter), globalLegMountAngle(initGlobalLegMountAngle), position_multiplier(initPositionMultiplier), rotation_multiplier(rotationMultiplier) {}
};

struct LegWalkingData {
    float t = 0.0f;
    int cycleProgress = 0;
    Vector3 cycleStartPoint;
    Vector3 currentLegPosition;
    const float distanceFromCenter = 200.0f;
    float pushFraction;
};

struct RobotLegs {
    Leg* middleRight;
    Leg* frontRight;
    Leg* frontLeft;
    Leg* middleLeft;
    Leg* backLeft;
    Leg* backRight;  

    RobotLegs(Leg* initMiddleRight, Leg* initFrontRight, Leg* initFrontLeft, Leg* initMiddleLeft, Leg* initBackLeft, Leg* initBackRight)
        : middleRight(initMiddleRight), frontRight(initFrontRight), frontLeft(initFrontLeft), middleLeft(initMiddleLeft), backLeft(initBackLeft),backRight(initBackRight) {}
};

struct RobotPhysicalData {
    float height = 0; // bearingCapToPatternBasePlate
    float distanceFromGround = -120;
};

struct JoystickDataStream {

};

#endif
