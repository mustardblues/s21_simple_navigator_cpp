// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_GUI_CLI_CLI_HPP_
#define _A2_SIMPLE_NAVIGATOR_GUI_CLI_CLI_HPP_

#include <string>
#include <vector>
#include <limits>
#include <iostream>
#include <filesystem>
#include <functional>

#include "./../presenter/presenter.hpp"

namespace s21::Text{

inline constexpr char select[] = "select:~$ ";

inline constexpr char info[] =
    "(1) load               (2) export\n" \
    "(3) depth first search (4) breadth first search \n" \
    "(5) Dijkstra           (6) Floyd-Warshall\n" \
    "(7) Prim               (0) info\n";

inline constexpr char fail[] =
    "FAIL\n";

inline constexpr char ok[] =
    "OK\n";

inline constexpr char file[] = 
    "select file:~$ ";

inline constexpr char format[] =
    "(0) directed format    (1) undirected format\n";

inline constexpr char vertices[] = 
    "select vertices:~$ ";

} // namespace s21::Text

namespace s21::Font{

inline constexpr char reset[] = "\033[0m";
inline constexpr char bold[] = "\033[1m";
inline constexpr char red[] = "\033[31m";
inline constexpr char green[] = "\033[32m";

} // namespace s21::CliColors

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
    void loadGraph();
    void exportGraph() const;

    void depthFirstSearch() const;
    void breadthFirstSearch() const;
    void dijkstraAlgorithm() const;
    void floydWarshallAlgorighm() const;
    void primAlgorithm() const;

    Presenter presenter_;

    std::vector<std::function<void()>> options_{
        {[](){ std::cout << Text::info; }},
        {[this](){ this->loadGraph(); }},
        {[this](){ this->exportGraph(); }},
        {[this](){ this->depthFirstSearch(); }},
        {[this](){ this->breadthFirstSearch(); }},
        {[this](){ this->dijkstraAlgorithm(); }},
    };

};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_GUI_CLI_CLI_HPP_
