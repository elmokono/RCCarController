#include <SoftwareSerial.h>  //Software Serial Port
#define RxD 1
#define TxD 2
#define MAX_BUF (64)//regular com

SoftwareSerial Serial(RxD, TxD);

int led = 4;
char buffer[MAX_BUF];  // where we store the message until we get a ';'
long sofar;  // how much is in the buffer
bool newData;

void setup()
{
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop()
{
  recvWithEndMarker();

  if (newData == true) {

    String str((char*)buffer);

    //process
    if (buffer[0] == 'W') digitalWrite(led, HIGH);
    if (buffer[0] == 'w') digitalWrite(led, LOW);
    
    sofar = 0; // clear input buffer
    Serial.print(str);
    Serial.println("ok");
    newData = false;
  }
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  sofar = 0;
  // if (Serial.available() > 0) {
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    //if (rc != endMarker) {
    if (rc != endMarker) {
      buffer[ndx] = rc;
      ndx++;
      if (ndx >= MAX_BUF) {
        ndx = MAX_BUF - 1;
      }
    }
    else {
      buffer[ndx] = '\0'; // terminate the string
      sofar = ndx;
      ndx = 0;
      newData = true;
    }
  }
}

/*void setupBlueToothConnection()
  {
  Serial.begin(9600);
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
    blueToothSerial.print("\r\n+STNA=HC-06\r\n"); //set the bluetooth name as "HC-05"
    blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
    blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here

    delay(2000); // This delay is required.
    blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable
    blueToothSerial.print("bluetooth connected!\n");

    delay(2000); // This delay is required.
    blueToothSerial.flush();
  }*/
