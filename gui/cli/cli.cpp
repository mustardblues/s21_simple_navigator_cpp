// Copyright 2024 stranger

#include "cli.hpp"

namespace s21{

void Cli::start() const{
    std::cout << TextInfo::creators << TextInfo::menu;

    while(true){
        std::cout << "Option: ";
        int index = this->userInput<int>();

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(std::cin.eof()) return;
        }
        else if(index >= 0 && index < 9){
            if(index > 1 && presenter_.graph_.vertices() != 0){
                options_[index]();
            }
            else if(index < 2){
                options_[index]();
            }
            else{
                std::cout << TextSettings::f_red << TextInfo::fail << TextSettings::reset;
            }
        }
    }
}

template <typename T>
T Cli::userInput() const{
    std::string str;
    std::getline(std::cin, str);
    std::stringstream stream(str);

    T code{};
    stream >> code;

    return code;
}

void Cli::loadGraph(){
    std::cout << "File: ";

    std::filesystem::path path = this->userInput<std::filesystem::path>();

    if(std::cin.fail()) return;

    bool code = presenter_.loadGraph(path);

    if(code){
        std::cout << TextSettings::f_green << TextInfo::success << TextSettings::reset;
    }
    else{
        std::cout << TextSettings::f_red << TextInfo::fail << TextSettings::reset;
    }
}

void Cli::exportGraph() const{
    std::cout << TextInfo::g_format;

    std::cout << "Format: ";
    int format = this->userInput<int>();

    if(std::cin.fail() || !(format >= 0 && format < 2)) return;

    std::cout << "File: ";
    std::filesystem::path path = this->userInput<std::filesystem::path>();

    if(format == 0){
        presenter_.exportDirectedGraph(path);
    }
    else if(format == 1){
        presenter_.exportUndirectedGraph(path);
    }

    std::cout << TextSettings::f_green << TextInfo::success << TextSettings::reset;
}

void Cli::depthFirstSearch() const{
    std::cout << "Vertex: ";
    int start_vertex = this->userInput<int>();

    if(!std::cin.fail()){
        std::deque<unsigned int> code = presenter_.depthFirstSearch(start_vertex);

        std::cout << TextInfo::result;

        for(unsigned int i = 0; i < code.size() - 1; ++i){
            std::cout << code[i] << " -> ";
        }

        std::cout << code.back()  << std::endl;
    }
}

void Cli::breadthFirstSearch() const{
    std::cout << "Vertex: ";
    int start_vertex = this->userInput<int>();

    if(!std::cin.fail()){
        std::deque<unsigned int> code = presenter_.breadthFirstSearch(start_vertex);

        std::cout << TextInfo::result;

        for(unsigned int i = 0, size = code.size() - 1; i < size; ++i){
            std::cout << code[i] << " -> ";
        }

        std::cout << code.back() << "\n";   
    }
}

void Cli::dijkstraAlgorithm() const{
    std::cout << "Vertex 1: ";
    int begin = this->userInput<int>();

    std::cout << "Vertex 2: ";
    int end = this->userInput<int>();

    if(std::cin.fail()) return;

    int code = presenter_.dijkstraAlgorithm(begin, end);

    std::cout << TextInfo::result << code << "\n";
}

void Cli::floydWarshallAlgorighm() const{
    Matrix<int> matrix = presenter_.floydWarshallAlgorighm();

    std::cout << TextInfo::result;

    for(unsigned int i = 0, rows = matrix.rows(); i < rows; ++i){
        for(unsigned int j = 0, colls = matrix.columns(); j < colls; ++j){
            std::cout << matrix(i, j) << " ";
        }

        std::cout << "\n";
    }
}

void Cli::primAlgorithm() const{
    Matrix<int> matrix = presenter_.primAlgorithm();

    std::cout << TextInfo::result;

    for(unsigned int i = 0, rows = matrix.rows(); i < rows; ++i){
        for(unsigned int j = 0, colls = matrix.columns(); j < colls; ++j){
            std::cout << matrix(i, j) << " ";
        }

        std::cout << "\n";
    }
}

} // namespace s21s
