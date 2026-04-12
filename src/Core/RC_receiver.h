#ifndef RC_RECEIVER_H
#define RC_RECEIVER_H

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>


struct JoysticksRestingPositions {
    int j1x, j1y, j2x, j2y;
};

// RC transmitter data structure
struct RC_TransmitterData {
    uint8_t j1x = 0;
    uint8_t j1y = 0;
    uint8_t j2x = 0;
    uint8_t j2y = 0;
    uint8_t j1b : 1;
    uint8_t j2b : 1;
};


class RC_Transmitter {
private:
    RF24 _radio;
    RC_TransmitterData _currentData;
    uint8_t _lastJ1bState = 1;
    bool _j1bJustPressed = false;
    uint8_t _lastJ2bState = 1;
    bool _j2bJustPressed = false;
    unsigned long _lastReceiveTime;
    uint8_t _address[6];
    
public:
    RC_Transmitter();
    void Begin();
    void Update();
    
    // Returns current data
    const RC_TransmitterData& GetData() const { 
        return _currentData; }
    
    // Verify if RC transmitter is connected
    bool isConnected() { return (millis() - _lastReceiveTime) < 500; }

    bool isJ1Clicked() const { return _j1bJustPressed; }
    bool isJ2Clicked() const { return _j2bJustPressed; }
    
};

#endif