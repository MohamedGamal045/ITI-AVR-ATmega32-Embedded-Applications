#define BLYNK_PRINT Serial               // Enable Blynk debug prints on the Serial Monitor

#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#define DHTPIN 0      // Pin where the DHT11 sensor is connected
#define DHTTYPE DHT11 // Define the sensor type as DHT11

#include <ESP8266WiFi.h>          // Include WiFi library for ESP8266
#include <BlynkSimpleEsp8266.h>   // Include Blynk library for ESP8266
#include <DHT.h>                  // Include DHT sensor library

// WiFi credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

DHT dht(DHTPIN, DHTTYPE);         // Initialize DHT sensor on defined pin and type
BlynkTimer timer;                 // Create a Blynk timer object

void setup()
{
  Serial.begin(9600);                     // Start serial communication at 9600 bps
  dht.begin();                            // Initialize DHT sensor
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Connect to WiFi and Blynk server using credentials
}

void loop()
{
  Blynk.run();                            // Keep the Blynk connection alive

  float humidity = dht.readHumidity();    // Read humidity from DHT sensor
  float temperature = dht.readTemperature(); // Read temperature in Celsius from DHT sensor

  if (isnan(humidity) || isnan(temperature)) { // Check if reading failed
    Serial.println("Failed to read from DHT sensor!"); // Print error message
    return;                                 // Exit loop if sensor failed
  }

  Serial.println("Temperature: ");         // Print label
  Serial.println(temperature);             // Print temperature value
  Serial.println(" °C, Humidity: ");       // Print label
  Serial.println(humidity);                // Print humidity value
  Serial.println(" %");                    // Print unit

  Blynk.virtualWrite(V0, humidity);        // Send humidity to Blynk app on virtual pin V0
  Blynk.virtualWrite(V1, temperature);     // Send temperature to Blynk app on virtual pin V1

  delay(1000);                             // Wait for 1 second before next reading
}