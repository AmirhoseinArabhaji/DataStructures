#ifndef QUEUE_LINKED_LIST_H
#define QUEUE_LINKED_LIST_H

#include "linked_list.h"

/**
 * Queue class implementation using template single linked list
 */

template <typename A>
class LLQueue {
public:

    int size() const;
    bool empty() const;
    A front();
    void push(A const &object);
    void pop();

private:

    LinkedList<A> linkedList;

};

template <typename A>
int LLQueue<A>::size() const {
    return linkedList.size();
}

template <typename A>
bool LLQueue<A>::empty() const {
    return linkedList.empty();
}

template <typename A>
A LLQueue<A>::front() {
    return linkedList.front();
}

template <typename A>
void LLQueue<A>::push(A const &object) {
    linkedList.pushBack(object);
}

template <typename A>
void LLQueue<A>::pop() {
    linkedList.pop();
}

#endif //QUEUE_LINKED_LIST_H
