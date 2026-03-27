#ifndef VECTORS_H // Preprocessor directives (used instead of #pragma once for portability)
#define VECTORS_H

#include "Arduino.h"


class Vector2 {
public:
    float x;
    float y;

    // Constructors
    Vector2();
    Vector2(float initX, float initY);

    // Methods
    String toString();
    float magnitude() const;
    void normalize();
    Vector2 rotate(int angleDeg, const Vector2& pivot) const;

    // Math Operators
    Vector2 operator+(const Vector2& vectorToSum) const;
    Vector2 operator*(const Vector2& vectorToMultiply) const;
    Vector2 operator*(const float scalar) const;
};

class Vector3 {
public:
    float x;
    float y;
    float z;

    // Constructors
    Vector3();
    Vector3(float initX, float initY, float initZ);

    // Methods
    String toString();
    float magnitude() const;
    void normalize();
    float distanceTo(const Vector3& secondVector) const;
    
    // Rotations
    Vector3 rotate(float angleDeg, const Vector2& pivot) const;
    Vector3 rotateZ(float angleDeg, Vector3 pivot = Vector3(0, 0, 0)) const;
    Vector3 rotateX(float angleDeg, Vector3 pivot = Vector3(0, 0, 0)) const;
    Vector3 rotateY(float angleDeg, const Vector3& pivot = Vector3(0, 0, 0)) const;

    // Comparison Operators
    bool operator != (const Vector3& vectorToCompare) const;
    bool operator == (const Vector3& vectorToCompare) const;

    // Math Operators
    Vector3 operator+(const Vector3& vectorToSum) const;
    Vector3 operator-(const Vector3& vectorToSubtract) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator*(const Vector3& vectorToMultiply) const;
    Vector3 operator/(float scalar) const;
    Vector3 operator/(const Vector3& vectorToDivide) const;
};

#endif