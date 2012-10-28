#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "Random.hpp"
#include <algorithm>
#include <array>

namespace ga {
    template<class INDIVIDUAL>
    class SinglePointCrossover {
    public:
	typedef typename INDIVIDUAL::Container Container;
	typedef typename INDIVIDUAL::Gene Gene;
	typedef std::tuple<Container, Container> MyTuple;

	SinglePointCrossover(double rate = 1.0):_rate(rate) { }
	MyTuple&& xover(const Container& father, const Container& mother);
	
    private:
	double _rate;
    };

    template<class INDIVIDUAL>
    typename SinglePointCrossover<INDIVIDUAL>::MyTuple&& //return value
    SinglePointCrossover<INDIVIDUAL>::xover(const Container& father, const Container& mother) {
	
	UniformIntDistribution<> random(0, father.size());
	const int xoverPoint = random();

	std::vector<Container> genes;
	constexpr int numChildren = 2;
	std::array<const Container&, 2> parents = { std::ref(father), std::ref(mother) };
	for(int i = 0; i < numChildren; ++i) {
	    genes[i].reserve(father.size());
	    std::copy(parents[0].begin(), parents[0].begin() + xoverPoint, genes[i].begin());
	    std::copy(parents[1].begin() + xoverPoint, parents[1].end(), genes[i].begin() + xoverPoint);
	    std::reverse(parents.begin(), parents.end());
	}

	return std::move(genes);
    }
}

#endif
