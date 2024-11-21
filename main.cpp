#include <iostream>

#include "src/graph/graph.hpp"
#include "src/algorithms/algorithms.hpp"

int main(void){
    s21::Graph graph;

    graph.loadGraphFromFile("sample.txt");

    std::cout << graph.length() << std::endl;

    for(unsigned int i = 0; i < 4; ++i){
        for(unsigned int j = 0; j < 4; ++j){
            std::cout << graph(i, j) << " ";
        }

        std::cout << std::endl;
    }

    std::filesystem::path path = "asd";

    graph.exportGraphToDot<s21::GraphType::Undirected>(path);

    return 0;
}   