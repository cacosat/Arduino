#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 tx(7, 8); //transmitterObject(ce, cns)
const byte address[6] = "00001"; //any strign of 5 char designates an address;
int payload[3]; //payload is an array of 2 int values (joyX and joyY) to send;

int joyXPin = A1;
int joyYPin = A0;
int joyX;
int joyY;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tx.begin();
  tx.openWritingPipe(address);
  tx.setPALevel(RF24_PA_MIN); //RF24_PA_MAX for major distances;
  tx.stopListening(); //Sets tx as transmitter;
}

void loop() {
  // put your main code here, to run repeatedly:
  joyX = analogRead(joyXPin); //reading joystick values
  joyY = analogRead(joyYPin);

  payload[0] = joyX; //setting payload array;
  payload[1] = joyY;
  payload[2] = 42; //test payload;
  tx.write(&payload, sizeof(payload)); //Sending payload

  Serial.print("Joystick X: ");
  Serial.print(payload[0]);
  Serial.print("; Joystick Y: ");
  Serial.print(payload[1]);
  Serial.print("; Test payload: ");
  Serial.println(payload[2]);

  delay(25);
}
