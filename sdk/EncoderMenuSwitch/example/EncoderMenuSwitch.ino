#include "EncoderSwitch.h"

EncoderSwitch encoder;

void setup()
{
  Serial.begin(9600);
  
  encoder.Initialize(25, 27, 29);
}

void loop()
{
  encoder.Dispatch();
}

void OnEncoderValueChanged(uint16_t newValue)
{
  Serial.println(newValue);
}

void OnEncoderClick()
{
  Serial.println("CLICK");
}
