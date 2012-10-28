#include "tests.hpp"
#include "Algorithm.hpp"
#include <algorithm>
#include <iostream>

double calcFitness(const ga::Individual<>& individual) {
    auto&& genes = individual.getGenes();
    return std::count(genes.begin(), genes.end(), true);
}

void algo() {
     // constexpr int populationSize = 8;
     // constexpr int genomeSize = 12;
     // ga::Algorithm<> ga(populationSize, genomeSize);

     // constexpr double fitness = genomeSize; //end condition
     // constexpr double mutate = 0.01;
     // std::cout << "Individual is " << ga.run(fitness, calcFitness, mutate) << std::endl;
}


int main() {
    asserts();
    return 0;
}
