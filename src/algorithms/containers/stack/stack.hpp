// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_HPP_

#include "./../node/node.hpp"

namespace s21{

/**
 * @class Stack
 * @brief Stack is a container that works according to LIFO rule.
 * 
 * @details Stack is a container with elements organized according to 
 * LIFO (Last-In, First-Out) principle. A stack container class object 
 * contains pointers to the "head" of the stack; removing and adding elements 
 * is done strictly from the "head". You can think of the stack as a glass or 
 * a pipe with one sealed end: in order to get to the element placed in the container 
 * first, you must take out all the elements on top.
 */
template <typename T>
class Stack final{
public:
    /**
     * @brief Default constructor. Creates an empty data stack.
     */
    Stack();

    Stack(const Stack& other) = delete;
    Stack(Stack&& other) noexcept = delete;

    /**
     * @brief Destructor. Clears all stack data.
     */
    ~Stack();

    Stack& operator = (const Stack& other) = delete;
    Stack& operator = (Stack&& other) = delete;

    /**
     * @brief Gives information about stack's fullness.
     * @return 0 if the stack is fill and 1 if the stack is empty.
     */
    bool empty() const { return node_ != nullptr ? false : true; }

    /**
     * @brief Accesses to the top of the stack.
     */
    T top() const { return node_ != nullptr ? node_->value_ : T{}; }

    /**
     * @brief Accesses to stack size.
     */
    std::size_t size() const { return size_; }

    /**
     * @brief Adds a value to the top of the stack.
     */
    void push(const T& value);

    /**
     * @brief Deletes the top of the stack.
     * @return The value of the top of the deleted stack.
     */
    T pop();

    /**
     * @brief Clears the stack.
     */
    void clear();

private:
    std::size_t size_;

    Node<T>* node_;
};

} // namespace s21

#include "stack.tpp"

#endif // _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_HPP_
