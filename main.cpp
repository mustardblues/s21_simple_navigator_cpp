#include <iostream>

#include <deque>

#include "src/algorithms/containers/stack/stack.hpp"

#include "src/algorithms/algorithms.hpp"

int main(void){
    // s21::Queue<int> queue;

    // for(unsigned int i = 0; i < 10; ++i){
    //     queue.push(i);
    // }

    // for(unsigned int i = 0; i < 10; ++i){
    //     std::cout << queue.pop() << " ";
    // }

    // std::cout << std::endl;

    s21::Graph graph("samples/matrix.txt");

    graph.exportGraphToDot<s21::GraphType::Undirected>("samples/graph");

    std::deque<unsigned int> dist = s21::GraphAlgorithms::breadthFirstSearch(graph, 1);

    for(unsigned int i = 0; i < dist.size(); ++i){
        std::cout << dist[i] << " ";
    }

    return 0;
}   