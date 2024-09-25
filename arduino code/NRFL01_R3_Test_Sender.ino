#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DHT.h>

#define CE_PIN 9
#define CSN_PIN 10
#define DHTPIN 7
#define DHTTYPE DHT22

#define LIGHT_SENSOR_PIN A0
#define SOIL_MOISTURE_SENSOR_PIN A1

RF24 radio(CE_PIN, CSN_PIN);
DHT dht(DHTPIN, DHTTYPE);
const byte address[6] = "00001";

struct SensorData {
  float temperature;
  float humidity;
  uint16_t light;           // Use uint16_t for light and soil moisture to ensure correct data size
  uint16_t soil_moisture;   // Use uint16_t for light and soil moisture to ensure correct data size
  uint8_t padding[2];       // Add padding to align the structure
};

void setup() {
  Serial.begin(9600);
  dht.begin();

  if (!radio.begin()) {
    Serial.println("nRF24L01 initialization failed!");
    while (1); // Initialization failed, halt
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  radio.stopListening();

  Serial.println("Transmitter started");
}

void loop() {
  SensorData data;
  data.temperature = dht.readTemperature();
  data.humidity = dht.readHumidity();
  
  int lightLevel = analogRead(LIGHT_SENSOR_PIN);
  int soilMoistureLevel = analogRead(SOIL_MOISTURE_SENSOR_PIN);

  // 센서 데이터 변환 (예: 0-1023 범위를 0-100% 범위로 변환)
  data.light = map(lightLevel, 0, 1023, 100, 0);
  data.soil_moisture = map(soilMoistureLevel, 0, 1023, 0, 100);

  // Adding padding to avoid structure alignment issues
  data.padding[0] = 0;
  data.padding[1] = 0;

  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (radio.write(&data, sizeof(data))) {
    Serial.print("Sent: Temp = ");
    Serial.print(data.temperature);
    Serial.print(", Humi = ");
    Serial.print(data.humidity);
    Serial.print(", Light = ");
    Serial.print(data.light);
    Serial.print(", Soil Moisture = ");
    Serial.println(data.soil_moisture);
  } else {
    Serial.println("Send failed");
  }
  delay(2000); // Adjust the delay as needed
}
