// Copyright 2024 stranger

#include "algorithms.hpp"

namespace s21{

[[ nodiscard ]] std::deque<unsigned int> GraphAlgorithms::depthFirstSearch(const Graph& graph, const unsigned int start_vertex){
    std::deque<unsigned int> path;

    path.emplace_back(start_vertex);

    Stack<unsigned int> stack;

    return path;
}

[[ nodiscard ]] std::deque<unsigned int> GraphAlgorithms::breadthFirstSearch(const Graph& graph, const unsigned int start_vertex){

}

} // namespace s21