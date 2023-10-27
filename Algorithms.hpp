#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <list>
#include <random>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "UtiliyFunc.hpp"

int StandardGreedy(std::ifstream& inputFile, int k);

int StreamGreedy(std::ifstream& inputFile, int k, double eps);

int ReservoirSampling(std::ifstream& inputFile, int k);

#endif