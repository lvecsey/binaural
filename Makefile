
CC=gcc

LIBS=-lm

CFLAGS=-O3 -Wall -g -pg

all : binaural binaural.raw binaural.wav binaural2 binaural2.raw binaural2.wav

%.wav : %.raw
	@sox --bits 64 --encoding floating-point --show-progress --channels 2 --rate 192000 $^ --bits 32 --encoding signed-integer --rate 48000 $@

binaural.raw : binaural
	@./$^ $@

binaural : binaural.o
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS) $(LIBS)

binaural2.raw : binaural2
	@./$^ $@

binaural2 : binaural2.o
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS) $(LIBS)

