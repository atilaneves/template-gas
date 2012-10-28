#ifndef _INDIVIUAL_HPP_
#define _INDIVIUAL_HPP_

#include <vector>

namespace ga {

    template<typename GENE = bool, class CONTAINER = std::vector<GENE>>
    class Individual {
    public:
	
	typedef CONTAINER Container;
	    
	Individual(const Container& genes):_genes(genes) { }
	template<class XOVER, class MUTATE>
	Individual(const Individual& father, const Individual& mother, const XOVER& xover, const MUTATE& mutate);
	    
    private:

	Container _genes;
	    
	Individual(const Individual& i) = delete;
    };        

    template<typename GENE, class CONTAINER>
    template<class XOVER, class MUTATE>
    Individual<GENE, CONTAINER>::Individual(const Individual& father, const Individual& mother,
					    const XOVER& xover, const MUTATE& mutate):
	_genes(xover(father._genes, mother._genes)) {
	
	mutate(_genes);
    }
}

#endif
