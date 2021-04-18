#import <Arduino.h>
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

  AddMenuButton(UI_SELECT_TRACK1, 5,  80, 230, 40, 0x0000, 0x1AAE, "Track 1     E103");
  AddMenuButton(UI_SELECT_TRACK2, 5, 125, 230, 40, 0x0000, 0x1AAE, "Track 2     V221");
  AddMenuButton(UI_SELECT_TRACK3, 5, 170, 230, 40, 0x0000, 0x1AAE, "Track 3     E10");
  AddMenuButton(UI_SELECT_TRACK4, 5, 215, 230, 40, 0x0000, 0x1AAE, "Track 4     E163");
  AddMenuButton(UI_SELECT_RETURN, 5, 260, 230, 40, 0x0000, 0x1AAE, "Back", 24, 24, BMP_RETURN);
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
      return GotoScreen(SCR_DRIVE_ID, 163, 1);
      
    case UI_SELECT_TRACK2: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, 163, 2);
      
    case UI_SELECT_TRACK3: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, 163, 3);
      
    case UI_SELECT_TRACK4: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_DRIVE_ID, 163, 4);
      
    case UI_SELECT_RETURN: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_MENU_ID);

    default:
      return NULL;
  }
}
