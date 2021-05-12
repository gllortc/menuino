#include "Screen.h"
#include "ScreenObjects.h" 

//----------------------------------------------
// Constructors
//----------------------------------------------
Screen::Screen() {}

//----------------------------------------------
// Methods
//----------------------------------------------
void Screen::Initialize(OpenSmart32* tft) //, uint8_t scrId, const char* scrCaption)
{
  display = tft;
  InitializeUI();
}

//----------------------------------------------
// Initialize the UI objects
//----------------------------------------------
void Screen::InitializeUI() {}

//----------------------------------------------------------------------------------------------------
// Dispatch screen events
//----------------------------------------------------------------------------------------------------
//void Screen::Dispatch(void)
//{
//  display->CheckTouch();
//}

//----------------------------------------------------------------------------------------------------
// Handle screen clicks
//----------------------------------------------------------------------------------------------------
ScreenParams* Screen::ClickHandler(uint8_t objId)
{ 
  // Toggle push buttons
  if (uiObjects[objId].type == UI_OBJTYPE_PUSH_BUTTON || uiObjects[objId].type == UI_OBJTYPE_MENU_BUTTON)
    ToggleButtonState(objId);
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
// Handle engine notifications
//----------------------------------------------------------------------------------------------------
void Screen::HandleEngineNotify(XpnEngine *engine) {}

//----------------------------------------------------------------------------------------------------
// Preoare screen parameters to go to another screen
//----------------------------------------------------------------------------------------------------
ScreenParams* Screen::GotoScreen(uint8_t scrId, uint16_t addr, uint8_t track, uint8_t inputMode)
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
void Screen::Show(ScreenParams *params)
{
  // Reset the screen
  display->tft.reset();
  DrawBaseScreen(caption, false);

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
        case UI_OBJTYPE_TEXT_LABEL:   DrawLabel(i);       break;
        case UI_OBJTYPE_TEXTBOX:      DrawTextBox(i);     break;
        case UI_OBJTYPE_PROGRESSBAR:  DrawProgressBar(i); break;
        case UI_OBJTYPE_BITMAP:       DrawBitmap(i);      break;
        case UI_OBJTYPE_LINE:         DrawLine(i);        break;
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
void Screen::Shown(ScreenParams *params) {}

//----------------------------------------------------------------------------------------------------
// Change the screen caption
//----------------------------------------------------------------------------------------------------
void Screen::SetScreenCaption(const char* newCaption)
{
  caption = newCaption;

  display->tft.fillRect(39, 21, 180, 50, COLOR_SCR_CAPTION_BACKGROUND);
  display->tft.setTextColor(COLOR_SCR_TEXT);
  display->tft.setTextSize(2);
  display->tft.setCursor(40, 40);
  display->tft.print(caption);
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
void Screen::AddPushButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, uint16_t bmpWidth, uint16_t bmpHeight, const unsigned char *bitmap)
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
void Screen::AddStateButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, uint16_t bmpWidth, uint16_t bmpHeight, const unsigned char *bitmap, bool pressed)
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
void Screen::AddMenuButton(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colNorm, uint16_t colPress, const char* caption, uint16_t bmpWidth, uint16_t bmpHeight, const unsigned char *bitmap)
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
   display->tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, (uiObjects[id].pressed ? uiObjects[id].colorPressed : uiObjects[id].colorUnpressed));      
   
   if (uiObjects[id].bmpWidth == 0 && uiObjects[id].bmpHeight == 0)
   {
      // Draw caption
      display->tft.setTextSize(2);
      display->tft.setTextColor(COLOR_SCR_TEXT);
      display->tft.setCursor(uiObjects[id].x + (uiObjects[id].width / 2) - (strlen(uiObjects[id].caption) * 12 / 2), uiObjects[id].y + ((uiObjects[id].height - 13) / 2));
      display->tft.print(uiObjects[id].caption);
   }
   else
   {
      // Draw bitmap
      display->tft.drawBitmap(uiObjects[id].x + ((uiObjects[id].width - uiObjects[id].bmpWidth) / 2), 
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
   display->tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, (uiObjects[id].pressed ? uiObjects[id].colorPressed : uiObjects[id].colorUnpressed));      
   
   if (uiObjects[id].bmpWidth == 0 && uiObjects[id].bmpHeight == 0)
   {
      // Draw caption
      display->tft.setTextSize(2);
      display->tft.setTextColor(COLOR_SCR_TEXT);
      display->tft.setCursor(uiObjects[id].x + 20, uiObjects[id].y + ((uiObjects[id].height - 13) / 2));
   }
   else
   {
      // Draw bitmap
      display->tft.drawBitmap(uiObjects[id].x + 20, 
                              uiObjects[id].y + ((uiObjects[id].height - uiObjects[id].bmpHeight) / 2), 
                              uiObjects[id].bitmap, uiObjects[id].bmpWidth, uiObjects[id].bmpHeight, COLOR_SCR_TEXT);

      display->tft.setCursor(uiObjects[id].x + uiObjects[id].bmpWidth + 40, uiObjects[id].y + ((uiObjects[id].height - 13) / 2));
   }

   display->tft.print(uiObjects[id].caption);
}

