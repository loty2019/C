CC = gcc
CFLAGS = -Wall -O2

all: myHuff

%: %.c 
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.out
