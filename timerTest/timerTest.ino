//--------------(c) Electronics project hub -----------//
#include <LiquidCrystal.h>
#include<EEPROM.h>
#include <Wire.h>
const int rs = 11, en =12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int stsp = 13;
const int inc = 7;
const int dec = 8;
const int set = 10;
const int buzz = 9;
int hrs = 0;
int Min = 0;
int sec = 0;
unsigned int check_val = 50;
int add_chk = 0;
int add_hrs = 1;
int add_min = 2;
int add_sec = 3;
bool RUN = true;
bool min_flag = true;
bool hrs_flag = true;
bool sec_flag = true;
void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   ELECTRONIC");
  lcd.setCursor(0, 1);
  lcd.print("COUNTDOWN TIMER");
  pinMode(stsp, INPUT_PULLUP);
  pinMode(inc, INPUT_PULLUP);
  pinMode(dec, INPUT_PULLUP);
  pinMode(set, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
  if (EEPROM.read(add_chk) != check_val)
  {
    EEPROM.write(add_chk, check_val);
    EEPROM.write(add_hrs, 0);
    EEPROM.write(add_min, 1);
    EEPROM.write(add_sec, 0);
  }
  else
  {
    hrs = EEPROM.read(add_hrs);
    Min = EEPROM.read(add_min);
    sec = EEPROM.read(add_sec);
  }
  delay(1500);
  INIT();
}

void loop()
{
  if (digitalRead(stsp) == LOW)
  {
    lcd.clear();
    delay(250);
    RUN = true;
    while (RUN)
    {
      if (digitalRead(stsp) == LOW)
      {
        delay(1000);
        if (digitalRead(stsp) == LOW)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("  TIMER STOPPED");
          lcd.setCursor(0, 1);
          lcd.print("----------------");
          delay(2000);
          RUN = false;
          INIT();
          break;
        }
      }
      sec = sec - 1;
      delay(1000);
      if (sec == -1)
      {
        sec = 59;
        Min = Min - 1;
      }
      if (Min == -1)
      {
        Min = 59;
        hrs = hrs - 1;
      }
      if (hrs == -1) hrs = 0;
      lcd.setCursor(0, 1);
      lcd.print("****************");
      lcd.setCursor(4, 0);
      if (hrs <= 9)
      {
        lcd.print('0');
      }
      lcd.print(hrs);
      lcd.print(':');
      if (Min <= 9)
      {
        lcd.print('0');
      }
      lcd.print(Min);
      lcd.print(':');
      if (sec <= 9)
      {
        lcd.print('0');
      }
      lcd.print(sec);
      if (hrs == 0 && Min == 0 && sec == 0)
      {
        lcd.setCursor(4,0);
        RUN = false;
        for (int i = 0; i < 20; i++)
        {
          digitalWrite(buzz, HIGH);
          delay(100);
          digitalWrite(buzz, LOW);
          delay(100);
        }
        // set higher LCD clock freq to avoid crypital characters error
        Wire.setClock(10000);
        lcd.clear();
        INIT();
      }
    }
  }
  if (digitalRead(set) == LOW)
  {
    delay(500);
    while (sec_flag)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SET SECOND: ");
      lcd.print(sec);
      delay(100);
      if (digitalRead(inc) == LOW)
      {
        sec = sec + 1;
        if (sec >= 60) sec = 0;
        delay(100);
      }
      if (digitalRead(dec) == LOW)
      {
        sec = sec - 1;
        if (sec <= -1) sec = 0;
        delay(100);
      }
      if (digitalRead(set) == LOW)
      {
        sec_flag = false;
        delay(250);
      }
    }
    while (min_flag)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SET MINUTE: ");
      lcd.print(Min);
      delay(100);
      if (digitalRead(inc) == LOW)
      {
        Min = Min + 1;
        if (Min >= 60) Min = 0;
        delay(100);
      }
      if (digitalRead(dec) == LOW)
      {
        Min = Min - 1;
        if (Min <= -1) Min = 0;
        delay(100);
      }
      if (digitalRead(set) == LOW)
      {
        min_flag = false;
        delay(250);
      }
    }
    while (hrs_flag)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SET HOUR: ");
      lcd.print(hrs);
      delay(100);
      if (digitalRead(inc) == LOW)
      {
        hrs = hrs + 1;
        if (hrs > 23) hrs = 0;
        delay(100);
      }
      if (digitalRead(dec) == LOW)
      {
        hrs = hrs - 1;
        if (hrs <= -1) hrs = 0;
        delay(100);
      }
      if (digitalRead(set) == LOW)
      {
        hrs_flag = false;
        delay(250);
      }
    }
    if (sec == 0 && hrs == 0 && Min == 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  INVAID TIME");
      delay(2000);
    }
    else
    {
      EEPROM.write(add_hrs, hrs);
      EEPROM.write(add_min, Min);
      EEPROM.write(add_sec, sec);
    }
    INIT();
  }
}

void INIT()
{
  hrs = EEPROM.read(add_hrs);
  Min = EEPROM.read(add_min);
  sec = EEPROM.read(add_sec);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start / Set Time");
  lcd.setCursor(4, 1);
  if (hrs <= 9)
  {
    lcd.print('0');
  }
  lcd.print(hrs);
  lcd.print(':');
  if (Min <= 9)
  {
    lcd.print('0');
  }
  lcd.print(Min);
  lcd.print(':');
  if (sec <= 9)
  {
    lcd.print('0');
  }
  lcd.print(sec);
  min_flag = true;
  hrs_flag = true;
  delay(500);
}
//--------------(c) Electronics project hub -----------//
