#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "Individual.hpp"
#include "Mutate.hpp"
#include "SinglePointCrossover.hpp"
#include "Tournament.hpp"
#include <functional>
#include <iostream>
#include <map>

namespace ga {
template<class INDIVIDUAL = Individual<>>
    class Algorithm {
    public:
        typedef std::function<double(const INDIVIDUAL&)> FitnessFunc;
        typedef typename INDIVIDUAL::MutateFunc MutateFunc;
        typedef typename INDIVIDUAL::XoverFunc XoverFunc;
        typedef typename SelectParents<INDIVIDUAL>::Rankings Rankings;
        typedef typename SelectParents<INDIVIDUAL>::ParentTuple ParentTuple;
        typedef typename SelectParents<INDIVIDUAL>::SelectFunc SelectFunc;
        
        Algorithm(unsigned populationSize, unsigned genomeSize);
        
        const INDIVIDUAL& run(double fitness, const FitnessFunc& fitnessFunc, const SelectFunc& select,
                              const XoverFunc& xover, const MutateFunc& mutate);
        const INDIVIDUAL& run(double fitness, const FitnessFunc& fitnessFunc,
                              double mutateRate, double xoverRate = 1.0);
        
    private:
        typedef std::vector<INDIVIDUAL> Population;

        Population _population;

        const INDIVIDUAL& getFittest(const FitnessFunc& fitnessFunc) const {
            return *std::max_element(_population.cbegin(), _population.cend(),
                                     [&](const INDIVIDUAL& i1, const INDIVIDUAL& i2) {
                                         return fitnessFunc(i1) < fitnessFunc(i2); });
        }

        double getHighestFitness(const FitnessFunc& fitnessFunc) const {
            std::vector<double> values(_population.size());
            std::transform(_population.cbegin(), _population.cend(), values.begin(),
                           [&](const INDIVIDUAL& i) { return fitnessFunc(i); });
            return *std::max_element(values.cbegin(), values.cend());
        }

        Rankings rankPopulation(const FitnessFunc& fitnessFunc) const {
            Rankings ranked;
            for(const auto& ind: _population) {
                ranked.insert(std::make_pair(fitnessFunc(ind), std::cref(ind)));
            }

            return ranked;
        }

        void printGeneration(int generation) const {
            std::cout << "Generation " << generation << std::endl;
            for(const INDIVIDUAL& ind: _population) std::cout << ind;
            std::cout << std::endl;
        }
    };

    template<class INDIVIDUAL>
    Algorithm<INDIVIDUAL>::Algorithm(unsigned populationSize, unsigned genomeSize) {
        for(unsigned i = 0; i < populationSize; ++i) {
            _population.push_back(INDIVIDUAL(genomeSize));
        }
    }

    template<class INDIVIDUAL>
    const INDIVIDUAL& Algorithm<INDIVIDUAL>::run(double fitness, const FitnessFunc& fitnessFunc,
                                                 const SelectFunc& select,
                                                 const XoverFunc& xover, const MutateFunc& mutate) {
        int generation = 0;
        while(getHighestFitness(fitnessFunc) < fitness) {
            printGeneration(generation);
            Population newPopulation;
            newPopulation.reserve(_population.size());

            while(newPopulation.size() < _population.size()) {
                const auto ranked = rankPopulation(fitnessFunc);
                const auto parents = select(ranked);
                auto children = INDIVIDUAL::createChildren(std::get<0>(parents), std::get<1>(parents),
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

    template<class INDIVIDUAL>
    const INDIVIDUAL& Algorithm<INDIVIDUAL>::run(double fitness, const FitnessFunc& fitnessFunc,
                                                 double mutateRate, double xoverRate) {
        return run(fitness, fitnessFunc, Tournament<INDIVIDUAL>(),
                   SinglePointCrossover<INDIVIDUAL>(xoverRate),
                   Mutate<INDIVIDUAL>(mutateRate));
    }
}

#endif
