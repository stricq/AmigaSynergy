#ifndef INPUTINJECTOR_HPP
#define INPUTINJECTOR_HPP

#include "Exec/InputEvent.hpp"
#include "Exec/InputDevice.hpp"

#define KEYCODE_FIRSTQUALIFIER 0x60
#define KEYCODE_LASTQUALIFIER  0x6A

#define RAWKEY_NUMLOCK 0x79

using namespace RAPlus;


class InjectorException { };


class InputInjector {

  public:

   ~InputInjector();

    static InputInjector *instance();

    void injectMouse(int mouseX, int mouseY);
    void injectMouseButton(int button, bool down);
    void injectMouseWheel(int deltaY,int deltaX);

    void injectKeyboard(int button, int qualifier, bool down);

    void setQualifiers(uint16 qualifiers);

    void setOS(int os) { keyMapIndex = os; }

    void setIgnoreMouse(bool ignore) { ignoreMouse = ignore; }

    static const int OS_LINUX   = 0;
    static const int OS_WINDOWS = 1;
    static const int OS_MAC     = 2;
    static const int OS_AMIGA   = 3;

  private:

    InputInjector();

    uint16 lookupRawkey(int button);

    bool   lookupKeypad(uint16 rawKey);

    static InputInjector *injector;

    bool capsLock;
    bool numLock;

    bool qualDown;

    bool ignoreMouse;

    uint8  prevCode[2];
    uint8  prevQual[2];

    uint16 mouseCode;
    uint16 mouseQual;
    uint16 keybdQual;
    uint16 lastQual;

    int keyMapIndex;

    Exec::InputDevice *input;
    Exec::InputEvent   injectedEvent;

    static const int keyMap[256][4];

    static const int keyPad[20];

    static const int amigaIndex = OS_AMIGA;

    static const uint16	keyModShift    = 0x0001; // Codes taken from Synergy
    static const uint16	keyModControl  = 0x0002;
    static const uint16	keyModAlt      = 0x0004;
    static const uint16	keyModWin      = 0x0010;
    static const uint16	keyModCapsLock = 0x1000;
    static const uint16	keyModNumLock  = 0x2000;

};


#endif // INPUTINJECTOR_HPP

