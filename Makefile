CC		:= gcc
CFLAGS	:= -std=c99 -Wall -Wextra -g

BIN		:= ./bin
SRC		:= ./src
INCL 	:= ./include
LIB		:= ./lib
IO		:= ./IOfiles

all: piLeib piMonte mv mm fibonacci

piLeib: $(SRC)/piLeib.c Makefile
	$(CC) $(CFLAGS) $(SRC)/piLeib.c -o $(BIN)/piLeib

piMonte: $(SRC)/piMonte.c Makefile
	$(CC) $(CFLAGS) $(SRC)/piMonte.c -o $(BIN)/piMonte

mv: $(SRC)/mv.c Makefile
	$(CC) $(CFLAGS) $(SRC)/mv.c -o $(BIN)/mv

mm: $(SRC)/mm.c $(LIB)/mmio.c Makefile
	$(CC) $(CFLAGS) $(SRC)/mm.c $(LIB)/mmio.c -o $(BIN)/mm

fibonacci: $(SRC)/fibonacci.c Makefile
	$(CC) $(CFLAGS) $(SRC)/fibonacci.c -o $(BIN)/fibonacci

clean: 
	-rm -f $(BIN)/*
	-rm -f $(IO)/*