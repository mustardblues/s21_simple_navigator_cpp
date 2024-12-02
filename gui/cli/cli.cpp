// Copyright 2024 stranger

#include "cli.hpp"

namespace s21{

void Cli::start() const{
    int input{};

    options_[0]();

    while(true){
        std::cout << Text::select;
        std::cin >> input;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(std::cin.eof()) return;
        }
        else{
            options_[input]();
        }
    }
}

void Cli::loadGraph(){
    std::filesystem::path path;

    std::cout << Text::file;

    std::cin >> path;

    if(std::cin.fail()) return;

    bool code = presenter_.loadGraph(path);

    if(code){
        std::cout << Text::ok;
    }
    else{
        std::cout << Text::fail;
    }
}

void Cli::exportGraph() const{
    int format{};

    std::cout << Text::format << Text::select;

    std::cin >> format;

    if(std::cin.fail() || !(format >= 0 && format < 2)) return;

    std::filesystem::path path;

    std::cout << Text::file;

    std::cin >> path;

    bool code{};

    if(format == static_cast<int>(GraphType::Directed)){
        code = presenter_.exportDirectedGraph(path);
    }
    else if(format == static_cast<int>(GraphType::Undirected)){
        code = presenter_.exportUndirectedGraph(path);
    }

    if(code){
        std::cout << Text::ok;
    }
    else{
        std::cout << Text::fail;
    }
}

void Cli::depthFirstSearch() const{
    unsigned int start_vertex{};

    std::cout << Text::vertices;

    std::cin >> start_vertex;

    if(std::cin.fail()) return;

    std::deque<unsigned int> code = presenter_.depthFirstSearch(start_vertex);

    if(!code.empty()){
        for(unsigned int i = 0; i < code.size() - 1; ++i){
            std::cout << code[i] << " -> ";
        }

        std::cout << code.back()  << std::endl;
    }
    else{
        std::cout << Text::fail;
    }
}

void Cli::breadthFirstSearch() const{
    unsigned int start_vertex{};

    std::cout << Text::vertices;

    std::cin >> start_vertex;

    if(std::cin.fail()) return;

    std::deque<unsigned int> code = presenter_.breadthFirstSearch(start_vertex);

    if(!code.empty()){
        for(unsigned int i = 0, size = code.size() - 1; i < size; ++i){
            std::cout << code[i] << " -> ";
        }

        std::cout << code.back() << "\n";
    }
    else{
        std::cout << Text::fail;
    }
}

void Cli::dijkstraAlgorithm() const{
    unsigned int begin{}, end{};

    std::cout << Text::vertices;

    std::cin >> begin >> end;

    if(std::cin.fail()) return;

    int code = presenter_.dijkstraAlgorithm(begin, end);

    std::cout << code << "\n";
}


} // namespace s21s
