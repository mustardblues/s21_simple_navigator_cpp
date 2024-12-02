// Copyright 2024 stranger

#include "cli.hpp"

namespace s21{

void Cli::start() const{
    int input;

    while(true){
        std::cout << Text::help << Font::endf;
        std::cout << "> ";

        std::cin >> input;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(std::cin.eof()) return;
        }
        else{
            options_[input]();
            std::cout << std::endl;
        }
    }
}

void Cli::loadGraph(){
    std::filesystem::path path;

    std::cout << Text::file_path << Font::endf;
    std::cout << Text::new_line;

    std::cin >> path;

    if(std::cin.fail()) return;

    bool code = presenter_.loadGraph(path);

    if(code){
        std::cout << Font::bold << Font::green << Text::success << Font::endf;
    }
    else{
        std::cout << Font::bold << Font::red << Text::error << Font::endf;
    }
}

void Cli::exportGraph() const{
    int format{};

    std::cout << Text::graph_format << Font::endf;
    std::cout << Text::new_line;

    std::cin >> format;

    if(std::cin.fail() || !(format > 0 && format < 3)) return;

    std::filesystem::path path;

    std::cout << Text::file_path << Font::endf;
    std::cout << Text::new_line;

    std::cin >> path;

    bool code{};

    if(format == static_cast<int>(GraphType::Directed)){
        code = presenter_.exportDirectedGraph(path);
    }
    else if(format == static_cast<int>(GraphType::Undirected)){
        code = presenter_.exportUndirectedGraph(path);
    }

    if(code){
        std::cout << Font::bold << Font::green << Text::success << Font::endf;
    }
    else{
        std::cout << Font::bold << Font::red << Text::error << Font::endf;
    }
}

void Cli::depthFirstSearch() const{
    unsigned int start_vertex{};

    std::cout << Text::specify_vertex << Font::endf;
    std::cout << Text::new_line;

    std::cin >> start_vertex;

    if(std::cin.fail()) return;

    std::deque<unsigned int> code = presenter_.depthFirstSearch(start_vertex);

    if(!code.empty()){
        std::cout << Font::bold << Font::blue << Text::output << Font::endf;

        for(unsigned int i = 0; i < code.size() - 1; ++i){
            std::cout << code[i] << " -> ";
        }

        std::cout << code.back()  << std::endl;
    }
    else{
        std::cout << Font::bold << Font::red << Text::error << Font::endf;
    }
}

void Cli::breadthFirstSearch() const{
    unsigned int start_vertex{};

    std::cout << Text::specify_vertex << Font::endf;
    std::cout << Text::new_line;

    std::cin >> start_vertex;

    if(std::cin.fail()) return;

    std::deque<unsigned int> code = presenter_.breadthFirstSearch(start_vertex);

    if(!code.empty()){
        std::cout << Font::bold << Font::blue << Text::output << Font::endf;

        for(unsigned int i = 0, size = code.size() - 1; i < size; ++i){
            std::cout << code[i] << " -> ";
        }

        std::cout << code.back() << "\n" << Font::endf;
    }
    else{
        std::cout << Font::bold << Font::red << Text::error << Font::endf;
    }
}

void Cli::dijkstraAlgorithm() const{
    unsigned int begin{}, end{};

    std::cout << Text::specify_vertex << Font::endf;
    std::cout << Text::new_line;

    std::cin >> begin >> end;

    if(std::cin.fail()) return;

    int code = presenter_.dijkstraAlgorithm(begin, end);

    std::cout << Font::bold << Font::blue << Text::output << Font::endf << code << "\n";
}


} // namespace s21s
