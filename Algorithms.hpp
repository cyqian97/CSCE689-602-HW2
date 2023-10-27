#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <list>
#include <fstream>
#include "UtiliyFunc.hpp"

int StandardGreedy(std::ifstream& inputFile, int k);

int StreamGreedy(std::ifstream& inputFile, int k);

int ReservoirSampling(std::ifstream& inputFile, int k);

#endif