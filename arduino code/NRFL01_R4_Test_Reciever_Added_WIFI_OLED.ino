#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <WiFiS3.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Replace with your network credentials
const char* ssid = "aterm-899480-g";
const char* password = "9a2dd9f5689d0";

// Replace with your server IP and PHP file
const char* serverIP = "35.213.49.212"; // IP 주소
const int serverPort = 80; // 기본 HTTP 포트

// OLED display width and height, in pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Reset pin (or -1 if sharing Arduino reset pin)
#define OLED_RESET -1

// Create an SSD1306 display object connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

struct SensorData {
  float temperature;
  float humidity;
  uint16_t light;
  uint16_t soil_moisture;
  uint8_t padding[2]; // Add padding to align the structure
};

WiFiClient client;
unsigned long lastSendTime = 0; // 타이머를 위한 변수
const unsigned long sendInterval = 600000; // 10분 (600,000 밀리초)

void setup() {
  Serial.begin(9600);

  if (!radio.begin()) {
    Serial.println("nRF24L01 initialization failed!");
    while (1); // Initialization failed, halt
  }

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  radio.startListening();

  Serial.println("Receiver started");

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (radio.available()) {
    SensorData data;
    radio.read(&data, sizeof(data));
    Serial.print("Received: Temp = ");
    Serial.print(data.temperature);
    Serial.print(", Humi = ");
    Serial.print(data.humidity);
    Serial.print(", Light = ");
    Serial.print(data.light);
    Serial.print(", Soil Moisture = ");
    Serial.println(data.soil_moisture);

    // Display on OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Sensor Data");
    display.setCursor(0, 10);
    display.print("Temp: ");
    display.print(data.temperature);
    display.println(" C");
    display.setCursor(0, 20);
    display.print("Humi: ");
    display.print(data.humidity);
    display.println(" %");
    display.setCursor(0, 30);
    display.print("Light: ");
    display.print(data.light);
    display.println(" %");
    display.setCursor(0, 40);
    display.print("Soil Moist: ");
    display.print(data.soil_moisture);
    display.println(" %");
    display.display();

    // 현재 시간 가져오기
    unsigned long currentMillis = millis();

    // 10분마다 데이터 전송
    if (currentMillis - lastSendTime >= sendInterval) {
      // Send data to server
      if (WiFi.status() == WL_CONNECTED) {
        if (client.connect(serverIP, serverPort)) {
          String httpRequestData = "temperature=" + String(data.temperature)
                                 + "&humidity=" + String(data.humidity)
                                 + "&light=" + String(data.light)
                                 + "&soil_moisture=" + String(data.soil_moisture);
          
          client.println("POST /SmartFarm_test/server/process_R4.php HTTP/1.1");
          client.print("Host: "); client.println(serverIP);
          client.println("Content-Type: application/x-www-form-urlencoded");
          client.print("Content-Length: "); client.println(httpRequestData.length());
          client.println();
          client.println(httpRequestData);
          
          while (client.connected() || client.available()) {
            if (client.available()) {
              String line = client.readStringUntil('\n');
              Serial.println(line);
            }
          }
          
          client.stop();
          lastSendTime = currentMillis; // 마지막 전송 시간을 갱신
        } else {
          Serial.println("Connection to server failed");
        }
      } else {
        Serial.println("WiFi Disconnected");
      }
    }
  } else {
    Serial.println("No data available");
  }
  delay(1000); // Adjust the delay as needed for receiving data and updating the display
}
