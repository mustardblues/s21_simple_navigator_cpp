// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_TPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_TPP_

namespace s21{

template <typename T>
Stack<T>::Stack() : size_(0), node_(nullptr) {}

template <typename T>
Stack<T>::~Stack(){
    if(node_ == nullptr) return;

    while(node_ != nullptr){
        Node<T>* current = node_;

        node_ = node_->next_;

        delete current;
    }

    size_ = 0;
}

template <typename T>
void Stack<T>::push(const T& value){
    Node<T>* top = new Node<T>{};

    top->value_ = value;
    top->next_ = node_;

    node_ = top;

    ++size_;
}

template <typename T>
T Stack<T>::pop(){
    if(node_ == nullptr) return 0;

    T value = node_->value_;

    Node<T>* next = node_->next_;

    delete node_;

    node_ = next;

    --size_;

    return value;
}

template <typename T>
void Stack<T>::clear(){ this->~Stack(); }

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_TPP_
