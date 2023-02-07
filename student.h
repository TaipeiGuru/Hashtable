// student.h file for LinkedLists 2

// Imports
#include <iostream>
#ifndef STUDENT_H
#define STUDENT_H

using namespace std;

class Student {
 // declaring functions
 public:
  // Constructor.
  Student();
  // Destructor.
  ~Student();
  // Printing the name.
  void printStudent();
  void setID(int myId);
  void setGPA(float myGPA);
  int getID();;
  float getGPA();
  char* getFirstName();
  char* getLastName();
 private:
  // Student details.
  char firstName[20];
  char lastName[20];
  int id;
  float gpa;
};

#endif
