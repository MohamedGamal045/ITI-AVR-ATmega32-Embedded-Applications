#include <SPI.h>                      // SPI library for communication with nRF24L01
#include <nRF24L01.h>                 // Definitions for the nRF24L01 module
#include <RF24.h>                     // RF24 communication library
#include <Servo.h>                    // Library to control PWM signals for servos
// ==== nRF24L01 pin configuration for Arduino Nano ====
#define CE_PIN   7                   // CE pin for radio module (adjust if needed)
#define CSN_PIN  8                   // CSN pin for radio module (adjust if needed)
RF24 radio(CE_PIN, CSN_PIN);
// ==== Same address as used by the transmitter ====
const byte address[] = "NODE1";
// ==== Structure of the received data packet ====
struct Packet {
  uint16_t throttle, yaw, pitch, roll; // Control channels
  bool signal, mode;                   // Signal active flag and flight mode
};
Packet packet;
// ==== Define servo output channels for APM 2.8 ====
Servo ch1_roll;    // Channel 1 → Roll
Servo ch2_pitch;   // Channel 2 → Pitch
Servo ch3_thr;     // Channel 3 → Throttle
Servo ch4_yaw;     // Channel 4 → Yaw
Servo ch5_mode;    // Channel 5 → Flight Mode (Hold/Stabilize)

void setup() {
  Serial.begin(115200);
  // ==== Initialize the nRF24L01 radio ====
  radio.begin();
  radio.setChannel(76);                  // Must match transmitter's channel
  radio.setPALevel(RF24_PA_MAX);         // Set maximum transmission power
  radio.setDataRate(RF24_1MBPS);         // Set data rate to 1 Mbps
  radio.openReadingPipe(0, address);     // Open the reading pipe using same address
  radio.startListening();                // Set radio to listening mode
  // ==== Attach servo outputs to APM input pins ====
  ch1_roll.attach(3);     // D3 → APM CH1
  ch2_pitch.attach(5);    // D6 → APM CH2
  ch3_thr.attach(6);      // D5 → APM CH3
  ch4_yaw.attach(9);      // D9 → APM CH4
  ch5_mode.attach(10);    // D10 → APM CH5
}

void loop() {
  // ==== If a data packet is received ====
  if (radio.available()) {
    radio.read(&packet, sizeof(packet));

    // Extract values from the packet
    int pwmThr    = packet.throttle;
    int pwmYaw    = packet.yaw;
    int pwmPit    = packet.pitch;
    int pwmRol    = packet.roll;
    int pwmmode   = packet.mode ? 1800 : 1500;       // Mode: 1800 = Hold, 1500 = Stabilize
    int pwmsignal = packet.signal ? 2000 : 1000;     // Signal switch: 2000 = active, 1000 = inactive
    // ==== If signal switch is ON (system armed) ====
    if (packet.signal == true) {
      // Send the PWM signals to APM
      ch1_roll.writeMicroseconds(pwmRol);
      ch2_pitch.writeMicroseconds(pwmPit);
      ch3_thr.writeMicroseconds(pwmThr);
      ch4_yaw.writeMicroseconds(pwmYaw);
      ch5_mode.writeMicroseconds(pwmmode);
    } else {
      // If not ready (disarmed), send safe neutral values
      ch1_roll.writeMicroseconds(1000);
      ch2_pitch.writeMicroseconds(1000);
      ch3_thr.writeMicroseconds(1000);
      ch4_yaw.writeMicroseconds(1000);     
      ch5_mode.writeMicroseconds(1000);
    }
    // ==== Print received values for monitoring ====
    Serial.print("T:"); Serial.print(pwmThr);
    Serial.print(" Y:"); Serial.print(pwmYaw);
    Serial.print(" P:"); Serial.print(pwmPit);
    Serial.print(" R:"); Serial.println(pwmRol);
    Serial.print(" Signal:"); Serial.println(pwmsignal);
    Serial.print(" Mode:"); Serial.println(pwmmode);
  }
}
