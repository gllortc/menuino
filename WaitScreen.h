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

#ifndef _WAITSCREEN_H 
#define _WAITSCREEN_H

#include <Arduino.h>
#include "Screen.h"

// UI elements ID definition
#define UI_WAIT_CANCEL  0
#define UI_WAIT_BMP     1

class WaitScreen : public Screen
{

  uint8_t   cancelScrId;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  WaitScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void InitializeUI() override;
  ScreenParams* ClickHandler(uint8_t objId) override;

};

#endif
