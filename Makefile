CC		:= gcc
CFLAGS	:= -std=c99 -Wall -Wextra -g
CFLAGSOMP  := $(CFLAGS) -fopenmp

BIN		:= ./bin
SRC		:= ./src
INCL 	:= ./include
LIB		:= ./lib
OUTPUT	:= ./output
TEST	:= ./test/
TESTOUTPUT := ./test/testOutput

all: piLeib piMonte mv mm fibonacci mv-openmp piLeib_openmp

piLeib_openmp: $(SRC)/piLeib_openmp.c Makefile
	$(CC) $(CFLAGS) -fopenmp $(SRC)/piLeib_openmp.c -o $(BIN)/piLeib_openmp

piLeib: $(SRC)/piLeib.c Makefile
	$(CC) $(CFLAGS) $(SRC)/piLeib.c -o $(BIN)/piLeib

piMonte: $(SRC)/piMonte.c Makefile
	$(CC) $(CFLAGS) $(SRC)/piMonte.c -o $(BIN)/piMonte

mv: $(SRC)/mv.c $(LIB)/mmio.c Makefile
	$(CC) $(CFLAGS) $(SRC)/mv.c $(LIB)/mmio.c -o $(BIN)/mv

mv-openmp: $(SRC)/mv-openmp.c $(LIB)/mmio.c Makefile
	$(CC) $(CFLAGSOMP) $(SRC)/mv-openmp.c $(LIB)/mmio.c -o $(BIN)/mv-openmp

mm: $(SRC)/mm.c $(LIB)/mmio.c Makefile
	$(CC) $(CFLAGS) $(SRC)/mm.c $(LIB)/mmio.c -o $(BIN)/mm

fibonacci: $(SRC)/fibonacci.c Makefile
	$(CC) $(CFLAGS) $(SRC)/fibonacci.c -o $(BIN)/fibonacci

tests:
	-$(TEST)/unit_tests.sh test_logs.txt

clean: 
	-rm -f $(BIN)/*
	-rm -f $(OUTPUT)/*

cleanTests:
	-rm -f $(TESTOUTPUT)/*
	-rm -f diff.out
	-rm -f test_logs.txt
