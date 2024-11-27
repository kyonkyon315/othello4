#include "depthDecision.h"
#include <iostream>
double depthDecision::calcx( int difV) {
    return   log(1. + (double)(difV) / (2. * sigma)) / log(1 - p);
}
void depthDecision::setMaxValue(int maxValue_) {
    maxValue = maxValue_;
}

void depthDecision::init() {
    if (maxValue < 0) {
        std::cerr << "In void depthDecision::init()\n"
                  << "maxValue is smaller than zero.\n"
                  << "collect it using void depthDecision::setMaxValue()\n";
    }
    table = std::vector<int>(2 * maxValue);
    for (int i = 0; i < (int)table.size(); i++) {
        table[i] = (int)(calcx(i)+0.99);
    }
}

int depthDecision::getDepth(int kingDepth, int diffirenceOfValue) {
    if (diffirenceOfValue >= 2 * maxValue) {
        std::cout << diffirenceOfValue << "\n";
        std::cerr << "diffirenceOfValue is out of range\n" << std::flush;
    }
    return std::max(minDepth, kingDepth + table[diffirenceOfValue]);
}