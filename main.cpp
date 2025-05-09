#include <iostream>
#include <memory>
#include <stdexcept>

// Node структура
template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev;
    Node(const T& value) : data(value), next(nullptr), prev() {}
};

//  Однозв'язний список
template<typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;

public:
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

    T& at(size_t index) {
        auto temp = head;
        for (size_t i = 0; temp && i < index; ++i) temp = temp->next;
        if (!temp) throw std::out_of_range("Index out of range");
        return temp->data;
    }

    bool empty() const { return head == nullptr; }

    size_t size() const {
        size_t count = 0;
        auto temp = head;
        while (temp) {
            ++count;
            temp = temp->next;
        }
        return count;
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

//  Двозв'язний список
template<typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<Node<T>> head, tail;

public:
    void push_front(const T& value) {
        auto new_node = std::make_shared<Node<T>>(value);
        if (!head) head = tail = new_node;
        else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }

    void push_back(const T& value) {
        auto new_node = std::make_shared<Node<T>>(value);
        if (!tail) head = tail = new_node;
        else {
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

    T& at(size_t index) {
        auto temp = head;
        for (size_t i = 0; temp && i < index; ++i) temp = temp->next;
        if (!temp) throw std::out_of_range("Index out of range");
        return temp->data;
    }

    const T& at(size_t index) const {
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

    bool empty() const { return head == nullptr; }

    size_t size() const {
        size_t count = 0;
        auto temp = head;
        while (temp) {
            ++count;
            temp = temp->next;
        }
        return count;
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

// Черга на однозв’язному списку
template<typename T>
class LinkedQueue {
private:
    SinglyLinkedList<T> list;

public:
    void enqueue(const T& value) { list.push_back(value); }
    void dequeue() { list.pop_front(); }
    T& peek() { return list.at(0); }
    bool isEmpty() const { return list.empty(); }
    bool isFull() const { return false; }
    void print() const { list.print(); }
};

// Стек на двозв’язному списку
template<typename T>
class LinkedStack {
private:
    DoublyLinkedList<T> list;

public:
    void push(const T& value) { list.push_front(value); }
    void pop() { list.pop_front(); }
    T& peek() { return list.at(0); }
    bool isEmpty() const { return list.empty(); }
    bool isFull() const { return false; }
    void print() const { list.print(); }
};

// Пріоритетна черга
template<typename T>
class PriorityQueue {
private:
    DoublyLinkedList<std::pair<int, T>> list;

public:
    void enqueue(const T& value, int priority) {
        size_t index = 0;
        while (index < list.size() && list.at(index).first <= priority) ++index;
        list.insert_at(index, {priority, value});
    }

    void dequeue() { list.pop_front(); }
    T& peek() { return list.at(0).second; }
    bool isEmpty() const { return list.empty(); }
    bool isFull() const { return false; }

    void print() const {
        for (size_t i = 0; i < list.size(); ++i)
            std::cout << "[" << list.at(i).first << "] " << list.at(i).second << " ";
        std::cout << std::endl;
    }
};

// Черга на масиві
template<typename T, size_t SIZE>
class ArrayQueue {
private:
    T data[SIZE];
    size_t front = 0, rear = 0, count = 0;

public:
    void enqueue(const T& value) {
        if (isFull()) throw std::runtime_error("Queue is full");
        data[rear] = value;
        rear = (rear + 1) % SIZE;
        ++count;
    }

    void dequeue() {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        front = (front + 1) % SIZE;
        --count;
    }

    T& peek() {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        return data[front];
    }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == SIZE; }

    void print() const {
        for (size_t i = 0, idx = front; i < count; ++i, idx = (idx + 1) % SIZE)
            std::cout << data[idx] << " ";
        std::cout << std::endl;
    }
};

//  Стек на масиві
template<typename T, size_t SIZE>
class ArrayStack {
private:
    T data[SIZE];
    int top = -1;

public:
    void push(const T& value) {
        if (isFull()) throw std::runtime_error("Stack is full");
        data[++top] = value;
    }

    void pop() {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        --top;
    }

    T& peek() {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        return data[top];
    }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == SIZE - 1; }

    void print() const {
        for (int i = 0; i <= top; ++i) std::cout << data[i] << " ";
        std::cout << std::endl;
    }
};


int main() {
    LinkedQueue<int> lq;
    lq.enqueue(1); lq.enqueue(2); lq.enqueue(3);
    std::cout << "LinkedQueue: "; lq.print();

    LinkedStack<int> ls;
    ls.push(10); ls.push(20); ls.pop();
    std::cout << "LinkedStack: "; ls.print();

    PriorityQueue<std::string> pq;
    pq.enqueue("low", 5);
    pq.enqueue("high", 1);
    pq.enqueue("medium", 3);
    std::cout << "PriorityQueue: "; pq.print();

    ArrayQueue<int, 5> aq;
    aq.enqueue(7); aq.enqueue(8); aq.dequeue();
    std::cout << "ArrayQueue: "; aq.print();

    ArrayStack<char, 5> as;
    as.push('A'); as.push('B'); as.pop();
    std::cout << "ArrayStack: "; as.print();

    return 0;
}
