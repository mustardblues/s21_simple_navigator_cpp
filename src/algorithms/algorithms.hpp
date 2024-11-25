// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_

#include <deque>
#include <vector>

#include "./../graph/graph.hpp"

#include "./../containers/queue/queue.hpp"
#include "./../containers/stack/stack.hpp"

#include "./../containers/priority_queue/priority_queue.hpp"

namespace s21{

/**
 * @struct EdgeWeight
 * @brief Contains information about weights of graph between vertices.
 */
struct EdgeWeight final{
    /**
     * @brief Weights between graph vertices.
     */
    unsigned int weight_;

    /**
     * @brief Row of weight element.
     */
    unsigned int row_;

    /**
     * @brief Column of weight element.
     */
    unsigned int column_;

    constexpr bool operator == (const EdgeWeight& other) const{
        return weight_ == other.weight_;
    }

    constexpr bool operator != (const EdgeWeight& other) const{
        return weight_ == other.weight_;
    }

    constexpr bool operator < (const EdgeWeight& other) const{
        return weight_ < other.weight_;
    }

    constexpr bool operator > (const EdgeWeight& other) const{
        return weight_ > other.weight_;
    }

    constexpr bool operator <= (const EdgeWeight& other) const{
        return weight_ <= other.weight_;
    }

    constexpr bool operator >= (const EdgeWeight& other) const{
        return weight_ >= other.weight_;
    }
};

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
    static auto depthFirstSearch(const Graph& graph, const unsigned int start_vertex = 1) -> std::deque<unsigned int>;

    /**
     * @brief A BFS algorithm for shortest path finding in graph.
     * @param graph Contains information about the vertices and edges of the graph.
     * @param start_vertex The starting vertex from where path starts.
     * @return The deque of the vertices which algorithm visited.
     */
    static auto breadthFirstSearch(const Graph& graph, const unsigned int start_vertex = 1) -> std::deque<unsigned int>;

    /**
     * @brief Dijkstra's algorithm for finding the shortest path in graph.
     * @param graph Contains information about the vertices and edges of the graph.
     * @param begin The starting vertex from where path starts.
     * @param end The last vertex where path ends.
     * @return A numerical result equal to the smallest distance between begin and last parameters.
     */
    static int getShortestPathBetweenVertices(const Graph &graph, const unsigned int begin, const unsigned int end);

    /**
     * @brief Floyd–Warshall algorithm algorithm for finding the shortest path in graph between all vertices.
     * @param graph Contains information about the vertices and edges of the graph.
     * @return A numerical result equal to the smallest distance between begin and last parameters.
     */
    static Graph getShortestPathsBetweenAllVertices(Graph &graph);

    /**
     * @brief Prim's algorithm for finding minimum spanning tree.
     * @param graph Contains information about the vertices and edges of the graph.
     * @return The object of Graph class with the adjacency matrix for the minimal spanning tree.
     */
    static Graph getLeastSpanningTree(const Graph& graph);
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
