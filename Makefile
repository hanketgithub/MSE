target  = mse
sources = main.c $(target).c psnr.c
objects = $(patsubst %.c,%.o,$(sources))
CC = gcc
OPTS = -Wall -O2
CP = cp

all: $(objects)
	$(CC) $(OPTS) -o $(target) $(objects) -lm

$(target).o: $(target).c
	$(CC) $(OPTS) -c $<

psnr.o: psnr.c
	$(CC) $(OPTS) -c $<

install:
	$(CP) $(target) /usr/local/bin

uninstall:
	$(RM) /usr/local/bin/$(target)

clean:
	$(RM) $(target) $(objects)
