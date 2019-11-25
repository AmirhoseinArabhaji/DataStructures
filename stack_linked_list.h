#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

/**
 * Stack class implementation using single linked list
 */

class LLStack {
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

void LLStack::push(int const &value) {
    linkedList.push(value);
}

void LLStack::pop() {
    if (empty()) throw Underflow();
    linkedList.pop();
}

int LLStack::top() {
    linkedList.front();
}

bool LLStack::empty() {
    return linkedList.empty();
}

int LLStack::search(int const &value) {

    int position = 0;

    for (auto ptr = linkedList.begin(); ptr != nullptr; ptr = ptr->next(), position++)
        if (ptr->value() == value)
            return position;

    return -1;
}

int LLStack::size() {
    return linkedList.size();
}


#endif //STACK_H
