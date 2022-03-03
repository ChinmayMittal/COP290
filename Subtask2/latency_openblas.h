#pragma once

#include <vector>
#include <string>

// Function declarations corresponding to latency_openblas.cpp. Used to compute latencies
void computeLatencies(std::vector<std::string> files, std::vector<std::string> labels);
void computeLatencies();