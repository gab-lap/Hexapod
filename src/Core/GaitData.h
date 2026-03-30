#ifndef GAIT_DATA_H
#define GAIT_DATA_H

#include "Arduino.h"
#include "config.h"

enum GaitName {
    TRIPOD,
    RIPPLE,
    WAVE,
    BI,
    QUAD,
    JUMP,

    NUM_GAITS
};

struct GaitData {
    GaitName type;
    String label;

    float cycleOffsets[NUM_LEGS];
    float cycleDuration; // review if it's still needed
    float pushFraction;
    //float liftFraction = 1 - pushFraction;
    float maxStepLength;
    float maxRotationLength;
    float liftHeight;

    float stepLengthMultiplier;
    float cycleSpeedMultiplier;

};

namespace Gaits {
    extern const GaitData Tripod;
    extern const GaitData Ripple;
    extern const GaitData Wave;
    extern const GaitData Bi;
    extern const GaitData Quad;
    extern const GaitData Jump;
}

#endif