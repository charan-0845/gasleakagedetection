# 🚨 Gas Leakage Detection System
---
A real-time **Gas Leakage Detection System** using **ESP32**, **MQ-5 Gas Sensor**, and **Telegram Bot Alerts**.  
This system ensures safety by continuously monitoring gas levels and triggering alerts with automated actions.

---



## ⚙️ Features

- 📡 **Real-time Gas Monitoring** using MQ-5 sensor.
- 🔔 **Local Buzzer Alert** when gas exceeds threshold.
- 📲 **Telegram Bot Alerts**:
  - Stage 1: Warning Message.
  - Stage 2: Critical Alert + Location link.
- 🔧 **Servo Motor Activation** to cut off supply (optional).
- 📊 **Firebase Logging** for alert history.
- 🌐 **Web & Remote Access** for monitoring.
- 💬 `\gas level` Telegram command to check live gas value.

---

## 🛠️ Hardware Components

- **ESP32** (WiFi-enabled microcontroller)  
- **MQ-5 Gas Sensor** (LPG, CH4, H2 detection)  
- **Buzzer** (local alert)  
- **Servo Motor** (optional valve control)  
- **LCD Display** (for live gas readings)  
- **18650 Batteries + Charger**  
- Supporting resistors, wires, and chassis  

Detailed hardware setup is in [`hardware/hardware.md`](hardware/hardware.md).

---

## 🔄 Detailed Workflow

The system monitors gas levels continuously and responds based on thresholds:

### 1️⃣ Normal Condition
- **Gas level < 200 ppm**
- LCD: `Safe`
- Buzzer: **OFF**
- No alert sent to Telegram
- Firebase: **No entry**

---

### 2️⃣ Warning Level
- **200 ppm ≤ Gas level < 400 ppm**
- LCD: `Warning: Gas Detected`
- Buzzer: **Beeping Slowly**
- Telegram Alert (Stage 1):  
  `"⚠️ Warning: Gas level exceeded safe limit!"`  
- Firebase: **Warning Logged**

---

### 3️⃣ Critical Level
- **Gas level ≥ 400 ppm**
- LCD: `CRITICAL: Gas Leakage`
- Buzzer: **Continuous Alarm**
- Servo: **Activated to close valve** (if connected)
- Telegram Alert (Stage 2):
- Firebase: **Critical Entry Logged**

---

### 4️⃣ Remote Monitoring
- User can send `\gas level` command to Telegram Bot.  
- Bot replies with:  
`"Current Gas Level: XXX ppm"`

---

## 🚀 Setup & Usage

1. Flash the ESP32 with the code in [`firmware/`](firmware/).  
2. Configure WiFi and Firebase credentials.  
3. Connect hardware as per [`hardware/circuit_diagram.png`](hardware/circuit_diagram.png).  
4. Run system – monitor via LCD, Telegram, and Firebase.

---

## 📸 Project Demo

(Add screenshots / photos of your hardware + Telegram alerts here)

---

## 👨‍💻 Team Members
- Charan 
- Rithya  
- Deeksha  
- Surya  
- Yashaswini  

---

## 📜 License
This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.




