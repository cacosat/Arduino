#include <Keypad.h>

//num of rows and columns:
const byte ROWS = 4;
const byte COLS = 4;
//array of the different symbol for each key:
char keySymbols[COLS][ROWS] = {
  {'4', '3', '2', '1'},
  {'8', '7', '6', '5'},
  {'B', 'A', '0', '9'},
  {'F', 'E', 'D', 'C'}
};
//Pinout on the arduino for rows and columns:
byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {11, 10, 9, 8};

//var to contain pressed key(s);
char keyPress;

//init instance of Keypad class:
Keypad keypadMatrix = Keypad(makeKeymap(keySymbols), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  keyPress = keypadMatrix.getKey();
  if (keyPress) {
    Serial.println(keyPress);
  }
}
