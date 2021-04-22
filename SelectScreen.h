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
#define UI_ADDR_TRACK1   4
#define UI_ADDR_TRACK2   5
#define UI_ADDR_TRACK3   6
#define UI_ADDR_TRACK4   7
#define UI_SELECT_RETURN 8

class SelectScreen : public Screen
{
  uint8_t selIdx;   // Selected menu ID
  uint8_t selPrev;  // Selected menu ID

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  SelectScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(HwdManager lcdDisplay);
  void Shown(ScrParameters *params) override;
  ScrParameters* ClickHandler(uint8_t objId) override;
  void EncoderHandler(uint8_t dir) override;

private:

  char* GetOptionCaption(uint8_t trackNum);

};

#endif
