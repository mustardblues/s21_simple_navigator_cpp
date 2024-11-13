#include <iostream>

#include "src/algorithms/containers/stack/stack.hpp"

int main(void){

    s21::Stack<unsigned int> stack;

    for(unsigned int i = 0; i < 10; ++i){
        stack.push(i);
    }

    s21::Stack<unsigned int> stack_two(stack);

    std::cout << stack.size() << std::endl;

    std::cout << stack_two.size() << std::endl;

    return 0;
}