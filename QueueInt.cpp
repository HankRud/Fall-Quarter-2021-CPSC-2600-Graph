// FILE: QueueInt.cpp
// DESCRIPTION: Class implementation for a queue of integers

// NOTE: You are not allowed to modify this file.

#include <iostream>
#include <cstdlib>
using namespace std;

#include "QueueInt.h"

// Add an integer to the back of the queue.
void QueueInt::enqueue(int val)
{
  queueObj.push(val);
}

// Removes and returns an integer from the front of the queue. Aborts the
// program is the queue is empty.
int QueueInt::dequeue()
{
  int val = front();
  queueObj.pop();
  return val;
}

// Returns but does not remove the integer at the front of the queue. Aborts the
// program is the queue is empty.
int QueueInt::front() const
{
  if (isEmpty()) {
    cerr << "Tried to access empty queue --> aborting program" << endl;
    exit(-1);
  }

  return queueObj.front();
}

// Returns true if the queue is empty.
bool QueueInt::isEmpty() const
{
  return queueObj.empty();
}
