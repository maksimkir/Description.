#ifndef NODE_H
#define NODE_H

#include <memory>

template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev; // для двозв'язного списку

    Node(const T& value) : data(value), next(nullptr), prev() {}
};

#endif // NODE_H
