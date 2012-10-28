#ifndef _INDIVIUAL_HPP_
#define _INDIVIUAL_HPP_

#include <vector>
#include <random>

namespace ga {

    template<typename GENE = bool, class CONTAINER = std::vector<GENE>>
    class Individual {
    public:	    	    
	Individual(unsigned size);
	Individual(Individual&& individual):_genes(std::move(individual._genes)) { }
	template<class XOVER, class MUTATE>
	Individual(const Individual& father, const Individual& mother, const XOVER& xover, const MUTATE& mutate);
	    
    private:

	typedef CONTAINER Container;

	Container _genes;
	    
	Individual(const Individual& i) = delete;
    };


    template<typename GENE, class CONTAINER>
    Individual<GENE, CONTAINER>::Individual(const unsigned size) {
	std::uniform_int_distribution<GENE> distribution;
	for(unsigned i = 0; i < size; ++i) {
	    _genes.push_back(distribution());
	}
    }

    template<typename GENE, class CONTAINER>
    template<class XOVER, class MUTATE>
    Individual<GENE, CONTAINER>::Individual(const Individual& father, const Individual& mother,
					    const XOVER& xover, const MUTATE& mutate):
	_genes(xover(father._genes, mother._genes)) {
	
	mutate(_genes);
    }
}


#endif
