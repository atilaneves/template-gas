#include "Random.hpp"
#include <time.h>

namespace ga {

    std::mt19937 Random::_gen;

    std::mt19937& Random::getGenerator() { 
	static bool init = false;
	if(!init) {
	    _gen.seed(time(NULL));
	    init = true;
	}
	return _gen;
    }
}
