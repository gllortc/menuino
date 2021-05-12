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
void InfoScreen::InitializeUI()
{
  id      = SCR_INFO_ID;
  caption = "INFORMATION";
  xpn     = XpnManager::getInstance();

  AddBitmap(UI_INFO_APP_ICON, 17, 90, 22, 30, 0xFF10, BMP_APP_ICON);
  AddLabel(UI_INFO_APP_TITLE, 50, 100, 2, COLOR_SCR_TEXT, "DUAL CONTROL");
  AddLabel(UI_INFO_MASTER, 17, 145, 1, COLOR_SCR_TEXT, "CENTRAL/MASTER");
  AddLabel(UI_INFO_HW_TYPE, 17, 155, 2, COLOR_SCR_TEXT, "");
  AddLabel(UI_INFO_LBL_DEVICE, 17, 180, 1, COLOR_SCR_TEXT, "XPN DEVICE UID (1..31)");
  AddLabel(UI_INFO_TXT_DEVICE, 17, 190, 2, COLOR_SCR_TEXT, "  ");
  AddLabel(UI_INFO_LBL_VER, 17, 215, 1, COLOR_SCR_TEXT, "SOFTWARE VERSION");
  AddLabel(UI_INFO_TXT_VER, 17, 225, 2, COLOR_SCR_TEXT, "v0.1-R");
  AddLabel(UI_INFO_LBL_ABOUT, 17, 250, 1, COLOR_SCR_TEXT, "ABOUT");
  AddLabel(UI_INFO_TXT_ABOUT, 17, 260, 1, COLOR_BTN_WARNING_NORMAL, "Copyright (c) 2021 Railwaymania");
  AddLabel(UI_INFO_TXT_ABOUT2, 17, 270, 1, COLOR_BTN_WARNING_NORMAL, "Gerard llort Casanova");
  AddLine(UI_INFO_APP_ULINE, 17, 127, display->tft.width() - 17, 127, 0xCE9A);
  AddPushButton(UI_INFO_BTN_BACK, (display->tft.width() - 180) / 2, ((display->tft.height() - 36) * 3 / 4) + 60, 180, 40, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "Return");
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void InfoScreen::Shown(ScreenParams *params) 
{
  SetLabelTextValue(UI_INFO_HW_TYPE, xpn->master.type);
  SetLabelIntValue(UI_INFO_TXT_DEVICE, xpn->GetDeviceID());
}

//----------------------------------------------------------------------------------------------------
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
ScreenParams* InfoScreen::ClickHandler(uint8_t objId)
{
  Screen::ClickHandler(objId);

  switch (objId)
  {
    case UI_INFO_BTN_BACK:
      return GotoScreen(SCR_MENU_ID);
  }

  return NULL;
}
