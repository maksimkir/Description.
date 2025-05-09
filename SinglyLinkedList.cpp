#ifndef SINGLY_LINKED_LIST_CPP
#define SINGLY_LINKED_LIST_CPP

#include "SinglyLinkedList.h"

template<typename T>
Node<T>::Node(const T& value) : data(value), next(nullptr), prev() {}

template<typename T>
void SinglyLinkedList<T>::push_front(const T& value) {
    auto new_node = std::make_shared<Node<T>>(value);
    new_node->next = head;
    head = new_node;
}

template<typename T>
void SinglyLinkedList<T>::push_back(const T& value) {
    auto new_node = std::make_shared<Node<T>>(value);
    if (!head) {
        head = new_node;
        return;
    }
    auto temp = head;
    while (temp->next) temp = temp->next;
    temp->next = new_node;
}

template<typename T>
void SinglyLinkedList<T>::pop_front() {
    if (head) head = head->next;
}

template<typename T>
T& SinglyLinkedList<T>::at(size_t index) {
    auto temp = head;
    for (size_t i = 0; temp && i < index; ++i) temp = temp->next;
    if (!temp) throw std::out_of_range("Index out of range");
    return temp->data;
}

template<typename T>
bool SinglyLinkedList<T>::empty() const { return head == nullptr; }

template<typename T>
size_t SinglyLinkedList<T>::size() const {
    size_t count = 0;
    auto temp = head;
    while (temp) {
        ++count;
        temp = temp->next;
    }
    return count;
}

template<typename T>
void SinglyLinkedList<T>::print() const {
    auto temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

#endif
