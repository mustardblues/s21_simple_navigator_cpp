// Copyright 2024 stranger

#include "graph.hpp"

namespace s21{

Graph::Graph() : vertices_(0) {}

Graph::Graph(const std::size_t vertices) : vertices_(vertices), matrix_(vertices_, vertices_) {}

Graph::Graph(const std::filesystem::path& path){ this->loadGraphFromFile(path); }

Graph::Graph(const Graph& other){
    vertices_ = other.vertices_;
    matrix_ = other.matrix_;
}

Graph::Graph(Graph&& other) noexcept{
    vertices_ = other.vertices_;
    matrix_ = std::move(other.matrix_);

    other.vertices_ = 0;
}

bool Graph::loadGraphFromFile(const std::filesystem::path& path){
    if(!std::filesystem::exists(path.c_str())) return false;

    std::fstream f_stream(path, std::ios::in);
    std::stringstream content;
    content << f_stream.rdbuf();
    f_stream.close();

    std::stringstream s_stream(content.str(), std::ios::in);

    std::size_t v{};
    s_stream >> v;

    if(s_stream.fail()) return false;

    vertices_ = v;

    Matrix<int> temp(vertices_, vertices_);

    std::copy(std::istream_iterator<unsigned int>(s_stream), std::istream_iterator<unsigned int>(), temp.begin());

    matrix_ = std::move(temp);

    return true;
}

template <>
bool Graph::exportGraphToDot<GraphType::Undirected>(const std::filesystem::path& path) const{
    if(vertices_ == 0) return false;

    std::filesystem::path filename = path;

    if(filename.extension() != ".dot") filename.replace_extension(std::filesystem::path(".dot"));

    std::fstream f_stream(filename, std::ios::out);

    std::string graphname(filename.stem());
    graphname.erase(std::remove(graphname.begin(), graphname.end(), '\"'), graphname.end());
    
    f_stream << "graph " <<  graphname << "{\n";

    for(unsigned int i = 0; i < vertices_; ++i){
        f_stream << "\t" << i + 1 << ";\n";
    }

    for(unsigned int i = 0; i < vertices_; ++i){
        for(unsigned int j = i; j < vertices_; ++j){
            if(matrix_(i, j) != 0 && matrix_(j, i) != 0){
                f_stream << "\t" << i + 1 << " -- " << j + 1 << ";\n";
            }
        }
    }

    f_stream << "}";

    return true;
}

template <>
bool Graph::exportGraphToDot<GraphType::Directed>(const std::filesystem::path& path) const{
    if(vertices_ == 0) return false;

    std::filesystem::path filename = path;

    if(filename.extension() != ".dot") filename.replace_extension(std::filesystem::path(".dot"));

    std::fstream f_stream(filename, std::ios::out);

    std::string graphname(filename.stem());
    graphname.erase(std::remove(graphname.begin(), graphname.end(), '\"'), graphname.end());

    f_stream << "digraph " <<  graphname << "{\n";

    for(unsigned int i = 0; i < vertices_; ++i){
        f_stream << "\t" << i + 1 << ";\n";
    }

    for(unsigned int i = 0; i < vertices_; ++i){
        for(unsigned int j = i; j < vertices_; ++j){
            if(matrix_(i, j) != 0){
                f_stream << "\t" << i + 1 << " -> " << j + 1 << ";\n";
            }
            else if(matrix_(j, i) != 0){
                f_stream << "\t" << j + 1 << " -> " << i + 1 << ";\n";
            }
        }
    }

    f_stream << "}";

    return true;
}

} // namespace s21