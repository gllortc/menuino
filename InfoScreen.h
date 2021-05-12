//==============================================
// Wait screen implementation
//----------------------------------------------
// Input parameters:
// - gotoScr:   Return screen ID in case of cancellation
// - inputMode: 0 = With cancel button
//              1 = Without cancel button
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _INFOSCREEN_H 
#define _INFOSCREEN_H

#include <Arduino.h>
#include "Screen.h"

// UI elements ID definition
#define UI_INFO_APP_ICON   0
#define UI_INFO_APP_TITLE  1
#define UI_INFO_APP_ULINE  2
#define UI_INFO_MASTER     3
#define UI_INFO_HW_TYPE    4
#define UI_INFO_LBL_DEVICE 5
#define UI_INFO_TXT_DEVICE 6
#define UI_INFO_LBL_VER    7
#define UI_INFO_TXT_VER    8
#define UI_INFO_LBL_ABOUT  9
#define UI_INFO_TXT_ABOUT  10
#define UI_INFO_TXT_ABOUT2 11
#define UI_INFO_BTN_BACK   12

class InfoScreen : public Screen
{

  uint8_t     cancelScrId;
  XpnManager* xpn;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  InfoScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void InitializeUI() override;
  void Shown(ScreenParams *params) override;
  ScreenParams* ClickHandler(uint8_t objId) override;

};

#endif
