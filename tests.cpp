#include "tests.hpp"
#include "Individual.hpp"
#include "Crossover.hpp"
#include <algorithm>

void individuals();
void xover();

void asserts() {
    //individuals();
    xover();
}

void individuals() {
    constexpr int genomeSize = 12;

    const ga::Individual<> individual(genomeSize);
    std::cout << "Individual is " << individual << std::endl;

    const auto robber = std::move(ga::Individual<>(genomeSize)); //test moving
    std::cout << "Robber is     " << robber << std::endl;

    struct Reverse {
	void operator()(ga::Individual<>::Container& container) const {
	    std::reverse(container.begin(), container.end());
	}
    };

    const ga::Individual<> reversed({0, 0, 0, 0, 1, 1, 1, 1}, Reverse());

    std::cout << "Reversed is " << reversed << std::endl;
}

void xover() {
    constexpr int genomeSize = 12;
    const ga::Individual<> father(genomeSize);
    const decltype(father) mother(genomeSize);
    std::cout << "Father is " << father;
    std::cout << "Mother is " << mother;
        
    ga::SinglePointCrossover<ga::Individual<>> xover;
    ga::Individual<>::Container child1, child2;
    std::tie(child1, child2) = xover(father.getGenes(), mother.getGenes());

    
}
