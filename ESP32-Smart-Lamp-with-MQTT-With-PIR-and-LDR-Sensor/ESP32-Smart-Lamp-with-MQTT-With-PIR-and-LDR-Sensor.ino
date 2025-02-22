/*
 * ESP32 Smart Lamp with MQTT
 * ---------------------------------------
 * This project controls a lamp using ESP32 via MQTT.
 * The system reads LDR (Light Sensor) and PIR (Motion Sensor) data and sends it to an MQTT broker.
 * The lamp can be controlled remotely using MQTT messages.
 *
 * Developed by: Yodha Ardiansyah
 * Website: https://arunovasi.my.id
 */

#include <WiFi.h>
#include <PubSubClient.h>

// WiFi Configuration (Replace with your actual credentials)
const char* ssid = "your_wifi_ssid";       
const char* password = "your_wifi_password";  

// MQTT Configuration (Replace with your actual credentials)
const char* mqtt_server = "your_mqtt_server";
const int mqtt_port = 1883;
const char* mqtt_user = "your_mqtt_username";
const char* mqtt_password = "your_mqtt_password";
const char* topic_sensors = "your_topic/smartlamp/sensors";
const char* topic_control = "your_topic/smartlamp/control";

WiFiClient espClient;
PubSubClient client(espClient);

// Pin Configuration
#define RELAY_PIN 13   // Relay (Lamp Control)
#define PIR_PIN 12     // PIR Motion Sensor
#define LDR_PIN 25     // LDR Light Sensor

// Variables
bool lampState = false;
unsigned long lastSensorSendTime = 0;
const unsigned long sensorSendInterval = 1000; // Send sensor data every 1 second

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  digitalWrite(RELAY_PIN, LOW); // Ensure lamp is off by default

  Serial.begin(115200);
  Serial.println("\nESP32 Smart Lamp - Starting...");

  connectWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32_SmartLamp", mqtt_user, mqtt_password)) {
      Serial.println("Connected!");
      client.subscribe(topic_control);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" - Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println("Received MQTT message: " + message);

  if (String(topic) == topic_control) {
    if (message == "on") {
      digitalWrite(RELAY_PIN, HIGH);
      lampState = true;
    } else if (message == "off") {
      digitalWrite(RELAY_PIN, LOW);
      lampState = false;
    }
    Serial.println("Lamp state changed: " + message);
  }
}

void sendSensorData() {
  int ldrValue = digitalRead(LDR_PIN);
  bool pirState = digitalRead(PIR_PIN);

  String sensorData = "{";
  sensorData += "\"ldr\": " + String(ldrValue) + ", ";
  sensorData += "\"pir\": " + String(pirState);
  sensorData += "}";

  client.publish(topic_sensors, sensorData.c_str());
  Serial.println("Sensor data sent: " + sensorData);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  if (millis() - lastSensorSendTime > sensorSendInterval) {
    sendSensorData();
    lastSensorSendTime = millis();
  }
}
