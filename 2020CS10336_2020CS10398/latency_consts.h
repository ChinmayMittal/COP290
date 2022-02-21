#pragma once

#include <vector>
#include <string>

// Default matrix files to be used to compute latencies
const std::vector<std::string> DEFAULT_FILES{
    "mat10x10_0.txt", "mat10x10_1.txt", "mat10x10_2.txt",
    "mat20x20_0.txt", "mat20x20_1.txt", "mat20x20_2.txt",
    "mat30x30_0.txt", "mat30x30_1.txt", "mat30x30_2.txt",
    "mat50x50_0.txt", "mat50x50_1.txt", "mat50x50_2.txt",
    "mat75x75_0.txt", "mat75x75_1.txt", "mat75x75_2.txt",
    "mat100x100_0.txt", "mat100x100_1.txt", "mat100x100_2.txt",
    "mat125x125_0.txt", "mat125x125_1.txt", "mat125x125_2.txt",
    "mat150x150_0.txt", "mat150x150_1.txt", "mat150x150_2.txt",
    "mat200x200_0.txt", "mat200x200_1.txt", "mat200x200_2.txt",
    "mat250x250_0.txt", "mat250x250_1.txt", "mat250x250_2.txt",
    "mat300x300_0.txt", "mat300x300_1.txt", "mat300x300_2.txt",
    "mat400x400_0.txt", "mat400x400_1.txt", "mat400x400_2.txt",
    "mat500x500_0.txt", "mat500x500_1.txt", "mat500x500_2.txt"};

// Default x-axis labels to be used for latency plots.
const std::vector<std::string> DEFAULT_LABELS{"10x10", "20x20", "30x30", "50x50", "75x75", "100x100", "125x125", "150x150", "200x200", "250x250", "300x300", "400x400", "500x500"};

// Files to which computed latencies will be output. These are used by gnuplot to generate the plots.
const std::string OUT_NAIVE = "naive.dat";
const std::string OUT_MULTITHREADED = "multithreaded.dat";
const std::string OUT_OPENBLAS = "openblas.dat";
const std::string OUT_MKL = "mkl.dat";

// Number of runs per matrix to compute the mean latency.
const int RUNS = 500;