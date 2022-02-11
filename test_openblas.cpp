#include <vector>
#include "matrixAlgebra.cpp"

void printMatrix(std::vector<std::vector<float>> mat)
{
    for (size_t i = 0; i < mat.size(); i++)
    {
        for (size_t j = 0; j < mat[0].size(); j++)
        {
            cout << mat[i][j] << "      ";
        }
        cout << std::endl;
    }
}
int main()
{
    std::vector<std::vector<float>> A(3, std::vector<float>(2, 0));
    std::vector<std::vector<float>> B(2, std::vector<float>(3, 0));
    std::vector<std::vector<float>> C(3, std::vector<float>(3, 0));

    A[0][0] = 1;
    B[0][0] = 2;
    B[0][1] = 3;

    C[0][0] = 1;
    C[0][1] = 5;

    std::vector<std::vector<float>> res = mulAndAdd_openblas(A, B, C);
    printMatrix(res);
}