//----------------------------------------------------------------------------------------------------
// Toggle push button state and returns to the unpressed position
//----------------------------------------------------------------------------------------------------
void Screen::ToggleButtonState(uint8_t id)
{
  switch (uiObjects[id].type)
  {
    case UI_OBJTYPE_PUSH_BUTTON:
      for (uint8_t i = 0; i <= 1; i++)
      {
        uiObjects[id].pressed = !uiObjects[id].pressed;
        DrawButton(id);
        delay(75);
      }
      uiObjects[id].pressed = false;
      break;

    case UI_OBJTYPE_CHECK_BUTTON:
      uiObjects[id].pressed = !uiObjects[id].pressed;
      DrawButton(id);
      break;

    case UI_OBJTYPE_MENU_BUTTON:
      for (uint8_t i = 0; i <= 1; i++)
      {
        uiObjects[id].pressed = !uiObjects[id].pressed;   
        DrawMenuButton(id);
        delay(75);
      }
      uiObjects[id].pressed = false;
      break;
  }
}

//----------------------------------------------------------------------------------------------------
// Set the state for the specified check button
// NOTE: For any other type of object the invokation will be cancelled
//----------------------------------------------------------------------------------------------------
void Screen::SetButtonState(uint8_t id, bool state)
{
  if (uiObjects[id].type == UI_OBJTYPE_CHECK_BUTTON && uiObjects[id].pressed != state)
  {
    uiObjects[id].pressed = state;
    DrawButton(id);
  }
}

//----------------------------------------------------------------------------------------------------
// Toggle button selection state
//----------------------------------------------------------------------------------------------------
void Screen::SelectButton(uint8_t objId)
{
  for (int i = 0; i < UI_MAX_OBJECTS; i++)
  {
    if (uiObjects[i].type == UI_OBJTYPE_MENU_BUTTON && uiObjects[i].selected)
      display->tft.drawRect(uiObjects[i].x, uiObjects[i].y, uiObjects[i].width, uiObjects[i].height, uiObjects[i].colorUnpressed);

    uiObjects[i].selected = false;
  }

  uiObjects[objId].selected = true;
  display->tft.drawRect(uiObjects[objId].x, uiObjects[objId].y, uiObjects[objId].width, uiObjects[objId].height, COLOR_BTN_SELECTED);
}

//----------------------------------------------------------------------------------------------------
// Add a text label to the current screen
//----------------------------------------------------------------------------------------------------
void Screen::AddLabel(uint8_t id, uint16_t x, uint16_t y, uint8_t size, uint16_t color, const char* text)
{
  if (!uiObjects[id].initialized)
   {
      uiObjects[id].initialized    = true;
      uiObjects[id].type           = UI_OBJTYPE_TEXT_LABEL;
      uiObjects[id].x              = x;
      uiObjects[id].y              = y;
      uiObjects[id].width          = size;
      uiObjects[id].colorPressed   = color;
      uiObjects[id].caption        = text;
   }
}

//----------------------------------------------
// Draw a text box object
//----------------------------------------------
void Screen::DrawLabel(uint8_t id)
{
  display->tft.setTextColor(uiObjects[id].colorPressed);
  display->tft.setTextSize(uiObjects[id].width);
  display->tft.setCursor(uiObjects[id].x, uiObjects[id].y);
  display->tft.print(uiObjects[id].caption);
}

//----------------------------------------------
// Update de label value and redraw it
//----------------------------------------------
void Screen::SetLabelTextValue(uint8_t id, const char* text)
{
  // Delete previous text
  display->tft.setTextColor(COLOR_SCR_BACKGROUND);
  display->tft.setTextSize(uiObjects[id].width);
  display->tft.setCursor(uiObjects[id].x, uiObjects[id].y);
  display->tft.print(uiObjects[id].caption);

  // Update text
  uiObjects[id].caption = text;
  DrawLabel(id);
}

void Screen::SetLabelIntValue(uint8_t id, uint16_t value)
{
  // Delete previous text
  display->tft.setTextColor(COLOR_SCR_BACKGROUND);
  display->tft.setTextSize(uiObjects[id].width);
  display->tft.setCursor(uiObjects[id].x, uiObjects[id].y);
  display->tft.print(uiObjects[id].caption);

  // Update text
  char buff[10];
  itoa(value, buff, 10);
  uiObjects[id].caption = buff;
  DrawLabel(id);
}

