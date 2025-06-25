#include <SoftwareSerial.h>

#define irSensorPin 2         // IR sensor input pin
#define buzzerPin  8          // Buzzer pin
#define ledPin     9          // LED for alert indication

SoftwareSerial gsm(10, 11);   // RX, TX pins for GSM module

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
  gsm.begin(9600);
  
  delay(1000);
  Serial.println("Emergency Alert System Initialized.");
  gsm.println("AT"); // Check GSM connection
  delay(1000);
  gsm.println("AT+CMGF=1"); // Set SMS text mode
  delay(1000);
}

void loop() {
  int sensorValue = digitalRead(irSensorPin);

  if (sensorValue == LOW) {
    Serial.println("Emergency Detected!");
    
    // Turn on buzzer and LED
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    
    // Send SMS alert
    sendSMS("Emergency detected! Please respond immediately!");
    
    delay(10000); // Wait 10 seconds before next alert
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }
  
  delay(500); // Small delay to reduce loop speed
}

void sendSMS(String message) {
  gsm.println("AT+CMGF=1");    // Set to text mode
  delay(1000);
  gsm.println("AT+CMGS=\"+91XXXXXXXXXX\""); // Replace with recipient phone number
  delay(1000);
  gsm.print(message);
  delay(500);
  gsm.write(26); // Ctrl+Z to send SMS
  delay(3000);
  Serial.println("SMS Sent.");
}
