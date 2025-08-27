#include <Arduino.h>
#include <Vex5.h>
#include <Servo.h>
Servo camera;

Vex5_Motor motor1;
Vex5_Motor motor2;
Vex5_Motor motor3;
Vex5_Motor motor4;
Vex5_Motor motor5;
Vex5_Motor ebedka1;
Vex5_Motor ebedka2;

int leftspeed = 0;
int period = 5000;
int rightspeed = 0;
int maxspeed = 3000;
int camspeed = 0;
unsigned long time_now = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("HIIII UWU :3 :D");
  Vex5.begin();
  motor1.begin(VEX5_PORT_1);
  motor2.begin(VEX5_PORT_6);
  motor3.begin(VEX5_PORT_7);
  motor4.begin(VEX5_PORT_12);
  motor5.begin(VEX5_PORT_8);
  ebedka1.begin(VEX5_PORT_5);
  ebedka2.begin(VEX5_PORT_4);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  camera.attach(28);
}

void loop() {

  /* while(Serial1.available()){
    gps.encode(Serial1.read());}// encode gps data
    if(millis() >= time_now + period){

    if(gps.location.isValid()){
      digitalWrite(13, LOW);
      Serial.println("Logging...");
        File dataFile = SD.open("log" + String(filecunt) + ".txt", FILE_WRITE);;
        dataFile.print(gps.location.lat(), 5);
        dataFile.print(" ");
        dataFile.print(gps.location.lng(), 5);
        dataFile.println(" ");
        time_now += period;
        Serial.println("Logged!");
        dataFile.close();
        digitalWrite(13, HIGH);}
  } Логика GPS, больше не используется */

	//motor.setSpeed(200);
  // 5 - KNOB LEFT
  // 6 - KNOB RIGHT
  // 3 - GAS
  // 4 - YAW
  // 2 - PITCH
  // 7 - ROLL


  maxspeed = map(pulseIn(3, HIGH), 1000, 2000, 0, 3000);
  if(pulseIn(7, HIGH) > 1500){
      leftspeed = map(pulseIn(7, HIGH), 1000, 2000, maxspeed, 0 - maxspeed);
      rightspeed = map(pulseIn(7, HIGH), 1000, 2000, maxspeed, 0 - maxspeed);
  }
  else if(pulseIn(7, HIGH) < 1400){
      leftspeed = map(pulseIn(7, HIGH), 1000, 2000, maxspeed, 0 - maxspeed);
      rightspeed = map(pulseIn(7, HIGH), 1000, 2000, maxspeed, 0- maxspeed);
  }
  else {
    leftspeed = map(pulseIn(2, HIGH), 1000, 2000, maxspeed, 0- maxspeed);
    rightspeed = map(pulseIn(2, HIGH), 1000, 2000, 0 -maxspeed, maxspeed);
  }

  if(pulseIn(4, HIGH) > 1800) {
    ebedka1.setSpeed(2000);
    ebedka2.setSpeed(-2000);

  }
  else if(pulseIn(4, HIGH) < 1300){
    ebedka1.setSpeed(-2000);
    ebedka2.setSpeed(2000);

  }
  else{
    ebedka1.setSpeed(0);
    ebedka2.setSpeed(0);
  }
  motor1.setSpeed(rightspeed);
  motor2.setSpeed(rightspeed);
  motor3.setSpeed(leftspeed);
  motor4.setSpeed(leftspeed);

  int angle = map(pulseIn(5, HIGH), 1000, 2000, 0, -300); // Последнее число - условная единица позиции моторов
  Serial.println(pulseIn(5, HIGH));
  int anglecam = map(pulseIn(6, HIGH), 1000, 2000, 0, 270); // Последнее число - условная единица позиции моторов
  motor5.setPosition(angle, 1000);
  camera.write(anglecam);
}