//----------------------------------------------------------------------------------------------------
// Add a text box to the current screen
//----------------------------------------------------------------------------------------------------
void Screen::AddTextBox(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t colBackground, uint16_t colBorder, const char* text)
{
   if (!uiObjects[id].initialized)
   {
      uiObjects[id].initialized    = true;
      uiObjects[id].type           = UI_OBJTYPE_TEXTBOX;
      uiObjects[id].x              = x;
      uiObjects[id].y              = y;
      uiObjects[id].width          = width;
      uiObjects[id].height         = height;
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
   display->tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorUnpressed); 
   display->tft.drawRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorPressed);
   display->tft.setTextColor(COLOR_SCR_TEXT);
   display->tft.setTextSize(3);
   display->tft.setCursor(uiObjects[id].x + 10, uiObjects[id].y + 10);
   display->tft.print(uiObjects[id].caption);
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
   display->tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorUnpressed);
   display->tft.fillRect(uiObjects[id].x, uiObjects[id].y, map(uiObjects[id].value, 0, 128, 0, uiObjects[id].width), uiObjects[id].height, uiObjects[id].colorPressed);
   display->tft.drawRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorBorder);
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
void Screen::AddBitmap(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, const unsigned char *bitmap)
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
      uiObjects[id].colorUnpressed = color;
      uiObjects[id].bitmap         = bitmap;
   }
}

//----------------------------------------------
// Draw a monochrome bitmap object
//----------------------------------------------
void Screen::DrawBitmap(uint8_t id)
{
   display->tft.fillRect(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, COLOR_SCR_BACKGROUND); 
   display->tft.drawBitmap(uiObjects[id].x, uiObjects[id].y, uiObjects[id].bitmap, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorUnpressed);
}

//----------------------------------------------
// Add a line to the screen
//----------------------------------------------
void Screen::AddLine(uint8_t id, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
  if (!uiObjects[id].initialized)
   {
      uiObjects[id].initialized    = true;
      uiObjects[id].type           = UI_OBJTYPE_LINE;
      uiObjects[id].x              = x0;
      uiObjects[id].y              = y0;
      uiObjects[id].width          = x1;
      uiObjects[id].height         = y1;
      uiObjects[id].colorUnpressed = color;
   }
}

//----------------------------------------------
// Draw a line
//----------------------------------------------
void Screen::DrawLine(uint8_t id)
{
  display->tft.drawLine(uiObjects[id].x, uiObjects[id].y, uiObjects[id].width, uiObjects[id].height, uiObjects[id].colorUnpressed);
}

//----------------------------------------------
// Paint a blank screen with caption
//----------------------------------------------
void Screen::DrawBaseScreen(const char* caption, bool resetNotifyBar)
{
  if (resetNotifyBar)
    display->tft.fillRect(0, 0, display->tft.width(), 20, COLOR_NAVBAR_BACKGROUND);

  display->tft.fillRect(0, 21, display->tft.width(), 50, COLOR_SCR_CAPTION_BACKGROUND);         // screen caption
  display->tft.fillRect(0, 72, display->tft.width(), display->tft.height() - 72, COLOR_SCR_BACKGROUND);  // screen area

  //display->tft.drawBitmap(220, 2, BMP_XPN_OFF, 18, 18, COLOR_NAVBAR_DISABLED);
  display->tft.drawBitmap(10, 35, BMP_MENU, 24, 24, COLOR_SCR_TEXT);
   
  display->tft.setTextColor(COLOR_SCR_TEXT);
  display->tft.setTextSize(2);                 
  display->tft.setCursor(40, 40);
  display->tft.print(caption);

  // Set default cursor position and text size at begining to the scr
  display->tft.setTextSize(1);      
  display->tft.setCursor(1, 85);
}

//----------------------------------------------
// Draw/update a notification icon
// Icons fixed sixe: 18x18px
//----------------------------------------------
void Screen::DrawNotifyIcon(uint8_t index, uint16_t color, const unsigned char *bitmap)
{
  // Remove previous icon
  display->tft.fillRect(display->tft.width() - ((index + 1) * 20), 0, 20, 20, COLOR_NAVBAR_BACKGROUND);

  // Draw/update the icon
  display->tft.drawBitmap(display->tft.width() - ((index + 1) * 20), 0, bitmap, 18, 18, color);
}

//----------------------------------------------
// Draw/update a notification icon
// Icons fixed sixe: 18x18px
//----------------------------------------------
void Screen::PrintNotifyText(const char *text, uint16_t color)
{
  // Remove previous text
  display->tft.fillRect(0, 0, display->tft.width() / 2, 20, COLOR_NAVBAR_BACKGROUND);

  // Print the text
  display->tft.setTextSize(1);
  display->tft.setTextColor(color);
  display->tft.setCursor(4, 8);
  display->tft.print(text);
}

//----------------------------------------------
// Print a text line in the screen
//----------------------------------------------
void Screen::PrintTextLine(const char *text)
{
  display->tft.setTextColor(COLOR_SCR_TEXT);
  display->tft.println(text);
}

//----------------------------------------------
// Print an error text line in the screen
//----------------------------------------------
void Screen::PrintErrTextLine(const char *text)
{
   display->tft.setTextColor(COLOR_SCR_ERROR_TEXT);
   display->tft.println(text);
}
