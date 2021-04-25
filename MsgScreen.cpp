#include <Arduino.h>
#include "MsgScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
MsgScreen::MsgScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void MsgScreen::Initialize(HwdManager lcdDisplay)
{
  disp    = lcdDisplay;
  id      = SCR_MESSAGE_ID;
  caption = "INFO";

  AddPushButton(UI_MSG_OK, 80, 280, 80, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "OK");
}

//----------------------------------------------------------------------------------------------------
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
ScrParameters* MsgScreen::ClickHandler(uint8_t objId)
{
  switch (objId)
  {
    case UI_MSG_OK:
      ToggleButtonState(objId);
      return GotoScreen(SCR_MENU_ID);

    default:
      return NULL;
  }
}
