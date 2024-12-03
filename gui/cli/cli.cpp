// Copyright 2024 stranger

#include "cli.hpp"

namespace s21{

void Cli::start() const{
    int input{};

    std::cout << TextInfo::creators;
    options_[0]();

    while(true){
        std::cout << "> ";
        std::cin >> input;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(std::cin.eof()) return;
        }
        else if(input >= 0 && input < 8){
            options_[input]();
        }
    }
}

void Cli::loadGraph(){
    std::filesystem::path path;

    std::cout << "Select file > ";

    std::cin >> path;

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
    int format{};

    std::cout << TextInfo::g_format << "Select format > ";

    std::cin >> format;

    if(std::cin.fail() || !(format >= 0 && format < 2)) return;

    std::filesystem::path path;

    std::cout << "Select file > ";

    std::cin >> path;

    bool code{};

    if(format == 0){
        code = presenter_.exportDirectedGraph(path);
    }
    else if(format == 1){
        code = presenter_.exportUndirectedGraph(path);
    }

    if(code){
        std::cout << TextSettings::f_green << TextInfo::success << TextSettings::reset;
    }
    else{
        std::cout << TextSettings::f_red << TextInfo::fail << TextSettings::reset;
    }
}

void Cli::depthFirstSearch() const{
    unsigned int start_vertex{};

    std::cout << "Select vertex > ";

    std::cin >> start_vertex;

    if(std::cin.fail()) return;

    std::deque<unsigned int> code = presenter_.depthFirstSearch(start_vertex);

    std::cout << TextInfo::result;

    for(unsigned int i = 0; i < code.size() - 1; ++i){
        std::cout << code[i] << " -> ";
    }

    std::cout << code.back()  << std::endl;
}

void Cli::breadthFirstSearch() const{
    unsigned int start_vertex{};

    std::cout << "Select vertex > ";

    std::cin >> start_vertex;

    if(std::cin.fail()) return;

    std::deque<unsigned int> code = presenter_.breadthFirstSearch(start_vertex);

    std::cout << TextInfo::result;

    for(unsigned int i = 0, size = code.size() - 1; i < size; ++i){
        std::cout << code[i] << " -> ";
    }

    std::cout << code.back() << "\n";
}

void Cli::dijkstraAlgorithm() const{
    unsigned int begin{}, end{};

    std::cout << "Select vertices > ";

    std::cin >> begin >> end;

    if(std::cin.fail()) return;

    int code = presenter_.dijkstraAlgorithm(begin, end);

    std::cout << TextInfo::result << code << "\n";
}

void Cli::floydWarshallAlgorighm() const{
    Matrix<int> matrix = presenter_.floydWarshallAlgorighm();

    if(matrix.capacity() == 0) return;

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

    if(matrix.capacity() == 0) return;

    std::cout << TextInfo::result;

    for(unsigned int i = 0, rows = matrix.rows(); i < rows; ++i){
        for(unsigned int j = 0, colls = matrix.columns(); j < colls; ++j){
            std::cout << matrix(i, j) << " ";
        }

        std::cout << "\n";
    }
}

} // namespace s21s
