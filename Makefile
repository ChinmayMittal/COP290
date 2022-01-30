# -*- MakeFile -*-

# target: dependencies
# 	action
yourcode.out: file.o relu.o tanh.o sigmoid.o softmax.o validators.o
	g++ file.o relu.o tanh.o sigmoid.o  softmax.o validators.o -o yourcode.out

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
	g++ -c file.cpp

clean:
	rm *.o yourcode.out