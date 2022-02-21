# -*- MakeFile -*-

# target: dependencies
# 	action

# Compiler to use
CXX = g++

# Flags: CPP => Preprocessor flags, passed to both c and cpp files, LDFFLAGS => Linker Flags, LDLIBS => Linker Libs
CPPFLAGS = -g -Wall
LDFLAGS = -g -Llibs/openblas/lib -Wl,-rpath,libs/openblas/lib
LDLIBS = -lopenblas -lpthread

# Executables to build
TARGET = yourcode.out
TEST_OPENBLAS = test_openblas.out
RANDOM_MAT = randomMat.out

objects = file.o relu.o tanh.o sigmoid.o softmax.o validators.o
objects_test_openblas = test_openblas.o
objects_random_mat = randomMain.o validators.o

all: $(TARGET) $(TEST_OPENBLAS) $(RANDOM_MAT)

$(TARGET): $(objects)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(objects) $(LDLIBS)

$(TEST_OPENBLAS): $(objects_test_openblas)
	$(CXX) $(LDFLAGS) -o $(TEST_OPENBLAS) $(objects_test_openblas) $(LDLIBS)

$(RANDOM_MAT): $(objects_random_mat)
	$(CXX) $(LDFLAGS) -o $(RANDOM_MAT) $(objects_random_mat) $(LDLIBS)
# If no action is specified for filename.o, make adds filename.cpp (or filename.cc or filename.c) to dependencies, and adds
# action "$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c filename.cpp

relu.o: relu.h

tanh.o: tanh.h

sigmoid.o: sigmoid.h

softmax.o: softmax.h

validators.o: validators.h

file.o: matrixio.cpp vectorio.cpp pooling.cpp matarr.cpp matrixAlgebra.cpp

test_openblas.o: matarr.cpp matrixAlgebra.cpp

randomMain.o: genRandom.cpp matrixio.cpp

clean:
	rm *.o $(TARGET) $(TEST_OPENBLAS) $(RANDOM_MAT)