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
    int top();
    bool empty();
    int search(A const &object);
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
int LLStack<A>::top() {
    linkedList.front();
}

template <typename A>
bool LLStack<A>::empty() {
    return linkedList.empty();
}

template <typename A>
int LLStack<A>::search(A const &object) {

    int position = 0;

    for (auto ptr = linkedList.begin(); ptr != nullptr; ptr = ptr->next(), position++)
        if (ptr->object() == object)
            return position;

    return -1;
}

template <typename A>
int LLStack<A>::size() {
    return linkedList.size();
}


#endif //STACK_H
