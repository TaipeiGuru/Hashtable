#include <iostream>
#ifndef STUDENT_H
#define STUDENT_H

using namespace std;

class Student {
 public:
  // Constructor.
  Student();
  // Destructor.
  ~Student();
  // Setting name to a passed-in char array.
  void setName(char* input);
  // Printing the name.
  void printName();
 private:
  // Student name.
  char name[10];
};

#endif
