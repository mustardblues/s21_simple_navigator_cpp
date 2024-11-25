#include <iostream>

#include "src/algorithms/algorithms.hpp"
#include "src/containers/priority_queue/priority_queue.hpp"

int main(void){
    s21::Graph graph("test.txt");

    using A = s21::GraphAlgorithms;

    std::cout << A::getShortestPathBetweenVertices(graph, 1, 5) << std::endl;

    // s21::Graph tree = s21::GraphAlgorithms::getLeastSpanningTree(graph);

    // for(unsigned int i = 0; i < tree.length(); ++i){
    //     for(unsigned int j = 0; j < tree.length(); ++j){
    //         std::cout << tree(i, j) << " ";
    //     }

    //     std::cout << std::endl;
    // }

    return 0;
}   