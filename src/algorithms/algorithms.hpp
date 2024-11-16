// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_

#include <deque>
#include <vector>

#include "./../graph/graph.hpp"

#include "containers/queue/queue.hpp"
#include "containers/stack/stack.hpp"

namespace s21{

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
    [[ nodiscard ]] static std::deque<unsigned int> depthFirstSearch(const Graph& graph, const unsigned int start_vertex = 1);

    /**
     * @brief A BFS algorithm for shortest path finding in graph.
     * @param graph Contains information about the vertices and edges of the graph.
     * @param start_vertex The starting vertex from where path starts.
     * @return The deque of the vertices which algorithm visited.
     */
    [[ nodiscard ]] static std::deque<unsigned int> breadthFirstSearch(const Graph& graph, const unsigned int start_vertex = 1);

    /**
     * @brief 
     */
    [[ nodiscard ]] static Graph getLeastSpanningTree(const Graph& graph);
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
