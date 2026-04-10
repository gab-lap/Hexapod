#ifndef DRIVER_SERVO_H
#define DRIVER_SERVO_H

#include "Servos.h"
#include "ESP32Servo.h"
#include <Adafruit_PWMServoDriver.h>

class DriverServo : public VirtualServo {
private:
    Adafruit_PWMServoDriver* _pwmDriver;
    int _channel;
public:
    DriverServo(Adafruit_PWMServoDriver* pwmDriver, int channel);

    void Begin() override;
    void WriteAngle(float angle) override;
    void SetMicroseconds(int initMinUs, int initMaxUs) override;
};

#endif