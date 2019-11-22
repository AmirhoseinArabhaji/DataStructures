#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "exception.h"

class LinkedList {
public:
    class Node {
    public:
        Node(int const & = int(), Node * = nullptr);

        int value() const;
        Node *next() const;

        int node_value;
        Node *next_node;

    };

    LinkedList();

    LinkedList(LinkedList const &);

    ~LinkedList();

    //Accessors

    int size() const;

    int empty() const;

    int front() const;

    int back() const;

    Node *begin() const;

    Node *end() const;

    Node *find(int const &) const;

    int count(int const &) const;

    //Mutators

    int erase(int const &);

    void swap(LinkedList &);

    void push(int const &);

    void pop();

    void insertEnd(int const &);

    void insert_after(Node *);

    void print() const;

private:

    Node *head;
    Node *tail;
    int length;

};

LinkedList::Node::Node(int const &value, LinkedList::Node *nn) : node_value(value), next_node(nn) {

}

int LinkedList::Node::value() const {
    return node_value;
}

LinkedList::Node *LinkedList::Node::next() const {
    return next_node;
}


LinkedList::LinkedList() : length(0), head(nullptr), tail(nullptr) {

}

LinkedList::LinkedList(LinkedList const &list) {

    for (auto ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
        this->insertEnd(ptr->value());
    }

}

LinkedList::~LinkedList() {
    while (head != nullptr) {
        this->pop();
    }
}

int LinkedList::size() const {
    return length;
}

int LinkedList::empty() const {
    return head == nullptr && tail == nullptr;
}

int LinkedList::front() const {
    return head->value();
}

int LinkedList::back() const {
    return tail->value();
}

LinkedList::Node *LinkedList::begin() const {
    return head;
}

LinkedList::Node *LinkedList::end() const {
    return tail;
}

LinkedList::Node *LinkedList::find(int const &value) const {

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
        if (ptr->value() == value) {
            return ptr;
        }
    }

    return nullptr;
}

int LinkedList::count(int const &value) const {

    int counter = 0;

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
        if (ptr->value() == value) {
            counter++;
        }
    }

    return 0;
}

void LinkedList::swap(LinkedList &list) {

    Node *temp_head = this->head;
    Node *temp_tail = this->tail;
    int temp_size = this->length;

    this->head = list.head;
    this->tail = list.tail;
    this->length = list.length;

    list.head = temp_head;
    list.tail = temp_tail;
    list.length = temp_size;
}

void LinkedList::push(int const &value) {

    Node *newnode = new Node(value, head);

    if (empty()) {
        head = newnode;
        tail = newnode;
    } else {
        head = newnode;
    }

    length++;
}

void LinkedList::pop() {

    if (empty()) throw Underflow();

    Node *temp = head;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = temp->next();
    }

    delete temp;
    length--;

}

void LinkedList::insertEnd(int const &value) {

    Node *newnode = new Node(value, nullptr);

    if (empty()) {
        head = newnode;
        tail = newnode;
    } else {
        tail->next_node = newnode;
        tail = newnode;
    }
}

int LinkedList::erase(int const &value) {

    if (empty()) throw Underflow();
    int counter = 0;

    Node *itr = head;
    Node *before = new Node(0, head);

    while (itr != nullptr) {
        if (itr->value() == value) {
            Node *temp = itr;

            if (temp == head) {
                if (head == tail) tail = nullptr;
                head = temp->next();
                before->next_node = temp->next();
                itr = itr->next();
            } else if (temp == tail) {
                tail = before;
                tail->next_node = nullptr;
                itr = nullptr;
            } else {
                before->next_node = itr->next();
                before = itr;
                itr = itr->next();
            }

            delete temp;
            length--;
            counter++;
        } else {
            before = itr;
            itr = itr->next();
        }
    }

    if (before->next() == head) {
        delete before;
    }
    return counter;
}

void LinkedList::print() const {
    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
        std::cout << ptr->value() << " --> ";
    }
    std::cout << "nullptr" << std::endl;
}


#endif //LINKED_LIST_LINKED_LIST_H
