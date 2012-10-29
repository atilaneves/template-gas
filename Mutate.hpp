#ifndef _MUTATE_H_
#define _MUTATE_H_

#include "Random.hpp"
#include "Individual.hpp"
#include <iostream>

namespace ga {

    template<class INDIVIDUAL = Individual<>>
    class Mutate {
    public:
        typedef typename INDIVIDUAL::Container Container;
        typedef typename INDIVIDUAL::Gene Gene;

        Mutate(double rate):_rate(rate) { }
        void operator()(Container& container) const;
    private:
        double _rate;
    };

    template<class INDIVIDUAL>
    void Mutate<INDIVIDUAL>::operator()(Container& container) const {
        UniformIntDistribution<Gene> randomGene;
        UniformRealDistribution<> rate;
        for(auto gene: container) {
            if(rate() < _rate) {
                gene = randomGene();
            }
        }
    }
    
}

#endif
