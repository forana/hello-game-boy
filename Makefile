# override if your gbdk install isn't in a dumb place
GBDK_PATH ?= /gbdk

# set a path to an emulator to test with
EMU_PATH ?= bgb

# CC = ${GBDK_PATH}/bin/lcc -Wa-l -Wl-m -Wl-j
CC = ${GBDK_PATH}/bin/lcc

BIN = hello.gb

default: $(BIN)

%.o: %.c
	$(CC) -Wa-l -c -o $@ $<

%.s: %.c
	$(CC) -S -o $@ $<

%.o: %.s
	$(CC) -Wa-l -c -o $@ $<

%.gb: %.o
	$(CC) -Wl-m -Wl-yp0x134=0x48 -Wl-yp0x135=0x65 -Wl-yp0x136=0x6C -Wl-yp0x137=0x6C -Wl-yp0x138=0x6F -o $@ $<

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm || true

emu: $(BIN)
	$(EMU_PATH) $(BIN)
