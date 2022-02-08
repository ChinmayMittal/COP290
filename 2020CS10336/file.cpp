#include<iostream>
#include<string>
#include"relu.h"
#include"tanh.h"
#include"sigmoid.h"
#include "matrixio.cpp"
#include "vectorio.cpp"
#include "softmax.h"
#include"pooling.cpp"
#include"matrixAlgebra.cpp"
#include"validator.h"
#include"timing.h"

using namespace std ; 

int main( int argc , const char * argv [] ){


    string task(argv[1]); // stores the name of the function to be called ( fullyconnected/activation/pooling/probability)
    
    try{

        if( task == "fullyconnected"){

            if( argc < 6 ) {
                throw ( "fully connected requires arguments in the form of fullyconnected (input_matrix_filename) (weight_matrix_filename) (bias_matrix_filename) (output_matrix_filename)") ;
             }

             string inputMatFileName( argv[2]) , weightMatFileName( argv[3]) , biasMatFileName( argv[4]) , outputFileName( argv[5]) ; 
             // get input, weight and bias matrices 
             
             vector<vector<float>>mat = read(inputMatFileName), weights = read( weightMatFileName) , bias = read(biasMatFileName);
             auto t1 = get_time() ; 
             vector<vector<float>> mulMat = mul( mat , weights) ; // matrix multiplication 
             auto t2 = get_time() ; 
             printTimeDuration("MATMUL" , t1 , t2 )  ; 
             vector<vector<float>> ans = add( mulMat , bias) ;  // matrix addition 
             write( ans , outputFileName ) ; // output to filename


        }else if( task == "activation"){

            if(argc < 5  ){
                throw ( "activation requires arguments in the format activation (type) (input_file_name) (output_filename)") ; 
            }

            string activation(argv[2]) , inputFileName(argv[3]) , outputFileName(argv[4]);
            vector<vector<float>>mat = read(inputFileName) ;

            if( (activation == "relu")){
                ReLU(mat) ; //// inplace termwise activation of the matrix 
                write(mat , outputFileName) ;
            }else if( activation == "tanh"){
                tanH(mat) ;  //// inplace termwise activation of the matrix 
                write(mat , outputFileName) ;
            }else {
                throw ( activation +  " is not a valid activation, use relu/tanh") ; 
            }


        }else if( task == "pooling"){

            if(argc < 6 ) { 
                 throw ( "pooling requires arguments in the format pooling (type) (input_file_name) (stride) (output_filename)") ;
            }

            string poolingType(argv[2]) , inputFileName(argv[3]) , strideString(argv[4]) , outputFileName(argv[5]);
            int stride = string_to_int_validator(strideString , "stride has to be a positive integer") ; // filter size is assumed to be (stride*stride)
            vector<vector<float>>mat = read(inputFileName) ; // get input matrix 

            if( poolingType == "average"){
                vector<vector<float>> reducedMatrix = pooling( mat, stride , poolingType ) ; 
                write( reducedMatrix, outputFileName ) ; 

            }else if( poolingType == "max"){
                vector<vector<float>> reducedMatrix = pooling( mat, stride , poolingType ) ; 
                write( reducedMatrix, outputFileName ) ; 
            }else{
                throw ( poolingType +  " is not a valid pooling type, use average/max") ; 
            }



        }else if( task == "probability"){

            if(argc < 5 ){
                throw ( "probability requires argumens in the format probability [type] [input_file_name] [output_file_name]") ; 
            }

            string typeOfProbability(argv[2]) , inputFileName( argv[3]) , outputFileName(argv[4]) ; 

            if( typeOfProbability == "sigmoid"){

                vector<float> arr =readVector(inputFileName);
                sigmoid(arr) ; // inplace probability for the vector 
                writeVector(outputFileName , arr ) ; 

            }else if( typeOfProbability == "softmax"){

                vector<float> arr =readVector(inputFileName);
                softmax(arr) ; // inplace softmax for the vector 
                writeVector(outputFileName , arr ) ; 

            }else{
                throw ( typeOfProbability +  " is not supported, use softmax/sigmoid") ; 
            }

        }else{
            // invalid function module 
            throw ( task + " is an invalid argument to the program , choose either fullyconnected | activation | pooling | probability") ; 
        }

    }catch( string exp){
        // ERROR HANDLING 
        cout << "ERROR:  PROGRAM TERMINATING....\n" ; 
        cout << exp << "\n" ; 
    }catch( char const* exp){
        cout << "ERROR:  PROGRAM TERMINATING....\n" ; 
        cout << exp << "\n" ; 
    }


    return 0 ; 
}
