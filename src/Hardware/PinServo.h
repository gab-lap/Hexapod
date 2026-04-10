#ifndef PIN_SERVO_H
#define PIN_SERVO_H

#include "Servos.h"
#include "ESP32Servo.h"
#include <Adafruit_PWMServoDriver.h>

class PinServo : public VirtualServo {
private:
    Servo _servo;
    int _pin;
public:
    PinServo(int pin);

    void Begin() override;
    void WriteAngle(float angle) override;
    void SetMicroseconds(int initMinUs, int initMaxUs) override;
};

#endif