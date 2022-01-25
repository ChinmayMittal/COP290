# -*- MakeFile -*-

# target: dependencies
# 	action
file.out: file.o relu.o tanh.o
	g++ file.o relu.o tanh.o -o file.out

relu.o: relu.cpp relu.h
	g++ -c relu.cpp

tanh.o: tanh.h tanh.cpp
	g++ -c tanh.cpp

file.o: file.cpp matrixio.cpp
	g++ -c file.cpp

clean:
	rm *.o file.out