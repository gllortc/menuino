#import  <Arduino.h>
#include <EEPROM.h>
#include <Encoder.h>
#include "SelectScreen.h"
#include "ScreenObjects.h"
#include <Encoder_Polling.h>

//----------------------------------------------
// Constructor
//----------------------------------------------
SelectScreen::SelectScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void SelectScreen::Initialize(TouchDisplay lcdDisplay)
{
  disp    = lcdDisplay;
  id      = SCR_SELECT_ID;
  caption = "SELECT TRAIN";

  encoder_begin(ENCODER_PIN_A, ENCODER_PIN_B);

  AddMenuButton(UI_SELECT_TRACK1, 5,  80, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "Track 1");
  AddMenuButton(UI_SELECT_TRACK2, 5, 125, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "Track 2");
  AddMenuButton(UI_SELECT_TRACK3, 5, 170, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "Track 3");
  AddMenuButton(UI_SELECT_TRACK4, 5, 215, 150, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "Track 4");
  AddMenuButton(UI_SELECT_RETURN, 5, 260, 230, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "Back", 24, 24, BMP_RETURN);
} 

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void SelectScreen::Shown(ScrParameters *params) 
{
  char     sadr[5];

  disp.tft.setTextSize(2);
  disp.tft.setTextColor(COLOR_SCR_TEXT);

  for (uint8_t i = 0; i < 4; i++)
  {
    itoa(Screen::GetTrackAddress(i + 1), sadr, 10);
    disp.tft.setCursor(170, 92 + (i * 45));
    disp.tft.print(sadr);
  }
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void SelectScreen::Dispatch()
{
  int selPrev = selIdx;
  int dir = encoder_data();

  if(dir == 1)       // Forward
  {
    selIdx--;
    if (selIdx < 0) selIdx = MENU_OPTIONS_COUNT - 1;
  }
  else if(dir == -1) // Backward
  {
    selIdx++;
    if (selIdx >= MENU_OPTIONS_COUNT) selIdx = 0;
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
ScrParameters* SelectScreen::ClickHandler(uint8_t objId)
{
  switch (objId)
  {
    case UI_SELECT_TRACK1: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, Screen::GetTrackAddress(1), 1);
      
    case UI_SELECT_TRACK2: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, Screen::GetTrackAddress(2), 2);
      
    case UI_SELECT_TRACK3: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, Screen::GetTrackAddress(3), 3);
      
    case UI_SELECT_TRACK4: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, Screen::GetTrackAddress(4), 4);
      
    case UI_SELECT_RETURN: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_MENU_ID);

    default:
      return NULL;
  }
}
