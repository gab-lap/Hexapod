#include "vectors.h"

// ------------ Vector2 implementation ------------

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float initX, float initY) : x(initX), y(initY) {}

// Returns the vector as a string
String Vector2::toString() {
    return ("(" + String(x) + "," + String(y) + ")");
}

// Returns the magnitude of the vector
float Vector2::magnitude() const {
    return sqrt(x*x + y*y);
}

// Normalizes the vector
void Vector2::normalize() {
    float mag = magnitude();
    if (mag > 0) {
        x = x / mag;
        y = y / mag;
    }
}

// Overrides the sum operator to implement vector sum
Vector2 Vector2::operator+(const Vector2& vectorToSum) const {
    return Vector2(x + vectorToSum.x, y + vectorToSum.y);
}

// Overrides the multiplication operator to implement vector multiplication
Vector2 Vector2::operator*(const Vector2& vectorToMultiply) const {
    return Vector2(x * vectorToMultiply.x, y * vectorToMultiply.y);
}

// Overrides the multiplication operator to implement vector by scalar multiplication
Vector2 Vector2::operator*(const float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

// Rotates vector by given angle around a pivot point
Vector2 Vector2::rotate(int angleDeg, const Vector2& pivot) const {
    if (angleDeg == 0)
        return Vector2(x, y);

    // Translates point so pivot point is at the origin
    float tempX = x - pivot.x;
    float tempY = y - pivot.y;
    float angleRad = radians(angleDeg);

    // Rotates point by angle (around the origin with 2D rotation matrix)
    float x_rotated = tempX * cos(angleRad) - tempY * sin(angleRad);
    float y_rotated = tempX * sin(angleRad) + tempY * cos(angleRad);

    // Translates point back to original position
    tempX = x_rotated + pivot.x;
    tempY = y_rotated + pivot.y;

    return Vector2(tempX, tempY);
}


// ------------ Vector3 implementation ------------

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(float initX, float initY, float initZ) : x(initX), y(initY), z(initZ) {}

// Returns the vector as a string
String Vector3::toString() {
    return ("(" + String(x) + "," + String(y) + "," + String(z) + ")");
}

// Returns the magnitude of the vector
float Vector3::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}

// Normalizes the vector
void Vector3::normalize() {
    float mag = magnitude();
    if (mag > 0) {
        x = x / mag;
        y = y / mag;
        z = z / mag;
    }
}

bool Vector3::operator != (const Vector3& vectorToCompare) const {
    return (x != vectorToCompare.x || y != vectorToCompare.y || z != vectorToCompare.z);
}

bool Vector3::operator == (const Vector3& vectorToCompare) const {
    return (x == vectorToCompare.x && y == vectorToCompare.y && z == vectorToCompare.z);
}

Vector3 Vector3::operator+(const Vector3& vectorToSum) const {
    return Vector3(x + vectorToSum.x, y + vectorToSum.y, z + vectorToSum.z);
}

Vector3 Vector3::operator-(const Vector3& vectorToSubtract) const {
    return Vector3(x - vectorToSubtract.x, y - vectorToSubtract.y, z - vectorToSubtract.z);
}

Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator*(const Vector3& vectorToMultiply) const {
    return Vector3(x * vectorToMultiply.x, y * vectorToMultiply.y, z * vectorToMultiply.z);
}

Vector3 Vector3::operator/(float scalar) const {
    return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3 Vector3::operator/(const Vector3& vectorToDivide) const {
    return Vector3(x / vectorToDivide.x, y / vectorToDivide.y, z / vectorToDivide.z);
}

Vector3 Vector3::rotate(float angleDeg, const Vector2& pivot) const {
    if (angleDeg == 0) 
        return Vector3(x, y, z);

    float tempX = x - pivot.x;
    float tempY = y - pivot.y;
    float angleRad = radians(angleDeg);

    float x_rotated = tempX * cos(angleRad) - tempY * sin(angleRad);
    float y_rotated = tempX * sin(angleRad) + tempY * cos(angleRad);

    tempX = x_rotated + pivot.x;
    tempY = y_rotated + pivot.y;

    return Vector3(tempX, tempY, z);
}

// Yaw, rotate around Z axis (XY plane)
Vector3 Vector3::rotateZ(float angleDeg, const Vector3 pivot) const {
    if (angleDeg == 0) 
        return Vector3(x, y, z);

    float angleRad = radians(angleDeg);
    float tempX = x - pivot.x;
    float tempY = y - pivot.y;

    return Vector3(
            tempX * cos(angleRad) - tempY * sin(angleRad) + pivot.x,
            tempX * sin(angleRad) + tempY * cos(angleRad) + pivot.y,
            z 
            );
}

// Roll, rotate around X axis (YZ plane)
Vector3 Vector3::rotateX(float angleDeg, const Vector3 pivot) const {
    if (angleDeg == 0) 
        return Vector3(x, y, z);

    float angleRad = radians(angleDeg);
    float tempY = y - pivot.y;
    float tempZ = z - pivot.z;

    return Vector3(
        x,
        tempY * cos(angleRad) - tempZ * sin(angleRad) + pivot.y,
        tempY * sin(angleRad) + tempZ * cos(angleRad) + pivot.z
        );
}

// Pitch, rotate around Y axis (XZ plane)
Vector3 Vector3::rotateY(float angleDeg, const Vector3& pivot) const {
    if (angleDeg == 0) 
        return Vector3(x, y, z);

    float angleRad = radians(angleDeg);
    float tempX = x - pivot.x;
    float tempZ = z - pivot.z;

    return Vector3(
        tempX * cos(angleRad) - tempZ * sin(angleRad) + pivot.x,
        y,
        tempX * sin(angleRad) + tempZ * cos(angleRad) + pivot.z
    );
}

float Vector3::distanceTo(const Vector3& secondVector) const {
    double dx = secondVector.x - x;
    double dy = secondVector.y - y;
    double dz = secondVector.z - z;

    return sqrt(dx*dx + dy*dy + dz*dz);
}