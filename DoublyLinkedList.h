#ifndef DoublyLinkedList_H
#define DoublyLinkedList_H

#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class DoublyLinkedList {

  public:
    unsigned int size;
    ListNode<T> *front;
    ListNode<T> *back;

    DoublyLinkedList(); //Constructor
    ~DoublyLinkedList(); //Destructor

    void insertBack(T data);
    T removeFront();
    ListNode<T>* getFront();

    void printList();
    void deletePos(int pos);

    bool isEmpty();
    unsigned int getSize();
};
//constructor
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
  size = 0;
  front = NULL;
  back = NULL;
}
//deconstructor
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {

}

//insert from the back
template <class T>
void DoublyLinkedList<T>::insertBack(T data) {
  ListNode<T> *node = new ListNode<T>(data);

   if(size == 0) { //if empty
       front = node;
   }

   else {  //Not Empty
       back->next = node;
       node->prev = back;
   }
   back = node;
   ++size;
}

//delete from the front of the list
template <class T>
T DoublyLinkedList<T>::removeFront() {
  if(!isEmpty()) {
    ListNode<T> *node = front;

    if(front->next == NULL) { //Only Node in List
      front = NULL;
      back = NULL;
    }
    else {  //More than One
      front->next->prev = NULL;
      front = front->next;
    }

    T temp = node->data;
    delete node;
    size;
    return temp;
  }
  else {
    return T();
  }
}

//get data from front of the list
template <class T>
ListNode<T>* DoublyLinkedList<T>::getFront() {
  return front;
}

//print the list
template <class T>
void DoublyLinkedList<T>::printList() {
  ListNode<T> *curr = front;
  while(true){
    cout << curr->data << endl;
    curr = curr->next;
  }
}
//delete at a position
template <class T>
void DoublyLinkedList<T>::deletePos(int pos) {
  int idx = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

   while(idx != pos) {
     prev = curr;
     curr = curr->next;
     idx++;
   }

   prev->next = curr->next;
   curr->next->prev = prev;
   curr->next = NULL;
   //curr->prev = NULL;
   //curr->data = NULL;

   size--;
   delete curr;
}

//check if the list is empty
template <class T>
bool DoublyLinkedList<T>::isEmpty() {
  return(size == 0);
}

//get size of list
template <class T>
unsigned int DoublyLinkedList<T>::getSize() {
  return size;
}
#endif
