#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "Random.hpp"
#include <algorithm>

namespace ga {
    template<class INDIVIDUAL>
    class SinglePointCrossover {
    public:
	typedef typename INDIVIDUAL::Container Container;
	typedef typename INDIVIDUAL::Gene Gene;

	SinglePointCrossover(double rate = 1.0):_rate(rate) { }
	Container&& xover(const Container& father, const Container& mother);
	
    private:
	double _rate;
    };

    template<class INDIVIDUAL>
    typename INDIVIDUAL::Container&& //return value
    SinglePointCrossover<INDIVIDUAL>::xover(const Container& father, const Container& mother) {
	
	UniformIntDistribution<> random(0, father.size());
	const int xoverPoint = random();

	Container genes;
	genes.reserve(father.size());

	std::copy(father.begin(), father.begin() + xoverPoint, genes.begin());
	std::copy(mother.begin() + xoverPoint, mother.end(), genes.begin() + xoverPoint);
	return std::move(genes);
    }
}

#endif
