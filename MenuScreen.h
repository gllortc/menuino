//==============================================
// Application main menu screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _MENUSCREEN_H 
#define _MENUSCREEN_H 

#import  <Arduino.h>
#include "Screen.h"

#define MENU_OPTIONS_COUNT 3

// UI elements ID definition
#define UI_MENU_SELECT  0
#define UI_MENU_MANUAL  1
#define UI_MENU_SETUP   2

// Hardware PINs used
#define ENCODER_PIN_1   22
#define ENCODER_PIN_2   23

class MenuScreen : public Screen
{
  uint8_t   selIdx;           // Selected menu ID
  long      oldEncPos    = -999;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  MenuScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(TouchDisplay lcdDisplay);
  void Dispatch(void);
  uint8_t ClickHandler(uint8_t objId) override;
  
};

//----------------------------------------------
// Callbacks
//----------------------------------------------
extern void ClickedElement(uint8_t id) __attribute__ ((weak));

#endif