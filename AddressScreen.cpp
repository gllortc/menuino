#import <Arduino.h>
#include "AddressScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
AddressScreen::AddressScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void AddressScreen::Initialize(TouchDisplay lcdDisplay)
{
  disp    = lcdDisplay;
  id      = SCR_ADDRESS_ID;
  caption = "SET ADDRESS";

  AddTextBox(   UI_ADDR_TXTBOX, 18, 85, 134, 42, COLOR_TXT_BACKGROUND, COLOR_TXT_BORDER, "");
  AddPushButton(UI_ADDR_DEL,    162, 85, 62, 42, COLOR_BTN_INFO_NORMAL, COLOR_BTN_INFO_PRESSED, 24, 24, BMP_DELETE);
   
  AddPushButton(UI_ADDR_1,      18,  135, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "1");
  AddPushButton(UI_ADDR_2,      90,  135, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "2");
  AddPushButton(UI_ADDR_3,      162, 135, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "3");
   
  AddPushButton(UI_ADDR_4,      18,  185, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "4");
  AddPushButton(UI_ADDR_5,      90,  185, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "5");
  AddPushButton(UI_ADDR_6,      162, 185, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "6");
   
  AddPushButton(UI_ADDR_7,      18,  235, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "7");
  AddPushButton(UI_ADDR_8,      90,  235, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "8");
  AddPushButton(UI_ADDR_9,      162, 235, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "9");
   
  AddPushButton(UI_ADDR_0,      90,  285, 62, 42, COLOR_BTN_NORMAL, COLOR_BTN_PRESSED, "0");
   
  AddPushButton(UI_ADDR_CANCEL, 18,  285, 62, 42, COLOR_BTN_ERROR_NORMAL, COLOR_BTN_ERROR_PRESSED, 24, 24, BMP_CANCEL);
  AddPushButton(UI_ADDR_OK,     162, 285, 62, 42, COLOR_BTN_SUCCESS_NORMAL, COLOR_BTN_SUCCESS_PRESSED, 24, 24, BMP_OK);
}

//----------------------------------------------
// Dispatch encoder movements and update menu
//----------------------------------------------
// void AddressScreen::Dispatch() {}

//----------------------------------------------
// Hadle screen clicks
//----------------------------------------------
void AddressScreen::ClickHandler(uint8_t objId, ScrParameters *params) 
{
  Serial.print("DriveScr object handled: "); Serial.println(objId);

  switch (objId)
  {
    case UI_ADDR_0:
    case UI_ADDR_1:
    case UI_ADDR_2:
    case UI_ADDR_3:
    case UI_ADDR_4:
    case UI_ADDR_5:
    case UI_ADDR_6:
    case UI_ADDR_7:
    case UI_ADDR_8:
    case UI_ADDR_9:
      DigitPressed(objId);
      break;

    case UI_ADDR_OK: 
      ToggleButtonState(objId);
      params->gotoScr = SCR_DRIVE_ID;
      params->address = GetNumericAddress();
      break; 

    case UI_ADDR_CANCEL: 
      ToggleButtonState(objId);
      params->gotoScr = SCR_MENU_ID;
      break; 

    case UI_ADDR_DEL: 
      DeleteButtonPressed(objId);
      break; 
  }
}

//----------------------------------------------
// Numeric button pressed
//----------------------------------------------
void AddressScreen::DigitPressed(uint8_t objId)
{
  if (addPos == 4) 
  {
    addPos = 0;
    txtAddress[0] = txtAddress[1] = txtAddress[2] = txtAddress[3] = '\0';
  }

  ToggleButtonState(objId);
   
  txtAddress[addPos] = 48 + objId;
  txtAddress[addPos + 1] = '\0';
  addPos++;
   
  SetTextBoxText(GetUIObject(UI_ADDR_TXTBOX), txtAddress);
}

//----------------------------------------------
// Delete button pressed
//----------------------------------------------
void AddressScreen::DeleteButtonPressed(uint8_t objId)
{
  if (addPos == 0) 
    return;

  ToggleButtonState(objId);

  addPos--;
  txtAddress[addPos] = '\0';
   
  SetTextBoxText(GetUIObject(UI_ADDR_TXTBOX), txtAddress);
}

//----------------------------------------------
// Convert screen address into an integer
//----------------------------------------------
uint16_t AddressScreen::GetNumericAddress()
{
  return atoi(txtAddress);
}

//----------------------------------------------
// Convert numeric addres into char array
//----------------------------------------------
void AddressScreen::SetAddress(uint16_t addr)
{
  ClearAddress();
  itoa(addr, txtAddress, 10);
}

//----------------------------------------------
// Clear address char array
//----------------------------------------------
void AddressScreen::ClearAddress()
{
  for (byte i = 0; i <= TXT_DIGITS_MAX; i++)
    txtAddress[i] = '\0';
}
