#include<iostream>
#include<string>
#include"relu.h"
#include"tanh.h"
#include "matrixio.cpp"

using namespace std ; 

int main( int argc , const char * argv [] ){

    string task(argv[1]);
    cout << argc << "\n" ; 
    try{


        if( task == "fullyconnected"){

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

        }else if( task == "probability"){

        }else{
            throw ( task + " is an invalid argument to the program , choose either fullyconnected | activation | pooling | probability") ; 
        }

    }catch( string exp){
        cout << exp << "\n" ; 
    }catch( char const* exp){
        cout << exp << "\n" ; 
    }


    // cout << ReLU(5) ; 
    // vector<vector<float>>mat = read("input.txt") ; 
    // ReLU(mat) ; 
    // write(mat , "relu.txt") ;
    // vector<vector<float>>mat2 = read("input2.txt") ; 
    // tanH(mat2) ; 
    // write( mat2 , "tanh.txt") ; 

    return 0 ; 
}
