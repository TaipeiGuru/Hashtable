#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

// Constructor.
Student::Student() {
}

// Destructor.
Student::~Student() {
}

// Using strcpy to set name to passed in char array.
void Student::setName(char* input) {
  strcpy(name, input);
}

// Printing the student name.
void Student::printName() {
  cout << name << endl;
}
