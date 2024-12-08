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

    bool loadGraph(const std::filesystem::path& path){
        return graph_.loadGraphFromFile(path);
    }

    bool exportUndirectedGraph(const std::filesystem::path& path) const{
        return graph_.exportGraphToDot<GraphType::Undirected>(path);
    }

    bool exportDirectedGraph(const std::filesystem::path& path) const{
        return graph_.exportGraphToDot<GraphType::Directed>(path);
    }

    auto depthFirstSearch(const std::size_t start_vertex) const -> std::deque<unsigned int>{
        return GraphAlgorithms::depthFirstSearch(graph_, start_vertex);
    }

    auto breadthFirstSearch(const std::size_t start_vertex) const -> std::deque<unsigned int>{
        return GraphAlgorithms::breadthFirstSearch(graph_, start_vertex);
    }

    int dijkstraAlgorithm(const std::size_t begin, const std::size_t end) const{
        return GraphAlgorithms::getShortestPathBetweenVertices(graph_, begin, end);
    }

    auto floydWarshallAlgorighm() const -> Matrix<int>{
        return GraphAlgorithms::getShortestPathsBetweenAllVertices(graph_);
    }

    auto primAlgorithm(const std::size_t start_vertex) const -> Matrix<int>{
        return GraphAlgorithms::getLeastSpanningTree(graph_, start_vertex);
    }

    Graph graph_;
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_GUI_PRESENTER_PRESENTER_HPP_
