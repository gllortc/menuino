//==============================================
// TFT TouchScreen controller
// for OPEN-SMART TFT shield
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _HWDMANAGER_H 
#define _HWDMANAGER_H 

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <EncoderMenuSwitch.h>
#include <TouchScreen.h>

// Hardware PINs used
#define ENCODER_PIN_1   25
#define ENCODER_PIN_2   27
#define ENCODER_PIN_SW  29

//------------------------------------------------------------------
// Touchscreen management
//------------------------------------------------------------------

class HwdManager
{
  // most mcufriend shields use these pins and Portrait mode:
  uint8_t       YP = A1;  // must be an analog pin, use "An" notation!
  uint8_t       XM = A2;  // must be an analog pin, use "An" notation!
  uint8_t       YM = 7;   // can be a digital pin
  uint8_t       XP = 6;   // can be a digital pin
  uint8_t       SwapXY = 0;

  // Calibration values
  uint16_t      TS_LEFT = 880;
  uint16_t      TS_RT   = 170;
  uint16_t      TS_TOP  = 950;
  uint16_t      TS_BOT  = 180;

  // Orientation
  uint8_t       Orientation = 2;    //LANDSCAPE
  
  TouchScreen   ts = TouchScreen(XP, YP, XM, YM, 260);
  TSPoint       tp;
  
  #define MINPRESSURE 200
  #define MAXPRESSURE 1000
  #define SWAP(a, b) { uint16_t tmp = a; a = b; b = tmp; }

public:

  //EncoderMenuSwitch encoder;
  MCUFRIEND_kbv     tft;

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  HwdManager();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize();
  void Dispatch();
  void DrawBaseScreen(const char* caption);
  void PrintTextLine(const char *text);
  void PrintErrTextLine(const char *text);

};

//----------------------------------------------
// Callbacks
//----------------------------------------------
extern void OnClick(uint16_t xpos, uint16_t ypos) __attribute__ ((weak));
extern void OnEncoderMoved(uint8_t dir) __attribute__ ((weak));

#endif
