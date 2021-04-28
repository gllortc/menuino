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
  scrMenu->Initialize(hardware);

  scrSelect = new SelectScreen();
  scrSelect->Initialize(hardware);

  scrDrive = new DriveScreen();
  scrDrive->Initialize(hardware);

  scrInput = new InputScreen();
  scrInput->Initialize(hardware);

  scrSetup = new SetupScreen();
  scrSetup->Initialize(hardware);

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
  // Discard notifications outside the drive screen
  if (scrCurrent->id != SCR_DRIVE_ID) return;

  ((DriveScreen*)scrCurrent)->HandleEngineNotify(adrHigh, adrLow, steps, speed, dir, F0, F1, F2, F3);
}

//----------------------------------------------
// Handle central status notifications
//----------------------------------------------
void Menuino::HandleMasterStatusNotify(uint8_t status)
{
  // Discard notifications outside the drive screen
  if (scrCurrent->id != SCR_DRIVE_ID) return;

  ((DriveScreen*)scrCurrent)->HandleMasterStatusNotify(status);
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

    case SCR_MESSAGE_ID:
      scrCurrent = scrMessage;
      scrCurrent->Show(params);
      break;

    case SCR_SETUP_ID:
      scrCurrent = scrSetup;
      scrCurrent->Show(params);
      break;
  }
}
