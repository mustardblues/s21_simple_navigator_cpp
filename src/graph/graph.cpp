// Copyright 2024 Team TL:stranger@student.21-school.ru

#include "graph.hpp"

namespace s21{

Graph::Graph() : length_(0), data_(nullptr) {}

Graph::Graph(const std::size_t length) : length_(length), data_(new unsigned int[length_ * length_]{}){}

Graph::Graph(const Graph& other){
    if(this == &other) return;

    length_ = other.length_;

    data_ = new unsigned int[length_ * length_]{};

    std::copy(other.data_, other.data_ + length_ * length_, data_);
}

Graph::Graph(Graph&& other) noexcept{
    std::swap(length_, other.length_);
    std::swap(data_, other.data_);

    other.length_ = 0;
    other.data_ = nullptr;
}

Graph::~Graph(){
    if(data_ == nullptr) return;

    delete[] data_;

    data_ = nullptr;

    length_ = 0;
}

Graph& Graph::operator = (const Graph& other){
    if(this != &other){
        length_ = other.length_;

        if(data_ != nullptr) delete[] data_;

        data_ = new unsigned int[length_ * length_]{};

        std::copy(other.data_, other.data_ + length_ * length_, data_);
    }

    return *this;
}

Graph& Graph::operator = (Graph&& other) noexcept{
    std::swap(length_, other.length_);
    std::swap(data_, other.data_);

    other.length_ = 0;
    other.data_ = nullptr;

    return *this;
}

[[ nodiscard ]] unsigned int Graph::operator () (const std::size_t row, const std::size_t col) const{
    if(row < length_ && col < length_){
        return *(data_ + (row * length_ + col));
    }

    return 0;
}

[[ nodiscard ]] unsigned int& Graph::operator () (const std::size_t row, const std::size_t col){
    if(row < length_ && col < length_){
        return *(data_ + (row * length_ + col));
    }

    static unsigned int default_value{0};

    return default_value;
}

bool Graph::loadGraphFromFile(const std::string& filename){
    std::stringstream stream(this->getFileContent(filename), std::ios::in);

    stream >> length_;

    if(data_ != nullptr) delete[] data_;

    data_ = new unsigned int[length_ * length_]{};

    for(unsigned int i = 0, size = length_ * length_; i < size; ++i){
        stream >> data_[i];

        if(stream.fail()){
            return false;
        }
    }

    return true;
}

std::string Graph::getFileContent(const std::string& filename){
    std::string content;

    std::fstream stream(filename, std::ios::in);

    if(stream.is_open()){
        std::stringstream buffer;

        buffer << stream.rdbuf();

        stream.close();

        content = buffer.str();
    }

    return content;
}

bool Graph::exportGraphToDot(const std::string& filename) const{
    std::fstream stream(filename, std::ios::out);

    stream << "graph graphname {\n";

    for(unsigned int i = 0; i < length_; ++i){
        for(unsigned int j = i; j < length_; ++j){
            if(data_[i * length_ + j] != 0){
                stream << "\t" << i + 1 << " -> " << j + 1 << ";" << std::endl;
            }
            else if(data_[j * length_ + i] != 0){
                stream << "\t" << i + 1 << " <- " << j + 1 << ";" << std::endl;
            }
            else{
                stream << "\t" << i + 1 << " -- " << j + 1 << ";" << std::endl;
            }
        }
    }

    stream << "}";

    return true;
}

} // namespace s21