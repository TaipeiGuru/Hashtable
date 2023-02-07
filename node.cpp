#include <iostream>
#include "node.h"

using namespace std;

// Constructing new node with no pointer to next and a passed-in student.
Node::Node(Student* myStudent) {
  next = NULL;
  student = myStudent;
}

// Destructor (deletes the associated student).
Node::~Node() {
  delete student;
}

// Sets the node pointer to the next (passed in) node.
void Node::setNext(Node* nextNode) {
  next = nextNode;
}

// Getter. 
Node* Node::getNext() {
  return next;
}

// Getter.
Student* Node::getStudent() {
  return student;
}
