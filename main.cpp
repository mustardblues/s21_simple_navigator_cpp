#include <iostream>

#include "src/algorithms/algorithms.hpp"

#include "src/containers/priority_queue/priority_queue.hpp"

int main(void){
    s21::Graph graph("data.txt");

    s21::Graph tree = s21::GraphAlgorithms::getLeastSpanningTree(graph);

    for(unsigned int i = 0; i < tree.length(); ++i){
        for(unsigned int j = 0; j < tree.length(); ++j){
            std::cout << tree(i, j) << " ";
        }

        std::cout << std::endl;
    }

    // tree.exportGraphToDot<s21::GraphType::Undirected>("pic.dot");

    return 0;
}   