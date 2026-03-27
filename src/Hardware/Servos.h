#ifndef SERVOS_H
#define SERVOS_H

class VirtualServo {
public:
    float offset = 0.0f;
    int minUs = 500;
    int maxUs = 2500;

    virtual void Begin() = 0;
    virtual void WriteAngle(float angle) = 0;
};

#endif