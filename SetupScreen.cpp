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
void SetupScreen::Initialize(HwdManager lcdDisplay)
{
  disp    = lcdDisplay;
  id      = SCR_SETUP_ID;
  caption = LNG_EN_SETUP_HEADER;

  AddMenuButton(UI_SETUP_ADR1,   5,  80, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_TRACK_1);
  AddMenuButton(UI_SETUP_ADR2,   5, 125, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_TRACK_2);
  AddMenuButton(UI_SETUP_ADR3,   5, 170, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_TRACK_3);
  AddMenuButton(UI_SETUP_ADR4,   5, 215, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_TRACK_4);
  AddMenuButton(UI_SETUP_DEVID,  5, 260, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_DEVICEID);
  AddMenuButton(UI_SETUP_RETURN, 5, 305, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SETUP_OPT_BACK, 24, 24, BMP_RETURN);
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void SetupScreen::Shown(ScrParameters *params) 
{
  char sadr[5];

  disp.tft.setTextSize(2);
  disp.tft.setTextColor(COLOR_SCR_TEXT);

  for (uint8_t i = 0; i < 4; i++)
  {
    itoa(Screen::GetTrackAddress(i + 1), sadr, 10);
    disp.tft.setCursor(170, 92 + (i * 45));
    disp.tft.print(sadr);
  }

  itoa(Screen::GetDeviceID(), sadr, 10);
  disp.tft.setCursor(170, 272);
  disp.tft.print(sadr);

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
void SetupScreen::EncoderClickHandler() 
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
ScrParameters* SetupScreen::ClickHandler(uint8_t objId) 
{
  switch (objId)
  {
    case UI_SETUP_DEVID:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, Screen::GetDeviceID(), 0, INPUT_MODE_DEVID);

    case UI_SETUP_ADR1:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, Screen::GetTrackAddress(1), 1, INPUT_MODE_TRACK_ADDR);

    case UI_SETUP_ADR2:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, Screen::GetTrackAddress(2), 2, INPUT_MODE_TRACK_ADDR);

    case UI_SETUP_ADR3:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, Screen::GetTrackAddress(3), 3, INPUT_MODE_TRACK_ADDR);

    case UI_SETUP_ADR4:
      ToggleButtonState(objId);
      return GotoScreen(SCR_ADDRESS_ID, Screen::GetTrackAddress(4), 4, INPUT_MODE_TRACK_ADDR);

    case UI_SETUP_RETURN:
      ToggleButtonState(objId);
      return GotoScreen(SCR_MENU_ID);

    default:
      return NULL;
  }
}
