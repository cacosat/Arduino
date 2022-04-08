#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 rx(7, 8); //recieverObject(cs, cns);
const byte address[6] = "00001";

int speedPin1 = 3; //motor 1
int dir1 = 2;
int dir2 = 4;
int speedPin2 = 10; //motor 2
int dir3 = 5;
int dir4 = 6;
int motorSpeed = 0; //range from 0-255;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rx.begin();
  rx.openReadingPipe(0, address);
  rx.setPALevel(RF24_PA_MIN);
  rx.startListening();

  pinMode(speedPin1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(speedPin2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int payload[3]; //payload[0] = X; payload[1]= Y; payload[2] = 42 (test);
  if (rx.available()) {
    rx.read(&payload, sizeof(payload));
    Serial.print("Joystick X: ");
    Serial.print(payload[0]);
    Serial.print("; Joystick Y: ");
    Serial.print(payload[1]);
    Serial.print("; Test payload: ");
    Serial.println(payload[2]);
  }

  //convert payload to directions: 
  //Y axis
  if (payload[1] < 650) {
    motorSpeed = map(payload[1], 650, 0, 0, 255);
    motorSpeed = constrain(motorSpeed, 0, 255);
    digitalWrite(dir1, HIGH); //Rueda 1
    digitalWrite(dir2, LOW);
    digitalWrite(dir3, HIGH); //Rueda 2
    digitalWrite(dir4, LOW);
    analogWrite(speedPin1, motorSpeed);
    analogWrite(speedPin2, motorSpeed);
    Serial.println(motorSpeed); 
  }
   if (payload[1] > 650) {
    motorSpeed = map(payload[1], 650, 1023, 0, 255);
    motorSpeed = constrain(motorSpeed, 0, 255);
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, HIGH);
    digitalWrite(dir3, LOW);
    digitalWrite(dir4, HIGH);
    analogWrite(speedPin1, motorSpeed);
    analogWrite(speedPin2, motorSpeed);
    Serial.println(motorSpeed);
  }
  
  //X Axis: Arreglar
//  else if (payload[1] < 910 && payload[1] < 650) {
//    motorSpeed = map(payload[1], 650, 0, 0, 255);
//    motorSpeed = constrain(motorSpeed, 0, 255);
//    digitalWrite(dir1, HIGH);
//    digitalWrite(dir2, LOW);
//    digitalWrite(dir3, HIGH);
//    digitalWrite(dir4, LOW);
//    analogWrite(speedPin1, motorSpeed);
//    analogWrite(speedPin2, 0);
//  }
}
