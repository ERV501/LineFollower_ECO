#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define TRI_Pin 4
#define ECH_Pin 5
#define SERVOMIN 280
#define SERVOMAX 400
#define SERVOSTOP 340

/*** Global variables ***/
int servo_derecho=1;
int servo_izquierdo=0;
int NEGRO=0;
boolean out;
                                                                                                                  /***THIS COULDN'T BE TESTED ON THE ACTUAL ROBOT ***/
/*** Function declaration ***/
void setup() {
pwm.begin();
pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates
pinMode( 2 , INPUT);
pinMode( 3 , INPUT);
pinMode(TRI_Pin,OUTPUT);
pinMode(ECH_Pin, INPUT);
Serial.begin (9600);
}

void loop() {
  int ir_derecho=digitalRead(3);
  int ir_izquierdo=digitalRead(2);
  long duracion, distancia;
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
    delay(10); 
    out=true; 
   } else {
    pwm.setPWM(servo_izquierdo, 0, SERVOSTOP);
    delay(10);
   }
  if (ir_izquierdo == NEGRO) {
    pwm.setPWM(servo_derecho, 0, SERVOMAX);
    delay(10);
    out=false;
   } else {
    pwm.setPWM(servo_derecho, 0, SERVOSTOP); 
    delay(10);  
   }
  
digitalWrite(TRI_Pin, LOW); // We secure the trigger is active
  delayMicroseconds(10); // Trigger is LOW
  digitalWrite(TRI_Pin, HIGH); // Activate the output pulse
  delayMicroseconds(10); // We wait 10 microseconds, the pulse is still active
  digitalWrite(TRI_Pin, LOW); // We cut the pulse and wait for the echo
  duracion = pulseIn (ECH_Pin, HIGH);
  distancia = duracion/58;
  delay(500);
}



