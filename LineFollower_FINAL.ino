#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 280 // (180) this is the 'minimum' pulse length count (out of 4096)
#define SERVOSTOP 340 // pulse length to stop de servo
#define SERVOMAX 400 // (500) this is the 'maximum' pulse length count (out of 4096)

/*** Global variables ***/
int servo_derecho=1;
int servo_izquierdo=0;
int NEGRO=0;
int buzzer = 9;
boolean out;

/*** Function declaration ***/
void setup() {
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates
  pinMode( 2 , INPUT);
  pinMode( 3 , INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int ir_derecho=digitalRead(3);
  int ir_izquierdo=digitalRead(2);
  if(ir_derecho == 1 && ir_izquierdo == 1){
    if(out == true){ 
      pwm.setPWM(servo_derecho, 0, SERVOMIN); 
      pwm.setPWM(servo_izquierdo,0, SERVOMIN);
     }
    if(out == false){
      ir_derecho=digitalRead(3);
      ir_izquierdo=digitalRead(2);
      pwm.setPWM(servo_derecho, 0, SERVOMAX); 
      pwm.setPWM(servo_izquierdo, 0, SERVOMAX);
     }   
   }
    if (ir_derecho == NEGRO) {
    pwm.setPWM(servo_izquierdo, 0, SERVOMIN); 
    analogWrite(buzzer, 100); 
    delay(10); 
    out=true; 
   } else {
    pwm.setPWM(servo_izquierdo, 0, SERVOSTOP);
    analogWrite(buzzer, 0);
    delay(10);
   }
  if (ir_izquierdo == NEGRO) {
    pwm.setPWM(servo_derecho, 0, SERVOMAX);
    analogWrite(buzzer, 0);
    delay(10);
    out=false;
   } else {
    pwm.setPWM(servo_derecho, 0, SERVOSTOP); 
    analogWrite(buzzer, 100);
    delay(10);  
   }
   // In this part we know in which part of the memory the variables are stored
   Serial.println((long) &servo_derecho, HEX); 
   Serial.println((long) &servo_izquierdo, HEX);
   Serial.println((long) &NEGRO, HEX);
   Serial.println((long) &buzzer, HEX);
   Serial.println((long) &out, HEX);
   Serial.println((long) &ir_derecho, HEX);
   Serial.println((long) &ir_izquierdo, HEX);
   delay(10000);
}
