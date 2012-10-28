#ifndef _TOURNAMENT_H_
#define _TOURNAMENT_H_

#include "Individual.hpp"
#include "Random.hpp"
#include <tuple>
#include <map>
#include <algorithm>

#include "Individual.hpp"

namespace ga {

    template<typename INDIVIDUAL = Individual<>>
    class Tournament {
    public:
	typedef std::multimap<double, const INDIVIDUAL&> Rankings;
	typedef std::tuple<const INDIVIDUAL&, const INDIVIDUAL&> ParentTuple;

	Tournament(unsigned numParticipants = 2u):_numParticipants(numParticipants) { }
	std::tuple<const INDIVIDUAL&, const INDIVIDUAL&> operator()(const Rankings& rankings) const;

    private:

	unsigned _numParticipants;
	const INDIVIDUAL& pickParent(const Rankings& rankings) const;
    };

    template<typename INDIVIDUAL>
    auto Tournament<INDIVIDUAL>::operator()(const Rankings& rankings) const -> ParentTuple {
	return std::make_tuple(std::cref(pickParent(rankings)), std::cref(pickParent(rankings)));
    }

    template<typename INDIVIDUAL>
    const INDIVIDUAL& Tournament<INDIVIDUAL>::pickParent(const Rankings& rankings) const {
	UniformIntDistribution<> _random(0, rankings.size() - 1);
	Rankings participants;
	for(unsigned i = 0; i < _numParticipants; ++i) {
	    auto it = rankings.begin();
	    const int offset = _random();
	    for(int j = 0; j < offset; ++j) ++it; //won't let me add
	    participants.insert(std::make_pair(it->first, std::cref(it->second)));
	}

	typedef typename Rankings::value_type pair;
	auto it = std::max_element(participants.begin(), participants.end(),
				   [](const pair& p1, const pair& p2) { return p1.first < p2.first; });
	return it->second;
    }
    
}

#endif
