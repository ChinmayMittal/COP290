#include<iostream>
#include<vector>
#include <cstdlib> 
#include <ctime> 
#include <stdlib.h>


using namespace std ; 

void matGen( vector<vector<float>>&mat , float lrange = 0 , float rrange = 1){

    srand(static_cast<unsigned int>(std::time(nullptr)));

    int m = mat.size() , n = mat[0].size() ; 
    for( int i = 0 ; i <  m ; i++ ){
        for( int j = 0 ; j < n ; j ++ ){
            mat[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(rrange-lrange));
        }
    }

}

template <class T>
void init_matrix(T *a, int m, int n, T value = 1){
    for(int i = 0; i < m * n; i++){
        if(value == 1){
            a[i] = (T)(rand() % 100);
        }else{
            a[i] = 0;
        }
    }
}

void vec2Arr( double* A , vector<vector<float>>&mat ) { 
    int m = mat.size() , n = mat[0].size() ;
     
    for( int i = 0 ; i < m ; i ++ ){
        for( int j = 0 ; j < n ; j ++ ){
            A[n*i+j] = (double)mat[i][j] ; 
        }
    }
}

vector<vector<float>> arr2Vec( double * A , int m , int n ) {

    vector<vector<float>>ans( m , vector<float>(n,0.0f)) ; 
    for( int i = 0 ; i < m*n ; i ++ ){
        ans[i/n][i%n] = A[i] ; 
    } 
    return ans ; 
}