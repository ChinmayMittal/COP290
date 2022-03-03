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
    for (size_t i = 0; i < (size_t)rows; i++)
    {
        for (size_t j = 0; j < (size_t)mat[0].size(); j++)
        {
            arr[i * cols + j] = mat[i][j];
        }
    }
}

std::vector<std::vector<float>> array1DToMat(double arr[], int rows, int cols)
{
    std::vector<std::vector<float>> res(rows, std::vector<float>(cols, 0));
    for (size_t i = 0; i < (size_t)rows; i++)
    {
        for (size_t j = 0; j < (size_t)cols; j++)
        {
            res[i][j] = arr[cols * i + j];
        }
    }
    return res;
}


std::vector<std::vector<float>> vectorToMatrix ( std::vector<float>vec , int rows , int columns , char order = 'R' ){

    std::vector<std::vector<float>> ans ( rows , std::vector<float>(columns , 0.0)) ; 

    if( order == 'R' ){
        for( size_t i = 0 ; i < (size_t)vec.size() ; i ++ )  {
            ans[i/columns][i%columns] = vec[i] ; 
        }
    }
    return ans ; 
}