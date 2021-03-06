CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4 libadwaita-1) -Wall -pedantic -Wextra
LDFLAGS = $(shell $(PKGCONFIG) --libs gtk4 libadwaita-1)

SRC = src/lunion-window.c src/lunion-application.c src/system.c src/main.c

OBJS = $(SRC:.c=.o)



all: lunion

%.o: %.c
	@echo "[-] info:: Generation du '.o' $(<)"
	$(CC) -o $(@) $(CFLAGS) -c $<

lunion: $(OBJS)
	$(CC) -o $(@F) $(^) $(LDFLAGS)

clean:
	@echo "[-] info:: Suppresion"
	rm -f $(OBJS)
	rm -f lunion
