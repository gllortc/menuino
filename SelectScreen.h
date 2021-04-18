//==============================================
// Application main menu screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _SELECTSCREEN_H
#define _SELECTSCREEN_H 

#import  <Arduino.h>
#include "Screen.h"

#define MENU_OPTIONS_COUNT 3

#define UI_SELECT_TRACK1 0
#define UI_SELECT_TRACK2 1
#define UI_SELECT_TRACK3 2
#define UI_SELECT_TRACK4 3
#define UI_SELECT_RETURN 4

#define ENCODER_PIN_A   22
#define ENCODER_PIN_B   23

class SelectScreen : public Screen
{
  uint8_t   selIdx;           // Selected menu ID
  long      oldEncPos    = -999;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  SelectScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(TouchDisplay lcdDisplay);
  void Dispatch();
  ScrParameters* ClickHandler(uint8_t objId) override;
  
};

#endif
