g++ main.cpp Algorithms.cpp -o main

### Algorithm Comparison
# ./main datasets/corel16k/Corel16k001_filtered.txt      
# ./main datasets/corel16k/Corel16k002_filtered.txt      
# ./main datasets/corel16k/Corel16k003_filtered.txt      
# ./main datasets/corel16k/Corel16k004_filtered.txt      
# ./main datasets/corel16k/Corel16k005_filtered.txt      
# ./main datasets/corel16k/Corel16k006_filtered.txt      
# ./main datasets/corel16k/Corel16k007_filtered.txt      
# ./main datasets/corel16k/Corel16k008_filtered.txt      
# ./main datasets/corel16k/Corel16k009_filtered.txt      
# ./main datasets/delicious/delicious_filtered.txt -k 10 200 10 0.1

### Effects of epsilon
./main datasets/delicious/delicious_filtered.txt -e 100 0.01 0.5 0.01

