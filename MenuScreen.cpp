#include <Arduino.h>
#include "MenuScreen.h"
#include "InputScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
MenuScreen::MenuScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void MenuScreen::Initialize(HwdManager lcdDisplay)
{
  disp    = lcdDisplay;
  id      = SCR_MENU_ID;
  caption = LNG_EN_MENU_HEADER;

  AddMenuButton(UI_MENU_SELECT, 5,  80, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_MENU_OPT_SELECT);
  AddMenuButton(UI_MENU_MANUAL, 5, 125, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_MENU_OPT_DRIVE);
  AddMenuButton(UI_MENU_SETUP,  5, 170, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_MENU_OPT_SETUP);
}

//----------------------------------------------------------------------------------------------------
// Screen shown event handler
//----------------------------------------------------------------------------------------------------
void MenuScreen::Shown(ScrParameters *params) 
{
  selIdx  = -1;
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void MenuScreen::EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir)
{
  switch (dir)
  {
    case EncoderMenuSwitch::ENCODER_UP:
      selIdx++;
      if (selIdx >= MENU_OPTIONS_COUNT) selIdx = 0;
      break;

    case EncoderMenuSwitch::ENCODER_DOWN:
      selIdx--;
      if (selIdx < 0) selIdx = MENU_OPTIONS_COUNT - 1;
      break;
  }

  if (selIdx >= 0)
    SelectButton(selIdx);
}

//----------------------------------------------
// Dispatch encoder clicks
//----------------------------------------------
void MenuScreen::EncoderClickHandler() 
{
  if (selIdx >= 0)
  {
    UIObject* obj = GetUIObject(selIdx);
    if (OnClick) OnClick(obj->x + 1, obj->y + 1);
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
