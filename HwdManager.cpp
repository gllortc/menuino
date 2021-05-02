#include <Arduino.h>
#include <EEPROM.h>
#include <EncoderMenuSwitch.h>
#include "ScreenObjects.h"
#include "HwdManager.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
HwdManager::HwdManager() {}

//----------------------------------------------
// Initialize the TFT display
//----------------------------------------------
void HwdManager::Initialize()
{
  uint16_t ID;

  //-----------------------------
  // Screen initialization
  //-----------------------------
  
  ID = tft.readID();
   
  // Screen equivalences
  if (ID == 0x0D3D3) ID = 0x9481;
   
  // Initialization
  tft.begin(ID);
   
  // if (tft.height() > tft.width()) 
  tft.setRotation(Orientation);
   
  DrawBaseScreen(LNG_EN_INI_HEADER, true);
  DrawNotifyIcon(0, COLOR_NAVBAR_DISABLED, BMP_XPN_OFF);

  PrintTextLine(LNG_EN_INI_VERSION);
  delay(1500);
  
  PrintTextLine(LNG_EN_INI_LCD);
  delay(200);  
   
  // Touchscreen initialization
  // switch (Orientation) // adjust for different aspects
  // {      
      // case 0:   break;        //no change,  calibrated for PORTRAIT
      // case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
      // case 2:   
      SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); // break;
      // case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
  // }
  ts = TouchScreen(XP, YP, XM, YM, 260);     // call the constructor AGAIN with new values.

  //-----------------------------
  // Encoder initialization
  //-----------------------------

  PrintTextLine(LNG_EN_INI_ENCODER);
  delay(200);

  encoder.Initialize(ENCODER_PIN_1, ENCODER_PIN_2, ENCODER_PIN_SW);

  //-----------------------------
  // XpressNet initialization
  //-----------------------------

  PrintTextLine(LNG_EN_INI_XPN);
  delay(200);

  xpn.start(GetDeviceID(), XPN_TXRX_PIN); // Start XPN
  xpn.getPower();                         // Get CS status

  PrintTextLine(LNG_EN_INI_READY);
  delay(500);
}

//----------------------------------------------
// Touschscreen dispatcher
//----------------------------------------------
void HwdManager::Dispatch()
{
  xpn.receive();      // XPN dispatcher
  encoder.Dispatch(); // Encoder dispatcher
  CheckTouch();       // Touchscreen dispatcher
}

//----------------------------------------------
// Check for touchscreen press
//----------------------------------------------
void HwdManager::CheckTouch()
{
  tp = ts.getPoint();  // tp.x, tp.y are ADC values

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(XP, OUTPUT);
  pinMode(YM, OUTPUT);

  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE)
  {
    delay(100);
    
    // is controller wired for Landscape ? or are we oriented in Landscape?
    if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
    
    if (OnClick) 
    {
      // scale from 0->1023 to tft.width  i.e. left = 0, rt = width
      // most mcufriend have touch (with icons) that extends below the TFT
      // screens without icons need to reserve a space for "erase"
      // scale the ADC values from ts.getPoint() to screen values e.g. 0-239

      OnClick(map(tp.x, TS_LEFT, TS_RT,  tft.width(),  0), 
              map(tp.y, TS_TOP,  TS_BOT, tft.height(), 0));
    }
  }
}

//----------------------------------------------
// Paint a blank screen with caption
//----------------------------------------------
void HwdManager::DrawBaseScreen(const char* caption, bool resetNotifyBar)
{
  if (resetNotifyBar)
    tft.fillRect(0, 0, tft.width(), 20, COLOR_NAVBAR_BACKGROUND);

  tft.fillRect(0, 21, tft.width(), 50, COLOR_SCR_CAPTION_BACKGROUND);         // screen caption
  tft.fillRect(0, 72, tft.width(), tft.height() - 72, COLOR_SCR_BACKGROUND);  // screen area

  //tft.drawBitmap(220, 2, BMP_XPN_OFF, 18, 18, COLOR_NAVBAR_DISABLED);
  tft.drawBitmap(10, 35, BMP_MENU,    24, 24, COLOR_SCR_TEXT);
   
  tft.setTextColor(COLOR_SCR_TEXT);
  tft.setTextSize(2);                 
  tft.setCursor(40, 40);
  tft.print(caption);

  // Set default cursor position and text size at begining to the scr
  tft.setTextSize(1);      
  tft.setCursor(1, 85);
}

//----------------------------------------------
// Draw/update a notification icon
// Icons fixed sixe: 18x18px
//----------------------------------------------
void HwdManager::DrawNotifyIcon(uint8_t index, uint16_t color, const unsigned char *bitmap)
{
  // Remove previous icon
  tft.fillRect(tft.width() - ((index + 1) * 20), 0, 20, 20, COLOR_NAVBAR_BACKGROUND);

  // Draw/update the icon
  tft.drawBitmap(tft.width() - ((index + 1) * 20), 0, bitmap, 18, 18, color);
}

//----------------------------------------------
// Print a text line in the screen
//----------------------------------------------
void HwdManager::PrintTextLine(const char *text)
{
  tft.setTextColor(COLOR_SCR_TEXT);
  tft.println(text);
}

//----------------------------------------------
// Print an error text line in the screen
//----------------------------------------------
void HwdManager::PrintErrTextLine(const char *text)
{
   tft.setTextColor(COLOR_SCR_ERROR_TEXT);
   tft.println(text);
}

//----------------------------------------------------------------------------------------------------
// XPN: Store the central station status
//----------------------------------------------------------------------------------------------------
void HwdManager::SetXPNStatus(uint8_t status)
{
  xpnMasterStatus = status;
}

//----------------------------------------------------------------------------------------------------
// XPN: Gets the central station status
//----------------------------------------------------------------------------------------------------
uint8_t HwdManager::GetXPNStatus()
{
  return xpnMasterStatus;
}

//----------------------------------------------------------------------------------------------------
// App Settings -> Gets the associated digital address from the EEPROM for the specified track number
//----------------------------------------------------------------------------------------------------
uint16_t HwdManager::GetTrackAddress(uint8_t trackNum)
{
  return (EEPROM.read(((trackNum - 1) * 2) + 1) << 8) + EEPROM.read(((trackNum - 1) * 2) + 2);
}

//----------------------------------------------------------------------------------------------------
// App Settings -> Sets the associated digital address to a track number in the EEPROM
//----------------------------------------------------------------------------------------------------
void HwdManager::SetTrackAddress(uint8_t track, uint16_t address)
{
  EEPROM.write(((track - 1) * 2) + 1, highByte(address));
  EEPROM.write(((track - 1) * 2) + 2, lowByte(address));
}

//----------------------------------------------------------------------------------------------------
// App Settings -> Gets the XPN digital ID from the EEPROM (default value: 25)
//----------------------------------------------------------------------------------------------------
uint8_t HwdManager::GetDeviceID()
{
  uint8_t devId = EEPROM.read(0);
  if (devId <= 0 || devId > 31) devId = 25;
  return devId;
}

//----------------------------------------------------------------------------------------------------
// App Settings -> Sets the XPN device ID in the EEPROM
//----------------------------------------------------------------------------------------------------
void HwdManager::SetDeviceID(uint8_t id)
{
  EEPROM.write(0, id);
}
