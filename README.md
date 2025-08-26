# 🔥 Gas Leakage Detection and Alert System  

## 📌 Overview  
This project is a **Gas Leakage Detection and Alert System** designed to detect hazardous gas leaks (like LPG/CO) and immediately alert users through **local alarms, Telegram notifications, and Firebase integration**. It is built using **ESP32** and **MQ-5 Gas Sensor**, with added safety features like automatic servo-based control.  

The system is highly useful for **homes, industries, and laboratories** where gas leakage poses a serious risk.  

---

## ⚙️ Features  
- ✅ **Real-time Gas Detection** using MQ-5 gas sensor.  
- ✅ **Two-level Alert System**:  
  - Level 1 → Local buzzer + LCD warning.  
  - Level 2 → Telegram bot alert + Servo activation.  
- ✅ **Remote Monitoring** via Telegram commands.  
- ✅ **Firebase Integration** – Logs leak events with location details.  
- ✅ **LCD Display** for live status of gas concentration.  
- ✅ **Automatic Servo Mechanism** for safety action (like closing a valve).  
- ✅ **IoT Integration** with WiFi support.  

---

## 🛠️ Hardware Requirements  
- ESP32 Microcontroller  
- MQ-5 Gas Sensor  
- Buzzer  
- Servo Motor  
- LCD Display (16x2 / I2C based)  
- 18650 Battery Pack / Power Supply  
- Jumper Wires & Breadboard  
- WiFi connection  

---

## 💻 Software Requirements  
- Arduino IDE / PlatformIO  
- Firebase Realtime Database (Google Firebase)  
- Telegram Bot API  
- C/C++ (Arduino Framework)  

---

## 🔗 System Workflow  
1. **MQ-5 sensor** detects gas leakage.  
2. **ESP32** processes the sensor data.  
3. If gas exceeds threshold:  
   - Buzzer and LCD activate.  
   - Telegram bot sends alerts to the user.  
   - Servo motor triggers emergency action.  
   - Location link pushed to Firebase.  
4. User can **remotely check status** via Telegram commands.  

---


