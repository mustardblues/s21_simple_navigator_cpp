// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ACO_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ACO_HPP_

#include "./../../../graph/graph.hpp"
#include "./../tsm_result.hpp"

namespace s21{

class Ant{
public:
    Ant(const std::size_t start_vertex = 1);
};

class AntColonyOptimization{
public:
    AntColonyOptimization() = delete;
    explicit AntColonyOptimization(const Graph& graph);
    AntColonyOptimization(const AntColonyOptimization& other) = delete;
    AntColonyOptimization(AntColonyOptimization&& other) = delete;
    ~AntColonyOptimization() = default;

    AntColonyOptimization& operator = (const AntColonyOptimization& other) = delete;
    AntColonyOptimization& operator = (AntColonyOptimization&& other) = delete;

    TsmResult SolveTravelingSalesmanProblem(const Graph& graph); 

private:
    const double alpha_{1.0};
    const double beta_{2.0};
    const double q_{5.0};

    Matrix<double> pheramone_;

};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ACO_HPP_
