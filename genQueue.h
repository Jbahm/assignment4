#ifndef GenQueue_H
#define GenQueue_H

#include <iostream>
#include "DoublyLinkedList.h"
#include "ListNode.h"
using namespace std;

template <class T>
class GenQueue {
  public:
    unsigned int numElements;
    ListNode<T> *front;
    ListNode<T> *back;

    GenQueue();
    ~GenQueue();

    void enqueue(T d);
    T dequeue();

    T vFront();
    T vBack();

    void printQ();
    bool isEmpty();
    unsigned int getSize();
};
//constructor
template <class T>
GenQueue<T>::GenQueue() {
  numElements = 0;
  front = NULL;
  back = NULL;
}
//deconstructor
template <class T>
GenQueue<T>::~GenQueue() {

}
//add an item to the queue
template <class T>
void GenQueue<T>::enqueue(T d) {
  ListNode<T> *node = new ListNode<T>(d);
  if(numElements == 0) {
      front = node;
  }
  else {
      back->next = node;
      node->prev = back;
  }

  back = node;
  ++numElements;
}
//delete an item from the Queue
template <class T>
T GenQueue<T>::dequeue() {

  if(!isEmpty()) {
    ListNode<T> *node = front;

    T temp = node->data;

//Only Node in List
    if(front->next == NULL) {
      front = NULL;
      back = NULL;
    }
//More than One
    else {
      front->next->prev = NULL;
      front = front->next;
    }

    delete node;
    numElements--;
    return temp;
  }
  else {
    return T();
  }
}

//returns the front of the queue
template <class T>
T GenQueue<T>::vFront() {
  if(isEmpty() == false){
  return front->data;
  }
  return T();
}

//returns the back of the queue
template <class T>
T GenQueue<T>::vBack() {
  if(isEmpty() == false){
  return back->data;
  }
  return T();
}

//prints the queue
template <class T>
void GenQueue<T>::printQ() {
  if(isEmpty() == false){
  ListNode<T> *curr = front;
  while(true) {
    if(curr != NULL) {
      curr->data.printPerson();
      curr = curr->next;
    }
    else {
      break;
    }
  }
}else{
  cout << "Queue is empty!" << endl;
}
}

//checks to see if the queue is empty
template <class T>
bool GenQueue<T>::isEmpty() {
  return (numElements == 0);
}

//get the size of the queue
template <class T>
unsigned int GenQueue<T>::getSize() {
  return numElements;
}


#endif
