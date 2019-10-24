#include <Wire.h>
#include <Adafruit_MotorShield.h>


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
//m1 - 1, m2 - 2, m3 - 3, m4 - 4
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(3);
int Led = 13 ;
int leftIR = 10;
int rightIR = 8;
int left;
int right;



void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  pinMode (Led, OUTPUT) ;
  pinMode (leftIR, INPUT) ;
  pinMode (rightIR, INPUT) ;
  AFMS.begin();

  LeftMotor->setSpeed(150);
  LeftMotor->run(FORWARD);
  LeftMotor->run(RELEASE);
  RightMotor->setSpeed(150);
  RightMotor->run(FORWARD);
  RightMotor->run(RELEASE);

}

void loop() {
  uint8_t i;
  left = digitalRead (leftIR) ;
  right = digitalRead (rightIR);// digital interface will be assigned a value of 3 to read val



  if ((left == LOW && right == LOW)||(left == HIGH && right == HIGH))
  {
    LeftMotor->run(FORWARD);
    LeftMotor->setSpeed(150);
    RightMotor->run(BACKWARD); //power and ground are opposite thats why it is the opposite direction
    RightMotor->setSpeed(150);
  }
  else if (left == HIGH && right == LOW)
  {
    LeftMotor->run(BACKWARD);
    LeftMotor->setSpeed(150);
    RightMotor->run(BACKWARD);
    RightMotor->setSpeed(150);
  }
  else if (left == LOW && right == HIGH)
  {
    LeftMotor->run(FORWARD);
    LeftMotor->setSpeed(150);
    RightMotor->run(FORWARD);
    RightMotor->setSpeed(150);
  }


}
