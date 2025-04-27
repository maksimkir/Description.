#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "Node.h"
#include <iostream>

template<typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;

public:
    DoublyLinkedList();

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    T& at(size_t index);
    void insert_at(size_t index, const T& value);
    void erase_at(size_t index);
    size_t size() const;
    bool empty() const;
    bool find(const T& value) const;
    void print() const;
};

#include "DoublyLinkedList.cpp"

#endif // DOUBLYLINKEDLIST_H
