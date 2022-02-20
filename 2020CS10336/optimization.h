#include<vector>
#include<utility>
using namespace std ; 

pair<vector<vector<float>> , double > pthreadOpt(vector<vector<float>>&mat, vector<vector<float>>&weight, vector<vector<float>>&bias ) ; 
pair<vector<vector<float>> , double > mklOpt(vector<vector<float>>&mat, vector<vector<float>>&weights, vector<vector<float>>&bias) ; 
pair<vector<vector<float>> , double >  mulAndAdd_openblas(vector<vector<float>> &mat1, vector<vector<float>> &mat2, vector<vector<float>> &mat3) ; 