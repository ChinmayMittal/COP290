#include <vector>
#include <cmath>

#include "softmax.h"

using namespace std;

void softmax(vector<float> &arr)
{

    float sum = 0; // calculates the denominator used later in the softmax

    for (auto ele : arr)
        sum += exp(ele);
    for (auto &ele : arr)
        ele = exp(ele) / sum;

    return;
}