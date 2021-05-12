//==============================================
// Application main menu screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _SETUPSCREEN_H 
#define _SETUPSCREEN_H 

#include <Arduino.h>
#include "Screen.h"

#define SETUP_OPTIONS_COUNT 6

// UI elements ID definition
#define UI_SETUP_ADR1       0
#define UI_SETUP_ADR2       1
#define UI_SETUP_ADR3       2
#define UI_SETUP_ADR4       3
#define UI_SETUP_DEVID      4
#define UI_SETUP_RETURN     5

class SetupScreen : public Screen
{
  uint8_t     selIdx = -1;   // Selected menu ID
  XpnManager* xpn;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  SetupScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void InitializeUI() override;
  void Shown(ScreenParams *params) override;
  ScreenParams* ClickHandler(uint8_t objId) override;
  void EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir) override;
  void EncoderClickHandler() override;
  
};

#endif
