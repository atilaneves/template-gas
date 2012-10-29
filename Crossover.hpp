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
    auto SinglePointCrossover<INDIVIDUAL>::operator()(const Container& father,
                                                      const Container& mother) const -> MyTuple {
        UniformIntDistribution<> random(0, father.size() - 1);
        const int xoverPoint = random();

        Container child1(father.size());
        Container child2(father.size());

        std::copy(father.cbegin(), father.cbegin() + xoverPoint, child1.begin());
        std::copy(mother.cbegin(), mother.cbegin() + xoverPoint, child2.begin());

        std::copy(mother.cbegin() + xoverPoint, mother.cend(), child1.begin() + xoverPoint);
        std::copy(father.cbegin() + xoverPoint, father.cend(), child2.begin() + xoverPoint);

        return std::make_tuple(child1, child2);
    }
}

#endif
