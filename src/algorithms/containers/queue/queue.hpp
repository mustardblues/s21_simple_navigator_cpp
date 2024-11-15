// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_QUEUE_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_QUEUE_HPP_

#include "./../node/node.hpp"

namespace s21{

/**
 * @class Queue
 * @brief Queue is a container that works according to FIFO rule.
 * 
 * @details Queue is a container with elements organized according to 
 * FIFO (First-In, First-Out) principle. Just like a list, an object 
 * of the queue container class has pointers to the "tail" and "head" 
 * of the queue, but the deletion is performed strictly from the "head", 
 * and the addition of new elements is performed strictly in the "tail". 
 * It is convenient to think of a queue as a kind of pipe, with elements 
 * entering at one end and exiting at another one.
 */
template <typename T>
class Queue final{
public:
    /**
     * @brief Default constructor. Creates an empty data queue.
     */
    Queue();

    Queue(const Queue& other) = delete;
    Queue(Queue&& other) noexcept = delete;

    /**
     * @brief Destructor. Clears all queue data.
     */
    ~Queue();

    Queue& operator = (const Queue& other) = delete;
    Queue& operator = (Queue&& other) = delete;

    /**
     * @brief Provides information about queue's fullness.
     * @return 0 if the queue is fill and 1 if the queue is empty.
     */
    bool empty() const { return size_ != 0 ? false : true; }

    /**
     * @brief Accesses to queue size.
     */
    std::size_t size() const { return size_; }

    /**
     * @brief Accesses the value from the beginning of the queue.
     */
    T front() const { return head_->value_; }

    /**
     * @brief Accesses the value from the end of the queue.
     */
    T back() const { return tail_->value_; }

    /**
     * @brief Adds a value to the beginning of the queue.
     */
    void push(const T& value);

    /**
     * @brief Deletes value from the beginning of the queue.
     * @return The deleted value from tshe beginning of the queue.
     */
    T pop();

    /**
     * @brief Clears the queue.
     */
    void clear();

private:
    std::size_t size_;

    Node<T>* head_;
    Node<T>* tail_;
};

} // namespace s21

#include "queue.tpp"

#endif // _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_QUEUE_HPP_
