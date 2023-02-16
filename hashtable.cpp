// This is a Hashtable that's used to store student information. Last modified by Jason Randolph on 2-17-13.
// Imports
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "node.h"
#include "student.h"

using namespace std;

// Prototypes
void addStudent(Node** myList, int hashFunctionValue, Student* newStudent);
int hashFunction(int id, int listSize);
void printStudent(Node** myList, int listSize);
bool collisionChecker(Node** list, int hashFunctionValue);
void reHash(int listSize, int newListSize, Node** &list, Node** temp);
void deleteStudent(Node** &myList, Node* headNode, int hashFunctionValue, int myID); 
int generateRandom(Node** &myList, int listSize, int studentNum);

// Initializing variables
int main() {
  char input[20];
  bool active = true;
  int listSize = 100;
  
  // Help from Galbraith with node double pointer/array logic
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
    cout << "\nYour options are \"ADD,\" \"DELETE,\" \"PRINT,\" \"RANDOM,\" and \"QUIT.\"" << endl;
    cin >> input;
    cin.clear();
    cin.ignore(10000, '\n');
    
    // If input is ADD...
    if(strcmp(input, "ADD") == 0){
      
      // Create new student and get information. Also get the hash (aka array index)
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
      
      // Checks for a collision
      if(collisionChecker(list, hash) == true) {
        
        // If there is a collision, create a pointer to a new array with twice the original size. Set all indices in the array to NULL
	      int newListSize = listSize * 2;
	      Node** temp = new Node*[newListSize];
        
        for(int j = 0; j < newListSize; j++) {
          temp[j] = NULL;
        }
        
        // Rehash existing students into new array, create another hash for the new student, and insert it into the new array. Then, update list size
        reHash(listSize, newListSize, list, temp);
	      hash = hashFunction(myID, newListSize);
	      addStudent(list, hash, newStudent);
	      listSize = newListSize;
      } else {
        
        // If no collision, just add new student.
	      addStudent(list, hash, newStudent);
	      cout << "Student added." << endl;
      }
    } else if(strcmp(input, "DELETE") == 0){
      
      // Get the ID of the student
      int deleteID;
      cout << "What is the ID of the user you'd like to delete?" << endl;
      cin >> deleteID;
      
      // Convert to hash and see if student exists
      hash = hashFunction(deleteID, listSize);
      if(list[hash] == NULL) {
        cout << "There is no student that matches this ID." << endl;
      } else {
        
        // If so, delete the student
        Node* headNode = list[hash];
        deleteStudent(list, headNode, hash, deleteID);
      }
    } else if(strcmp(input, "PRINT") == 0){
      printStudent(list, listSize);
    } else if(strcmp(input, "QUIT") == 0){
      active = false;
    } else if(strcmp(input, "RANDOM") == 0){
      int studentNum; 
      cout << "How many students would you like to generate?" << endl;
      cin >> studentNum;
      listSize = generateRandom(list, listSize, studentNum);
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
    Node* tempNode = new Node(newStudent);
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

void deleteStudent(Node** &myList, Node* headNode, int hashFunctionValue, int myID) { 
  if(headNode->getStudent()->getID() == myID && headNode->getNext() == NULL) {
    delete headNode;
    myList[hashFunctionValue] = NULL;
    cout << "Student deleted." << endl;
  } else if (headNode->getNext()->getStudent()->getID() == myID && headNode->getNext()->getNext() != NULL) {
    Node* tempNode = headNode->getNext();
    headNode->setNext(headNode->getNext()->getNext());
    delete tempNode;
    cout << "Student deleted." << endl;
  } else if(headNode->getNext()->getStudent()->getID() == myID && headNode->getNext()->getNext() == NULL) {
    Node* tempNode2 = headNode->getNext();
    headNode->setNext(NULL);
    delete tempNode2;
    cout << "Student deleted." << endl;
  } else if (headNode->getStudent()->getID() == myID && headNode->getNext() != NULL) {
    Node* tempNode3 = headNode;
    headNode = headNode->getNext();
    myList[hashFunctionValue] = headNode;
    delete tempNode3;
    cout << "Student deleted." << endl;
  } else {
    Node* tempNode4 = headNode->getNext();
    deleteStudent(myList, tempNode4, hashFunctionValue, myID);   
  }
}

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

// File-reading help from https://cplusplus.com/forum/beginner/8388/
int generateRandom(Node** &myList, int listSize, int studentNum) {
  for(int k = 0; k < studentNum; k++) {
    ifstream firstNameFile;
    ifstream lastNameFile;
    firstNameFile.open("first.txt");
    lastNameFile.open("last.txt");
    char name[20];
  
    Student* newStudent = new Student();
    
    // srand((unsigned) time(NULL));
  	int randomLine = rand() % 20;
    
    if(firstNameFile.is_open() == true) {
      for(int a = 0; a < 20; a++) {
        if(a != randomLine){
          firstNameFile >> name; 
        } else {
          strcpy(newStudent->getFirstName(), name);
        }
      }
    }
    
    randomLine = rand() % 20;
    if(lastNameFile.is_open() == true) {
      for(int b = 0; b < 20; b++) {
        if(b != randomLine){
          lastNameFile >> name; 
        } else {
          strcpy(newStudent->getLastName(), name);
        }
      }
    }
    firstNameFile.close();
    lastNameFile.close();
  
    // Help with random number generator from https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus
  	// srand((unsigned) time(NULL));
  	float gpa = rand() % 500;
    gpa = gpa / 100;
    newStudent->setGPA(gpa);
  
    int id = 100000 + k;
    bool idExists = true;
    int idMatches;
    // Thanks to Vatsal Parikh for helping with NULL logic
    while(idExists == true) {
      idMatches = 0;
      for(int i = 0; i < listSize; i++) {
        if(myList[i] != NULL && myList[i]->getStudent()->getID() == id) {
          idMatches++;
        }
        if(myList[i] != NULL && myList[i]->getNext() != NULL && myList[i]->getNext()->getStudent()->getID() == id) {
          idMatches++;
        }
        if(myList[i] != NULL && myList[i]->getNext() != NULL && myList[i]->getNext()->getNext() != NULL && myList[i]->getNext()->getNext()->getStudent()->getID() == id) {
          idMatches++; 
        }
      }
      if(idMatches == 0) {
          idExists = false;
      } else {
          id++;
      }
    }
    newStudent->setID(id);
      
    int hash = hashFunction(id, listSize);
    if(collisionChecker(myList, hash) == true) {
      int newListSize = listSize * 2;
      Node** temp = new Node*[newListSize];
      for(int j = 0; j < newListSize; j++) {
        temp[j] = NULL;
      }
      reHash(listSize, newListSize, myList, temp);
      hash = hashFunction(id, newListSize);
      addStudent(myList, hash, newStudent);
      listSize = newListSize;
    } else {
      addStudent(myList, hash, newStudent);
    }
  }
  return listSize;
}
