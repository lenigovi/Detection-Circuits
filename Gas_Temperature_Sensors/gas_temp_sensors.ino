// Pin definitions
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);

int seconds = 0;
const int gasSensorPin = A0;
const int tempSensorPin = A1;
const int redLedPin = 13;
const int greenLedPin = 10;
const int buzzerPin = 12;

// Threshold values
const int gasThreshold = 300; // Example threshold for gas sensor
const float tempThresholdStop = 50.0; // Stop if temperature > 50°C
const float tempThresholdResume = 35.0; // Resume if temperature < 35°C
const float tempMaxOperating = 30.0; // Max operating temperature when gas is detected

void setup() {
  pinMode(gasSensorPin, INPUT);
  pinMode(tempSensorPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT); // Added to set buzzer pin as OUTPUT
  lcd_1.begin(16, 2);
  lcd_1.print("System Started");
  delay(500);
  Serial.begin(9600);
}

void loop() {
  int gasSensorValue = analogRead(gasSensorPin);
  int tempSensorValue = analogRead(tempSensorPin);

  float voltage = tempSensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;

  Serial.print("Gas Sensor Value: ");
  Serial.print(gasSensorValue);
  Serial.print(" | Temperature: ");
  Serial.println(temperatureC);

  lcd_1.clear(); // Clear the LCD screen

  if (gasSensorValue >= gasThreshold) {
    // Safety conditions met, stop the robot
    digitalWrite(redLedPin, HIGH); // Turn on Red LED
    digitalWrite(greenLedPin, LOW); // Turn off Green LED
    digitalWrite(buzzerPin, HIGH); // Activate buzzer
    Serial.println("Robot stopped");
    lcd_1.print("Gas Detected"); // Display message on LCD
  }
  else if (temperatureC > tempThresholdStop) {
    // Safety conditions met, stop the robot
    digitalWrite(redLedPin, HIGH); // Turn on Red LED
    digitalWrite(greenLedPin, LOW); // Turn off Green LED
    digitalWrite(buzzerPin, HIGH); // Activate buzzer
    Serial.println("Robot stopped");
    lcd_1.print("Robot Stopped"); // Display message on LCD
  }
  else if (temperatureC < tempThresholdResume && gasSensorValue < gasThreshold && temperatureC < tempMaxOperating) {
    // Safe to resume
    digitalWrite(redLedPin, LOW); // Turn off Red LED
    digitalWrite(greenLedPin, HIGH); // Turn on Green LED
    digitalWrite(buzzerPin, LOW); // Deactivate buzzer
    Serial.println("Safe to resume.");
    lcd_1.print("Safe to resume"); // Display message on LCD
  } else {
    // Keep robot stopped
    digitalWrite(redLedPin, HIGH); // Turn on Red LED
    digitalWrite(greenLedPin, LOW); // Turn off Green LED
    digitalWrite(buzzerPin, HIGH); // Activate buzzer
    Serial.println("Not safe to operate.");
    lcd_1.print("Not safe to operate"); // Display message on LCD
  }

  delay(1000); // Wait for 1 second before next loop
}
