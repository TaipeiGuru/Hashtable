#include <iostream>
#include <cstring>

using namespace std;

void addStudent(Node* &headNode, Student* newStudent);
void printStudent(Node* headNode);
void deleteStudent(Node* &headNode, int myID); 

int main() {
  char input[20];
  bool active = true;
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

void addStudent(Node* &headNode, Student* newStudent) {
   
}

void printStudent(Node* headNode) {
 
}

void deleteStudent(Node* &headNode, int myID) {

}
