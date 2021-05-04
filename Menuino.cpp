#include <Arduino.h>
#include "ScreenObjects.h"
#include "Menuino.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
Menuino::Menuino() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void Menuino::Initialize()
{
  // Initialize the display
  hardware.Initialize();

  // Initialize the screen parameters
  params = new ScreenParams();

  // Initialize the screens
  scrMenu = new MenuScreen();
  scrMenu->Initialize(&hardware);

  scrSelect = new SelectScreen();
  scrSelect->Initialize(&hardware);

  scrDrive = new DriveScreen();
  scrDrive->Initialize(&hardware);

  scrInput = new InputScreen();
  scrInput->Initialize(&hardware);

  scrSetup = new SetupScreen();
  scrSetup->Initialize(&hardware);

  scrInfo = new InfoScreen();
  scrInfo->Initialize(&hardware);

  // Show initial screen
  params->gotoScr = SCR_MENU_ID;
  ShowScreen(params);
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void Menuino::Dispatch()
{
  hardware.Dispatch();
  // scrCurrent->Dispatch();
}

//----------------------------------------------
// Handle the screen clicks
//----------------------------------------------
void Menuino::HandleScreenClick(uint16_t xpos, uint16_t ypos)
{
  uint8_t objId = scrCurrent->GetScreenClickedObjectID(xpos, ypos);
  if (objId == UI_OBJECT_NULL) return;

  params = scrCurrent->ClickHandler(objId);
  if (params == NULL) return;

  ShowScreen(params);
}

//----------------------------------------------
// Handle the encoder movement
//----------------------------------------------
void Menuino::HandleEncoderMoved(EncoderMenuSwitch::EncoderDirection dir)
{
  scrCurrent->EncoderMovementHandler(dir);
}

//----------------------------------------------
// Handle the encoder click
//----------------------------------------------
void Menuino::HandleEncoderClick()
{
  scrCurrent->EncoderClickHandler();
}

//----------------------------------------------
// Handle engine notification received
//----------------------------------------------
void Menuino::HandleEngineNotify(uint8_t adrHigh, uint8_t adrLow, uint8_t steps, uint8_t speed, uint8_t dir, uint8_t F0, uint8_t F1, uint8_t F2, uint8_t F3)
{
  scrCurrent->HandleEngineNotify(adrHigh, adrLow, steps, speed, dir, F0, F1, F2, F3);
}

//----------------------------------------------
// Handle central status notifications
//----------------------------------------------
void Menuino::HandleMasterStatusNotify(uint8_t status)
{
  hardware.xpnMaster.status = status;
  
  switch (hardware.xpnMaster.status) 
  {
    case csNormal:
      hardware.DrawNotifyIcon(0, COLOR_NAVBAR_NORMAL, BMP_XPN_ON);
      break;

    case csShortCircuit: // Corto circuito - OFF
      hardware.DrawNotifyIcon(0, COLOR_NAVBAR_ERROR, BMP_XPN_SHORT);
      break;
    
    case csTrackVoltageOff: // Sin tension en via - OFF
      hardware.DrawNotifyIcon(0, COLOR_NAVBAR_WARNING, BMP_XPN_WARN);
      break;

    case csEmergencyStop: // Parada emergencia - StoP
      hardware.DrawNotifyIcon(0, COLOR_NAVBAR_WARNING, BMP_XPN_WARN);
      break;

    case csServiceMode: // Programacion en modo servicio - Pro
      hardware.DrawNotifyIcon(0, COLOR_NAVBAR_NORMAL, BMP_XPN_SERVICE);
      break;
  }
}

//----------------------------------------------
// Handle central status information
//----------------------------------------------
void Menuino::HandleXPNInfo(uint8_t ver, uint8_t hdwtype)
{
  hardware.xpnMaster.vermajor = ver >> 4;
  hardware.xpnMaster.verminor = (ver && 0xF0);
  hardware.xpnMaster.type     = hdwtype;
}

//----------------------------------------------
// Gets the current screen instance
//----------------------------------------------
Screen* Menuino::GetCurrentScreen()
{
  return scrCurrent;
}

//----------------------------------------------
// Set new current screen
//----------------------------------------------
void Menuino::ShowScreen(ScreenParams* params)
{
  switch (params->gotoScr)
  {
    case SCR_MENU_ID:
      scrCurrent = scrMenu;
      scrCurrent->Show(params);
      break;

    case SCR_SELECT_ID:
      scrCurrent = scrSelect;
      scrCurrent->Show(params);
      break;

    case SCR_DRIVE_ID:
      scrCurrent = scrDrive;
      scrCurrent->Show(params);
      break;

    case SCR_ADDRESS_ID:
      scrCurrent = scrInput;
      scrCurrent->Show(params);
      break;

    case SCR_WAIT_ID:
      scrCurrent = scrWait;
      scrCurrent->Show(params);
      break;

    case SCR_SETUP_ID:
      scrCurrent = scrSetup;
      scrCurrent->Show(params);
      break;

    case SCR_INFO_ID:
      scrCurrent = scrInfo;
      scrCurrent->Show(params);
      break;
  }
}
