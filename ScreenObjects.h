#ifndef _SCREENOBJECTS_H 
#define _SCREENOBJECTS_H 

// Screen IDs
#define SCR_MENU_ID    1
#define SCR_SELECT_ID  2
#define SCR_DRIVE_ID   3
#define SCR_ADDRESS_ID 4
#define SCR_MESSAGE_ID 5

//---------------------------------------------------------
// Icons used outside the classes
//---------------------------------------------------------

const uint8_t BMP_MENU[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xff, 0xf8, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1f, 0xff, 0xf8, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1f, 0xff, 0xf8, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//---------------------------------------------------------
// Icons used inside classes
//---------------------------------------------------------

const uint8_t BMP_INFO[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x01, 0xff, 0x80, 0x07, 0x81, 0xe0, 0x0e, 
  0x00, 0x70, 0x0c, 0x00, 0x30, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x30, 0x00, 0x0c, 0x30, 0x00, 
  0x0c, 0x30, 0x18, 0x0c, 0x30, 0x18, 0x0c, 0x30, 0x18, 0x0c, 0x30, 0x18, 0x0c, 0x18, 0x18, 0x18, 
  0x18, 0x18, 0x18, 0x0c, 0x00, 0x30, 0x0e, 0x00, 0x70, 0x07, 0x81, 0xe0, 0x01, 0xff, 0x80, 0x00, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_RETURN[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 
  0x38, 0x00, 0x00, 0x70, 0x00, 0x00, 0xe0, 0x00, 0x01, 0xc0, 0x00, 0x03, 0x80, 0x00, 0x07, 0x00, 
  0x00, 0x0f, 0xff, 0xf0, 0x0f, 0xff, 0xf0, 0x07, 0x00, 0x00, 0x03, 0x80, 0x00, 0x01, 0xc0, 0x00, 
  0x00, 0xe0, 0x00, 0x00, 0x70, 0x00, 0x00, 0x38, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_DELETE[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfe, 0x07, 0xff, 0xff, 0x0e, 
  0x00, 0x03, 0x0c, 0x00, 0x03, 0x18, 0x20, 0x43, 0x38, 0x70, 0xe3, 0x30, 0x39, 0xc3, 0x60, 0x1f, 
  0x83, 0xe0, 0x0f, 0x03, 0xe0, 0x0f, 0x03, 0x60, 0x1f, 0x83, 0x30, 0x39, 0xc3, 0x38, 0x70, 0xe3, 
  0x18, 0x20, 0x43, 0x0c, 0x00, 0x03, 0x0e, 0x00, 0x03, 0x07, 0xff, 0xff, 0x03, 0xff, 0xfe, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_OK[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x38, 0x00, 0x00, 0x70, 0x00, 0x00, 0xe0, 0x00, 0x01, 
  0xc0, 0x00, 0x03, 0x80, 0x08, 0x07, 0x00, 0x0c, 0x0e, 0x00, 0x0e, 0x1c, 0x00, 0x07, 0x38, 0x00, 
  0x03, 0xf0, 0x00, 0x01, 0xe0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_CANCEL[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 
  0x00, 0x40, 0x07, 0x00, 0xe0, 0x03, 0x81, 0xc0, 0x01, 0xc3, 0x80, 0x00, 0xe7, 0x00, 0x00, 0x7e, 
  0x00, 0x00, 0x3c, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x7e, 0x00, 0x00, 0xe7, 0x00, 0x01, 0xc3, 0x80, 
  0x03, 0x81, 0xc0, 0x07, 0x00, 0xe0, 0x02, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_LIGHT[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0xff, 0x00, 0x01, 0xc3, 0x80, 0x03, 
  0x81, 0xc0, 0x07, 0x00, 0xc0, 0x06, 0x00, 0x60, 0x06, 0x00, 0x60, 0x06, 0x00, 0x60, 0x06, 0x00, 
  0x60, 0x07, 0x00, 0xc0, 0x03, 0x81, 0xc0, 0x01, 0xc3, 0x80, 0x00, 0xc3, 0x00, 0x00, 0xc3, 0x00, 
  0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_BACK[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x7b, 0x00, 0x01, 0xe3, 
  0x00, 0x03, 0xc3, 0x00, 0x03, 0xc3, 0x00, 0x01, 0xe3, 0x00, 0x00, 0x7b, 0x00, 0x00, 0x3f, 0x00, 
  0x00, 0x0f, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_FAST_BACKWARD[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x20, 0x10, 0x00, 0x60, 0x30, 0x01, 0xe0, 0xf0, 0x03, 0xe1, 0xf0, 0x07, 0x63, 
  0xb0, 0x1e, 0x6f, 0x30, 0x1e, 0x6f, 0x30, 0x07, 0x63, 0xb0, 0x03, 0xe1, 0xf0, 0x01, 0xe0, 0xf0, 
  0x00, 0x60, 0x30, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_FORWARD[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x80, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xde, 0x00, 0x00, 0xc7, 
  0x80, 0x00, 0xc3, 0xc0, 0x00, 0xc3, 0xc0, 0x00, 0xc7, 0x80, 0x00, 0xde, 0x00, 0x00, 0xfc, 0x00, 
  0x00, 0xf0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_FAST_FORWARD[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x08, 0x04, 0x00, 0x0c, 0x06, 0x00, 0x0f, 0x07, 0x80, 0x0f, 0x87, 0xc0, 0x0d, 0xc6, 
  0xe0, 0x0c, 0xf6, 0x78, 0x0c, 0xf6, 0x78, 0x0d, 0xc6, 0xe0, 0x0f, 0x87, 0xc0, 0x0f, 0x07, 0x80, 
  0x0c, 0x06, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_DIR_BACK[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x80, 0x00, 0x07, 0x80, 0x00, 
  0x0f, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x78, 0x00, 0x00, 0xf0, 0x00, 0x01, 0xe0, 
  0x00, 0x03, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x01, 0xe0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x78, 0x00, 
  0x00, 0x3c, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x07, 0x80, 0x00, 0x03, 0x80, 0x00, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_DIR_FORWARD[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0xc0, 0x00, 0x01, 0xe0, 0x00, 0x00, 
  0xf0, 0x00, 0x00, 0x78, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x07, 
  0x80, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x07, 0x80, 0x00, 0x0f, 0x00, 0x00, 0x1e, 0x00, 
  0x00, 0x3c, 0x00, 0x00, 0x78, 0x00, 0x00, 0xf0, 0x00, 0x01, 0xe0, 0x00, 0x01, 0xc0, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t BMP_STOP[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x01, 0xff, 0x80, 0x03, 
  0x81, 0xc0, 0x07, 0x00, 0xe0, 0x0e, 0x00, 0x70, 0x1c, 0xc2, 0x38, 0x18, 0xe7, 0x18, 0x18, 0x7e, 
  0x18, 0x18, 0x3c, 0x18, 0x18, 0x3c, 0x18, 0x18, 0x7e, 0x18, 0x18, 0xe7, 0x18, 0x18, 0xc3, 0x38, 
  0x0c, 0x00, 0x70, 0x06, 0x00, 0xe0, 0x03, 0x01, 0xc0, 0x01, 0xff, 0x80, 0x00, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Screen object colors
#define COLOR_SCR_BACKGROUND            0x3186
#define COLOR_SCR_NOTIFYBAR_BACKGROUND  0x3186
#define COLOR_SCR_CAPTION_BACKGROUND    0x02B3
#define COLOR_SCR_CAPTION_TEXT          0xFFFF
#define COLOR_SCR_TEXT                  0xFFFF
#define COLOR_SCR_ERROR_TEXT            0xAA28

#define COLOR_BTN_NORMAL                0x0000
#define COLOR_BTN_PRESSED               0x1AAE
#define COLOR_BTN_TXT                   0xFFFF

#define COLOR_BTN_ERROR_NORMAL          0xD2C8
#define COLOR_BTN_ERROR_PRESSED         0xB226
#define COLOR_BTN_SUCCESS_NORMAL        0x85CF
#define COLOR_BTN_SUCCESS_PRESSED       0x64CB
#define COLOR_BTN_INFO_NORMAL           0x4459
#define COLOR_BTN_INFO_PRESSED          0x1B55
#define COLOR_BTN_WARNING_NORMAL        0xFDAA
#define COLOR_BTN_WARNING_PRESSED       0xE4A5

#define COLOR_TXT_BACKGROUND            0x39C7
#define COLOR_TXT_BORDER                0xF7BE

#endif