CC		:= gcc
CFLAGS	:= -std=c11 -Wall -Wextra -g
MPI		:= mpicc

BIN		:= ./bin
SRC		:= ./src
INCL 	:= ./include
LIB		:= ./lib
OUTPUT	:= ./output
TEST	:= ./test/
TESTOUTPUT := ./test/testOutput

all: piLeib piMonte mv mm mm-mpi fibonacci

piLeib: $(SRC)/piLeib.c Makefile
	$(CC) $(CFLAGS) $(SRC)/piLeib.c -o $(BIN)/piLeib

piMonte: $(SRC)/piMonte.c Makefile
	$(CC) $(CFLAGS) $(SRC)/piMonte.c -o $(BIN)/piMonte

mv: $(SRC)/mv.c $(LIB)/mmio.c Makefile
	$(CC) $(CFLAGS) $(SRC)/mv.c $(LIB)/mmio.c -o $(BIN)/mv

mm: $(SRC)/mm.c $(LIB)/mmio.c Makefile
	$(CC) $(CFLAGS) $(SRC)/mm.c $(LIB)/mmio.c -o $(BIN)/mm

mm-mpi: $(SRC)/mm-mpi.c Makefile
	$(MPI) $(CFLAGS) $(SRC)/mm-mpi.c -o $(BIN)/mm-mpi -lm

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