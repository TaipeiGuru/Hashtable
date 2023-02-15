#include <iostream>
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

void addStudent(Node** myList, int hashFunctionValue, Student* newStudent);
int hashFunction(int id, int listSize);
void printStudent(Node** myList, Node* headNode);
bool collisionChecker(Node** list, int hashFunctionValue);
// void deleteStudent(Node* &headNode, int myID); 

int main() {
  char input[20];
  bool active = true;
  int listSize = 100;
  Node** list;
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
      hash = hashFunction(myID, listSize);

      if(collisionChecker(list, hash) == true) {
	Node* temp[listSize];
	for(int j = 0; j < listSize; j++) {
	  temp[j] = list[j];
	}
	int newListSize = listSize * 2;
	list = new Node*[newListSize];

	hash = hashFunction(myID, newListSize);
	for(int m = 0; m < listSize; m++) {
	  if(temp[m] != NULL) {
	    list[m] = temp[m];
	    if(temp[m]->getNext() != NULL) {
	      list[m]->setNext(temp[m]->getNext());
	      if(temp[m]->getNext()->getNext() != NULL) {
		list[m]->getNext()->setNext(temp[m]->getNext()->getNext());
	      }
	    }
	  } else {
	    list[m] = NULL;
	  }
	}
	
	delete[] temp;
	listSize = newListSize;
      }
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


void addStudent(Node** myList, int hashFunctionValue, Student* newStudent) {
  cout << "hi" << endl;
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
    int newSize = 2*sizeof(myList)/sizeof(myList[0]);
    Node* newList[newSize];

    for(int j = 0; j<newSize; j++) {
      if(myList[j] != NULL) {
	newList[j] = myList[j];
      }
    }
    
    delete[] myList;
    
    Node* tempNode = new Node(newStudent);
    int newValue = hashFunction(tempNode->getStudent()->getID(), newSize); 
    myList[newValue] = tempNode;
    cout << "Student added." << endl;
  } 
}
      
int hashFunction(int id, int listSize) {
  int value = id % listSize;
  return value;
}


void printStudent(Node** myList, Node* headNode) {
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
