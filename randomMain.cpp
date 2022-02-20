#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "genRandom.cpp"
#include "matrixio.cpp"

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

    bool mult = mode == "mult";

    if (mult && argc < 4)
    {
        std::cout << USAGE << '\n';
        return 0;
    }

    int nmats = mult ? std::stoi(argv[2]) : 0;
    int rows = mult ? std::stoi(argv[3]) : std::stoi(argv[2]);

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

    std::string outputFile;
    if (mult)
    {
        outputFile = "mat" + std::to_string(rows) + "x" + std::to_string(cols) + "_";
    }
    else if (argc > 4)
    {
        outputFile = argv[4];
    }
    else
    {
        outputFile = "mat" + std::to_string(rows) + "x" + std::to_string(cols) + ".txt";
    }

    float maxVal = argc > 5 ? std::stof(argv[5]) : 100;

    if (!mult)
    {
        std::vector<std::vector<float>> res = genRandomMatrix(rows, cols, maxVal);
        write(res, outputFile);
        return 0;
    }

    for (size_t i = 0; i < nmats; i++)
    {
        std::vector<std::vector<float>> res = genRandomMatrix(rows, cols, maxVal);
        write(res, outputFile + to_string(i) + ".txt");
    }

    return 0;
}
