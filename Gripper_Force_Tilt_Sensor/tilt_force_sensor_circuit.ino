#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);

int SENSOR_1;
int SENSOR_2;
int FORCE_SENSOR;
int MOTOR;
int STATUS_1;
int STATUS_2;
int FORCE_SENSOR_VALUE;
int RED_LED;
int GREEN_LED;
int BLUE_LED;
int BUTTON;
int BUTTON_STATE;
const int FORCE_THRESHOLD = 4;  // threshold value for the force sensor

void setup()
{
  SENSOR_1 = 4;
  SENSOR_2 = 5;
  FORCE_SENSOR = A0;
  MOTOR = 6;
  RED_LED = 11;
  GREEN_LED = 10;
  BLUE_LED = 9;
  BUTTON = 7;
  STATUS_1 = 0;
  STATUS_2 = 0;
  FORCE_SENSOR_VALUE = 0;
  BUTTON_STATE = 3;

  Serial.begin(9600);

  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(FORCE_SENSOR, INPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  delay(1000);

  lcd_1.begin(16, 2);
  lcd_1.print("System Started");
  delay(500);
  lcd_1.clear(); // Clear the initial message after the delay
}

void loop()
{
  STATUS_1 = digitalRead(SENSOR_1);
  STATUS_2 = digitalRead(SENSOR_2);
  FORCE_SENSOR_VALUE = analogRead(FORCE_SENSOR);
  BUTTON_STATE = digitalRead(BUTTON);
  
  if (FORCE_SENSOR_VALUE > FORCE_THRESHOLD) {
    // Stop the motor if the force sensor value exceeds the threshold
    digitalWrite(MOTOR, LOW);  // Use digitalWrite for a digital pin
    // Turn the LED red
    analogWrite(RED_LED, 255);
    analogWrite(GREEN_LED, 0);
    analogWrite(BLUE_LED, 0);
    // Display "Force Exceeded" on the LCD
    lcd_1.clear();
    lcd_1.print("Force Exceeded");
  } else if ((STATUS_1 == HIGH) || (STATUS_2 == HIGH)) {
    // Stop the motor if any tilt is detected
    digitalWrite(MOTOR, LOW);  // Use digitalWrite for a digital pin
    // Turn the LED red
    analogWrite(RED_LED, 255);
    analogWrite(GREEN_LED, 0);
    analogWrite(BLUE_LED, 0);
    // Display "Gripper Tilted" on the LCD
    lcd_1.clear();
    lcd_1.print("Gripper Tilted");
  } else {
    // Turn the motor on if no tilt is detected and force sensor value is not exceeded
    digitalWrite(MOTOR, HIGH);  // Use digitalWrite for a digital pin
    // Turn RGB LED to a different color
    analogWrite(RED_LED, 0);
    analogWrite(GREEN_LED, 255);
    analogWrite(BLUE_LED, 255);
    // Clear the LCD display
  }
}
