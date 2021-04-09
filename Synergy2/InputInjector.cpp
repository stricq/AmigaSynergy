#include "InputInjector.hpp"

#include <libraries/keymap.h>

#include <proto/exec.h>

#include <stdio.h>


InputInjector *InputInjector::injector = NULL;


const int InputInjector::keyMap[256][4] = { // Linux Input, Windows Input, Mac Input, Amiga Output
  { 0x0000, 0x0000, 0x0000, 0xFF }, // No key
  { 0x0009, 0x0001, 0x0036, 0x45 }, // ESC
  { 0x0043, 0x003B, 0x007B, 0x50 }, // F1
  { 0x0044, 0x003C, 0x0079, 0x51 }, // F2
  { 0x0045, 0x003D, 0x0064, 0x52 }, // F3
  { 0x0046, 0x003E, 0x0077, 0x53 }, // F4
  { 0x0047, 0x003F, 0x0061, 0x54 }, // F5
  { 0x0048, 0x0040, 0x0062, 0x55 }, // F6
  { 0x0049, 0x0041, 0x0063, 0x56 }, // F7
  { 0x004A, 0x0042, 0x0065, 0x57 }, // F8
  { 0x004B, 0x0043, 0x0066, 0x58 }, // F9
  { 0x004C, 0x0044, 0x006E, 0x59 }, // F10
  { 0x005F, 0x0057, 0x0068, 0x4B }, // F11
  { 0x0060, 0x0058, 0x0070, 0x6F }, // F12
  { 0x0031, 0x0029, 0x0033, 0x00 }, // `
  { 0x000A, 0x0002, 0x0013, 0x01 }, // 1
  { 0x000B, 0x0003, 0x0014, 0x02 }, // 2
  { 0x000C, 0x0004, 0x0015, 0x03 }, // 3
  { 0x000D, 0x0005, 0x0016, 0x04 }, // 4
  { 0x000E, 0x0006, 0x0018, 0x05 }, // 5
  { 0x000F, 0x0007, 0x0017, 0x06 }, // 6
  { 0x0010, 0x0008, 0x001B, 0x07 }, // 7
  { 0x0011, 0x0009, 0x001D, 0x08 }, // 8
  { 0x0012, 0x000A, 0x001A, 0x09 }, // 9
  { 0x0013, 0x000B, 0x001E, 0x0A }, // 0
  { 0x0014, 0x000C, 0x001C, 0x0B }, // -
  { 0x0015, 0x000D, 0x0019, 0x0C }, // =
  { 0x0016, 0x000E, 0x0034, 0x41 }, // Backspace
  { 0x0017, 0x000F, 0x0031, 0x42 }, // Tab
  { 0x0018, 0x0010, 0x000D, 0x10 }, // Q
  { 0x0019, 0x0011, 0x000E, 0x11 }, // W
  { 0x001A, 0x0012, 0x000F, 0x12 }, // E
  { 0x001B, 0x0013, 0x0010, 0x13 }, // R
  { 0x001C, 0x0014, 0x0012, 0x14 }, // T
  { 0x001D, 0x0015, 0x0011, 0x15 }, // Y
  { 0x001E, 0x0016, 0x0021, 0x16 }, // U
  { 0x001F, 0x0017, 0x0023, 0x17 }, // I
  { 0x0020, 0x0018, 0x0020, 0x18 }, // O
  { 0x0021, 0x0019, 0x0024, 0x19 }, // P
  { 0x0022, 0x001A, 0x0022, 0x1A }, // [
  { 0x0023, 0x001B, 0x001F, 0x1B }, // ]
  { 0x0033, 0x002B, 0x002B, 0x2B }, // Backslash
  { 0x0042, 0x003A, 0x003A, 0x62 }, // Caps Lock (Special Handling)
  { 0x0026, 0x001E, 0x0001, 0x20 }, // A
  { 0x0027, 0x001F, 0x0002, 0x21 }, // S
  { 0x0028, 0x0020, 0x0003, 0x22 }, // D
  { 0x0029, 0x0021, 0x0004, 0x23 }, // F
  { 0x002A, 0x0022, 0x0006, 0x24 }, // G
  { 0x002B, 0x0023, 0x0005, 0x25 }, // H
  { 0x002C, 0x0024, 0x0027, 0x26 }, // J
  { 0x002D, 0x0025, 0x0029, 0x27 }, // K
  { 0x002E, 0x0026, 0x0026, 0x28 }, // L
  { 0x002F, 0x0027, 0x002A, 0x29 }, // ;
  { 0x0030, 0x0028, 0x0028, 0x2A }, // '
  { 0x0024, 0x001C, 0x0025, 0x44 }, // Return
  { 0x0032, 0x002A, 0x0039, 0x60 }, // Left Shift
  { 0x0034, 0x002C, 0x0007, 0x31 }, // Z
  { 0x0035, 0x002D, 0x0008, 0x32 }, // X
  { 0x0036, 0x002E, 0x0009, 0x33 }, // C
  { 0x0037, 0x002F, 0x000A, 0x34 }, // V
  { 0x0038, 0x0030, 0x000C, 0x35 }, // B
  { 0x0039, 0x0031, 0x002E, 0x36 }, // N
  { 0x003A, 0x0032, 0x002F, 0x37 }, // M
  { 0x003B, 0x0033, 0x002C, 0x38 }, // ,
  { 0x003C, 0x0034, 0x0030, 0x39 }, // .
  { 0x003D, 0x0035, 0x002D, 0x3A }, // /
  { 0x003E, 0x0036, 0x0039, 0x61 }, // Right Shift
  { 0x0025, 0x001D, 0x003C, 0x63 }, // Control (Left)
  { 0x0073, 0x015B, 0x0000, 0x66 }, // Left Amiga (Win)
  { 0x0040, 0x0038, 0x003B, 0x64 }, // Left Alt
  { 0x0041, 0x0039, 0x0032, 0x40 }, // Space Bar
  { 0x0071, 0x0138, 0x003B, 0x65 }, // Right Alt
  { 0x0074, 0x015C, 0x0038, 0x67 }, // Right Amiga (Win)
  { 0x0075, 0x015D, 0x0000, 0x6B }, // Menu
  { 0x006D, 0x011D, 0x003C, 0xFE }, // Control (Right)
  { 0x006F, 0x0137, 0x006A, 0x5F }, // Prt Scr/Sys Req
  { 0x004E, 0x0046, 0x006C, 0xFF }, // Scroll Lock
  { 0x006E, 0x0045, 0x0072, 0x6E }, // Pause/Break
  { 0x006A, 0x0152, 0x006B, 0x47 }, // Insert
  { 0x0061, 0x0147, 0x0074, 0x70 }, // Home
  { 0x0063, 0x0149, 0x0075, 0x48 }, // Page Up
  { 0x006B, 0x0153, 0x0076, 0x46 }, // Delete
  { 0x0067, 0x014F, 0x0078, 0x71 }, // End
  { 0x0069, 0x0151, 0x007A, 0x49 }, // Page Down
  { 0x0062, 0x0148, 0x007F, 0x4C }, // Cursor Up
  { 0x0064, 0x014B, 0x007C, 0x4F }, // Cursor Left
  { 0x0068, 0x0150, 0x007E, 0x4D }, // Cursor Down
  { 0x0066, 0x014D, 0x007D, 0x4E }, // Cursor Right
  { 0x004D, 0x0145, 0x0048, 0x79 }, // Num Lock (Special Handling)
  { 0x0070, 0x0135, 0x004C, 0x5C }, // Keypad /
  { 0x003F, 0x0037, 0x0044, 0x5D }, // Keypad *
  { 0x0052, 0x004A, 0x004F, 0x4A }, // Keypad -
  { 0x004F, 0x0047, 0x005A, 0x3D }, // Keypad 7
  { 0x0050, 0x0048, 0x005C, 0x3E }, // Keypad 8
  { 0x0051, 0x0049, 0x005D, 0x3F }, // Keypad 9
  { 0x0056, 0x004E, 0x0046, 0x5E }, // Keypad +
  { 0x0053, 0x004B, 0x0057, 0x2D }, // Keypad 4
  { 0x0054, 0x004C, 0x0058, 0x2E }, // Keypad 5
  { 0x0055, 0x004D, 0x0059, 0x2F }, // Keypad 6
  { 0x0057, 0x004F, 0x0054, 0x1D }, // Keypad 1
  { 0x0058, 0x0050, 0x0055, 0x1E }, // Keypad 2
  { 0x0059, 0x0051, 0x0056, 0x1F }, // Keypad 3
  { 0x005A, 0x0052, 0x0053, 0x0F }, // Keypad 0
  { 0x005B, 0x0053, 0x0042, 0x3C }, // Keypad .
  { 0x006C, 0x011C, 0x004D, 0x43 }, // Keypad Enter
  { 0x0000, 0x016D, 0x0000, 0xFF }, // Media
  { 0x0000, 0x0130, 0x0000, 0xFF }, // Volume Up
  { 0x0000, 0x012E, 0x0000, 0xFF }, // Volume Down
  { 0x0000, 0x0120, 0x0000, 0xFF }, // Mute
  { 0x0000, 0x0110, 0x0041, 0x76 }, // Previous
  { 0x0000, 0x0119, 0x0051, 0x77 }, // Next
  { 0x0000, 0x0122, 0x0050, 0x73 }, // Play/Pause
  { 0x0000, 0x0124, 0x0000, 0x72 }, // Stop
  { 0x0000, 0x0000, 0x0000, 0xFF }, // Finance
  { 0x0000, 0x0000, 0x0000, 0xFF }, // My Sites
  { 0x0000, 0x0000, 0x0000, 0xFF }, // Community
  { 0x0000, 0x0166, 0x0000, 0xFF }, // Favorites
  { 0x0000, 0x0000, 0x0000, 0xFF }, // iTouch
  { 0x0000, 0x016C, 0x0000, 0xFF }, // E-Mail
  { 0x0000, 0x0000, 0x0000, 0xFF }, // Shopping
  { 0x0000, 0x0165, 0x0000, 0xFF }, // Search
  { 0x0000, 0x0132, 0x0000, 0xFF }, // My Home
  { 0x0000, 0x016A, 0x0000, 0xFF }, // Previous (Web Page)
  { 0x0000, 0x0169, 0x0000, 0xFF }, // Go (to URL)
  { 0x0000, 0x0000, 0x0000, 0xFF }  // Array Filler
};


