// Copyright 2024 stranger

#include "graph.hpp"

namespace s21{

Graph::Graph() : length_(0), capacity_(0), data_(nullptr) {}

Graph::Graph(const std::size_t length) : length_(length), 
                                        capacity_(length_ * length_), 
                                        data_(new unsigned int[capacity_]{}) {}

Graph::Graph(const std::filesystem::path& filepath) : Graph(){
    this->loadGraphFromFile(filepath);
}

Graph::Graph(const Graph& other) : Graph(){ *this = other; }

Graph::Graph(Graph&& other) noexcept : Graph() { *this = std::move(other); }

Graph::~Graph(){
    if(data_ == nullptr) return;

    delete[] data_;

    length_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

Graph& Graph::operator = (const Graph& other){
    if(this == &other) return *this;

    length_ = other.length_;

    capacity_ = other.capacity_;

    if(data_ != nullptr) delete[] data_;

    data_ = new unsigned int[capacity_]{};

    std::copy(other.data_, other.data_ + capacity_, data_);

    return *this;
}

Graph& Graph::operator = (Graph&& other) noexcept{
    std::swap(length_, other.length_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);

    other.length_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;

    return *this;
}

[[ nodiscard ]] unsigned int& Graph::operator () (const std::size_t row, const std::size_t col){
    if(row < length_ && col < length_){
        return *(data_ + (row * length_ + col));
    }

    static unsigned int default_value{0};

    return default_value;
}

unsigned int Graph::operator () (const std::size_t row, const std::size_t col) const{
    if(row < length_ && col < length_){
        return *(data_ + (row * length_ + col));
    }

    return 0;
}

bool Graph::loadGraphFromFile(const std::filesystem::path& filepath){
    if(!std::filesystem::exists(filepath.c_str())) return false;

    std::fstream f_stream(filepath, std::ios::in);
    std::stringstream content;
    content << f_stream.rdbuf();
    f_stream.close();

    std::stringstream s_stream(content.str(), std::ios::in);

    std::size_t new_length{};
    s_stream >> new_length;

    if(s_stream.fail()) return false;
    
    if(length_ != new_length){
        length_ = new_length;

        capacity_ = length_ * length_;

        if(data_ != nullptr) delete[] data_;

        data_ = new unsigned int[capacity_]{};
    }

    std::copy(std::istream_iterator<unsigned int>(s_stream), std::istream_iterator<unsigned int>(), data_);

    return true;
}

template <>
bool Graph::exportGraphToDot<GraphType::Undirected>(const std::filesystem::path& filepath) const{
    if(length_ == 0) return false;

    std::filesystem::path f = filepath;

    if(f.extension() != ".dot"){
        f.replace_extension(std::filesystem::path(".dot"));
    }

    std::fstream f_stream(f, std::ios::out);

    std::string graphname(f.stem());
    graphname.erase(std::remove(graphname.begin(), graphname.end(), '\"'), graphname.end());
    
    f_stream << "graph " <<  graphname << "{\n";

    for(unsigned int i = 0; i < length_; ++i){
        f_stream << "\t" << i + 1 << ";\n";
    }

    for(unsigned int i = 0; i < length_; ++i){
        for(unsigned int j = i; j < length_; ++j){
            if(data_[i * length_ + j] != 0 && data_[j * length_ + i] != 0){
                f_stream << "\t" << i + 1 << " -- " << j + 1 << ";\n";
            }
        }
    }

    f_stream << "}";

    return true;
}

template <>
bool Graph::exportGraphToDot<GraphType::Directed>(const std::filesystem::path& filepath) const{
    if(length_ == 0) return false;

    std::filesystem::path f = filepath;

    if(f.extension() != ".dot"){
        f.replace_extension(std::filesystem::path(".dot"));
    }

    std::fstream f_stream(f, std::ios::out);

    std::string graphname(f.stem());
    graphname.erase(std::remove(graphname.begin(), graphname.end(), '\"'), graphname.end());

    f_stream << "digraph " <<  graphname << "{\n";

    for(unsigned int i = 0; i < length_; ++i){
        f_stream << "\t" << i + 1 << ";\n";
    }

    for(unsigned int i = 0; i < length_; ++i){
        for(unsigned int j = i; j < length_; ++j){
            if(data_[i * length_ + j] != 0){
                f_stream << "\t" << i + 1 << " -> " << j + 1 << ";\n";
            }
            else if(data_[j * length_ + i] != 0){
                f_stream << "\t" << j + 1 << " -> " << i + 1 << ";\n";
            }
        }
    }

    f_stream << "}";

    return true;
}

} // namespace s21