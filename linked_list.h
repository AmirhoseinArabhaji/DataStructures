#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "exception.h"

class LinkedList {
public:
    class Node {
    public:
        Node(int const & = int(), Node * = nullptr);

        int value() const;
        Node *next() const;

        int nodeValue;
        Node *nextNode;

    };

    LinkedList();
    LinkedList(LinkedList const &list);
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
    void print() const;

private:

    Node *head;
    Node *tail;
    int length;

    friend std::ostream &operator<<(std::ostream &, LinkedList const &);

};

/**
 * constructor for creating a node
 * @param value nodeValue
 * @param nn nextNode
 */

LinkedList::Node::Node(int const &value, LinkedList::Node *nn) : nodeValue(value), nextNode(nn) {

}

/**
 * @return node value
 */

int LinkedList::Node::value() const {
    return nodeValue;
}

/**
 * @return next node address
 */

LinkedList::Node *LinkedList::Node::next() const {
    return nextNode;
}

/**
 * constructor for creating a linked list
 */

LinkedList::LinkedList() : length(0), head(nullptr), tail(nullptr) {

}

/**
 * this constructor receives a linked list and copis all of its elements to itself
 * @param list
 */

LinkedList::LinkedList(LinkedList const &list) {

    for (auto ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
        this->insertEnd(ptr->value());
    }

}

/**
 * delete every element in linked list by pop function when destructor called
 */

LinkedList::~LinkedList() {
    while (head != nullptr) {
        this->pop();
    }
}

/**
 * @return size of linked list
 */

int LinkedList::size() const {
    return length;
}

/**
 * @return true if linked list is empty
 */

int LinkedList::empty() const {
    return head == nullptr && tail == nullptr;
}

/**
 * @throw Underflow exception if list is empty
 * @return value of head
 */

int LinkedList::front() const {
    if (empty()) throw Underflow();
    return head->value();
}

/**
 * @throw Underflow exception if list is empty
 * @return value of tail
 */

int LinkedList::back() const {
    if (empty()) throw Underflow();
    return tail->value();
}

/**
 * @return the beginning (head) address of linkedList
 */

LinkedList::Node *LinkedList::begin() const {
    return head;
}

/**
 * @return the end address (tail) of linkedList
 */

LinkedList::Node *LinkedList::end() const {
    return tail;
}

/**
 * @param value
 * @return the address of first node whose value is equal to the input parameter value
 * @return nullptr if not found
 */

LinkedList::Node *LinkedList::find(int const &value) const {

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
        if (ptr->value() == value) {
            return ptr;
        }
    }

    return nullptr;
}

/**
 * @param value
 * @return the number of elements whose value is equal to the input parameter value
 */

int LinkedList::count(int const &value) const {

    int counter = 0;

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
        if (ptr->value() == value) {
            counter++;
        }
    }

    return 0;
}

/**
 * this function swap input linked list with this
 * Works by swapping the parameters of the two DoubleLinkedList one by one
 * @param list
 */

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

/**
 * creates new node with the given value in the input and insert it at the beginning of the list
 * @param value
 */

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

/**
 * removes the beginning node of linked list
 * @throw Underflow exception if the list is empty
 */

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

/**
 * create a new node with the given value in the input and insert it at the end of linked list
 * @param value
 */

void LinkedList::insertEnd(int const &value) {

    Node *newnode = new Node(value, nullptr);

    if (empty()) {
        head = newnode;
        tail = newnode;
    } else {
        tail->nextNode = newnode;
        tail = newnode;
    }
}

/**
 * remove all nodes whose value is equal to the input value
 * @param value
 * @return
 */

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
                before->nextNode = temp->next();
                itr = itr->next();
            } else if (temp == tail) {
                tail = before;
                tail->nextNode = nullptr;
                itr = nullptr;
            } else {
                before->nextNode = itr->next();
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

std::ostream &operator<<(std::ostream &out, LinkedList const &list) {

    for (auto *ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
        out << ptr->value() << "->";
    }
    out << "0";


    return out;
}

#endif //LINKED_LIST_H
