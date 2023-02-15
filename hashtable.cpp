
#include <iostream>
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

void addStudent(Node** myList, int hashFunctionValue, Student* newStudent);
int hashFunction(int id, int listSize);
void printStudent(Node** myList, int listSize);
bool collisionChecker(Node** list, int hashFunctionValue);
void reHash(int listSize, int newListSize, Node** &list, Node** temp);
// void deleteStudent(Node* &headNode, int myID); 

int main() {
  char input[20];
  bool active = true;
  int listSize = 100;
  Node** list = new Node*[listSize];
  int myID;
  float myGPA;
  int hash;
  Node* headNode = NULL;
  
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
      hash = hashFunction(myID, listSize);
      
      if(collisionChecker(list, hash) == true) {
	int newListSize = listSize * 2;
	Node** temp = new Node*[newListSize];
        
        for(int j = 0; j < newListSize; j++) {
          temp[j] = NULL;
        }

        reHash(listSize, newListSize, list, temp);
	hash = hashFunction(myID, newListSize);
	addStudent(list, hash, newStudent);
	listSize = newListSize;
      } else {
	addStudent(list, hash, newStudent);
	cout << "Student added." << endl;
      }

    } else if(strcmp(input, "DELETE") == 0){   

    } else if(strcmp(input, "PRINT") == 0){
      printStudent(list, listSize);
    } else if(strcmp(input, "QUIT") == 0){
      active = false;
    } else {
      cout << "Invalid input." << endl;
    }
  }
  
  return 0;
}


void addStudent(Node** myList, int hashFunctionValue, Student* newStudent) {
  if(myList[hashFunctionValue] == NULL) {
    Node* tempNode = new Node(newStudent);
    myList[hashFunctionValue] = tempNode;
  } else if(myList[hashFunctionValue]->getNext() == NULL) {
    cout << "expected" << endl;
    Node* tempNode = new Node(newStudent);
    cout << hashFunctionValue << endl;
    myList[hashFunctionValue]->setNext(tempNode);
  } else if(myList[hashFunctionValue]->getNext()->getNext() == NULL) {
    Node* tempNode = new Node(newStudent);
    myList[hashFunctionValue]->getNext()->setNext(tempNode);
  }  
}

void reHash(int listSize, int newListSize, Node** &list, Node** temp) {
  int hash;
  for (int i = 0; i < listSize; i++) {
    if (list[i] != NULL) {
      Node* tempNode = list[i];
      while (tempNode != NULL) {
        hash = hashFunction(tempNode->getStudent()->getID(), newListSize);
	cout << hash << endl;
        addStudent(temp, hash, tempNode->getStudent());
        tempNode = tempNode->getNext();
      }
    }
  }
  delete[] list;
  list = temp;
}

int hashFunction(int id, int listSize) {
  int value = id % listSize;
  return value;
}


void printStudent(Node** myList, int listSize) {
  for(int i = 0; i<listSize; i++) {
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

bool collisionChecker(Node** list, int hashFunctionValue) {
  if(list[hashFunctionValue] != NULL) {
    if(list[hashFunctionValue]->getNext() != NULL) {
      if(list[hashFunctionValue]->getNext()->getNext() != NULL) {
	      return true;
      }
    }
  }
  return false;
}
