#include <vector>
using namespace std;

vector<vector<float>> add(vector<vector<float>> &mat1, vector<vector<float>> &mat2);
vector<vector<float>> mul(vector<vector<float>> &mat1, vector<vector<float>> &mat2);

std::vector<std::vector<float>> mulAndAdd_openblas(vector<vector<float>> &mat1, vector<vector<float>> &mat2, vector<vector<float>> &mat3);