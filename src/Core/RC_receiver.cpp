#include "RC_Receiver.h"
#include "config.h"


RC_Transmitter::RC_Transmitter() : _radio(CE_PIN, CSN_PIN) {
    _lastReceiveTime = 0;
    memcpy(_address, "00001", 6);
}

void RC_Transmitter::Begin() {
    // Initialize ESP32's custom SPI bus 
    SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CSN_PIN);

    if (!_radio.begin()) {
        Serial.println("Error: nRF24 not found");
        return;
    }
    _radio.setChannel(110);
    _radio.openReadingPipe(0, _address);
    _radio.setPALevel(RF24_PA_LOW);
    _radio.setDataRate(RF24_250KBPS);
    _radio.startListening();
    
    Serial.println("nRF24 Receiver found.");
}

void RC_Transmitter::Update() {
    if (_radio.available()) {
        // Read the data and update the struct
        _radio.read(&_currentData, sizeof(RC_TransmitterData));
        _lastReceiveTime = millis();
        
        // J1 press
        if (_currentData.j1b == 0 && _lastJ1bState == 1) {
            _j1bJustPressed = true;
        } else {
            _j1bJustPressed = false;
        }

        _lastJ1bState = _currentData.j1b;

        // J2 press
        if (_currentData.j2b == 0 && _lastJ2bState == 1) {
            _j2bJustPressed = true;
        } else {
            _j2bJustPressed = false;
        }

        _lastJ2bState = _currentData.j2b;

    }
    else {
        _j1bJustPressed = false;
        _j2bJustPressed = false;
    }
}