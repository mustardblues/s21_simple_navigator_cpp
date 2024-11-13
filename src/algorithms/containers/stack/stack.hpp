// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_HPP_

namespace s21{

template <typename T>
class Stack final{
public:
    using value_type = T;

    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack();

    /**
     * @brief Copying assignment operator.
     * @param other Graph reference parameter.
     */
    Stack& operator = (const Stack& other);

    /**
     * @brief Rvalue assignment operator.
     * @param other Rvalue parameter.
     */
    Stack& operator = (Stack&& other);

    /**
     * @brief Give information about stack's fullness.
     * @return 0 if the stack is fill and 1 if the stack is empty.
     */
    bool empty() const { return node_ != nullptr ? false : true; }

    /**
     * @brief Access to the top of the stack.
     */
    value_type top() const { 
        return node_ != nullptr ? node_->value_ : value_type{}; 
    }

    /**
     * @brief Access to stack size.
     */
    std::size_t size() const { return size_; }

    /**
     * @brief Add a value to the top of the stack.
     */
    void push(const value_type& value);

    /**
     * @brief Delete the top of the stack.
     */
    void pop();

    /**
     * @brief Clean up the stack.
     */
    void clear();

private:
    struct Node final{
        value_type value_;
        struct Node* next_;
    };

    std::size_t size_;

    Node* node_;

};

} // namespace s21

#include "stack.tpp"

#endif // _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_HPP_
