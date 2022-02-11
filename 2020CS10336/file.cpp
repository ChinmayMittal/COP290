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
#include"matGen.cpp"
#include"optimization.h"
#include"mkl.h"

using namespace std ; 
using namespace std::chrono;

int main( int argc , const char * argv [] ){

    // vector<vector<float>>a(500,vector<float>(500)) ;
    // matGen(a,0,10) ;
    // write(a , "matrix.txt") ;  
    // matGen(a,0,10) ; 
    // write(a,"weight.txt")  ; 
    // matGen(a,0,10) ; 
    // write(a,"bias.txt") ; 
    string task(argv[1]); // stores the name of the function to be called ( fullyconnected/activation/pooling/probability)
    
    try{

        if( task == "fullyconnected"){

            if( argc < 6 ) {
                throw ( "fully connected requires arguments in the form of fullyconnected (input_matrix_filename) (weight_matrix_filename) (bias_matrix_filename) (output_matrix_filename)") ;
             }
            string inputMatFileName( argv[2]) , weightMatFileName( argv[3]) , biasMatFileName( argv[4]) , outputFileName( argv[5]) ;
            // get input, weight and bias matrices  
            vector<vector<float>>mat = read(inputMatFileName), weights = read( weightMatFileName) , bias = read(biasMatFileName) ; 
            if(argc == 6 ){
                // naive implementation 
                auto t1 = get_time() ; 
                vector<vector<float>> mulMat = mul( mat , weights) ; // matrix multiplication 
                vector<vector<float>> ans = add( mulMat , bias) ;  // matrix addition 
                auto t2 = get_time() ; 
                printTimeDuration("MATMUL NAIVE:" , t1 , t2 )  ; 
                write( ans , outputFileName ) ; // output to filename
            }else{
                // optimized implementation 
                string optimization(argv[6]) ;
                if(optimization == "mkl"){
                     // Matrices
                     double *A, *B, *C , *outputMatrix ;
                     A = (double *)mkl_malloc(mat.size() * mat[0].size() * sizeof(double), 64);
                     B = (double *)mkl_malloc(weights.size() * weights[0].size() * sizeof(double), 64);
                     C = (double *)mkl_malloc(bias.size() * bias[0].size() * sizeof(double), 64);
                     vec2Arr( A , mat ) ; vec2Arr( B , weights ) , vec2Arr(C,weights) ; 
                     // Scale factors
                     double alpha, beta;
                     alpha = 1.0;
                     beta = 1.0;
                    auto mkl_t1 = get_time();
                    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat.size() , weights[0].size() , mat[0].size(),
                            alpha, A, mat[0].size() , B, weights[0].size(), beta, C, weights[0].size());
                    auto mkl_t2 = get_time();                     
                    printTimeDuration("MATMUL MKL:" , mkl_t1 , mkl_t2 )  ; 
                    vector<vector<float>> ans = arr2Vec(C,bias.size(),bias[0].size());
                    write( ans , outputFileName) ; 
                }else if( optimization == "openblas"){

                }else if( optimization == "pthread"){
                   vector<vector<float>> ans =  pthreadOpt(mat,weights,bias);
                   write( ans , outputFileName ) ; 
                }else{
                    throw ( optimization + " is not supported use mkl|openblas|pthread") ; 
                }

            }
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



    // Matrix dimensions
    int m, n, k;
    m = 2000;
    k = 200;
    n = 1000;



    // Allocate 64-byte-aligned memory
    // A is a "m x k" matrix
//     A = (double *)mkl_malloc(m * k * sizeof(double), 64);
//     // B is a "k x n" matrix
//     B = (double *)mkl_malloc(k * n * sizeof(double), 64);
//     // C is a "m x n" matrix
//     C = (double *)mkl_malloc(m * n * sizeof(double), 64);
//         // Initialize the matrices
//     init_matrix<double>(A, m, k);
//     init_matrix<double>(B, k, n);
//     // Initialize the result matrix to 0s
//     init_matrix<double>(C, m, n, 0);
//     auto mkl_t1 = get_time();
//     cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k,
//             alpha, A, k, B, n, beta, C, n);
//     auto mkl_t2 = get_time();

//     // Compute the execution time
//     auto mkl_time_span =
//         duration_cast<duration<double>>(mkl_t2 - mkl_t1);
//     cout << "Elapsed time MKL: " << mkl_time_span.count() << " s" << endl;
    return 0 ; 
}
