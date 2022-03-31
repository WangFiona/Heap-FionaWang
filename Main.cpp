#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

/*
 * Author: Fiona Wang
 * Date: March 31st, 2022
 * This code takes in a file or user input and sorts it using a max heap
 */

//Declaring functions
void generate(int* &heap);
void userInput(int* & heap);
void add(int* &heap, int data, int index); //Recursive
void printTree(int* heap, int index, int depth, int size);
void printOutput(int* &heap, int &size, int* &output, int &x);

int main(){
  //Initializing variables
  int* heap = new int[100];
  char command[15];

  //Ask the user if they are using a file or input
  cout << "Would you like to generate numbers or input your own?" <<
    " (Enter 'generate' or 'input')" << endl;
  cin >> command;

  //Empty out the heap
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
    userInput(heap);
  }
  else {
    cout << "Not a valid command" << endl;
  }
  
  return 0;
}

//Function to generate numbers using a file
void generate(int* &heap){
  int* output = new int[100];
  char* fileName = new char[20];

  //Empty out the output
  for(int i=0; i<1000; i++){
    output[i] = 0;
  }

  //Ask the user to enter the file name
  cout << "Enter the name of the file: (include the '.txt')" << endl;
  cin >> fileName;
  fstream file;
  file.open(fileName);

  //Extract numbers from the file
  int input = 0;
  int inputNum = 1;
  while(file >> input){
    add(heap, input, inputNum);
    inputNum++;
  }
  file.close();

  /*for(int i=1; i<inputNum; i++){
    cout << heap[i] << " ";
  }
  cout << endl;*/

  //Print out the visual tree
  int x = 0;
  int temp = inputNum;
  inputNum--;
  cout << "Visual Tree:" << endl;
  printTree(heap, 1, 0, inputNum);
  cout << endl;

  //Print out the output (biggest to smallest)
  printOutput(heap, inputNum, output, x);
  cout << "Output:" << endl;
  for(int i=0; i<temp-1; i++){
    cout << output[i] << " ";
  }
  cout << endl;
}

//Function to take numbers from the user
void userInput(int* &heap){
  int* output = new int[100];
  bool entering = true;
  char input[10];

  //Empty out the output
  for(int i=0; i<1000; i++){
    output[i] = 0;
  }

  //Ask the user for numbers or the word "done"
  cout
    << "Enter a number (1-1000) or enter \"done\" to print the tree and output"
       << endl;
  int inputNum = 1;
  //Keep asking for input until the user enters "done"
  while(entering){
    cin >> input;
    //Allow both upper and lower case
    for(int i=0; i < strlen(input); i++) {
      input[i] = toupper(input[i]);
    }

    //Check if the input is a number or "done"
    bool isNum = true;
    for(int i=0; i<strlen(input); i++){
      if(!isdigit(input[i])){
	isNum = false;
      }
    }

    //If the user is done, print out the tree and output
    if(strcmp(input, "DONE") == false){
      int x = 0;
      int temp = inputNum;
      inputNum--;
      //Print out the tree
      cout << "Visual Tree:" << endl;
      printTree(heap, 1, 0, inputNum);
      cout << endl;

      //Print out the output (biggest to smallest)
      printOutput(heap, inputNum, output, x);
      cout << "Output: " << endl;
      for(int i=0; i<temp-1; i++){
	cout << output[i] << " ";
      }
      cout << endl;
      entering = false;
    }
    //Keep asking for numbers
    else if(!isNum){
      cout
	<< "Enter a number (1-1000)"
	<< " or enter \"done\" to print the tree and output"
       << endl;
    }
    else{
      int num = atoi(input);
      add(heap, num, inputNum);
      cout
        << "Enter a number (1-1000)"
        << " or enter \"done\" to print the tree and output"
       << endl;
      inputNum++;
    }
  }
}

//Function to add numbers one by one into the heap
void add(int* &heap, int data, int index){
  if(index > 1){ //Check that it is not the root
    heap[index] = data;
    int parentIndex = index/2;
    int parentData = heap[parentIndex];
    if(data > parentData){ //If the new number is bigger, swap
      heap[parentIndex] = data;
      heap[index] = parentData;
      //Continue recursively
      add(heap, data, parentIndex);
    }
  } else{
    heap[index] = data;
  }
}

//Function to print out the visual tree
void printTree(int* heap, int index, int depth, int size){
  //Go through the right
  if(index*2+1 <= size && heap[index*2+1] != 0){
    printTree(heap, index*2+1, depth+1, size);
  }

  //Print with right amount of tabs
  for(int i = 0; i<depth; i++){
    cout << "\t";
  }
  cout << heap[index] << endl;

  //Go through the left
  if(index*2 <= size && heap[index*2] != 0){
    printTree(heap, index*2, depth+1, size);
  }
}

//Function to print out the output (biggest to smallest)
void printOutput(int* &heap, int &size, int* &output, int &x){
  //Initialize the variables
  int num = heap[size];
  output[x] = heap[1];
  heap[1] = num;
  heap[size] = 0;
  size--;
  x++;

  //While loop to keep switching the bottom number
  int ind = 1;
  while(heap[ind*2] != 0){
    if(num < heap[ind*2] || num < heap[ind*2+1]){
      if(heap[ind*2+1] > heap[ind*2]){ //If the right > left
	//Swap with right
	heap[ind] = heap[ind*2+1];
        heap[ind*2+1] = num;
        ind = ind*2+1;
      } else {
	//Swap with left
	heap[ind] = heap[ind*2];
        heap[ind*2] = num;
        ind = ind*2;
      }
    } else {
      break;
    }
  }

  //Recursively go through the array
  if(size > 1){
    printOutput(heap, size, output, x);
  } else if(size == 1){
    output[x] = heap[1];
  } else {
    return;
  }
}
