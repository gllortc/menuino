//==============================================
// Application main menu screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _SCREENMANAGER_H 
#define _SCREENMANAGER_H 

#import  <Arduino.h>
#include "TouchDisplay.h" 
#include "MenuScreen.h" 
#include "SelectScreen.h" 
#include "DriveScreen.h" 
#include "AddressScreen.h" 
#include "MsgScreen.h" 

class ScreenManager 
{
  TouchDisplay   scr;

  Screen*        scrCurrent;
  MenuScreen*    scrMenu;
  SelectScreen*  scrSelect;
  DriveScreen*   scrDrive;
  AddressScreen* scrAddress;
  MsgScreen*     srcMessage;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  ScreenManager();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(void);
  void Dispatch(void);
  void ShowScreen(uint8_t scrId);
  void HandleScreenClick(uint16_t xpos, uint16_t ypos);
  Screen* GetCurrentScreen(void);
  
};

#endif
