#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

class Stack {
public:

    void push(int const &);

    void pop();

    int top();

    bool empty();

    int search(int const &);

    int size();

private:

    LinkedList linkedList;

};

void Stack::push(int const &value) {
    linkedList.push(value);
}

void Stack::pop() {
    if (empty()) throw Underflow();
    linkedList.pop();
}

int Stack::top() {
    linkedList.front();
}

bool Stack::empty() {
    return linkedList.empty();
}

int Stack::search(int const &value) {

    int position = 0;

    for (auto ptr = linkedList.begin(); ptr != nullptr; ptr = ptr->getNext(), position++)
        if (ptr->getValue() == value)
            return position;

    return -1;
}

int Stack::size() {
    return linkedList.size();
}


#endif //STACK_H
