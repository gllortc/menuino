#include <EEPROM.h>
#include "Screen.h"
#include "HwdManager.h" 
#include "ScreenObjects.h" 

//----------------------------------------------
// Constructors
//----------------------------------------------
Screen::Screen() {}

//----------------------------------------------
// Methods
//----------------------------------------------
void Screen::Initialize(HwdManager lcdDisplay, uint8_t scrId, const char* scrCaption)
{
  id      = scrId;
  caption = scrCaption;
  disp    = lcdDisplay;
}

//----------------------------------------------------------------------------------------------------
// Dispatch screen events
//----------------------------------------------------------------------------------------------------
void Screen::Dispatch(void)
{
  disp.Dispatch();
}

//----------------------------------------------------------------------------------------------------
// Handle screen clicks
//----------------------------------------------------------------------------------------------------
ScrParameters* Screen::ClickHandler(uint8_t objId)
{ 
  return NULL;
}

//----------------------------------------------------------------------------------------------------
// Handle encoder clicks
//----------------------------------------------------------------------------------------------------
void Screen::EncoderClickHandler() {}

//----------------------------------------------------------------------------------------------------
// Handle encoder movements
//----------------------------------------------------------------------------------------------------
void Screen::EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir) {}

//----------------------------------------------------------------------------------------------------
// Preoare screen parameters to go to another screen
//----------------------------------------------------------------------------------------------------
ScrParameters* Screen::GotoScreen(uint8_t scrId, uint16_t addr, uint8_t track, uint8_t inputMode)
{
  params.gotoScr   = scrId;
  params.trackNum  = track;
  params.address   = addr;
  params.inputMode = inputMode;
  return &params;
}

//----------------------------------------------------------------------------------------------------
// Get an UI object from current screen
//----------------------------------------------------------------------------------------------------
UIObject* Screen::GetUIObject(uint8_t objId)
{
  return &uiObjects[objId];
}

//----------------------------------------------------------------------------------------------------
// Get the clicked object ID in current screen
// NOTE: The ID corresponds to the array index
//----------------------------------------------------------------------------------------------------
uint8_t Screen::GetScreenClickedObjectID(int x, int y)
{
  for (int i = 0; i < UI_MAX_OBJECTS; i++)
  {
    if (uiObjects[i].initialized)
    {
      if (x >= uiObjects[i].x && x <= (uiObjects[i].x + uiObjects[i].width))
      {
        // Serial.println("X matches");
        if (y >= uiObjects[i].y && y <= (uiObjects[i].y + uiObjects[i].height))
        {
          // Serial.println("Y matches");
          return i;
        }
      }
    }
  }
   
  return UI_OBJECT_NULL;
}

