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
// Callback for screen touch
//----------------------------------------------
void OnClick(uint16_t xpos, uint16_t ypos) 
{
  Serial.print("Click -> "); 
  Serial.print("x:"); Serial.print(xpos); Serial.print(" ");
  Serial.print("y:"); Serial.println(ypos);

  manager.HandleScreenClick(xpos, ypos);
}



 
