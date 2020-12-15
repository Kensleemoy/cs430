#!/bin/bash

#SBATCH -J CUDA_TEST     # job name
#SBATCH -o log_slurm.o%j  # output and error file name (%j expands to jobID)
#SBATCH -n 1             # total number of tasks requested
#SBATCH -N 1 		  # number of nodes you want to run on	
#SBATCH -p classroomgpu  # queue (partition) -- defq, eduq, gpuq, shortq
#SBATCH -t 00:30:00       # run time (hh:mm:ss) - 12.0 hours in this example.
# Generally needed modules:
module load slurm
module load cuda10.0

# Execute the program
./bin/mandelbrot-cuda ./dumpTest/cuda.ppm

status=$?
if [ $status -ne 0 ]; then
    exit $status
fi

# Do some post processing.
