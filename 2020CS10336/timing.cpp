#include <chrono>
#include<string>
#include<iostream>

// utility functions for timing code execution 

std::chrono::high_resolution_clock::time_point get_time(){
     /* 
        Returns the current clock time 
     */
    return std::chrono::high_resolution_clock::now();
}

void printTimeDuration( std::string message , std::chrono::high_resolution_clock::time_point t1 , std::chrono::high_resolution_clock::time_point t2){
        /* 
                Prints the time elapsed in seconds along with a message
       */
        auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        std::cout << message << " " << time_span.count() << " s" << std::endl ;  
}

double getTimeDuration( std::chrono::high_resolution_clock::time_point t1 , std::chrono::high_resolution_clock::time_point t2 ){
        /* 
                Returns the time elapsed in seconds as a double
       */
        auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        return time_span.count()  ;     
}