#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void generate(int* &heap);
void userInput(int* & heap);
void add(int* &heap, int data, int index); //Recursive
void printTree(int* heap);
void printOutput(int* &heap, int &size, int* &output, int &x);

int main(){
  int* heap = new int[100];
  char command[15];

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
    userInput(heap);
  }
  else {
    cout << "Not a valid command" << endl;
  }
  
  return 0;
}

void generate(int* &heap){
  int* output = new int[100];
  char* fileName = new char[20];

  for(int i=0; i<1000; i++){
    output[i] = 0;
  }
  
  cout << "Enter the name of the file: (include the '.txt')" << endl;
  cin >> fileName;
  fstream file;
  file.open(fileName);

  int input = 0;
  int inputNum = 1;
  while(file >> input){
    cout << input << " ";
    add(heap, input, inputNum);
    inputNum++;
  }
  file.close();
  cout << endl;

  for(int i=1; i<inputNum; i++){
    cout << heap[i] << " ";
  }
  cout << endl;
  
  printTree(heap);
  int x = 0;
  int temp = inputNum;
  inputNum--;
  //cout << inputNum << endl;
  printOutput(heap, inputNum, output, x);
  for(int i=0; i<temp-1; i++){
    cout << output[i] << " ";
  }
  cout << endl;
}

void userInput(int* &heap){
  int* output = new int[100];
  bool entering = true;
  char input[10];

  for(int i=0; i<1000; i++){
    output[i] = 0;
  }
  
  cout << "Enter a number or enter \"done\" to print the tree and output"
       << endl;
  int inputNum = 1;
  while(entering){
    cin >> input;
    //Allow both upper and lower case
    for(int i=0; i < strlen(input); i++) {
      input[i] = toupper(input[i]);
    }

    bool isNum = true;
    for(int i=0; i<strlen(input); i++){
      if(!isdigit(input[i])){
	isNum = false;
      }
    }

    if(strcmp(input, "DONE") == false){
      printTree(heap);
      int x = 0;
      printOutput(heap, inputNum, output, x);
      entering = false;
    }
    else if(!isNum){
      cout << "Please enter a number or \"done\"" << endl;
    }
    else{
      int num = atoi(input);
      add(heap, num, inputNum);
      cout << "Enter a number or enter \"done\" to print the tree and output"
	   << endl;
      inputNum++;
    }
  }
}

void add(int* &heap, int data, int index){
  if(index > 1){
    heap[index] = data;
    int parentIndex = index/2;
    int parentData = heap[parentIndex];
    if(data > parentData){
      heap[parentIndex] = data;
      heap[index] = parentData;
      add(heap, data, parentIndex);
    }
  } else{
    heap[index] = data;
  }
}

void printTree(int* heap){
}

void printOutput(int* &heap, int &size, int* &output, int &x){
  int num = heap[size];
  output[x] = heap[1];
  heap[1] = num;
  heap[size] = 0;
  size--;
  x++;
  
  int ind = 1;
  //cout << heap[ind*2] << endl;
  while(heap[ind*2] != 0){// && ind*2+1 <= size){
    if(num < heap[ind*2]){
      if(heap[ind*2+1] > heap[ind*2]){
	heap[ind] = heap[ind*2+1];
        heap[ind*2+1] = num;
        ind = ind*2+1;
	//cout << "index" << ind << endl;
      } else {
	heap[ind] = heap[ind*2];
        heap[ind*2] = num;
        ind = ind*2;
	//cout <<	"index"	<< ind << endl;
      }
    } else {
      break;
    }

    /*if(num < heap[ind*2] || num < heap[ind*2+1]){
      if(num < heap[ind*2]){
	heap[ind] = heap[ind*2];
	heap[ind*2] = num;
	ind = ind*2;
      } else{
	heap[ind] = heap[ind*2+1];
        heap[ind*2+1] = num;
	ind = ind*2+1;
      }
      }*/
  }

  if(size > 1){
    printOutput(heap, size, output, x);
  } else if(size == 1){
    output[x] = heap[1];
    //cout << heap [1];
  } else {
    return;
  }
}
