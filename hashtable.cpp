#include <iostream>
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

void addStudent(Node* myList[100], int hashFunctionValue, Student* newStudent);
int hashFunction(int id);
void printStudent(Node* myList[100], Node* headNode);
// void deleteStudent(Node* &headNode, int myID); 

int main() {
  char input[20];
  bool active = true;
  Node* list[100];
  int myID;
  float myGPA;
  int hash;
  Node* headNode;
  
  // Sets each object in the array to null. Help with this from https://stackoverflow.com/questions/4178804/how-to-see-if-an-element-is-null-in-an-array-in-c
  for(int i = 0; i<100; i++) {
    list[i] = NULL;
  }
  
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
      printStudent(list, headNode);
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
    Node* tempNode = new Node(newStudent);
    myList[hashFunctionValue] = tempNode;
    cout << "Student added." << endl;
  } else if(myList[hashFunctionValue]->getNext() == NULL) {
    Node* tempNode = new Node(newStudent);
    myList[hashFunctionValue]->setNext(tempNode);
    cout << "Student added." << endl;
  } else if(myList[hashFunctionValue]->getNext()->getNext() == NULL) {
    Node* tempNode = new Node(newStudent);
    myList[hashFunctionValue]->getNext()->setNext(tempNode);
    cout << "Student added." << endl;
  } else {
    int newSize = 2*sizeof(list)/sizeof(list[0]);
    Node* newList = new Node*[newSize];
    int* temp = list;
    list = newList;
    delete[] temp;
    
    Node* tempNode = new Node(newStudent);
    myList[199] = tempNode;
    cout << "Student added." << endl;
  } 
}
      
int hashFunction(int id) {
  int value = id % 100;
  return value;
}


void printStudent(Node* myList[100], Node* headNode) {
  for(int i = 0; i<100; i++) {
    if(myList[i] != NULL) {
      myList[i]->getStudent()->printStudent();
      if(myList[i]->getNext() != NULL) {
        myList[i]->getNext()->getStudent()->printStudent();
	if(myList[i]->getNext()->getNext() != NULL) {
	  myList[i]->getNext()->getNext()->getStudent()->printStudent();
	}
      }
    }
  } 
}
/*
void deleteStudent(Node* &headNode, int myID) {

}
*/
