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

#include"interfaceNN.h"
#include"predHelper.h"

using namespace std ;

bool predictionComparator( pred_t pred1 , pred_t pred2 ) {

    return pred1.prob > pred2.prob ;  
}

void libaudioAPI(const char *audiofeatures, pred_t *pred){
    
    string filename( audiofeatures)  ; 
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
     
    for( int i = 0 ; i < 12 ; i ++ ){ 
        pred[i] = { i+1, ans[0][i] } ;
    }  

    sort( pred , pred + 12 , predictionComparator ) ; 
    // for( int i = 0 ; i < 12 ; i ++ )  cout << pred[i].label << " " << pred[i].prob << " " << numToLabel[pred[i].label] << "\n" ;  

}


// int main( int argc, const char *argv[] ) {
 
//     const char* a = "mfcc_features/b2ae3928_nohash_1.txt" ; 
//     pred_t predictions [12] ; 
//     libaudioAPI(a, predictions ) ; 
 
//     return 0 ; 
// }

