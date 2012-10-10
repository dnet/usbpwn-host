TARGET=host.exe
UNCOMPRESSED=host_uc.exe
OBJECTS=host.o win32kbd.o

all: $(TARGET)

$(TARGET): $(UNCOMPRESSED)
	upx --best -o $@ $<

$(UNCOMPRESSED): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) $(UNCOMPRESSED)

.PHONY: clean all
