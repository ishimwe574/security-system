#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define LDR_PIN A0
#define BUZZER_PIN 6
#define RELAY_PIN 7

Servo doorLock;

int distanceThreshold = 30;
int lightThreshold = 500;

bool alarmOn = false;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  doorLock.attach(5);
  doorLock.write(0);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);

  delay(2000);
  sendSMS("Security System Started");
}

void loop() {
  int distance = getDistance();
  int light = analogRead(LDR_PIN);

  Serial.print("D: ");
  Serial.print(distance);
  Serial.print(" | L: ");
  Serial.println(light);

  if (distance > 0 && distance < distanceThreshold) {
    triggerAlarm(light);
  } else {
    resetSystem();
  }

  delay(500);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void triggerAlarm(int light) {
  if (!alarmOn) {
    alarmOn = true;

    doorLock.write(90);
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, HIGH);

    if (light < lightThreshold) {
      sendSMS("ALERT! Intruder detected in DARK area!");
    } else {
      sendSMS("ALERT! Intruder detected!");
    }

    Serial.println("ALARM ON");
  }
}

void resetSystem() {
  if (alarmOn) {
    alarmOn = false;

    doorLock.write(0);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);

    Serial.println("System Normal");
  }
}

// GSM FUNCTION
void sendSMS(String msg) {
  Serial.println("AT+CMGF=1");
  delay(1000);

  Serial.println("AT+CMGS=\"+2507XXXXXXXX\"");
  delay(1000);

  Serial.print(msg);
  delay(500);

  Serial.write(26);
  delay(3000);
}
  

