#include<Servo.h>


struct EStop {
    const int ledPin;
    const int buttonPin;
    int state;
    bool isOn;
};

struct Sensor {
  const int trigPin;
  const int echoPin;
  long duration;
  int distance;
};

struct WaterPump {
  const int motorPin;
  bool canDispense;
  EStop state;
  Sensor sensor;
};

struct PillDropper {
  const int motorPin;
  bool canDispense;
  int dropDistance;
  EStop state;
  Sensor sensor;
};

//ORDER: led, button, TRUE
EStop pillDropperEStop = {4, 6, 0, true};
EStop waterPumpEStop = {5, 7, 0, true};
//ORDER: trig, echo, 0, 0
Sensor pillDropperSensor = {10, 11, 0,0};
Sensor waterPumpSensor = {12,13,0,0};

Servo pillDropperServo;
Servo waterPumpServo;

PillDropper pillDropper = {2, true, -60, pillDropperEStop, pillDropperSensor};
WaterPump waterPump = {3, true, waterPumpEStop, waterPumpSensor};



void setup() {
  // put your setup code here, to run once:
  //PillDropper
  pinMode(pillDropper.sensor.trigPin, OUTPUT);
  pinMode(pillDropper.sensor.echoPin, INPUT);
  pinMode(pillDropper.state.ledPin, OUTPUT);
  pinMode(pillDropper.state.buttonPin, INPUT_PULLUP);
  digitalWrite(pillDropper.state.ledPin, HIGH);
  pillDropperServo.attach(pillDropper.motorPin);
  //WaterPump  
  pinMode(waterPump.motorPin, OUTPUT);
  digitalWrite(waterPump.motorPin, LOW);
  pinMode(waterPump.sensor.trigPin, OUTPUT);
  pinMode(waterPump.sensor.echoPin, INPUT);
  pinMode(waterPump.state.ledPin, OUTPUT);
  pinMode(waterPump.state.buttonPin, INPUT_PULLUP);
  digitalWrite(waterPump.state.ledPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Pill Dropper
  digitalWrite(pillDropper.sensor.trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pillDropper.sensor.trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pillDropper.sensor.trigPin, LOW);
  pillDropper.sensor.duration = pulseIn(pillDropper.sensor.echoPin, HIGH);
  pillDropper.sensor.distance = pillDropper.sensor.duration * 0.034 / 2;
  if(pillDropper.state.isOn) {
    if(pillDropper.sensor.distance == 2 && pillDropper.canDispense) {
      pillDropper.canDispense = false;
      pillDropperServo.write(pillDropper.dropDistance);
      delay(1000);
      pillDropperServo.write(-pillDropper.dropDistance);
      delay(1000);
    } else if (pillDropper.sensor.distance >= 10) {
      pillDropper.canDispense = true;
    }
  }

  //WaterPump
  digitalWrite(waterPump.sensor.trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(waterPump.sensor.trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(waterPump.sensor.trigPin, LOW);
  waterPump.sensor.duration = pulseIn(waterPump.sensor.echoPin, HIGH);
  waterPump.sensor.distance = waterPump.sensor.duration * 0.034 / 2;
  if(waterPump.state.isOn) {
    if(waterPump.sensor.distance == 2 && waterPump.canDispense) {
      waterPump.canDispense = false;
      digitalWrite(waterPump.motorPin, HIGH);
      delay(2000);
    } else if (waterPump.sensor.distance >= 10) {
      digitalWrite(waterPump.motorPin, LOW);
      waterPump.canDispense = true;
    } else if (waterPump.canDispense == false) {
      digitalWrite(waterPump.motorPin, LOW);
    }
  }

  //Both EStops
  pillDropper.state.state = digitalRead(pillDropper.state.buttonPin);
  if(pillDropper.state.state == LOW) {
    pillDropper.state.isOn = false;
  }

  if(pillDropper.state.isOn) {
    digitalWrite(pillDropper.state.ledPin, HIGH);
  } else {
    digitalWrite(pillDropper.state.ledPin, LOW);  
  }

  waterPump.state.state = digitalRead(waterPump.state.buttonPin);
  if(waterPump.state.state == LOW) {
    waterPump.state.isOn = false;
  }

  if(waterPump.state.isOn) {
    digitalWrite(waterPump.state.ledPin, HIGH);
  } else {
    digitalWrite(waterPump.state.ledPin, LOW);  
  }



}
