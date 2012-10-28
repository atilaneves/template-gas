#ifndef _INDIVIUAL_HPP_
#define _INDIVIUAL_HPP_

#include "Random.hpp"
#include <vector>
#include <tuple>
#include <iostream>

namespace ga {

    template<typename GENE = bool, class CONTAINER = std::vector<GENE>>
    class Individual {
    public:
	typedef GENE Gene;
	typedef CONTAINER Container;
	    	    
	Individual(unsigned size);
	Individual(Individual&& individual):_genes(std::move(individual._genes)) { }
	template<class MUTATE>
	Individual(Container&& genes, const MUTATE& mutate):_genes(genes) { mutate(_genes); }

	template<class XOVER, class MUTATE>
	static std::tuple<Individual, Individual>&& createChildren(const Individual& father,
								   const Individual& mother,
								   const XOVER& xover,
								   const MUTATE& mutate);
	const Container& getGenes() const { return _genes; }
	    
    private:

	Container _genes;
	    
	Individual(const Individual& i) = delete;
    };

    template<typename GENE, class CONTAINER>
    Individual<GENE, CONTAINER>::Individual(const unsigned size) {
	UniformIntDistribution<GENE> random;
	for(unsigned i = 0; i < size; ++i) {
	    _genes.push_back(random());
	}
    }

    template<typename GENE, class CONTAINER>
    template<class XOVER, class MUTATE>
    std::tuple<Individual<GENE, CONTAINER>, Individual<GENE, CONTAINER>>&&//return value
	Individual<GENE, CONTAINER>::createChildren(const Individual& father,
						    const Individual& mother,
						    const XOVER& xover,
						    const MUTATE& mutate) {
	std::tuple<Container, Container> genes = xover(father._genes, mother._genes);
	return std::forward_as_tuple(Individual(std::move(std::get<0>(genes)), mutate),
				     Individual(std::move(std::get<1>(genes)), mutate));
    }
}

template<typename GENE, class CONTAINER>
std::ostream& operator<<(std::ostream &out, const ga::Individual<GENE, CONTAINER> &individual) {
    out << "    ";
    for(GENE gene: individual.getGenes()) {
	out << gene;
    }
    out << std::endl;
    return out;
}

#endif
