#include <iostream>
#include <vector>
#include "matarr.cpp"
#include"timing.h"
#include "libs/openblas/include/cblas.h"

using namespace std;

pair<vector<vector<float>> , double >  mulAndAdd_openblas(vector<vector<float>> &mat1, vector<vector<float>> &mat2, vector<vector<float>> &mat3)
{
    double *A = new double[mat1.size() * mat1[0].size()];
    matToArray1D(mat1, A);

    double *B = new double[mat2.size() * mat2[0].size()];
    matToArray1D(mat2, B);

    double *C = new double[mat3.size() * mat3[0].size()];
    matToArray1D(mat3, C);
    auto t1 = get_time() ; 
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat1.size(), mat2[0].size(), mat2.size(), 1, A, mat1.size(), B, mat2[0].size(), 1, C, mat3.size());
    auto t2 = get_time() ; 
    printTimeDuration( "OPENBLAS" , t1 , t2 ) ; 
    std::vector<std::vector<float>> res = array1DToMat(C, mat3.size(), mat3[0].size());
    return pair<vector<vector<float>> , double >  ( res , getTimeDuration( t1 , t2 ) ) ;
}