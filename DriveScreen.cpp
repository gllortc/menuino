#include <Arduino.h>
#include <EEPROM.h>
#include "DriveScreen.h"
#include "ScreenObjects.h"

//----------------------------------------------
// Constructor
//----------------------------------------------
DriveScreen::DriveScreen() {}

//----------------------------------------------
// Initialize the instance
//----------------------------------------------
void DriveScreen::Initialize(HwdManager lcdDisplay)
{
  disp    = lcdDisplay;
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
}

//----------------------------------------------------------------------------------------------------
// Virtual method that can be implemented by derived classes 
// to show information when the screen is shown
//----------------------------------------------------------------------------------------------------
void DriveScreen::Shown(ScreenParams *params) 
{
  xpnDeviceID = disp.GetDeviceID();
  
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

  // Set current engine
  engine.address   = params->address;
  engine.steps     = 128;
  engine.speed     = 0;
  engine.direction = 0;

  disp.tft.setTextSize(1);

  char id[2];
  disp.tft.setCursor(4, 8);
  disp.tft.print(LNG_EN_DRIVE_DEVICEID);
  disp.tft.print(itoa(xpnDeviceID, id, 10));
  
  disp.tft.setCursor(18, 85);
  disp.tft.print(LNG_EN_DRIVE_ADR);
  disp.tft.setTextSize(3);
  disp.tft.setCursor(18, 100);
  disp.tft.print(engine.address);
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
    case UI_CTRL_F1: 
    case UI_CTRL_F2: 
    case UI_CTRL_F3: 
    case UI_CTRL_F4: 
    case UI_CTRL_F5: 
    case UI_CTRL_F6: 
    case UI_CTRL_F7: 
      ToggleButtonState(objId);
      break;

    case UI_CTRL_DIR_REV: 
    case UI_CTRL_DIR_FWD: 
      ToggleButtonState(UI_CTRL_DIR_FWD);
      ToggleButtonState(UI_CTRL_DIR_REV);
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
  switch (dir)
  {
    case EncoderMenuSwitch::ENCODER_UP:
      if (engine.speed < engine.steps) engine.speed++;
      break;

    case EncoderMenuSwitch::ENCODER_DOWN:
      if (engine.speed > 0) engine.speed--;
      break;
  }

  SetProgressBarValue(UI_CTRL_PGBAR, engine.speed);
}

//----------------------------------------------
// Dispatch encoder clicks
//----------------------------------------------
void DriveScreen::EncoderClickHandler() 
{

}

//------------------------------------------------------
// Gets the CV17 (address high byte)
//------------------------------------------------------
uint8_t DriveScreen::GetCV17AdrHighByte(uint16_t address) 
{
  if (address > 99) address |= 0xC000;  // Check for long address
  return highByte(address);
}

//------------------------------------------------------
// Gets the CV18 (address low byte)
//------------------------------------------------------
uint8_t DriveScreen::GetCV18AdrLowByte(uint16_t address) 
{
  return lowByte(address);
}

//------------------------------------------------------
// Gets locomotive information
//------------------------------------------------------
void DriveScreen::GetEngineInfo()
{
//  pideInfoLoco       = false;
//  pedirFuncPendiente = true;

  disp.xpn.getLocoInfo(GetCV17AdrHighByte(engine.address), GetCV18AdrLowByte(engine.address));
}

//------------------------------------------------------
// Gets functions information
//------------------------------------------------------
void DriveScreen::GetEngineFuncs()
{
//  pideInfoFunc = false;

  disp.xpn.getLocoFunc(GetCV17AdrHighByte(engine.address), GetCV18AdrLowByte(engine.address));
}

//------------------------------------------------------
// Gets speed steps (for encoder)
//------------------------------------------------------
uint8_t DriveScreen::GetSpeedMax(uint8_t steps)
{
  switch (steps) 
  { 
    case SPEED_STEPS_14:  return 14;
    case SPEED_STEPS_28:  return 28;
    case SPEED_STEPS_128: return 126;
  }
}

//------------------------------------------------------
// Set speed
//------------------------------------------------------
void DriveScreen::SetEngineSpeed(uint8_t speed)
{ 
  int velocidad;
  engine.speed = speed;

  // nos saltamos el paso de parada de emergencia
  switch (engine.steps) 
  { 
    case SPEED_STEPS_14:
    case SPEED_STEPS_128:
      if (speed > 0) 
        velocidad = speed + 1;
      else           
        velocidad = 0;
      break;

    case SPEED_STEPS_28:        // ponemos los 28 pasos en su formato
      if (speed > 0)            // pasamos velocidad entre 0 y 31 (0 0 0 S4 S3 S2 S1 S0)
        velocidad = speed + 3;  // nos saltamos pasos parada de emergencia
      else
        velocidad = 0;
      bitWrite(velocidad, 5, bitRead(velocidad, 0));  // copia bit 0 (0 0 S0 S4 S3 S2 S1 S0)
      velocidad >>= 1;                                // coloca en su sitio (0 0 0 S0 S4 S3 S2 S1)
      break;
  }

  if (engine.direction) // añade el sentido
    velocidad |= 0x80;
    
  disp.xpn.setLocoDrive(GetCV17AdrHighByte(engine.address), GetCV18AdrLowByte(engine.address), engine.steps, velocidad);
}