const int InputInjector::keyPad[20] = {       0x5C, 0x5D, 0x4A,
                                        0x3D, 0x3E, 0x3F, 0x5E,
                                        0x2D, 0x2E, 0x2F,
                                        0x1D, 0x1E, 0x1F, 0x43,
                                        0x0F,       0x3C       };


InputInjector *InputInjector::instance() {

  if (injector == NULL) injector = new InputInjector();

  return(injector);

}


InputInjector::InputInjector() :
  capsLock(false),
  numLock(false),
  qualDown(false),
  ignoreMouse(false),
  mouseQual(0),
  keybdQual(0),
  lastQual(0),
  keyMapIndex(0) {

  input = new Exec::InputDevice();

  for(int i = 0; i < 2; i++) prevCode[i] = prevQual[i] = 0;

}


InputInjector::~InputInjector() {

  delete input;

}


void InputInjector::injectMouse(int mouseX, int mouseY) {

  if (ignoreMouse) return;

  injectedEvent.setClass(IECLASS_POINTERPOS);
  injectedEvent.setSubClass(0);
  injectedEvent.setCode(IECODE_NOBUTTON);
  injectedEvent.setQualifier(mouseQual);
  injectedEvent.setX(mouseX);
  injectedEvent.setY(mouseY);

  input->writeEvent(injectedEvent);

}


