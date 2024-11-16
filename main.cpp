#include "src/graph/graph.hpp"

int main(void){
    s21::Graph graph("tests/unit/files/adjacency_matrix.txt");

    graph.exportGraphToDot<s21::GraphType::Directed>("src/GRAPH");

    return 0;
}   