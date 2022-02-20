#include <vector>
#include <cstdlib>

std::vector<std::vector<float>> genRandomMatrix(int rows, int cols, float max = 100)
{

    std::vector<std::vector<float>> res(rows, std::vector<float>(cols, 0));
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            res[i][j] = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * max;
        }
    }
    return res;
}