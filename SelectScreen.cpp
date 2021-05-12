#include <Arduino.h>
#include <EEPROM.h>
#include "SelectScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
SelectScreen::SelectScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void SelectScreen::InitializeUI()
{
  id      = SCR_SELECT_ID;
  caption = LNG_EN_SELECT_HEADER;

  AddMenuButton(UI_SELECT_TRACK1, 5,  80, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SELECT_OPT_TRACK_1);
  AddMenuButton(UI_SELECT_TRACK2, 5, 125, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SELECT_OPT_TRACK_2);
  AddMenuButton(UI_SELECT_TRACK3, 5, 170, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SELECT_OPT_TRACK_3);
  AddMenuButton(UI_SELECT_TRACK4, 5, 215, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SELECT_OPT_TRACK_4);
  AddMenuButton(UI_SELECT_RETURN, 5, 260, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, LNG_EN_SELECT_OPT_BACK, 24, 24, BMP_RETURN);
} 

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void SelectScreen::Shown(ScreenParams *params) 
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

  selIdx = -1;
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void SelectScreen::EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir)
{
  switch (dir)
  {
    case EncoderMenuSwitch::ENCODER_UP:
      selIdx++;
      if (selIdx >= SELECT_OPTIONS_COUNT) selIdx = 0;
      break;

    case EncoderMenuSwitch::ENCODER_DOWN:
      selIdx--;
      if (selIdx < 0) selIdx = SELECT_OPTIONS_COUNT - 1;
      break;
  }

  if (selIdx >= 0)
    SelectButton(selIdx);
}

//----------------------------------------------
// Dispatch encoder clicks
//----------------------------------------------
void SelectScreen::EncoderClickHandler() 
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
ScreenParams* SelectScreen::ClickHandler(uint8_t objId)
{
  switch (objId)
  {
    case UI_SELECT_TRACK1: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, XpnManager::GetTrackAddress(1), 1);
      
    case UI_SELECT_TRACK2: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, XpnManager::GetTrackAddress(2), 2);
      
    case UI_SELECT_TRACK3: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, XpnManager::GetTrackAddress(3), 3);
      
    case UI_SELECT_TRACK4: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, XpnManager::GetTrackAddress(4), 4);
      
    case UI_SELECT_RETURN: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_MENU_ID);

    default:
      return NULL;
  }
}
