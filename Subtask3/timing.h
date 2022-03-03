#include <chrono>
#include <string>
#include <iostream>

// header file for timing utility functions

std::chrono::high_resolution_clock::time_point get_time();

void printTimeDuration(std::string message, std::chrono::high_resolution_clock::time_point t1, std::chrono::high_resolution_clock::time_point t2);

double getTimeDuration(std::chrono::high_resolution_clock::time_point t1, std::chrono::high_resolution_clock::time_point t2);