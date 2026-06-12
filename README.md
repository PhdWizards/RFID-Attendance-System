# RFID-Attendance-System
Developed an ESP32-based RFID attendance system that records user check-in/check-out events and automatically synchronizes attendance data with Google Sheets via Wi-Fi.

## Overview
The system allows students or employees to register attendance by scanning RFID cards.
Attendance records are automatically uploaded to Google Sheets through Wi-Fi.

## Features
- RFID card identification
- Wi-Fi connectivity
- Google Sheets integration
- Real-time attendance logging
- ESP32-based architecture

## Hardware
- ESP32 Dev Board
- RC522 RFID Reader
- RFID Cards/Tags

## Software
- Arduino Framework
- Google Apps Script
- Google Sheets API

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
