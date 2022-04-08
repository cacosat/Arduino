#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <TimeLib.h>
#include <virtuabotixRTC.h>

//Objects:
LiquidCrystal_I2C lcd(0x27, 16, 2); //I2C pins --> SDA - AX; SCL - AX
virtuabotixRTC clockModule(5, 6, 7); //CLK, DAT, RST

//Variables:
int counter = 0;
int timerCounter;
String mode = "TIMEROFF";
int timerMin;
int timerSec;
int minRestantes;
int secRestantes;

/*
   Buttons:
*/
int startButtonPin = 8;
int startButton;
int resetButtonPin = 12;
int resetButton;
int leftButtonPin = 3;
int leftButton;
int rightButtonPin = 11;
int rightButton;
int backlightButtonPin = 10;
int backlightButton;

/*
   Buzzer:
*/
int buzzerPin = 9;

/*
   LCD
*/
int backlightStatus;
int backlightStatusOld = 1;
int backlightStatusNew;

/****************************************************/

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  /*
     Buttons
  */
  pinMode(startButtonPin, INPUT);
  pinMode(resetButtonPin, INPUT);
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  /*
     Clock Module setup: clockObject.setDS1302Time(sec, min, hr, day week, day month, month, year);
  */
  //clockModule.setDS1302Time(0, 14, 22, 3, 20, 10, 2021); //Comentar despues de la primera

  /*
     LCD
  */
  lcd.init();
}

/****************************************************/

void loop() {
  // put your main code here, to run repeatedly:
  clockModule.updateTime();
  
  /*
     Buttons:
  */
  startButton = digitalRead(startButtonPin);
  resetButton = digitalRead(resetButtonPin);
  leftButton = digitalRead(leftButtonPin);
  rightButton = digitalRead(rightButtonPin);
  backlightButton = digitalRead(backlightButtonPin);

  /*
     Backlight toggle:
  */
  backlightStatusNew = backlightButton;
  if (backlightStatusOld == 0 and backlightStatusNew == 1) {
    if (backlightStatus == 0) {
      lcd.setBacklight(HIGH);
      backlightStatus = 1;
    }
    else {
      lcd.setBacklight(LOW);
      backlightStatus = 0;
    }
  }
  backlightStatusOld = backlightStatusNew;

  /*
     LCD prints:
  */
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(clockModule.hours);
  lcd.print(":");
  lcd.print(clockModule.minutes);
  lcd.print(" | ");
  lcd.print(clockModule.dayofmonth);
  lcd.print("/");
  lcd.print(clockModule.month);
  lcd.print("  ");
  lcd.setCursor(0, 1);
  lcd.print("Timer ");

  if (startButton == 1 and timerCounter == 0) {
    lcd.setCursor(6, 1);
    lcd.print("          ");
    timerCounter = 0;
    mode = "TIMERON";
  }

  if (mode == "TIMERON") {
    lcd.setCursor(6, 1);
    lcd.print("set to ");
    lcd.print(timerCounter);
    lcd.print("     ");
    if (rightButton == 1) {
      timerCounter++;
      delay(75);
    }
    if (leftButton == 1) {
      timerCounter--;
      delay(75);
    }
    if (timerCounter <= 0) {
      timerCounter = 0;
    }
  }

  if (resetButton == 1) {
    mode = "TIMEROFF";
    timerCounter = 0;
  }
  if (mode == "TIMEROFF") {
    lcd.setCursor(6, 1);
    lcd.print("OFF       ");
  }

  //start of timer:
  if (startButton == 1 and timerCounter != 0) {
    mode = "TIMER_RUNNING";
    lcd.setCursor(6, 1);
    lcd.print("          ");
    setTime(0);
  }
  if (mode == "TIMER_RUNNING") {
    time_t t = now();
    timerMin = minute(t);
    timerSec = second(t);
    minRestantes = timerCounter - 1 - timerMin;
    secRestantes = 59 - timerSec;
    
    lcd.setCursor(6, 1);
    lcd.print("(");
    lcd.print(timerCounter);
    lcd.print(") ");
    lcd.print(minRestantes);
    lcd.print(":");
    lcd.print(secRestantes);
    lcd.print("    ");

    //Buzzer
    if (timerCounter == timerMin) {
        analogWrite(buzzerPin, 125);
        delay(250);
        analogWrite(buzzerPin, 0);
        delay(100);  
        analogWrite(buzzerPin, 125);
        delay(250);
        analogWrite(buzzerPin, 0);
        delay(100);
        analogWrite(buzzerPin, 150);
        delay(250);
        analogWrite(buzzerPin, 0);
        delay(100); 
    }
  }
}
