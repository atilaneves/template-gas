#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "Individual.hpp"
#include "Tournament.hpp"
#include "Mutate.hpp"
#include "Crossover.hpp"
#include <iostream>

namespace ga {

    template<typename GENE = bool, class CONTAINER = std::vector<GENE>>
    class Algorithm {
    public:
	typedef Individual<GENE, CONTAINER> MyIndividual;

	Algorithm(unsigned populationSize, unsigned genomeSize);

	template<class FITNESS,
		 class SELECT = Tournament<MyIndividual>,
		 class XOVER = SinglePointCrossover<MyIndividual>,
		 class MUTATE = Mutate<MyIndividual>>
        const MyIndividual& run(double fitness, const FITNESS& fitnessFunc, const SELECT& select,
				const XOVER& xover, const MUTATE& mutate);
	template<class FITNESS>
	const MyIndividual& run(double fitness, const FITNESS& fitnessFunc,
				double mutateRate, double xoverRate = 1.0);

    private:
	typedef std::vector<MyIndividual> Population;

	Population _population;

	template<class FITNESS>
	const MyIndividual& getFittest(const FITNESS& fitnessFunc) const {
	    return *std::max_element(_population.begin(), _population.end(),
				     [&](const MyIndividual& i1, const MyIndividual& i2) {
					 return fitnessFunc(i1) < fitnessFunc(i2); });
	}

	template<class FITNESS>
	std::multimap<double, const MyIndividual*> rankPopulation(const FITNESS& fitnessFunc) const {
	    std::multimap<double, const MyIndividual*> ranked;
	    for(const MyIndividual& ind: _population) {
		ranked.insert(std::make_pair(fitnessFunc(ind), &ind));
	    }

	    return std::move(ranked);
	}
    };

    template<typename GENE, class CONTAINER>
    Algorithm<GENE, CONTAINER>::Algorithm(unsigned populationSize, unsigned genomeSize) {
	for(unsigned i = 0; i < populationSize; ++i) {
	    _population.push_back(MyIndividual(genomeSize));
	}
    }

    template<typename GENE, class CONTAINER>
    template<class FITNESS, class SELECT, class XOVER, class MUTATE>
    const typename Algorithm<GENE, CONTAINER>::MyIndividual& //return value
    Algorithm<GENE, CONTAINER>::run(double fitness, const FITNESS& fitnessFunc, const SELECT& select,
				    const XOVER& xover, const MUTATE& mutate) {
	const MyIndividual& fittest = getFittest(fitnessFunc);
	int i = 0;
	while(fitnessFunc(getFittest(fitnessFunc)) < fitness) {
	    std::cout << "Generation " << i << std::endl;
	    for(const MyIndividual& ind: _population) std::cout << ind;
	    std::cout << std::endl;
	    
	    Population newPopulation;
	    newPopulation.reserve(_population.size());

	    while(newPopulation.size() < _population.size()) {
		const auto ranked = rankPopulation(fitnessFunc);
		const auto parents = select(ranked);
		auto children = MyIndividual::createChildren(std::get<0>(parents), std::get<1>(parents),
							     xover, mutate);
		newPopulation.push_back(std::move(std::get<0>(children)));
		newPopulation.push_back(std::move(std::get<1>(children)));
	    }
	    ++i;
	}
	return fittest;
    }

    template<typename GENE, class CONTAINER>
    template<class FITNESS>
    const typename Algorithm<GENE, CONTAINER>::MyIndividual& //return value
    Algorithm<GENE, CONTAINER>::run(double fitness, const FITNESS& fitnessFunc,
				    double mutateRate, double xoverRate) {
	return run(fitness, fitnessFunc, Tournament<MyIndividual>(),
		   SinglePointCrossover<MyIndividual>(xoverRate),
		   Mutate<MyIndividual>(mutateRate));
    }
}

#endif
