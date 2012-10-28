#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <random>
#include <time.h>

namespace ga {

    class Random {
    public:

	static std::mt19937& getGenerator() { 
	    static bool init = false;
	    if(!init) {
		_gen.seed(time(NULL));
	    }
	    return _gen;
	}
    private:
	static std::mt19937 _gen;
    };

    template<typename T = int>
    class UniformIntDistribution {
    public:
	UniformIntDistribution(T a = 0, T b = std::numeric_limits<T>::max()):
	    _distribution(a, b) { }
	T operator()() { return _distribution(Random::getGenerator()); }
    private:
	std::uniform_int_distribution<T> _distribution;
    };

    std::mt19937 Random::_gen;
}

#endif
