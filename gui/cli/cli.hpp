// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_GUI_CLI_CLI_HPP_
#define _A2_SIMPLE_NAVIGATOR_GUI_CLI_CLI_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#include <functional>

#include <limits>
#include <iomanip>

#include "./../presenter/presenter.hpp"

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

    std::string text_[8]{
        #include "text.hpp"

    };

    Presenter presenter_;

    std::function<void()> options_[8]{
        {[this](){ std::cout << text_[3]; }},
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
