#ifndef _WIN32_KBD_H_
#define _WIN32_KBD_H_

#include <windows.h>
#include <stdint.h>

#define NUM VK_NUMLOCK
#define SCROLL VK_SCROLL
#define CAPS VK_CAPITAL

void toggle_key(const BYTE key);
uint8_t check_state(const BYTE key);
void set_lock(const BYTE key, const uint8_t state);

#endif /* _WIN32_KBD_H_ */
