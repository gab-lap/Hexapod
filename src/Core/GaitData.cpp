#include "GaitData.h"

namespace Gaits {
    /*const*/ GaitData Tripod = {
        TRIPOD,     // Type
        "Tripod",   // Name
        {0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f}, // MR, FR, and so on counterclockwise...
        1000.0f, // Cycle Duration
        0.55f,              // pushFraction (50% a terra)
        150.0f,             // maxStepLength
        80.0f,              // maxRotationLength
        100.0f,             // liftHeight
        0.50f,              // stepLengthMultiplier
        0.75f               // cycleSpeedMultiplier
    };

    const GaitData Ripple = {
        RIPPLE,
        "Ripple",
        {0.0f, 0.67f, 0.33f, 0.83f, 0.17f, 0.5f}, // {0.0f, 0.5f, 0.25f, 0.75f, 0.25f, 0.5f}
        1000.0f,
        0.6f,               // pushFraction       // 0.66f
        200.0f,             // maxStepLength
        80.0f,
        100.0f,             // liftHeight
        1.1f,              // stepLengthMultiplier
        1.1f               // cycleSpeedMultiplier
    };

    const GaitData Wave = {
        WAVE, 
        "Wave", 
        {0.0f, 0.16f, 0.33f, 0.5f, 0.66f, 0.83f}, 
        1000.0f,  //3000.0f
        0.83f,             // pushFraction
        200.0f,             // maxStepLength
        80.0f,
        130.0f,             // liftHeight
        1.4f,              // stepLengthMultiplier  // 0.8
        0.5f               // cycleSpeedMultiplier
    };

    // others to be defined
}
