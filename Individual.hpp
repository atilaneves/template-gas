#ifndef _INDIVIUAL_HPP_
#define _INDIVIUAL_HPP_

#include "Random.hpp"
#include <vector>
#include <tuple>
#include <iostream>
#include <functional>

namespace ga {

    template<typename GENE = bool, class CONTAINER = std::vector<GENE>>
    class Individual {
    public:
        typedef GENE Gene;
        typedef CONTAINER Container;
        typedef std::tuple<Individual, Individual> ChildrenTuple;
        typedef std::function<void(Container&)> MutateFunc;
        typedef std::tuple<Container, Container> ContainerTuple;
        typedef std::function<ContainerTuple(const Container&, const Container&)> XoverFunc;
                
        Individual(unsigned size);        
        Individual(const Container& genes): _genes(genes) { }
        Individual(Container&& genes): _genes(std::move(genes)) { }
        Individual(Container&& genes, const MutateFunc& mutate):
            _genes(std::move(genes)) {
            mutate(_genes);
        }

        static ChildrenTuple createChildren(const Individual& father, const Individual& mother,
                                            const XoverFunc& xover, const MutateFunc& mutate);
        const Container& getGenes() const { return _genes; }
        
    private:

        Container _genes;
    };

    template<typename GENE, class CONTAINER>
    Individual<GENE, CONTAINER>::Individual(const unsigned size) {
        UniformIntDistribution<GENE> random;
        for(unsigned i = 0; i < size; ++i) {
            _genes.push_back(random());
        }
    }

    template<typename GENE, class CONTAINER>
    auto Individual<GENE, CONTAINER>::createChildren(const Individual& father,
                                                     const Individual& mother,
                                                     const XoverFunc& xover,
                                                     const MutateFunc& mutate) -> ChildrenTuple {
        Container child1, child2;
        std::tie(child1, child2) = xover(father._genes, mother._genes);
        return std::forward_as_tuple(Individual(std::move(child1), mutate),
                                     Individual(std::move(child2), mutate));
    }
}

template<typename GENE, class CONTAINER>
std::ostream& operator<<(std::ostream &out, const ga::Individual<GENE, CONTAINER>& individual) {
    out << "    ";
    for(auto gene: individual.getGenes()) {
        out << gene;
    }
    out << std::endl;
    return out;
}


#endif
