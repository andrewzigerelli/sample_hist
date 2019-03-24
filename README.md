# sample_hist
Example on how to sample from a distribution (described as a histogram of values).

The histogram is a C++ map\<int, int> mapping value -> frequency.

## Usage
### build 
```
mkdir build;
cd build;
cmake ..
make
```
### run
./sample_hist

## TODO
Make the sample histogram not fixed. We can probably generate it by
drawing from `std::uniform_int_distribution<int>`.
