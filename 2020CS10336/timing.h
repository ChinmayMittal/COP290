#include <chrono>
#include<string>
#include<iostream>

std::chrono::high_resolution_clock::time_point get_time(){
    return std::chrono::high_resolution_clock::now();
}

void printTimeDuration( std::string message , std::chrono::high_resolution_clock::time_point t1 , std::chrono::high_resolution_clock::time_point t2){
        auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        std::cout << message << " " << time_span.count() << " s" << std::endl ;  
}