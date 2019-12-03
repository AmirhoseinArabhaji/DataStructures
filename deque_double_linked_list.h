#ifndef DEQUE_DOUBLE_LINKED_LIST_H
#define DEQUE_DOUBLE_LINKED_LIST_H

template<typename A>
class DLLDeque {
public:

    int size();
    bool empty();

    A front();
    A back();

    void pushFront(A const &object);
    void pushBack(A const &object);

    void popFront();
    void popBak();

    void clear();

private:

    DoubleLinkedList<A> doubleLinkedList;

};

template<typename A>
int DLLDeque<A>::size() {
    return doubleLinkedList.size();
}

template<typename A>
bool DLLDeque<A>::empty() {
    return doubleLinkedList.empty();
}

template<typename A>
A DLLDeque<A>::front() {
    return doubleLinkedList.front();
}

template<typename A>
A DLLDeque<A>::back() {
    return doubleLinkedList.back();
}

template<typename A>
void DLLDeque<A>::pushFront(const A &object) {
    doubleLinkedList.pushFront(object);
}

template<typename A>
void DLLDeque<A>::pushBack(const A &object) {
    doubleLinkedList.pushBack(object);
}

template<typename A>
void DLLDeque<A>::popFront() {
    doubleLinkedList.popFront();
}

template<typename A>
void DLLDeque<A>::popBak() {
    doubleLinkedList.popBack();
}

template<typename A>
void DLLDeque<A>::clear() {
    while (!doubleLinkedList.empty()) {
        doubleLinkedList.popFront();
    }
}

#endif //DEQUE_DOUBLE_LINKED_LIST_H
