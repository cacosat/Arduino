//Conexiones 74HC a 7 segment (5461AS-1; is is common cathode):
// - Q1 - A (11)
// - Q2 - B (7)
// - Q3 - C (4)
// - Q4 - D (2)
// - Q5 - E (1)
// - Q6 - F(10)
// - Q7 - G (5)
// - Q0 - Decimal (3)

int clockPin = 5; //shift register pin 11;
int latchPin = 6; //shift register storage pin 12;
int dataPin = 7; //shift register data pin 14;
int C1 = 8; //Dígito 1 de izquierda a derecha
int C2 = 9; //Dígito 2 de izquierda a derecha
int C3 = 10; //Dígito 3 de izquierda a derecha
int C4 = 11; //Dígito 4 de izquierda a derecha

int dTime = 1;

//numbers for display in hex (according to wiring): (binary order is G-F-E-D-C-B-A-DP)
byte num1 = 0b00001100; //12 in decimal; 0x0C in hex
byte num2 = 0b10110110; //182; 0xB6
byte num3 = 0b10011110; //158; 0x9E
byte num4 = 0b11001100; //204; 0xCC
byte num5 = 0b11011010; //218; 0xDA
byte num6 = 0b11111010; //250; 0xFA
byte num7 = 0b00001110; //14; 0x0E
byte num8 = 0b11111110; //254; 0xFE
byte num9 = 0b11001110; //206; 0xCE
byte num0 = 0b01111110; //126; 0x7E
byte numDP = 0b00000001; //1; 0x01

void setup() {
  // put your setup code here, to run once:
  
  //Shift register;
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //Display common pins (digit pins);
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //DIGITO 1
  //Common pins (al ser common cathode el display LOW es el que prende;
  digitalWrite(C1, LOW); //first digit;
  digitalWrite(C2, HIGH); //second digit;
  digitalWrite(C3, HIGH); //third digit;
  digitalWrite(C4, HIGH); //fourth digit;

  digitalWrite(latchPin, HIGH);
  shiftOut(dataPin, clockPin, MSBFIRST, num0);
  digitalWrite(latchPin, LOW);

  delay(dTime);

  //DIGITO 2
  digitalWrite(C1, HIGH); //first digit;
  digitalWrite(C2, LOW); //second digit;
  digitalWrite(C3, HIGH); //third digit;
  digitalWrite(C4, HIGH); //fourth digit;
  
  digitalWrite(latchPin, HIGH);
  shiftOut(dataPin, clockPin, MSBFIRST, num1);
  digitalWrite(latchPin, LOW);

  delay(dTime);
  
  //DIGITO 3
  digitalWrite(C1, HIGH); //first digit;
  digitalWrite(C2, HIGH); //second digit;
  digitalWrite(C3, LOW); //third digit;
  digitalWrite(C4, HIGH); //fourth digit;
  
  digitalWrite(latchPin, HIGH);
  shiftOut(dataPin, clockPin, MSBFIRST, num2);
  digitalWrite(latchPin, LOW);

  delay(dTime);
  
  //DIGITO 4
  digitalWrite(C1, HIGH); //first digit;
  digitalWrite(C2, HIGH); //second digit;
  digitalWrite(C3, HIGH); //third digit;
  digitalWrite(C4, LOW); //fourth digit;
  
  digitalWrite(latchPin, HIGH);
  shiftOut(dataPin, clockPin, MSBFIRST, num3);
  digitalWrite(latchPin, LOW);
 
  delay(dTime);
}
