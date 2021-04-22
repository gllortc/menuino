//==============================================
// Screen base class
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _SCREEN_H 
#define _SCREEN_H 

#import  <Arduino.h>
#include "HwdManager.h" 
#include "ScreenObjects.h" 

#define UI_MAX_OBJECTS          20

#define UI_OBJTYPE_CHECK_BUTTON 1
#define UI_OBJTYPE_PUSH_BUTTON  2
#define UI_OBJTYPE_MENU_BUTTON  3
#define UI_OBJTYPE_TRANSAREA    4
#define UI_OBJTYPE_TEXTBOX      5
#define UI_OBJTYPE_PROGRESSBAR  6
#define UI_OBJTYPE_BITMAP       7

//----------------------------------------------
// Struct storing UI object
//----------------------------------------------
typedef struct 
{
  bool            initialized    = false;
  byte            type           = UI_OBJECT_NULL;
  uint16_t        x              = 0;
  uint16_t        y              = 0;
  uint8_t         width          = 0;
  uint8_t         height         = 0;
  bool            pressed        = false;
  uint16_t        colorPressed   = 0x0000;
  uint16_t        colorUnpressed = 0x0000;
  uint16_t        colorBorder    = 0x0000;
  uint8_t         bmpWidth       = 0;
  uint8_t         bmpHeight      = 0;
  unsigned char  *bitmap;
  const char*     caption;
  uint16_t        value          = 0;
} UIObject;

class Screen
{
  ScrParameters   params;
  UIObject        uiObjects[UI_MAX_OBJECTS];

public:

  HwdManager    disp;
  uint8_t         id;         // Screen ID
  const char*     caption;    // Screen caption

  // Screen parameters
  uint8_t         scrParamTrack   = 0;
  uint16_t        scrParamAddress = 0;

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  virtual Screen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  virtual void Initialize(HwdManager lcdDisplay, uint8_t scrId, const char* scrCaption);
  virtual void Dispatch();
  virtual void Show(ScrParameters *params);
  virtual void Shown(ScrParameters *params);
  virtual ScrParameters* ClickHandler(uint8_t objId);
  virtual void EncoderHandler(uint8_t dir);

  ScrParameters* GotoScreen(uint8_t scrId, uint16_t addr = 0, uint8_t track = 0, uint8_t inputMode = 0);
  UIObject* GetUIObject(uint8_t objId);
  uint8_t GetScreenClickedObjectID(int x, int y);
  void SetScreenCaption(const char* newCaption);
  void SetObjectCaption(uint8_t objId, char* newCaption);
  
  void AddPushButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption);
  void AddPushButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, uint16_t bmpWidth, uint16_t bmpHeight, unsigned char *bitmap);
  void AddStateButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, uint16_t bmpWidth, uint16_t bmpHeight, unsigned char *bitmap, bool pressed);
  void AddStateButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption, bool pressed);
  void DrawButton(UIObject* obj);
  void ToggleButtonState(uint8_t objIdx);

  void AddMenuButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption);
  void AddMenuButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption, uint16_t bmpWidth, uint16_t bmpHeight, unsigned char *bitmap);
  void DrawMenuButton(UIObject* obj);
  
  void AddTextBox(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colBackground, uint16_t colBorder, const char* text);
  void DrawTextBox(UIObject* obj);
  void SetTextBoxText(UIObject* obj, const char* text);

  void AddProgressBar(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colBackground, uint16_t colBorder, uint16_t colFill, uint16_t value);
  void DrawProgressBar(UIObject* obj);
  void SetProgressBarValue(UIObject* obj, uint16_t value);

  void AddBitmap(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t bgColor, const char* fileName);
  void DrawBitmap(UIObject* obj);

  // Settings management
  static uint16_t GetTrackAddress(uint8_t trackNum);
  static void SetTrackAddress(uint8_t track, uint16_t address);
  static uint8_t GetDeviceID();
  static void SetDeviceID(uint8_t id = 25);
  
};

//----------------------------------------------
// Callbacks
//----------------------------------------------
extern void ClickedElement(uint8_t id) __attribute__ ((weak));

#endif
