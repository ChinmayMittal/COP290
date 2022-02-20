# -*- MakeFile -*-

# target: dependencies
# 	action

CXX = g++

COMPILER_FLAGS = -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl
MKL_LIB_DIRI = /opt/intel/oneapi/mkl/2022.0.2/lib/intel64
MKL_INCLUDE_DIRI = /opt/intel/oneapi/mkl/2022.0.2/include

CPPFLAGS = -g -Wall
LDFLAGS = -g -Llibs/openblas/lib -Wl,-rpath,libs/openblas/lib
LDLIBS = -lopenblas -lpthread

objects_test_openblas = openblas_mm.o
TEST_OPENBLAS = openblas_mm.out

RANDOM_MAT = randomMat.out
objects_random_mat = randomMain.o validators.o

all: yourcode.out openblas_mm.out $(RANDOM_MAT)

$(RANDOM_MAT): $(objects_random_mat)
	$(CXX) $(LDFLAGS) -o $(RANDOM_MAT) $(objects_random_mat) $(LDLIBS)

yourcode.out: file.o relu.o tanh.o sigmoid.o softmax.o validators.o pthreadopt.o mklopt.o timing.o latency_others.o
	g++ -Wl,-rpath,$(MKL_LIB_DIRI) -L$(MKL_LIB_DIRI) -I$(MKL_INCLUDE_DIRI) file.o relu.o tanh.o sigmoid.o mklopt.o softmax.o pthreadopt.o timing.o validators.o latency_others.o -o yourcode.out $(COMPILER_FLAGS)

openblas_mm.out: openblas_mm.o file2.o timing.o latency_openblas.o
	g++ $(LDFLAGS) -o $(TEST_OPENBLAS) $(objects_test_openblas) file2.o validators.o timing.o latency_openblas.o $(LDLIBS)

relu.o: relu.cpp relu.h
	g++ -c relu.cpp

tanh.o: tanh.h tanh.cpp
	g++ -c tanh.cpp

sigmoid.o: sigmoid.cpp sigmoid.h
	g++ -c sigmoid.cpp 

softmax.o: softmax.cpp softmax.h
	g++ -c softmax.cpp 

validators.o: validators.cpp validator.h
	g++ -c validators.cpp

pthreadopt.o: pthreadopt.cpp
	g++ -c pthreadopt.cpp

mklopt.o: mklopt.cpp
	g++ -c -L$(MKL_LIB_DIRI) -I$(MKL_INCLUDE_DIRI) mklopt.cpp $(COMPILER_FLAGS)

timing.o: timing.cpp
	g++ -c timing.cpp

file.o: file.cpp matrixio.cpp vectorio.cpp pooling.cpp matrixAlgebra.cpp
	g++ -c  file.cpp 

file2.o: file2.cpp matrixio.cpp
	g++ -c file2.cpp

openblas_mm.o: openblasopt.cpp matarr.cpp
	g++ -c openblasopt.cpp -o openblas_mm.o $(CPPFLAGS)

latency_openblas.o: latency_openblas.h latency_consts.h matrixio.h optimization.h
latency_others.o: latency_others.h latency_consts.h matrixio.h optimization.h matrixAlgebra.h

randomMain.o: genRandom.cpp matrixio.cpp

clean:
	rm *.o yourcode.out openblas_mm.out $(RANDOM_MAT)