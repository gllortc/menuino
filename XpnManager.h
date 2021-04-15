//==============================================
// Application main menu screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _XPNMANAGER_H
#define _XPNMANAGER_H

#import  <Arduino.h>

class XpnManager 
{

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  XpnManager();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(void);
  void Dispatch(void);
  
};

#endif
