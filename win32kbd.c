#include "win32kbd.h"

/* http://support.microsoft.com/kb/177674 */

void toggle_key(const BYTE key) {
	keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

uint8_t check_state(const BYTE key) {
	BYTE keyState[256];
	GetKeyboardState(keyState);
	return keyState[key];
}

void set_lock(const BYTE key, const uint8_t state) {
	if (check_state(key) != state) {
		toggle_key(key);
	}
}
