CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4) -Wall -pedantic -Wextra
LDFLAGS = $(shell $(PKGCONFIG) --libs gtk4)

MAIN = src
GUI = src/gui
UTILS = src/utils

SRC = $(GUI)/lunion-window.c $(GUI)/lunion-application.c $(UTILS)/system.c $(MAIN)/main.c

OBJS = $(SRC:.c=.o)



all: lunion

%.o: %.c
	@echo "INFO Generation du '.o' $(<)"
	$(CC) -o $(@) $(CFLAGS) -c $<

lunion: $(OBJS)
	$(CC) -o $(@F) $(^) $(LDFLAGS)

clean:
	@echo "-> Suppresion"
	rm -f $(OBJS)
	rm -f lunion
