// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_TPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_TPP_

namespace s21{

template <typename T>
Stack<T>::Stack() : size_(0), node_(nullptr) {}

template <typename T>
Stack<T>::Stack(const Stack& other) : Stack(){
    *this = other;
}

template <typename T>
Stack<T>::Stack(Stack&& other) noexcept{
    *this = std::move(other);
}

template <typename T>
Stack<T>::~Stack(){
    if(node_ == nullptr) return;

    while(node_ != nullptr){
        struct Node* current_node = node_;

        node_ = node_->next_;

        delete current_node;
    }

    size_ = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator = (const Stack& other){
    if(this == &other) return *this;

    struct Node* temp = other.node_;

    value_type* list = new value_type[other.size_]{};

    for(unsigned int i = 0; i < other.size_; ++i){
        list[i] = temp->value_;

        temp = temp->next_;
    }

    for(unsigned int i = 0; i < other.size_; ++i){
        this->push(list[i]);
    }

    delete[] list;

    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator = (Stack&& other){
    if(this == &other) return *this;

    std::swap(size_, other.size_);
    std::swap(node_, other.node_);

    other.size_ = 0;
    other.node_ = nullptr;

    return *this;
}

template <typename T>
void Stack<T>::push(const value_type& value){
    struct Node* new_node = new Node{};

    new_node->value_ = value;
    new_node->next_ = node_;

    node_ = new_node;

    ++size_;
}

template <typename T>
void Stack<T>::pop(){
    if(node_ == nullptr) return;

    struct Node* current_node = node_;

    node_ = node_->next_;

    delete current_node;

    --size_;
}

template <typename T>
void Stack<T>::clear(){
    this->~Stack();
}

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_CONTAINERS_STACK_TPP_
