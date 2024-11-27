// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_GUI_PRESENTER_PRESENTER_HPP_
#define _A2_SIMPLE_NAVIGATOR_GUI_PRESENTER_PRESENTER_HPP_

#include <deque>
#include <filesystem>

#include "./../../src/graph/graph.hpp"
#include "./../../src/algorithms/algorithms.hpp"

namespace s21{

class Presenter final{
public:
    Presenter() = default;
    Presenter(const Presenter& other) = delete;
    Presenter(Presenter&& other) noexcept = delete;
    ~Presenter() = default;

    Presenter& operator = (const Presenter& other) = delete;
    Presenter& operator = (Presenter&& other) noexcept = delete;

    Graph loadGraphFromFile(const std::filesystem::path& filepath){
        return Graph(filepath);
    }

    auto depthFirstSearch(const Graph& graph, const unsigned int start_vertex) -> std::deque<unsigned int>{
        return GraphAlgorithms::depthFirstSearch(graph, start_vertex);
    }

    auto breadthFirstSearch(const Graph& graph, const unsigned int start_vertex) -> std::deque<unsigned int>{
        return GraphAlgorithms::breadthFirstSearch(graph, start_vertex);
    }

    int DijkstraAlgorithm(const Graph& graph, const unsigned int begin, const unsigned int end){
        return GraphAlgorithms::getShortestPathBetweenVertices(graph, begin, end);
    }

    auto FloydWarshallAlgorighm(const Graph& graph) -> Matrix<int>{
        return GraphAlgorithms::getShortestPathsBetweenAllVertices(graph);
    }

    auto PrimAlgorithm(const Graph& graph) -> Matrix<int>{
        return GraphAlgorithms::getLeastSpanningTree(graph);
    }
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_GUI_PRESENTER_PRESENTER_HPP_
