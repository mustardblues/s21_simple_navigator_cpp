// Copyright 2024 stranger

#include "algorithms.hpp"

namespace s21{

[[ nodiscard ]] std::deque<unsigned int> GraphAlgorithms::depthFirstSearch(const Graph& graph, const unsigned int start_vertex){
    std::deque<unsigned int> dist;

    Stack<unsigned int> stack;
    stack.push(start_vertex - 1);

    std::vector<bool> visited(graph.length(), false);
    visited[start_vertex - 1] = true;

    while(!stack.empty()){
        auto vertex = stack.pop();

        dist.emplace_back(vertex + 1);

        for(unsigned int i = 0; i < graph.length(); ++i){
            if(graph(vertex, i) != 0 && visited[i] == false){
                stack.push(i);

                visited[i] = true;
            }
        }
    }

    return dist;
}

[[ nodiscard ]] std::deque<unsigned int> GraphAlgorithms::breadthFirstSearch(const Graph& graph, const unsigned int start_vertex){
    std::deque<unsigned int> dist;

    Queue<unsigned int> queue;
    queue.push(start_vertex - 1);

    std::vector<bool> visited(graph.length(), false);
    visited[start_vertex - 1] = true;

    while(!queue.empty()){
        auto vertex = queue.pop();

        dist.emplace_back(vertex + 1);

        for(unsigned int i = 0; i < graph.length(); ++i){
            if(graph(vertex, i) != 0 && visited[i] == false){
                queue.push(i);

                visited[i] = true;
            }
        }
    }

    return dist;
}

[[ nodiscard ]] Graph GraphAlgorithms::getLeastSpanningTree(const Graph& graph){
    
}

} // namespace s21