#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>

#include "latency_others.h"

#include "latency_consts.h"
#include "matrixAlgebra.h"
#include "matrixio.h"
#include "optimization.h"
#include "timing.h"

void computeLatencies(std::vector<std::string> files, std::vector<std::string> labels)
{
    std::ofstream naiveFile;
    naiveFile.open(OUT_NAIVE);

    std::ofstream multithreadedFile;
    multithreadedFile.open(OUT_MULTITHREADED);

    std::ofstream mklFile;
    mklFile.open(OUT_MKL);

    for (size_t i = 0; i < files.size(); i += 3)
    {
        std::vector<std::vector<float>> mat = read(files[i]);
        std::vector<std::vector<float>> weights = read(files[i + 1]);
        std::vector<std::vector<float>> bias = read(files[i + 2]);

        double mean = 0;
        double sd = 0;

        for (size_t j = 0; j < RUNS; j++)
        {
            std::pair<std::vector<std::vector<float>>, double> result = pthreadOpt(mat, weights, bias);

            double latency = 1000 * result.second;
            mean += latency;
            sd += latency * latency;
        }

        mean /= RUNS;
        sd /= RUNS;
        sd -= mean * mean;
        sd = sqrt(sd);

        multithreadedFile << i / 3 << "\t" << labels[i / 3] << "\t" << mean << "\t" << sd << '\n';

        mean = 0;
        sd = 0;

        for (size_t j = 0; j < RUNS; j++)
        {
            std::pair<std::vector<std::vector<float>>, double> result = mklOpt(mat, weights, bias);

            double latency = 1000 * result.second;
            mean += latency;
            sd += latency * latency;
        }

        mean /= RUNS;
        sd /= RUNS;
        sd -= mean * mean;
        sd = sqrt(sd);

        mklFile << i / 3 << "\t" << labels[i / 3] << "\t" << mean << "\t" << sd << '\n';

        mean = 0;
        sd = 0;

        for (size_t j = 0; j < RUNS; j++)
        {
            auto t1 = get_time();
            vector<vector<float>> mulMat = mul(mat, weights); // matrix multiplication
            vector<vector<float>> ans = add(mulMat, bias);    // matrix addition
            auto t2 = get_time();
            double latency = 1000 * getTimeDuration(t1, t2);
            mean += latency;
            sd += latency * latency;
        }

        mean /= RUNS;
        sd /= RUNS;
        sd -= mean * mean;
        sd = sqrt(sd);

        naiveFile << i / 3 << "\t" << labels[i / 3] << "\t" << mean << "\t" << sd << '\n';
    }
}

void computeLatencies()
{
    computeLatencies(DEFAULT_FILES, DEFAULT_LABELS);
}