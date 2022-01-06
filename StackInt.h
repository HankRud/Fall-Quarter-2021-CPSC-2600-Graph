// FILE: StackInt.h
// DESCRIPTION: Class definition for a stack of integers

// NOTE: You are not allowed to modify this file.

#ifndef STACKINT_H
#define STACKINT_H

#include <stack>
using namespace std;

class StackInt
{
 public:

   // Add an integer to the top of the stack.
   void push(int val);

   // Removes and returns an integer from the top of the stack. Aborts the
   // program is the stack is empty.
   int pop();

   // Returns but does not remove the integer at the top of the stack. Aborts the
   // program is the stack is empty.
   int top() const;

   // Returns true if the stack is empty.
   bool isEmpty() const;

 private:
   stack<int> stackObj;		// underyling STL stack object
};
#endif // STACKINT_H
