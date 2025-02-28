// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ACO_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ACO_HPP_

#include <cmath>
#include <random>
#include <deque>

#include "./../../../constants/constants.hpp"
#include "./../../../graph/graph.hpp"
#include "./../tsm_result.hpp"

namespace s21{

/**
 * @class AntColonyOptimization
 * @brief Finds a solution to the traveling salesman problem.
 */
class AntColonyOptimization final{
public:
    AntColonyOptimization() = delete;

    /**
     * @brief Class constructor that accepts a graph class.
     */
    AntColonyOptimization(const Graph<int>& graph);

    AntColonyOptimization(const AntColonyOptimization& other) = delete;
    AntColonyOptimization(AntColonyOptimization&& other) = delete;
    ~AntColonyOptimization() = default;

    AntColonyOptimization& operator = (const AntColonyOptimization& other) = delete;
    AntColonyOptimization& operator = (AntColonyOptimization&& other) = delete;

    /**
     * @brief Finds a solution to the traveling salesman problem using a standard ACO algorithm.
     * @return Returns a data structure with visited vertices and the distance between them.
     */
    TsmResult findPath();

private:
    const unsigned int max_iterations_{500};

    const unsigned int vertex_number_{0};

    const double start_pheromone_{0.1};

    const double alpha_{1.0};
    const double beta_{2.0};
    const double q_{5.0};
    const double evaporation_{0.5};

    Matrix<double> pheromone_;
    Graph<int> graph_;

    /**
     * @class Ant
     * @brief Used in the AntColonyOptimization class.
     */
    class Ant{
    public:
        unsigned int start_vertex_;
        unsigned int current_vertex_;

        std::vector<bool> visited_;

        TsmResult report_;

        explicit Ant(const unsigned int vertex_number, const unsigned int start_vertex = 0)
        : start_vertex_(start_vertex), current_vertex_(start_vertex), visited_(vertex_number, false){
            visited_[start_vertex] = true;

            report_.distance_ = 0.0;
            report_.vertices_.push_back(start_vertex);
        }

        ~Ant() = default;
    };

    void antRun(Ant& ant);
    double makeRandomChoice();
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_ACO_HPP_
