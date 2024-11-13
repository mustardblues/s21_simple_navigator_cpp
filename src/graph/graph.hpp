// Copyright 2024 Team TL:stranger@student.21-school.ru

#ifndef _A1_SIMPLE_NAVIGATOR_SRC_GRAPTH_GRAPH_HPP_
#define _A1_SIMPLE_NAVIGATOR_SRC_GRAPTH_GRAPH_HPP_

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

namespace s21{

/**
 * @class Graph
 * @brief The class is used to store information about graphs. 
 */
class Graph final{
public:
    Graph();
    Graph(const std::size_t length);
    Graph(const Graph& other);
    Graph(Graph&& other) noexcept;
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
     * @brief Provide access to graph without segmentation fault.
     * @param row Row element index.
     * @param col Column element index.
     * @return Element reference from graph.
     */
    [[ nodiscard ]] unsigned int& operator () (const std::size_t row, const std::size_t col);

    /**
     * @brief Provide access to graph without segmentation fault.
     * @param row Row element index.
     * @param col Column element index.
     * @return Value stored in the graph.
     */
    [[ nodiscard ]] unsigned int operator () (const std::size_t row, const std::size_t col) const;

    /**
     * @brief Get graph information from adjacency matrices.
     * @param filename The name of the file storing the adjacency matrices.
     * @return 0 if the load was in error, or 1 if the graph information was received.
     */
    bool loadGraphFromFile(const std::string& filename);

    /**
     * @brief Export graph information to dot file.
     * @param filename The name of dot file to export.
     * @return 0 if the export to dot file was invalid, or 1 if the export was successful.
     */
    bool exportGraphToDot(const std::string& filename) const;

    /**
     * @brief Returns the number of vertices.
     */
    inline std::size_t length() const { return length_; }

private:
    std::string getFileContent(const std::string& filename);
    
    std::size_t length_;

    unsigned int* data_;

};

} // namespace s21

#endif // _A1_SIMPLE_NAVIGATOR_SRC_GRAPTH_GRAPH_HPP_
