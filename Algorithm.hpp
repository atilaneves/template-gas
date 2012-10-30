#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "Individual.hpp"
#include "Tournament.hpp"
#include "Mutate.hpp"
#include "SinglePointCrossover.hpp"
#include <functional>
#include <iostream>

namespace ga {

    template<typename GENE = bool, class CONTAINER = std::vector<GENE>>
    class Algorithm {
    public:
        typedef Individual<GENE, CONTAINER> MyIndividual;
        typedef std::function<double(const MyIndividual&)> FitnessFunc;
        
        Algorithm(unsigned populationSize, unsigned genomeSize);
        
        template<class SELECT, class XOVER, class MUTATE>
        const MyIndividual& run(double fitness, const FitnessFunc& fitnessFunc, const SELECT& select,
                                const XOVER& xover, const MUTATE& mutate);
        const MyIndividual& run(double fitness, const FitnessFunc& fitnessFunc,
                                double mutateRate, double xoverRate = 1.0);
        
    private:
        typedef std::vector<MyIndividual> Population;

        Population _population;

        const MyIndividual& getFittest(const FitnessFunc& fitnessFunc) const {
            return *std::max_element(_population.cbegin(), _population.cend(),
                                     [&](const MyIndividual& i1, const MyIndividual& i2) {
                                         return fitnessFunc(i1) < fitnessFunc(i2); });
        }

        double getHighestFitness(const FitnessFunc& fitnessFunc) const {
            std::vector<double> values(_population.size());
            std::transform(_population.cbegin(), _population.cend(), values.begin(),
                           [&](const MyIndividual& i) { return fitnessFunc(i); });
            return *std::max_element(values.cbegin(), values.cend());
        }

        template<class SELECT>
        typename SELECT::Rankings rankPopulation(const FitnessFunc& fitnessFunc) const {
            typename SELECT::Rankings ranked;
            for(const auto& ind: _population) {
                ranked.insert(std::make_pair(fitnessFunc(ind), std::cref(ind)));
            }

            return ranked;
        }

        void printGeneration(int generation) const {
            std::cout << "Generation " << generation << std::endl;
            for(const MyIndividual& ind: _population) std::cout << ind;
            std::cout << std::endl;
        }
    };

    template<typename GENE, class CONTAINER>
    Algorithm<GENE, CONTAINER>::Algorithm(unsigned populationSize, unsigned genomeSize) {
        for(unsigned i = 0; i < populationSize; ++i) {
            _population.push_back(MyIndividual(genomeSize));
        }
    }

    template<typename GENE, class CONTAINER>
    template<class SELECT, class XOVER, class MUTATE>
    auto Algorithm<GENE, CONTAINER>::run(double fitness, const FitnessFunc& fitnessFunc, const SELECT& select,
                                         const XOVER& xover, const MUTATE& mutate) -> const MyIndividual& {
        int generation = 0;
        while(getHighestFitness(fitnessFunc) < fitness) {
            printGeneration(generation);
            Population newPopulation;
            newPopulation.reserve(_population.size());

            while(newPopulation.size() < _population.size()) {
                const auto ranked = rankPopulation<SELECT>(fitnessFunc);
                const auto parents = select(ranked);
                auto children = MyIndividual::createChildren(std::get<0>(parents), std::get<1>(parents),
                                                             xover, mutate);
                newPopulation.push_back(std::move(std::get<0>(children)));
                newPopulation.push_back(std::move(std::get<1>(children)));
            }

            _population = std::move(newPopulation);
            ++generation;
        }
        printGeneration(generation);
        return getFittest(fitnessFunc);
    }

    template<typename GENE, class CONTAINER>
    auto Algorithm<GENE, CONTAINER>::run(double fitness, const FitnessFunc& fitnessFunc,
                                         double mutateRate, double xoverRate) -> const MyIndividual& {
        return run(fitness, fitnessFunc, Tournament<MyIndividual>(),
                   SinglePointCrossover<MyIndividual>(xoverRate),
                   Mutate<MyIndividual>(mutateRate));
    }
}

#endif
