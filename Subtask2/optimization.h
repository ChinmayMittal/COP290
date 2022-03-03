#include<vector>
#include<utility>
using namespace std ; 

//optimization headers, all implementations result the output matrix and time ( in seconds and as double type) as a pair

pair<vector<vector<float>> , double > pthreadOpt(vector<vector<float>>&mat, vector<vector<float>>&weight, vector<vector<float>>&bias ) ; 
pair<vector<vector<float>> , double > mklOpt(vector<vector<float>>&mat, vector<vector<float>>&weights, vector<vector<float>>&bias) ; 
pair<vector<vector<float>> , double >  mulAndAdd_openblas(vector<vector<float>> &mat1, vector<vector<float>> &mat2, vector<vector<float>> &mat3) ; 