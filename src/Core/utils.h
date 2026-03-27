#ifndef UTILS_H
#define UTILS_H

#include "vectors.h"
#include "Leg.h"

/// @brief Linearly interpolates between two floats.
/// @param a Starting value.
/// @param b Ending value.
/// @param t Interpolation factor (0.0 to 1.0).
/// @return The value at point t between a and b.
float lerp(float a, float b, float t);

/// @brief Linearly interpolates between two Vector2 positions.
/// @param a Starting Vector2.
/// @param b Ending Vector2.
/// @param t Interpolation factor (0.0 to 1.0).
/// @return The Vector2 position at point t.
Vector2 lerp(Vector2 a, Vector2 b, float t);

/// @brief Linearly interpolates between two Vector3 positions.
/// @param a Starting Vector3.
/// @param b Ending Vector3.
/// @param t Interpolation factor (0.0 to 1.0).
/// @return The Vector3 position at point t.
Vector3 lerp(Vector3 a, Vector3 b, float t);

/// @brief Calculates the hypotenuse of a rectangle triangle.
/// @param x The length of the first side.
/// @param y The length of the second side.
/// @return The square root of (x^2 + y^2).
float calculateHypotenuse(float x, float y);

/// @brief Re-maps a float value from one range to another.
/// @param x The value to map.
/// @param in_min The lower bound of the input range.
/// @param in_max The upper bound of the input range.
/// @param out_min The lower bound of the output range.
/// @param out_max The upper bound of the output range.
/// @return The mapped value as a float.
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);

/// @brief Calculates the binomial coefficient (n choose k) with the formula (n!) / (k! * (n - k)!).
/// @param n Total number of points in the curve minus one.
/// @param k The current point index.
/// @return The calculated coefficient.
int binomialCoefficient(int n, int k);

/// @brief Calculates a 2D coordinate on a Bezier curve at a given progress t.
/// @param points Pointer to an array of Vector2 control points.
/// @param numPoints The number of control points in the array.
/// @param t Progress along the curve (0.0 to 1.0).
/// @return The calculated Vector2 position on the curve.
Vector2 GetPointOnBezierCurve(Vector2* points, int numPoints, float t);

/// @brief Calculates a 3D coordinate on a Bezier curve at a given progress t.
/// @param points Pointer to an array of Vector3 control points.
/// @param numPoints The number of control points in the array.
/// @param t Progress along the curve (0.0 to 1.0).
/// @return The calculated Vector3 position on the curve.
Vector3 GetPointOnBezierCurve(Vector3* points, int numPoints, float t);

/// @brief Converts a 3D coordinate from a leg's local coordinate system to the robot's global coordinate system.
/// @param localTarget Position relative to the leg's Coxa (it's coordinate system).
/// @param leg The Leg object containing physical mounting data.
/// @return Vector3 position relative to the center of the robot.
Vector3 LocalToGlobal(Vector3& localTarget, Leg& leg);

/// @brief Converts a 3D coordinate from the robot's global center point to a specific leg's local coordinate system.
/// @param globalTarget The target position relative to the center of the robot.
/// @param leg The Leg object containing physical mounting data.
/// @return Position relative to the leg's Coxa (it's coordinate system).
Vector3 GlobaltoLocal(Vector3& globalTarget, Leg& leg);

/// @brief A macro to execute a block of code at a specific time interval.
/// Creates a static timer variable unique to each call location.
/// @param interval The time to wait between executions in milliseconds.
/// @usage every(500) { Serial.println("Happens every 0.5 seconds"); }
#define every(interval)\
    static uint32_t __every__##interval = millis();\
    if (millis() - __every__##interval >= interval && (__every__##interval = millis()))

#endif