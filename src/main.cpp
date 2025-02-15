// INCLUDES
#include <Arduino.h>
#include <ServoSmooth.h>
#include <GyverMotor2.h>
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
// PINS

// VARS
uint32_t tmr;
boolean flag;
// VARS

// INITS
GMotor2<DRIVER3WIRE> right_mot(RMOTORA, RMOTORB, RMOTORPWM);
GMotor2<DRIVER3WIRE> left_mot(LMOTORA, LMOTORB, LMOTORPWM);
ServoSmooth Servo_rot;
ServoSmooth Servo_Up;
ServoSmooth Servo_Fd;
// INITS

void setup() {
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
  Servo_Up.setAutoDetach(false);
  Servo_Fd.setAutoDetach(false);
  
  //Servo_rot.attach(5);
  Servo_Up.attach(6, 120);
  Servo_Up.smoothStart();
  Servo_Fd.attach(7, 180);
  Servo_Fd.smoothStart();
}

void loop() {
  right_mot.tick();
  left_mot.tick();

  //Servo_rot.tick();
  Servo_Fd.tick();
  Servo_Up.tick();

  if (millis() - tmr >= 3000) {
    tmr = millis();
    flag = !flag;
    Servo_Fd.setTargetDeg(flag ? 180 : 80);
    Servo_Up.setTargetDeg(flag ? 120 : 150);
  }
}