//----------------------------------------------------------------------------------------------------
// Paint the screen with its current UI objects states
//----------------------------------------------------------------------------------------------------
void Screen::Show(ScrParameters *params)
{
  // Reset the screen
  disp.tft.reset();
  disp.DrawBaseScreen(caption);

  // Draw all UI objects
  for (int i = 0; i < UI_MAX_OBJECTS; ++i)
  {
    if (uiObjects[i].initialized)
    {
      switch (uiObjects[i].type)
      {
        case UI_OBJTYPE_CHECK_BUTTON: 
        case UI_OBJTYPE_PUSH_BUTTON:  DrawButton(i);      break;
        case UI_OBJTYPE_MENU_BUTTON:  DrawMenuButton(i);  break;
        case UI_OBJTYPE_TEXTBOX:      DrawTextBox(i);     break;
        case UI_OBJTYPE_PROGRESSBAR:  DrawProgressBar(i); break;
        case UI_OBJTYPE_BITMAP:       DrawBitmap(i);      break;
        default:                                          break;
      }
    }
  }

  // Raise the shown event in the screen
  Shown(params);
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void Screen::Shown(ScrParameters *params) {}

//----------------------------------------------------------------------------------------------------
// Change the screen caption
//----------------------------------------------------------------------------------------------------
void Screen::SetScreenCaption(const char* newCaption)
{
  caption = newCaption;

  disp.tft.fillRect(39, 21, 180, 50, COLOR_SCR_CAPTION_BACKGROUND);
  disp.tft.setTextColor(COLOR_SCR_TEXT);
  disp.tft.setTextSize(2);
  disp.tft.setCursor(40, 40);
  disp.tft.print(caption);
}

//----------------------------------------------------------------------------------------------------
// Change an UI object caption without drawing it
//----------------------------------------------------------------------------------------------------
void Screen::SetObjectCaption(uint8_t id, char* newCaption)
{
  uiObjects[id].caption = newCaption;
}

//----------------------------------------------------------------------------------------------------
// Add a check button to the current screen
//----------------------------------------------------------------------------------------------------
void Screen::AddPushButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption)
{
  if (!uiObjects[id].initialized)
  {
    uiObjects[id].initialized    = true;
    uiObjects[id].type           = UI_OBJTYPE_PUSH_BUTTON;
    uiObjects[id].x              = x;
    uiObjects[id].y              = y;
    uiObjects[id].width          = width;
    uiObjects[id].height         = height;
    uiObjects[id].pressed        = false;
    uiObjects[id].colorPressed   = colPress;
    uiObjects[id].colorUnpressed = colNorm;
    uiObjects[id].caption        = caption;
  }
}

//----------------------------------------------------------------------------------------------------
// Add a check button to the current screen
//----------------------------------------------------------------------------------------------------
void Screen::AddPushButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, uint16_t bmpWidth, uint16_t bmpHeight, unsigned char *bitmap)
{
  if (!uiObjects[id].initialized)
  {
    uiObjects[id].initialized    = true;
    uiObjects[id].type           = UI_OBJTYPE_PUSH_BUTTON;
    uiObjects[id].x              = x;
    uiObjects[id].y              = y;
    uiObjects[id].width          = width;
    uiObjects[id].height         = height;
    uiObjects[id].pressed        = false;
    uiObjects[id].colorPressed   = colPress;
    uiObjects[id].colorUnpressed = colNorm;
    uiObjects[id].bmpWidth       = bmpWidth;
    uiObjects[id].bmpHeight      = bmpHeight;
    uiObjects[id].bitmap         = bitmap;
  }
}

//----------------------------------------------------------------------------------------------------
// Add a state button to the current screen
//----------------------------------------------------------------------------------------------------
void Screen::AddStateButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption, bool pressed)
{
  if (!uiObjects[id].initialized)
  {
    uiObjects[id].initialized    = true;
    uiObjects[id].type           = UI_OBJTYPE_CHECK_BUTTON;
    uiObjects[id].x              = x;
    uiObjects[id].y              = y;
    uiObjects[id].width          = width;
    uiObjects[id].height         = height;
    uiObjects[id].pressed        = pressed;
    uiObjects[id].colorPressed   = colPress;
    uiObjects[id].colorUnpressed = colNorm;
    uiObjects[id].caption        = caption;
  }
}

//----------------------------------------------------------------------------------------------------
// Add a state button to the current screen
//----------------------------------------------------------------------------------------------------
void Screen::AddStateButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, uint16_t bmpWidth, uint16_t bmpHeight, unsigned char *bitmap, bool pressed)
{
   if (!uiObjects[id].initialized)
   {
      uiObjects[id].initialized    = true;
      uiObjects[id].type           = UI_OBJTYPE_CHECK_BUTTON;
      uiObjects[id].x              = x;
      uiObjects[id].y              = y;
      uiObjects[id].width          = width;
      uiObjects[id].height         = height;
      uiObjects[id].pressed        = pressed;
      uiObjects[id].colorPressed   = colPress;
      uiObjects[id].colorUnpressed = colNorm;
      uiObjects[id].bmpWidth       = bmpWidth;
      uiObjects[id].bmpHeight      = bmpHeight;
      uiObjects[id].bitmap         = bitmap;
   }
}

