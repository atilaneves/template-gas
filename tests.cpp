#include "tests.hpp"
#include "Individual.hpp"
#include "Crossover.hpp"
#include "Tournament.hpp"
#include "Mutate.hpp"
#include <algorithm>
#include <assert.h>

void individuals();
void xover();
void tournament();

void asserts() {
    //individuals();
    xover();
    //tournament();
}


namespace {
    struct Reverse {
        void operator()(ga::Individual<>::Container& container) const {
            std::reverse(container.begin(), container.end());
        }
    };
}

void individuals() {
    constexpr int genomeSize = 12;

    const ga::Individual<> individual(genomeSize);
    std::cout << "Individual is " << individual << std::endl;

    const auto robber = std::move(ga::Individual<>(genomeSize)); //test moving
    std::cout << "Robber is     " << robber << std::endl;

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
    ga::Individual<>::Container child1Genes, child2Genes;
    auto genes = xover(father.getGenes(), mother.getGenes());
    decltype(father) child1(std::get<0>(genes));
    decltype(father) child2(std::get<1>(genes));

    std::cout << "Child1 from genes is " << child1;
    std::cout << "Child2 from genes is " << child2;

    assert(child1.getGenes().size() == child2.getGenes().size());
    assert(child1.getGenes().size() == father.getGenes().size());
    assert(child1.getGenes().size() == mother.getGenes().size());

    auto&& children = ga::Individual<>::createChildren(father, mother, xover, Reverse());
    std::cout << "1st children: " << std::get<0>(children);
    std::cout << "2nd children: " << std::get<1>(children);
}

void tournament() {
    const ga::Individual<> weak({0, 0, 0, 1});
    decltype(weak) strong({1, 1, 1, 1});
    decltype(weak) medium({1, 0, 1, 0});
    ga::Tournament<>::Rankings ranked{ { 1, std::cref(weak)}, {2, std::cref(medium)}, {4, std::cref(strong)} };

    ga::Tournament<> select(3);
    auto&& winners = select(ranked);
    
    std::cout << "1st winner: " << std::get<0>(winners);
    std::cout << "2nd winner: " << std::get<1>(winners);
}
