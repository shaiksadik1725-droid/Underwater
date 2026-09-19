# Underwater Acoustic Sensor Communication Prototype

An embedded communication experiment that transmits water-related sensor data using audio-frequency FSK and decodes it on a separate receiver.

## Overview
The transmitter reads temperature and TDS-oriented sensor data, converts text characters into binary data, and represents bits using two audio frequencies. The receiver measures the incoming frequency, reconstructs characters, parses the payload, and displays the decoded values on an I2C LCD.

## Communication Method
- Binary Frequency-Shift Keying (FSK)
- High tone represents one binary state
- Low tone represents the other
- Character-by-character transmission
- Receiver-side synchronization and decoding

## Technology
ESP32 / Arduino, C++, DS18B20/DallasTemperature, analog TDS input, microphone input, I2C LCD.

## Structure
```text
Underwater/
├── Transmiter/Transmiter.ino
├── Receiver/Receiver.ino
├── TRANSMITER_BLOCK.png
├── TRANSMITER_FLOW.png
├── TRANSMITTER_CIRCUIT.png
├── RECEIVER_BLOCK.png
├── RECEIVER_FLOW.png
└── RECIEVER_CIRCUIT.png
```

## Future Improvements
- Add checksums / CRC
- Improve synchronization and framing
- Increase communication speed
- Characterize range and error rate underwater
- Replace threshold decoding with frequency-domain detection
- Add retransmission and packet IDs

## Author
**Sadik Shaik**
