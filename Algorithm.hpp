#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "Individual.hpp"

namespace ga {

    template<typename GENE = bool, class CONTAINER = std::vector<GENE>>
    class Algorithm {
    public:
	typedef Individual<GENE, CONTAINER> MyIndividual;

	Algorithm(unsigned populationSize, unsigned genomeSize);

	template<class FITNESS, class SELECT, class XOVER, class MUTATE>
	MyIndividual* run(const FITNESS& fitness, const SELECT& select,
			  const XOVER& xover, const MUTATE& mutate);

    private:
	typedef std::vector<MyIndividual> Population;

	Population _population;
    };

    template<typename GENE, class CONTAINER>
    Algorithm<GENE, CONTAINER>::Algorithm(unsigned populationSize, unsigned genomeSize) {
	for(unsigned i = 0; i < populationSize; ++i) {
	    _population.push_back(Individual<GENE, CONTAINER>());
	}
    }

    template<typename GENE, class CONTAINER>
    template<class FITNESS, class SELECT, class XOVER, class MUTATE>
    typename Algorithm<GENE, CONTAINER>::MyIndividual* //return value
    Algorithm<GENE, CONTAINER>::run(const FITNESS& fitness, const SELECT& select,
				    const XOVER& xover, const MUTATE& mutate) {
	return nullptr;
    }


}

#endif
