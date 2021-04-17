#import <Arduino.h>
#include "ScreenObjects.h"
#include "TouchDisplay.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
TouchDisplay::TouchDisplay() {}

//----------------------------------------------
// Initialize the TFT display
//----------------------------------------------
void TouchDisplay::Initialize()
{
   uint16_t ID;
   // uint16_t tmp;
   
   // Screen initialization
   ID = tft.readID();
   
   // Screen equivalences
   if (ID == 0x0D3D3) ID = 0x9481;
   
   // Initialization
   tft.begin(ID);
   
   // if (tft.height() > tft.width()) 
   tft.setRotation(Orientation);
   
   DrawBaseScreen("TRAIN CONTROL");

   PrintTextLine("Running MENUINO UI version 1.1");
   delay(1500);
   PrintTextLine("> Starting LCD manager");
   delay(200);
   PrintTextLine("> Ready");
   delay(200);
   
   // Touchscreen initialization
   // switch (Orientation) // adjust for different aspects
   // {      
      // case 0:   break;        //no change,  calibrated for PORTRAIT
      // case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
      // case 2:   SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); break;
      // case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
   // }
   ts = TouchScreen(XP, YP, XM, YM, 260);     // call the constructor AGAIN with new values.
}

//----------------------------------------------
// Touschscreen dispatcher
//----------------------------------------------
void TouchDisplay::Dispatch()
{
   uint8_t  idx = -1;
   uint16_t xpos;       //screen coordinates
   uint16_t ypos;
   
   tp = ts.getPoint();  // tp.x, tp.y are ADC values

   // if sharing pins, you'll need to fix the directions of the touchscreen pins
   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);
   pinMode(XP, OUTPUT);
   pinMode(YM, OUTPUT);
   
   if (!(tp.z > MINPRESSURE && tp.z < MAXPRESSURE)) return 99;

   // Avoid read multiple pressed
   delay(100);
   
   // is controller wired for Landscape ? or are we oriented in Landscape?
   if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
   
   // scale from 0->1023 to tft.width  i.e. left = 0, rt = width
   // most mcufriend have touch (with icons) that extends below the TFT
   // screens without icons need to reserve a space for "erase"
   // scale the ADC values from ts.getPoint() to screen values e.g. 0-239
   xpos = map(tp.x, TS_LEFT, TS_RT, tft.width(), 0);
   ypos = map(tp.y, TS_TOP, TS_BOT, tft.height(), 0);

   if (OnClick)
      OnClick(xpos, ypos);
}

//----------------------------------------------
// Paint a blank screen with caption
//----------------------------------------------
void TouchDisplay::DrawBaseScreen(const char* caption)
{
  tft.fillScreen(COLOR_SCR_BACKGROUND);
  tft.fillRect(0, 0,  240, 20, COLOR_NAVBAR_BACKGROUND);
  tft.fillRect(0, 21, 240, 50, COLOR_SCR_CAPTION_BACKGROUND);  

  tft.drawBitmap(220, 2, BMP_XPN_OFF, 18, 18, COLOR_NAVBAR_DISABLED);
  tft.drawBitmap(10, 35, BMP_MENU,    24, 24, 0xFFFF);
   
  tft.setTextColor(COLOR_SCR_TEXT);
  tft.setTextSize(2);                 
  tft.setCursor(40, 40);
  tft.print(caption);

  // Set default cursor position and text size at begining to the scr
  tft.setTextSize(1);      
  tft.setCursor(1, 85);
}

//----------------------------------------------
// Print a text line in the screen
//----------------------------------------------
void TouchDisplay::PrintTextLine(const char *text)
{
  tft.setTextColor(COLOR_SCR_TEXT);
  tft.println(text);
}

//----------------------------------------------
// Print an error text line in the screen
//----------------------------------------------
void TouchDisplay::PrintErrTextLine(const char *text)
{
   tft.setTextColor(COLOR_SCR_ERROR_TEXT);
   tft.println(text);
}