//------------------------------------------------------
// Sets function status
//------------------------------------------------------
void DriveScreen::ToggleEngineFunction(uint8_t funcNum)
{
  if (bitRead(engine.func.Bits, funcNum)) 
  {
    disp.xpn.setLocoFunc(GetCV17AdrHighByte(engine.address), GetCV18AdrLowByte(engine.address), FUNC_OFF, funcNum);
    bitClear(engine.func.Bits, funcNum);
  } 
  else 
  {
    disp.xpn.setLocoFunc(GetCV17AdrHighByte(engine.address), GetCV18AdrLowByte(engine.address), FUNC_ON, funcNum);
    bitSet(engine.func.Bits, funcNum);
  }
}

void DriveScreen::HandleEngineNotify(uint8_t adrHigh, uint8_t adrLow, uint8_t steps, uint8_t speed, uint8_t dir, uint8_t F0, uint8_t F1, uint8_t F2, uint8_t F3)
{
  // Check if engine address is the controlled engine
  uint16_t engineAdr = ((adrHigh << 8) & 0x3F) + adrLow;
  if (engineAdr != engine.address) 
    return;

  engine.direction = dir;
  engine.steps     = steps;

  // ajusta mi Velocidad segun los pasos
  switch (steps) 
  { 
    case SPEED_STEPS_14:
    case SPEED_STEPS_128:
      engine.speed = speed - 1;               // remove the emergency stop step
      break;
    case SPEED_STEPS_28:                      // Mover bits a su sitio (0 0 0 S0 S4 S3 S2 S1)
      speed <<= 1;                            // Hacemos sitio para el bit (0 0 S0 S4 S3 S2 S1 0 )
      bitWrite(speed, 0, bitRead(speed, 5));  // colocamos bit (0 0 S0 S4 S3 S2 S1 S0)
      speed &= 0x1F;                          // Limpiamos (0 0 0 S4 S3 S2 S1 S0);
      engine.speed = speed - 3;               // remove the emergency stop step
      break;
  }

  if (engine.speed > 127) 
    engine.speed = 0;

  engine.func.Xpress[3] = F3;               // F3: F28 F27 F26 F25 F24 F23 F22 F21
  engine.func.Xpress[2] = F2;               // F2: F20 F19 F18 F17 F16 F15 F14 F13
  engine.func.Xpress[1] = F1;               // F1: F12 F11 F10 F9 F8 F7 F6 F5
  engine.func.Xpress[0] = F0 << 4;          // F0: F4 F3 F2 F1 0 0 0 0
    
  if (bitRead(F0, 4))                       // ponemos F0: x x x F0 F4 F3 F2 F1 asi F4 F3 F2 F1 F0 x x x para reordenarlos
    bitSet(engine.func.Xpress[0], 3);       // F4 F3 F2 F1 F0 0 0 0

  engine.func.Bits = engine.func.Bits >> 3; // desplazamos los 29 bits a su sitio: 000F28F27...F0
}
//----------------------------------------------
// Handle central status notifications
//----------------------------------------------
void DriveScreen::HandleMasterStatusNotify(uint8_t status)
{
  xpnMasterStatus = status;
  
  switch (xpnMasterStatus) 
  {
    case csNormal: // Al entrar en modo normal mostramos la direccion de nuestra locomotora
//      miModo = NORMAL; // pedimos informacion de la locomotora por si ha cambiado
//      mostrarNumero(miLocomotora, 4);
//      encoderMax = GetSpeedMax(engine.steps);
//      encoderValor = engine.speed;
//      pideInfoLoco = true;
      break;
    case csShortCircuit: // Corto circuito - OFF
    case csTrackVoltageOff: // Sin tension en via - OFF
//      digitos[MILES] = 0;
//      digitos[CENTENAS] = CH_F;
//      digitos[DECENAS] = CH_F;
//      digitos[UNIDADES] = CH_ESPACIO;
//      miModo = ERROR_XN;
      break;
    case csEmergencyStop: // Parada emergencia - StoP
//      digitos[MILES] = 5;
//      digitos[CENTENAS] = CH_t;
//      digitos[DECENAS] = CH_o;
//      digitos[UNIDADES] = CH_P;
//      miModo = ERROR_XN;
      break;
    case csServiceMode: // Programacion en modo servicio - Pro
//      digitos[MILES] = CH_P;
//      digitos[CENTENAS] = CH_r;
//      digitos[DECENAS] = CH_o;
//      digitos[UNIDADES] = CH_ESPACIO;
//      miModo = ERROR_XN;
      break;
  }
}
