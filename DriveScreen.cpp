#include <Arduino.h>
#include <EEPROM.h>
#include <EncoderMenuSwitch.h>
#include <XpnManager.h>
#include "DriveScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
DriveScreen::DriveScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void DriveScreen::InitializeUI()
{
  id      = SCR_DRIVE_ID;
  caption = "";

  AddPushButton(UI_CTRL_RETURN,         180, 85, 42, 42,  COLOR_BTN_INFO_NORMAL,  COLOR_BTN_INFO_PRESSED,   24, 24, BMP_RETURN);

  AddStateButton(UI_CTRL_F0,            18,  135, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_WARNING_NORMAL, 24, 24, BMP_LIGHT, false);
  AddStateButton(UI_CTRL_F1,            72,  135, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_WARNING_NORMAL, "F1", false);
  AddStateButton(UI_CTRL_F2,            126, 135, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_WARNING_NORMAL, "F2", false);
  AddStateButton(UI_CTRL_F3,            180, 135, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_WARNING_NORMAL, "F3", false);
   
  AddStateButton(UI_CTRL_F4,            18,  185, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_WARNING_NORMAL, "F4", false);
  AddStateButton(UI_CTRL_F5,            72,  185, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_WARNING_NORMAL, "F5", false);
  AddStateButton(UI_CTRL_F6,            126, 185, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_WARNING_NORMAL, "F6", false);
  AddStateButton(UI_CTRL_F7,            180, 185, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_WARNING_NORMAL, "F7", false);
   
  // Speed controller
  AddPushButton(UI_CTRL_SPEED_DWN_BIG,  18,  235, 42, 60, COLOR_BTN_NORMAL,       COLOR_BTN_PRESSED,        24, 24, BMP_FAST_BACKWARD);
  AddPushButton(UI_CTRL_SPEED_DWN,      72,  235, 42, 60, COLOR_BTN_NORMAL,       COLOR_BTN_PRESSED,        24, 24, BMP_BACK);
  AddPushButton(UI_CTRL_SPEED_UP,       126, 235, 42, 60, COLOR_BTN_NORMAL,       COLOR_BTN_PRESSED,        24, 24, BMP_FORWARD);
  AddPushButton(UI_CTRL_SPEED_UP_BIG,   180, 235, 42, 60, COLOR_BTN_NORMAL,       COLOR_BTN_PRESSED,        24, 24, BMP_FAST_FORWARD);
   
  AddStateButton(UI_CTRL_DIR_FWD,       18,  303, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_PRESSED,        24, 24, BMP_DIR_BACK,    true);
  AddStateButton(UI_CTRL_STOP,          72,  303, 92, 42, COLOR_BTN_ERROR_NORMAL, COLOR_BTN_ERROR_PRESSED,  24, 24, BMP_STOP,        false);
  AddStateButton(UI_CTRL_DIR_REV,       180, 303, 42, 42, COLOR_BTN_NORMAL,       COLOR_BTN_PRESSED,        24, 24, BMP_DIR_FORWARD, false);
   
  // Progress bar
  AddProgressBar(UI_CTRL_PGBAR,         18, 355, 204, 20, COLOR_PGB_BACKGROUND,   COLOR_PGB_BORDER,         COLOR_PGB_FILL, 0); // activeEngine.speed);

  xpn = XpnManager::getInstance();
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void DriveScreen::Shown(ScreenParams *params) 
{
  xpn->master.devId = XpnManager::GetDeviceID();
  
  // Show XPN device ID
  char buffer[11];
  sprintf(buffer, LNG_EN_DRIVE_DEVICEID, xpn->master.devId);
  PrintNotifyText(buffer);

  // Show screen caption
  switch (params->trackNum)
  {
    case 1:
      SetScreenCaption(LNG_EN_DRIVE_HEADER_TRACK_1);
      break;

    case 2:
      SetScreenCaption(LNG_EN_DRIVE_HEADER_TRACK_2);
      break;

    case 3:
      SetScreenCaption(LNG_EN_DRIVE_HEADER_TRACK_3);
      break;

    case 4:
      SetScreenCaption(LNG_EN_DRIVE_HEADER_TRACK_4);
      break;
       
    default:
      SetScreenCaption(LNG_EN_DRIVE_HEADER_MANUAL);
      break;
  }

  // Get selected engine information
  xpn->StartOperatingEngine(params->address);

  // Update engine information
  display->tft.setTextSize(1);
  display->tft.setCursor(18, 85);
  display->tft.print(LNG_EN_DRIVE_ADR);
  display->tft.setTextSize(3);
  display->tft.setCursor(18, 100);
  display->tft.print(xpn->engine.address);
}

//----------------------------------------------------------------------------------------------------
// Hadle screen clicks
//----------------------------------------------------------------------------------------------------
ScreenParams* DriveScreen::ClickHandler(uint8_t objId)
{
  switch (objId)
  {
    case UI_CTRL_RETURN:
      ToggleButtonState(objId);
      return GotoScreen(SCR_MENU_ID);
      
    case UI_CTRL_F0: 
      xpn->ToggleEngineFunction(0);
      break;
      
    case UI_CTRL_F1: 
      xpn->ToggleEngineFunction(1);
      break;
      
    case UI_CTRL_F2: 
      xpn->ToggleEngineFunction(2);
      break;
      
    case UI_CTRL_F3: 
      xpn->ToggleEngineFunction(3);
      break;
      
    case UI_CTRL_F4: 
      xpn->ToggleEngineFunction(4);
      break;
      
    case UI_CTRL_F5: 
      xpn->ToggleEngineFunction(5);
      break;
      
    case UI_CTRL_F6:
      xpn->ToggleEngineFunction(6);
      break;
      
    case UI_CTRL_F7:
      xpn->ToggleEngineFunction(7);
      break;

    case UI_CTRL_DIR_REV:
      xpn->SetEngineDirection(1);
      break;
    
    case UI_CTRL_DIR_FWD:
      xpn->SetEngineDirection(0);
      break;

    case UI_CTRL_STOP:
      ToggleButtonState(UI_CTRL_STOP);
      break;
      
    case UI_CTRL_SPEED_UP: 
      break;
      
    case UI_CTRL_SPEED_UP_BIG: 
      break;
      
    case UI_CTRL_SPEED_DWN: 
      break;
      
    case UI_CTRL_SPEED_DWN_BIG: 
      break;

    default:
      return NULL;
  }
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void DriveScreen::EncoderMovementHandler(EncoderMenuSwitch::EncoderDirection dir)
{
  Serial.print("Status: "); Serial.println(xpn->master.status);
  
  if (xpn->master.status != csNormal)
    return;

  switch (dir)
  {
    case EncoderMenuSwitch::ENCODER_UP:
      if (xpn->engine.speed < xpn->engine.steps) xpn->engine.speed++;
      break;

    case EncoderMenuSwitch::ENCODER_DOWN:
      if (xpn->engine.speed > 0) xpn->engine.speed--;
      break;
  }

  Serial.print("Speed req: "); Serial.println(xpn->engine.speed);

  // SetProgressBarValue(UI_CTRL_PGBAR, engine.speed);
  xpn->SetEngineSpeed(xpn->engine.speed);
}

//----------------------------------------------
// Dispatch encoder clicks
//----------------------------------------------
void DriveScreen::EncoderClickHandler() 
{
  // TODO: What to do on an encoder click?
}

//----------------------------------------------
// Handle CS engine notifications
//----------------------------------------------
void DriveScreen::HandleEngineNotify(XpnEngine *engine)
{
  Serial.print("Adr:  "); Serial.println(xpn->engine.address);
  Serial.print("Dir:  "); Serial.println(xpn->engine.direction);
  // Serial.print("Steps:"); Serial.println(xpn->GetSpeedMax(steps));

  // Update the progress bar value
  SetProgressBarValue(UI_CTRL_PGBAR, xpn->engine.speed);

  // Update direction button states
  SetButtonState(UI_CTRL_DIR_FWD, xpn->engine.direction);
  SetButtonState(UI_CTRL_DIR_REV, !xpn->engine.direction);

  // Update function button states
  SetButtonState(UI_CTRL_F0, bitRead(xpn->engine.func.Bits, 0));
  SetButtonState(UI_CTRL_F1, bitRead(xpn->engine.func.Bits, 1));
  SetButtonState(UI_CTRL_F2, bitRead(xpn->engine.func.Bits, 2));
  SetButtonState(UI_CTRL_F3, bitRead(xpn->engine.func.Bits, 3));
  SetButtonState(UI_CTRL_F4, bitRead(xpn->engine.func.Bits, 4));
  SetButtonState(UI_CTRL_F5, bitRead(xpn->engine.func.Bits, 5));
  SetButtonState(UI_CTRL_F6, bitRead(xpn->engine.func.Bits, 6));
  SetButtonState(UI_CTRL_F7, bitRead(xpn->engine.func.Bits, 7));

  Serial.print("Speed:"); Serial.println(xpn->engine.speed);
  Serial.print("F0:"); Serial.println(bitRead(xpn->engine.func.Bits, 0));
  Serial.print("F1:"); Serial.println(bitRead(xpn->engine.func.Bits, 1));
  Serial.print("F2:"); Serial.println(bitRead(xpn->engine.func.Bits, 2));
  Serial.print("F3:"); Serial.println(bitRead(xpn->engine.func.Bits, 3));
}
