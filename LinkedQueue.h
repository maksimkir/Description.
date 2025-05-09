#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "SinglyLinkedList.h"

template<typename T>
class LinkedQueue {
private:
    SinglyLinkedList<T> list;

public:
    void enqueue(const T& value);
    void dequeue();
    T& peek();
    bool isEmpty() const;
    bool isFull() const;
    void print() const;

};

#include "LinkedQueue.cpp"
#endif