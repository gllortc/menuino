//------------------------------------------------------------------
// Library includes
//------------------------------------------------------------------

#include <EncoderMenuSwitch.h>
#include <OpenSmart32.h>
#include <XpnManager.h>
#include "Menuino.h"

// PIN definicitons
#define BOARD_LED           13

#define ENCODER_PIN_A       25
#define ENCODER_PIN_B       27
#define ENCODER_PIN_SWITCH  29

#define XPN_PIN_TXRX        31

// Hardware declarations
OpenSmart32       display;
EncoderMenuSwitch encoder;
XpnManager*       xpn;

// MENUino declaration
Menuino           menuino;

//------------------------------------------------------------------
// Arduino main routines
//------------------------------------------------------------------

void setup()
{
  // Shut down board LED
  pinMode(BOARD_LED, OUTPUT);
  digitalWrite(BOARD_LED, HIGH); 

  Serial.begin(115200);

  display.Initialize();
  encoder.Initialize(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_PIN_SWITCH);

  xpn = XpnManager::getInstance();
  xpn->Initialize(XPN_PIN_TXRX);

  menuino.Initialize(&display);
}
 
void loop()
{
  xpn->Dispatch();
  display.Dispatch();
  encoder.Dispatch();
}

//----------------------------------------------
// Display click callback
//----------------------------------------------
void OnDisplayClick(uint16_t xpos, uint16_t ypos)
{
  menuino.HandleDisplayClick(xpos, ypos);
}

//----------------------------------------------
// Encoder movement callback
//----------------------------------------------
void OnEncoderMoved(EncoderMenuSwitch::EncoderDirection dir)
{
  menuino.HandleEncoderMoved(dir);
}

//----------------------------------------------
// Encoder click callback
//----------------------------------------------
void OnEncoderClick()
{
  menuino.HandleEncoderClick();
}

//------------------------------------------------------
// XPN Callback: XPN connection stablished
//------------------------------------------------------
void OnXpnMasterConnected()
{
  OnXpnPowerChanged(xpn->GetPowerStatus());
}

//------------------------------------------------------
// XPN Callback: XPN power notification
//------------------------------------------------------
void OnXpnPowerChanged(uint8_t state) 
{
  menuino.HandleMasterStatusNotify(state);
}

//------------------------------------------------------
// XPN Callback: Locomotive status notification
//------------------------------------------------------
void OnXpnEngineChanged(XpnEngine *engine)
{
  menuino.HandleEngineNotify(engine);
}

//------------------------------------------------------
// XPN Callback: network status notification
//------------------------------------------------------
void OnXpnNetworkStatus(uint8_t state) 
{
  // TODO: should be a separate LED in the controller
  digitalWrite(LED_BUILTIN, state); 
}



 
