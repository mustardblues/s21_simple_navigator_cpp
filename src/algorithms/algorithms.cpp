// Copyright 2024 stranger

#include "algorithms.hpp"

namespace s21{

auto GraphAlgorithms::depthFirstSearch(const Graph<int>& graph, const std::size_t start_vertex) -> std::deque<unsigned int>{
    const std::size_t vertex_number = graph.vertices();

    if(vertex_number == 0 || start_vertex == 0 || start_vertex > vertex_number) return std::deque<unsigned int>();

    std::deque<unsigned int> dist;

    Stack<unsigned int> stack;
    stack.push(start_vertex - 1);

    std::vector<bool> visited(vertex_number, false);

    while(!stack.empty()){
        auto vertex = stack.pop();

        if(!visited[vertex]){
            visited[vertex] = true;

            dist.emplace_back(vertex + 1);

            for(unsigned int i = 0; i < vertex_number; ++i){
                if(graph(vertex, i) != 0){
                    stack.push(i);
                }
            }
        }
    }

    return dist;
}

auto GraphAlgorithms::breadthFirstSearch(const Graph<int>& graph, const std::size_t start_vertex) -> std::deque<unsigned int>{
    const std::size_t vertex_number = graph.vertices();

    if(vertex_number == 0 || start_vertex == 0 || start_vertex > vertex_number) return std::deque<unsigned int>();

    std::deque<unsigned int> dist;

    Queue<unsigned int> queue;
    queue.push(start_vertex - 1);

    std::vector<bool> visited(vertex_number, false);

    while(!queue.empty()){
        auto vertex = queue.pop();

        if(!visited[vertex]){
            visited[vertex] = true;

            dist.emplace_back(vertex + 1);

            for(unsigned int i = 0; i < vertex_number; ++i){
                if(graph(vertex, i) != 0){
                    queue.push(i);
                }
            }
        }
    }

    return dist;
}

int GraphAlgorithms::getShortestPathBetweenVertices(const Graph<int>& graph, const std::size_t begin, const std::size_t end){
    const std::size_t vertex_number = graph.vertices();

    if((vertex_number == 0) || (begin == 0 || begin > vertex_number) || (end == 0 || end > vertex_number)) return 0;

    PriorityQueue<std::pair<unsigned int, unsigned int>> queue;
    queue.push({0, begin - 1});

    std::vector<bool> visited(vertex_number, false);

    std::vector<unsigned int> dist(vertex_number, static_cast<unsigned int>(s21::Constants::inf));
    dist[begin - 1] = 0;

    while(!queue.empty()){
        auto [weight, index] = queue.pop();

        if(index + 1 == end) return dist[index];

        if(!visited[index]){
            visited[index] = true;

            for(unsigned int i = 0; i < vertex_number; ++i){
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

auto GraphAlgorithms::getShortestPathsBetweenAllVertices(const Graph<int>& graph) -> Matrix<int>{
    const std::size_t vertex_number = graph.vertices();

    if(vertex_number == 0) return Matrix<int>();

    Matrix<int> matrix(vertex_number, 0);

    const std::size_t capacity = matrix.capacity();

    for(unsigned int i = 0; i < capacity; ++i){
        matrix(i) = static_cast<int>(Constants::inf);  

        if(graph(i) != 0) matrix(i) = graph(i);
    }

    for(unsigned int i = 0; i < capacity; i += vertex_number + 1){
        matrix(i) = 0;
    }

    for(unsigned int k = 0; k < vertex_number; ++k){
        for(unsigned int i = 0; i < vertex_number; ++i){
            for(unsigned int j = 0; j < vertex_number; ++j){
                if(matrix(i, k) != static_cast<int>(Constants::inf) && matrix(k, j) != static_cast<int>(Constants::inf)){
                    int weight = matrix(i, k) + matrix(k, j);

                    if(matrix(i, j) > weight) matrix(i, j) = weight;
                }
            }
        }
    }

    return matrix;
}

auto GraphAlgorithms::getLeastSpanningTree(const Graph<int>& graph, const std::size_t start_vertex) -> Matrix<int>{
    const std::size_t vertex_number = graph.vertices();

    if(vertex_number == 0 || start_vertex == 0 || start_vertex > vertex_number) return Matrix<int>();

    std::vector<int> root(vertex_number, 0);
    root[start_vertex - 1] = -1;

    std::vector<int> key(vertex_number, static_cast<int>(Constants::inf));
    key[start_vertex - 1] = 0;

    std::vector<bool> visited(vertex_number, false);

    PriorityQueue<std::pair<int, int>> queue;
    queue.push({start_vertex - 1, start_vertex - 1});

    while(!queue.empty()){
        auto [weight, index] = queue.pop();
        
        if(!visited[index]){
            visited[index] = true;

            for(unsigned int i = 0; i < vertex_number; ++i){
                const int weight = graph(index, i);

                if(!visited[i] && weight != 0 && weight < key[i]){
                    key[i] = weight;

                    root[i] = index;

                    queue.push({weight, i});
                }
            }   
        }
    }

    Matrix<int> matrix(vertex_number, 0);

    for(unsigned int i = 0; i < vertex_number; ++i){
        const int index = root[i];

        matrix(index, i) = graph(index, i);

        if(graph(i, index) != 0) matrix(i, index) = graph(i, index);
    }

    return matrix;
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(const Graph<int>& graph){
    AntColonyOptimization aco(graph);

    return aco.findPath();
}

} // namespace s21