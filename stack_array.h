#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

class ArrStack {
public:

    ArrStack(int const &capacity);

    ArrStack(ArrStack &stack);

    ~ArrStack();

    bool empty() const;

    int top() const;

    void push(int const &value);

    void pop();

    void print();

private:

    int *array;
    int stackSize;
    int stackCapacity;

};

ArrStack::ArrStack(int const &capacity) :
        array(new int[capacity > 1 ? capacity : 1]),
        stackCapacity(capacity > 1 ? capacity : 1),
        stackSize(0) {

}

ArrStack::ArrStack(ArrStack &stack) :
        array(stack.array),
        stackCapacity(stack.stackCapacity),
        stackSize(stack.stackSize) {

}

ArrStack::~ArrStack() {
    delete[] array;
}

bool ArrStack::empty() const {
    return stackSize == 0;
}

int ArrStack::top() const {
    return array[stackSize - 1];
}

void ArrStack::push(int const &value) {
    if (stackSize == stackCapacity) {
        int *tempArray = new int[stackCapacity * 2];
        for (int i = 0; i < stackSize; i++) {
            tempArray[i] = array[i];
        }
        delete[] array;
        array = tempArray;
        stackCapacity *= 2;
        array[stackSize++] = value;
    } else {
        array[stackSize++] = value;
    }

}

void ArrStack::pop() {
    stackSize--;
}

void ArrStack::print() {
    cout << "bottom-->";
    for (int i = 0; i < stackSize; i++) {
        cout << array[i] << "-->";
    }
    cout << "top" << endl;
}

#endif //STACK_ARRAY_H
