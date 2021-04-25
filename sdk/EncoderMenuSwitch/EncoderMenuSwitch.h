#ifndef _ENCODERMENUSWITCH_H 
#define _ENCODERMENUSWITCH_H 

#include <Arduino.h>

class EncoderMenuSwitch
{
  // Encoder variables
  bool          init             = false;
  uint8_t       pinOutA;
  uint8_t       pinOutB;
  uint8_t       valuePinA        = LOW;
  uint8_t       valuePinAcurrent = LOW;
  
  // Switchbutton variables
  bool          btnFirstPress    = false;
  uint8_t       btnPin;
  unsigned long btnElapsedMs     = 0;

public:

  enum EncoderDirection {
    ENCODER_UP,
    ENCODER_DOWN
  };

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  EncoderMenuSwitch();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(uint8_t pinA, uint8_t pinB, uint8_t pinSwt);
  void Dispatch();

};

//----------------------------------------------
// Callbacks
//----------------------------------------------
extern void OnEncoderMoved(EncoderMenuSwitch::EncoderDirection dir) __attribute__ ((weak));
extern void OnEncoderClick() __attribute__ ((weak));

#endif