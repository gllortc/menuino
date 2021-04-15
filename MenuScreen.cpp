#import <Arduino.h>
#include <Encoder.h>
#include "MenuScreen.h"
#include "ScreenObjects.h"
#include <Encoder_Polling.h>

//----------------------------------------------
// Constructor
//----------------------------------------------
MenuScreen::MenuScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void MenuScreen::Initialize(TouchDisplay lcdDisplay)
{
  disp    = lcdDisplay;
  id      = SCR_MENU_ID;
  caption = "MAIN MENU";

  encoder_begin(ENCODER_PIN_1, ENCODER_PIN_2);

  AddMenuButton(UI_MENU_SELECT, 5,  80, 230, 40, 0x0000, 0x1AAE, "Select train");
  AddMenuButton(UI_MENU_MANUAL, 5, 125, 230, 40, 0x0000, 0x1AAE, "Manual drive");
  AddMenuButton(UI_MENU_SETUP,  5, 170, 230, 40, 0x0000, 0x1AAE, "Settings");
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void MenuScreen::Dispatch()
{
  int selPrev = selIdx;
  int dir = encoder_data();

  if(dir == 1)       // Forward
  {
    selIdx--;
    if (selIdx < 0) selIdx = MENU_OPTIONS_COUNT - 1;
    Serial.println("Menu DOWN");
  }
  else if(dir == -1) // Backward
  {
    selIdx++;
    if (selIdx >= MENU_OPTIONS_COUNT) selIdx = 0;
    Serial.println("Menu UP");
  }

  if (selPrev != selIdx)
  {
    ToggleButtonState(GetUIObject(selPrev));
    ToggleButtonState(GetUIObject(selIdx));
  }
}

//----------------------------------------------------------------------------------------------------
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
void MenuScreen::ClickHandler(uint8_t objId, ScrParameters *returnParams) 
{
  Serial.print("Handling object "); Serial.println(objId);

  switch (objId)
  {
    case UI_MENU_SELECT:
      ToggleButtonState(objId);
      returnParams->gotoScr = SCR_SELECT_ID;
      break;

    case UI_MENU_MANUAL:
      ToggleButtonState(objId);
      returnParams->gotoScr = SCR_ADDRESS_ID;
      break;

    case UI_MENU_SETUP:
      ToggleButtonState(objId);
      returnParams->gotoScr = SCR_MESSAGE_ID;
      break;
  }
}
