#import <Arduino.h>
#include "DriveScreen.h"
#include "ScreenObjects.h"
#include <Encoder_Polling.h>

//----------------------------------------------
// Constructor
//----------------------------------------------
DriveScreen::DriveScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void DriveScreen::Initialize(TouchDisplay lcdDisplay)
{
  disp    = lcdDisplay;
  id      = SCR_DRIVE_ID;
  caption = "E103 - Track 1";

  encoder_begin(ENCODER_PIN_1, ENCODER_PIN_2);

  AddPushButton(UI_CTRL_RETURN, 180, 85, 42, 42, COLOR_BTN_INFO_NORMAL, COLOR_BTN_INFO_PRESSED, 24, 24, BMP_RETURN);

  AddStateButton(UI_CTRL_F0, 18,  135, 42, 42, COLOR_BTN_NORMAL, COLOR_BTN_WARNING_NORMAL, 24, 24, BMP_LIGHT, false);
  AddStateButton(UI_CTRL_F1, 72,  135, 42, 42, COLOR_BTN_NORMAL, COLOR_BTN_WARNING_NORMAL, "F1", false);
  AddStateButton(UI_CTRL_F2, 126, 135, 42, 42, COLOR_BTN_NORMAL, COLOR_BTN_WARNING_NORMAL, "F2", false);
  AddStateButton(UI_CTRL_F3, 180, 135, 42, 42, COLOR_BTN_NORMAL, COLOR_BTN_WARNING_NORMAL, "F3", false);
   
  AddStateButton(UI_CTRL_F4, 18,  185, 42, 42, COLOR_BTN_NORMAL, COLOR_BTN_WARNING_NORMAL, "F4", false);
  AddStateButton(UI_CTRL_F5, 72,  185, 42, 42, COLOR_BTN_NORMAL, COLOR_BTN_WARNING_NORMAL, "F5", false);
  AddStateButton(UI_CTRL_F6, 126, 185, 42, 42, COLOR_BTN_NORMAL, COLOR_BTN_WARNING_NORMAL, "F6", false);
  AddStateButton(UI_CTRL_F7, 180, 185, 42, 42, COLOR_BTN_NORMAL, COLOR_BTN_WARNING_NORMAL, "F7", false);
   
  // Speed controller
  AddPushButton(UI_CTRL_SPEED_DWN_BIG, 18,  235, 42, 60, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, 24, 24, BMP_FAST_BACKWARD);
  AddPushButton(UI_CTRL_SPEED_DWN,     72,  235, 42, 60, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, 24, 24, BMP_BACK);
  AddPushButton(UI_CTRL_SPEED_UP,      126, 235, 42, 60, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, 24, 24, BMP_FORWARD);
  AddPushButton(UI_CTRL_SPEED_UP_BIG,  180, 235, 42, 60, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, 24, 24, BMP_FAST_FORWARD);
   
  AddStateButton(UI_CTRL_DIR_FWD, 18,  303, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_PRESSED,       24, 24, BMP_DIR_BACK,    true);
  AddStateButton(UI_CTRL_STOP,    72,  303, 92, 42, COLOR_BTN_ERROR_NORMAL, COLOR_BTN_ERROR_PRESSED, 24, 24, BMP_STOP,        false);
  AddStateButton(UI_CTRL_DIR_REV, 180, 303, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_PRESSED,       24, 24, BMP_DIR_FORWARD, false);
   
  // Progress bar
  AddProgressBar(UI_CTRL_PGBAR, 18, 355, 204, 20, 0x3186, 0x02B3, 0x1AAE, 0); // activeEngine.speed);
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void DriveScreen::Shown(void) 
{
  disp.tft.setCursor(20, 90);
  disp.tft.print(scrParamAddress);
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void DriveScreen::Dispatch()
{
  // TODO -> XpressNet library stuff
}

//----------------------------------------------------------------------------------------------------
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
uint8_t DriveScreen::ClickHandler(uint8_t objId) 
{
  Serial.print("DriveScr object handled: "); Serial.println(objId);

  switch (objId)
  {
    case UI_CTRL_RETURN:
      ToggleButtonState(objId);
      return SCR_MENU_ID;
      break; 
      
    case UI_CTRL_F0: 
    case UI_CTRL_F1: 
    case UI_CTRL_F2: 
    case UI_CTRL_F3: 
    case UI_CTRL_F4: 
    case UI_CTRL_F5: 
    case UI_CTRL_F6: 
    case UI_CTRL_F7: 
      Serial.print("Function button clicked. ID="); Serial.println(objId);
      ToggleButtonState(objId);
      break;

    case UI_CTRL_DIR_FWD: 
      break;
      
    case UI_CTRL_DIR_REV: 
      break;
      
    case UI_CTRL_SPEED_UP: 
      break;
      
    case UI_CTRL_SPEED_UP_BIG: 
      break;
      
    case UI_CTRL_SPEED_DWN: 
      break;
      
    case UI_CTRL_SPEED_DWN_BIG: 
      break;
  }

  return UI_OBJECT_NULL;
}
