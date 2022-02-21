#include <vector>

#include "matarr.h"

/*
    Helper functions for data format conversion of matrices
    from vector of vectors to 2-D arrays stored contiguosly in memory ( row major order) or vice-versa
*/
void matToArray1D(std::vector<std::vector<float>> &mat, double arr[])
{
    int rows = mat.size();
    int cols = mat[0].size();
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < mat[0].size(); j++)
        {
            arr[i * cols + j] = mat[i][j];
        }
    }
}

std::vector<std::vector<float>> array1DToMat(double arr[], int rows, int cols)
{
    std::vector<std::vector<float>> res(rows, std::vector<float>(cols, 0));
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            res[i][j] = arr[cols * i + j];
        }
    }
    return res;
}