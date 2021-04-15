//==============================================
// Application main menu screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _DRIVESCREEN_H 
#define _DRIVESCREEN_H 

#import  <Arduino.h>
#include "Screen.h"

#define UI_CTRL_F0            0
#define UI_CTRL_F1            1
#define UI_CTRL_F2            2
#define UI_CTRL_F3            3
#define UI_CTRL_F4            4
#define UI_CTRL_F5            5
#define UI_CTRL_F6            6
#define UI_CTRL_F7            7
#define UI_CTRL_DIR_FWD       8
#define UI_CTRL_DIR_REV       9
#define UI_CTRL_RETURN        10
#define UI_CTRL_SPEED_UP      11
#define UI_CTRL_SPEED_UP_BIG  12
#define UI_CTRL_SPEED_DWN     13
#define UI_CTRL_SPEED_DWN_BIG 14
#define UI_CTRL_STOP          15
#define UI_CTRL_PGBAR         16

#define ENCODER_PIN_1   22
#define ENCODER_PIN_2   23

class DriveScreen : public Screen
{
  uint8_t   selIdx;           // Selected menu ID
  long      oldEncPos    = -999;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  DriveScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(TouchDisplay lcdDisplay);
  void Dispatch(void);
  void Shown(ScrParameters *params) ;
  void ClickHandler(uint8_t objId, ScrParameters *params) override;
  
};

//----------------------------------------------
// Callbacks
//----------------------------------------------
extern void ClickedElement(uint8_t id) __attribute__ ((weak));

#endif
