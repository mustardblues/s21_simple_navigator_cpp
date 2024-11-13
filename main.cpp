#include <iostream>

#include "src/graph/graph.hpp"

#include <vector>

int main(void){
    s21::Graph graph;

    graph.loadGraphFromFile("samples/matrix.txt");

    // graph.exportGraphToDot<s21::GraphType::Directed>("samples/graph.dot");

    std::vector<unsigned int> v(25, 0);

    std::copy(graph.begin(), graph.end(), v.begin());

    for(unsigned int i = 0; i < v.size(); ++i){
        std::cout << v[i] << " " << std::endl;
    }

    // std::cout << "Result: " << std::boolalpha << result << std::endl;

    // std::cout << "Length: " << graph.length() << std::endl;

    // for(unsigned int i = 0; i < graph.length(); ++i){
    //     for(unsigned int j = 0; j < graph.length(); ++j){
    //         std::cout << graph(i, j) << " ";
    //     }

    //     std::cout << std::endl;
    // }

    return 0;
}