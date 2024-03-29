#include "tests.hpp"
#include "Algorithm.hpp"
#include <algorithm>
#include <iostream>

double calcFitness(const ga::Individual<>& individual) {
    const auto& genes = individual.getGenes();
    return std::count(genes.cbegin(), genes.cend(), true);
}

void algo() {
    constexpr int populationSize = 20;
    constexpr int genomeSize = 12;
    ga::Algorithm<> geneticAlgo(populationSize, genomeSize);

    constexpr double fitness = genomeSize; //end condition
    constexpr double mutate = 0.05;
    const auto& winner = geneticAlgo.run(fitness, calcFitness, mutate);
    std::cout << "Individual of fitness " << calcFitness(winner) << " is " << winner;
}


int main() {
    //asserts();
    algo();
    return 0;
}
