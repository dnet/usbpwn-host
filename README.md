USBpwn Windows host
===================

The purpose of this program is to send any (text or binary) file using the LEDs
on the keyboard (Num, Caps and Scroll lock). It uses standard C and Win32 API
calls and can be run without administrative privileges. The protocol used is
the following, implemented in `send_frame`:

 - the Num and Caps lock state is set to the first two bits to send (in this order)
 - the Scroll lock is turned on
 - the program waits for a newline
 - the Scroll lock is turned off

In other words, Scroll lock is used as a "clock signal", and at raising edge,
the two other LEDs can be sampled for data. The newline (that can be achieved
by the Enter/Return key) is the acknowledgement signal, making the protocol
fully synchronous. For example, sending the bits `1101` can be done in the
following way:

	            __________________________________
	   NUM ____/
	                               _______________
	  CAPS _______________________/
	                ______            ______
	SCROLL ________/      \__________/      \_____
	
	                  01                11

Bits are sent from LSB to MSB by `send_byte`, n bytes are sent from 0 to n-1 by
`send_bytes`. The main program sends the length of the transmission in bytes
using ASCII characters, surrounded by two dashes (`--`) before the raw data.

Usage
-----

	> host filename.bin

Compiling
---------

As only standard APIs are used, any decent C compiler can be used. The
`Makefile` takes care of dependencies, you just have to set the compiler
used, if you'd like to cross-compile, like me. For example, I used the
following commands to compile it under Debian Wheezy:

	# apt-get install mingw32
	$ CC=i586-mingw32msvc-gcc make

License
-------

The whole project is under MIT license.
