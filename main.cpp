#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

#include "Algorithms.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_filename>" << std::endl;
        return 1;
    }

    const char *inputFilename = argv[1];
    std::ifstream inputFile(inputFilename);

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file: " << inputFilename << std::endl;
        return 1;
    }

    double eps = 0.1;
    for (int k = 10; k < 210; k += 10)
    {
        int res0 = StandardGreedy(inputFile, k);
        std::cout << "k: " << k << "\t0: " << res0 << "\t";
        inputFile.clear();
        inputFile.seekg(0);

        std::cout << "1: " << ReservoirSampling(inputFile, k) << "\t";
        inputFile.clear();
        inputFile.seekg(0);

        auto compare = [](int a, int b) -> std::string
        {
            if (a > b)
            {
                return " > ";
            }
            else if (a < b)
            {
                return " < ";
            }
            else
            {
                return " = ";
            }
        };

        int res2 = StreamGreedy(inputFile, k, eps);
        std::cout << "2: " << res2 << compare(res2, res0 * (0.5 - eps)) << res0 << "*(1/2-eps)" << std::endl;
        inputFile.clear();
        inputFile.seekg(0);
    }

    inputFile.close();
    return 0;
}
