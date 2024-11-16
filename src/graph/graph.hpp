// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_GRAPH_GRAPH_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_GRAPH_GRAPH_HPP_

#include <fstream>
#include <sstream>

#include <string>

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
class Graph final{
public:
    /**
     * @brief Creates an empty adjacency matrix.
     */
    Graph();

    /**
     * @brief Creates an N x N adjacency matrix where N is the length parameter.
     */
    Graph(const std::size_t length);

    /**
     * @brief Loads the adjacency matrix from a file.
     */
    Graph(const std::string& filename);

    /**
     * @brief Copies data from another object from Graph class.
     */
    Graph(const Graph& other);

    /**
     * @brief Moves data from another object from Graph class.
     */
    Graph(Graph&& other) noexcept;

    /**
     * @brief Clears all data of the Graph class after leaving the scope.
     */
    ~Graph();

    /**
     * @brief Copying assignment operator.
     * @param other Graph reference parameter.
     */
    Graph& operator = (const Graph& other);

    /**
     * @brief Rvalue assignment operator.
     * @param other Rvalue parameter.
     */
    Graph& operator = (Graph&& other) noexcept;

    /**
     * @brief Compares the adjacency matrices of two graphs.
     * @return 0 if the graphs aren't equal, or 1 if they are.
     */
    constexpr bool operator == (const Graph& other) const{
        if(length_ != other.length_) return false;

        return std::equal(other.begin(), other.end(), data_);
    }

    /**
     * @brief Provides access to graph without segmentation fault.
     * @param row Row element index.
     * @param col Column element index.
     * @return Element reference from graph.
     */
    [[ nodiscard ]] unsigned int& operator () (const std::size_t row, const std::size_t col);

    /**
     * @brief Provides access to graph without segmentation fault.
     * @param row Row element index.
     * @param col Column element index.
     * @return Value stored in the graph.
     */
    unsigned int operator () (const std::size_t row, const std::size_t col) const;

    /**
     * @brief Returns the number of vertices.
     */
    std::size_t length() const { return length_; }

    /**
     * @brief Returns a constant first pointer from the graph.
     */
    [[ nodiscard ]] unsigned int* begin() { return data_; }

    /**
     * @brief Returns a constant last pointer from the graph.
     */
    [[ nodiscard ]] unsigned int* end() { return data_ + length_ * length_; }

    /**
     * @brief Returns a constant first pointer from the graph.
     */
    const unsigned int* begin() const { return data_; }

    /**
     * @brief Returns a constant last pointer from the graph.
     */
    const unsigned int* end() const { return data_ + length_ * length_; }

    /**
     * @brief Gets graph information from adjacency matrices.
     * @param filename The name of the file storing the adjacency matrices.
     * @return 0 if the load was in error, or 1 if the graph information was received.
     */
    bool loadGraphFromFile(const std::string& filename);

    /**
     * @brief Exports graph information to dot file.
     * @param filename The name of dot file to export.
     * @return 0 if the export to dot file was invalid, or 1 if the export was successful.
     */
    template <GraphType T>
    bool exportGraphToDot(const std::string& filename) const;

    /**
     * @brief Clears all data of the Graph class.
     */
    void clear() { this->~Graph(); }

private:
    inline std::string getFileContent(const std::string& filename);

    inline std::string setValidFileName(const std::string& filename) const;
    
    std::size_t length_;

    unsigned int* data_;

};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_GRAPH_GRAPH_HPP_
