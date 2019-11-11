#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
#include "exception.h"

class DoubleLinkedList {
public:
    class DoubleNode {
    public:
        DoubleNode(int const & = int(), DoubleNode * = nullptr, DoubleNode * = nullptr);

        int value() const;

        DoubleNode *previous() const;
        DoubleNode *next() const;

        int nodeValue;
        DoubleNode *previousNode;
        DoubleNode *nextNode;
    };

    DoubleLinkedList();
    DoubleLinkedList(DoubleLinkedList const &);
    ~DoubleLinkedList();

    // Accessors

    int size() const;
    bool empty() const;

    int front() const;
    int back() const;

    DoubleNode *begin() const;
    DoubleNode *end() const;

    DoubleNode *find(int const &) const;
    int count(int const &) const;

    // Mutators

    void swap(DoubleLinkedList &);

    void pushFront(int const &);
    void pushBack(int const &);

    void popFront();
    void popBack();

    int erase(int const &);

private:
    DoubleNode *listHead;
    DoubleNode *listTail;
    int listSize;

    // List any additional private member functions you author here

    void eraseDoubleNode(DoubleNode* );

    // Friends

    friend std::ostream &operator<<(std::ostream &, DoubleLinkedList const &);
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

/**
 * constructor
 * make an object from DoubleLinkedList class
 */

DoubleLinkedList::DoubleLinkedList() : listHead(nullptr), listTail(nullptr), listSize(0) {

}

/**
 * this constructor receives a linked list and copies all of its elements
 *
 * @param list
 */

DoubleLinkedList::DoubleLinkedList(DoubleLinkedList const &list) : listHead(nullptr), listTail(nullptr), listSize(0) {

    for ( auto ptr = list.begin(); ptr != nullptr; ptr = ptr->next() ) // loop for iterating in this list
        this->pushBack(ptr->nodeValue); // add elements from back of double linked list

}

/**
 * delete every element in Double linked list by popFront function when destructor called
 */

DoubleLinkedList::~DoubleLinkedList() {
    while (listHead != nullptr) {
        this->popFront();
    }
}

/**
 * @return listSize
 */

int DoubleLinkedList::size() const {
    return listSize;
}

/**
 * @return true when list is empty ...
 */

bool DoubleLinkedList::empty() const {
    return this->listTail == nullptr && this->listHead == nullptr; // check both head and tail for empty
}

/**
 * @throw Underflow if DoubleLinkedList is empty
 * @return nodeValue of listHead
 */

int DoubleLinkedList::front() const {
    if (listHead == nullptr) throw Underflow();
    return listHead->nodeValue;
}

/**
 * @throw Underflow if DoubleLinkedList is empty
 * @return nodeValue of listTail
 */

int DoubleLinkedList::back() const {
    if (listTail == nullptr) throw Underflow();
    return listTail->nodeValue;
}

/**
 * @return the beginning address (listHead) of DoubleLinkedlist
 */

DoubleLinkedList::DoubleNode *DoubleLinkedList::begin() const {
    return listHead;
}

/**
 * @return the end address (listTail) of DoubleLinkedlist
 */

DoubleLinkedList::DoubleNode *DoubleLinkedList::end() const {
    return listTail;
}

/**
 * @param value
 * @return the address of first node whose value is equal to the input parameter value
 * if not found return nullptr
 */

DoubleLinkedList::DoubleNode *DoubleLinkedList::find(int const &value) const {

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) // loop for iterating in list
        if (ptr->nodeValue == value)
            return ptr;

    return nullptr;
}

/**
 * @param value
 * @Return the number of elements whose value is equal to the input parameter value
 */

int DoubleLinkedList::count(int const &value) const {

    int counter = 0;

    for (auto ptr = this->begin(); ptr != nullptr; ptr = ptr->next()) // loop for iterating in list
        if (ptr->nodeValue == value)
            counter++;

    return counter;

}

/**
 * this function swap input linked list with this
 * Works by swapping the parameters of the two DoubleLinkedList one by one
 * @param list
 */

void DoubleLinkedList::swap(DoubleLinkedList &list) {

    DoubleNode* tempHead = this->listHead;
    DoubleNode* tempTail = this->listTail;
    int tempSize = this->listSize;

    this->listHead = list.listHead;
    this->listTail = list.listTail;
    this->listSize = list.listSize;

    list.listHead = tempHead;
    list.listTail = tempTail;
    list.listSize = tempSize;


}

/**
 * Creates a new node with the given value in the input and inserts it at the beginning of the list
 * @param value
 */

void DoubleLinkedList::pushFront(int const &value) {

    DoubleNode* newnode = new DoubleNode(value, nullptr, listHead); // create a new node for adding at front of the list

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
 * @param value
 */

void DoubleLinkedList::pushBack(int const &value) {

    DoubleNode *newnode = new DoubleNode(value, listTail, nullptr); // create a new node for adding at end of list

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

void DoubleLinkedList::popFront() {

    if (listHead == nullptr) throw Underflow();

    DoubleNode *temp = listHead;

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

void DoubleLinkedList::popBack() {

    if (listTail == nullptr) throw Underflow();

    DoubleNode *temp = listTail;

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
 * @param value
 * @return the number of removed nodes in DoubleLinkedList
 */

int DoubleLinkedList::erase(int const &value) {

    int counter = 0;

    DoubleNode* node = listHead;
    DoubleNode* nextNode;

    while (node != nullptr) {
        if (node->nodeValue == value) {
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

/**
 * constructor for creating a node
 * @param nv nodeValue
 * @param pn previousNode
 * @param nn nextNode
 */

DoubleLinkedList::DoubleNode::DoubleNode(int const &nv, DoubleLinkedList::DoubleNode *pn, DoubleLinkedList::DoubleNode *nn) :
        nodeValue(nv),
        previousNode(pn),
        nextNode(nn) {

}

/**
 * @return the node value of this node
 * @throw Underflow() exception if list is empty
 */

int DoubleLinkedList::DoubleNode::value() const {
    if (this == nullptr) throw Underflow();
    return nodeValue;
}

/**
 * @return the address of previous node of this node
 */

DoubleLinkedList::DoubleNode *DoubleLinkedList::DoubleNode::previous() const {
    return previousNode;
}

/**
 * @return the address of next node of this node
 */

DoubleLinkedList::DoubleNode *DoubleLinkedList::DoubleNode::next() const {
    return nextNode;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

/**
 * this function is for delete a given node
 * @param node
 */

void DoubleLinkedList::eraseDoubleNode(DoubleLinkedList::DoubleNode* node) {

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

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &out, DoubleLinkedList const &list) {
    out << "head";

    // print list from start to end
    for (auto *ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
        out << "->" << ptr->value();
    }
    out << "->0" << std::endl << "tail";

    // print list from end to start
    for (DoubleLinkedList::DoubleNode *ptr = list.end(); ptr != nullptr; ptr = ptr->previous()) {
        out << "->" << ptr->value();
    }
    out << "->0";

    return out;
}


#endif