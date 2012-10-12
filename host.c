#include <stdint.h>
#include <stdio.h>

#include "win32kbd.h"

/*
 * Send a 2-bit frame by settings Num Lock to bit 0 and Caps Lock to bit 1.
 * Toggling Scroll Lock acts as a clock signal.
 */
void send_frame(const uint8_t frame) {
	set_lock(NUM,  (frame & 0x01) == 0x01);
	set_lock(CAPS, (frame & 0x02) == 0x02);
	set_lock(SCROLL, 1);
	printf("sending frame 0x%02x...", frame);
	printf("got 0x%02x from getchar\n", getchar());
	toggle_key(SCROLL);
}

/* Send an 8-bit byte from LSB to MSB */
void send_byte(uint8_t data) {
	printf("sending byte 0x%02x\n", data);
	uint8_t i;
	for (i = 0; i < 4; i++) {
		send_frame(data);
		data >>= 2;
	}
}

/* Send len bytes from data */
void send_bytes(const uint8_t *data, const int len) {
	int i;
	for (i = 0; i < len; i++) {
		send_byte(data[i]);
	}
}

int main(int argc, char** argv) {
	return 0;
}
