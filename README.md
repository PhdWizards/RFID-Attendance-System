![ESP32](https://img.shields.io/badge/ESP32-blue)

![RC522](https://img.shields.io/badge/RC522-green)

![Arduino](https://img.shields.io/badge/Arduino-teal)

![GoogleSheets](https://img.shields.io/badge/Google%20Sheets-brightgreen)

![WiFi](https://img.shields.io/badge/WiFi-orange)

# RFID-Attendance-System

![Prototype](photos/prototype.jpg)

Developed an ESP32-based RFID attendance system that records user check-in/check-out events and automatically synchronizes attendance data with Google Sheets via Wi-Fi.

## Overview
The system allows students or employees to register attendance by scanning RFID cards.
Attendance records are automatically uploaded to Google Sheets through Wi-Fi.

## Features
- RFID card identification using RC522
- Automatic attendance logging
- Check-in / Check-out detection
- Real-time synchronization with Google Sheets
- Wi-Fi connectivity via ESP32
- Compact 3D-printed enclosure
- Visual status indication using LEDs

## Tech Stack

### Hardware
- ESP32 DevKit
- RC522 RFID Reader
- RFID Cards/Tags
- Status LEDs

### Firmware
- Arduino Framework (C++)
- MFRC522 Library
- WiFi Library
- HTTPClient

### Cloud
- Google Sheets
- Google Apps Script

### Design
- Fusion 360

## System Architecture
RFID Card -> RC522 -> ESP32 -> Wi-Fi -> Google Sheets

## Future Improvements
- OLED display
- Local database backup
- NFC phone support
- Web dashboard

## Technical Challenges

### Attendance State Management
Implemented automatic IN/OUT detection logic using RFID card history.

### Wi-Fi Reliability
Added reconnection handling to prevent attendance data loss during network interruptions.

### Google Sheets Integration
Used HTTP requests to synchronize attendance events with a cloud-based spreadsheet.

## Mechanical Design
Custom enclosure designed in Fusion 360 and manufactured using FDM 3D printing.

## Wiring
![Wiring](photos/wiring.png)

## Hardware Connection
| RC522 Pin | ESP32 Pin | Description |
|-----------|-----------|-------------|
| SDA (SS)  | GPIO5     | SDA / SS    |
| SCK       | GPIO18    | SPI Clock   |
| MOSI      | GPIO23    | MOSI        |
| MISO      | GPIO19    | MISO        |
| RST       | GPIO22    | Reset       |
| 3.3V      | 3.3V      | Power       |
| GND       | GND       | Ground      |
