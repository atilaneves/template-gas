#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

#include "Random.hpp"
#include <algorithm>
#include <array>
#include <iostream>

namespace ga {
    template<class INDIVIDUAL>
    class SinglePointCrossover {
    public:
	typedef typename INDIVIDUAL::Container Container;
	typedef typename INDIVIDUAL::Gene Gene;
	typedef std::tuple<Container, Container> MyTuple;

	SinglePointCrossover(double rate = 1.0):_rate(rate) { }
	MyTuple operator()(const Container& father, const Container& mother) const;
	
    private:
	double _rate;
    };

    template<class INDIVIDUAL>
    typename SinglePointCrossover<INDIVIDUAL>::MyTuple //return value
    SinglePointCrossover<INDIVIDUAL>::operator()(const Container& father, const Container& mother) const {
	
	UniformIntDistribution<> random(0, father.size());
	const int xoverPoint = random();
	std::cout << "Xover point is " << xoverPoint << std::endl;

	Container child1(father.begin(), father.begin() + xoverPoint);
	Container child2(mother.begin(), mother.begin() + xoverPoint);

	std::copy(father.begin() + xoverPoint, father.end(), child1.begin() + xoverPoint);
	std::copy(mother.begin() + xoverPoint, mother.end(), child2.begin() + xoverPoint);

	std::cout << "Returning tuple of vectors\n";
	return std::make_tuple(child1, child2);
    }
}

#endif
