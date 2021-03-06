#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "header.h"

template <typename A>
class LinkedList {
public:
    template <typename B>
    class Node {
    public:
        Node(B const & = 0, Node<B> * = nullptr);

        B object() const;
        Node<B> *next() const;

        B nodeObject;
        Node<B> *nextNode;

    };

    LinkedList();
    LinkedList(LinkedList const &list);
    ~LinkedList();

    //Accessors

    int size() const;
    bool empty() const;

    A front() const;
    A back() const;

    Node<A> *begin() const;
    Node<A> *end() const;

    Node<A> *find(int const &) const;
    int count(int const &) const;

    //Mutators

    int erase(const A &object);
    void swap(LinkedList &);

    void push(const A &object);
    void pop();

    void pushBack(const A &object);
    void print() const;

    Node<A> *getNthNode(int const &) const;
    A getIndex(int const &) const;

private:

    Node<A> *head;
    Node<A> *tail;
    int listSize;

};

/**
 * constructor for creating a node
 * @param value nodeValue
 * @param nn nextNode
 */

template <typename A>
template <typename B>
LinkedList<A>::Node<B>::Node(B const &obj, LinkedList::Node<B> *nn) : nodeObject(obj), nextNode(nn) {

}

/**
 * @return node value
 */

template <typename A>
template <typename B>
B LinkedList<A>::Node<B>::object() const {
    if (this == nullptr) throw Underflow();
    return nodeObject;
}

/**
 * @return next node address
 */

template <typename A>
template <typename B>
typename LinkedList<A>::template Node<B> *LinkedList<A>::Node<B>::next() const {
    return nextNode;
}

/**
 * constructor for creating a linked list
 */

template <typename A>
LinkedList<A>::LinkedList() : listSize(0), head(nullptr), tail(nullptr) {

}

/**
 * this constructor receives a linked list and copies all of its elements to itself
 * @param list
 */

template <typename A>
LinkedList<A>::LinkedList(LinkedList<A> const &list) {

    for (auto ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
        this->pushBack(ptr->object());
    }

}

/**
 * delete every element in linked list by pop function when destructor called
 */

template <typename A>
LinkedList<A>::~LinkedList() {
    while (head != nullptr) {
        this->pop();
    }
}

/**
 * @return size of linked list
 */

template <typename A>
int LinkedList<A>::size() const {
    return listSize;
}

/**
 * @return true if linked list is empty
 */

template <typename A>
bool LinkedList<A>::empty() const {
    return head == nullptr && tail == nullptr;
}

/**
 * @throw Underflow exception if list is empty
 * @return value of head
 */

template <typename A>
A LinkedList<A>::front() const {
    if (empty()) throw Underflow();
    return head->object();
}

/**
 * @throw Underflow exception if list is empty
 * @return value of tail
 */

template <typename A>
A LinkedList<A>::back() const {
    if (empty()) throw Underflow();
    return tail->object();
}

/**
 * @return the beginning (head) address of linkedList
 */

template <typename A>
typename LinkedList<A>::template Node<A> *LinkedList<A>::begin() const {
    return head;
}

/**
 * @return the end address (tail) of linkedList
 */

template <typename A>
typename LinkedList<A>::template Node<A> *LinkedList<A>::end() const {
    return tail;
}

/**
 * @param object
 * @return the address of first node whose value is equal to the input parameter value
 * @return nullptr if not found
 */

template <typename A>
typename LinkedList<A>::template Node<A> *LinkedList<A>::find(int const &object) const {

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
        if (ptr->object() == object) {
            return ptr;
        }
    }

    return nullptr;
}

/**
 * @param value
 * @return the number of elements whose value is equal to the input parameter value
 */

template <typename A>
int LinkedList<A>::count(int const &object) const {

    int counter = 0;

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
        if (ptr->object() == object) {
            counter++;
        }
    }

    return counter;
}

/**
 * this function swap input linked list with this
 * Works by swapping the parameters of the two DoubleLinkedList one by one
 * @param list
 */

template <typename A>
void LinkedList<A>::swap(LinkedList &list) {

    std::swap(this->head, list.head);
    std::swap(this->tail, list.tail);
    std::swap(this->listSize, list.listSize);

}

/**
 * creates new node with the given value in the input and insert it at the beginning of the list
 * @param value
 */

template <typename A>
void LinkedList<A>::push(A const &object) {

    Node<A> *newnode = new Node<A>(object, head);

    if (empty()) {
        head = newnode;
        tail = newnode;
    } else {
        head = newnode;
    }

    listSize++;
}

/**
 * removes the beginning node of linked list
 * @throw Underflow exception if the list is empty
 */

template <typename A>
void LinkedList<A>::pop() {

    if (empty()) throw Underflow();

    Node<A> *temp = head;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = temp->next();
    }

    delete temp;
    listSize--;

}

/**
 * create a new node with the given value in the input and insert it at the end of linked list
 * @param value
 */

template <typename A>
void LinkedList<A>::pushBack(A const &object) {

    Node<A> *newnode = new Node<A>(object, nullptr);

    if (empty()) {
        head = newnode;
        tail = newnode;
    } else {
        tail->nextNode = newnode;
        tail = newnode;
    }

    listSize++;
}

/**
 * remove all nodes whose value is equal to the input value
 * @param value
 * @return
 */

template <typename A>
int LinkedList<A>::erase(A const &object) {

    if (empty()) throw Underflow();
    int counter = 0;

    Node<A> *itr = head;
    Node<A> *before = new Node<A>(0, head);

    while (itr != nullptr) {
        if (itr->object() == object) {
            Node<A> *temp = itr;

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
            listSize--;
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

template <typename A>
void LinkedList<A>::print() const {
    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
        std::cout << ptr->object() << " --> ";
    }
    std::cout << "nullptr" << std::endl;
}

/**
 * this function gives Nth index of linked list
 * @throw OutOfRange if the index is negative or is bigger than size of linked list
 * @tparam A
 * @param index
 * @return
 */

template<typename A>
typename LinkedList<A>::template Node<A> *LinkedList<A>::getNthNode(int const &index) const{

    if (index < 0 || index >= size())
        throw OutOfRange();

    Node<A> *node = head;

    for (int i = 1; i <= index; i++) {
        node = node->next();
    }

    return node;
}

/**
 * @tparam A
 * @param index
 * @return the object of Nth node in list
 */

template<typename A>
A LinkedList<A>::getIndex(int const &index) const {

    if (index < 0 || index >= size())
        throw OutOfRange();

    Node<A> *node = head;

    for (int i = 1; i <= index; i++) {
        node = node->next();
    }

    return node->nodeObject;

}

#endif //LINKED_LIST_H
