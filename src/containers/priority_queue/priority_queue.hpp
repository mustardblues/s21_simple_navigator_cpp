// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_PRIORITY_QUEUE_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_PRIORITY_QUEUE_HPP_

#include "./../queue/queue.hpp"

namespace s21{

/**
 * @class PriorityQueue
 * @brief PriorityQueue is a container that orders values in ascending order.
 */
template <typename T>
class PriorityQueue final : public Queue<T>{
public:
    /**
     * @brief Creates an empty data queue.
     */
    PriorityQueue() : Queue<T>(){}

    /**
     * @brief List constructor. Sets the list values in a queue in order.
     * @param list std::initializar_list<T> data type.
     */
    PriorityQueue(const std::initializer_list<T>& list) : Queue<T>(){
        for(const auto value : list){
            this->push(value);
        }
    }

    /**
     * @brief Adds the value to the queue in order.
     */
    void push(const T& value) override{
        Node<T>* node = new Node<T>{};
        node->value_ = value;

        node->prev_ = nullptr;
        node->next_ = nullptr;

        if(Queue<T>::head_ == nullptr){
            Queue<T>::head_ = node;
            Queue<T>::tail_ = node;
        }
        else if(node->value_ <= Queue<T>::head_->value_){
            node->next_ = Queue<T>::head_;
            Queue<T>::head_->prev_ = node;
            Queue<T>::head_ = node;
        }
        else if(node->value_ >= Queue<T>::tail_->value_){
            node->prev_ = Queue<T>::tail_;
            Queue<T>::tail_->next_ = node;
            Queue<T>::tail_ = node;
        }
        else{
            for(Node<T>* ptr = Queue<T>::head_; ptr != nullptr;){
                if(node->value_ < ptr->value_){
                    node->prev_ = ptr->prev_;
                    node->next_ = ptr;
                    
                    ptr->prev_->next_ = node;
                    ptr->prev_ = node;

                    ptr = nullptr;
                }
                else{
                    ptr = ptr->next_;
                }
            }
        }

        ++Queue<T>::size_;
    }
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_PRIORITY_QUEUE_HPP_
