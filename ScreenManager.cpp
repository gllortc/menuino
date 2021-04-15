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

  // Show 1st screen
  scrCurrent = scrMenu;
  scrCurrent->Show();
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

  uint8_t newScr = scrCurrent->ClickHandler(objId);
  if (newScr == UI_OBJECT_NULL) return;

  Serial.print("Moving to screen: ");
  Serial.println(newScr);

  ShowScreen(newScr);
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
void ScreenManager::ShowScreen(uint8_t scrId)
{
  switch (scrId)
  {
    case SCR_MENU_ID:
      scrCurrent = scrMenu;
      scrCurrent->Show();
      break;

    case SCR_SELECT_ID:
      scrCurrent = scrSelect;
      scrCurrent->Show();
      break;

    case SCR_DRIVE_ID:
      scrCurrent = scrDrive;
      scrCurrent->Show();
      break;

    case SCR_ADDRESS_ID:
      scrCurrent = scrAddress;
      scrCurrent->Show();
      break;

    case SCR_MESSAGE_ID:
      scrCurrent = srcMessage;
      scrCurrent->Show();
      break;

    default:
      break;
  }
}
