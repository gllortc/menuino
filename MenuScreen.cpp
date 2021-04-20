#import  <Arduino.h>
#include <Encoder.h>
#include "MenuScreen.h"
#include "AddressScreen.h"
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
ScrParameters* MenuScreen::ClickHandler(uint8_t objId)
{
  switch (objId)
  {
    case UI_MENU_SELECT:
      ToggleButtonState(objId);
      return GotoScreen(SCR_SELECT_ID);

    case UI_MENU_MANUAL:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, 0, 0, INPUT_MODE_MANUAL_ADDR);

    case UI_MENU_SETUP:
      ToggleButtonState(objId);
      return GotoScreen(SCR_SETUP_ID);

    default:
      return NULL;
  }
}
