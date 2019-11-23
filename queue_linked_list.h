#ifndef QUEUE_LINKED_LIST_H
#define QUEUE_LINKED_LIST_H

class LLQueue {
public:

    int size() const;
    bool empty() const;
    int front();
    void push(int const &value);
    void pop();

private:
    LinkedList linkedList;

};

int LLQueue::size() const {
    return linkedList.size();
}

bool LLQueue::empty() const {
    return linkedList.empty();
}

int LLQueue::front() {
    return linkedList.front();
}

void LLQueue::push(int const &value) {
    linkedList.insertEnd(value);
}

void LLQueue::pop() {
    linkedList.pop();
}

#endif //QUEUE_LINKED_LIST_H
