CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0) -Wall -pedantic -Wextra
LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

MAIN = src
GUI = src/gui
UTILS = src/utils

SRC = $(GUI)/lunion-application.c $(GUI)/lunion-window.c $(UTILS)/system.c $(MAIN)/main.c
#BUILT_SRC = resources.c



all: lunion

%.o: %.c
	@echo "INFO Generation du '.o' $(<)"
	$(CC) -o $(@) $(CFLAGS) -c $<

lunion: $(OBJS)
	$(CC) -o $(@F) $(^) \
	 $(LIBS)

clean:
	@echo "-> Suppresion"
	rm -f $(OBJS)
	rm -f $(@F)
	rm -f lunion
