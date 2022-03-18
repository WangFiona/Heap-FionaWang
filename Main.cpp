#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void generate(int* &heap);
void userInput(int* & heap);
void add(int* &heap, int data, int index); //Recursive
void printTree(int* heap);
void printOutput(int* &heap, int data, int index); //Recursive

int main(){
  int* heap = new int[100];
  char* command = new char[15];

  cout << "Would you like to generate numbers or input your own?" <<
    " (Enter 'generate' or 'input')" << endl;
  cin >> command;

  for(int i=0; i<1000; i++){
    heap[i] = 0;
  }
  
  //Allow both upper and lower case
  for(int i=0; i < strlen(command); i++) {
    command[i] = toupper(command[i]);
  }
  
  if(strcmp(command, "GENERATE") == false){
    generate(heap);
  }
  else if(strcmp(command, "INPUT") == false){
    //add(heap);
  }
  else {
    cout << "Not a valid command" << endl;
  }
  
  return 0;
}

void generate(int* &heap){
}

void userInput(int* &heap){
}
