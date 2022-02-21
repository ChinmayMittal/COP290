#pragma once

#include <vector>
#include <string>

// Default matrix files to be used to compute latencies
const std::vector<std::string> DEFAULT_FILES{
    "mat10x10_0.txt", "mat10x10_1.txt", "mat10x10_2.txt",
    "mat20x20_0.txt", "mat20x20_1.txt", "mat20x20_2.txt",
    "mat50x50_0.txt", "mat50x50_1.txt", "mat50x50_2.txt",
    "mat100x100_0.txt", "mat100x100_1.txt", "mat100x100_2.txt",
    "mat200x200_0.txt", "mat200x200_1.txt", "mat200x200_2.txt"};

// Default x-axis labels to be used for latency plots.
const std::vector<std::string> DEFAULT_LABELS{"10x10", "20x20", "50x50", "100x100", "200x200"};

// Files to which computed latencies will be output. These are used by gnuplot to generate the plots.
const std::string OUT_NAIVE = "naive.dat";
const std::string OUT_MULTITHREADED = "multithreaded.dat";
const std::string OUT_OPENBLAS = "openblas.dat";
const std::string OUT_MKL = "mkl.dat";

// Number of runs per matrix to compute the mean latency.
const int RUNS = 100;