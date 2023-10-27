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
    
    for(int k = 10; k<5000; k+=1000)
    {
        std::cout << "k: " << k << " utility: " << StandardGreedy(inputFile,k) << std::endl;
        inputFile.clear();
        inputFile.seekg(0);
    }


    inputFile.close();
    return 0;
}
