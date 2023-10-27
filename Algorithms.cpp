#include "Algorithms.hpp"

int StandardGreedy(std::ifstream &inputFile, int k)
{
    std::list<type_element> set_ground;

    std::string line;
    while (std::getline(inputFile, line))
    {
        type_element bits(line);
        set_ground.push_back(bits);
    }

    UtiliyFunc f{};
    for (int i = 0; i < k; i++)
    {
        int max_marginal_gain = 0;
        std::list<type_element>::iterator it_max_element;
        for (std::list<type_element>::iterator it = set_ground.begin(); it != set_ground.end(); ++it)
        {
            int marginal_gain = f.marginal_gain(*it);
            if (marginal_gain >= max_marginal_gain)
            {
                max_marginal_gain = marginal_gain;
                it_max_element = it;
            }
        }
        f.add_element(*it_max_element);
        set_ground.erase(it_max_element);
    }

    return f.value();
}

int StreamGreedy(std::ifstream &inputFile, int k, double eps)
{
    // Initialize all threads with the first element
    std::list<int> list_est_order;
    std::list<UtiliyFunc> list_sets;

    std::string line;
    std::getline(inputFile, line);
    type_element bits(line);

    int max_singleton = bits.count();
    int lb = ceil(log(max_singleton) / log(1 + eps));
    int ub = floor(log(2 * k * max_singleton) / log(1 + eps));
    for (int i = lb; i <= ub; i++)
    {
        list_est_order.push_back(i);
        UtiliyFunc f{};
        f.add_element(bits);
        list_sets.push_back(f);
    }

    // Streaming
    while (std::getline(inputFile, line))
    {
        type_element bits(line);

        if (bits.count() > max_singleton) // Max singleton updated
        {
            max_singleton = bits.count();

            // New order range
            int lb = ceil(log(max_singleton) / log(1 + eps));
            int ub = floor(log(2 * k * max_singleton) / log(1 + eps));

            // Discard thread with orders two small
            for (int i = list_est_order.front(); i < lb; i++)
            {
                list_est_order.pop_front();
                list_sets.pop_front();
            }

            // Loop through all remaining threads, check the threshold condition
            std::list<int>::iterator it_order = list_est_order.begin();
            std::list<UtiliyFunc>::iterator it_set = list_sets.begin();

            for (int i = 0; i < list_est_order.size(); i++)
            {
                double mg_thr = (pow(1.0 + eps, *it_order) / 2.0 - it_set->value()) / (k - it_set->size());
                if (it_set->size() < k && it_set->marginal_gain(bits) >= mg_thr)
                {
                    it_set->add_element(bits);
                }
                it_order++;
                it_set++;
            }

            // Initialize new threads with higher orders
            for (int i = list_est_order.back() + 1; i <= ub; i++)
            {
                list_est_order.push_back(i);
                UtiliyFunc f{};
                f.add_element(bits);
                list_sets.push_back(f);
            }
        }
        else // Max singleton not updated
        {
            // Loop through all threads, check the threshold condition
            std::list<int>::iterator it_order = list_est_order.begin();
            std::list<UtiliyFunc>::iterator it_set = list_sets.begin();

            for (int i = 0; i < list_est_order.size(); i++)
            {
                double mg_thr = (pow(1.0 + eps, *it_order) / 2.0 - it_set->value()) / (k - it_set->size());
                if (it_set->size() < k && it_set->marginal_gain(bits) >= mg_thr)
                {
                    it_set->add_element(bits);
                }
                it_order++;
                it_set++;
            }
        }
    }

    // Return the maximum value in all threads
    int max_value = 0;
    for (auto &s : list_sets)
    {
        max_value = std::max(max_value, s.value());
    }
    return max_value;
}

int ReservoirSampling(std::ifstream &inputFile, int k)
{
    std::string line;
    int id_element = 0;
    std::vector<type_element> resorvior(k);
    while (std::getline(inputFile, line))
    {
        type_element bits(line);
        if (id_element < k)
        {
            resorvior[id_element] = bits;
        }
        else
        {
            int j = (rand() % (id_element + 1)) + 1;
            if (j < k)
            {
                resorvior[j] = bits;
            }
        }
        id_element++;
    }

    UtiliyFunc f{};
    for (type_element &bits : resorvior)
    {
        f.add_element(bits);
    }
    return f.value();
};