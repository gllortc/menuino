//==============================================
// Engine drive screen
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _DRIVESCREEN_H 
#define _DRIVESCREEN_H 

#include <Arduino.h>
#include "Screen.h"

#define SPEED_STEPS_14        0 // Speed steps
#define SPEED_STEPS_28        2
#define SPEED_STEPS_128       3

#define FUNC_OFF              0 // Engine function status
#define FUNC_ON               1
#define FUNC_CHANGE           2

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

//----------------------------------------------
// EEPROM storage
//----------------------------------------------
// byte  |  description
//--------------------------
//  0    |  Device ID
//  1    |  Track 1 addr low byte
//  2    |  Track 1 addr high byte
//  3    |  Track 2 addr low byte
//  4    |  Track 2 addr high byte
//  5    |  Track 3 addr low byte
//  6    |  Track 3 addr high byte
//  7    |  Track 4 addr low byte
//  8    |  Track 4 addr high byte

//----------------------------------------------
// Struct storing engine info
//----------------------------------------------

// Engine functions
union Functions {
  uint8_t Xpress[4];  // array para funciones, F0F4, F5F12, F13F20 y F21F28
  unsigned long Bits; // long para acceder a los bits
};

// Current engine data
typedef struct 
{
  boolean   loaded  = false;
  uint16_t  address = 3;
  uint8_t   steps   = 128;
  uint8_t   speed   = 0;
  uint8_t   direction;
  Functions func;
} Engine;

//----------------------------------------------
// Class declaration
//----------------------------------------------
class DriveScreen : public Screen
{
  bool            controlEnabled  = false;  // Indicate if an engine is controlled
  uint8_t         xpnDeviceID     = 25;     // Store the XPN device ID
  uint8_t         xpnMasterStatus;
  
  Engine          engine;

public:

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  DriveScreen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(HwdManager lcdDisplay);
  void Shown(ScreenParams *params);
  ScreenParams* ClickHandler(uint8_t objId) override;
  void EncoderClickHandler() override;
  void EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir) override;

  // XPN methods
  uint8_t GetCV17AdrHighByte(uint16_t address);
  uint8_t GetCV18AdrLowByte(uint16_t address);
  uint8_t GetSpeedMax(uint8_t steps);
  void GetEngineInfo();
  void GetEngineFuncs();
  void SetEngineSpeed(uint8_t speed);
  void ToggleEngineFunction(uint8_t funcNum);

  void HandleEngineNotify(uint8_t adrHigh, uint8_t adrLow, uint8_t steps, uint8_t speed, uint8_t dir, uint8_t F0, uint8_t F1, uint8_t F2, uint8_t F3);
  void HandleMasterStatusNotify(uint8_t status);
  
};

#endif
