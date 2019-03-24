#include <iostream>
#include <string>
#include <map>
#include <random>
#include <cassert>

void printInfo(std::map<int, int> &hist, std::map<int, std::pair<int,int>> &intervals);
int findEntry(int loc, std::map<int, std::pair<int,int>> &intervals);
void printCompare(std::map<int, int> &hist, std::map<int, int> &new_hist);

#define DEBUG
#ifdef DEBUG
#define DPRINTINFO(x,y) printInfo(x,y);
#else
#define DPRINTINFO(x,y)
#endif

#define SAMPLE_SIZE 10e6

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd()); /* weak prng */
    std::map<int, int> hist;
    hist[1] = 1;
    hist[3] = 4;
    hist[5] = 3;
    hist[7] = 5;
    hist[9] = 3;
    hist[11] = 2;
    hist[13] = 1;
    hist[15] = 1;
    /* make intervals */
    std::map<int, std::pair<int,int>> intervals; /*distjoint, weighted according to hist */
    int max, length, upper_bound; 
    int lower_bound = 1;
    std::map<int, int>::iterator it;
    for (it = hist.begin(); it!= hist.end(); it++) {
        length = it->second;
        max += length;
        upper_bound = lower_bound + length - 1;
        intervals[it->first] = std::make_pair(lower_bound, upper_bound);
        /* for next iteration */
        lower_bound = upper_bound + 1;
    }
    std::uniform_int_distribution<int> dist(1, max);

    DPRINTINFO(hist, intervals)
    int loc, entry;
    std::map<int, int> new_hist;
    for (int n = 0; n < SAMPLE_SIZE; ++n) {
        loc = dist(gen);
        entry = findEntry(loc, intervals);
        ++new_hist[entry];
    }
    printCompare(hist, new_hist);
}
void printInfo(std::map<int, int> &hist, std::map<int, std::pair<int,int>> &intervals) {
    /* print hist and intervals */
    std::map<int, int>::iterator it;
    std::map<int, std::pair<int,int>>::iterator it2;
    it = hist.begin();
    it2 = intervals.begin();
    std::printf("%7s %4s\t%s\n", "value", "freq", "mapped range");
    while(it != hist.end()) {
        std::printf("%3d : %3d\t[%3d, %3d]\n", it->first, it->second,
                it2->second.first, it2->second.second);
        it++;
        it2++;
    }
}
int findEntry(int loc, std::map<int, std::pair<int,int>> &intervals){
    /* given loc, finds entry in intervals s.t.
     * pair(1) <= loc <= pair(2) */
    std::map<int, std::pair<int,int>>::iterator it;
    std::pair<int, int> interval;
    it = intervals.begin();
    while (it != intervals.end()) {
        interval = it->second;
        if ( loc >= interval.first && loc <= interval.second ) {
            return it->first;
        }
        it++;
    }
    assert(it != intervals.end()); //should never get here
}
void printCompare(std::map<int, int> &hist, std::map<int, int> &new_hist) {
    std::map<int, int>::iterator it = hist.begin();
    std::map<int, int>::iterator it2 = new_hist.begin();
    std::printf("%40s\n","Proportion comparisons");
    std::printf("\thist\t\tnew_hist\tabs diff\n");
    double first,second, diff;
    while(it != hist.end()) {
        first=static_cast<double>(it->second)/20;
        second=static_cast<double>(it2->second)/SAMPLE_SIZE;
        diff = std::abs(first - second);
        std::printf("%3d :\t%.3e\t%.3e\t%.3e\n",it->first, first, second, diff);
        it++;
        it2++;
    }
}
