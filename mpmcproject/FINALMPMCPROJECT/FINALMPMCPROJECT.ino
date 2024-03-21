#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial bluetooth(10, 11); // RX, TX for HC-05 module

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  bluetooth.begin(9600); // Initialize HC-05 module
}

void loop() {
  delay(2000);
  float temperature = dht.readTemperature();
  char alertMessage[30]; // Store the alert message

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp.: ");
    lcd.print(temperature);
    lcd.print(" C");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    if (temperature >= 32.0) {
      strcpy(alertMessage, "High Temp! Alert");
      lcd.setCursor(0, 1);
      lcd.print(alertMessage);

      Serial.println(alertMessage);
    } else {
      strcpy(alertMessage, "Temperature OK");
      lcd.setCursor(0, 1);
      lcd.print(alertMessage);

      Serial.println(alertMessage);
    }

    // Send temperature and alert message to HC-05 for Bluetooth communication
    bluetooth.print("Temperature: ");
    bluetooth.print(temperature);
    bluetooth.print(" C");
    bluetooth.print(", ");
    bluetooth.println(alertMessage);
  }
}


