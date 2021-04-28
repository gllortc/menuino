//==============================================
// Main menu screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _MENUSCREEN_H 
#define _MENUSCREEN_H 

#include <Arduino.h>
#include "Screen.h"

#define MENU_OPTIONS_COUNT 3

// UI elements ID definition
#define UI_MENU_SELECT  0
#define UI_MENU_MANUAL  1
#define UI_MENU_SETUP   2

class MenuScreen : public Screen
{
  int selIdx  = -1;  // Selected menu ID

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  MenuScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(HwdManager lcdDisplay);
  void Shown(ScreenParams *params) override;
  ScreenParams* ClickHandler(uint8_t objId) override;
  void EncoderClickHandler() override;
  void EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir) override;
  
};

#endif
