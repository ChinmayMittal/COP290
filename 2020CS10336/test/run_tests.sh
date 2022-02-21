#!/bin/sh
cd ..
make clean
make

./yourcode.out fullyconnected test/matrix.txt test/weight.txt test/bias.txt test/naive_out.txt
./yourcode.out fullyconnected test/matrix.txt test/weight.txt test/bias.txt test/pthread_out.txt pthread
./yourcode.out fullyconnected test/matrix.txt test/weight.txt test/bias.txt test/mkl_out.txt mkl
./openblas_mm.out fullyconnected test/matrix.txt test/weight.txt test/bias.txt test/openblas_out.txt openblas

./randomMat.out mult 3 10
./randomMat.out mult 3 20
./randomMat.out mult 3 50
./randomMat.out mult 3 100
./randomMat.out mult 3 200

./yourcode.out calclatency
./openblas_mm.out calclatency

gnuplot ./gen_plots.plt