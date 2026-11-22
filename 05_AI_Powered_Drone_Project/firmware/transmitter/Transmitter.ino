#include <SPI.h>                      // SPI library for nRF24L01 communication
#include <nRF24L01.h>                 // nRF24L01 hardware definitions
#include <RF24.h>                     // RF24 radio communication library
#include <Wire.h>                     // I2C library for OLED screen
#include <Adafruit_GFX.h>             // Graphics library for OLED
#include <Adafruit_SSD1306.h>         // SSD1306 OLED driver
// ==== OLED Display Setup ====
#define SCREEN_WIDTH 128              // Screen width in pixels
#define SCREEN_HEIGHT 64              // Screen height in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// ==== nRF24L01 Pins for ESP32 ====
#define CE_PIN   4                    // Adjust according to wiring
#define CSN_PIN  5                    // Adjust according to wiring
RF24 radio(CE_PIN, CSN_PIN);
// ==== Radio Communication Address (Pipe) ====
const byte address[] = "NODE1";       // Radio channel address
// ==== Joystick Axis Pin Mapping ====
#define JOY1_Y_PIN 15                 // Throttle (Vertical axis)
#define JOY1_X_PIN 2                  // Yaw      (Horizontal axis)
#define JOY2_Y_PIN 39                 // Pitch    (Vertical axis)
#define JOY2_X_PIN 36                 // Roll     (Horizontal axis)
// ==== Switch Pin Mapping ====
#define SIGNAL_PIN 32                 // Altitude Hold switch
#define MODE_PIN   33                 // Flight Mode switch
// ==== ADC Constants ====
const int MID_RAW      = 4095 / 2;    // ADC mid-scale value (~2047)
const int DEADZONE_RAW = 20;          // Range near center to treat as stable (mapped to 1500)
// ==== Offset Variables for Joystick Calibration ====
int offsetThr = 0;
int offsetYaw = 0;
int offsetPit = 0;
int offsetRol = 0;
// ==== Data Packet Structure for Transmission ====
struct Packet {
  uint16_t throttle, yaw, pitch, roll;  // PWM values (1000–2000 or 1500 center)
  bool signal, mode;                    // Switch states
};
Packet packet;

void setup() {
  // Configure ADC attenuation for full voltage range on all joystick pins
  analogSetPinAttenuation(JOY1_Y_PIN, ADC_11db);
  analogSetPinAttenuation(JOY1_X_PIN, ADC_11db);
  analogSetPinAttenuation(JOY2_Y_PIN, ADC_11db);
  analogSetPinAttenuation(JOY2_X_PIN, ADC_11db);

  // === Axis Calibration ===
  // Capture 50 readings at joystick center position and compute the average
  // Subtract MID_RAW to get offset for centering
  long sum;

  // Throttle Offset
  sum = 0;
  for (int i = 0; i < 50; i++) {
    sum += analogRead(JOY1_Y_PIN);
    delay(5);
  }
  offsetThr = (sum / 50) - MID_RAW;
  // Yaw Offset
  sum = 0;
  for (int i = 0; i < 50; i++) {
    sum += analogRead(JOY1_X_PIN);
    delay(5);
  }
  offsetYaw = (sum / 50) - MID_RAW;
  // Pitch Offset
  sum = 0;
  for (int i = 0; i < 50; i++) {
    sum += analogRead(JOY2_Y_PIN);
    delay(5);
  }
  offsetPit = (sum / 50) - MID_RAW;
  // Roll Offset
  sum = 0;
  for (int i = 0; i < 50; i++) {
    sum += analogRead(JOY2_X_PIN);
    delay(5);
  }
  offsetRol = (sum / 50) - MID_RAW;
  // === OLED Initialization ===
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed"));
    while (1);
  }
  display.clearDisplay();
  display.display();
  // === Radio Configuration ===
  radio.begin();
  radio.setChannel(76);                  // Use same channel as receiver
  radio.setPALevel(RF24_PA_MAX);         // Set to maximum transmission power
  radio.setDataRate(RF24_1MBPS);         // Set data rate
  radio.openWritingPipe(address);        // Set write pipe address
  radio.stopListening();                 // Enable transmitter mode
  // === Configure Switch Pins with Internal Pullups ===
  pinMode(SIGNAL_PIN, INPUT_PULLUP);
  pinMode(MODE_PIN, INPUT_PULLUP);
}
void loop() {
  // ==== Throttle Axis Processing ====
  int raw0_Thr = analogRead(JOY1_Y_PIN);
  int corrThr = raw0_Thr - offsetThr;
  if (abs(corrThr - MID_RAW) <= DEADZONE_RAW) {
    packet.throttle = 1500;
  } else {
    int invThr = 4095 - raw0_Thr;
    packet.throttle = map(invThr, 0, 4095, 1000, 2000);
  }
  // ==== Yaw Axis Processing ====
  int raw0_Yaw = analogRead(JOY1_X_PIN);
  int corrYaw = raw0_Yaw - offsetYaw;
  if (abs(corrYaw - MID_RAW) <= DEADZONE_RAW) {
    packet.yaw = 1500;
  } else {
    int invYaw = 4095 - raw0_Yaw;
    packet.yaw = map(invYaw, 0, 4095, 1000, 2000);
  }
  // ==== Pitch Axis Processing ====
  int raw0_Pit = analogRead(JOY2_Y_PIN);
  int corrPit = raw0_Pit - offsetPit;
  if (abs(corrPit - MID_RAW) <= DEADZONE_RAW) {
    packet.pitch = 1500;
  } else {
    int invPit = 4095 - raw0_Pit;
    packet.pitch = map(invPit, 0, 4095, 1000, 2000);
  }
  // ==== Roll Axis Processing ====
  int raw0_Rol = analogRead(JOY2_X_PIN);
  int corrRol = raw0_Rol - offsetRol;
  if (abs(corrRol - MID_RAW) <= DEADZONE_RAW) {
    packet.roll = 1500;
  } else {
    int invRol = 4095 - raw0_Rol;
    packet.roll = map(invRol, 0, 4095, 1000, 2000);
  }
  // ==== Read Switch States (LOW = active due to INPUT_PULLUP) ====
  packet.signal = (digitalRead(SIGNAL_PIN) == LOW);
  packet.mode   = (digitalRead(MODE_PIN) == LOW);
  // ==== Send Packet over Radio ====
  radio.write(&packet, sizeof(packet));
  // ==== Update OLED Display ====
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Thr:");    display.println(packet.throttle);
  display.print("Yaw:");    display.println(packet.yaw);
  display.print("Pitch:");  display.println(packet.pitch);
  display.print("Roll :");  display.println(packet.roll);
  display.print("Signal :");display.println(packet.signal ? "On" : "Off");
  display.print("Mode :");  display.println(packet.mode ? "Hold" : "Stabilize");
  display.display();
}
