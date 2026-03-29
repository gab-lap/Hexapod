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
    uint8_t j1x;
    uint8_t j1y;
    uint8_t j2x;
    uint8_t j2y;
};


class RC_Transmitter {
private:
    RF24 _radio;
    RC_TransmitterData _currentData;
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
    
};

#endif