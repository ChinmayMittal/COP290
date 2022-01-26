#include<iostream>
#include<vector>
#include<cmath>
using namespace std ; 


float sigmoid( float x ) {

    return 1 / ( 1 + exp(-x)) ; 
}

void sigmoid( vector<float>&arr){
    for( auto &ele : arr ) {
        ele = sigmoid(ele) ; 
    }
}