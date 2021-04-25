//==============================================
// Application main menu screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _SCREENMANAGER_H 
#define _SCREENMANAGER_H 

#include <Arduino.h>
#include "HwdManager.h" 
#include "MenuScreen.h" 
#include "SelectScreen.h" 
#include "DriveScreen.h" 
#include "InputScreen.h" 
#include "MsgScreen.h" 
#include "SetupScreen.h" 

class ScreenManager 
{
  HwdManager   scr;

  Screen*        scrCurrent;
  MenuScreen*    scrMenu;
  SelectScreen*  scrSelect;
  DriveScreen*   scrDrive;
  InputScreen*   scrInput;
  MsgScreen*     scrMessage;
  SetupScreen*   scrSetup;

  ScrParameters* params;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  ScreenManager();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize();
  void Dispatch();
  void ShowScreen(ScrParameters* params);
  void HandleScreenClick(uint16_t xpos, uint16_t ypos);
  void HandleEngineNotify(uint8_t adrHigh, uint8_t adrLow, uint8_t steps, uint8_t speed, uint8_t dir, uint8_t F0, uint8_t F1, uint8_t F2, uint8_t F3);
  void HandleMasterStatusNotify(uint8_t status);
  void HandleEncoderMoved(EncoderMenuSwitch::EncoderDirection dir);
  void HandleEncoderClick();
  Screen* GetCurrentScreen();
  
};

#endif
