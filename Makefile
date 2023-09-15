EXE := sliding-tile
INSTALL_PATH := /usr/local/bin/$(EXE)

SRCDIR := src

SOURCES := $(wildcard $(SRCDIR)/*.c)

CPPFLAGS := -I.
CFLAGS   := -Wall -std=c99
LDLIBS   := -lcurses

.PHONY: all clean install uninstall

all: $(EXE)

clean:
	$(RM) $(EXE)

install: all
	cp $(EXE) $(INSTALL_PATH)

uninstall:
	$(RM) $(INSTALL_PATH)

$(EXE): $(SOURCES)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
