#include "Screen.h"
#include "TouchDisplay.h" 
#include "ScreenObjects.h" 

//----------------------------------------------
// Constructors
//----------------------------------------------
Screen::Screen() 
{}

//----------------------------------------------
// Methods
//----------------------------------------------
void Screen::Initialize(TouchDisplay lcdDisplay, uint8_t scrId, const char* scrCaption)
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
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
uint8_t Screen::ClickHandler(uint8_t objId) 
{ 
  Serial.println("ERR: Handling click in base class!");
  return UI_OBJECT_NULL; 
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
            Serial.println("X matches");
            if (y >= uiObjects[i].y && y <= (uiObjects[i].y + uiObjects[i].height))
            {
               Serial.println("Y matches");
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
void Screen::Show(void)
{
  Serial.println("Showing screen...");

  disp.tft.reset();
  disp.DrawBaseScreen(caption);

  for (int i = 0; i < UI_MAX_OBJECTS; ++i)
  {
    if (uiObjects[i].initialized)
    {
      switch (uiObjects[i].type)
      {
        case UI_OBJTYPE_CHECK_BUTTON: 
        case UI_OBJTYPE_PUSH_BUTTON:  DrawButton(&uiObjects[i]);      break;
        case UI_OBJTYPE_MENU_BUTTON:  DrawMenuButton(&uiObjects[i]);  break;
        case UI_OBJTYPE_TEXTBOX:      DrawTextBox(&uiObjects[i]);     break;
        case UI_OBJTYPE_PROGRESSBAR:  DrawProgressBar(&uiObjects[i]); break;
        //case UI_OBJTYPE_BITMAP:       drawBitmap(&uiObjects[i]);    break;
        case UI_OBJTYPE_TRANSAREA:
        default:                                                      break;
      }
    }
  }

  Shown();

  Serial.println("Screen shown!");
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void Screen::Shown(void) {}

//----------------------------------------------------------------------------------------------------
// Change the screen caption
//----------------------------------------------------------------------------------------------------
void Screen::SetScreenCaption(const char* newCaption)
{
   caption = newCaption;
   
   disp.tft.fillRect(0, 21, 180, 50, COLOR_SCR_CAPTION_BACKGROUND);  
   disp.tft.setTextColor(COLOR_SCR_TEXT);
   disp.tft.setTextSize(3);                 
   disp.tft.setCursor(18, 36);
   disp.tft.print(caption);
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
void Screen::DrawButton(UIObject* obj)
{
   // Draw button background
   disp.tft.fillRect(obj->x, obj->y, obj->width, obj->height, (obj->pressed ? obj->colorPressed : obj->colorUnpressed));      
   
   if (obj->bmpWidth == 0 && obj->bmpHeight == 0)
   {
      // Draw caption
      disp.tft.setTextSize(2);
      disp.tft.setTextColor(COLOR_SCR_TEXT);
      disp.tft.setCursor(obj->x + ((obj->width - 20) / 2), obj->y + ((obj->height - 13) / 2));
      disp.tft.print(obj->caption);
   }
   else
   {
      // Draw bitmap
      disp.tft.drawBitmap(obj->x + ((obj->width - obj->bmpWidth) / 2), 
                          obj->y + ((obj->height - obj->bmpHeight) / 2), 
                          obj->bitmap, obj->bmpWidth, obj->bmpHeight, 0xFFFF);
   }
}

//----------------------------------------------
// Draw a menu button object
//----------------------------------------------
void Screen::DrawMenuButton(UIObject* obj)
{
   // Draw button background
   disp.tft.fillRect(obj->x, obj->y, obj->width, obj->height, (obj->pressed ? obj->colorPressed : obj->colorUnpressed));      
   
   if (obj->bmpWidth == 0 && obj->bmpHeight == 0)
   {
      // Draw caption
      disp.tft.setTextSize(2);
      disp.tft.setTextColor(COLOR_SCR_TEXT);
      disp.tft.setCursor(obj->x + 20, obj->y + ((obj->height - 13) / 2));
   }
   else
   {
      // Draw bitmap
      disp.tft.drawBitmap(obj->x + 20, 
                          obj->y + ((obj->height - obj->bmpHeight) / 2), 
                          obj->bitmap, obj->bmpWidth, obj->bmpHeight, 0xFFFF);

      disp.tft.setCursor(obj->x + obj->bmpWidth + 40, obj->y + ((obj->height - 13) / 2));
   }

   disp.tft.print(obj->caption);
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
        DrawButton(&uiObjects[objId]);
        delay(75);
      }
      uiObjects[objId].pressed = false;
      break;

    case UI_OBJTYPE_CHECK_BUTTON:
      uiObjects[objId].pressed = !uiObjects[objId].pressed;
      DrawButton(&uiObjects[objId]);
      break;

    case UI_OBJTYPE_MENU_BUTTON:
      for (uint8_t i = 0; i <= 1; i++)
      {
        uiObjects[objId].pressed = !uiObjects[objId].pressed;   
        DrawMenuButton(&uiObjects[objId]);
        delay(75);
      }
      uiObjects[objId].pressed = false;
      break;
  }
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
void Screen::DrawTextBox(UIObject* obj)
{
   // Draw button background
   disp.tft.fillRect(obj->x, obj->y, obj->width, obj->height, obj->colorUnpressed); 
   disp.tft.drawRect(obj->x, obj->y, obj->width, obj->height, obj->colorPressed);
   disp.tft.setTextColor(COLOR_SCR_TEXT);
   disp.tft.setTextSize(3);
   disp.tft.setCursor(obj->x + 10, obj->y + 10);
   disp.tft.print(obj->caption);
}

//----------------------------------------------------------------------------------------------------
// Sets the text box text
//----------------------------------------------------------------------------------------------------
void Screen::SetTextBoxText(UIObject* obj, const char* text)
{
   obj->caption = text;
   DrawTextBox(obj);
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
void Screen::DrawProgressBar(UIObject* obj)
{
   disp.tft.fillRect(obj->x, obj->y, obj->width, obj->height, obj->colorUnpressed);                           // 0x3186
   disp.tft.fillRect(obj->x, obj->y, map(obj->value, 0, 128, 0, obj->width), obj->height, obj->colorPressed); // 0x1AAE 
   disp.tft.drawRect(obj->x, obj->y, obj->width, obj->height, obj->colorBorder);                              // 0x02B3
}

//----------------------------------------------------------------------------------------------------
// Sets the progress bar value
//----------------------------------------------------------------------------------------------------
void Screen::SetProgressBarValue(UIObject* obj, uint16_t value)
{
   obj->value = value;
   DrawProgressBar(obj);
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
// Draw a progress bar object
//----------------------------------------------
void Screen::DrawBitmap(UIObject* obj)
{
   // Train picture
   disp.tft.fillRect(obj->x, obj->y, obj->width, obj->height, obj->colorUnpressed); 
   disp.tft.drawBitmap(obj->x, obj->y, obj->bitmap, obj->width, obj->height, 0xFFFFFF);
}
