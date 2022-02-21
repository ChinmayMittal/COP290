#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>

#include "latency_openblas.h"

#include "latency_consts.h"
#include "matrixio.h"
#include "optimization.h"

void computeLatencies(std::vector<std::string> files, std::vector<std::string> labels)
{

    std::ofstream openblasFile;
    openblasFile.open(OUT_OPENBLAS);

    for (size_t i = 0; i < files.size(); i += 3)
    {
        std::vector<std::vector<float>> mat = read(files[i]);
        std::vector<std::vector<float>> weights = read(files[i + 1]);
        std::vector<std::vector<float>> bias = read(files[i + 2]);

        double mean = 0;
        double sd = 0;

        for (size_t j = 0; j < RUNS; j++)
        {
            std::pair<std::vector<std::vector<float>>, double> result = mulAndAdd_openblas(mat, weights, bias);

            double latency = 1000 * result.second;
            mean += latency;
            sd += latency * latency;
        }

        mean /= RUNS;
        sd /= RUNS;
        sd -= mean * mean;
        sd = sqrt(sd);

        openblasFile << i / 3 << "\t" << labels[i / 3] << "\t" << mean << "\t" << sd << '\n';
    }
}

void computeLatencies()
{
    computeLatencies(DEFAULT_FILES, DEFAULT_LABELS);
}