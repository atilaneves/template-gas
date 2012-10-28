#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "Individual.hpp"
#include "Tournament.hpp"
#include "Mutate.hpp"
#include "Crossover.hpp"

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
        MyIndividual* run(double fitness, const FITNESS& fitnessFunc, const SELECT& select,
			  const XOVER& xover, const MUTATE& mutate);
	template<class FITNESS>
	MyIndividual* run(double fitness, const FITNESS& fitnessFunc,
			  double mutateRate, double xoverRate = 1.0);

    private:
	typedef std::vector<MyIndividual> Population;

	Population _population;
    };

    template<typename GENE, class CONTAINER>
    Algorithm<GENE, CONTAINER>::Algorithm(unsigned populationSize, unsigned genomeSize) {
	for(unsigned i = 0; i < populationSize; ++i) {
	    _population.push_back(MyIndividual(genomeSize));
	}
    }

    template<typename GENE, class CONTAINER>
    template<class FITNESS, class SELECT, class XOVER, class MUTATE>
    typename Algorithm<GENE, CONTAINER>::MyIndividual* //return value
    Algorithm<GENE, CONTAINER>::run(double fitness, const FITNESS& fitnessFunc, const SELECT& select,
				    const XOVER& xover, const MUTATE& mutate) {
	return nullptr;
    }

    template<typename GENE, class CONTAINER>
    template<class FITNESS>
    typename Algorithm<GENE, CONTAINER>::MyIndividual* //return value
    Algorithm<GENE, CONTAINER>::run(double fitness, const FITNESS& fitnessFunc,
				    double mutateRate, double xoverRate) {
	return run(fitness, fitnessFunc, Tournament<MyIndividual>(),
		   SinglePointCrossover<MyIndividual>(xoverRate),
		   Mutate<MyIndividual>(mutateRate));
    }

}

#endif
