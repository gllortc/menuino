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
#include <XpnManager.h>
#include "MenuScreen.h" 
#include "SelectScreen.h" 
#include "DriveScreen.h" 
#include "InputScreen.h" 
#include "WaitScreen.h" 
#include "SetupScreen.h" 
#include "InfoScreen.h" 

class Menuino 
{
  OpenSmart32*   display;
  XpnManager*    xpn;

  Screen*        scrCurrent;
  MenuScreen*    scrMenu;
  SelectScreen*  scrSelect;
  DriveScreen*   scrDrive;
  InputScreen*   scrInput;
  WaitScreen*    scrWait;
  SetupScreen*   scrSetup;
  InfoScreen*    scrInfo;

  ScreenParams*  params;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  Menuino();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(OpenSmart32* tft);
  void Dispatch();
  void ShowScreen(ScreenParams* params);
  Screen* GetCurrentScreen();

  //----------------------------------------------
  // Event handlers
  //----------------------------------------------
  void HandleDisplayClick(uint16_t xpos, uint16_t ypos);
  void HandleEngineNotify(XpnEngine *engine);
  void HandleMasterStatusNotify(uint8_t status);
  void HandleEncoderMoved(EncoderMenuSwitch::EncoderDirection dir);
  void HandleEncoderClick();

};

#endif
