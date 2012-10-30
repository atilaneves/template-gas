#ifndef _TOURNAMENT_H_
#define _TOURNAMENT_H_

#include "Random.hpp"
#include "SelectParents.hpp"
#include <algorithm>

namespace ga {

    template<typename INDIVIDUAL = Individual<>>
    class Tournament {
    public:

        typedef typename SelectParents<INDIVIDUAL>::Rankings Rankings;
        typedef typename SelectParents<INDIVIDUAL>::ParentTuple ParentTuple;

        Tournament(unsigned numParticipants = 2u):_numParticipants(numParticipants) { }
        ParentTuple operator()(const Rankings& rankings) const;

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
            auto it = rankings.cbegin();
            const int offset = _random();
            for(int j = 0; j < offset; ++j) ++it; //won't let me add
            participants.insert(std::make_pair(it->first, std::cref(it->second)));
        }

        typedef typename Rankings::value_type pair;
        auto it = std::max_element(participants.cbegin(), participants.cend(),
                                   [](const pair& p1, const pair& p2) { return p1.first < p2.first; });
        return it->second;
    }
    
}

#endif
