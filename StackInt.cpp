// FILE: StackInt.cpp
// DESCRIPTION: Class implementation for a stack of integers

// NOTE: You are not allowed to modify this file.

#include <iostream>
#include <cstdlib>
using namespace std;

#include "StackInt.h"

// Add an integer to the top of the stack.
void StackInt::push(int val)
{
  stackObj.push(val);
}

// Removes and returns an integer from the top of the stack. Aborts the
// program is the stack is empty.
int StackInt::pop()
{
  int val = top();
  stackObj.pop();
  return val;
}

// Returns but does not remove the integer at the top of the stack. Aborts the
// program is the stack is empty.
int StackInt::top() const
{
  if (isEmpty()) {
    cerr << "Tried to access empty stack --> aborting program" << endl;
    exit(-1);
  }

  return stackObj.top();
}

// Returns true if the stack is empty.
bool StackInt::isEmpty() const
{
  return stackObj.empty();
}
