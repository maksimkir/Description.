#include <iostream>
#include <memory>

// Структура Node
template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev; // Для двозв'язного списку

    Node(const T& value) : data(value), next(nullptr), prev() {}
};

//однозв'язковий список
template<typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void push_front(const T& value) {
        auto new_node = std::make_shared<Node<T>>(value);
        new_node->next = head;
        head = new_node;
    }

    void push_back(const T& value) {
        auto new_node = std::make_shared<Node<T>>(value);
        if (!head) {
            head = new_node;
            return;
        }
        auto temp = head;
        while (temp->next) temp = temp->next;
        temp->next = new_node;
    }

    void pop_front() {
        if (head) head = head->next;
    }

    void pop_back() {
        if (!head) return;
        if (!head->next) {
            head.reset();
            return;
        }
        auto temp = head;
        while (temp->next->next) temp = temp->next;
        temp->next.reset();
    }

    T& at(size_t index) {
        auto temp = head;
        for (size_t i = 0; temp && i < index; ++i) temp = temp->next;
        if (!temp) throw std::out_of_range("Index out of range");
        return temp->data;
    }

    void insert_at(size_t index, const T& value) {
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

    void erase_at(size_t index) {
        if (index == 0) {
            pop_front();
            return;
        }
        auto temp = head;
        for (size_t i = 0; temp && i < index - 1; ++i) temp = temp->next;
        if (!temp || !temp->next) throw std::out_of_range("Index out of range");
        temp->next = temp->next->next;
    }

    size_t size() const {
        size_t count = 0;
        auto temp = head;
        while (temp) {
            ++count;
            temp = temp->next;
        }
        return count;
    }

    bool empty() const {
        return head == nullptr;
    }

    bool find(const T& value) const {
        auto temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }

    void print() const {
        auto temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

};

// Клас для двозв'язного списку
template<typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void push_front(const T& value) {
        auto new_node = std::make_shared<Node<T>>(value);
        if (!head) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }

    void push_back(const T& value) {
        auto new_node = std::make_shared<Node<T>>(value);
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }

    void pop_front() {
        if (!head) return;
        head = head->next;
        if (head) head->prev.reset();
        else tail.reset();
    }

    void pop_back() {
        if (!tail) return;
        if (tail->prev.expired()) {
            head.reset();
            tail.reset();
            return;
        }
        tail = tail->prev.lock();
        tail->next.reset();
    }

    T& at(size_t index) {
        auto temp = head;
        for (size_t i = 0; temp && i < index; ++i) temp = temp->next;
        if (!temp) throw std::out_of_range("Index out of range");
        return temp->data;
    }

    void insert_at(size_t index, const T& value) {
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

    void erase_at(size_t index) {
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

    size_t size() const {
        size_t count = 0;
        auto temp = head;
        while (temp) {
            ++count;
            temp = temp->next;
        }
        return count;
    }

    bool empty() const {
        return head == nullptr;
    }

    bool find(const T& value) const {
        auto temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }

    void print() const {
        auto temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    SinglyLinkedList<int> s_list;
    DoublyLinkedList<int> d_list;

    // Приклади використання
    s_list.push_back(1);
    s_list.push_back(2);
    s_list.push_front(0);
    s_list.print();

    d_list.push_back(10);
    d_list.push_front(5);
    d_list.insert_at(1, 7);
    d_list.print();

    return 0;
}
