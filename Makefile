target  = mse
sources = main.c $(target).c psnr.c
objects = $(patsubst %.c,%.o,$(sources))
CC = gcc
OPTS = -Wall -O2

all: $(objects)
	$(CC) $(OPTS) -o $(target) $(objects) -lm

$(target).o: $(target).c
	$(CC) $(OPTS) -c $<

psnr.o: psnr.c
	$(CC) $(OPTS) -c $<

clean:
	$(RM) $(target) $(objects)
