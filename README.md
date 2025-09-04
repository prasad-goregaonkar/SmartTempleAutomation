# SmartTempleAutomation
Smart Temple Automation System with Lighting &amp; Audio Control
1. Overview
This project is an IoT-based Smart Temple Automation System designed to automate temple rituals such as lighting lamps, playing devotional music, and controlling relays based on sensor input.

It uses Arduino UNO, PIR motion sensor, Ultrasonic sensor, and LDR sensor to detect presence, distance, and day/night conditions.  
The system is built to ensure energy efficiency and provide an automated spiritual experience.

2. Features
Music Playback using DFPlayer Mini (optional)  
Relay Control for temple lamps, diya, and lights  
PIR Motion Sensor detects human presence  
Ultrasonic Sensor ensures person is near before activation  
LDR Sensor distinguishes between day & night for smart lighting  
Auto shutdown after 6 minutes with reset capability  
Separate relay power supply for reliability  

3.  Components Used
- Arduino UNO  
- Ultrasonic Sensor (HC-SR04)  
- PIR Motion Sensor (HC-SR501)  
- LDR + 10kΩ Resistor  
- DFPlayer Mini + Speaker (optional for audio)  
- Relay Module (4-channel / 6-channel)  
- LEDs (for simulation in Tinkercad instead of real lamps)  
- External 5V Power Supply for relays  

4. Circuit Diagram

Designed in [Tinkercad](https://www.tinkercad.com/)

5. Arduino Code
Code is available in [`Arduino_Code/temple_automation.ino`](./Arduino_Code/temple_automation.ino).  

6.  How It Works
1. When a devotee approaches the temple, PIR detects motion.  
2. Ultrasonic sensor confirms the person is within 1 ft (30 cm).  
3. LDR checks ambient light:  
   - 🌞 Daytime → Only devotional music plays.  
   - 🌙 Nighttime → Lamps + music are activated.  
4. Relays remain ON for 6 minutes.  
5. After time elapses, the system resets automatically.  

7.  Future Enhancements
- Integration with IoT (Blynk / MQTT) for remote monitoring  
- Mobile app control for manual override  
- RTC (Real Time Clock) module for fixed-time rituals  
- Solar panel integration for eco-friendly operation  

8. Author
- Prasad Goregaonkar  
  Computer Engineering | IoT & Automation Enthusiast  

---