void InputInjector::injectMouseWheel(int deltaY, int deltaX) {

  injectedEvent.setClass(IECLASS_MOUSEWHEEL);
  injectedEvent.setSubClass(0);
  injectedEvent.setCode(IECODE_NOBUTTON);
  injectedEvent.setQualifier(IEQUALIFIER_RELATIVEMOUSE);
  injectedEvent.setX(deltaX < 0 ? 1 : (deltaX > 0 ? -1 : 0));
  injectedEvent.setY(deltaY < 0 ? 1 : (deltaY > 0 ? -1 : 0));

  input->writeEvent(injectedEvent);
/*
  injectedEvent.setClass(IECLASS_RAWKEY);
  injectedEvent.setSubClass(0);
  injectedEvent.setCode(deltaY < 0 ? 0x7B : 0x7A);
  injectedEvent.setQualifier(IEQUALIFIER_RELATIVEMOUSE);
  injectedEvent.setX(0);
  injectedEvent.setY(0);

  input->writeEvent(injectedEvent);
*/
}


void InputInjector::injectMouseButton(int button, bool down) {

  mouseCode = IECODE_NOBUTTON;

  switch(button) {
    case 1: {
      if (down) {
        mouseQual |= IEQUALIFIER_LEFTBUTTON;
        mouseCode = IECODE_LBUTTON;
      }
      else {
        mouseQual &= ~IEQUALIFIER_LEFTBUTTON;
        mouseCode = IECODE_LBUTTON | IECODE_UP_PREFIX;
      }
      break;
    }
    case 2: {
      if (down) {
        mouseQual |= IEQUALIFIER_MIDBUTTON;
        mouseCode = IECODE_MBUTTON;
      }
      else {
        mouseQual &= ~IEQUALIFIER_MIDBUTTON;
        mouseCode = IECODE_MBUTTON | IECODE_UP_PREFIX;
      }
      break;
    }
    case 3: {
      if (down) {
        mouseQual |= IEQUALIFIER_RBUTTON;
        mouseCode = IECODE_RBUTTON;
      }
      else {
        mouseQual &= ~IEQUALIFIER_RBUTTON;
        mouseCode = IECODE_RBUTTON | IECODE_UP_PREFIX;
      }
      break;
    }
    case 4: {
      if (down) {
//      mouseQual |= IEQUALIFIER_4TH_BUTTON;  // <-- fixme
        mouseCode = IECODE_4TH_BUTTON;
      }
      else {
//      mouseQual &= ~IEQUALIFIER_4TH_BUTTON; // <-- fixme
        mouseCode = IECODE_4TH_BUTTON | IECODE_UP_PREFIX;
      }
      break;
    }
    case 5: {
      if (down) {
//      mouseQual |= IEQUALIFIER_5TH_BUTTON;  // <-- fixme
        mouseCode = IECODE_5TH_BUTTON;
      }
      else {
//      mouseQual &= ~IEQUALIFIER_5TH_RBUTTON; // <-- fixme
        mouseCode = IECODE_5TH_BUTTON | IECODE_UP_PREFIX;
      }
      break;
    }
  }

  injectedEvent.setClass(IECLASS_RAWMOUSE);
  injectedEvent.setSubClass(0);
  injectedEvent.setCode(mouseCode);
  injectedEvent.setQualifier(IEQUALIFIER_RELATIVEMOUSE | mouseQual | keybdQual);
  injectedEvent.setX(0);
  injectedEvent.setY(0);

  input->addEvent(injectedEvent);

  if (mouseCode & IECODE_UP_PREFIX) mouseCode = IECODE_NOBUTTON;

}


