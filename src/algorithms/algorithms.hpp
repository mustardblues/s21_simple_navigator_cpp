// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_

#include <deque>

#include "./../graph/graph.hpp"

#include "containers/queue/queue.hpp"
#include "containers/stack/stack.hpp"

namespace s21{

class GraphAlgorithms final{
public:
    GraphAlgorithms() = default;
    GraphAlgorithms(const GraphAlgorithms& other) = delete;
    GraphAlgorithms(GraphAlgorithms&& other) = delete;
    ~GraphAlgorithms() = default;

    GraphAlgorithms& operator = (const GraphAlgorithms& other) = delete;
    GraphAlgorithms& operator = (GraphAlgorithms&& other) = delete;

    [[ nodiscard ]] static std::deque<unsigned int> depthFirstSearch(const Graph& graph, int start_vertex);
    [[ nodiscard ]] static std::deque<unsigned int> breadthFirstSearch(const Graph& graph, int start_vertex);

private:

};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ALGORITHMS_HPP_
