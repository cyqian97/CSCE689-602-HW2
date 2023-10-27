#include "Algorithms.hpp"


int StandardGreedy(std::ifstream& inputFile, int k){
    std::list<type_set> set_ground;
    
    std::string line;
    while (std::getline(inputFile, line))
    {
        type_set bits(line);
        set_ground.push_back(bits);
    }
    

    UtiliyFunc f{};
    for(int i=0; i<k; i++){
        int max_marginal_gain = 0;
        std::list<type_set>::iterator it_max_element;
        for (std::list<type_set>::iterator it=set_ground.begin(); it!=set_ground.end(); ++it){
            int marginal_gain = f.marginal_gain(*it);
            if(marginal_gain>=max_marginal_gain){
                max_marginal_gain = marginal_gain;
                it_max_element = it;
            }
        }
        f.add_element(*it_max_element);
        set_ground.erase(it_max_element);
    }

    return f.value();
}

// int StreamGreedy(std::ifstream& inputFile, int k){};

// int ReservoirSampling(std::ifstream& inputFile, int k){};