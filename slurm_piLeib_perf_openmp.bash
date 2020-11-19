#!/bin/bash

#SBATCH -J OpenMP_TEST     # job name
#SBATCH -o log_slurm_openmp.txt   # output and error file name (%j expands to jobID)
#SBATCH -n 4               # total number of tasks requested
#SBATCH -N 1 		   # number of nodes you want to run on	
#SBATCH -p classroom       # queue (partition) -- defq, eduq, gpuq, shortq
#SBATCH -t 00:05:00        # run time (hh:mm:ss) - ...

# Generally needed modules:
module load slurm
module load gcc

# Execute the program

#export OMP_NUM_THREADS=28

./bin/piLeib-openmp 1000
./bin/piLeib-openmp 2000
./bin/piLeib-openmp 3000
./bin/piLeib-openmp 4000
./bin/piLeib-openmp 5000

./bin/piLeib-openmp 10000
./bin/piLeib-openmp 20000
./bin/piLeib-openmp 30000
./bin/piLeib-openmp 40000
./bin/piLeib-openmp 50000

./bin/piLeib-openmp 100000
./bin/piLeib-openmp 200000
./bin/piLeib-openmp 300000
./bin/piLeib-openmp 400000
./bin/piLeib-openmp 500000

./bin/piLeib-openmp 1000000
./bin/piLeib-openmp 2000000
./bin/piLeib-openmp 3000000
./bin/piLeib-openmp 4000000
./bin/piLeib-openmp 5000000

## Some examples:
# mpirun python3 script.py

# Exit if mpirun errored:
status=$?
if [ $status -ne 0 ]; then
    exit $status
fi

# Do some post processing.
