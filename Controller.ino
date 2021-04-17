//------------------------------------------------------------------
// Library includes
//------------------------------------------------------------------

#include "TouchDisplay.h" 
#include "ScreenManager.h" 

// Pin 13 has an LED connected on most Arduino boards.
#define BOARD_LED 13

ScreenManager manager;

//------------------------------------------------------------------
// Arduino main routines
//------------------------------------------------------------------

void setup()
{
  // Shut down board LED
  pinMode(BOARD_LED, OUTPUT);
  digitalWrite(BOARD_LED, HIGH); 

  Serial.begin(9600);

  manager.Initialize();
}
 
void loop()
{
  manager.Dispatch();
}

//----------------------------------------------
// Touchscreen callback
//----------------------------------------------
void OnClick(uint16_t xpos, uint16_t ypos) 
{
  Serial.print("Click -> "); 
  Serial.print("x:"); Serial.print(xpos); Serial.print(" ");
  Serial.print("y:"); Serial.println(ypos);

  manager.HandleScreenClick(xpos, ypos);
}

//------------------------------------------------------
// XPN Callback: XPN power notification
//------------------------------------------------------
void notifyXNetPower(uint8_t State) 
{
  manager.HandleMasterStatusNotify(State);
}

//------------------------------------------------------
// XPN Callback: Locomotive status notification
//------------------------------------------------------
void notifyLokAll(uint8_t Adr_High, uint8_t Adr_Low, boolean Busy, uint8_t Steps, uint8_t Speed, uint8_t Direction, uint8_t F0, uint8_t F1, uint8_t F2, uint8_t F3, boolean Req) 
{
  manager.HandleEngineNotify(Adr_High, Adr_Low, Busy, Steps, Speed, Direction, F0, F1, F2, F3, Req);
}



 
