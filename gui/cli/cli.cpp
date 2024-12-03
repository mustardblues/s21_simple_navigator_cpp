// Copyright 2024 stranger

#include "cli.hpp"

namespace s21{

void Cli::start() const{
    std::cout << TextSettings::f_green << TextInfo::title << TextSettings::reset;
    std::cout << TextInfo::menu;

    for(int index{}; index != -1; ){
        std::cout << "~ ";
        index = this->userInput<int>();

        if(index >= 0 && index < 8){
            if(presenter_.graph_.vertices() != 0){
                options_[index]();
            }
            else if(index < 2){
                options_[index]();
            }
            else{
                std::cout << TextSettings::f_red << "[Fail]\n\n" << TextSettings::reset;
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

    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(std::cin.eof()) exit(1);
    }
    else{
        stream >> code;
    }

    return code;
}

void Cli::loadGraph(){
    std::cout << "Enter file name:\n" << "~ ";

    std::filesystem::path path = this->userInput<std::filesystem::path>();

    if(presenter_.loadGraph(path)){
        std::cout << TextSettings::f_green << "[Ok]\n\n" << TextSettings::reset;
    }
    else{
        std::cout << TextSettings::f_red << "[Fail]\n\n" << TextSettings::reset;
    }
}

void Cli::exportGraph() const{
    std::cout << "Enter file name:\n" << "~ ";
    std::filesystem::path path = this->userInput<std::filesystem::path>();

    std::cout << "Directed format? 0 (false) 1 (true):\n" << "~ ";
    int format = this->userInput<int>();

    if(format < 0 || format > 1){
        std::cout << TextSettings::f_red << "[Fail]\n\n" << TextSettings::reset;

        return;
    }

    if(format == 0){
        presenter_.exportUndirectedGraph(path);
    }
    else if(format == 1){
        presenter_.exportDirectedGraph(path);
    }

    std::cout << TextSettings::f_green << "[Ok]\n\n" << TextSettings::reset;
}

void Cli::depthFirstSearch() const{
    std::cout << "Select vertex:\n" << "~ ";
    int start_vertex = this->userInput<int>();

    std::deque<unsigned int> dist = presenter_.depthFirstSearch(start_vertex);

    for(unsigned int i = 0; i < dist.size() - 1; ++i){
        std::cout << dist[i] << " -> ";
    }

    std::cout << dist.back()  << std::endl;

    std::cout << TextSettings::f_green << "[Ok]\n\n" << TextSettings::reset;
}

void Cli::breadthFirstSearch() const{
    std::cout << "Select vertex:\n" << "~ ";
    int start_vertex = this->userInput<int>();

    std::deque<unsigned int> dist = presenter_.breadthFirstSearch(start_vertex);

    for(unsigned int i = 0, size = dist.size() - 1; i < size; ++i){
        std::cout << dist[i] << " -> ";
    }

    std::cout << dist.back() << "\n";   

    std::cout << TextSettings::f_green << "[Ok]\n\n" << TextSettings::reset;
}

void Cli::dijkstraAlgorithm() const{
    std::cout << "Select first vertex:\n" << "~ ";
    int begin = this->userInput<int>();

    std::cout << "Select second vertex:\n" << "~ ";
    int end = this->userInput<int>();

    std::cout << presenter_.dijkstraAlgorithm(begin, end) << "\n";

    std::cout << TextSettings::f_green << "[Ok]\n\n" << TextSettings::reset;
}

void Cli::floydWarshallAlgorighm() const{
    this->printMatrix(presenter_.floydWarshallAlgorighm());

    std::cout << TextSettings::f_green << "[Ok]\n\n" << TextSettings::reset;
}

void Cli::primAlgorithm() const{
    this->printMatrix(presenter_.primAlgorithm());

    std::cout << TextSettings::f_green << "[Ok]\n\n" << TextSettings::reset;
}

void Cli::printMatrix(const Matrix<int>& matrix) const{
    const unsigned int size = matrix.rows();

    std::vector<unsigned int> offset(size, false);

    auto number_of_digits = [](const int number){
        std::ostringstream stream;
        stream << number;
        return stream.str().size();
    };

    for(unsigned int i = 0; i < size; ++i){
        unsigned int max{};

        for(unsigned int j = 0; j < size; ++j){
            unsigned int current = number_of_digits(matrix(i, j));

            if(current > max) max = current;
        }

        offset[i] = max;
    }

    for(unsigned int i = 0; i < size; ++i){
        for(unsigned int j = 0; j < size; ++j){
            std::cout << (j == 0 ? "| " : "");
            std::cout << std::setw(offset[j]) << matrix(i, j);
            std::cout << (j == size - 1 ? " |\n" : " ");
        }
    }
}

} // namespace s21
