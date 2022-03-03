# -*- MakeFile -*-

# target: dependencies
# 	action

CXX = g++

MKL_LIB_DIR = /opt/intel/oneapi/mkl/2022.0.2/lib/intel64
MKL_INCLUDE_DIR = /opt/intel/oneapi/mkl/2022.0.2/include

OPENBLAS_LIB_DIR = /opt/OpenBLAS/lib
OPENBLAS_INCLUDE_DIR = /opt/OpenBLAS/include

CPPFLAGS = -g -Wall -I$(OPENBLAS_INCLUDE_DIR) -I$(MKL_INCLUDE_DIR)
LDFLAGS = -g -L$(OPENBLAS_LIB_DIR) -L$(MKL_LIB_DIR) -Wl,-rpath,$(OPENBLAS_LIB_DIR) -Wl,-rpath,$(MKL_LIB_DIR)

OPENBLAS_LIB = -lopenblas -lpthread
MKL_LIB = -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

RANDOM_MAT = randomMat.out
objects_random_mat = genRandom.o matrixio.o randomMain.o validators.o

MAIN_EXEC = yourcode.out
objects_main_exec = file.o latency_others.o matarr.o matrixAlgebra.o matrixio.o mklopt.o pooling.o pthreadopt.o relu.o sigmoid.o softmax.o tanh.o timing.o validators.o vectorio.o

OPENBLAS_EXEC = openblas_mm.out
objects_openblas_exec =  file2.o latency_openblas.o matarr.o matrixio.o openblasopt.o timing.o validators.o

all: $(RANDOM_MAT) $(MAIN_EXEC) $(OPENBLAS_EXEC) 

$(RANDOM_MAT): $(objects_random_mat)
	$(CXX) $(LDFLAGS) -o $(RANDOM_MAT) $(objects_random_mat)

$(MAIN_EXEC): $(objects_main_exec)
	$(CXX) $(LDFLAGS) -o $(MAIN_EXEC) $(objects_main_exec) $(MKL_LIB)

$(OPENBLAS_EXEC): $(objects_openblas_exec)
	$(CXX) $(LDFLAGS) -o $(OPENBLAS_EXEC) $(objects_openblas_exec) $(OPENBLAS_LIB)

file.o: relu.h tanh.h sigmoid.h softmax.h pooling.h matrixio.h vectorio.h matrixAlgebra.h optimization.h validators.h timing.h latency_others.h

file2.o: matrixio.h optimization.h latency_openblas.h

genRandom.o: genRandom.h

latency_openblas.o: latency_openblas.h latency_consts.h matrixio.h optimization.h

latency_others.o: latency_others.h latency_consts.h matrixAlgebra.h matrixio.h optimization.h timing.h

matarr.o: matarr.h

matrixAlgebra.o: matrixAlgebra.h

matrixio.o: matrixio.h validators.h

mklopt.o: optimization.h matarr.h timing.h

openblasopt.o: optimization.h matarr.h timing.h

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
	rm *.o $(RANDOM_MAT) $(MAIN_EXEC) $(OPENBLAS_EXEC)