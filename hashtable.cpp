// This is a Hashtable that's used to store student information. All other files are the same as in LinkedLists2. Last modified by Jason Randolph on 2-17-13.
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

    // If input is print, printStudent
    } else if(strcmp(input, "PRINT") == 0){
      printStudent(list, listSize);
	    
    // If input is QUIT, end the while loop
    } else if(strcmp(input, "QUIT") == 0){
      active = false;
      
    /* If input is random, ask for the number of students and then call the generator function. Also update listSize in case collisions occur
     * during random generation */
    } else if(strcmp(input, "RANDOM") == 0){
      int studentNum; 
      cout << "How many students would you like to generate?" << endl;
      cin >> studentNum;
      listSize = generateRandom(list, listSize, studentNum);
    } else if(strcmp(input, "NIVIDH") == 0){
      cout << "Greetings, Cambodian rizzler!" << endl;
    } else {
      cout << "Invalid input." << endl;
    }
  }
  return 0;
}

/* Add student function. If the index of the student's hash is empty, make a new node containing that student and insert it. If not, 
 * check the next two linked nodes to see if any exist. If not, put the new student there. */
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

/* Rehash function. If the index in the old array isn't empty, copy it to a new node, hash the student at that node, and add the student
 * to the new array. Then, change the node to its next node to account for any chained students. Help on this from Vatsal Parikh */
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
  
  // Delete the old list and set list equal to the new array
  delete[] list;
  list = temp;
}

// Hash function, uses modulo. ID modulo listSize is returned
int hashFunction(int id, int listSize) {
  int value = id % listSize;
  return value;
}

// Print student function. For each slot in the array, check for the existence of nodes (and chained nodes). If there are any, get the student and print. 
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

// Delete student function. Virtually the same as that of LinkedLists 2
void deleteStudent(Node** &myList, Node* headNode, int hashFunctionValue, int myID) { 
  
  // If there's only one node at that index, the node is deleted and that index is set to NULL
  if(headNode->getStudent()->getID() == myID && headNode->getNext() == NULL) {
    delete headNode;
    myList[hashFunctionValue] = NULL;
    cout << "Student deleted." << endl;
    
  // If there are three nodes at that index and the middle one matches the ID, set the headNode's next to the third node and delete the second
  } else if (headNode->getNext()->getStudent()->getID() == myID && headNode->getNext()->getNext() != NULL) {
    Node* tempNode = headNode->getNext();
    headNode->setNext(headNode->getNext()->getNext());
    delete tempNode;
    cout << "Student deleted." << endl;
    
  // If there are two nodes at that index and the second one matches the ID, delete the second and set the headNode's next to NULL
  } else if(headNode->getNext()->getStudent()->getID() == myID && headNode->getNext()->getNext() == NULL) {
    Node* tempNode2 = headNode->getNext();
    headNode->setNext(NULL);
    delete tempNode2;
    cout << "Student deleted." << endl;
    
  // If there are two nodes at that index and the first one matches the ID, set the second node as the headNode and then delete the first
  } else if (headNode->getStudent()->getID() == myID && headNode->getNext() != NULL) {
    Node* tempNode3 = headNode;
    headNode = headNode->getNext();
    myList[hashFunctionValue] = headNode;
    delete tempNode3;
    cout << "Student deleted." << endl;
    
  // Otherwise, use recursion to run through the nodes again
  } else {
    Node* tempNode4 = headNode->getNext();
    deleteStudent(myList, tempNode4, hashFunctionValue, myID);   
  }
}

// Collision checker function. If there are three nodes at a certain index, return true. Else, return false
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

// Random student generator. File-reading help from https://cplusplus.com/forum/beginner/8388/
int generateRandom(Node** &myList, int listSize, int studentNum) {
  // Generate seed. Help with this from Galbraith
  srand(time(NULL));
  
  for(int k = 0; k < studentNum; k++) {
    
    // Create objects for first and last name files
    ifstream firstNameFile;
    ifstream lastNameFile;
    
    // Open both files
    firstNameFile.open("first.txt");
    lastNameFile.open("last.txt");
    char name[20];
  
    // Create a new student
    Student* newStudent = new Student();

    // Initialize random line
    int randomLine = rand() % 20;
    /* If the file is open and the reader reaches the randomly generated line, copy that name into the student's first name slot. 
     * Otherwise, put that name into a char array and continue on */
    if(firstNameFile.is_open() == true) {
      for(int a = 0; a < 20; a++) {
        if(a != randomLine){
          firstNameFile >> name; 
        } else {
          strcpy(newStudent->getFirstName(), name);
        }
      }
    }
    
    // Repeat the above for last name
    int randomLine2 = rand() % 20;
    if(lastNameFile.is_open() == true) {
      for(int b = 0; b < 20; b++) {
        if(b != randomLine2){
          lastNameFile >> name; 
        } else {
          strcpy(newStudent->getLastName(), name);
        }
      }
    }
    
    // Close both files
    firstNameFile.close();
    lastNameFile.close();
  
    // Help with random number generator from https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus
  	float gpa = rand() % 500;
    gpa = gpa / 100;
    newStudent->setGPA(gpa);
  
    // ID generation. Starts at 100000 and adds k with each iteration, causing the ID to be incremented by 1 for each student
    int id = 100000 + k;
    bool idExists = true;
    
    // Initialize counter
    int idMatches;
    
    // This checks to see if a randomly generated ID already exists in the Hashtable. Thanks to Vatsal Parikh for helping with NULL logic
    while(idExists == true) {
      
      // Set counter to 0
      idMatches = 0;
      
      // For each index in the array...
      for(int i = 0; i < listSize; i++) {
        
        // If that spot isn't NULL and the ID matches, increment the counter
        if(myList[i] != NULL && myList[i]->getStudent()->getID() == id) {
          idMatches++;
        }
        
        // If that spot isn't NULL, the second node isn't NULL, and the second node's ID matches, increment the counter
        if(myList[i] != NULL && myList[i]->getNext() != NULL && myList[i]->getNext()->getStudent()->getID() == id) {
          idMatches++;
        }
        
        // If that spot isn't NULL, the second node isn't NULL, the third isn't NULL, and the third node's ID matches, increment the counter
        if(myList[i] != NULL && myList[i]->getNext() != NULL && myList[i]->getNext()->getNext() != NULL && myList[i]->getNext()->getNext()->getStudent()->getID() == id) {
          idMatches++; 
        }
      }
      
      // If the counter is equal to 0 (indicating that the ID doesn't already exist), end the while loop. Otherwise, increment the ID by one and try again
      if(idMatches == 0) {
          idExists = false;
      } else {
          id++;
      }
    }
    newStudent->setID(id);
      
    // Create a hash for the ID and check for collisions. Collision logic is the same as above when we were adding new students
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
  
  // List size is returned since the listSize is stored in main and will need to be updated if any collisions occur in this scope 
  return listSize;
}