void InputInjector::injectKeyboard(int button, int, bool down) {

  uint16 rawKey = lookupRawkey(button);

//printf("key = 0x%04X\n", button);

  if (rawKey == 0x00FF) return;

  if (rawKey == 0x00FE) rawKey = RAWKEY_RCOMMAND;

  bool keyPad = lookupKeypad(rawKey);

  uint8 prev1Code = prevCode[0];
  uint8 prev1Qual = prevQual[0];
  uint8 prev2Code = prevCode[1];
  uint8 prev2Qual = prevQual[1];

  if (rawKey >= KEYCODE_FIRSTQUALIFIER && rawKey <= KEYCODE_LASTQUALIFIER) {
    if (down) {
      if (qualDown && lastQual == rawKey) return;
      else {
        qualDown = true;
        lastQual = rawKey;
        prev1Code = prev1Qual = prev2Code = prev2Qual = 0;
      }
    }
    else qualDown = false;
  }

  if (!down) {
    rawKey |= IECODE_UP_PREFIX;
    prev1Code = prev1Qual = prev2Code = prev2Qual = 0;
  }

  if (rawKey == RAWKEY_CAPSLOCK || rawKey == RAWKEY_NUMLOCK) return;

  if (rawKey == RAWKEY_LSHIFT) keybdQual |= IEQUALIFIER_LSHIFT;
  else if (rawKey == (RAWKEY_LSHIFT | IECODE_UP_PREFIX)) keybdQual &= ~IEQUALIFIER_LSHIFT;
  else if (rawKey == RAWKEY_RSHIFT) keybdQual |= IEQUALIFIER_RSHIFT;
  else if (rawKey == (RAWKEY_RSHIFT | IECODE_UP_PREFIX)) keybdQual &= ~IEQUALIFIER_RSHIFT;
  else if (rawKey == RAWKEY_LALT) keybdQual |= IEQUALIFIER_LALT;
  else if (rawKey == (RAWKEY_LALT | IECODE_UP_PREFIX)) keybdQual &= ~IEQUALIFIER_LALT;
  else if (rawKey == RAWKEY_RALT) keybdQual |= IEQUALIFIER_RALT;
  else if (rawKey == (RAWKEY_RALT | IECODE_UP_PREFIX)) keybdQual &= ~IEQUALIFIER_RALT;
  else if (rawKey == RAWKEY_LCOMMAND) keybdQual |= IEQUALIFIER_LCOMMAND;
  else if (rawKey == (RAWKEY_LCOMMAND | IECODE_UP_PREFIX)) keybdQual &= ~IEQUALIFIER_LCOMMAND;
  else if (rawKey == RAWKEY_RCOMMAND) keybdQual |= IEQUALIFIER_RCOMMAND;
  else if (rawKey == (RAWKEY_RCOMMAND | IECODE_UP_PREFIX)) keybdQual &= ~IEQUALIFIER_RCOMMAND;
  else if (rawKey == RAWKEY_LCTRL) keybdQual |= IEQUALIFIER_CONTROL;
  else if (rawKey == (RAWKEY_LCTRL | IECODE_UP_PREFIX)) keybdQual &= ~IEQUALIFIER_CONTROL;
  else if (rawKey == (RAWKEY_CAPSLOCK | IECODE_UP_PREFIX)) {
    capsLock = (capsLock ? false : true);
    if (capsLock) {
      rawKey = RAWKEY_CAPSLOCK;
      keybdQual |= IEQUALIFIER_CAPSLOCK;
    }
    else keybdQual &= ~IEQUALIFIER_CAPSLOCK;
  }
  else if (rawKey == (RAWKEY_NUMLOCK | IECODE_UP_PREFIX)) {
    numLock = (numLock ? false : true);
    if (numLock) rawKey = RAWKEY_NUMLOCK;
  }

  if (keyPad) keybdQual |= IEQUALIFIER_NUMERICPAD;
  else keybdQual &= ~IEQUALIFIER_NUMERICPAD;

  if ((keybdQual & (IEQUALIFIER_CONTROL | IEQUALIFIER_LCOMMAND | IEQUALIFIER_RCOMMAND)) == (IEQUALIFIER_CONTROL | IEQUALIFIER_LCOMMAND | IEQUALIFIER_RCOMMAND)) {
    IExec->ColdReboot();
  }

  if ((keybdQual & (IEQUALIFIER_CONTROL | IEQUALIFIER_LALT | IEQUALIFIER_RALT)) == (IEQUALIFIER_CONTROL | IEQUALIFIER_LALT | IEQUALIFIER_RALT)) {
    IExec->IceColdReboot();
  }

  injectedEvent.setClass(IECLASS_RAWKEY);
  injectedEvent.setSubClass(0);
  injectedEvent.setCode(rawKey);
  injectedEvent.setQualifier(keybdQual | IEQUALIFIER_RELATIVEMOUSE);
  injectedEvent.setPrev1DownCode(prev1Code);
  injectedEvent.setPrev1DownQual(prev1Qual);
  injectedEvent.setPrev2DownCode(prev2Code);
  injectedEvent.setPrev2DownQual(prev2Qual);

  input->addEvent(injectedEvent);

	if (down && (rawKey < KEYCODE_FIRSTQUALIFIER || rawKey > KEYCODE_LASTQUALIFIER)) {
    prevCode[1] = prevCode[0];
    prevCode[0] = rawKey;
    prevQual[1] = prevQual[0];
    prevQual[0] = keybdQual;
	}

}


