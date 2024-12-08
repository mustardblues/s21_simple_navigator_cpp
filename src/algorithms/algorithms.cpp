// Copyright 2024 stranger

#include "algorithms.hpp"
#include <iostream>

namespace s21{

auto GraphAlgorithms::depthFirstSearch(const Graph& graph, const std::size_t start_vertex) -> std::deque<unsigned int>{
    const std::size_t vertices = graph.vertices();

    if(vertices == 0 || start_vertex == 0 || start_vertex > vertices) return std::deque<unsigned int>();

    std::deque<unsigned int> dist;

    Stack<unsigned int> stack;
    stack.push(start_vertex - 1);

    std::vector<bool> visited(vertices, false);

    while(!stack.empty()){
        auto vertex = stack.pop();

        if(!visited[vertex]){
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

auto GraphAlgorithms::breadthFirstSearch(const Graph& graph, const std::size_t start_vertex) -> std::deque<unsigned int>{
    const std::size_t vertices = graph.vertices();
    
    if(vertices == 0 || start_vertex == 0 || start_vertex > vertices) return std::deque<unsigned int>();

    std::deque<unsigned int> dist;

    Queue<unsigned int> queue;
    queue.push(start_vertex - 1);

    std::vector<bool> visited(vertices, false);

    while(!queue.empty()){
        auto vertex = queue.pop();

        if(!visited[vertex]){
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

int GraphAlgorithms::getShortestPathBetweenVertices(const Graph& graph, const std::size_t begin, const std::size_t end){
    const std::size_t vertices = graph.vertices();

    if(vertices == 0 || (begin == 0 || begin > vertices) || (end == 0 || end > vertices)) return 0;

    PriorityQueue<std::pair<unsigned int, unsigned int>> queue;
    queue.push({0, begin - 1});

    std::vector<bool> visited(vertices, false);

    std::vector<unsigned int> dist(vertices, static_cast<unsigned int>(s21::Constants::inf));
    dist[begin - 1] = 0;

    while(!queue.empty()){
        auto [weight, index] = queue.pop();

        if(index + 1 == end) return dist[index];

        if(!visited[index]){
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

    if(vertices == 0) return Matrix<int>();

    Matrix<int> matrix(vertices, vertices);

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
                if(matrix(i, k) != static_cast<int>(Constants::inf) && matrix(k, j) != static_cast<int>(Constants::inf)){
                    int weight = matrix(i, k) + matrix(k, j);

                    if(matrix(i, j) > weight) matrix(i, j) = weight;
                }
            }
        }
    }

    return matrix;
}

auto GraphAlgorithms::getLeastSpanningTree(const Graph& graph, const std::size_t start_vertex) -> Matrix<int>{
    const std::size_t vertices = graph.vertices();

    if(vertices == 0 || start_vertex == 0 || start_vertex > vertices) return Matrix<int>();

    std::vector<int> root(vertices, 0);
    root[start_vertex - 1] = -1;

    std::vector<int> key(vertices, static_cast<int>(Constants::inf));
    key[start_vertex - 1] = 0;

    std::vector<bool> visited(vertices, false);

    PriorityQueue<std::pair<int, int>> queue;
    queue.push({start_vertex - 1, start_vertex - 1});

    while(!queue.empty()){
        auto [weight, index] = queue.pop();
        
        if(!visited[index]){
            visited[index] = true;

            for(unsigned int i = 0; i < vertices; ++i){
                const int weight = graph(index, i);

                if(!visited[i] && weight != 0 && weight < key[i]){
                    key[i] = weight;

                    root[i] = index;

                    queue.push({weight, i});
                }
            }   
        }
    }

    Matrix<int> matrix(vertices, vertices);

    for(unsigned int i = 0; i < vertices; ++i){
        const int index = root[i];

        matrix(index, i) = graph(index, i);

        if(graph(i, index) != 0) matrix(i, index) = graph(i, index);
    }

    return matrix;
}

} // namespace s21