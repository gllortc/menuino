#include <Arduino.h>
#include "EncoderMenuSwitch.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
EncoderMenuSwitch::EncoderMenuSwitch() { }

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void EncoderMenuSwitch::Initialize(byte pinA, byte pinB, byte pinSwitch)
{
  pinOutA = pinA;
  pinOutB = pinB;
  btnPin  = pinSwitch;

  pinMode(pinOutA, INPUT_PULLUP);
  pinMode(pinOutB, INPUT_PULLUP);
  pinMode(btnPin,  INPUT_PULLUP);
}

//------------------------------------------------------
// Encoder dispatcher
//------------------------------------------------------
void EncoderMenuSwitch::Dispatch()
{ 
  // Encoder read
  valuePinAcurrent = digitalRead(pinOutA);
  if ((valuePinA == LOW) && (valuePinAcurrent == HIGH)) 
  {
    if (init)
    {
      if (digitalRead(pinOutB) == LOW) 
      {
        if (OnEncoderMoved) OnEncoderMoved(EncoderDirection::ENCODER_UP);
      } 
      else 
      {
        if (OnEncoderMoved) OnEncoderMoved(EncoderDirection::ENCODER_DOWN);
      }
    }
    else
    {
      init = true;
    }
  }
  valuePinA = valuePinAcurrent;
  
  // Push button read
  if (digitalRead(btnPin) == 0)
  {
    if (!btnFirstPress)
    {
       btnFirstPress = true; 
       btnElapsedMs = millis(); 
    } 
    else
    {
      if ((millis() - btnElapsedMs) > 200)
      {  
          btnFirstPress = false;
          if (OnEncoderClick) OnEncoderClick();
      }
    }
  }
}