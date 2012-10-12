#include "win32kbd.h"

/* http://support.microsoft.com/kb/177674 */

void toggle_key(const BYTE key) {
	keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void set_lock(const BYTE key, const uint8_t state) {
	while (GetKeyState(key) != state) {
		toggle_key(key);
	}
}