//----------------------------------------------------------------------------------------------------
// Adds a menu button to the current screen. Text caption.
//----------------------------------------------------------------------------------------------------
void Screen::AddMenuButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption)
{
   if (!uiObjects[id].initialized)
   {
      uiObjects[id].initialized    = true;
      uiObjects[id].type           = UI_OBJTYPE_MENU_BUTTON;
      uiObjects[id].x              = x;
      uiObjects[id].y              = y;
      uiObjects[id].width          = width;
      uiObjects[id].height         = height;
      uiObjects[id].pressed        = false;
      uiObjects[id].colorPressed   = colPress;
      uiObjects[id].colorUnpressed = colNorm;
      uiObjects[id].caption        = caption;
   }
}

//----------------------------------------------------------------------------------------------------
// Adds a menu button to the current screen. Text and image caption
//----------------------------------------------------------------------------------------------------
void Screen::AddMenuButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption, uint16_t bmpWidth, uint16_t bmpHeight, unsigned char *bitmap)
{
   if (!uiObjects[id].initialized)
   {
      uiObjects[id].initialized    = true;
      uiObjects[id].type           = UI_OBJTYPE_MENU_BUTTON;
      uiObjects[id].x              = x;
      uiObjects[id].y              = y;
      uiObjects[id].width          = width;
      uiObjects[id].height         = height;
      uiObjects[id].pressed        = false;
      uiObjects[id].colorPressed   = colPress;
      uiObjects[id].colorUnpressed = colNorm;
      uiObjects[id].caption        = caption;
      uiObjects[id].bmpWidth       = bmpWidth;
      uiObjects[id].bmpHeight      = bmpHeight;
      uiObjects[id].bitmap         = bitmap;
   }
}

//----------------------------------------------
// Draw a button object
//----------------------------------------------
void Screen::DrawButton(uint8_t id)
{
   // Draw button background
   disp.tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, (uiObjects[id].pressed ? uiObjects[id].colorPressed : uiObjects[id].colorUnpressed));      
   
   if (uiObjects[id].bmpWidth == 0 && uiObjects[id].bmpHeight == 0)
   {
      // Draw caption
      disp.tft.setTextSize(2);
      disp.tft.setTextColor(COLOR_SCR_TEXT);
      disp.tft.setCursor(uiObjects[id].x + ((uiObjects[id].width - 20) / 2), uiObjects[id].y + ((uiObjects[id].height - 13) / 2));
      disp.tft.print(uiObjects[id].caption);
   }
   else
   {
      // Draw bitmap
      disp.tft.drawBitmap(uiObjects[id].x + ((uiObjects[id].width - uiObjects[id].bmpWidth) / 2), 
                          uiObjects[id].y + ((uiObjects[id].height - uiObjects[id].bmpHeight) / 2), 
                          uiObjects[id].bitmap, uiObjects[id].bmpWidth, uiObjects[id].bmpHeight, COLOR_SCR_TEXT);
   }
}

//----------------------------------------------
// Draw a menu button object
//----------------------------------------------
void Screen::DrawMenuButton(uint8_t id)
{
   // Draw button background
   disp.tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, (uiObjects[id].pressed ? uiObjects[id].colorPressed : uiObjects[id].colorUnpressed));      
   
   if (uiObjects[id].bmpWidth == 0 && uiObjects[id].bmpHeight == 0)
   {
      // Draw caption
      disp.tft.setTextSize(2);
      disp.tft.setTextColor(COLOR_SCR_TEXT);
      disp.tft.setCursor(uiObjects[id].x + 20, uiObjects[id].y + ((uiObjects[id].height - 13) / 2));
   }
   else
   {
      // Draw bitmap
      disp.tft.drawBitmap(uiObjects[id].x + 20, 
                          uiObjects[id].y + ((uiObjects[id].height - uiObjects[id].bmpHeight) / 2), 
                          uiObjects[id].bitmap, uiObjects[id].bmpWidth, uiObjects[id].bmpHeight, COLOR_SCR_TEXT);

      disp.tft.setCursor(uiObjects[id].x + uiObjects[id].bmpWidth + 40, uiObjects[id].y + ((uiObjects[id].height - 13) / 2));
   }

   disp.tft.print(uiObjects[id].caption);
}

