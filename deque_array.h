#ifndef RESIZABLE_DEQUE_H
#define RESIZABLE_DEQUE_H

#include <algorithm>
#include "exception.h"

/**
 * Resizable Deque implementation using circular array
 */

class ResizableDeque {
public:
    ResizableDeque(int = 16);
    ResizableDeque(ResizableDeque const &);
    ~ResizableDeque();

    int front() const;
    int back() const;
    int size() const;
    bool empty() const;
    int capacity() const;

    void swap(ResizableDeque &);
    void pushFront(int const &);
    void pushBack(int const &);
    void popFront();
    void popBack();
    void clear();

private:
    // Your member variables
    int iFront;
    int iBack;
    int dequeSize;
    int initialCapacity;
    int currCapacity;
    int *array;

    // Any private member functions
    // TODO function for resizing array

    // Friends

    friend std::ostream &operator<<(std::ostream &, ResizableDeque const &);
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor

/**
 * constructor gets capacity as an optional parameter
 * if there is no input capacity, capacity considered 16
 * if the capacity is smaller than 16, capacity considered 16
 * @param n
 */

ResizableDeque::ResizableDeque(int n) :
        array(new int[n > 16 ? n : 16]),
        iFront(0),
        iBack(0),
        dequeSize(0),
        currCapacity(n > 16 ? n : 16),
        initialCapacity(n > 16 ? n : 16)
{

}

// Copy Constructor

/**
 * constructor received a list and copies all of its elements
 * @param deque
 */

ResizableDeque::ResizableDeque(ResizableDeque const &deque) :
        array(new int[deque.currCapacity]),
        iFront(deque.iFront),
        iBack(deque.iBack),
        dequeSize(deque.dequeSize),
        currCapacity(deque.currCapacity),
        initialCapacity(deque.initialCapacity)
{
    for (int i = iFront, j = 0; j < dequeSize; i = (i + 1) % currCapacity, j++)
        this->array[i] = deque.array[i];
}

// Destructor

/**
 * destructor deletes array
 */

ResizableDeque::~ResizableDeque() {
    delete[] array;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

/**
 * size is the current number of objects in the array
 * @return size of Deque
 */

int ResizableDeque::size() const {
    return dequeSize;
}

/**
 * capacity is the size of the current array we use for deque
 * @return current capacity for array
 */

int ResizableDeque::capacity() const {
    return currCapacity;
}

/**
 * @return true if deque is empty
 */

bool ResizableDeque::empty() const {
    return dequeSize == 0;
}

/**
 * @return the front element of deque which is the iFront element of array
 * @throw Underflow if deque is empty
 */

int ResizableDeque::front() const {
    if (empty()) throw Underflow();
    return array[iFront];
}

/**
 * @return the back element of deque which is the iBack element of array
 * @throw Underflow if deque is empty
 */

int ResizableDeque::back() const {
    if (empty()) throw Underflow();
    return array[iBack];
}

/**
 * this functions swap the input deque with this deque
 * @param deque
 */

void ResizableDeque::swap(ResizableDeque &deque) {
    std::swap(this->array, deque.array);
    std::swap(this->iFront, deque.iFront);
    std::swap(this->iBack, deque.iBack);
    std::swap(this->dequeSize, deque.dequeSize);
    std::swap(this->initialCapacity, deque.initialCapacity);
    std::swap(this->currCapacity, deque.currCapacity);
}

/**
 * this function inserts the given value at the beginning of the deque
 * if there is no space in the list it doubles the capacity of list
 * @param val
 */

void ResizableDeque::pushFront(int const &val) {
    /// checks if list is full
    if(dequeSize == currCapacity){
        /// create a new array double the capacity before
        int *temp = new int[currCapacity * 2];
        /// copies all elements to new array
        for (int i = iFront, j = 0; j < dequeSize; i = (i + 1) % currCapacity, j++)
            temp[j] = array[i];
        /// deletes previous array
        delete[] array;
        array = temp;
        currCapacity *= 2;
        /// correct the place of front and back of the list
        iFront = currCapacity - 1;
        iBack = dequeSize - 1;
        array[iFront] = val;
        dequeSize++;
    } else {
        /// checks if list is empty
        if (empty()){
            array[iFront] = val;
        } else {
            /// checks if iFront is negative
            iFront = iFront - 1 < 0 ? currCapacity - 1 : iFront - 1;
            //iFront--;
            //if (iFront < 0) iFront = currCapacity - 1;
            array[iFront] = val;
        }
        dequeSize++;
    }
}

/**
 * this function inserts the given value at the beginning of the deque
 * if there is no space in the list it doubles the capacity of list
 * @param val
 */

void ResizableDeque::pushBack(int const &val) {
    /// checks if list is full
    if (dequeSize == currCapacity){
        /// create a new array double the capacity before
        int *temp = new int[currCapacity * 2];
        /// copies all elements to new array
        for (int i = iFront, j = 0; j < dequeSize; i = (i + 1) % currCapacity, j++)
            temp[j] = array[i];
        /// deletes previous array
        delete[] array;
        array = temp;
        currCapacity *= 2;
        /// correct the place of front and back of the list
        iFront = 0;
        iBack = dequeSize;
        array[iBack] = val;
        dequeSize++;
    } else {
        /// checks if list is empty
        if (empty()){
            array[iBack] = val;
        } else {
            iBack = iBack + 1 == currCapacity ? 0 : iBack + 1;
            //iBack++;
            //if (iBack == currCapacity) iBack = 0;
            array[iBack] = val;
        }
        dequeSize++;
    }
}

/**
 * deletes first element of the list
 * @throw Underflow if list is empty
 * after deleting if the size of list is less than the current capacity and
 * the current capacity is bigger than the initial capacity, list capacity will be halved
 */

void ResizableDeque::popFront() {
    /// throws Underflow if list is empty
    if (empty()) throw Underflow();
    /// checks if last has more than one element
    if (dequeSize > 1) {
        iFront = (iFront + 1 == currCapacity) ? 0 : iFront + 1;
    } else if (dequeSize == 1) {
        iFront = 0;
        iBack = 0;
    }
    dequeSize--;

    if (dequeSize <= currCapacity / 4 && currCapacity > initialCapacity) {
        /// creates a new array with half of the current capacity
        int *temp = new int[currCapacity / 2];
        /// copies all elements to the new list
        for (int i = iFront, j = 0; j < dequeSize; i = (i + 1) % currCapacity, j++)
            temp[j] = array[i];
        /// delete previous array
        delete[] array;
        array = temp;
        currCapacity /= 2;
        /// correcting the place of front and back of the list after moving elements
        iFront = 0;
        iBack = dequeSize - 1;
    }
}

/**
 * deletes last element of the list
 * @throw Underflow if list is empty
 * after deleting if the size of list is less than the current capacity and
 * the current capacity is bigger than the initial capacity, list capacity will be halved
 */

void ResizableDeque::popBack() {
    /// throws Underflow if list is empty
    if (empty()) throw Underflow();
    /// checks if last has more than one element
    if (dequeSize > 1) {
        iBack = iBack - 1 < 0 ? currCapacity - 1 : iBack - 1;
    } else if (dequeSize == 1) {
        iFront = 0;
        iBack = 0;
    }
    dequeSize--;

    if (dequeSize <= currCapacity / 4 && currCapacity > initialCapacity) {
        /// creates a new array with half of the current capacity
        int *temp = new int[currCapacity / 2];
        /// copies all elements to the new list
        for (int i = iFront, j = 0; j < dequeSize; i = (i + 1) % currCapacity, j++)
            temp[j] = array[i];
        /// delete previous array
        delete[] array;
        array = temp;
        currCapacity /= 2;
        /// correcting the place of front and back of the list after moving elements
        iFront = 0;
        iBack = dequeSize - 1;
    }
}

/**
 * this function clears the list and returns the current capacity to initial capacity
 */

void ResizableDeque::clear() {
    delete[] array;
    array = new int[initialCapacity];
    currCapacity = initialCapacity;
    iBack = 0;
    iFront = 0;
    dequeSize = 0;
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functions (helper functions) here


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<(std::ostream &out, ResizableDeque const &list) {

    out << "START->";

    for (int i = list.iFront, j = 0; j < list.dequeSize; i = (i + 1) % list.currCapacity, j++) {
        out << list.array[i] << "->";
    }

    out << "END";

    return out;
}

#endif