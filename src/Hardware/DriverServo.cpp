#include "DriverServo.h"

// Servos using servo driver (PCA9685) implementation

DriverServo::DriverServo(Adafruit_PWMServoDriver *pwmDriver, int channel)
{
    _pwmDriver = pwmDriver;
    _channel = channel;
}

void DriverServo::Begin()
{

}

void DriverServo::WriteAngle(float angle)
{
    float pulse = map(angle + offset, 0, 180, minUs, maxUs);
    _pwmDriver->setPWM(_channel, 0, pulse);
}
