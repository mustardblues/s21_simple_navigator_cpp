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
inline constexpr char new_line[] = "> ";

inline constexpr char help[] =
    "\t0\tload                 \n" \
    "\t1\texport               \n" \
    "\t2\tdepth first search   \n" \
    "\t3\tbreadth first search \n" \
    "\t4\tDijkstra             \n" \
    "\t5\tFloyd-Warshall       \n" \
    "\t6\tPrim                 \n";

inline constexpr char error[] =
    "\t+-------------------------+\n" \
    "\t|          Error          |\n" \
    "\t+-------------------------+\n";

inline constexpr char success[] =
    "\t+-------------------------+\n" \
    "\t|         Success         |\n" \
    "\t+-------------------------+\n";

inline constexpr char output[] =
    "\t+-------------------------+\n" \
    "\t|         Output          |\n" \
    "\t+-------------------------+\n";

inline constexpr char file_path[] = 
    "\tabc\tEnter the file path\n";

inline constexpr char graph_format[] =
    "\t1\tdirected format      \n" \
    "\t2\tundirected format    \n";

inline constexpr char specify_vertex[] = "\tSpecify the vertices\n";

} // namespace s21::Eng

namespace s21::Font{
inline constexpr char bold[] = "\033[1m";
inline constexpr char red[] = "\033[31m";
inline constexpr char green[] = "\033[32m";
inline constexpr char yellow[] = "\033[33m";
inline constexpr char blue[] = "\033[36m";
inline constexpr char endf[] = "\033[0m";

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
    void info() const;

    void loadGraph();
    void exportGraph() const;

    void depthFirstSearch() const;
    void breadthFirstSearch() const;
    void dijkstraAlgorithm() const;
    void floydWarshallAlgorighm() const;
    void primAlgorithm() const;

    Presenter presenter_;

    std::vector<std::function<void()>> options_{
        {[this](){ this->loadGraph(); }},
        {[this](){ this->exportGraph(); }},
        {[this](){ this->depthFirstSearch(); }},
        {[this](){ this->breadthFirstSearch(); }},
        {[this](){ this->dijkstraAlgorithm(); }},
    };

};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_GUI_CLI_CLI_HPP_
