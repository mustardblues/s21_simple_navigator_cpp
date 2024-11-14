// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_

#include <deque>

#include "./../graph/graph.hpp"

#include "containers/queue/queue.hpp"
#include "containers/stack/stack.hpp"

namespace s21{

/**
 * @class GraphAlgorithms
 * @brief
 * 
 * @details 
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
     * 
     * @details The DFS algorithm works on a stack basis. 
     */
    [[ nodiscard ]] static std::deque<unsigned int> depthFirstSearch(const Graph& graph, const unsigned int start_vertex);

    /**
     * @brief A BFS algorithm for shortest path finding in graph.
     * @param graph Contains information about the vertices and edges of the graph.
     * @param start_vertex The starting vertex from where path starts.
     * @return The deque of the vertices which algorithm visited.
     * 
     * @details The DFS algorithm works on a queue basis. 
     */
    [[ nodiscard ]] static std::deque<unsigned int> breadthFirstSearch(const Graph& graph, const unsigned int start_vertex);

private:

};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
