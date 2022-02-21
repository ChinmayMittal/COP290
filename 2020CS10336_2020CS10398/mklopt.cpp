#include <utility>
#include <vector>

#include "mkl.h"

#include "optimization.h"

#include "matarr.h"
#include "timing.h"

using namespace std;

// main function for mkl implementation
pair<vector<vector<float>>, double> mklOpt(vector<vector<float>> &mat, vector<vector<float>> &weights, vector<vector<float>> &bias)
{
        /*
           Returns the output matrix and the time taken in seconds as a double in a pair
           computes mat X weights  + bias
         */
        // Matrices
        double *A, *B, *C, *outputMatrix;
        // dynamically allocate memory for matrices
        A = (double *)mkl_malloc(mat.size() * mat[0].size() * sizeof(double), 64);
        B = (double *)mkl_malloc(weights.size() * weights[0].size() * sizeof(double), 64);
        C = (double *)mkl_malloc(bias.size() * bias[0].size() * sizeof(double), 64);
        matToArray1D(mat, A);
        matToArray1D(weights, B), matToArray1D(weights, C);
        // Scale factors
        double alpha, beta;
        alpha = 1.0;
        beta = 1.0;
        auto mkl_t1 = get_time();
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat.size(), weights[0].size(), mat[0].size(),
                    alpha, A, mat[0].size(), B, weights[0].size(), beta, C, weights[0].size());
        auto mkl_t2 = get_time();
        printTimeDuration("MATMUL MKL:", mkl_t1, mkl_t2);
        // convert matrix to vector of vectors
        vector<vector<float>> ans = array1DToMat(C, bias.size(), bias[0].size());
        return pair<vector<vector<float>>, double>(ans, getTimeDuration(mkl_t1, mkl_t2));
}