#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <memory>
#include <iostream>
#include <stdexcept>

template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev;
    Node(const T& value);
};

template<typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;

public:
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    T& at(size_t index);
    bool empty() const;
    size_t size() const;
    void print() const;
};

#include "SinglyLinkedList.cpp"
#endif
