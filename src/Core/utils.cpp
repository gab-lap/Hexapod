#include "utils.h"
#include "models.h"


float lerp(float a, float b, float t) {
    return a * (1.0 - t) + (b * t);
}


Vector2 lerp(Vector2 a, Vector2 b, float t) {
    return Vector2(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
}


Vector3 lerp(Vector3 a, Vector3 b, float t) {
    return Vector3(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t));
}


float calculateHypotenuse(float x, float y) {
    return sqrt(x*x + y*y);
}


float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


int binomialCoefficient(int n, int k) {
    int ret = 1;

    for (int i = 1; i <= k; i++) {
        ret *= (n - (k - i));
        ret /= i;
    }

    return ret;
}


Vector2 GetPointOnBezierCurve(Vector2* points, int numPoints, float t) {
    Vector2 pos;

    for (int i = 0; i < numPoints; i++) {
        float b = binomialCoefficient(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
        pos.x += b * points[i].x;
        pos.y += b * points[i].y;
    }

    return pos;
}


Vector3 GetPointOnBezierCurve(Vector3* points, int numPoints, float t) {
    Vector3 pos;

    for (int i = 0; i < numPoints; i++) {
        float b = binomialCoefficient(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
        pos.x += b * points[i].x;
        pos.y += b * points[i].y;
        pos.z += b * points[i].z;
    }

    return pos;
}


Vector3 LocalToGlobal(const Vector3& localTarget, const Leg& leg)
{
    // Extracts the leg's physical data
    LegPhysicalData physicalData = leg.physicalData;

    // Computes sin and cos and converts them to radians
    float cosTheta = cos(physicalData.globalLegMountAngle * DEG_TO_RAD);
    float sinTheta = sin(physicalData.globalLegMountAngle * DEG_TO_RAD);

    // Finds the global X and Y coordinates of the Coxa
    float globalCoxaX = physicalData.coxaToRobotCenter * cosTheta;
    float globalCoxaY = physicalData.coxaToRobotCenter * sinTheta;

    // Apply rotation matrix (rotation matrix where Y is the "forward axis" relative to the leg and X is the "left" relative to the leg)
    // to rotate the target's position relative to leg and "rotates" it to match the robot's oritentation (it's coordinates system)
    float rotatedTargetX = localTarget.x * (-sinTheta) + localTarget.y * cosTheta;
    float rotatedTargetY = localTarget.x * (cosTheta) + localTarget.y * sinTheta;

    // Adds the global position of the Coxa (from Robot center to Coxa's servo rotation axis)
    // to the rotated target position 
    float globalTargetX = globalCoxaX + rotatedTargetX;
    float globalTargetY = globalCoxaY + rotatedTargetY;
    float globalTargetZ = localTarget.z - physicalData.bearingCapToPatternBasePlate;

    return Vector3(globalTargetX, globalTargetY, globalTargetZ);
}


Vector3 GlobaltoLocal(const Vector3 &globalTarget, Leg &leg)
{
    // Extracts the leg's physical data
    LegPhysicalData physicalData = leg.physicalData;

    // Computes sin and cos and converts them to radians
    float cosTheta = cos(physicalData.globalLegMountAngle * DEG_TO_RAD);
    float sinTheta = sin(physicalData.globalLegMountAngle * DEG_TO_RAD);

    // Finds the global X and Y coordinates of the Coxa
    float globalCoxaX = physicalData.coxaToRobotCenter * cosTheta;
    float globalCoxaY = physicalData.coxaToRobotCenter * sinTheta;

    // Calculates the difference between the "global" target and the Coxa to Robot's center distance.
    // It's like bringing the Leg's coordinate system (which origin is at the Coxa's servo rotation axis)
    // to the Robot's global coordinate system (center of the robot) or vice versa.
    float globalToLocalX = globalTarget.x - globalCoxaX;
    float globalToLocalY = globalTarget.y - globalCoxaY;

    // Apply rotation matrix (rotation matrix where Y is the "forward axis" relative to the leg and X is the "left" relative to the leg)
    // to rotate the target's position relative to the Robot (global) and "rotates" it to match the leg's oritentation (it's coordinates system)
    float localTargetX = globalToLocalX * (-sinTheta) + globalToLocalY * cosTheta;
    float localTargetY = globalToLocalX * cosTheta + globalToLocalY * sinTheta;
    float localTargetZ = globalTarget.z + physicalData.bearingCapToPatternBasePlate;

    return Vector3(localTargetX, localTargetY, localTargetZ);
}
