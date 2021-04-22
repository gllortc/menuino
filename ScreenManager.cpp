#import <Arduino.h>
#include "ScreenObjects.h"
#include "ScreenManager.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
ScreenManager::ScreenManager() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void ScreenManager::Initialize()
{
  // Initialize the display
  scr.Initialize();

  // Initialize the screen parameters
  params = new ScrParameters();

  // Initialize the screens
  scrMenu = new MenuScreen();
  scrMenu->Initialize(scr);

  scrSelect = new SelectScreen();
  scrSelect->Initialize(scr);

  scrDrive = new DriveScreen();
  scrDrive->Initialize(scr);

  scrInput = new InputScreen();
  scrInput->Initialize(scr);

  scrSetup = new SetupScreen();
  scrSetup->Initialize(scr);

  // Show initial screen
  params->gotoScr = SCR_MENU_ID;
  ShowScreen(params);
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
void ScreenManager::Dispatch()
{
  scr.Dispatch();
  scrCurrent->Dispatch();
}

//----------------------------------------------
// Handle the screen clicks
//----------------------------------------------
void ScreenManager::HandleScreenClick(uint16_t xpos, uint16_t ypos)
{
  uint8_t objId = scrCurrent->GetScreenClickedObjectID(xpos, ypos);
  if (objId == UI_OBJECT_NULL) return;

  Serial.print("Object clicked: ");
  Serial.println(objId);

  params = scrCurrent->ClickHandler(objId); //, &params);
  if (params == NULL) return;

  Serial.print("Moving to screen: ");
  Serial.println(params->gotoScr);

  ShowScreen(params);
}

//----------------------------------------------
// Handle the encoder movement
//----------------------------------------------
void ScreenManager::HandleEncoderMovement(uint8_t dir)
{
  
}

//----------------------------------------------
// Handle engine notification received
//----------------------------------------------
void ScreenManager::HandleEngineNotify(uint8_t adrHigh, uint8_t adrLow, uint8_t steps, uint8_t speed, uint8_t dir, uint8_t F0, uint8_t F1, uint8_t F2, uint8_t F3)
{
  // Discard notifications outside the drive screen
  if (scrCurrent->id != SCR_DRIVE_ID) return;

  ((DriveScreen*)scrCurrent)->HandleEngineNotify(adrHigh, adrLow, steps, speed, dir, F0, F1, F2, F3);
}

//----------------------------------------------
// Handle central status notifications
//----------------------------------------------
void ScreenManager::HandleMasterStatusNotify(uint8_t status)
{
  // Discard notifications outside the drive screen
  if (scrCurrent->id != SCR_DRIVE_ID) return;

  ((DriveScreen*)scrCurrent)->HandleMasterStatusNotify(status);
}

//----------------------------------------------
// Gets the current screen instance
//----------------------------------------------
Screen* ScreenManager::GetCurrentScreen()
{
  return scrCurrent;
}

//----------------------------------------------
// Set new current screen
//----------------------------------------------
void ScreenManager::ShowScreen(ScrParameters* params)
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
