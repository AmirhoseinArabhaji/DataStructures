#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

/**
 * Stack class implementation using template single linked list
 */

template <typename A>
class LLStack {
public:

    void push(A const &object);
    void pop();
    A top();
    bool empty();
    int size();

private:

    LinkedList<A> linkedList;

};

template <typename A>
void LLStack<A>::push(A const &object) {
    linkedList.push(object);
}

template <typename A>
void LLStack<A>::pop() {
    if (empty()) throw Underflow();
    linkedList.pop();
}

template <typename A>
A LLStack<A>::top() {
    return linkedList.front();
}

template <typename A>
bool LLStack<A>::empty() {
    return linkedList.empty();
}

template <typename A>
int LLStack<A>::size() {
    return linkedList.size();
}


#endif //STACK_H
