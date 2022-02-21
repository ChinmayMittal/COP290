#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "genRandom.h"
#include "matrixio.h"

/*
 * This utility program generates one or multiple random matrices of given size.
 * This is useful to generate matrices for calculating latencies and plotting.
 */
int main(int argc, char const *argv[])
{
    srand(time(0));
    const string USAGE = "USAGE:\nrandomMat mult <nmats> <nrows> [ncols [maxVal]]\nOR\nrandomMat one <nrows> [ncols [outFile [maxVal]]]";

    if (argc < 3 || argc > 6)
    {
        std::cout << USAGE << '\n';
        return 0;
    }

    string mode(argv[1]);
    if (mode != "mult" && mode != "one")
    {
        std::cout << USAGE << '\n';
        return 0;
    }

    // Mult corresponds to whether the mode is multi or one.
    bool mult = mode == "mult";

    if (mult && argc < 4)
    {
        std::cout << USAGE << '\n';
        return 0;
    }

    int nmats = mult ? std::stoi(argv[2]) : 0;
    int rows = mult ? std::stoi(argv[3]) : std::stoi(argv[2]);

    // If cols is given then use it, else set it equal to rows
    int cols = 0;
    if (mult && argc > 4)
    {
        cols = std::stoi(argv[4]);
    }
    else if (!mult && argc > 3)
    {
        cols = std::stoi(argv[3]);
    }
    else
    {
        cols = rows;
    }

    // If mode is multi or if filename is not given, filename(s) are auto generated.
    // Else use the name given.
    std::string outputFile;
    if (mult)
    {
        // In multi mode, filename is "mat(nrows)x(ncols)_(i).txt for ith matrix
        outputFile = "mat" + std::to_string(rows) + "x" + std::to_string(cols) + "_";
    }
    else if (argc > 4)
    {
        outputFile = argv[4];
    }
    else
    {
        // In one mode, filename is "mat(nrows)x(ncols).txt
        outputFile = "mat" + std::to_string(rows) + "x" + std::to_string(cols) + ".txt";
    }

    // If maxVal is given, use it. Else set it to 100.
    float maxVal = argc > 5 ? std::stof(argv[5]) : 100;

    // If mode is one, simply generate a single random matrix, output it and exit.
    if (!mult)
    {
        std::vector<std::vector<float>> res = genRandomMatrix(rows, cols, maxVal);
        write(res, outputFile);
        return 0;
    }

    // Mode is multi. So generate multiple matrices and output them.
    for (size_t i = 0; i < nmats; i++)
    {
        std::vector<std::vector<float>> res = genRandomMatrix(rows, cols, maxVal);
        write(res, outputFile + to_string(i) + ".txt");
    }

    return 0;
}
