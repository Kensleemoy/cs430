CC		:= gcc
CFLAGS	:= -std=c99 -Wall -Wextra -g
RANDFLAGS := -std=gnu99 -Wall -Wextra -g
OMPFLAG := -fopenmp

BIN		:= ./bin
SRC		:= ./src
OUTPUT	:= ./output
TEST	:= ./test/
TESTOUTPUT := ./test/testOutput

all: mandelbrot mandelbrot-omp mandelbrot-cuda

mandelbrot: $(SRC)/mandelbrot.c Makefile
	$(CC) $(CFLAGS) $(SRC)/mandelbrot.c -o $(BIN)/mandelbrot

mandelbrot-omp: $(SRC)/mandelbrot-omp.c Makefile
	$(CC) $(CFLAGS) $(OMPFLAG) $(SRC)/mandelbrot-omp.c -o $(BIN)/mandelbrot-omp

mandelbrot-cuda: $(SRC)/mandelbrot-cuda.cu Makefile
	nvcc $(SRC)/mandelbrot-cuda.cu -o $(BIN)/mandelbrot-cuda

tests:
	-$(TEST)/unit_tests.sh test_logs.txt

clean: 
	-rm -f $(BIN)/*
	-rm -f $(OUTPUT)/*

cleanTests:
	-rm -f $(TESTOUTPUT)/*
	-rm -f diff.out
	-rm -f test_logs.txt
	-rm -f log_slurm.*
