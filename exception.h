#ifndef EXCEPTION_H
#define EXCEPTION_H

/*
* All exceptions are derived from the 'exception' class
*  - consequently, catch( exception ) { ... } will catch only these exceptions
*
*       exception <----- Underflow
*                    |-- Underflow
*                    |-- Overflow
*                    |-- DivisionByZero
*                    |-- IllegalArgument
*                     -- OutOfRange
*/

class Exception {
    // empty class
};

class Underflow : public Exception {
    // empty class
};

class Overflow : public Exception {
    // empty class
};

class DivisionByZero : public Exception {
    // emtpy class
};

class IllegalArgument : public Exception {
    // emtpy class
};

class OutOfRange : public Exception {
    // emtpy class
};

#endif