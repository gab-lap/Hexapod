#ifndef MODELS_H
#define MODELS_H

#include <Arduino.h>

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

    float coxaToRobotCenter = 0.0f;
    float globalLegMountAngle = 0.0f;
    float bearingCapToPatternBasePlate = 10.1f;

    LegPhysicalData(float initCoxaToRobotCenter, float initGlobalLegMountAngle)
        : coxaToRobotCenter(initCoxaToRobotCenter), globalLegMountAngle(initGlobalLegMountAngle) {}
};

struct RobotPhysicalData {
    float height = 0; // bearingCapToPatternBasePlate
};

struct JoystickDataStream {

};

#endif
