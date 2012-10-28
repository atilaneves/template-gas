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
	    	    
	~Individual() { std::cout << "Individual dying\n"; }
	explicit Individual(unsigned size);
	Individual(Individual&& individual):_genes(std::move(individual._genes)) {
	    std::cout << "Robbing from individual\n";
	}
	Individual(const Container& genes): _genes(genes) {
	    std::cout << "Copying from genes\n";
	}
	Individual(Container&& genes): _genes(std::move(genes)) {
	    std::cout << "Robbing from genes\n";
	}
	template<class MUTATE>
	Individual(Container&& genes, const MUTATE& mutate):_genes(std::move(genes)) {
	    std::cout << "Mutating\n";
	    mutate(_genes);
	}

	template<class XOVER, class MUTATE>
	static std::tuple<Individual, Individual>&& createChildren(const Individual& father,
								   const Individual& mother,
								   const XOVER& xover,
								   const MUTATE& mutate);
	const Container& getGenes() const { return _genes; }
	    
    private:

	Container _genes;
	    
	Individual() = delete;
	Individual(const Individual& i) = delete;
	Individual& operator=(const Individual& i) = delete;
    };

    template<typename GENE, class CONTAINER>
    Individual<GENE, CONTAINER>::Individual(const unsigned size) {
	std::cout << "Creating random individual\n";
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
	Container child1, child2;
	std::tie(child1, child2) = xover(father._genes, mother._genes);
	return std::forward_as_tuple(Individual(std::move(child1), mutate),
				     Individual(std::move(child2), mutate));
    }
}

template<typename GENE, class CONTAINER>
std::ostream& operator<<(std::ostream &out, const ga::Individual<GENE, CONTAINER>& individual) {
    out << "    ";
    for(GENE gene: individual.getGenes()) {
	out << gene;
    }
    out << std::endl;
    return out;
}


#endif
