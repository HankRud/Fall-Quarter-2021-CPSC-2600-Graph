// FILE: QueueInt.h
// DESCRIPTION: Class definition for a queue of integers

// NOTE: You are not allowed to modify this file.

#ifndef QUEUEINT_H
#define QUEUEINT_H

#include <queue>
using namespace std;

class QueueInt
{
 public:

   // Add an integer to the back of the queue.
   void enqueue(int val);

   // Removes and returns an integer from the front of the queue. Aborts the
   // program is the queue is empty.
   int dequeue();

   // Returns but does not remove the integer at the front of the queue. Aborts the
   // program is the queue is empty.
   int front() const;

   // Returns true if the queue is empty.
   bool isEmpty() const;

 private:
   queue<int> queueObj;		// underyling STL queue object
};

#endif // QUEUE_H
