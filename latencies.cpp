#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include "matrixio.cpp"

#include "matrixAlgebra.h"
#include "2020CS10336/timing.h"

const std::vector<std::string> DEFAULT_FILES{"mat10x10_0.txt", "mat10x10_1.txt", "mat10x10_2.txt"};
const std::vector<std::string> DEFAULT_LABELS{"10x10"};

const std::string OUT_NAIVE = "naive.dat";
const std::string OUT_MULTITHREADED = "multithreaded.dat";
const std::string OUT_OPENBLAS = "openblas.dat";
const std::string OUT_MKL = "mkl.dat";

const int RUNS = 100;

void computeLatencies(std::vector<std::string> files, std::vector<std::string> labels)
{
    std::ofstream naiveFile;
    naiveFile.open(OUT_NAIVE);

    std::ofstream multithreadedFile;
    multithreadedFile.open(OUT_MULTITHREADED);

    std::ofstream openblasFile;
    openblasFile.open(OUT_OPENBLAS);

    std::ofstream mklFile;
    mklFile.open(OUT_MKL);

    for (size_t i = 0; i < files.size() / 3; i += 3)
    {
        std::vector<std::vector<float>> A = read(files[i]);
        std::vector<std::vector<float>> B = read(files[i + 1]);
        std::vector<std::vector<float>> C = read(files[i + 2]);

        long long mean = 0;
        double sd = 0;

        for (size_t j = 0; j < RUNS; j++)
        {
            auto startTime = get_time();
            vector<vector<float>> mulMat = mul(A, B);   // matrix multiplication
            vector<vector<float>> ans = add(mulMat, C); // matrix addition
            auto endTime = get_time();
            std::chrono::duration<float> secs = endTime - startTime;
            std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(secs);
            long long millisCount = millis.count();
            mean += millisCount;
            sd += millisCount * millisCount;
        }

        mean /= RUNS;
        sd -= mean * mean;
        sd = sqrt(sd);

        naiveFile << i / 3 << "\t" << labels[i / 3] << "\t" << mean << "\t" << sd << '\n';

        mean = 0;
        sd = 0;

        for (size_t j = 0; j < RUNS; j++)
        {
            auto startTime = get_time();

            // TODO: Call multithreaded function

            auto endTime = get_time();
            std::chrono::duration<float> secs = endTime - startTime;
            std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(secs);
            long long millisCount = millis.count();
            mean += millisCount;
            sd += millisCount * millisCount;
        }

        mean /= RUNS;
        sd -= mean * mean;
        sd = sqrt(sd);

        multithreadedFile << i / 3 << "\t" << labels[i / 3] << "\t" << mean << "\t" << sd << '\n';

        mean = 0;
        sd = 0;

        for (size_t j = 0; j < RUNS; j++)
        {
            auto startTime = get_time();

            // TODO: Call openblas function

            auto endTime = get_time();
            std::chrono::duration<float> secs = endTime - startTime;
            std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(secs);
            long long millisCount = millis.count();
            mean += millisCount;
            sd += millisCount * millisCount;
        }

        mean /= RUNS;
        sd -= mean * mean;
        sd = sqrt(sd);

        openblasFile << i / 3 << "\t" << labels[i / 3] << "\t" << mean << "\t" << sd << '\n';

        mean = 0;
        sd = 0;

        for (size_t j = 0; j < RUNS; j++)
        {
            auto startTime = get_time();

            // TODO: Call MKL function

            auto endTime = get_time();
            std::chrono::duration<float> secs = endTime - startTime;
            std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(secs);
            long long millisCount = millis.count();
            mean += millisCount;
            sd += millisCount * millisCount;
        }

        mean /= RUNS;
        sd -= mean * mean;
        sd = sqrt(sd);

        mklFile << i / 3 << "\t" << labels[i / 3] << "\t" << mean << "\t" << sd << '\n';
    }
}

void computeLatencies()
{
    computeLatencies(DEFAULT_FILES, DEFAULT_LABELS);
}