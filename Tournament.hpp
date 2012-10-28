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
	typedef std::multimap<double, const INDIVIDUAL*> Population;

	Tournament(unsigned numParticipants = 2u):_numParticipants(numParticipants) { }
	std::tuple<const INDIVIDUAL&, const INDIVIDUAL&>&& operator()(const Population& population) const;

    private:

	unsigned _numParticipants;
	const INDIVIDUAL& pickParent(const Population& population) const;
    };

    template<typename INDIVIDUAL>
    std::tuple<const INDIVIDUAL&, const INDIVIDUAL&>&& //return value
    Tournament<INDIVIDUAL>::operator()(const Population& population) const {
	return make_tuple(std::ref(pickParent(population)), std::ref(pickParent(population)));
    }

    template<typename INDIVIDUAL>
    const INDIVIDUAL& Tournament<INDIVIDUAL>::pickParent(const Population& population) const {
	UniformIntDistribution<> _random(0, population.size() - 1);
	typedef std::pair<double, const INDIVIDUAL*> Pair;
	std::vector<Pair> participants;
	for(unsigned i = 0; i < _numParticipants; ++i) {
	    auto it = population.begin();
	    //it += (std::ptrdiff_t)_random();
	    participants.push_back(Pair(*it));	    
	}

	auto it = std::max_element(participants.begin(), participants.end(),
				   [](const Pair& p1, const Pair& p2) { return p1.first < p2.first; });
	return *it->second;
    }
    
}

#endif
