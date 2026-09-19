# Underwater Acoustic Sensor Communication Prototype

<p align="center">
  <strong>Audio-frequency FSK communication for transmitting water sensor data between embedded nodes</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Arduino-C++-00979D?logo=arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/FSK-Digital_Communication-2563EB" />
  <img src="https://img.shields.io/badge/Embedded-Prototype-4B5563" />
</p>

## Project at a Glance

| Item | Details |
|---|---|
| Domain | Embedded communication |
| Modulation | Binary FSK |
| Data | Temperature and TDS-oriented readings |
| Transmitter | Tone-based embedded node |
| Receiver | Frequency detection + LCD output |
| Status | Academic communication prototype |

## System Design

<p align="center">
  <img src="TRANSMITER_BLOCK.png" width="48%" alt="Transmitter block diagram" />
  <img src="RECEIVER_BLOCK.png" width="48%" alt="Receiver block diagram" />
</p>

## Overview

The transmitter converts sensor values into characters, converts each character into binary data, and sends the bits using two audio frequencies. The receiver estimates incoming frequency, reconstructs the byte stream, parses the payload, and displays the decoded values.

## Communication Flow

```mermaid
flowchart LR
    A[Temperature + TDS] --> B[Payload Encoding]
    B --> C[8-bit Characters]
    C --> D[Binary FSK Tones]
    D --> E[Acoustic Channel]
    E --> F[Frequency Detection]
    F --> G[Byte Reconstruction]
    G --> H[LCD Display]
```

## Technology Stack

- ESP32 / Arduino
- C++
- DallasTemperature / DS18B20
- Analog TDS input
- Microphone input
- I2C LCD
- Binary FSK

## Repository Structure

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

## Future Work

- Add packet framing
- Add CRC / checksum validation
- Improve synchronization
- Increase bit rate
- Characterize underwater range and BER
- Use FFT/Goertzel-based frequency detection
- Add retransmission and packet IDs

## Author

**Sadik Shaik**

Computer Engineering · Embedded Systems · Digital Communication
