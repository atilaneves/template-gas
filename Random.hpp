#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <random>
#include <iostream>

namespace ga {

    class Random {
    public:

	static std::mt19937& getGenerator();
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

    template<> class UniformIntDistribution<bool> {
    public:
	UniformIntDistribution():
	    _distribution(0, 1) { }
	bool operator()() { return _distribution(Random::getGenerator()); }
    private:
	std::uniform_int_distribution<> _distribution;
    };

    template<typename T = double>
    class UniformRealDistribution {
    public:
	UniformRealDistribution(T a = 0.0, T b = 1.0):
	    _distribution(a, b) { }
	T operator()() { return _distribution(Random::getGenerator()); }
    private:
	std::uniform_real_distribution<T> _distribution;
    };
}

#endif
