src = $(wildcard *.c)
obj = $(src:.c=.o)

CC = gcc
LDFLAGS = -lGL -lpng -lz -lm

network: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) network