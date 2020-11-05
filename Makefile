CC		:= gcc
CFLAGS	:= -std=c99 -Wall -Wextra -g
OMPFLAGS := -fopenmp

BIN		:= ./bin
SRC		:= ./src
INCL 	:= ./include
LIB		:= ./lib
OUTPUT	:= ./output
TEST	:= ./test/
TESTOUTPUT := ./test/testOutput

all: piLeib piMonte mv mm omp-mm fibonacci 

piLeib: $(SRC)/piLeib.c Makefile
	$(CC) $(CFLAGS) $(SRC)/piLeib.c -o $(BIN)/piLeib

piMonte: $(SRC)/piMonte.c Makefile
	$(CC) $(CFLAGS) $(SRC)/piMonte.c -o $(BIN)/piMonte

mv: $(SRC)/mv.c $(LIB)/mmio.c Makefile
	$(CC) $(CFLAGS) $(SRC)/mv.c $(LIB)/mmio.c -o $(BIN)/mv

mm: $(SRC)/serial-mm.c $(LIB)/mmio.c Makefile
	$(CC) $(CFLAGS) $(SRC)/serial-mm.c $(LIB)/mmio.c -o $(BIN)/mm

omp-mm: $(SRC)/omp-mm.c $(LIB)/mmio.c Makefile
		$(CC) $(CFLAGS) $(OMPFLAGS) $(SRC)/omp-mm.c $(LIB)/mmio.c -o $(BIN)/omp-mm        

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
