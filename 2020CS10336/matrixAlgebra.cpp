#include <vector>

#include "matrixAlgebra.h"

using namespace std;

// addition of matrices
vector<vector<float>> add(vector<vector<float>> &mat1, vector<vector<float>> &mat2)
{

    int row1 = mat1.size(), col1 = mat1[0].size(), row2 = mat2.size(), col2 = mat2[0].size();

    if (row1 != row2 or col1 != col2)
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

// multiplication of matrices

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