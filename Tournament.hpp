#ifndef _TOURNAMENT_H_
#define _TOURNAMENT_H_

#include "Individual.hpp"
#include "Random.hpp"
#include <tuple>
#include <map>
#include <algorithm>

namespace ga {

    template<typename INDIVIDUAL>
    class Tournament {
    public:
	typedef std::multimap<double, INDIVIDUAL*> Population;

	Tournament(unsigned numParticipants = 2u):_numParticipants(numParticipants) { }
	std::tuple<INDIVIDUAL*, INDIVIDUAL*> operator()(const Population& population);

    private:

	unsigned _numParticipants;
	INDIVIDUAL* pickParent(const Population& population);
    };

    template<typename INDIVIDUAL>
    std::tuple<INDIVIDUAL*, INDIVIDUAL*> Tournament<INDIVIDUAL>::operator()(const Population& population) {
	return std::make_tuple(pickParent(population), pickParent(population));
    }

    template<typename INDIVIDUAL>
    INDIVIDUAL* Tournament<INDIVIDUAL>::pickParent(const Population& population) {
	UniformIntDistribution<> _random(0, population.size() - 1);
	typedef typename Population::value_type Pair;
	std::vector<Pair> participants;
	for(unsigned i = 0; i < _numParticipants; ++i) {
	    auto it = population.const_begin() + _random();
	    participants.push_back(*it);
	}

	auto it = std::max_element(participants.begin(), participants.end(),
				   [](const Pair& p1, const Pair& p2) { return p1.first < p2.first; });
	return it->second;
    }
    
}

#endif
