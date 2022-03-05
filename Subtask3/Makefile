# -*- MakeFile -*-

# target: dependencies
# 	action

CXX = g++

MKL_LIB_DIR = /opt/intel/oneapi/mkl/2022.0.2/lib/intel64
MKL_INCLUDE_DIR = /opt/intel/oneapi/mkl/2022.0.2/include

CPPFLAGS = -g -Wall -I$(MKL_INCLUDE_DIR) -fpic
LDFLAGS_LIB = -g -L$(MKL_LIB_DIR) -Wl,-rpath,$(MKL_LIB_DIR)
LDFLAGS_EXEC = -g -L. -Wl,-rpath,.

MKL_LIB = -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl
MAIN_LIB = -laudio

NN_LIB = libaudio.so
objects_NN_lib = ann.o matarr.o matrixAlgebra.o mklopt.o relu.o softmax.o timing.o validators.o vectorio.o

MAIN_EXEC = yourcode.out
objects_main_exec = NNMain.o matarr.o vectorio.o

all: $(NN_LIB) $(MAIN_EXEC) 

$(NN_LIB): $(objects_NN_lib)
	$(CXX) $(LDFLAGS_LIB) -shared -o $(NN_LIB) $(objects_NN_lib) $(MKL_LIB)

$(MAIN_EXEC): $(objects_main_exec)
	$(CXX) $(LDFLAGS_EXEC) -o $(MAIN_EXEC) $(objects_main_exec) $(MAIN_LIB)

ann.o: optimization.h vectorio.h relu.h softmax.h matarr.h dnn_weights.h interfaceNN.h

matarr.o: matarr.h

matrixAlgebra.o: matrixAlgebra.h

mklopt.o: optimization.h matarr.h timing.h

NNMain.o: interfaceNN.h matarr.h predHelper.h vectorio.h

relu.o: relu.h

softmax.o: softmax.h

timing.o: timing.h

validators.o: validators.h

vectorio.o: vectorio.h validators.h

clean:
	rm *.o $(NN_LIB) $(MAIN_EXEC) 