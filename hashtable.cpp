#include <iostream>
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

void addStudent(Node* myList[100], int hashFunctionValue, Student* newStudent);
int hashFunction(int id);
// void printStudent(Node* headNode);
// void deleteStudent(Node* &headNode, int myID); 

int main() {
  char input[20];
  bool active = true;
  Node* list[100];
  int myID;
  float myGPA;
  int hash;
  
  cout << "Welcome to Hashtable!" << endl; 
  
  // While loop to keep track of game running
  while(active == true) {
    cout << "Your options are \"ADD,\" \"DELETE,\" \"PRINT,\" and \"QUIT.\"" << endl;
    cin >> input;
    cin.clear();
    cin.ignore(10000, '\n');
    
    if(strcmp(input, "ADD") == 0){
      Student* newStudent = new Student();
      cout << "Enter the student's first name:" << endl; 
      cin >> newStudent->getFirstName();
      cout << "Enter the student's last name:" << endl; 
      cin >> newStudent->getLastName();
      cout << "Enter the student's ID:" << endl;
      cin >> myID;
      newStudent->setID(myID);
      cout << "Enter the student's GPA:" << endl;
      cin >> myGPA;
      newStudent->setGPA(myGPA);
      hash = hashFunction(myID);
      addStudent(list, hash, newStudent);
    } else if(strcmp(input, "DELETE") == 0){   

    } else if(strcmp(input, "PRINT") == 0){

    } else if(strcmp(input, "QUIT") == 0){
      active = false;
    } else {
      cout << "Invalid input." << endl;
    }
  }
  
  return 0;
}


void addStudent(Node* myList[100], int hashFunctionValue, Student* newStudent) {
   if(myList[hashFunctionValue] == NULL) {
    Node* headNode = new Node(newStudent);
    myList[hashFunctionValue] = headNode;
    cout << "Student added." << endl;
  } /*else if(headNode->getStudent()->getID() > newStudent->getID()) {
    Node* tempNode = headNode;
    headNode = new Node(newStudent);
    headNode->setNext(tempNode);
    cout << "Student added." << endl;
  } else if(headNode->getNext() == NULL) {
    Node* tempNode4 = new Node(newStudent);
    headNode->setNext(tempNode4);
    cout << "Student added." << endl;
  } else if(newStudent->getID() <= headNode->getNext()->getStudent()->getID() && newStudent->getID() >= headNode->getStudent()->getID()) {
    Node* tempNode2 = new Node(newStudent);
    tempNode2->setNext(headNode->getNext());
    headNode->setNext(tempNode2);
    cout << "Student added." << endl;
  } else {
    Node* tempNode3 = headNode->getNext();
    addStudent(tempNode3, newStudent);  
  } */
}
      
int hashFunction(int id) {
  int value = id % 100;
  return value;
}

/*
void printStudent(Node* headNode) {
 
}

void deleteStudent(Node* &headNode, int myID) {

}
*/
