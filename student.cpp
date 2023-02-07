// Student CPP file

// Imports
#include <iostream>
#include <cstring>
#include <iomanip>
#include "student.h"

using namespace std;

// Constructor.
Student::Student() {
}

// Destructor.
Student::~Student() {
}

// Printing the student information. Setprecision used to limit GPA decimals
void Student::printStudent() {
  cout << firstName << " " << lastName << ", " << id << ", " << fixed << setprecision(2) << gpa << endl;
}

// Setters
void Student::setID(int myID) {
  id = myID;
}

void Student::setGPA(float myGPA) {
  gpa = myGPA;
}

// Getters
int Student::getID() {
  return id;
}

float Student::getGPA() {
  return gpa;
}

char* Student::getFirstName() {
  return firstName;
}

char* Student::getLastName() {
  return lastName;
}
