#include "DoublyLinkedList.h"

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

template<typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    auto new_node = std::make_shared<Node<T>>(value);
    if (!head) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    auto new_node = std::make_shared<Node<T>>(value);
    if (!tail) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (!head) return;
    head = head->next;
    if (head) head->prev.reset();
    else tail.reset();
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (!tail) return;
    if (tail->prev.expired()) {
        head.reset();
        tail.reset();
        return;
    }
    tail = tail->prev.lock();
    tail->next.reset();
}

template<typename T>
T& DoublyLinkedList<T>::at(size_t index) {
    auto temp = head;
    for (size_t i = 0; temp && i < index; ++i) temp = temp->next;
    if (!temp) throw std::out_of_range("Index out of range");
    return temp->data;
}

template<typename T>
void DoublyLinkedList<T>::insert_at(size_t index, const T& value) {
    if (index == 0) {
        push_front(value);
        return;
    }
    auto temp = head;
    for (size_t i = 0; temp && i < index - 1; ++i) temp = temp->next;
    if (!temp) throw std::out_of_range("Index out of range");
    auto new_node = std::make_shared<Node<T>>(value);
    new_node->next = temp->next;
    if (temp->next) temp->next->prev = new_node;
    new_node->prev = temp;
    temp->next = new_node;
    if (!new_node->next) tail = new_node;
}

template<typename T>
void DoublyLinkedList<T>::erase_at(size_t index) {
    if (index == 0) {
        pop_front();
        return;
    }
    auto temp = head;
    for (size_t i = 0; temp && i < index; ++i) temp = temp->next;
    if (!temp) throw std::out_of_range("Index out of range");
    auto prev_node = temp->prev.lock();
    if (prev_node) prev_node->next = temp->next;
    if (temp->next) temp->next->prev = prev_node;
    if (!temp->next) tail = prev_node;
}

template<typename T>
size_t DoublyLinkedList<T>::size() const {
    size_t count = 0;
    auto temp = head;
    while (temp) {
        ++count;
        temp = temp->next;
    }
    return count;
}

template<typename T>
bool DoublyLinkedList<T>::empty() const {
    return head == nullptr;
}

template<typename T>
bool DoublyLinkedList<T>::find(const T& value) const {
    auto temp = head;
    while (temp) {
        if (temp->data == value) return true;
        temp = temp->next;
    }
    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const {
    auto temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}
