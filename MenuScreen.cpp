#include <Arduino.h>
#include <EncoderMenuSwitch.h>
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
void MenuScreen::InitializeUI()
{
  id      = SCR_MENU_ID;
  caption = LNG_EN_MENU_HEADER;

  AddMenuButton(UI_MENU_SELECT, 5,  80, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_MENU_OPT_SELECT);
  AddMenuButton(UI_MENU_MANUAL, 5, 125, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_MENU_OPT_DRIVE);
  AddMenuButton(UI_MENU_SETUP,  5, 170, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_MENU_OPT_SETUP);
  AddMenuButton(UI_MENU_INFO,   5, 215, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_MENU_OPT_INFO);

  if (CURRENT_TERMINAL == TERMINAL_RIGHT)
    AddBitmap(UI_MENU_IMG_LOGO, display->tft.width() - 80, display->tft.height() - 60, 60, 40, 0xFF10, BMP_APP_LOGO_RIGHT);
  else
    AddBitmap(UI_MENU_IMG_LOGO, 20, display->tft.height() - 60, 60, 40, 0xFF10, BMP_APP_LOGO_LEFT);
}

//----------------------------------------------------------------------------------------------------
// Screen shown event handler
//----------------------------------------------------------------------------------------------------
void MenuScreen::Shown(ScreenParams *params) 
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
    if (OnDisplayClick) OnDisplayClick(obj->x + 1, obj->y + 1);
  }
}

//----------------------------------------------------------------------------------------------------
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
ScreenParams* MenuScreen::ClickHandler(uint8_t objId)
{
  Screen::ClickHandler(objId);
  
  switch (objId)
  {
    case UI_MENU_SELECT:
      return GotoScreen(SCR_SELECT_ID);

    case UI_MENU_MANUAL:
      return GotoScreen(SCR_ADDRESS_ID, 0, 0, INPUT_MODE_MANUAL_ADDR);

    case UI_MENU_SETUP:
      return GotoScreen(SCR_SETUP_ID);

    case UI_MENU_INFO:
      return GotoScreen(SCR_INFO_ID);

    default:
      return NULL;
  }
}
