#include <Arduino.h>
#include "InputScreen.h"
#include "SetupScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
SetupScreen::SetupScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void SetupScreen::InitializeUI()
{
  id      = SCR_SETUP_ID;
  caption = LNG_EN_SETUP_HEADER;

  AddMenuButton(UI_SETUP_ADR1,   5,  80, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_TRACK_1);
  AddMenuButton(UI_SETUP_ADR2,   5, 125, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_TRACK_2);
  AddMenuButton(UI_SETUP_ADR3,   5, 170, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_TRACK_3);
  AddMenuButton(UI_SETUP_ADR4,   5, 215, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_TRACK_4);
  AddMenuButton(UI_SETUP_DEVID,  5, 260, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_DEVICEID);
  AddMenuButton(UI_SETUP_RETURN, 5, 305, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_BACK, 24, 24, BMP_RETURN);

  xpn = XpnManager::getInstance();
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void SetupScreen::Shown(ScreenParams *params) 
{
  char sadr[5];

  display->tft.setTextSize(2);
  display->tft.setTextColor(COLOR_SCR_TEXT);

  for (uint8_t i = 0; i < 4; i++)
  {
    itoa(XpnManager::GetTrackAddress(i + 1), sadr, 10);
    display->tft.setCursor(170, 92 + (i * 45));
    display->tft.print(sadr);
  }

  itoa(XpnManager::GetDeviceID(), sadr, 10);
  display->tft.setCursor(170, 272);
  display->tft.print(sadr);

  selIdx = -1;
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void SetupScreen::EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir)
{
  switch (dir)
  {
    case EncoderMenuSwitch::ENCODER_UP:
      selIdx++;
      if (selIdx >= SETUP_OPTIONS_COUNT) selIdx = 0;
      break;

    case EncoderMenuSwitch::ENCODER_DOWN:
      selIdx--;
      if (selIdx < 0) selIdx = SETUP_OPTIONS_COUNT - 1;
      break;
  }

  if (selIdx >= 0)
    SelectButton(selIdx);
}

//----------------------------------------------
// Dispatch encoder clicks
//----------------------------------------------
void SetupScreen::EncoderClickHandler() 
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
ScreenParams* SetupScreen::ClickHandler(uint8_t objId) 
{
  switch (objId)
  {
    case UI_SETUP_DEVID:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, XpnManager::GetDeviceID(), 0, INPUT_MODE_DEVID);

    case UI_SETUP_ADR1:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, XpnManager::GetTrackAddress(1), 1, INPUT_MODE_TRACK_ADDR);

    case UI_SETUP_ADR2:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, XpnManager::GetTrackAddress(2), 2, INPUT_MODE_TRACK_ADDR);

    case UI_SETUP_ADR3:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, XpnManager::GetTrackAddress(3), 3, INPUT_MODE_TRACK_ADDR);

    case UI_SETUP_ADR4:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, XpnManager::GetTrackAddress(4), 4, INPUT_MODE_TRACK_ADDR);

    case UI_SETUP_RETURN:
      ToggleButtonState(objId);
      return GotoScreen(SCR_MENU_ID);

    default:
      return NULL;
  }
}
