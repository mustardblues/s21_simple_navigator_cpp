// Copyright 2024 stranger

#include "aco.hpp"

namespace s21{

AntColonyOptimization::AntColonyOptimization(const Graph<int>& graph) 
: vertex_number_(graph.vertices()), pheromone_(vertex_number_, start_pheromone_), graph_(graph){
    for(unsigned int i = 0; i < vertex_number_; ++i){
        pheromone_(i, i) = 0;
    }
}

TsmResult AntColonyOptimization::findPath(){
    TsmResult result;
    result.distance_ = Constants::inf;

    if(graph_.empty()) return result;

    for(unsigned int i = 0; i < max_iterations_; ++i){
        Matrix<double> new_pheromon_portion(vertex_number_, 0.0);
        
        for(unsigned int j = 0; j < vertex_number_; ++j){
            Ant ant(vertex_number_, j);

            this->antRun(ant);

            if(ant.report_.vertices_.size() == vertex_number_ + 1){
                for(unsigned int k = 0, size = vertex_number_; k < size; ++k){
                    const unsigned int from = ant.report_.vertices_[k];
                    const unsigned int to = ant.report_.vertices_[k + 1];

                    new_pheromon_portion(from, to) += q_ / ant.report_.distance_;
                }

                if(ant.report_.distance_ < result.distance_){
                    result = std::move(ant.report_);
                }
            }
        }

        for(unsigned int j = 0; j < vertex_number_; ++j){
            for(unsigned int k = 0; k < vertex_number_; ++k){
                pheromone_(j, k) = evaporation_ * pheromone_(j, k) + new_pheromon_portion(j, k);
            }
        }
    }

    return result;
}

void AntColonyOptimization::antRun(Ant& ant){
    while(true){
        std::deque<unsigned int> neighboring_vertex;

        double all_wishes{};
        std::deque<double> wish;

        for(unsigned int i = 0; i < vertex_number_; ++i){
            if(!ant.visited_[i] && graph_(ant.current_vertex_, i) != 0){
                neighboring_vertex.push_back(i);

                double p = std::pow(pheromone_(ant.current_vertex_, i), alpha_);
                double g = std::pow(1.0 / graph_(ant.current_vertex_, i), beta_);

                wish.push_back(p * g);
                all_wishes += wish.back();
            }
        }

        if(neighboring_vertex.empty()){
            if(graph_(ant.current_vertex_, ant.start_vertex_) != 0){
                ant.report_.vertices_.push_back(ant.start_vertex_);
                ant.report_.distance_ += graph_(ant.current_vertex_, ant.start_vertex_);
            }

            break;
        }

        double probability_range{};
        const double choice = this->makeRandomChoice() * all_wishes;

        for(unsigned int i = 0, size = wish.size(); i < size; ++i){
            probability_range += wish[i];

            if(choice <= probability_range){
                double next_vertex = neighboring_vertex[i];

                ant.report_.distance_ += graph_(ant.current_vertex_, next_vertex);
                ant.report_.vertices_.push_back(next_vertex);

                ant.current_vertex_ = next_vertex;

                ant.visited_[next_vertex] = true;

                i = size;
            }
        }
    }
}

double AntColonyOptimization::makeRandomChoice(){
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    return dist(gen);
}

} // namespace s21