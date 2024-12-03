// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_GUI_CLI_CLI_HPP_
#define _A2_SIMPLE_NAVIGATOR_GUI_CLI_CLI_HPP_

#include <string>
#include <vector>
#include <limits>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <functional>

#include "./../presenter/presenter.hpp"

namespace s21::TextSettings{

inline constexpr char reset[] = "\033[0m";
inline constexpr char f_red[] = "\033[31m";
inline constexpr char f_green[] = "\033[32m";


} // namespace s21::FontSettings

namespace s21::TextInfo{

inline constexpr char title[] = 
"   ____    __             __  ___ ___\n" \
"  / __/___/ /  ___  ___  / / |_  <  /\n" \
" _\\ \\/ __/ _ \\/ _ \\/ _ \\/ / / __// / \n" \
"/___/\\__/_//_/\\___/\\___/_/ /____/_/  \n"; 
                                     
inline constexpr char menu[] =
    "+----+----------------------+-----------------------------------------------------------------------------+\n" \
    "|  # | Option               | Description                                                                 |\n" \
    "+----+----------------------+-----------------------------------------------------------------------------+\n" \
    "| -1 | Exit                 |                                                                             |\n" \
    "|  0 | Menu                 | Shows this message.                                                         |\n" \
    "|  1 | Load                 | Loads graph data from an adjacency matrix file.                             |\n" \
    "|  2 | Export               | Creates a .dot file with the graph data.                                    |\n" \
    "|  3 | Depth first search   | Performs graph traversal using a depth first search algorithm.              |\n" \
    "|  4 | Breadth first search | Performs graph traversal using a breadth first search algorithm.            |\n" \
    "|  5 | Dijkstra             | Outputs the shortest distance between two vertices of the graph.            |\n" \
    "|  6 | Floyd-Warshall       | Outputs a matrix with the shortest paths between all vertices of the graph. |\n" \
    "|  7 | Prim                 | Outputs the matrix of the graph's spanning tree.                            |\n" \
    "+----+----------------------+-----------------------------------------------------------------------------+\n";

} // namespace s21::Text

namespace s21{

class Cli final{
public:
    Cli() = default;
    Cli(const Cli& other) = delete;
    Cli(Cli&& other) = delete;
    ~Cli() = default;

    Cli& operator = (const Cli& other) = delete;
    Cli& operator = (Cli&& other) = delete;

    void start() const;

private:
    template <typename T>
    T userInput() const;

    void loadGraph();
    void exportGraph() const;

    void depthFirstSearch() const;
    void breadthFirstSearch() const;
    void dijkstraAlgorithm() const;
    void floydWarshallAlgorighm() const;
    void primAlgorithm() const;

    void printMatrix(const Matrix<int>& matrix) const;

    Presenter presenter_;

    std::vector<std::function<void()>> options_{
        {[](){ std::cout << TextInfo::menu; }},
        {[this](){ this->loadGraph(); }},
        {[this](){ this->exportGraph(); }},
        {[this](){ this->depthFirstSearch(); }},
        {[this](){ this->breadthFirstSearch(); }},
        {[this](){ this->dijkstraAlgorithm(); }},
        {[this](){ this->floydWarshallAlgorighm(); }},
        {[this](){ this->primAlgorithm(); }}
    };

};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_GUI_CLI_CLI_HPP_