//----------------------------------------------------------------------------------------------------
// Toggle push button state and returns to the unpressed position
//----------------------------------------------------------------------------------------------------
void Screen::ToggleButtonState(uint8_t objId)
{
  switch (uiObjects[objId].type)
  {
    case UI_OBJTYPE_PUSH_BUTTON:
      for (uint8_t i = 0; i <= 1; i++)
      {
        uiObjects[objId].pressed = !uiObjects[objId].pressed;
        DrawButton(objId);
        delay(75);
      }
      uiObjects[objId].pressed = false;
      break;

    case UI_OBJTYPE_CHECK_BUTTON:
      uiObjects[objId].pressed = !uiObjects[objId].pressed;
      DrawButton(objId);
      break;

    case UI_OBJTYPE_MENU_BUTTON:
      for (uint8_t i = 0; i <= 1; i++)
      {
        uiObjects[objId].pressed = !uiObjects[objId].pressed;   
        DrawMenuButton(objId);
        delay(75);
      }
      uiObjects[objId].pressed = false;
      break;
  }
}

//----------------------------------------------------------------------------------------------------
// Toggle button selection state
//----------------------------------------------------------------------------------------------------
void Screen::SelectButton(uint8_t objId)
{
  Serial.println("btn sel toggle");

  for (int i = 0; i < UI_MAX_OBJECTS; i++)
  {
    if (uiObjects[i].type == UI_OBJTYPE_MENU_BUTTON && uiObjects[i].selected)
      disp.tft.drawRect(uiObjects[i].x, uiObjects[i].y, uiObjects[i].width, uiObjects[i].height, uiObjects[i].colorUnpressed);

    uiObjects[i].selected = false;
  }

  uiObjects[objId].selected = true;
  disp.tft.drawRect(uiObjects[objId].x, uiObjects[objId].y, uiObjects[objId].width, uiObjects[objId].height, COLOR_BTN_SELECTED);
}

//----------------------------------------------------------------------------------------------------
// Add a text box to the current screen
//----------------------------------------------------------------------------------------------------
void Screen::AddTextBox(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colBackground, uint16_t colBorder, const char* text)
{
   if (!uiObjects[id].initialized)
   {
      uiObjects[id].initialized    = true;
      uiObjects[id].type           = UI_OBJTYPE_PUSH_BUTTON;
      uiObjects[id].x              = x;
      uiObjects[id].y              = y;
      uiObjects[id].width          = width;
      uiObjects[id].height         = height;
      uiObjects[id].pressed        = false;
      uiObjects[id].colorPressed   = colBorder;
      uiObjects[id].colorUnpressed = colBackground;
      uiObjects[id].caption        = text;
   }
}

//----------------------------------------------
// Draw a text box object
//----------------------------------------------
void Screen::DrawTextBox(uint8_t id)
{
   // Draw button background
   disp.tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorUnpressed); 
   disp.tft.drawRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorPressed);
   disp.tft.setTextColor(COLOR_SCR_TEXT);
   disp.tft.setTextSize(3);
   disp.tft.setCursor(uiObjects[id].x + 10, uiObjects[id].y + 10);
   disp.tft.print(uiObjects[id].caption);
}

//----------------------------------------------------------------------------------------------------
// Sets the text box text
//----------------------------------------------------------------------------------------------------
void Screen::SetTextBoxText(uint8_t id, const char* text)
{
   uiObjects[id].caption = text;
   DrawTextBox(id);
}

