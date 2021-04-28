#include <Arduino.h>
#include <EEPROM.h>
#include "InputScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
InputScreen::InputScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void InputScreen::Initialize(HwdManager lcdDisplay)
{
  disp    = lcdDisplay;
  id      = SCR_ADDRESS_ID;
  caption = LNG_EN_INPUT_HEADER;

  AddTextBox(   UI_ADDR_TXTBOX, 18, 85, 134, 42,  COLOR_TXT_BACKGROUND,  COLOR_TXT_BORDER, "");
  AddPushButton(UI_ADDR_DEL,    162, 85, 62, 42,  COLOR_BTN_INFO_NORMAL, COLOR_BTN_INFO_PRESSED, 24, 24, BMP_DELETE);
   
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
   
  AddPushButton(UI_ADDR_CANCEL, 18,  285, 62, 42, COLOR_BTN_ERROR_NORMAL,   COLOR_BTN_ERROR_PRESSED,   24, 24, BMP_CANCEL);
  AddPushButton(UI_ADDR_OK,     162, 285, 62, 42, COLOR_BTN_SUCCESS_NORMAL, COLOR_BTN_SUCCESS_PRESSED, 24, 24, BMP_OK);
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void InputScreen::Shown(ScreenParams *params) 
{
  mode       = params->inputMode;
  track      = params->trackNum;
  inputValue = params->address;

  if (inputValue > 0) 
  {
    itoa(inputValue, txtAddress, 10);
    SetTextBoxText(UI_ADDR_TXTBOX, txtAddress);
  }

  switch (mode)
  {
    case INPUT_MODE_MANUAL_ADDR:
      SetScreenCaption(LNG_EN_INPUT_HEADER_MANUAL);
      break;

    case INPUT_MODE_TRACK_ADDR:
      switch (params->trackNum)
      {
        case 1:
          SetScreenCaption(LNG_EN_INPUT_HEADER_TRACK_1);
          break;
        case 2:
          SetScreenCaption(LNG_EN_INPUT_HEADER_TRACK_2);
          break;
        case 3:
          SetScreenCaption(LNG_EN_INPUT_HEADER_TRACK_3);
          break;
        case 4:
          SetScreenCaption(LNG_EN_INPUT_HEADER_TRACK_4);
          break;
      }
      break;

    case INPUT_MODE_DEVID:
      SetScreenCaption(LNG_EN_INPUT_HEADER_DEVICE);
      break;
  }

  disp.tft.setTextSize(2);
}

//----------------------------------------------
// Hadle screen clicks
//----------------------------------------------
ScreenParams* InputScreen::ClickHandler(uint8_t objId)
{
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
      return OkButtonPressed(objId);

    case UI_ADDR_CANCEL: 
      ToggleButtonState(objId);
      return GotoScreen(SCR_MENU_ID);

    case UI_ADDR_DEL: 
      DeleteButtonPressed(objId);
      break; 
  }

  return NULL;
}

//----------------------------------------------
// Numeric button pressed
//----------------------------------------------
void InputScreen::DigitPressed(uint8_t objId)
{
  ToggleButtonState(objId);
  
  if (addPos == 4) 
  {
    addPos = 0;
    txtAddress[0] = txtAddress[1] = txtAddress[2] = txtAddress[3] = '\0';
  }

  txtAddress[addPos] = 48 + objId;
  txtAddress[addPos + 1] = '\0';
  addPos++;
   
  SetTextBoxText(UI_ADDR_TXTBOX, txtAddress);
}

//----------------------------------------------
// Delete button pressed
//----------------------------------------------
void InputScreen::DeleteButtonPressed(uint8_t objId)
{
  if (addPos == 0) 
    return;

  ToggleButtonState(objId);

  addPos--;
  txtAddress[addPos] = '\0';
   
  SetTextBoxText(UI_ADDR_TXTBOX, txtAddress);
}

//----------------------------------------------
// Delete button pressed
//----------------------------------------------
ScreenParams* InputScreen::OkButtonPressed(uint8_t objId)
{
  uint16_t inputValue = GetInputValue();

  ToggleButtonState(objId);
  
  switch (mode)
  {
    case INPUT_MODE_MANUAL_ADDR:
      return GotoScreen(SCR_DRIVE_ID, inputValue);

    case INPUT_MODE_TRACK_ADDR:
      disp.SetTrackAddress(track, inputValue);
      return GotoScreen(SCR_SETUP_ID, inputValue);

    case INPUT_MODE_DEVID:
      disp.SetDeviceID(lowByte(inputValue));
      return GotoScreen(SCR_SETUP_ID, id);

    default:
      return NULL;
  }
}

//----------------------------------------------
// Convert screen address into an integer
//----------------------------------------------
uint16_t InputScreen::GetInputValue()
{
  return atoi(txtAddress);
}

//----------------------------------------------
// Convert numeric addres into char array
//----------------------------------------------
void InputScreen::SetAddress(uint16_t addr)
{
  ClearAddress();
  itoa(addr, txtAddress, 10);
}

//----------------------------------------------
// Clear address char array
//----------------------------------------------
void InputScreen::ClearAddress()
{
  for (byte i = 0; i <= TXT_DIGITS_MAX; i++)
    txtAddress[i] = '\0';
}
