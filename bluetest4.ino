#include <Servo.h>
#include <SoftwareSerial.h>

Servo motor1;
Servo motor2;

int state = 0;
void setup() 
{
  Serial.begin(9600);
  motor1.attach(9);
  motor2.attach(11);
  pinMode(13, OUTPUT);
}
void loop()
{
  int data;
  if(Serial.available() > 0)  
  {
    digitalWrite(13, HIGH);
    data = Serial.read();
    Serial.println(data);

    if(data == 1)
    {
      state = 1;
    }
    if(data == 2)
    {
      state = 2;
    }
    else if(data == 20)
    {
       digitalWrite(13, LOW);
    }
    else if(data > 20)
    {
      if(state == 1)
      {
        motor1.write(data);
      }
      else if(state == 2)
      {
        motor2.write(data);
      }
    }
  }
  else
  {
    data = 0;
  }
    delay(25);
}
