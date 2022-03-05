#include<iostream>
#include<vector>
#include<string>
#include"algorithm"

#include "optimization.h"

#include"vectorio.h"
#include"matarr.h"

// pre-trained weights and biases 
#include"dnn_weights.h"

#include"relu.h"
#include"softmax.h"

#include"interfaceNN.h"

using namespace std ;

bool predictionComparator( pred_t pred1 , pred_t pred2 ) {
    /*
        custom comparator for comparing prediction values, predictions with higher probabiliy will come first 
    */
    return pred1.prob > pred2.prob ;  
}

void libaudioAPI(const char *audiofeatures, pred_t *pred){
    
    string filename( audiofeatures)  ; 
    // read the input features for the neural network ( [ 1 X 250 ] ) , the last parameter denotes row major order 
    vector<vector<float>>inputFeatures = vectorToMatrix( readVectorInOneLine(filename)  , 1 , 250  , 'R')  ; 
    // pre-trained weights and biases are defined in a seperate header, dimensions are specified in funciton call ( NAME_OF_VECTOR , ROWS , COLUMNS , ROW_MAJOR_ORDER)
    vector<vector<float>>weights1 = vectorToMatrix ( IP1_WT  , 250 , 144 , 'R') , weights2 = vectorToMatrix (  IP2_WT, 144 , 144 , 'R' ) , weights3 = vectorToMatrix (IP3_WT ,144 , 144 , 'R'), weights4 = vectorToMatrix(IP4_WT  , 144 , 12 , 'R'), bias1 = vectorToMatrix ( IP1_BIAS , 1 , 144 , 'R' ) , bias2 = vectorToMatrix(IP2_BIAS , 1 , 144 , 'R'), bias3 = vectorToMatrix (  IP3_BIAS , 1 , 144 , 'R' )  , bias4 = vectorToMatrix ( IP4_BIAS , 1 , 12 , 'R' )  , out1 , out2 , out3 , ans ; 

    // mkl (fastest) implemenentation of NN 
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

    // sort all predictions based on the output probability 
    sort( pred , pred + 12 , predictionComparator ) ; 

}



