#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
#include "exception.h"

template <typename A>
class DoubleLinkedList {
public:
    template <typename B>
    class DoubleNode {
    public:
        DoubleNode(B const & = 0, DoubleNode<B> * = nullptr, DoubleNode<B> * = nullptr);

        B object() const;

        DoubleNode<B> *previous() const;
        DoubleNode<B> *next() const;

        int nodeObject;
        DoubleNode<B> *previousNode;
        DoubleNode<B> *nextNode;
    };

    DoubleLinkedList();
    DoubleLinkedList(DoubleLinkedList const &);
    ~DoubleLinkedList();

    // Accessors

    int size() const;
    bool empty() const;

    A front() const;
    A back() const;

    DoubleNode<A> *begin() const;
    DoubleNode<A> *end() const;

    DoubleNode<A> *find(A const &) const;
    int count(A const &) const;

    // Mutators

    void swap(DoubleLinkedList &);

    void pushFront(A const &);
    void pushBack(A const &);

    void popFront();
    void popBack();

    int erase(A const &);
    void print();

private:
    DoubleNode<A> *listHead;
    DoubleNode<A> *listTail;
    int listSize;


    void eraseDoubleNode(DoubleNode<A>* );

    // Friends

    //friend std::ostream &operator<<(std::ostream &, DoubleLinkedList const &);
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////


/**
 * constructor for creating a node
 * @param obj nodeValue
 * @param pn previousNode
 * @param nn nextNode
 */

template <typename A>
template <typename B>
DoubleLinkedList<A>::DoubleNode<B>::DoubleNode(B const &obj, DoubleLinkedList::DoubleNode<B> *pn, DoubleLinkedList::DoubleNode<B> *nn) :
        nodeObject(obj),
        previousNode(pn),
        nextNode(nn) {

}

/**
 * @return the node value of this node
 * @throw Underflow() exception if list is empty
 */

template <typename A>
template <typename B>
B DoubleLinkedList<A>::DoubleNode<B>::object() const {
    if (this == nullptr) throw Underflow();
    return nodeObject;
}

/**
 * @return the address of previous node of this node
 */

template <typename A>
template <typename B>
typename DoubleLinkedList<A>::template DoubleNode<B> *DoubleLinkedList<A>::DoubleNode<B>::previous() const {
    return previousNode;
}

/**
 * @return the address of next node of this node
 */

template <typename A>
template <typename B>
typename DoubleLinkedList<A>::template DoubleNode<B> *DoubleLinkedList<A>::DoubleNode<B>::next() const {
    return nextNode;
}

/**
 * constructor
 * make an object from DoubleLinkedList class
 */

template <typename A>
DoubleLinkedList<A>::DoubleLinkedList() : listHead(nullptr), listTail(nullptr), listSize(0) {

}

/**
 * this constructor receives a linked list and copies all of its elements
 *
 * @param list
 */

template <typename A>
DoubleLinkedList<A>::DoubleLinkedList(DoubleLinkedList<A> const &list) : listHead(nullptr), listTail(nullptr), listSize(0) {

    for ( auto ptr = list.begin(); ptr != nullptr; ptr = ptr->next() ) // loop for iterating in this list
        this->pushBack(ptr->nodeObject); // add elements from back of double linked list

}

/**
 * delete every element in Double linked list by popFront function when destructor called
 */

template <typename A>
DoubleLinkedList<A>::~DoubleLinkedList() {
    while (listHead != nullptr) {
        this->popFront();
    }
}

/**
 * @return listSize
 */

template <typename A>
int DoubleLinkedList<A>::size() const {
    return listSize;
}

/**
 * @return true when list is empty
 */

template <typename A>
bool DoubleLinkedList<A>::empty() const {
    return this->listTail == nullptr && this->listHead == nullptr; // check both head and tail for empty
}

/**
 * @throw Underflow if DoubleLinkedList is empty
 * @return nodeValue of listHead
 */

template <typename A>
A DoubleLinkedList<A>::front() const {
    if (listHead == nullptr) throw Underflow();
    return listHead->nodeObject;
}

/**
 * @throw Underflow if DoubleLinkedList is empty
 * @return nodeValue of listTail
 */

template <typename A>
A DoubleLinkedList<A>::back() const {
    if (listTail == nullptr) throw Underflow();
    return listTail->nodeObject;
}

/**
 * @return the beginning address (listHead) of DoubleLinkedlist
 */

template <typename A>
typename DoubleLinkedList<A>::template DoubleNode<A> *DoubleLinkedList<A>::begin() const {
    return listHead;
}

/**
 * @return the end address (listTail) of DoubleLinkedlist
 */

template <typename A>
typename DoubleLinkedList<A>::template DoubleNode<A> *DoubleLinkedList<A>::end() const {
    return listTail;
}

/**
 * @param object
 * @return the address of first node whose value is equal to the input parameter value
 * if not found return nullptr
 */

template <typename A>
typename DoubleLinkedList<A>::template DoubleNode<A> *DoubleLinkedList<A>::find(A const &object) const {

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) // loop for iterating in list
        if (ptr->nodeObject == object)
            return ptr;

