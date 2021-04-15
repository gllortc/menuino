#import <Arduino.h>
#include <Encoder.h>
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

  // Initialize the screens
  scrMenu = new MenuScreen();
  scrMenu->Initialize(scr);

  scrSelect = new SelectScreen();
  scrSelect->Initialize(scr);

  scrDrive = new DriveScreen();
  scrDrive->Initialize(scr);

  scrAddress = new AddressScreen();
  scrAddress->Initialize(scr);

  // Show initial screen
  ShowScreen(SCR_MENU_ID);
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

  ScrParameters params;

  scrCurrent->ClickHandler(objId, &params);
  if (params.gotoScr == UI_OBJECT_NULL) return;

  Serial.print("Moving to screen: ");
  Serial.println(params.gotoScr);

  ShowScreen(params);
}

//----------------------------------------------
// Gets the current screen instance
//----------------------------------------------
Screen* ScreenManager::GetCurrentScreen(void)
{
  return scrCurrent;
}

//----------------------------------------------
// Set new current screen
//----------------------------------------------
void ScreenManager::ShowScreen(uint8_t gotoScr)
{
  ScrParameters params;
  params.gotoScr = gotoScr;
  ShowScreen(params);
}

//----------------------------------------------
// Set new current screen
//----------------------------------------------
void ScreenManager::ShowScreen(ScrParameters params)
{
  switch (params.gotoScr)
  {
    case SCR_MENU_ID:
      scrCurrent = scrMenu;
      scrCurrent->Show(&params);
      break;

    case SCR_SELECT_ID:
      scrCurrent = scrSelect;
      scrCurrent->Show(&params);
      break;

    case SCR_DRIVE_ID:
      scrCurrent = scrDrive;
      scrCurrent->Show(&params);
      break;

    case SCR_ADDRESS_ID:
      scrCurrent = scrAddress;
      scrCurrent->Show(&params);
      break;

    case SCR_MESSAGE_ID:
      scrCurrent = srcMessage;
      scrCurrent->Show(&params);
      break;
  }
}
