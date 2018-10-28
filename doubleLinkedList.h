#include <iostream>

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
    T getFront();

    void printList();
    int deletePos(int pos);

    bool isEmpty();
    unsigned int getSize();
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
  size = 0;
  int front = NULL;
  int back = NULL;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {

}

template <class T>
void DoublyLinkedList<T>::insertBack(T data) {
  ListNode<T> *node = new ListNode<T>;

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

template <class T>
T DoublyLinkedList<T>::getFront() {
  return front->data;
}

template <class T>
void DoublyLinkedList<T>::printList() {
  ListNode<T> *curr = front;
  while(true) {
    if(curr->next == NULL) {
      break;
    }
    cout << curr->data << endl;
    curr = curr->next;
  }
}

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

template <class T>
bool DoublyLinkedList<T>::isEmpty() {
  return(size == 0);
}

template <class T>
unsigned int DoublyLinkedList<T>::getSize() {
  return size;
}
