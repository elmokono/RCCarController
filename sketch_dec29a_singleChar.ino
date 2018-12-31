#include <SoftwareSerial.h>  //Software Serial Port
#define RxD 1
#define TxD 2

SoftwareSerial Serial(RxD, TxD);

int led = 4;

void setup()
{
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop()
{
  char rc;

  while (Serial.available() > 0) {
    rc = Serial.read();
    if (rc == 'W') digitalWrite(led, HIGH); //lights on
    if (rc == 'w') digitalWrite(led, LOW); //lights off
    if (rc == 'F') //forward
    {
    }
    if (rc == 'S') //stop
    {
    }
    if (rc == 'L') //left
    {
    }
    if (rc == 'R') //right
    {
    }
  }
}

