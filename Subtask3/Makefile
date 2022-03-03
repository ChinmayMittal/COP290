# -*- MakeFile -*-

# target: dependencies
# 	action

CXX = g++

MKL_LIB_DIR = /opt/intel/oneapi/mkl/2022.0.2/lib/intel64
MKL_INCLUDE_DIR = /opt/intel/oneapi/mkl/2022.0.2/include

CPPFLAGS = -g -Wall -I$(MKL_INCLUDE_DIR)
LDFLAGS = -g -L$(MKL_LIB_DIR) -Wl,-rpath,$(MKL_LIB_DIR)

MKL_LIB = -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

RANDOM_MAT = randomMat.out
objects_random_mat = genRandom.o matrixio.o randomMain.o validators.o

MAIN_EXEC = yourcode.out
objects_main_exec = file.o latency_others.o matarr.o matrixAlgebra.o matrixio.o mklopt.o pooling.o pthreadopt.o relu.o sigmoid.o softmax.o tanh.o timing.o validators.o vectorio.o

NN_exec = NN.out
objects_NN_exec = ann.o vectorio.o mklopt.o relu.o softmax.o validators.o matarr.o timing.o matrixAlgebra.o

all: $(RANDOM_MAT) $(MAIN_EXEC) $(NN_exec)

$(RANDOM_MAT): $(objects_random_mat)
	$(CXX) $(LDFLAGS) -o $(RANDOM_MAT) $(objects_random_mat)

$(MAIN_EXEC): $(objects_main_exec)
	$(CXX) $(LDFLAGS) -o $(MAIN_EXEC) $(objects_main_exec) $(MKL_LIB)

$(NN_exec): $(objects_NN_exec)
	$(CXX) $(LDFLAGS) -o $(NN_exec) $(objects_NN_exec) $(MKL_LIB)

ann.o: optimization.h vectorio.h relu.h softmax.h matarr.h

file.o: relu.h tanh.h sigmoid.h softmax.h pooling.h matrixio.h vectorio.h matrixAlgebra.h optimization.h validators.h timing.h latency_others.h

file2.o: matrixio.h optimization.h latency_openblas.h

genRandom.o: genRandom.h

latency_others.o: latency_others.h latency_consts.h matrixAlgebra.h matrixio.h optimization.h timing.h

matarr.o: matarr.h

matrixAlgebra.o: matrixAlgebra.h

matrixio.o: matrixio.h validators.h

mklopt.o: optimization.h matarr.h timing.h

pooling.o: pooling.h

pthreadopt.o: optimization.h timing.h

randomMain.o: genRandom.h matrixio.h

relu.o: relu.h

sigmoid.o: sigmoid.h

softmax.o: softmax.h

tanh.o: tanh.h

timing.o: timing.h

validators.o: validators.h

vectorio.o: vectorio.h validators.h

clean:
	rm *.o $(RANDOM_MAT) $(MAIN_EXEC) $(NN_exec)