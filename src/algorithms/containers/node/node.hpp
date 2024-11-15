// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_NODE_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_NODE_HPP_

namespace s21{

/**
 * @struct Node
 * @brief The structure used in Queue<T> and Stack<T> classes.
 */
template <typename T>
struct Node final{
    /**
     * @brief Stores some data.
     */
    T value_;

    /**
     * @brief Stores the pointer of the previous Node. Used in Queue<T> class.
     */
    Node* prev_;

    /**
     * @brief Stores the pointer of the next Node. 
     * Used in Queue<T> and Stack<T> classes.
     */
    Node* next_;
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_NODE_HPP_
