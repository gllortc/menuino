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
#define UI_INFO_BACK  0

class InfoScreen : public Screen
{

  uint8_t   cancelScrId;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  InfoScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(HwdManager* hardware);
  void Shown(ScreenParams *params) override;
  ScreenParams* ClickHandler(uint8_t objId) override;

};

#endif
