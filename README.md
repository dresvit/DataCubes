## Introduction
This is an greedy algorithm which implements data cubes efficiently. It is an **approximation method**.

## Reference
> [1] [Implementing Data Cubes Efficiently. In SIGMOD 1996.]([SIGMOD 1996] Implementing Data Cubes Efficiently.pdf)

## Generate Dataset
* Compile: `g++ generate_data.cpp -o generate_data`
* Run: `./generate_data`
* You can change the size of the dataset.

## Run
* Compile: `g++ greedy.cpp -o greedy`
* Run: `./greedy -f input.txt -k n-1` where `n` is the number of views