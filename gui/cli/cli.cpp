// Copyright 2024 stranger

#include "cli.hpp"

namespace s21{

void Cli::start() const{
    std::cout << text_[2] << text_[3];

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
                std::cout << text_[1] << "\n";
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
    std::cout << text_[4] << "~ ";

    std::filesystem::path path = this->userInput<std::filesystem::path>();

    if(presenter_.loadGraph(path)){
        std::cout << text_[0] << "\n";
    }
    else{
        std::cout << text_[1] << "\n";
    }
}

void Cli::exportGraph() const{
    std::cout << text_[4] << "~ ";
    std::filesystem::path path = this->userInput<std::filesystem::path>();

    std::cout << text_[5] << "~ ";
    int format = this->userInput<int>();

    if(format == 0){
        presenter_.exportUndirectedGraph(path);

        std::cout << text_[0] << "\n";
    }
    else if(format == 1){
        presenter_.exportDirectedGraph(path);

        std::cout << text_[0] << "\n";
    }
    else{
        std::cout << text_[1] << "\n";
    }
}

void Cli::depthFirstSearch() const{
    std::cout << text_[6] << "~ ";
    int start_vertex = this->userInput<int>();

    std::deque<unsigned int> dist = presenter_.depthFirstSearch(start_vertex);

    if(dist.size() == 0){
        std::cout << text_[1] << "\n";

        return;
    }

    for(unsigned int i = 0, size = dist.size() - 1; i < size; ++i){
        std::cout << dist[i] << " -> ";
    }

    std::cout << dist.back() << std::endl;

    std::cout << text_[0] << "\n";
}

void Cli::breadthFirstSearch() const{
    std::cout << text_[6] << "~ ";
    int start_vertex = this->userInput<int>();

    std::deque<unsigned int> dist = presenter_.breadthFirstSearch(start_vertex);

    if(dist.size() == 0){
        std::cout << text_[1] << "\n";

        return;
    }

    for(unsigned int i = 0, size = dist.size() - 1; i < size; ++i){
        std::cout << dist[i] << " -> ";
    }

    std::cout << dist.back() << "\n";   

    std::cout << text_[0] << "\n";
}

void Cli::dijkstraAlgorithm() const{
    std::cout << text_[6] << "~ ";
    int begin = this->userInput<int>();

    std::cout << text_[7] << "~ ";
    int end = this->userInput<int>();

    if(begin < 0 || end < 0){
        std::cout << text_[1] << "\n";

        return;
    }

    std::cout << presenter_.dijkstraAlgorithm(begin, end) << "\n";

    std::cout << text_[0] << "\n";
}

void Cli::floydWarshallAlgorighm() const{
    this->printMatrix(presenter_.floydWarshallAlgorighm());

    std::cout << text_[0] << "\n";
}

void Cli::primAlgorithm() const{
    std::cout << text_[6] << "~ ";
    int start_vertex = this->userInput<int>();

    if(start_vertex < 0){
        std::cout << text_[1] << "\n";

        return;
    }

    this->printMatrix(presenter_.primAlgorithm(start_vertex));

    std::cout << text_[0] << "\n";
}

void Cli::printMatrix(const Matrix<int>& matrix) const{
    const unsigned int size = matrix.rows();

    std::vector<unsigned int> offset(size, false);

    auto number_of_digits = [](const int number){
        if(number == static_cast<int>(Constants::inf)) return 3;

        std::ostringstream stream;
        stream << number;
        return static_cast<int>(stream.str().size());
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
            std::cout << std::setw(offset[j]);

            if(matrix(i, j) != static_cast<int>(Constants::inf)){
                std::cout << matrix(i, j);
            }
            else{
                std::cout << "inf";
            }

            std::cout << (j == size - 1 ? "\n" : " ");
        }
    }
}

} // namespace s21
