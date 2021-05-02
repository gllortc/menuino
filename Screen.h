//==============================================
// Screen base class
//----------------------------------------------
// Author:  Gerard Llort Casanova
// Version: 1.1
// Copyright (c) 2021
//==============================================

#ifndef _SCREEN_H 
#define _SCREEN_H 

#include <Arduino.h>
#include "HwdManager.h" 
#include "ScreenObjects.h" 

#define UI_MAX_OBJECTS          20

#define UI_OBJTYPE_CHECK_BUTTON 1
#define UI_OBJTYPE_PUSH_BUTTON  2
#define UI_OBJTYPE_MENU_BUTTON  3
#define UI_OBJTYPE_TEXTBOX      4
#define UI_OBJTYPE_PROGRESSBAR  5
#define UI_OBJTYPE_BITMAP       6

//----------------------------------------------
// Struct storing UI object
//----------------------------------------------
typedef struct 
{
  bool                  initialized    = false;
  bool                  selected       = false;
  byte                  type           = UI_OBJECT_NULL;
  uint16_t              x              = 0;
  uint16_t              y              = 0;
  uint8_t               width          = 0;
  uint8_t               height         = 0;
  bool                  pressed        = false;
  uint16_t              colorPressed   = 0x0000;
  uint16_t              colorUnpressed = 0x0000;
  uint16_t              colorBorder    = 0x0000;
  uint8_t               bmpWidth       = 0;
  uint8_t               bmpHeight      = 0;
  const unsigned char*  bitmap;
  const char*           caption;
  uint16_t              value          = 0;
} UIObject;

class Screen
{
  ScreenParams    params;
  UIObject        uiObjects[UI_MAX_OBJECTS];

public:

  HwdManager      disp;
  uint8_t         id;         // Screen ID
  const char*     caption;    // Screen caption

  // Screen parameters
  uint8_t         scrParamTrack   = 0;
  uint16_t        scrParamAddress = 0;

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  Screen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  virtual void Initialize(HwdManager lcdDisplay, uint8_t scrId, const char* scrCaption);
  virtual void Dispatch();

  // Hardware handlers
  virtual ScreenParams* ClickHandler(uint8_t objId);
  virtual void EncoderClickHandler();
  virtual void EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir);
  virtual void XpnMasterStatusNotifyHandler(uint8_t state);
  virtual void HandleEngineNotify(uint8_t adrHigh, uint8_t adrLow, uint8_t steps, uint8_t speed, uint8_t dir, uint8_t F0, uint8_t F1, uint8_t F2, uint8_t F3);

  // Screen managers
  virtual void Show(ScreenParams *params);
  virtual void Shown(ScreenParams *params);
  uint8_t GetScreenClickedObjectID(int x, int y);
  ScreenParams* GotoScreen(uint8_t scrId, uint16_t addr = 0, uint8_t track = 0, uint8_t inputMode = 0);
  UIObject* GetUIObject(uint8_t objId);

  // UI objects managers
  void SetScreenCaption(const char* newCaption);
  void SetObjectCaption(uint8_t objId, char* newCaption);
  
  void AddPushButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption);
  void AddPushButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, uint16_t bmpWidth, uint16_t bmpHeight, const unsigned char *bitmap);
  void AddStateButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, uint16_t bmpWidth, uint16_t bmpHeight, const unsigned char *bitmap, bool pressed);
  void AddStateButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption, bool pressed);
  void DrawButton(uint8_t id);
  void ToggleButtonState(uint8_t id);
  void SetButtonState(uint8_t id, bool state);
  void SelectButton(uint8_t id);

  void AddMenuButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption);
  void AddMenuButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption, uint16_t bmpWidth, uint16_t bmpHeight, const unsigned char *bitmap);
  void DrawMenuButton(uint8_t id);
  
  void AddTextBox(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colBackground, uint16_t colBorder, const char* text);
  void DrawTextBox(uint8_t id);
  void SetTextBoxText(uint8_t id, const char* text);

  void AddProgressBar(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colBackground, uint16_t colBorder, uint16_t colFill, uint16_t value);
  void DrawProgressBar(uint8_t id);
  void SetProgressBarValue(uint8_t id, uint16_t value);

  void AddBitmap(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, const char* fileName);
  void DrawBitmap(uint8_t id);

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
