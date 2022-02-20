#include"mkl.h"
#include"timing.h"
#include"matarr.cpp"
#include<utility>

using namespace std ; 


pair<vector<vector<float>> , double > mklOpt(vector<vector<float>>&mat, vector<vector<float>>&weights, vector<vector<float>>&bias){
    
     // Matrices
     double *A, *B, *C , *outputMatrix ;
     A = (double *)mkl_malloc(mat.size() * mat[0].size() * sizeof(double), 64);
     B = (double *)mkl_malloc(weights.size() * weights[0].size() * sizeof(double), 64);
     C = (double *)mkl_malloc(bias.size() * bias[0].size() * sizeof(double), 64);
     matToArray1D(  mat , A ) ; matToArray1D(  weights , B  ) , matToArray1D( weights , C) ; 
     // Scale factors
     double alpha, beta;
     alpha = 1.0;
     beta = 1.0;
    auto mkl_t1 = get_time();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat.size() , weights[0].size() , mat[0].size(),
            alpha, A, mat[0].size() , B, weights[0].size(), beta, C, weights[0].size());
    auto mkl_t2 = get_time();                     
    printTimeDuration("MATMUL MKL:" , mkl_t1 , mkl_t2 )  ; 
    vector<vector<float>> ans = array1DToMat(C,bias.size(),bias[0].size());
    return pair<vector<vector<float>> , double>(ans , getTimeDuration(mkl_t1 , mkl_t2) )  ; 
}