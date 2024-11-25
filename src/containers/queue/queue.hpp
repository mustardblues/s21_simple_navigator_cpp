// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_QUEUE_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_QUEUE_HPP_

#include "./../node/node.hpp"

namespace s21{

/**
 * @class Queue
 * @brief Queue is a container that works according to FIFO rule.
 */
template <typename T>
class Queue{
public:
    /**
     * @brief Creates an empty data queue.
     */
    Queue();

    /**
     * @brief List constructor. Sets the list values into a queue.
     * @param list std::initializar_list<T> data type.
     */
    Queue(const std::initializer_list<T>& list); 

    Queue(const Queue& other) = delete;
    Queue(Queue&& other) noexcept = delete;

    /**
     * @brief Destructor. Clears all queue data.
     */
    virtual ~Queue();

    Queue& operator = (const Queue& other) = delete;
    Queue& operator = (Queue&& other) = delete;

    /**
     * @brief Provides information about queue's fullness.
     * @return 0 if the queue is fill and 1 if the queue is empty.
     */
    bool empty() const { return size_ == 0; }

    /**
     * @brief Accesses to queue size.
     */
    std::size_t size() const { return size_; }

    /**
     * @brief Accesses the value from the beginning of the queue.
     */
    T front() const { return head_ != nullptr ? head_->value_ : 0; }

    /**
     * @brief Accesses the value from the end of the queue.
     */
    T back() const { return tail_ != nullptr ? tail_->value_ : 0; }

    /**
     * @brief Adds a value to the beginning of the queue.
     */
    virtual void push(const T& value);

    /**
     * @brief Deletes value from the beginning of the queue.
     * @return The deleted value from tshe beginning of the queue.
     */
    T pop();

    /**
     * @brief Clears the queue.
     */
    void clear();

protected:
    std::size_t size_;

    Node<T>* head_;
    Node<T>* tail_;
};

} // namespace s21

#include "queue.tpp"

#endif // _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_QUEUE_HPP_
