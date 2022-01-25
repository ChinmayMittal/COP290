#include<iostream>
#include"relu.h"
#include"tanh.h"
#include "matrixio.cpp"

using namespace std ; 

int main(){

    // cout << ReLU(5) ; 
    vector<vector<float>>mat = read("input.txt") ; 
    ReLU(mat) ; 
    write(mat , "relu.txt") ;
    vector<vector<float>>mat2 = read("input2.txt") ; 
    tanH(mat2) ; 
    write( mat2 , "tanh.txt") ; 

    return 0 ; 
}
