// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_QUEUE_TPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_QUEUE_TPP_

namespace s21{

template <typename T>
Queue<T>::Queue() : size_(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
Queue<T>::~Queue(){
    if(size_ == 0) return;

    while(tail_ != nullptr){
        Node<T>* node = tail_;

        tail_ = tail_->next_;

        delete node;
    }

    size_ = 0;
}

template <typename T>
void Queue<T>::push(const T& value){
    Node<T>* node = new Node<T>{};

    node->value_ = value;

    if(head_ == nullptr){
        node->prev_ = nullptr;
        node->next_ = nullptr;

        head_ = node;
        tail_ = node;
    }
    else{
        tail_->next_ = node;

        node->prev_ = tail_;

        tail_ = node;
    }

    ++size_;
}

template <typename T>
T Queue<T>::pop(){
    if(head_ == nullptr) { return T{}; }

    T value = head_->value_;

    Node<T>* node = head_;

    head_ = node->next_;

    delete node;

    --size_;

    return value;
}

template <typename T>
void Queue<T>::clear(){ this->~Stack(); }

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_QUEUE_TPP_
