#ifndef RC_RECEIVER_H
#define RC_RECEIVER_H

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>


// RC transmitter data structure
struct RC_TransmitterData {
    int j1x = 2048;
    int j1y = 2048;
    int j2x = 2048;
    int j2y = 2048;
};

class RC_Transmitter {
public:
    RC_Transmitter();
    void Begin();
    void Update();
    
    // Returns current data
    const RC_TransmitterData& GetData() const { 
        return _currentData; }
    
    // Verify if RC transmitter is connected
    bool isConnected() { return (millis() - _lastReceiveTime) < 500; }

private:
    RF24 _radio;
    RC_TransmitterData _currentData;
    unsigned long _lastReceiveTime;
    uint8_t _address[6];
};

#endif