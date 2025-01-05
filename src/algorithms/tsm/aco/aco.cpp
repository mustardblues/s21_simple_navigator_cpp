// Copyright 2024 stranger

#include "aco.hpp"

#include <iostream>

namespace s21{

AntColonyOptimization::AntColonyOptimization(const Graph& graph) : pheromone_(graph.vertices(), 0.0), graph_(graph){
    for(unsigned int i = 0, size = pheromone_.rows(); i < size; ++i){
        for(unsigned int j = 0; j < size; ++j){
            if(i != j) pheromone_(i, j) = start_pheromone_;
        }
    }
}

TsmResult AntColonyOptimization::findPath(){
    TsmResult result;

    result.distance_ = Constants::inf;

    const unsigned int vertex_number = graph_.vertices();
    const unsigned int pheromone_number = pheromone_.rows();

    for(unsigned int i = 0; i < max_iterations_; ++i){
        Matrix<double> new_pheromone_portion(vertex_number, 0.0);

        for(unsigned int j = 0; j < vertex_number; ++j){
            Ant ant(vertex_number, j);

            while(this->makeChoice(ant)) {}

            bool is_correct_size = ant.report_.vertices_.size() == vertex_number + 1;
            bool is_correct_dist = ant.report_.vertices_.front() == ant.report_.vertices_.back();

            if(is_correct_size && is_correct_dist){
                for(unsigned int k = 0; k < vertex_number; ++k){
                    const unsigned int from = ant.report_.vertices_[k];
                    const unsigned int to = ant.report_.vertices_[k + 1];

                    new_pheromone_portion(from, to) += q_ / ant.report_.distance_;
                }

                if(ant.report_.distance_ < result.distance_){
                    result = std::move(ant.report_);
                }
            }
        }

        for(unsigned int j = 0; j < pheromone_number; ++j){
            for(unsigned int k = 0; k < pheromone_number; ++k){
                pheromone_(j, k) = evaporation_ * pheromone_(j, k) + new_pheromone_portion(j, k);
            }
        }
    }

    for(unsigned int i = 0; i < pheromone_number; ++i){
        for(unsigned int j = 0; j < pheromone_number; ++j){
            std::cout << static_cast<int>(pheromone_(i, j)) << " ";
        }
        std::cout << "\n";
    }

    // tests/unit/data/matrix_11.txt

    return result;
}

bool AntColonyOptimization::makeChoice(Ant& ant){
    std::deque<unsigned int> neighboring_vertices;

    for(unsigned int i = 0, size = graph_.vertices(); i < size; ++i){
        if(ant.visited_[i] == false && graph_(ant.current_vertex_, i) != 0){
            neighboring_vertices.push_back(i);
        }
    }

    const unsigned int neighbors_number = neighboring_vertices.size();

    if(neighbors_number == 0){
        if(graph_(ant.current_vertex_, ant.start_vertex_) != 0){
            ant.report_.distance_ += graph_(ant.current_vertex_, ant.start_vertex_);
            ant.report_.vertices_.push_back(ant.start_vertex_);
        }

        return false;
    }

    double all_wishes{};
    std::deque<double> wish;

    for(const auto& n : neighboring_vertices){
        wish.push_back(std::pow(pheromone_(ant.current_vertex_, n), alpha_) 
        * std::pow(1.0 / graph_(ant.current_vertex_, n), beta_));

        all_wishes += wish.back();
    }

    const double choice = this->makeRandomChoice() * all_wishes;

    double probability_range{};

    for(unsigned int i = 0; i < neighbors_number; ++i){
        probability_range += wish[i];

        if(choice <= probability_range){
            double next_vertex = neighboring_vertices[i];

            ant.report_.distance_ += graph_(ant.current_vertex_, next_vertex);
            ant.report_.vertices_.push_back(next_vertex);

            ant.visited_[next_vertex] = true;

            ant.current_vertex_ = next_vertex;

            i = neighbors_number;
        }
    }

    return true;
}

double AntColonyOptimization::makeRandomChoice(){
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    return dist(gen);
}

} // namespace s21