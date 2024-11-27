#include <iostream>

#include "src/graph/graph.hpp"

int main(void){
    s21::Graph graph(10);

    graph(5, 5) = 25;

    for(unsigned int i = 0; i < graph.vertices(); ++i){
        for(unsigned int j = 0; j < graph.vertices(); ++j){
            std::cout << graph(i, j) << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}   