// Copyright 2024 stranger

#include "algorithms.hpp"
#include <iostream>

namespace s21{

auto GraphAlgorithms::depthFirstSearch(const Graph& graph, const unsigned int start_vertex) -> std::deque<unsigned int>{
    std::deque<unsigned int> dist;

    const std::size_t vertices = graph.vertices();
    
    if(vertices == 0) return dist;

    Stack<unsigned int> stack;
    stack.push(start_vertex - 1);

    std::vector<bool> visited(vertices, false);

    while(!stack.empty()){
        auto vertex = stack.pop();

        if(visited[vertex]){
            visited[vertex] = true;

            dist.emplace_back(vertex + 1);

            for(unsigned int i = 0; i < vertices; ++i){
                if(graph(vertex, i) != 0){
                    stack.push(i);
                }
            }
        }
    }

    return dist;
}

auto GraphAlgorithms::breadthFirstSearch(const Graph& graph, const unsigned int start_vertex) -> std::deque<unsigned int>{
    std::deque<unsigned int> dist;

    const std::size_t vertices = graph.vertices();
    
    if(vertices == 0) return dist;

    Queue<unsigned int> queue;
    queue.push(start_vertex - 1);

    std::vector<bool> visited(vertices, false);

    while(!queue.empty()){
        auto vertex = queue.pop();

        if(visited[vertex]){
            visited[vertex] = true;

            dist.emplace_back(vertex + 1);

            for(unsigned int i = 0; i < vertices; ++i){
                if(graph(vertex, i) != 0){
                    queue.push(i);
                }
            }
        }
    }

    return dist;
}

int GraphAlgorithms::getShortestPathBetweenVertices(const Graph& graph, const unsigned int begin, const unsigned int end){
    const std::size_t vertices = graph.vertices();

    if(vertices == 0) return 0;

    PriorityQueue<std::pair<unsigned int, unsigned int>> queue;
    queue.push({0, begin - 1});

    std::vector<bool> visited(vertices, false);

    std::vector<unsigned int> dist(vertices, static_cast<unsigned int>(s21::Constants::inf));
    dist[begin - 1] = 0;

    while(!queue.empty()){
        auto [weight, index] = queue.pop();

        if(index + 1 == end) return dist[index];

        if(visited[index]){
            visited[index] = true;

            for(unsigned int i = 0; i < vertices; ++i){
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

auto GraphAlgorithms::getShortestPathsBetweenAllVertices(const Graph& graph) -> Matrix<int>{
    const std::size_t vertices = graph.vertices();

    Matrix<int> matrix(vertices, vertices);

    if(vertices == 0) return matrix;

    const std::size_t capacity = matrix.capacity();

    for(unsigned int i = 0; i < capacity; ++i){
        matrix(i) = static_cast<int>(Constants::inf);  

        if(graph(i) != 0) matrix(i) = graph(i);
    }

    for(unsigned int i = 0; i < capacity; i += vertices + 1){
        matrix(i) = 0;
    }

    for(unsigned int k = 0; k < vertices; ++k){
        for(unsigned int i = 0; i < vertices; ++i){
            for(unsigned int j = 0; j < vertices; ++j){
                if(matrix(i, k) != static_cast<int>(Constants::inf) 
                    && matrix(k, j) != static_cast<int>(Constants::inf)){
                    int weight = matrix(i, k) + matrix(k, j);

                    if(matrix(i, j) > weight) matrix(i, j) = weight;
                }
            }
        }
    }

    return matrix;
}

auto GraphAlgorithms::getLeastSpanningTree(const Graph& graph) -> Matrix<int>{
    const std::size_t vertices = graph.vertices();

    Matrix<int> matrix(vertices, vertices);

    if(vertices == 0) return matrix;

    PriorityQueue<std::pair<unsigned int, unsigned int>> queue;

    std::vector<int> key(vertices, false);

    std::vector<bool> visited(vertices, false);

    while(!queue.empty()){
        auto [weight, row, col] = queue.pop();

        if(visited[col]){
            matrix(row, col) = matrix(col, row) = weight;

            visited[col] = true;

            for(unsigned int i = 0; i < vertices; ++i){
                if(visited[i] && graph(col, i) != 0 && graph(col, i) < weight){
                    queue.push({graph(col, i), col, i});
                }
            }
        }
    }

    return matrix;
}

} // namespace s21