/* 
Group 6
  - Fathur
  - Syahmi
  - Imran
  - Afiqah

References: https://www.youtube.com/watch?v=t7k9D1jDEtk
Link Gdrice: https://drive.google.com/drive/folders/1qB5IcSiQ6l2yzzB9l10zXVxmEKHARAIf
*/



#include <AFMotor.h>

#define LEFT_SENSOR_PIN A0
#define RIGHT_SENSOR_PIN A1

const int ON_BLACK = 300;
const int ON_WHITE = 700;

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

void setMotorSpeeds(int speed1, int speed2, int speed3, int speed4) {
  motor1.setSpeed(speed1);
  motor1.run(speed1 > 0 ? FORWARD : BACKWARD);

  motor2.setSpeed(speed2);
  motor2.run(speed2 > 0 ? FORWARD : BACKWARD);

  motor3.setSpeed(speed3);
  motor3.run(speed3 > 0 ? FORWARD : BACKWARD);

  motor4.setSpeed(speed4);
  motor4.run(speed4 > 0 ? FORWARD : BACKWARD);
}

void setup() {
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Left: ");
  Serial.print(digitalRead(LEFT_SENSOR_PIN));
  Serial.print("\tRight: ");
  Serial.println(digitalRead(RIGHT_SENSOR_PIN));

  // Line detected by both sensors
  if (digitalRead(LEFT_SENSOR_PIN) == LOW && digitalRead(RIGHT_SENSOR_PIN) == LOW) {
    // Forward
    setMotorSpeeds(80, 80, 80, 80);
  }
  // Line detected by left sensor
  else if (digitalRead(LEFT_SENSOR_PIN) == LOW && digitalRead(RIGHT_SENSOR_PIN) == HIGH) {
    // Turn left with proportional control
    int correction = map(analogRead(RIGHT_SENSOR_PIN), ON_BLACK, ON_WHITE, 0, 30);
    setMotorSpeeds(-50, 110 + correction, 110 + correction, -50);
    delay(100);  // Introduce a small delay to stabilize the turn
  }
  // Line detected by right sensor
  else if (digitalRead(LEFT_SENSOR_PIN) == HIGH && digitalRead(RIGHT_SENSOR_PIN) == LOW) {
    // Turn right with proportional control
    int correction = map(analogRead(LEFT_SENSOR_PIN), ON_BLACK, ON_WHITE, 0, 30);
    setMotorSpeeds(110 + correction, -50, -50, 110 + correction);
    delay(100);  // Introduce a small delay to stabilize the turn
  }
  // Line detected by none
  else if (digitalRead(LEFT_SENSOR_PIN) == HIGH && digitalRead(RIGHT_SENSOR_PIN) == HIGH) {
    // Stop
    setMotorSpeeds(0, 0, 0, 0);
  }
}