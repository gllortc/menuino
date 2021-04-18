//==============================================
// Application adress selection screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _ADDRESSSCREEN_H
#define _ADDRESSSCREEN_H

#import  <Arduino.h>
#include "Screen.h"

#define INPUT_MODE_MANUAL_ADDR  1
#define INPUT_MODE_TRACK_ADDR   2
#define INPUT_MODE_DEVID        3

#define UI_ADDR_0               0
#define UI_ADDR_1               1
#define UI_ADDR_2               2
#define UI_ADDR_3               3
#define UI_ADDR_4               4
#define UI_ADDR_5               5
#define UI_ADDR_6               6
#define UI_ADDR_7               7
#define UI_ADDR_8               8
#define UI_ADDR_9               9
#define UI_ADDR_OK              10
#define UI_ADDR_CANCEL          11
#define UI_ADDR_DEL             12
#define UI_ADDR_TXTBOX          13

#define TXT_DIGITS_MAX          4

class AddressScreen : public Screen
{
  char  txtAddress[TXT_DIGITS_MAX + 1];
  byte  addPos = 0;
  byte  mode   = 0;
  byte  track  = 0;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  AddressScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(TouchDisplay lcdDisplay);
  ScrParameters* ClickHandler(uint8_t objId) override;
  void Shown(ScrParameters *params);

private:

  void DigitPressed(uint8_t objId);
  void DeleteButtonPressed(uint8_t objId);
  ScrParameters* OkButtonPressed(uint8_t objId);
  uint16_t GetNumericAddress();
  void SetAddress(uint16_t addr);
  void ClearAddress();
  
};

#endif
