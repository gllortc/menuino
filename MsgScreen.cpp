#import <Arduino.h>
#include "MsgScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
MsgScreen::MsgScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void MsgScreen::Initialize(TouchDisplay lcdDisplay)
{
  disp    = lcdDisplay;
  id      = SCR_MESSAGE_ID;
  caption = "INFO";

  AddPushButton(UI_MSG_OK, 80, 280, 80, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "OK");
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void MsgScreen::Dispatch() {}

//----------------------------------------------------------------------------------------------------
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
uint8_t MsgScreen::ClickHandler(uint8_t objId) 
{
  switch (objId)
  {
    case UI_MSG_OK:
      ToggleButtonState(objId);
      return SCR_MENU_ID;

    default:
      return UI_OBJECT_NULL;
  }
}
