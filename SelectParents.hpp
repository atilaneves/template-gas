#ifndef _SELECT_H_
#define _SELECT_H_

#include <map>
#include <functional>
#include <tuple>

template<class INDIVIDUAL>
class SelectParents {
public:

    typedef std::multimap<double, const INDIVIDUAL&> Rankings;
    typedef std::tuple<const INDIVIDUAL&, const INDIVIDUAL&> ParentTuple;
    typedef std::function<ParentTuple(const Rankings&)> SelectFunc;

};

#endif
