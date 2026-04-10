#include "PinServo.h"

// Servos using GPIO pins implementation

PinServo::PinServo(int pin)
{
    _pin = pin;
}

void PinServo::Begin()
{
    _servo.attach(_pin, minUs, maxUs);
}

void PinServo::WriteAngle(float angle)
{
    _servo.write(angle + offset);
}

void PinServo::SetMicroseconds(int initMinUs, int initMaxUs)
{
    minUs = initMinUs;
    maxUs = initMaxUs;
}
