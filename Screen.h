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
#include <OpenSmart32.h>
#include <EncoderMenuSwitch.h>
#include <XpnManager.h>
#include "ScreenObjects.h" 

#define UI_MAX_OBJECTS          20

#define UI_OBJTYPE_CHECK_BUTTON 1
#define UI_OBJTYPE_PUSH_BUTTON  2
#define UI_OBJTYPE_MENU_BUTTON  3
#define UI_OBJTYPE_TEXT_LABEL   4
#define UI_OBJTYPE_TEXTBOX      5
#define UI_OBJTYPE_PROGRESSBAR  6
#define UI_OBJTYPE_BITMAP       7
#define UI_OBJTYPE_LINE         8

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

//----------------------------------------------
// Screen calling parameters
//----------------------------------------------
typedef struct 
{
  uint8_t  gotoScr   = UI_OBJECT_NULL; // MANDATORY
  uint8_t  inputMode = 0;
  uint8_t  trackNum  = 0;              // app defined
  uint16_t address   = 0;              // app defined
} ScreenParams;

//----------------------------------------------
// Screen class
//----------------------------------------------
class Screen
{
  ScreenParams    params;
  UIObject        uiObjects[UI_MAX_OBJECTS];

public:

  OpenSmart32*    display;
  uint8_t         id;         // Screen ID
  const char*     caption;    // Screen caption

  //----------------------------------------------
  // Constructors
  //----------------------------------------------
  Screen();

  //----------------------------------------------
  // Methods
  //----------------------------------------------
  void Initialize(OpenSmart32* tft);
  virtual void InitializeUI();

  // Hardware handlers
  virtual ScreenParams* ClickHandler(uint8_t objId);
  virtual void EncoderClickHandler();
  virtual void EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir);
  virtual void HandleEngineNotify(XpnEngine *engine);

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

  void AddLabel(uint8_t id, uint16_t x, uint16_t y, uint8_t size, uint16_t color, const char* text);
  void DrawLabel(uint8_t id);
  void SetLabelTextValue(uint8_t id, const char* text);
  void SetLabelIntValue(uint8_t id, uint16_t value);
  
  void AddTextBox(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colBackground, uint16_t colBorder, const char* text);
  void DrawTextBox(uint8_t id);
  void SetTextBoxText(uint8_t id, const char* text);

  void AddProgressBar(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colBackground, uint16_t colBorder, uint16_t colFill, uint16_t value);
  void DrawProgressBar(uint8_t id);
  void SetProgressBarValue(uint8_t id, uint16_t value);

  void AddBitmap(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, const unsigned char *bitmap);
  void DrawBitmap(uint8_t id);

  void AddLine(uint8_t id, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
  void DrawLine(uint8_t id);

  void DrawBaseScreen(const char* caption, bool resetNotifyBar = true);
  void DrawNotifyIcon(uint8_t index, uint16_t color, const unsigned char *bitmap);
  void PrintNotifyText(const char *text, uint16_t color = COLOR_SCR_TEXT);
  void PrintTextLine(const char *text);
  void PrintErrTextLine(const char *text);

  // Settings management
  static uint16_t GetTrackAddress(uint8_t trackNum);
  static void SetTrackAddress(uint8_t track, uint16_t address);
  static uint8_t GetDeviceID();
  static void SetDeviceID(uint8_t id = 25);
  
};

#endif
