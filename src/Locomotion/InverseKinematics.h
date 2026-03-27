#ifndef INVERSE_KINEMATICS_H
#define INVERSE_KINEMATICS_H

#include "models.h"
#include "vectors.h"

// Calculates the servo angles for a single leg given a 3D target position
LegAngles ik(Vector3 target);

#endif