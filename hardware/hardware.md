
---
## ⚡ Hardware Components
- ESP32 Development Board  
- MQ-5 Gas Sensor  
- Buzzer  
- LEDs (Green + Red)  
- I2C LCD (16x2)  
- Servo Motor (optional for valve control)  
- Jumper wires, Breadboard/PCB  

---

## 🖼️ System Workflow
![System Diagram](GASDET.png)

---

## 📸 Hardware Setup
![Hardware Setup](circuit.jpg)

---

## ☁️ Firebase Integration
The system pushes alerts and location links to Firebase:  

![Firebase Screenshot](firebase.png)

---

## 💬 Telegram Alerts
Gas Guard bot sends real-time alerts to users:  

![Telegram Alerts](telegram.jpg)

---

## 🚀 How to Run
1. Install **Arduino IDE** and add ESP32 board manager.  
2. Install required libraries:  
   - `WiFi.h`  
   - `WiFiClientSecure.h`  
   - `UniversalTelegramBot.h`  
   - `HTTPClient.h`  
   - `ArduinoJson.h`  
   - `LiquidCrystal_PCF8574.h`  
   - `ESP32Servo.h`  

3. Open `Code/gas_leakage_detection.ino` and update:  
   - WiFi SSID & Password  
   - Firebase Credentials  
   - Telegram Bot Token & Chat ID  

4. Upload code to ESP32.  
5. Open Serial Monitor to see gas readings.  

---



## 📜 License
This project is licensed under the **MIT License** - feel free to use and modify.  

---

## 👨‍💻 Author
Developed by **B CHARAN TEJA GOUD** (CSE - AIML) 🚀  
