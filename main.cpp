#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include "Algorithms.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2 && !(argc == 7 && (strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "-k") == 0)))
    {
        std::cerr << "Usage:\t" << argv[0] << " <input_filename> "
                  << "(-k) "
                  << "(init k) "
                  << "(end k) "
                  << "(step) "
                  << "(epsilon)" << std::endl
                  << "\t" << argv[0] << " <input_filename> "
                  << "(-e) "
                  << "(k) "
                  << "(init eps) "
                  << "(end eps) "
                  << "(step)" << std::endl;
        return 1;
    }

    int init_k = 10;
    int end_k = 100;
    double init_eps = 0.1;
    double end_eps = 0;
    double step = 5;

    if (argc == 7)
    {
        if (strcmp(argv[2], "-k") == 0)
        {
            init_k = std::stoi(argv[3]);
            end_k = std::stoi(argv[4]);
            step = std::stoi(argv[5]);
            init_eps = std::stod(argv[6]);
        }
        if (strcmp(argv[2], "-e") == 0)
        {
            init_k = std::stoi(argv[3]);
            init_eps = std::stod(argv[4]);
            end_eps = std::stod(argv[5]);
            step = std::stod(argv[6]);
            // std::cout << init_eps << ", " << end_eps << ", " << step << std::endl;
        }
    }

    std::string inputFilename = argv[1];

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

    std::string outputFileName;
    if (argc < 7)
        outputFileName = "results/" + filenameWithoutExtension + "_results.txt";
    else
        outputFileName = "results/" + filenameWithoutExtension + argv[2] + "_results.txt";

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

    if (argc == 2 || strcmp(argv[2], "-k") == 0)
    {
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
            int res2 = StreamGreedy(inputFile, k, init_eps, num_eval2);
            std::cout << "2: " << res2 << compare(res2, res0 * (0.5 - init_eps)) << res0 << "*(1/2-eps=" << init_eps << ")\t"
                      << "n_eval 0: " << num_eval0 << "\t1: " << num_eval2 << std::endl;
            outputFile << k << ", " << res0 << ", " << res1 << ", " << res2 << ", " << num_eval0 << ", " << num_eval2 << std::endl;
            inputFile.clear();
            inputFile.seekg(0);
        }
    }
    else if (strcmp(argv[2], "-e") == 0)
    {
        // Standard greedy
        int num_eval0;
        int res0 = StandardGreedy(inputFile, init_k, num_eval0);
        std::cout << "k: " << init_k << "\t0: " << res0 << std::endl;
        inputFile.clear();
        inputFile.seekg(0);

        for (double eps = init_eps; eps <= end_eps; eps += step)
        {
            int num_eval2;
            int res2 = StreamGreedy(inputFile, init_k, eps, num_eval2);
            std::cout << "esp: " << eps << "\t"
                      << "1: " << res0 << "\t"
                      << "2: " << res2 << "\t"
                      << "n_eval 0: " << num_eval0 << "\t1: " << num_eval2 << std::endl;
            outputFile << eps << ", " << res0 << ", " << res2 << ", " << num_eval0 << ", " << num_eval2 << std::endl;
            inputFile.clear();
            inputFile.seekg(0);
        }
    }
    inputFile.close();
    outputFile.close();
    return 0;
}
