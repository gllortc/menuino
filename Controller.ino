//------------------------------------------------------------------
// Library includes
//------------------------------------------------------------------

#include <EncoderMenuSwitch.h>
#include "Menuino.h" 

// Pin 13 has an LED connected on most Arduino boards.
#define BOARD_LED 13

Menuino           menuino;

//------------------------------------------------------------------
// Arduino main routines
//------------------------------------------------------------------

void setup()
{
  // Shut down board LED
  pinMode(BOARD_LED, OUTPUT);
  digitalWrite(BOARD_LED, HIGH); 

  Serial.begin(9600);

  menuino.Initialize();
}
 
void loop()
{
  menuino.Dispatch();
}

//----------------------------------------------
// Touchscreen callback
//----------------------------------------------
void OnClick(uint16_t xpos, uint16_t ypos) 
{
  menuino.HandleScreenClick(xpos, ypos);
}

//----------------------------------------------
// Encoder movement callback
//----------------------------------------------
void OnEncoderMoved(EncoderMenuSwitch::EncoderDirection dir)
{
  menuino.HandleEncoderMoved(dir);
}

//----------------------------------------------
// Encoder click callback
//----------------------------------------------
void OnEncoderClick()
{
  menuino.HandleEncoderClick();
}

//------------------------------------------------------
// XPN Callback: XPN power notification
//------------------------------------------------------
void notifyXNetPower(uint8_t state) 
{
  menuino.HandleMasterStatusNotify(state);
}

//------------------------------------------------------
// XPN Callback: Locomotive status notification
//------------------------------------------------------
void notifyLokAll(uint8_t adrHigh, uint8_t adrLow, boolean busy, uint8_t steps, uint8_t speed, uint8_t direction, uint8_t F0, uint8_t F1, uint8_t F2, uint8_t F3, boolean req) 
{
  menuino.HandleEngineNotify(adrHigh, adrLow, steps, speed, direction, F0, F1, F2, F3);
}

//------------------------------------------------------
// XPN Callback: network status notification
//------------------------------------------------------
void notifyXNetStatus(uint8_t state) 
{
  // TODO: should be a separate LED in the controller
  digitalWrite(LED_BUILTIN, state); 
}



 
