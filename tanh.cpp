#include <vector>
#include <cmath>
using namespace std;

float tanH(float x)
{
    float negExp = exp(-x);
    float posExp = exp(x);
    return (posExp - negExp) / (posExp + negExp);
}

void tanH(vector<vector<float>> &mat)
{

    int m = mat.size(), n = mat[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = tanH(mat[i][j]);
        }
    }
}