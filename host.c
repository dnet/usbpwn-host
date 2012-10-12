/*
 * host.c - sends a file from a host to a USBpwn device
 *
 * Copyright (c) 2012 András Veres-Szentkirályi
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
	FILE *infile;
	uint32_t filepos, filelen;
	char inbuf, filelen_str[16];

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	infile = fopen(argv[1], "rb");
	if (!infile) {
		fprintf(stderr, "Cannot open file %s\n", argv[1]);
		return 1;
	}

	fseek(infile, 0, SEEK_END);
	filelen = ftell(infile);
	fseek(infile, 0, SEEK_SET);
	sprintf(filelen_str, "--%d--", filelen);
	send_bytes((uint8_t*)filelen_str, strlen(filelen_str));
	for (filepos = 0; filepos < filelen; filepos++) {
		fread(&inbuf, 1, 1, infile);
		send_byte(inbuf);
	}
	fclose(infile);

	printf("Sent bytes\n");
	return 0;
}
