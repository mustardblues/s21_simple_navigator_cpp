#include <iostream>

#include "src/containers/priority_queue/priority_queue.hpp"

int main(void){
    s21::PriorityQueue<int> queue{8, 12, 5, 6, 11, 9, 1, 0};

    // std::cout << queue.size() << std::endl;

    for(unsigned int i = 0; i < 8; ++i){
        std::cout << queue.pop() << " ";
    }

    std::cout << std::endl;

    return 0;
}   