# 🌍 ESP32 Earthquake Detector with Web Server

An **ESP32-based earthquake detection system** that uses a vibration sensor to detect tremors, and provides **real-time alerts** through a buzzer, LED, and a **web interface** hosted on the ESP32. The web interface updates instantly using WebSockets, ensuring fast notification during an earthquake event.

---

## 📖 Introduction
This project demonstrates how to build a **low-cost earthquake detector** using the **ESP32 microcontroller**.  
The system continuously monitors vibrations from a connected sensor. When tremors are detected:  
- An **LED** turns on,  
- A **buzzer** sounds an alarm,  
- The **web page** hosted by the ESP32 displays an **Earthquake Detected!** alert in real-time.  

After a configurable duration, the system resets and resumes monitoring.  

---

## 🛠️ Hardware Requirements
- **ESP32 Development Board**  
- **Vibration Sensor** (SW-420 module or equivalent)  
- **LED**  
- **Buzzer**  
- Jumper wires, breadboard, USB cable  

---

## 🔌 Circuit Connections

| Component       | ESP32 Pin |
|-----------------|-----------|
| Vibration Sensor Signal | GPIO 4 |
| LED (positive)  | GPIO 25  |
| Buzzer (positive) | GPIO 26 |
| All Grounds (sensor, LED, buzzer) | GND |
| Power (Sensor VCC) | 3.3V / 5V |

---

## ⚙️ Software Requirements
- Arduino IDE (with ESP32 board support installed)  
- Libraries:  
  - `WiFi.h`  
  - `ESPAsyncWebServer.h`  
  - `AsyncTCP.h`  

---

## 📜 Features
- Detects vibrations indicating possible earthquake activity.  
- Activates LED and buzzer for visual and audible alerts.  
- Hosts a **real-time web dashboard** on the ESP32:  
  - Displays current system status (Safe / Earthquake Detected).  
  - Updates instantly via WebSocket (no page refresh required).  
- Automatically clears alerts after a set duration.  

---

## 🚀 How It Works
1. ESP32 connects to your Wi-Fi network.  
2. The vibration sensor monitors for tremors.  
3. If vibration is detected:  
   - LED turns ON.  
   - Buzzer beeps continuously.  
   - Web interface shows **Earthquake Detected!**.  
4. After ~8 seconds, the system resets to normal mode (LED OFF, buzzer OFF).  

---

## 🌐 Web Interface Preview
When you access the ESP32 IP in your browser:  

- **Safe Mode**:  
(shown in green)  

- **Alert Mode**:  
(shown in red with buzzer + LED active)  

---

## 👨‍💻 Author
Developed by **Rahul A**  
Feel free to fork, modify, and contribute!  

