#include<iostream>
#include<vector>
#include<string>

#include "optimization.h"

#include"vectorio.h"
#include"matarr.h"
#include"matrixAlgebra.h"

#include"dnn_weights.h"

#include"relu.h"
#include"softmax.h"

using namespace std ; 

int main ( int argc, const char *argv[] ) {
 
    string filename = "mfcc_features/e4be0cf6_nohash_3.txt" ; 
    vector<vector<float>>inputFeatures = vectorToMatrix( readVectorInOneLine(filename)  , 1 , 250  , 'R')  ; 
    vector<vector<float>>weights1 = vectorToMatrix ( IP1_WT  , 250 , 144 , 'R') , weights2 = vectorToMatrix (  IP2_WT, 144 , 144 , 'R' ) , weights3 = vectorToMatrix (IP3_WT ,144 , 144 , 'R'), weights4 = vectorToMatrix(IP4_WT  , 144 , 12 , 'R'), bias1 = vectorToMatrix ( IP1_BIAS , 1 , 144 , 'R' ) , bias2 = vectorToMatrix(IP2_BIAS , 1 , 144 , 'R'), bias3 = vectorToMatrix (  IP3_BIAS , 1 , 144 , 'R' )  , bias4 = vectorToMatrix ( IP4_BIAS , 1 , 12 , 'R' )  , out1 , out2 , out3 , ans ; 

    cout << inputFeatures.size() << " " << inputFeatures[0].size() << "\n" ; 
    cout << weights1.size() << " " << weights1[0].size() << "\n" ; 
    cout << bias1.size() << " " << bias1[0].size() << "\n" ;

    // naive 
    // out1 = mul( inputFeatures , weights1 ) ;  
    // out1 = add( out1, bias1) ; 
    // ReLU(out1) ; 
    // out2 = mul( out1 , weights2 ) ;  
    // out2 = add( out2, bias2) ; 
    // ReLU(out2) ; 
    // out3 = mul( out2 , weights3 ) ;  
    // out3 = add( out3, bias3) ; 
    // ReLU(out3) ; 
    // ans = mul( out3 , weights4 ) ;  
    // ans = add( ans, bias4) ; 
    // softmax( ans[0]) ;

    // mkl 
    out1 = mklOpt(  inputFeatures , weights1 , bias1 ).first; 
    ReLU( out1 ) ; 
    out2 = mklOpt( out1 , weights2 , bias2 ).first ; 
    ReLU( out2 ) ; 
    out3 = mklOpt( out2 , weights3 , bias3 ).first ; 
    ReLU( out3 ) ;
    ans = mklOpt ( out3, weights4 , bias4 ).first ;  
    softmax( ans[0]) ; 
     
    for( int i = 0 ; i < 12 ; i ++ ) cout << ans[0][i] << "\n" ; 
 
    return 0 ; 
}