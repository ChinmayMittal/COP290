# -*- MakeFile -*-

# target: dependencies
# 	action
COMPILER_FLAGS = -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl
MKL_LIB_DIRI = /home/chinmay/intel/oneapi/mkl/2022.0.2/lib/intel64
MKL_INCLUDE_DIRI = /home/chinmay/intel/oneapi/mkl/2022.0.2/include

yourcode.out: file.o relu.o tanh.o sigmoid.o softmax.o validators.o pthreadopt.o mklopt.o timing.o
	g++ -Wl,-rpath,$(MKL_LIB_DIRI) -L$(MKL_LIB_DIRI) -I$(MKL_INCLUDE_DIRI) file.o relu.o tanh.o sigmoid.o mklopt.o softmax.o pthreadopt.o timing.o validators.o -o yourcode.out $(COMPILER_FLAGS)

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

clean:
	rm *.o yourcode.out