    return nullptr;
}

/**
 * @param value
 * @Return the number of elements whose value is equal to the input parameter value
 */

template <typename A>
int DoubleLinkedList<A>::count(A const &object) const {

    int counter = 0;

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) // loop for iterating in list
        if (ptr->nodeObject == object)
            counter++;

    return counter;

}

/**
 * this function swap input linked list with this
 * Works by swapping the parameters of the two DoubleLinkedList one by one
 * @param list
 */

template <typename A>
void DoubleLinkedList<A>::swap(DoubleLinkedList<A> &list) {

    std::swap(this->listHead, list.listHead);
    std::swap(this->listTail, list.listTail);
    std::swap(this->listSize, list.listSize);

}

/**
 * Creates a new node with the given value in the input and inserts it at the beginning of the list
 * @param object
 */

template <typename A>
void DoubleLinkedList<A>::pushFront(A const &object) {

    DoubleNode<A>* newnode = new DoubleNode<A>(object, nullptr, listHead); // create a new node for adding at front of the list

    if (listHead == nullptr) { // check if list is empty
        listHead = newnode;
        listTail = newnode;
    } else { // if list is not empty
        listHead->previousNode = newnode;
        listHead = newnode;
    }

    listSize++;
}

/**
 * Creates a new node with the given value in the input and inserts it at the end of the list
 * @param object
 */

template <typename A>
void DoubleLinkedList<A>::pushBack(A const &object) {

    DoubleNode<A> *newnode = new DoubleNode<A>(object, listTail, nullptr); // create a new node for adding at end of list

    if (listTail == nullptr) { // check if list is empty
        listTail = newnode;
        listHead = newnode;
    } else { // if list is not empty
        listTail->nextNode = newnode;
        listTail = newnode;
    }

    listSize++;
}

/**
 * removes the beginning node of DoubleLinkedList
 * @throw Underflow() exception if the list is empty
 */

template <typename A>
void DoubleLinkedList<A>::popFront() {

    if (listHead == nullptr) throw Underflow();

    DoubleNode<A> *temp = listHead;

    if (listHead == listTail) { // check if list has one node
        listTail = nullptr;
        listHead = nullptr;
    } else { // if list has more than one node
        temp->nextNode->previousNode = nullptr;
        listHead = temp->nextNode;
    }

    delete temp;

    listSize--;

}

/**
 * removes the end node of DoubleLinkedList
 * @throw Underflow() if the list is empty
 */

template <typename A>
void DoubleLinkedList<A>::popBack() {

    if (listTail == nullptr) throw Underflow();

    DoubleNode<A> *temp = listTail;

    if (listHead == listTail) { // check if list has one node
        listTail = nullptr;
        listHead = nullptr;
    } else { // if list has more than one node
        temp->previousNode->nextNode = nullptr;
        listTail = temp->previousNode;
    }

    delete temp;

    listSize--;

}

/**
 * Removes all nodes whose value is equal to the input parameter value
 * @param object
 * @return the number of removed nodes in DoubleLinkedList
 */

template <typename A>
int DoubleLinkedList<A>::erase(A const &object) {

    int counter = 0;

    DoubleNode<A>* node = listHead;
    DoubleNode<A>* nextNode;

    while (node != nullptr) {
        if (node->nodeObject == object) {
            nextNode = node->nextNode;
            eraseDoubleNode(node);
            node = nextNode;
            counter++;
            listSize--;
        } else {
            node = node->nextNode;
        }
    }

    return counter;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

/**
 * this function is for delete a given node
 * @param node
 */

template <typename A>
void DoubleLinkedList<A>::eraseDoubleNode(DoubleLinkedList<A>::DoubleNode<A>* node) {

    if (listHead == listTail){ // check if list has one node or more
        listHead = nullptr;
        listTail = nullptr;
    } else if (node == listHead){ // check if given node is head
        listHead = node->nextNode;
        node->nextNode->previousNode = nullptr;
    } else if (node == listTail){ // check if given node is tail
        listTail = node->previousNode;
        node->previousNode->nextNode = nullptr;
    } else { // if given node is middle of list
        node->previousNode->nextNode = node->nextNode;
        node->nextNode->previousNode = node->previousNode;
    }

    delete node;
}

template<typename A>
void DoubleLinkedList<A>::print() {

    std::cout << "Head";
    for (auto *ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) {
        std::cout << "->" << ptr->object();
    }
    std::cout << "->Tail" << std::endl;

}

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

//std::ostream &operator<<(std::ostream &out, DoubleLinkedList const &list) {
//    out << "head";
//
//    // print list from start to end
//    for (auto *ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
//        out << "->" << ptr->object();
//    }
//    out << "->0" << std::endl << "tail";
//
//    // print list from end to start
//    for (DoubleLinkedList::DoubleNode *ptr = list.end(); ptr != nullptr; ptr = ptr->previous()) {
//        out << "->" << ptr->object();
//    }
//    out << "->0";
//
//    return out;
//}


#endif