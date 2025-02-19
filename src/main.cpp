// INCLUDES
#include <Arduino.h>
#include <ServoSmooth.h>
#include <GyverMotor2.h>
#include <SoftwareSerial.h>
// INCLUDES

// SETTINGS
// SETTINGS

// PINS
#define RMOTORA 2
#define RMOTORB 4
#define RMOTORPWM 3

#define LMOTORA 9
#define LMOTORB 10
#define LMOTORPWM 11
#define BT_RX 12
#define BT_TX 13
// PINS

// VARS
uint32_t tmr;
boolean parsingDone, parsingStart;
String string_convert;
// VARS

// INITS
SoftwareSerial BTser(BT_RX, BT_TX);
GMotor2<DRIVER3WIRE> right_mot(RMOTORA, RMOTORB, RMOTORPWM);
GMotor2<DRIVER3WIRE> left_mot(LMOTORA, LMOTORB, LMOTORPWM);
ServoSmooth Servo_rot;
ServoSmooth Servo_Up;
ServoSmooth Servo_Fd;
// INITS

void parsing() {
  if (BTser.available() > 0) {       // если в буфере есть данные
    char incomingChar = BTser.read();// читаем из буфера
    if (parsingStart) {                 // начать принятие пакетов
      if (incomingChar == ' ') {        // принят пакет dataX
        //dataX = string_convert.toInt(); // ковертируем принятый пакет в переменную
        string_convert = "";            // очищаем переменную пакета
      }
      else if (incomingChar == ';') {   // принят пакет dataY
        //dataY = string_convert.toInt(); // ковертируем принятый пакет в переменную
        string_convert = "";            // очищаем переменную пакета
        parsingStart = false;           // закончить принятие пакетов
        parsingDone = true;             // парсинг окончен, можно переходить к движению
      } else {
        string_convert += incomingChar; // записываем  принятые данные в переменную
      }
    }
    if (incomingChar == '$') {          // начало парсинга
      parsingDone = true;              // начать принятие пакетов
    }
  }
}

void setup()
{
  right_mot.setSmoothSpeed(10);
  left_mot.setSmoothSpeed(10);
  right_mot.smoothMode(true);
  left_mot.smoothMode(true);
  left_mot.reverse(true);

  Servo_rot.setSpeed(90);
  Servo_Up.setSpeed(90);
  Servo_Fd.setSpeed(90);
  Servo_rot.setAccel(0.1);
  Servo_Up.setAccel(0.1);
  Servo_Fd.setAccel(0.1);
  Servo_rot.setAutoDetach(false);
  Servo_Up.setAutoDetach(false);
  Servo_Fd.setAutoDetach(false);

  Servo_rot.attach(5, 90);
  Servo_Up.attach(6, 120);
  Servo_Fd.attach(7, 150);
}

void loop()
{
  right_mot.tick();
  left_mot.tick();

  Servo_rot.tick();
  Servo_Fd.tick();
  Servo_Up.tick();
}