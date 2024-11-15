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
     * 
     * @details Depth-first search is an algorithm for searching graph data structures. 
     * The algorithm starts at the start vertex and explores as far as possible along 
     * each branch before backtracking. Extra memory, usually a stack, is needed to keep 
     * track of the nodes discovered so far along a specified branch which helps in backtracking 
     * of the graph.
     */
    [[ nodiscard ]] static std::deque<unsigned int> depthFirstSearch(const Graph& graph, const unsigned int start_vertex);

    /**
     * @brief A BFS algorithm for shortest path finding in graph.
     * @param graph Contains information about the vertices and edges of the graph.
     * @param start_vertex The starting vertex from where path starts.
     * @return The deque of the vertices which algorithm visited.
     * 
     * @details Breadth-first search is an algorithm for searching graph data 
     * structure. It starts at the start vertex and explores all vertices at the 
     * present depth prior to moving on to the nodes at the next depth level. Extra memory, 
     * usually a queue, is needed to keep track of the child nodes that were encountered but 
     * not yet explored.
     */
    [[ nodiscard ]] static std::deque<unsigned int> breadthFirstSearch(const Graph& graph, const unsigned int start_vertex);

};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
