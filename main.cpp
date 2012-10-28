#include "Algorithm.hpp"

int main() {
    constexpr int populationSize = 12;
    constexpr int genomeSize = 8;
    ga::Algorithm<> ga(populationSize, genomeSize);
    //ga.run();
    return 0;
}
