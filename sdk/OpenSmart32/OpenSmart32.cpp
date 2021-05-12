#include <Arduino.h>
#include "OpenSmart32.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
OpenSmart32::OpenSmart32() {}

//----------------------------------------------
// Initialize the TFT display
//----------------------------------------------
void OpenSmart32::Initialize()
{
  uint16_t ID;

  //-----------------------------
  // Screen initialization
  //-----------------------------
  
  ID = tft.readID();
   
  // Screen equivalences
  if (ID == 0x0D3D3) ID = 0x9481;
   
  // Initialization
  tft.begin(ID);
   
  // if (tft.height() > tft.width()) 
  tft.setRotation(Orientation);
   
  // Touchscreen initialization
  // switch (Orientation) // adjust for different aspects
  // {      
      // case 0:   break;        //no change,  calibrated for PORTRAIT
      // case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
      // case 2:   
      SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); // break;
      // case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
  // }
  ts = TouchScreen(XP, YP, XM, YM, 260);     // call the constructor AGAIN with new values.
}

//----------------------------------------------
// Check for touchscreen press
//----------------------------------------------
void OpenSmart32::Dispatch()
{
  tp = ts.getPoint();  // tp.x, tp.y are ADC values

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(XP, OUTPUT);
  pinMode(YM, OUTPUT);

  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE)
  {
    delay(100);
    
    // is controller wired for Landscape ? or are we oriented in Landscape?
    if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
    
    if (OnDisplayClick) 
    {
      // scale from 0->1023 to tft.width  i.e. left = 0, rt = width
      // most mcufriend have touch (with icons) that extends below the TFT
      // screens without icons need to reserve a space for "erase"
      // scale the ADC values from ts.getPoint() to screen values e.g. 0-239

      OnDisplayClick(map(tp.x, TS_LEFT, TS_RT,  tft.width(),  0), 
                     map(tp.y, TS_TOP,  TS_BOT, tft.height(), 0));
    }
  }
}
