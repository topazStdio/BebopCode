
// Define MOTORS Pins
#define IN1 23
#define IN2 19

#define IN3 18
#define IN4 5

//create function to move your motors
void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, 80);
  digitalWrite(IN3, 80);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, 80);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, 80);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, 80);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, 80);
}

void left() {
  digitalWrite(IN1, 80);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, 80);
  digitalWrite(IN4, LOW);
}