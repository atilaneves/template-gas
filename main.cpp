#include "Algorithm.hpp"
#include <algorithm>
#include <iostream>

double calcFitness(const ga::Individual<>& individual) {
    auto&& genes = individual.getGenes();
    return std::count(genes.begin(), genes.end(), true);
}

int main() {
    constexpr int populationSize = 12;
    constexpr int genomeSize = 8;
    ga::Algorithm<> ga(populationSize, genomeSize);

    constexpr double fitness = genomeSize; //end condition
    constexpr double mutate = 0.01;
    std::cout << "Pointer to the individual is " << ga.run(fitness, calcFitness, mutate) << std::endl;
    return 0;
}
