#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> // Required for I2C communication
#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_SSD1306.h> // Driver for SSD1306 OLED displays

// RFID Pin Configuration
#define SS_PIN 21   // SDA for RFID
#define RST_PIN 22  // RST for RFID

// OLED Display Configuration
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_SDA 4       // SDA pin for OLED
#define OLED_SCL 15      // SCL pin for OLED
#define OLED_RST -1      // Reset pin # (or -1 if sharing Arduino reset pin)

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Create Adafruit OLED display instance
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void setup() {
  Serial.begin(115200);

  // Initialize RFID
  SPI.begin(18, 19, 23, 21); // SCK, MISO, MOSI, SS for RFID
  mfrc522.PCD_Init();
  Serial.println("RFID Reader Initialized.");

  // Initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL); // Start I2C communication with specified pins
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // --- Show initial message on OLED ---
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 28);
  display.println("Scan RFID Card...");
  display.display(); // Actually draw the message

  Serial.println("Place your RFID card near the reader...");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // --- Display UID on Serial Monitor ---
  Serial.print("Card UID: ");
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    uidString += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    uidString += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) {
      uidString += ":";
    }
  }
  Serial.println();
  uidString.toUpperCase();

  // --- Display UID on OLED Screen ---
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(28, 10);
  display.println("UID:");
  display.setTextSize(1);
  display.setCursor(10, 40);
  display.println(uidString);
  display.display(); // Show the UID on the OLED

  delay(2000); // Keep UID on screen for 2 seconds

  // --- Reset OLED to initial message ---
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(15, 28);
  display.println("Scan RFID Card...");
  display.display();

  // Halt PICC to allow new cards to be read
  mfrc522.PICC_HaltA();
}