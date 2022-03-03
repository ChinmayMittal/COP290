#include<iostream>
#include<vector>
#include<string>
#include"algorithm"

#include "optimization.h"

#include"vectorio.h"
#include"matarr.h"
#include"matrixAlgebra.h"

#include"dnn_weights.h"

#include"relu.h"
#include"softmax.h"

#include"predict_t.h"
#include"predHelper.h"

using namespace std ;



bool predictionComparator( pred_t pred1 , pred_t pred2 ) {

    return pred1.prob > pred2.prob ;  
}
int main( int argc, const char *argv[] ) {
 
    string filename = "mfcc_features/c9b5ff26_nohash_4.txt" ; 
    vector<vector<float>>inputFeatures = vectorToMatrix( readVectorInOneLine(filename)  , 1 , 250  , 'R')  ; 
    vector<vector<float>>weights1 = vectorToMatrix ( IP1_WT  , 250 , 144 , 'R') , weights2 = vectorToMatrix (  IP2_WT, 144 , 144 , 'R' ) , weights3 = vectorToMatrix (IP3_WT ,144 , 144 , 'R'), weights4 = vectorToMatrix(IP4_WT  , 144 , 12 , 'R'), bias1 = vectorToMatrix ( IP1_BIAS , 1 , 144 , 'R' ) , bias2 = vectorToMatrix(IP2_BIAS , 1 , 144 , 'R'), bias3 = vectorToMatrix (  IP3_BIAS , 1 , 144 , 'R' )  , bias4 = vectorToMatrix ( IP4_BIAS , 1 , 12 , 'R' )  , out1 , out2 , out3 , ans ; 

    // mkl implemenentation of NN 
    out1 = mklOpt(  inputFeatures , weights1 , bias1 ).first; 
    ReLU( out1 ) ; 
    out2 = mklOpt( out1 , weights2 , bias2 ).first ; 
    ReLU( out2 ) ; 
    out3 = mklOpt( out2 , weights3 , bias3 ).first ; 
    ReLU( out3 ) ;
    ans = mklOpt ( out3, weights4 , bias4 ).first ;  
    softmax( ans[0]) ; 
     
    vector<pred_t> ansArray ; 
    for( int i = 0 ; i < 12 ; i ++ ){ 

        ansArray.push_back({
            i+1 , 
            ans[0][i]
         }
        ) ; 
    }  

    sort( ansArray.begin() , ansArray.end() , predictionComparator ) ;
    for( auto ele : ansArray ) cout << ele.label << " " << ele.prob << " " << numToLabel[ele.label] << "\n" ;  
 
    return 0 ; 
}