## Group 3 <br />
Kenslee Moy, Nori Natsuhara, Shivani Singh, Monte Hedrick, Tung Ho

## INSTALLATION <br />
**Run all commands from the top level**

* To compile all programs at once, run:

    `make all`

* To compile a single program, run any of these options:

    `make piLeib`

    `make piLeib-openmp`
	
    `make piMonte`

    `make mc-openmp`
	
    `make fibonacci`

    `make fib-omp`
	
    `make mm`

    `make omp-mm`
	
    `make mv`

    `make mv-openmp`

## EXECUTION <br />
**Run all commands from the top level**

* To run Leibniz's Estimation, run:
   ` ./bin/piLeib <integer>`

* To run Leibniz's Estimation using OpenMP, run:
   ` sbatch slurm_piLeib_openmp.bash`

* To run Monte Carlo's Estimation, run:
   ` ./bin/piMonte`

* To run Monte Carlo's Estimation using OpenMP, run:
   ` sbatch slurm_mcopenmp.bash <natural long number>`

* To run Fibonacci, run:
   ` ./bin/fibonacci <natural integer number>`

* To run Fibonacci using OpenMP, run:
    ` sbatch slurm_fibomp.bash <natural integer number>`

* To run Matrix-Vector Multiplication, run:
    `./bin/mv <path to matrix .m file> <path to vector .m file> <path to output .m file>`
	
	NOTE: mv will only accept a .m file with the header:
        `%%MatrixMarket matrix array integer general`
    and with a column of size 1

    NOTE: mv will quit if matrix row size != vector column size

    NOTE: example acceptable files are provided in ./input/ or in the "format" secion of this README
    

* To run Matrix-Matrix Multiplication, run:

    `./bin/mm <path to 1st matrix .m file> <path to 2nd matrix.m file> <path to output .m file>`

    NOTE: mm will quit if the 1st matrix's column size != 2nd matrix's row size

    NOTE: example acceptable files are provided in ./input/ or in the "format" secion of this README
    
* To run Matrix-Vector Multiplication using OpenMP, run:
    `export OMP_NUM_THREADS=<desired number of threads>`
    `sbatch slurm_mvopenmp.bash <path to matrix .m file> <path to vector .m file> <path to output .m file> <num_threads>`
	
	NOTE: mv-openmp will only accept a .m file with the header:
        `%%MatrixMarket matrix array integer general`
    and with a column of size 1

    NOTE: mv-openmp will quit if matrix row size != vector column size

    NOTE: example acceptable files are provided in ./input/ or in the "format" secion of this README

* To run Matrix-Matrix Multiplication using OpenMP, run:

    `sbatch slurm_mm_openmp.bash <path to 1st matrix .m file> <path to 2nd matrix.m file> <path to output .m file> <num_threads>`

    NOTE: omp-mm will quit if the 1st matrix's column size != 2nd matrix's row size

    NOTE: example acceptable files are provided in ./input/ or in the "format" secion of this README

* To clean program, run:

    `make clean`

* To clean testing files, run:

   ` make cleanTests`

    NOTE: it is suggested to use this command before running tests to ensure output file contains 
        only the most recent logs

## TESTING <br />
**Run all commands from the top level**

* To test the toy problems, run: <br />
   ` ./test/unit_tests.sh <output file>`

   NOTE: it is recommended to run a `make clean` before running the tests

   NOTE: this will place all test logs in a top-level file in your specified file name

   NOTE: errors documents will be placed into test/testOutput/

* To alter input/output files, edit the `unit_tests.sh` file directly

## FORMATTING <br />
* Format of accepted Matrix .m files:
```c
    %%MatrixMarket matrix array integer general
    <row size integer> <column size integer>
    <value>
    <value>
    ...
    <value>
```

## PERFORMANCE <br />

* To run Leibniz's series using OpenMP thread(s), run:
    
    `make clean && make all && sbatch slurm_piLeib_perf_openmp.bash`
    
    NOTE: the macro 'PERFORMANCE' should be defined as 1 in src/piLeib-openmp.c for timer enabled.
   
    NOTE: the collected data can be found at output/log_leibniz_perf_openmp.txt.

