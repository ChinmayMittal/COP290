#include <vector>

#include "relu.h"

using namespace std;

// matrix and single element relu activation

float ReLU(float x)
{
    if (x >= 0)
    {
        return x;
    }
    else
    {
        return 0;
    }
}

void ReLU(vector<vector<float>> &mat)
{

    int m = mat.size(), n = mat[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = ReLU(mat[i][j]);
        }
    }
}
