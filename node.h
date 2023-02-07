// node.h file for linked lists.
// Imports.
#include <iostream>
#include "student.h"

// Header guard.
#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  // Constructor that takes in a student pointer. 
  Node(Student*);
  // Destructor. 
  ~Node();
  // Creates a pointer to the next node (which is passed in).
  void setNext(Node* nextNode);
  // Gets a pointer to the next node.
  Node* getNext();
  // Returns the student pointer associated with this node.
  Student* getStudent();
 private:
  // Student pointer associated with this node.
  Student* student;
  // Node pointer to the next node.
  Node* next;
};

#endif
