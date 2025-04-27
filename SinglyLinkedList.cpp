#include "SinglyLinkedList.h"

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr) {}

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
void SinglyLinkedList<T>::pop_back() {
    if (!head) return;
    if (!head->next) {
        head.reset();
        return;
    }
    auto temp = head;
    while (temp->next->next) temp = temp->next;
    temp->next.reset();
}

template<typename T>
T& SinglyLinkedList<T>::at(size_t index) {
    auto temp = head;
    for (size_t i = 0; temp && i < index; ++i) temp = temp->next;
    if (!temp) throw std::out_of_range("Index out of range");
    return temp->data;
}

template<typename T>
void SinglyLinkedList<T>::insert_at(size_t index, const T& value) {
    if (index == 0) {
        push_front(value);
        return;
    }
    auto temp = head;
    for (size_t i = 0; temp && i < index - 1; ++i) temp = temp->next;
    if (!temp) throw std::out_of_range("Index out of range");
    auto new_node = std::make_shared<Node<T>>(value);
    new_node->next = temp->next;
    temp->next = new_node;
}

template<typename T>
void SinglyLinkedList<T>::erase_at(size_t index) {
    if (index == 0) {
        pop_front();
        return;
    }
    auto temp = head;
    for (size_t i = 0; temp && i < index - 1; ++i) temp = temp->next;
    if (!temp || !temp->next) throw std::out_of_range("Index out of range");
    temp->next = temp->next->next;
}

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
bool SinglyLinkedList<T>::empty() const {
    return head == nullptr;
}

template<typename T>
bool SinglyLinkedList<T>::find(const T& value) const {
    auto temp = head;
    while (temp) {
        if (temp->data == value) return true;
        temp = temp->next;
    }
    return false;
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
