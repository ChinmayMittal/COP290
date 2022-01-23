# -*- MakeFile -*-

# target: dependencies
# 	action
main: file.o relu.o
	g++ file.o relu.o -o main

relu.o: relu.cpp
	g++ -c relu.cpp

file.o: file.cpp
	g++ -c file.cpp