#include<iostream>
#include"relu.h"
#include"tanh.h"
#include "matrixio.cpp"

using namespace std ; 

int main(){

    // cout << ReLU(5) ; 
    vector<vector<float>>mat = read("input.txt") ; 
    ReLU(mat) ; 
    cout << mat.size() << " " << mat[0].size() << "\n" ; 
    for( int i =0 ; i < mat.size() ; i ++ ){
        for( int j = 0 ; j < mat[0].size() ; j++ ){
            cout << mat[i][j] << " " ; 
        }
        cout << "\n" ; 
    }
    vector<vector<float>>mat2 = read("input.txt") ; 
    tanH(mat2) ; 
    cout << mat2.size() << " " << mat2[0].size() << "\n" ; 
    for( int i =0 ; i < mat2.size() ; i ++ ){
        for( int j = 0 ; j < mat2[0].size() ; j++ ){
            cout << mat2[i][j] << " " ; 
        }
        cout << "\n" ; 
    }

    return 0 ; 
}
