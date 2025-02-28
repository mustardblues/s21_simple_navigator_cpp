// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_

#include <deque>
#include <vector>

#include "./../constants/constants.hpp"
#include "./../graph/graph.hpp"
#include "./../containers/queue/queue.hpp"
#include "./../containers/stack/stack.hpp"
#include "./../containers/priority_queue/priority_queue.hpp"
#include "tsm/aco/aco.hpp"

namespace s21{

/**
 * @class GraphAlgorithms.
 * @brief Provides the user with algorithms that use a graph in the course of their work.
 */
class GraphAlgorithms final{
public:
    GraphAlgorithms() = delete;
    GraphAlgorithms(const GraphAlgorithms& other) = delete;
    GraphAlgorithms(GraphAlgorithms&& other) = delete;
    ~GraphAlgorithms() = delete;

    GraphAlgorithms& operator = (const GraphAlgorithms& other) = delete;
    GraphAlgorithms& operator = (GraphAlgorithms&& other) = delete;

    /**
     * @brief A DFS algorithm for path finding in graph.
     * @param graph Contains information about the vertices and edges of the graph.
     * @param start_vertex The starting vertex from where path starts.
     * @return The deque of the vertices which algorithm visited.
     */
    static auto depthFirstSearch(const Graph<int>& graph, const std::size_t start_vertex = 1) -> std::deque<unsigned int>;

    /**
     * @brief A BFS algorithm for shortest path finding in graph.
     * @param graph Contains information about the vertices and edges of the graph.
     * @param start_vertex The starting vertex from where path starts.
     * @return The deque of the vertices which algorithm visited.
     */
    static auto breadthFirstSearch(const Graph<int>& graph, const std::size_t start_vertex = 1) -> std::deque<unsigned int>;

    /**
     * @brief Dijkstra's algorithm for finding the shortest path in graph.
     * @param graph Contains information about the vertices and edges of the graph.
     * @param begin The starting vertex from where path starts.
     * @param end The last vertex where path ends.
     * @return A numerical result equal to the smallest distance between begin and last parameters.
     */
    static int getShortestPathBetweenVertices(const Graph<int>& graph, const std::size_t begin, const std::size_t end);

    /**
     * @brief Floyd–Warshall algorithm algorithm for finding the shortest path in graph between all vertices.
     * @param graph Contains information about the vertices and edges of the graph.
     * @return 
     */
    static auto getShortestPathsBetweenAllVertices(const Graph<int>& graph) -> Matrix<int>;

    /**
     * @brief Prim's algorithm for finding minimum spanning tree.
     * @param graph Contains information about the vertices and edges of the graph.
     * @return The object of Graph class with the adjacency matrix for the minimal spanning tree.
     */
    static auto getLeastSpanningTree(const Graph<int>& graph, const std::size_t start_vertex = 1) -> Matrix<int>;

    /**
     * @brief Solves the traveling salesman problem using ACO algorithm.
     * @param graph Contains information about the vertices and edges of the graph.
     * @return TsmResult structure containing distance and vertexes solution.
     */
    static TsmResult solveTravelingSalesmanProblem(const Graph<int>& graph);
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
