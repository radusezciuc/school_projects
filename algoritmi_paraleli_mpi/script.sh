#!/bin/bash

$procese=$1
$fileIn=$2
$fileOut=$3

module load libraries/openmpi-1.6-gcc-4.4.6
mpirun -np $procese ./sursa $fileIn $fileOut 

