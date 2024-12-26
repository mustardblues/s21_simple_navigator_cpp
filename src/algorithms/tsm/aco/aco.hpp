// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ACO_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ACO_HPP_

#include <cmath>
#include <random>
#include <deque>

#include "./../../../graph/graph.hpp"
#include "./../tsm_result.hpp"

namespace s21{

class AntColonyOptimization{
public:
    AntColonyOptimization() = delete;
    AntColonyOptimization(const Graph& graph);
    AntColonyOptimization(const AntColonyOptimization& other) = delete;
    AntColonyOptimization(AntColonyOptimization&& other) = delete;
    ~AntColonyOptimization() = default;

    AntColonyOptimization& operator = (const AntColonyOptimization& other) = delete;
    AntColonyOptimization& operator = (AntColonyOptimization&& other) = delete;

    TsmResult findPath();

private:
    const unsigned int max_interations_{100};

    unsigned int start_vertex_{0};
    unsigned int current_vertex_{0};

    const double alpha_{1.0};
    const double beta_{2.0};
    const double q_{5.0};
    const double start_pheramone_{1};
    const double evaporation_{0.6};

    double distance_{};
    std::vector<unsigned int> vertices_;

    Graph graph_;
    std::vector<bool> visited_;
    Matrix<double> pheramone_;

    bool makeChoice();
    double makeRandomChoice();
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ACO_HPP_
