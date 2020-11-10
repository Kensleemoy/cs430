#!/bin/bash

#SBATCH -J OpenMP_TEST     # job name
#SBATCH -o log_slurm_serial.txt   # output and error file name (%j expands to jobID)
#SBATCH -n 4               # total number of tasks requested
#SBATCH -N 1 		   # number of nodes you want to run on	
#SBATCH -p classroom       # queue (partition) -- defq, eduq, gpuq, shortq
#SBATCH -t 00:05:00        # run time (hh:mm:ss) - ...

# Generally needed modules:
module load slurm
module load gcc

# Execute the program

#export OMP_NUM_THREADS=28

./bin/piLeib 1000
./bin/piLeib 2000
./bin/piLeib 3000
./bin/piLeib 4000
./bin/piLeib 5000

./bin/piLeib 10000
./bin/piLeib 20000
./bin/piLeib 30000
./bin/piLeib 40000
./bin/piLeib 50000

./bin/piLeib 100000
./bin/piLeib 200000
./bin/piLeib 300000
./bin/piLeib 400000
./bin/piLeib 500000

./bin/piLeib 1000000
./bin/piLeib 2000000
./bin/piLeib 3000000
./bin/piLeib 4000000
./bin/piLeib 5000000

## Some examples:
# mpirun python3 script.py

# Exit if mpirun errored:
status=$?
if [ $status -ne 0 ]; then
    exit $status
fi

# Do some post processing.
