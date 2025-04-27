#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "Node.h"
#include <iostream>

template<typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;

public:
    SinglyLinkedList();

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

#include "SinglyLinkedList.cpp"

#endif // SINGLYLINKEDLIST_H
