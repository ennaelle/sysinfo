CC=gcc
CFLAGS=-Wall -Wextra -I./src
SRC=src/sysinfo.c
DEST=sysinfo

all: lint build run

lint: $(SRC)
	$(CC) -fsyntax-only $(SRC)

build: $(SRC) 
	$(CC) $(CFLAGS) -o $(DEST) $(SRC)

run: $(DEST)
	./$(DEST)

clean:
	rm -f $(DEST)
