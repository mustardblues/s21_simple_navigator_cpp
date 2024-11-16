// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_HPP_

#include "./../node/node.hpp"

namespace s21{

/**
 * @class Stack
 * @brief Stack is a container that works according to LIFO rule.
 */
template <typename T>
class Stack final{
public:
    /**
     * @brief Creates an empty data stack.
     */
    Stack();

    /**
     * @brief List constructor. Sets the list values to the top of the stack.
     * @param list std::initializar_list<T> data type.
     */
    Stack(const std::initializer_list<T>& list);

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
