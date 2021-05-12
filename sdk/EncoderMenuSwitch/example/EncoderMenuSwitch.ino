#include "EncoderMenuSwitch.h"

EncoderMenuSwitch encoder;

void setup()
{
  Serial.begin(9600);
  
  encoder.Initialize(25, 27, 29);
}

void loop()
{
  encoder.Dispatch();
}

void OnEncoderMoved(EncoderMenuSwitch::EncoderDirection dir)
{
  Serial.println(dir);
}

void OnEncoderClick()
{
  Serial.println("CLICK");
}