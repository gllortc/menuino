#include <Arduino.h>
#include "WaitScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
WaitScreen::WaitScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void WaitScreen::Initialize(HwdManager *hardware)
{
  hdw     = hardware;
  id      = SCR_WAIT_ID;
  caption = "WAIT";

  AddBitmap(UI_WAIT_BMP, (hdw->tft.width() - 36) / 2, (hdw->tft.height() - 36) / 2, 36, 36, COLOR_NAVBAR_WARNING, BMP_WAIT);
  AddPushButton(UI_WAIT_CANCEL, (hdw->tft.width() - 80) / 2, ((hdw->tft.height() - 36) / 2) + 60, 80, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "Cancel");
}

//----------------------------------------------------------------------------------------------------
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
ScreenParams* WaitScreen::ClickHandler(uint8_t objId)
{
  Screen::ClickHandler(objId);

  switch (objId)
  {
    case UI_WAIT_CANCEL:
      return GotoScreen(SCR_MENU_ID);
  }

  return NULL;
}
