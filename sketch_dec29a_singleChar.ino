#include <SoftwareServo.h>
#include <SoftwareSerial.h>

//at tiny pins ///////////////////////////////
#define servopin 0
#define RxD 2
#define TxD 1
#define tip120 3
#define led 4
//////////////////////////////////////////////

SoftwareSerial Serial(RxD, TxD);
SoftwareServo servo;

unsigned long servoRefresh;

void setup()
{
  Serial.begin(9600);
  servo.attach(servopin);
  pinMode(led, OUTPUT);
  pinMode(tip120, OUTPUT);
  pinMode(servopin, OUTPUT);

  digitalWrite(led, HIGH);  
}

void refreshServo()
{
  //servo refresh every 50ms
  if (millis() - servoRefresh > 50) {
    servoRefresh = millis();
    SoftwareServo::refresh();
  }
}

void loop()
{
  char rc;

  while (Serial.available() > 0) {
    rc = Serial.read();
    if (rc == 'W') digitalWrite(led, HIGH); //lights on
    if (rc == 'w') digitalWrite(led, LOW); //lights off
    if (rc == 'F' || rc == 'G' || rc == 'I') //forward
    {
      digitalWrite(tip120, HIGH); //gas
    }
    if (rc == 'F' ) //forward
    {
      servo.write(90);
    }
    if (rc == 'S') //stop
    {
      digitalWrite(tip120, LOW); //stop
    }
    if (rc == 'L' || rc == 'G') //left
    {
      servo.write(140);
    }
    if (rc == 'R' || rc == 'I') //right
    {
      servo.write(40);
    }
  }

  refreshServo();

}

