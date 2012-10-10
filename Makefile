TARGET=host.exe
UNCOMPRESSED=host_uc.exe
OBJECTS=host.o win32kbd.o

$(TARGET): $(UNCOMPRESSED)
	rm -f $@
	upx --best -o $@ $<

$(UNCOMPRESSED): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) $(UNCOMPRESSED)

.PHONY: clean all
