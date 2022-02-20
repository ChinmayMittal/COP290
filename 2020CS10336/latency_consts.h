#pragma once

#include <vector>
#include <string>

const std::vector<std::string> DEFAULT_FILES{"mat10x10_0.txt", "mat10x10_1.txt", "mat10x10_2.txt", "mat20x20_0.txt", "mat20x20_1.txt", "mat20x20_2.txt"};
const std::vector<std::string> DEFAULT_LABELS{"10x10", "20x20"};
const std::string OUT_NAIVE = "naive.dat";
const std::string OUT_MULTITHREADED = "multithreaded.dat";
const std::string OUT_OPENBLAS = "openblas.dat";
const std::string OUT_MKL = "mkl.dat";
const int RUNS = 100;