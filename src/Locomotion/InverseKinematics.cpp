#include "vectors.h"
#include "models.h"
#include "config.h"
#include "Arduino.h"

LegAngles ik(Vector3 target) {
    LegAngles ret;

    float x = target.x;
    float y = target.y;
    float z = -target.z;

    float A1_rad = atanf(x / y); // change for atan2f
    float h = sqrtf(x*x + y*y);
    float h1 = h - R;
    float l = sqrtf(z*z + h1*h1);

    float cos_alpha = (l*l + LJ2*LJ2 - LJ3*LJ3) / (2.0f * l * LJ2);
    float cos_A3    = (LJ2*LJ2 + LJ3*LJ3 - l*l) / (2.0f * LJ2 * LJ3);
    if (cos_alpha < -1.0f || cos_alpha > 1.0f || cos_A3 < -1.0f || cos_A3 > 1.0f)
        return ret;

    float alpha  = acosf(cos_alpha);
    float alpha1 = atanf(z / h1);
    float A2_rad = alpha + (-alpha1);
    float A3_rad = acosf(cos_A3);

    float a1 = degrees(A1_rad);
    float a2 = degrees(A2_rad);
    float a3 = degrees(A3_rad);

    a1 = 90.0f + a1;  //remember to remove the offsets (will be handled in the servo class)
    a2 = 45.0f + a2;
    a3 = 160.0f - a3; // -20 deg for tibia construction

    a1 = constrain(a1, 30.0f, 150.0f);
    a3 = constrain(a3,  0.0f, 130.0f);
    
    ret.angleJ1 = a1;
    ret.angleJ2 = a2;
    ret.angleJ3 = a3;
    ret.valid = true;
    
    return ret;
}