#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "matrixio.h"
#include "optimization.h"
#include "latency_openblas.h";

using namespace std;

// different file and executable for openblas to avoid conficts between mkl and openblas
int main(int argc, const char *argv[])
{
    if (argc == 1)
    {
        cout << "This executable only supports fullyconnected task. Use it as: " << '\n'
             << "./openblas_mm.out fullyconnected (input_matrix_filename) (weight_matrix_filename) (bias_matrix_filename) (output_matrix_filename) openblas" << '\n';
        return 0;
    }

    string task(argv[1]); // only fullyconnected for openblas
    try
    {

        if (task == "fullyconnected")
        {

            if (argc < 7)
            {
                throw("fully connected requires arguments in the form of fullyconnected (input_matrix_filename) (weight_matrix_filename) (bias_matrix_filename) (output_matrix_filename) openblas");
            }
            string inputMatFileName(argv[2]), weightMatFileName(argv[3]), biasMatFileName(argv[4]), outputFileName(argv[5]);
            // get input, weight and bias matrices
            vector<vector<float>> mat = read(inputMatFileName), weights = read(weightMatFileName), bias = read(biasMatFileName);
            if (argc == 7)
            {
                // openblas implementation
                string optimization(argv[6]);
                if (optimization == "openblas")
                {
                    pair<vector<vector<float>>, double> result = mulAndAdd_openblas(mat, weights, bias);
                    write(result.first, outputFileName);
                }
                else
                {
                    throw(optimization + " is not supported use openblas");
                }
            }
        }
        else if (task == "calclatency")
        {
            computeLatencies();
        }
        else
        {
            // invalid function module
            throw(task + " is an invalid argument to the program , this excutable supports only fullyconnected version of openblas");
        }
    }
    catch (string exp)
    {
        // ERROR HANDLING
        cout << "ERROR:  PROGRAM TERMINATING....\n";
        cout << exp << "\n";
    }
    catch (char const *exp)
    {
        cout << "ERROR:  PROGRAM TERMINATING....\n";
        cout << exp << "\n";
    }
    return 0;
}