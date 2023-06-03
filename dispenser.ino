#include <Servo.h>

struct EStop
{
  const int ledPin;    // the led/output pin
  const int buttonPin; // the button/input pin
  int state;           // the state of the button (pressed/not pressed)
  bool isOn;           // is the mechanism on(True) or off(False)?
};

struct Sensor
{
  const int trigPin; // ultrasonic's TRIG pin
  const int echoPin; // utrasonic's ECHO pin
  long duration;     // the sound wave travel time in microseconds
  int distance;      // the calculated distance
};

struct WaterPump
{
  const int motorPin; // the pin for the water pump
  bool canDispense;   // can the mechanism pump water?
  EStop btn;          // the mechanism's Estop button
  Sensor sensor;      // water pump's sensor
};

struct PillDropper
{
  const int motorPin; // the pin for the servo motor
  bool canDispense;   // can the mechanism drop pills?
  int dropDistance;   // how far the servo moves up and down
  EStop btn;          // the mechanism's Estop button
  Sensor sensor;      // pill dropper's sensor
};

// ORDER: led, button, TRUE
EStop pillDropperEStop = {4, 6, 0, true};
EStop waterPumpEStop = {5, 7, 0, true};
// ORDER: trig, echo, 0, 0
Sensor pillDropperSensor = {10, 11, 0, 0};
Sensor waterPumpSensor = {12, 13, 0, 0};

Servo pillDropperServo;
Servo waterPumpServo;

PillDropper pillDropper = {2, true, 60, pillDropperEStop, pillDropperSensor};
WaterPump waterPump = {3, true, waterPumpEStop, waterPumpSensor};

void setup()
{
  // put your setup code here, to run once:
  // PillDropper
  // mechanism
  pinMode(pillDropper.sensor.trigPin, OUTPUT);
  pinMode(pillDropper.sensor.echoPin, INPUT);
  // estop
  pinMode(pillDropper.btn.ledPin, OUTPUT);
  pinMode(pillDropper.btn.buttonPin, INPUT_PULLUP);
  digitalWrite(pillDropper.btn.ledPin, HIGH);
  pillDropperServo.attach(pillDropper.motorPin);
  pillDropperServo.write(-pillDropper.dropDistance);
  // WaterPump
  // mechanism
  pinMode(waterPump.motorPin, OUTPUT);
  digitalWrite(waterPump.motorPin, LOW);
  pinMode(waterPump.sensor.trigPin, OUTPUT);
  pinMode(waterPump.sensor.echoPin, INPUT);
  // estop
  pinMode(waterPump.btn.ledPin, OUTPUT);
  pinMode(waterPump.btn.buttonPin, INPUT_PULLUP);
  digitalWrite(waterPump.btn.ledPin, HIGH);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Pill Dropper
  // detect if hand is next to the front of the mechanism thru the ultrasonic sensor
  digitalWrite(pillDropper.sensor.trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pillDropper.sensor.trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pillDropper.sensor.trigPin, LOW);
  pillDropper.sensor.duration = pulseIn(pillDropper.sensor.echoPin, HIGH);
  pillDropper.sensor.distance = pillDropper.sensor.duration * 0.034 / 2;
  // check if the dropper is on
  if (pillDropper.btn.isOn)
  {
    if (pillDropper.sensor.distance == 2 && pillDropper.canDispense)
    {                                                   // is the distance is just right and not currently dispensing.
      pillDropper.canDispense = false;                  // disable future dispensing
      pillDropperServo.write(pillDropper.dropDistance); // move servo down
      delay(1000);
      pillDropperServo.write(-pillDropper.dropDistance); // return servo back to default
      delay(1000);
    }
    else if (pillDropper.sensor.distance >= 10)
    {                                 // is nothing close to sensor
      pillDropper.canDispense = true; // enable future dispensing
    }
  }

  // WaterPump
  // detect if hand is next to the front of the mechanism thru the ultrasonic sensor
  digitalWrite(waterPump.sensor.trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(waterPump.sensor.trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(waterPump.sensor.trigPin, LOW);
  waterPump.sensor.duration = pulseIn(waterPump.sensor.echoPin, HIGH);
  waterPump.sensor.distance = waterPump.sensor.duration * 0.034 / 2;
  // check if pump is on
  if (waterPump.btn.isOn)
  {
    if (waterPump.sensor.distance == 2 && waterPump.canDispense)
    {                                // is the distance just right and not currently dispensing (pumping)
      waterPump.canDispense = false; // disable future dispensing
      digitalWrite(waterPump.motorPin, HIGH);
      delay(2000);
    }
    else if (waterPump.sensor.distance >= 10)
    {                                        // is nothing close to sensor
      digitalWrite(waterPump.motorPin, LOW); // force pump off
      waterPump.canDispense = true;          // enable future dispensing
    }
    else if (waterPump.canDispense == false)
    {                                        // can the mechanism NOT pump water
      digitalWrite(waterPump.motorPin, LOW); // force pump off
    }
  }

  // Both EStops
  // check if button is pressed. if so, change the mechanism's on state
  pillDropper.btn.state = digitalRead(pillDropper.btn.buttonPin);
  if (pillDropper.btn.state == LOW)
  {
    pillDropper.btn.isOn = false;
  }

  // is mechanism is on, turn on it's LED
  // else, turn off
  if (pillDropper.btn.isOn)
  {
    digitalWrite(pillDropper.btn.ledPin, HIGH);
  }
  else
  {
    digitalWrite(pillDropper.btn.ledPin, LOW);
  }

  // check if button is pressed .if so, change the mechanism's on state
  waterPump.btn.state = digitalRead(waterPump.btn.buttonPin);
  if (waterPump.btn.state == LOW)
  {
    waterPump.btn.isOn = false;
    digitalWrite(waterPump.motorPin, LOW);
  }

  // is mechanism is on, turn on it's LED
  // else, turn off
  if (waterPump.btn.isOn)
  {
    digitalWrite(waterPump.btn.ledPin, HIGH);
  }
  else
  {
    digitalWrite(waterPump.btn.ledPin, LOW);
  }
}
