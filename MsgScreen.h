//==============================================
// Application message screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _MSGCREEN_H 
#define _MSGSCREEN_H 

#import  <Arduino.h>
#include "Screen.h"

// UI elements ID definition
#define UI_MSG_OK  0

class MsgScreen : public Screen
{

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  MsgScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(TouchDisplay lcdDisplay);
  void Dispatch(void);
  uint8_t ClickHandler(uint8_t objId) override;
  
};

#endif
