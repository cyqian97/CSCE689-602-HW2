#include <iostream>
#include <fstream>
#include <string>

#include "Algorithms.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 6)
    {
        std::cerr << "Usage: " << argv[0] << " <input_filename> "
                  << "(init k) "
                  << "(end k) "
                  << "(step) "
                  << "(epsilon)" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    int init_k = 10;
    int end_k = 100;
    int step = 5;
    double eps = 0.1;

    if (argc == 6)
    {
        init_k = std::stoi(argv[2]);
        end_k = std::stoi(argv[3]);
        step = std::stoi(argv[4]);
        eps = std::stod(argv[5]);
    }

    std::ifstream inputFile(inputFilename);

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file: " << inputFilename << std::endl;
        return 1;
    }

    // Extract the filename without extension
    size_t lastSlash = inputFilename.find_last_of("/\\");
    size_t lastDot = inputFilename.find_last_of(".");

    std::string filenameWithoutExtension;
    if (lastSlash != std::string::npos)
    {
        filenameWithoutExtension = inputFilename.substr(lastSlash + 1, lastDot - lastSlash - 1);
    }
    else
    {
        filenameWithoutExtension = inputFilename.substr(0, lastDot);
    }
    std::string outputFileName = "results/" + filenameWithoutExtension + "_results.txt";
    std::ofstream outputFile(outputFileName);
    if (!outputFile)
    {
        std::cerr << "Error: Failed to create output file." << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Result file: " << outputFileName << std::endl;
    }

    for (int k = init_k; k <= end_k; k += step)
    {
        int num_eval0;
        int res0 = StandardGreedy(inputFile, k, num_eval0);
        std::cout << "k: " << k << "\t0: " << res0 << "\t";
        inputFile.clear();
        inputFile.seekg(0);

        int res1 = ReservoirSampling(inputFile, k);
        std::cout << "1: " << res1 << "\t";
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

        int num_eval2;
        int res2 = StreamGreedy(inputFile, k, eps, num_eval2);
        std::cout << "2: " << res2 << compare(res2, res0 * (0.5 - eps)) << res0 << "*(1/2-eps=" << eps << ")\t"
                  << "n_eval 0: " << num_eval0 << "\t1: " << num_eval2 << std::endl;
        outputFile << k << ", " << res0 << ", " << res1 << ", " << res2 << ", " << num_eval0 << ", " << num_eval2 << std::endl;
        inputFile.clear();
        inputFile.seekg(0);
    }

    inputFile.close();
    outputFile.close();
    return 0;
}
