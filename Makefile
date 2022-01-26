# -*- MakeFile -*-

# target: dependencies
# 	action
file.out: file.o relu.o tanh.o sigmoid.o softmax.o
	g++ file.o relu.o tanh.o sigmoid.o  softmax.o -o file.out

relu.o: relu.cpp relu.h
	g++ -c relu.cpp

tanh.o: tanh.h tanh.cpp
	g++ -c tanh.cpp

sigmoid.o: sigmoid.cpp sigmoid.h
	g++ -c sigmoid.cpp 

softmax.o: softmax.cpp softmax.h
	g++ -c softmax.cpp 

file.o: file.cpp matrixio.cpp vectorio.cpp
	g++ -c file.cpp

clean:
	rm *.o file.out