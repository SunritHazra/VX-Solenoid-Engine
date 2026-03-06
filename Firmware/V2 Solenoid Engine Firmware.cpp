/*
 * V2 Solenoid Engine ESP32 Firmware
 * 
 * Author: Sunrit Hazra (@SunritHazra)
 * Date: March 2026
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <BluetoothSerial.h>

// Pin definitions (match your PCB)
#define PWM_PIN1 25      // Coil 1 PWM (GPIO25)
#define PWM_PIN2 26      // Coil 2 PWM (GPIO26)
#define SENSOR_PIN1 34   // TCRT5000 Sensor 1 (interrupt)
#define SENSOR_PIN2 35   // TCRT5000 Sensor 2 (interrupt)
#define TEMP_PIN 36      // NTC thermistor (ADC1_CH0)
#define BUTTON_PIN 0     // External power button (pull-up)

#define PWM_FREQ_MIN 1000  // Hz
#define PWM_FREQ_MAX 5000  // Hz
#define PWM_DUTY_MAX 40    // % (safety limit for no overheating)
#define TEMP_CUTOFF 80     // °C (thermal cutoff)

AsyncWebServer server(80);  // WiFi web server on port 80
BluetoothSerial SerialBT;   // Bluetooth Serial for debug

// Global variables
volatile bool trigger1 = false;  // Sensor 1 interrupt flag
volatile bool trigger2 = false;  // Sensor 2 interrupt flag
float dutyCycle = 20.0;          // Initial duty %
int pwmFreq = 2000;              // Initial frequency Hz
int advanceAngle = 15;           // Firing advance degrees (0-30)
bool engineOn = false;           // Master enable
float currentTemp = 0.0;         // Temperature °C

// PWM channels
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int pwmResolution = 8;     // 8-bit (0-255)

// WiFi AP credentials
const char* ssid = "Solenoid_AP";
const char* password = "engine123";

// Temperature calibration (NTC 10kΩ + 10kΩ divider, beta=3950, R25=10k)
float readTemperature() {
  int adcValue = analogRead(TEMP_PIN);
  float voltage = (adcValue / 4095.0) * 3.3;  // ESP32 ADC 12-bit, 3.3V ref
  float resistance = 10000.0 * (3.3 / voltage - 1.0);  // Divider formula
  float tempK = 1.0 / (1.0 / 298.15 + log(resistance / 10000.0) / 3950.0);  // Beta equation
  return tempK - 273.15;  // Celsius
}

// Interrupt service routines (ISR)
void IRAM_ATTR sensorISR1() {
  trigger1 = true;
}

void IRAM_ATTR sensorISR2() {
  trigger2 = true;
}

// PWM setup
void setupPWM() {
  ledcSetup(pwmChannel1, pwmFreq, pwmResolution);
  ledcSetup(pwmChannel2, pwmFreq, pwmResolution);
  ledcAttachPin(PWM_PIN1, pwmChannel1);
  ledcAttachPin(PWM_PIN2, pwmChannel2);
}

// Apply duty cycle to both channels (phased)
void updatePWM() {
  int dutyValue = (dutyCycle / 100.0) * 255;
  if (dutyValue > (PWM_DUTY_MAX / 100.0 * 255)) dutyValue = (PWM_DUTY_MAX / 100.0 * 255);  // Safety limit
  
  if (engineOn) {
    ledcWrite(pwmChannel1, dutyValue);  // Coil 1 on
    ledcWrite(pwmChannel2, 0);          // Coil 2 off (180° phase via sensors)
    delay(advanceAngle * 10);           // Simple advance delay (refine with encoder later)
    ledcWrite(pwmChannel1, 0);
    ledcWrite(pwmChannel2, dutyValue);  // Coil 2 on
  } else {
    ledcWrite(pwmChannel1, 0);
    ledcWrite(pwmChannel2, 0);
  }
}

// Web server handlers
void handleRoot(AsyncWebServerRequest *request) {
  String html = R"(
<!DOCTYPE html>
<html><head><title>Solenoid Engine Control</title>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<style>body{font-family:Arial;margin:20px;background:#f0f0f0;} .slider{max-width:300px;}</style></head>
<body>
<h1>V2 Solenoid Engine Control</h1>
<p>Temp: )" + String(currentTemp, 1) + R"( °C | Status: )" + String(engineOn ? "ON" : "OFF") + R"(</p>
<label for='duty'>Duty Cycle (%): </label><input type='range' id='duty' min='0' max='40' value=)" + String(dutyCycle) + R"( onchange='sendValue("duty",this.value)'><span id='dutyVal'>)" + String(dutyCycle) + R"(</span><br>
<label for='freq'>Frequency (Hz): </label><input type='range' id='freq' min='1000' max='5000' value=)" + String(pwmFreq) + R"( onchange='sendValue("freq",this.value)'><span id='freqVal'>)" + String(pwmFreq) + R"(</span><br>
<label for='advance'>Advance Angle (°): </label><input type='range' id='advance' min='0' max='30' value=)" + String(advanceAngle) + R"( onchange='sendValue("advance",this.value)'><span id='advanceVal'>)" + String(advanceAngle) + R"(</span><br>
<button onclick='toggleEngine()'>)" + String(engineOn ? "STOP" : "START") + R"(</button>
<script>
function sendValue(param, value) {
  fetch('/set?'+param+'='+value).then(() => location.reload());
  document.getElementById(param+'Val').innerText = value;
}
function toggleEngine() {
  fetch('/toggle').then(() => location.reload());
}
setInterval(() => location.reload(), 2000);  // Refresh every 2s for temp/status
</script>
</body></html>
)";
  request->send(200, "text/html", html);
}

void handleSet(AsyncWebServerRequest *request) {
  if (request->hasParam("duty")) dutyCycle = request->getParam("duty")->value().toFloat();
  if (request->hasParam("freq")) pwmFreq = request->getParam("freq")->value().toInt();
  if (request->hasParam("advance")) advanceAngle = request->getParam("advance")->value().toInt();
  updatePWM();  // Immediate update
  request->send(200, "text/plain", "OK");
}

void handleToggle(AsyncWebServerRequest *request) {
  engineOn = !engineOn;
  updatePWM();
  request->send(200, "text/plain", engineOn ? "ON" : "OFF");
}

// Setup
void setup() {
  Serial.begin(115200);
  SerialBT.begin("Solenoid_BT");  // Bluetooth debug
  Serial.println("V2 Solenoid Engine Firmware Starting...");

  // Pin modes
  pinMode(SENSOR_PIN1, INPUT_PULLUP);
  pinMode(SENSOR_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TEMP_PIN, INPUT);

  // Interrupts for sensors (falling edge for trigger)
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN1), sensorISR1, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN2), sensorISR2, FALLING);

  // PWM setup
  setupPWM();

  // WiFi AP
  WiFi.softAP(ssid, password);
  Serial.print("WiFi AP IP: ");
  Serial.println(WiFi.softAPIP());

  // Web server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/set", HTTP_GET, handleSet);
  server.on("/toggle", HTTP_GET, handleToggle);
  server.begin();

  // POST (power-on self-test)
  currentTemp = readTemperature();
  Serial.print("POST: Temp = ");
  Serial.print(currentTemp);
  Serial.println(" °C");
  updatePWM();  // Off initially
}

// Main loop
void loop() {
  // Read temperature every 500 ms
  static unsigned long lastTemp = 0;
  if (millis() - lastTemp > 500) {
    currentTemp = readTemperature();
    if (currentTemp > TEMP_CUTOFF) {
      engineOn = false;  // Thermal cutoff
      Serial.println("Thermal cutoff! Engine OFF.");
    }
    lastTemp = millis();
  }

  // Sensor triggering (phasing)
  if (trigger1) {
    trigger1 = false;
    // Advance logic: Fire coil 2 with advance
    delay(advanceAngle * 5);  // Simple delay-based advance (refine with timer)
    if (engineOn) ledcWrite(pwmChannel2, (dutyCycle / 100.0) * 255);
    delayMicroseconds(5000 / pwmFreq * 1000 * (dutyCycle / 100.0));  // On time
    ledcWrite(pwmChannel2, 0);
    SerialBT.println("Trigger1: Coil2 fired");
  }

  if (trigger2) {
    trigger2 = false;
    delay(advanceAngle * 5);
    if (engineOn) ledcWrite(pwmChannel1, (dutyCycle / 100.0) * 255);
    delayMicroseconds(5000 / pwmFreq * 1000 * (dutyCycle / 100.0));
    ledcWrite(pwmChannel1, 0);
    SerialBT.println("Trigger2: Coil1 fired");
  }

  // Button for soft power (optional)
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50);  // Debounce
    if (digitalRead(BUTTON_PIN) == LOW) {
      engineOn = !engineOn;
      updatePWM();
      Serial.println(engineOn ? "Engine ON" : "Engine OFF");
    }
  }

  // Debug output
  if (Serial.available()) {
    String cmd = Serial.readString();
    cmd.trim();
    if (cmd == "status") {
      Serial.println("Duty: " + String(dutyCycle) + "%, Freq: " + String(pwmFreq) + "Hz, Temp: " + String(currentTemp) + "°C, On: " + String(engineOn));
    } else if (cmd.startsWith("duty ")) {
      dutyCycle = cmd.substring(5).toFloat();
      updatePWM();
    } // Add more commands...
  }
}