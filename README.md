# Homework 2: Streaming Submodular Maximization
## Code Structure
```
Root
├── datasets
│   ├── corel16k
│   └── delicious
├── images
├── results
├── utils
│   ├── Plot.py           (Draw plots in the report)
│   └── ProcessRawData.py (Preprocessing the raw data)
├── Alogrithms.cpp        (Implement Standard Greedy, Streaming Greedy and Reservior Sampling)
├── UtiliyFunc.hpp        (Implenent the submodular function)
├── main.cpp              (Main function to run the experiment)
└── experiment.sh         (Compile and run all the experiments)
``````
## Usage
First run ```ProcessRawData.py``` to process the raw data, then execute ```./experiment.sh``` to generate all expriment results, finally run ```Plot.py``` to draw plots of the results.