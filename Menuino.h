//==============================================
// MENUINO manager
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _MENUINO_H 
#define _MENUINO_H 

#include <Arduino.h>
#include "HwdManager.h" 
#include "MenuScreen.h" 
#include "SelectScreen.h" 
#include "DriveScreen.h" 
#include "InputScreen.h" 
#include "MsgScreen.h" 
#include "SetupScreen.h" 

class Menuino 
{
  HwdManager     hardware;

  Screen*        scrCurrent;
  MenuScreen*    scrMenu;
  SelectScreen*  scrSelect;
  DriveScreen*   scrDrive;
  InputScreen*   scrInput;
  MsgScreen*     scrMessage;
  SetupScreen*   scrSetup;

  ScreenParams* params;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  Menuino();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize();
  void Dispatch();
  void ShowScreen(ScreenParams* params);
  void HandleScreenClick(uint16_t xpos, uint16_t ypos);
  void HandleEngineNotify(uint8_t adrHigh, uint8_t adrLow, uint8_t steps, uint8_t speed, uint8_t dir, uint8_t F0, uint8_t F1, uint8_t F2, uint8_t F3);
  void HandleMasterStatusNotify(uint8_t status);
  void HandleEncoderMoved(EncoderMenuSwitch::EncoderDirection dir);
  void HandleEncoderClick();
  Screen* GetCurrentScreen();
  
};

#endif
