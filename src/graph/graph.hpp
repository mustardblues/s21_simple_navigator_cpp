// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_GRAPH_GRAPH_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_GRAPH_GRAPH_HPP_

#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iterator>

#include "./../matrix/matrix.hpp"

namespace s21{

/**
 * @enum GraphType
 * @brief Contains information about graph types.
 */
enum class GraphType : char{
    Undirected,
    Directed
};

/**
 * @class Graph
 * @brief The class is used to store information about graphs.
 * 
 * @details Graph class contains data about the vertices and 
 * edges of a graph in the format of an adjacency matrix.
 */
template <typename T>
class Graph final{
public:
    /**
     * @brief Creates an empty adjacency matrix.
     */
    Graph() : vertices_(0), capacity_(0), data_(nullptr) {}

    /**
     * @brief Creates an N x N adjacency matrix where N is the length parameter.
     */
    Graph(const std::size_t vertices) 
    : vertices_(vertices), capacity_(vertices * vertices), data_(new T[capacity_]{}) {}

    /**
     * @brief Loads the adjacency matrix from a file.
     */
    Graph(const std::filesystem::path& path){ this->loadGraphFromFile(path); }

    /**
     * @brief Copies data from another object from Graph class.
     */
    Graph(const Graph& other) : Graph(other.vertices_){
        std::copy(other.data_, other.data_ + other.capacity_, data_);
    }

    /**
     * @brief Moves data from another object from Graph class.
     */
    Graph(Graph&& other) noexcept{
        vertices_ = other.vertices_;
        capacity_ = other.capacity_;
        data_ = other.data_;

        other.vertices_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }

    /**
     * @brief Clears all data of the Graph class after leaving the scope.
     */
    ~Graph(){
        if(data_ == nullptr) return;

        delete[] data_;
        data_ = nullptr;

        vertices_ = 0;
        capacity_ = 0;
    }

    /**
     * @brief Copying assignment operator.
     * @param other Graph reference parameter.
     */
    Graph& operator = (const Graph& other){
        if(this == &other) return *this;

        vertices_ = other.vertices_;
        capacity_ = other.capacity_;
        data_ = new T[other.capacity_]{};

        std::copy(other.data_, other.data_ + other.capacity_, data_);

        return *this;
    }

    /**
     * @brief Rvalue assignment operator.
     * @param other Rvalue parameter.
     */
    Graph& operator = (Graph&& other) noexcept{
        if(this == &other) return *this;

        vertices_ = other.vertices_;
        capacity_ = other.capacity_;
        data_ = other.data_;

        other.vertices_ = 0;
        other.data_ = nullptr;

        return *this;
    }

    /**
     * @brief compares objects of the Graph class.
     */
    bool operator == (const Graph& other) const{
        if (vertices_ != other.vertices_) return false;

        return std::equal(other.data_, other.data_ + other.capacity_, data_);
    }

    /**
     * @brief Provides access to graph without segmentation fault.
     * @param row Row element index.
     * @param col Column element index.
     * @return Element reference from graph.
     */
    [[ nodiscard ]] int& operator () (const std::size_t row, const std::size_t col) {
        if(row < vertices_ && col < vertices_) return data_[vertices_ * row + col];

        static T default_value{};

        return default_value;
    }

    /**
     * @brief Provides access to graph without segmentation fault.
     * @param row Row element index.
     * @param col Column element index.
     * @return Value stored in the graph.
     */
    int operator () (const std::size_t row, const std::size_t col) const { 
        if(row < vertices_ && col < vertices_) return data_[vertices_ * row + col];

        return 0;
    }

    /**
     * @brief Provides access to graph without segmentation fault.
     * @param pos Element index.
     * @return Value stored in the graph.
     */
    [[ nodiscard ]] int& operator () (const std::size_t pos) { 
        if(pos < capacity_) return data_[pos];

        static T default_value{};

        return default_value;
    }

    /**
     * @brief Provides access to graph without segmentation fault.
     * @param pos Element index.
     * @return Value stored in the graph.
     */
    int operator () (const std::size_t pos) const {
        if(pos < capacity_) return data_[pos];
        
        return 0;
    }

    /**
     * @brief Returns a first pointer from the graph.
     */
    [[ nodiscard ]] int* begin(){ return data_; }

    /**
     * @brief Returns a constant first pointer from the matrix.
     */
    const int* begin() const { return data_; }

    /**
     * @brief Returns a last pointer from the graph.
     */
    [[ nodiscard ]] int* end(){ return data_ + capacity_; }
    
    /**
     * @brief Returns a constant last pointer from the matrix.
     */
    const int* end() const { return data_ + capacity_; }

    /**
     * @brief Checks if the graph is empty.
     */
    bool empty() const { return data_ == nullptr; }

    /**
     * @brief Returns the number of vertices.
     */
    std::size_t vertices() const { return vertices_; }

    /**
     * @brief Returns graph's capacity.
     */
    std::size_t capacity() const { return capacity_; }

    /**
     * @brief Returns graph type.
     * @return Undirected or directed graph type.
     */
    GraphType type() const;

    /**
     * @brief Gets graph information from adjacency matrices.
     * @param filename The name of the file storing the adjacency matrices.
     * @return 0 if the load was in error, or 1 if the graph information was received.
     */
    bool loadGraphFromFile(const std::filesystem::path& filepath);

    /**
     * @brief Exports graph information to dot file.
     * @param filename The name of dot file to export.
     * @return 0 if the export to dot file was invalid, or 1 if the export was successful.
     */
    bool exportGraphToDot(const std::filesystem::path& filepath) const;

private:
    std::size_t vertices_;
    std::size_t capacity_;

    T* data_;
};

} // namespace s21

#include "graph.tpp"

#endif // _A2_SIMPLE_NAVIGATOR_SRC_GRAPH_GRAPH_HPP_