//----------------------------------------------------------------------------------------------------
// Add a progress bar to the current screen
//----------------------------------------------------------------------------------------------------
void Screen::AddProgressBar(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colBackground, uint16_t colBorder, uint16_t colFill, uint16_t value)
{
   // If not registered, register the button
   if (!uiObjects[id].initialized)
   {
      uiObjects[id].initialized    = true;
      uiObjects[id].type           = UI_OBJTYPE_PROGRESSBAR;
      uiObjects[id].x              = x;
      uiObjects[id].y              = y;
      uiObjects[id].width          = width;
      uiObjects[id].height         = height;
      uiObjects[id].pressed        = false;
      uiObjects[id].colorPressed   = colFill;
      uiObjects[id].colorUnpressed = colBackground;
      uiObjects[id].colorBorder    = colBorder;
      uiObjects[id].value          = value;
   }
}

//----------------------------------------------
// Draw a progress bar object
//----------------------------------------------
void Screen::DrawProgressBar(uint8_t id)
{
   disp.tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorUnpressed);
   disp.tft.fillRect(uiObjects[id].x, uiObjects[id].y, map(uiObjects[id].value, 0, 128, 0, uiObjects[id].width), uiObjects[id].height, uiObjects[id].colorPressed);
   disp.tft.drawRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorBorder);
}

//----------------------------------------------------------------------------------------------------
// Sets the progress bar value
//----------------------------------------------------------------------------------------------------
void Screen::SetProgressBarValue(uint8_t id, uint16_t value)
{
   uiObjects[id].value = value;
   DrawProgressBar(id);
}

//----------------------------------------------------------------------------------------------------
// Add a check button to the current screen
//----------------------------------------------------------------------------------------------------
void Screen::AddBitmap(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t bgColor, const char* fileName)
{
   if (!uiObjects[id].initialized)
   {
      uiObjects[id].initialized    = true;
      uiObjects[id].type           = UI_OBJTYPE_BITMAP;
      uiObjects[id].x              = x;
      uiObjects[id].y              = y;
      uiObjects[id].width          = width;
      uiObjects[id].height         = height;
      uiObjects[id].pressed        = false;
      uiObjects[id].colorUnpressed = bgColor;
      uiObjects[id].caption        = fileName;
   }
}

//----------------------------------------------
// Draw a monochrome bitmap object
//----------------------------------------------
void Screen::DrawBitmap(uint8_t id)
{
   disp.tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorUnpressed); 
   disp.tft.drawBitmap(uiObjects[id].x, uiObjects[id].y, uiObjects[id].bitmap, uiObjects[id].width, uiObjects[id].height, COLOR_SCR_TEXT);
}

//----------------------------------------------------------------------------------------------------
// App Settings -> Gets the associated digital address from the EEPROM for the specified track number
//----------------------------------------------------------------------------------------------------
uint16_t Screen::GetTrackAddress(uint8_t trackNum)
{
  return (EEPROM.read(((trackNum - 1) * 2) + 1) << 8) + EEPROM.read(((trackNum - 1) * 2) + 2);
}

//----------------------------------------------------------------------------------------------------
// App Settings -> Sets the associated digital address to a track number in the EEPROM
//----------------------------------------------------------------------------------------------------
void Screen::SetTrackAddress(uint8_t track, uint16_t address)
{
  EEPROM.write(((track - 1) * 2) + 1, highByte(address));
  EEPROM.write(((track - 1) * 2) + 2, lowByte(address));
}

//----------------------------------------------------------------------------------------------------
// App Settings -> Gets the XPN digital ID from the EEPROM (default value: 25)
//----------------------------------------------------------------------------------------------------
uint8_t Screen::GetDeviceID()
{
  uint8_t xpnDeviceID = EEPROM.read(0);
  if (xpnDeviceID <= 0 || xpnDeviceID > 31) xpnDeviceID = 25;
  return xpnDeviceID;
}

//----------------------------------------------------------------------------------------------------
// App Settings -> Sets the XPN device ID in the EEPROM
//----------------------------------------------------------------------------------------------------
void Screen::SetDeviceID(uint8_t id = 25)
{
  EEPROM.write(0, id);
}
