#include <Arduino.h>
#include "InfoScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
InfoScreen::InfoScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void InfoScreen::Initialize(HwdManager *hardware)
{
  hdw     = hardware;
  id      = SCR_INFO_ID;
  caption = "INFORMATION";

  AddPushButton(UI_INFO_BACK, (hdw->tft.width() - 160) / 2, ((hdw->tft.height() - 36) / 2) + 60, 160, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "Return");
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void InfoScreen::Shown(ScreenParams *params) 
{
  // Update engine information
  hdw->tft.setCursor(1, 85);
  hdw->tft.setTextSize(2);
  hdw->tft.println(F("Master"));
  hdw->tft.setTextSize(1);
  hdw->tft.print("Hardware: "); 
  switch (hdw->xpnMaster.type)
  {
    case 0x00: hdw->tft.println(F("LZV100"));       break;
    case 0x01: hdw->tft.println(F("LH 200"));       break;
    case 0x02: hdw->tft.println(F("DPC"));          break;
    case 0x03: hdw->tft.println(F("Control Plus")); break;
    default:   hdw->tft.println(F("Unknown"));      break;
  }  
  hdw->tft.print("Version : "); hdw->tft.print(hdw->xpnMaster.vermajor); hdw->tft.print(F(".")); hdw->tft.println(hdw->xpnMaster.verminor);
  hdw->tft.setTextSize(2);
  hdw->tft.println(F("Slave"));
  hdw->tft.setTextSize(1);
  hdw->tft.print("XPN ID  : "); hdw->tft.println(hdw->xpnMaster.devId);
  hdw->tft.print("Version : "); hdw->tft.println(F("1.0"));
  hdw->tft.print("Author  : "); hdw->tft.println(F("Gerard Llort Casanova"));
}

//----------------------------------------------------------------------------------------------------
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
ScreenParams* InfoScreen::ClickHandler(uint8_t objId)
{
  Screen::ClickHandler(objId);

  switch (objId)
  {
    case UI_INFO_BACK:
      return GotoScreen(SCR_MENU_ID);
  }

  return NULL;
}
