// Copyright 2024 stranger

#include "aco.hpp"

namespace s21{

AntColonyOptimization::AntColonyOptimization(const Graph& graph)
 : graph_(graph), 
 visited_(graph_.vertices(), false), 
 pheramone_(graph_.vertices(), start_pheramone_) {}

TsmResult AntColonyOptimization::findPath(){
    if(graph_.vertices() == 0) return {};

    TsmResult result;

    for(unsigned int i; i < max_interations_; ++i){
        Matrix<double> new_pheramone(graph_.vertices(), 0.0f);

        for(unsigned int j = 0, size = graph_.vertices(); j < size; ++j){
            while(this->makeChoice()) {}

            if(vertices_.size() != size + 1){
                for(unsigned int k = 0, size = vertices_.size() - 1; k < size; ++k){
                    new_pheramone(vertices_[k], vertices_[k + 1]) += q_ / distance_;
                }
            }
        }

        for(unsigned int j = 0; j < pheramone_.capacity(); ++j){
            pheramone_(j) = evaporation_ * pheramone_(j) + new_pheramone(j);
        }

        distance_ = 0.0f;
        vertices_.clear();
    }

    return result;
}

bool AntColonyOptimization::makeChoice(){
    std::deque<std::size_t> nearest_vertices;

    for(unsigned int i = 0; i < graph_.vertices(); ++i){
        if(visited_[i] == false && graph_(current_vertex_, i) != 0){
            nearest_vertices.push_back(i);
        }
    }

    if(nearest_vertices.empty()){
        if(graph_(current_vertex_, start_vertex_) != 0){
            vertices_.push_back(start_vertex_);
            distance_ += graph_(current_vertex_, start_vertex_);
        }

        return false;
    }

    std::deque<double> wish(nearest_vertices.size(), 0.0f);
    double all_wishes = 0.0f;

    for(auto v : nearest_vertices){
        wish.push_back(std::pow(pheramone_(current_vertex_, v), alpha_) 
        * std::pow(graph_(current_vertex_, v), beta_));
        all_wishes += wish.back();
    }

    std::vector<double> probability(nearest_vertices.size(), 0.0f);
    probability[0] = wish[0] / all_wishes;

    for(unsigned int i = 1; i < wish.size(); ++i){
        probability[i] = wish[i] / all_wishes + probability[i - 1];
    }
    
    double choice = makeRandomChoice();

    for(unsigned int i = 0, size = probability.size(); i < size; ++i){
        if(choice <= probability[i]){
            vertices_.push_back(nearest_vertices[i]);
            distance_ += graph_(current_vertex_, nearest_vertices[i]);

            current_vertex_ = nearest_vertices[i];

            visited_[i] = true;

            i = size;
        }
    }

    return true;
}

double AntColonyOptimization::makeRandomChoice(){
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dist(0.0, 1.0);

    return dist(gen);
}

} // namespace s21