uint16 InputInjector::lookupRawkey(int button) {

  for(int i = 0; i < 256; i++) if (keyMap[i][keyMapIndex] == button) return(keyMap[i][amigaIndex]);

  return(0x00FF);

}


bool InputInjector::lookupKeypad(uint16 rawKey) {

  for(int i = 0; i < 20; i++) if (keyPad[i] == rawKey) return(true);

  return(false);

}


void InputInjector::setQualifiers(uint16 qualifiers) {

  if (qualifiers & keyModCapsLock) keybdQual |= IEQUALIFIER_CAPSLOCK;
  else keybdQual &= ~IEQUALIFIER_CAPSLOCK;

  if (qualifiers & keyModNumLock) keybdQual |= IEQUALIFIER_NUMERICPAD;
  else keybdQual &= ~IEQUALIFIER_NUMERICPAD;

  if (!(qualifiers & keyModShift)) keybdQual &= ~(IEQUALIFIER_LSHIFT | IEQUALIFIER_RSHIFT);

  if (!(qualifiers & keyModControl)) keybdQual &= ~IEQUALIFIER_CONTROL;

  if (!(qualifiers & keyModAlt)) keybdQual &= ~(IEQUALIFIER_LALT | IEQUALIFIER_RALT);

  if (!(qualifiers & keyModWin)) keybdQual &= ~(IEQUALIFIER_LCOMMAND | IEQUALIFIER_RCOMMAND);

}

