#include <Servo.h>
#include <math.h>
#include <string.h>

Servo servo_vertical;
Servo servo_horizontal;

int currentPosVertical = 45;
int currentPosHorizontal = 45;

int ledYes = 11;
int ledNo = 12;
//
char command;
float sp = 2.0;

void setup() 
{
  servo_vertical.attach(9);
  servo_horizontal.attach(10);

  Serial.begin(9600);

  pinMode(ledYes, OUTPUT);
  pinMode(ledNo, OUTPUT);
  
  servo_horizontal.write(currentPosHorizontal);
  servo_vertical.write(currentPosVertical);
}

void loop()
{
  if (Serial.available() > 0)
  {
    command = Serial.read();
    Serial.println(command); 
    if(command == '0')
    {
      //Idle
      digitalWrite(ledNo, HIGH);
      digitalWrite(ledYes, LOW);
    }
    else
    {
      digitalWrite(ledNo, LOW);
      digitalWrite(ledYes, HIGH);
    }
    
    if(command == '1')
    {
      turnUp();
    }
    if(command == '2')
    {
      turnDown();
    }
    if(command == '3')
    {
      idle_vertical();
    }
    
    if(command == '4')
    {
      turnRight();
    }
    if(command == '5')
    {
      turnLeft();
    }
    if(command == '6')
    {
      idle_horizontal();
    }
  }  
}

void idle_vertical()
{
  servo_vertical.write(currentPosVertical);
}

void turnUp()
{
  currentPosVertical += sp;
  servo_vertical.write(currentPosVertical);
}

void turnDown()
{
  currentPosVertical -= sp;
  servo_vertical.write(currentPosVertical);
}

void idle_horizontal()
{
  servo_horizontal.write(currentPosHorizontal);
}

void turnLeft()
{
  currentPosHorizontal -= sp;
  servo_horizontal.write(currentPosHorizontal);
}

void turnRight()
{
  currentPosHorizontal += sp;
  servo_horizontal.write(currentPosHorizontal);
}
