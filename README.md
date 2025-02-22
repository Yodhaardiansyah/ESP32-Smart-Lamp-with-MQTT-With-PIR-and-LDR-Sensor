# **ESP32 Smart Lamp - MQTT Controlled Lighting System With PIR and LDR Sensor**  
🚀 **Developed by:** *Yodha Ardiansyah (arunovasi.my.id)*  

---

## **📌 Project Overview**  
This project allows you to control a **smart lamp** using an **ESP32** and **MQTT**.  
The system reads data from an **LDR (Light Sensor)** and a **PIR (Motion Sensor)**, then sends it to an MQTT broker.  
The lamp can be turned **ON/OFF remotely** via MQTT messages.  

---

## **🔧 Features**  
✅ **WiFi & MQTT Connectivity** – Connects to an MQTT broker to receive and send data  
✅ **LDR Sensor** – Detects ambient light levels  
✅ **PIR Sensor** – Detects motion to trigger the lamp  
✅ **Remote Control via MQTT** – Turn the lamp ON/OFF remotely  
✅ **Automatic Reconnect** – Reconnects if WiFi or MQTT disconnects  
✅ **Compact & Efficient Code** – Optimized for ESP32  

---

## **📜 Requirements**  
### **🛠 Hardware**  
- **ESP32**  
- **Relay Module** (to control the lamp)  
- **LDR Sensor** (Light sensor)  
- **PIR Sensor** (Motion sensor)  

### **💾 Software & Libraries**  
- **Arduino IDE** (or PlatformIO)  
- **WiFi.h** (Built-in ESP32 library)  
- **PubSubClient** (for MQTT)  

---

## **📥 Installation & Setup**  

### **1️⃣ Install Required Libraries**  
In **Arduino IDE**, install the following libraries via **Library Manager**:  
✅ **PubSubClient** (by Nick O’Leary)  

### **2️⃣ Configure Your Credentials**  
Edit the following lines in the **code** with your actual credentials:  

```cpp
// WiFi Configuration
const char* ssid = "your_wifi_ssid";       
const char* password = "your_wifi_password";  

// MQTT Configuration
const char* mqtt_server = "your_mqtt_server";
const int mqtt_port = 1883;
const char* mqtt_user = "your_mqtt_username";
const char* mqtt_password = "your_mqtt_password";
```

### **3️⃣ Upload the Code**  
- Connect your ESP32 to your PC  
- Select the correct **Board & Port** in Arduino IDE  
- Click **Upload**  

### **4️⃣ Monitor Output**  
- Open the **Serial Monitor** (`115200 baud`)  
- You should see logs indicating **WiFi & MQTT connection status**  

---

## **📡 How It Works**  

### **📤 Sensor Data Transmission**  
- The ESP32 reads **PIR & LDR sensor values**  
- Sends the data to the MQTT topic:  
  ```
  your_topic/smartlamp/sensors
  ```
- **Example Payload Sent:**
  ```json
  {
    "ldr": 1,
    "pir": 0
  }
  ```

### **📥 Receiving MQTT Commands**  
- The ESP32 listens for messages on:  
  ```
  your_topic/smartlamp/control
  ```
- **Accepted Commands:**  
  - `"on"` → **Turns lamp ON**  
  - `"off"` → **Turns lamp OFF**  

---

## **⚙️ Full MQTT Topics**  

| **Function**     | **MQTT Topic**                     | **Example Payload** |
|-----------------|---------------------------------|----------------|
| Send Sensor Data | `your_topic/smartlamp/sensors` | `{"ldr":1, "pir":0}` |
| Control Lamp     | `your_topic/smartlamp/control` | `"on"` or `"off"` |

---

## **💡 Future Improvements**  
✅ Add **Blynk Integration** for mobile control  
✅ Implement **Dimming Feature** for brightness control  
✅ Add **Cloud Dashboard** for real-time monitoring  

---

## **📢 Credits**  
**Developed by:** *Yodha Ardiansyah*  
🌍 **Website:** [https://arunovasi.my.id](https://arunovasi.my.id)  
🔗 **GitHub:** *Coming soon!*  

🚀 *Enjoy your Smart Lamp with ESP32 & MQTT!* 🎉
