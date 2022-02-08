# -*- MakeFile -*-

# target: dependencies
# 	action
COMPILER_FLAGS = -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl
MKL_LIB_DIRI = /home/chinmay/intel/oneapi/mkl/2022.0.2/lib/intel64
MKL_INCLUDE_DIRI = /home/chinmay/intel/oneapi/mkl/2022.0.2/include

yourcode.out: file.o relu.o tanh.o sigmoid.o softmax.o validators.o
	g++ -L$(MKL_LIB_DIRI) -I$(MKL_INCLUDE_DIRI) file.o relu.o tanh.o sigmoid.o  softmax.o validators.o -o yourcode.out $(COMPILER_FLAGS)

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

file.o: file.cpp matrixio.cpp vectorio.cpp pooling.cpp matrixAlgebra.cpp
	g++ -c -L$(MKL_LIB_DIRI) -I$(MKL_INCLUDE_DIRI) file.cpp $(COMPILER_FLAGS)

clean:
	rm *.o yourcode.out