* To run Leibniz's series using single Linux thread, run:
    
    `make clean && make all && sbatch slurm_piLeib_perf_serial.bash`
    
    NOTE: the macro 'PERFORMANCE' should be defined as 1 in src/piLeib.c for timer enabled.
    
    NOTE: the collected data can be found at output/log_leibniz_perf_serial.txt.
    
* To run Leibniz's series (i.e. OpenMP, Linux), run:
    
    `make clean && make all && sbatch slurm_piLeib_perf.bash`
    
    NOTE: the macro 'PERFORMANCE' should be defined as 1 in src/piLeib-openmp.c for timer enabled.
    
    NOTE: the macro 'PERFORMANCE' should be defined as 1 in src/piLeib.c for timer enabled.
    
    NOTE: the collected data can be found at output/log_leibniz_perf_openmp.txt.
    
    NOTE: the collected data can be found at output/log_leibniz_perf_serial.txt.

* Format of accepted Vector .m files:
```c
    %%MatrixMarket matrix array integer general
    <row size integer> 1
    <value>
    <value>
    ...
    <value>
```

## DESCRIPTION <br />
**piLeib** <br />
piLeib takes in an integer argument and estimates pi using Leibniz's Series. 
The result is printed to the console.

**piLeib-openmp** <br />
piLeib takes in an integer argument and estimates pi using Leibniz's Series. 
OpenMP is used to share the workload of the for-loop and reduce the result into
the chose variable. The result is printed to the console.

**piMonte** <br />
piMonte takes no parameters. It estimates pi using Monte Carlo's Pi
Estimation based upon 10 (hypothetical) darts. The result is printed to
the console.

**mc-openmp** <br />
mc-openmp takes in one parameter that tells the program how many darts to throw.
It estimates pi using Monte Carlo's Pi Estimation based upon the specified number
of darts. The result is printed to the console.

**fibonacci** <br />
fibonacci takes in a natural integer argument and calculates the nth
number in the Fibonacci sequence, based upon the given argument. The result
is printed to the console. 
NOTE: Fibonacci starts at fib(0) = 0, so to calculate the 
3rd term, it will display terms 0, 1, 1, 2, 3 to give you the fib(3) = 2.

**fib-omp** <br />
fib-omp takes in a natural integer argument and calculated the nth number in
the Fibonacci sequence. This calculates it sequentially starting with Fib(0)
and Fib(1) all the way to Fib(n) and shares the work using OpenMP parallel.
The result is then put into a log_slurm.txt file.

**mv** <br />
mv takes in a matrix .m file, a matrix .m file where the column size is 1, 
and an output file to write the resulting vector to. mv checks to see if the
given files can be multiplied together.

**mv-openmp** <br />
mv-openmp uses the number of threads specified by OMP_NUM_THREADS environment variable
to perform matrix vector multiplication. mv-openmp takes in a matrix .m file, a matrix 
.m file where the column size is 1, and an output file to write the resulting vector to.
mv-openmp checks to see if the given files can be multiplied together.

**mm** <br />
mm takes in a matix .m file, another matrix .m file, and an output file to
write the resulting matrix to. mm checks to see if the given matrices cna be
multiplied together.

**omp-mm** <br />
omp-mm takes in a matix .m file, another matirx .m file, and an output file to
write the resulting matrix to. omp-mm checks to see if the given matrices can be
multiplied together. Once valid matrices are read in, the program shares the work
via OpenMP parallel for actually multiplying the matrices themselves.

## RESOURCES <br />
[Leibniz formula](https://stackoverflow.com/questions/18036367/leibniz-formula-for-%CF%80-is-this-any-good-python "Leibniz formula")

[Checking for valid input](https://stackoverflow.com/questions/17292545/how-to-check-if-the-input-is-a-number-or-not-in-c "Checking for valid input")

[Monte Carlo formula](https://www.geeksforgeeks.org/estimating-value-pi-using-monte-carlo/ "Monte Carlo formula")

[Thread safe Pseudo-Random Number Generator](https://linux.die.net/man/3/rand_r "rand_r")

[Fibonacci formula](https://www.programiz.com/c-programming/examples/fibonacci-series "Fibonacci formula")

[Matrix Matrix multiply formula](https://www.programiz.com/python-programming/examples/multiply-matrix "Matrix Matrix multiply formula")

[Matrix Vector multiply](https://mathinsight.org/matrix_vector_multiplication "Matrix Vector multiply")

