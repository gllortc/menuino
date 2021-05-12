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

#define MENU_OPTIONS_COUNT 4

// UI elements ID definition
#define UI_MENU_SELECT    0
#define UI_MENU_MANUAL    1
#define UI_MENU_SETUP     2
#define UI_MENU_INFO      3
#define UI_MENU_IMG_LOGO  4

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
  void InitializeUI() override;
  void Shown(ScreenParams *params) override;
  ScreenParams* ClickHandler(uint8_t objId) override;
  void EncoderClickHandler() override;
  void EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir) override;
  
};

#endif
