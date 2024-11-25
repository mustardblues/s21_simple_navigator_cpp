// Copyright 2024 stranger

#include "algorithms.hpp"
#include <iostream>

namespace s21{

[[ nodiscard ]] std::deque<unsigned int> GraphAlgorithms::depthFirstSearch(const Graph& graph, const unsigned int start_vertex){
    std::deque<unsigned int> dist;

    Stack<unsigned int> stack;
    stack.push(start_vertex - 1);

    std::size_t length = graph.length();

    std::vector<bool> visited(length, false);
    visited[start_vertex - 1] = true;

    while(!stack.empty()){
        auto vertex = stack.pop();

        dist.emplace_back(vertex + 1);

        for(unsigned int i = 0; i < length; ++i){
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

    std::size_t length = graph.length();

    std::vector<bool> visited(length, false);
    visited[start_vertex - 1] = true;

    while(!queue.empty()){
        auto vertex = queue.pop();

        dist.emplace_back(vertex + 1);

        for(unsigned int i = 0; i < length; ++i){
            if(graph(vertex, i) != 0 && visited[i] == false){
                queue.push(i);

                visited[i] = true;
            }
        }
    }

    return dist;
}

[[ nodiscard ]] Graph GraphAlgorithms::getLeastSpanningTree(const Graph& graph){
    std::size_t length = graph.length();

    Graph tree(length);

    PriorityQueue<EdgeWeight> queue;
    queue.push({0, 0, 0});

    std::vector<bool> visited(length, false);

    while(!queue.empty()){
        auto [weight, row, col] = queue.pop();

        if(!visited[col]){
            tree(row, col) = tree(col, row) = weight;

            visited[col] = true;

            for(unsigned int i = 0; i < length; ++i){
                if(!visited[i] && graph(col, i) != 0) queue.push({graph(col, i), col, i});
            }
        }
    }

    std::cout << "size: " << queue.size() << std::endl;

    return tree;
}

} // namespace s21