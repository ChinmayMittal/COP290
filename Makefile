# -*- MakeFile -*-

# target: dependencies
# 	action

# Compiler to use
CXX = g++

# Flags: CPP => Preprocessor flags, passed to both c and cpp files, LDFFLAGS => Linker Flags, LDLIBS => Linker Libs
CPPFLAGS = -g -Wall
LDFLAGS = -g -Llibs/openblas/lib 
LDLIBS = -lopenblas -lpthread

# Executables to build
TARGET = yourcode.out
TEST_OPENBLAS = test_openblas.out

objects = file.o relu.o tanh.o sigmoid.o softmax.o validators.o
objects_test_openblas = test_openblas.o

all: $(TARGET) $(TEST_OPENBLAS)

$(TARGET): $(objects)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(objects) $(LDLIBS)

$(TEST_OPENBLAS): $(objects_test_openblas)
	$(CXX) $(LDFLAGS) -o $(TEST_OPENBLAS) $(objects_test_openblas) $(LDLIBS)


# If no action is specified for filename.o, make adds filename.cpp (or filename.cc or filename.c) to dependencies, and adds
# action "$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c filename.cpp

relu.o: relu.h

tanh.o: tanh.h

sigmoid.o: sigmoid.h

softmax.o: softmax.h

validators.o: validator.h

file.o: matrixio.cpp vectorio.cpp pooling.cpp matarr.cpp matrixAlgebra.cpp

test_openblas.o: matarr.cpp matrixAlgebra.cpp

clean:
	rm *.o $(TARGET) $(TEST_OPENBLAS)