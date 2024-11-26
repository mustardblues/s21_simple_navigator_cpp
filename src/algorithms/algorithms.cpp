// Copyright 2024 stranger

#include "algorithms.hpp"
#include <iostream>

namespace s21{

auto GraphAlgorithms::depthFirstSearch(const Graph& graph, const unsigned int start_vertex) -> std::deque<unsigned int>{
    std::deque<unsigned int> dist;

    const std::size_t length = graph.length();

    Stack<unsigned int> stack;
    stack.push(start_vertex - 1);

    std::vector<bool> visited(length, false);
    visited[start_vertex - 1] = true;

    while(!stack.empty()){
        auto vertex = stack.pop();

        dist.emplace_back(vertex + 1);

        for(unsigned int i = 0; i < length; ++i){
            if(visited[i] == false && graph(vertex, i) != 0){
                stack.push(i);

                visited[i] = true;
            }
        }
    }

    return dist;
}

auto GraphAlgorithms::breadthFirstSearch(const Graph& graph, const unsigned int start_vertex) -> std::deque<unsigned int>{
    std::deque<unsigned int> dist;

    const std::size_t length = graph.length();

    Queue<unsigned int> queue;
    queue.push(start_vertex - 1);

    std::vector<bool> visited(length, false);
    visited[start_vertex - 1] = true;

    while(!queue.empty()){
        auto vertex = queue.pop();

        dist.emplace_back(vertex + 1);

        for(unsigned int i = 0; i < length; ++i){
            if(visited[i] == false && graph(vertex, i) != 0){
                queue.push(i);

                visited[i] = true;
            }
        }
    }

    return dist;
}

int GraphAlgorithms::getShortestPathBetweenVertices(const Graph &graph, const unsigned int begin, const unsigned int end){
    const std::size_t length = graph.length();

    PriorityQueue<std::pair<unsigned int, unsigned int>> queue;
    queue.push({begin - 1, 0});

    std::vector<bool> visited(length, false);

    std::vector<unsigned int> dist(length, static_cast<unsigned int>(s21::Constants::inf));
    dist[0] = 0;

    while(!queue.empty()){
        auto [weight, index] = queue.pop();

        if(index + 1 == end) return dist[index];

        if(visited[index] == false){
            visited[index] = true;

            for(unsigned int i = 0; i < length; ++i){
                unsigned int new_weight = graph(index, i) + dist[index];

                if(graph(index, i) != 0 && new_weight < dist[i]){
                    dist[i] = new_weight;

                    queue.push({new_weight, i});
                }
            }
        }
    }

    return 0;
}

Graph GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph){
    const std::size_t length = graph.length();

    Graph matrix(length);
    const std::size_t capacity = matrix.capacity()
    const int infinity = static_cast<int>(Constants::inf);
    // O(N)
    for(unsigned int i = 0; i < capacity; ++i){
        matrix(i) = infinity;

        if(graph(i) != 0) matrix(i) = graph(i);
    }
    // O(logN)
    for(unsigned int i = 0; i < capacity; i += length + 1){
        matrix(i) = 0;
    }

    for(unsigned int k = 0; k < length; ++k){
        for(unsigned int i = 0; i < length; ++i){
            for(unsigned int j = 0; j < length; ++j){
                if(matrix(i, k) != infinity && matrix(k, j) != infinity){
                    int weight = matrix(i, k) + matrix(k, j);

                    if(matrix(i, j) > weight) matrix(i, j) = weight;
                }
            }
        }
    }

    return matrix;
}

Graph GraphAlgorithms::getLeastSpanningTree(const Graph& graph){
    const std::size_t length = graph.length();

    Graph tree(length);

    PriorityQueue<EdgeWeight> queue;
    queue.push({0, 0, 0});

    std::vector<bool> visited(length, false);

    while(!queue.empty()){
        auto [weight, row, col] = queue.pop();

        if(visited[col] == false){
            tree(row, col) = tree(col, row) = weight;

            visited[col] = true;

            for(unsigned int i = 0; i < length; ++i){
                if(visited[i] == false && graph(col, i) != 0) queue.push({graph(col, i), col, i});
            }
        }
    }

    return tree;
}

} // namespace s21