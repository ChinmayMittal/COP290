#include <iostream>
#include <vector>
#include "matarr.cpp"
#include "libs/openblas/include/cblas.h"

using namespace std;

vector<vector<float>> add(vector<vector<float>> &mat1, vector<vector<float>> &mat2)
{

    int row1 = mat1.size(), col1 = mat1[0].size(), row2 = mat2.size(), col2 = mat2[0].size();

    if (row1 != row2 || col1 != col2)
    {
        throw("Matrix dimension mismatch during addition");
    }

    vector<vector<float>> ans(row1, vector<float>(col1, 0.0));

    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col1; j++)
        {
            ans[i][j] = mat1[i][j] + mat2[i][j];
        }
    }

    return ans;
}

vector<vector<float>> mul(vector<vector<float>> &mat1, vector<vector<float>> &mat2)
{

    int row1 = mat1.size(), col1 = mat1[0].size(), row2 = mat2.size(), col2 = mat2[0].size();

    if (col1 != row2)
    {
        throw("Matrix dimension mismatch during multiplication");
    }

    vector<vector<float>> ans(row1, vector<float>(col2, 0.0));

    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            for (int k = 0; k < col1; k++)
                ans[i][j] += (mat1[i][k] * mat2[k][j]);
        }
    }

    return ans;
}

std::vector<std::vector<float>> mulAndAdd_openblas(vector<vector<float>> &mat1, vector<vector<float>> &mat2, vector<vector<float>> &mat3)
{
    double *A = new double[mat1.size() * mat1[0].size()];
    matToArray1D(mat1, A);

    double *B = new double[mat2.size() * mat2[0].size()];
    matToArray1D(mat2, B);

    double *C = new double[mat3.size() * mat3[0].size()];
    matToArray1D(mat3, C);

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat1.size(), mat2[0].size(), mat2.size(), 1, A, mat1.size(), B, mat2[0].size(), 1, C, mat3.size());

    std::vector<std::vector<float>> res = array1DToMat(C, mat3.size(), mat3[0].size());
    return res;
}