/* @Author
Student Name: Bekir Koray Kural
Student ID: 150170053
Date: 8.10.2019 */

#include <iostream> // allows program to perform input and output
#include <stdlib.h> // contains function prototypes for memory allocation 

using namespace std;

struct node{
  int  size;
  int  quant;
  node *next;
};

struct stock{
  node *head;
  void create();
  void add_stock(int);
  void sell(int);
  void current_stock();
  void clear();
} shoe_stock;

void stock::create() {
  shoe_stock.head = NULL;
}
 
void stock::add_stock(int size) {
  // If list is empty
  if(shoe_stock.head == NULL) {
    node *newnode = new node;
    shoe_stock.head = newnode;
    newnode->next = NULL;
    newnode->quant = 1;
    newnode->size = size;
    return;
  }
  
  // Move until find the correct place
  node *traverse = shoe_stock.head;
  node *previous = shoe_stock.head;
  while(traverse && traverse->size < size) {
    previous = traverse;
    traverse = traverse->next;
  }

  // If a node exists with exact size
  if (traverse && traverse->size == size) {
    traverse->quant += 1;
    return;
  }

  else if(previous->size == size) {
    previous->quant += 1;
    return;
  }

  // Size is smaller than heads size
  else if(size < shoe_stock.head->size) {
    node *newnode = new node;
    shoe_stock.head = newnode;
    newnode->next = traverse;
    newnode->quant = 1;
    newnode->size = size;
    return;
  }

  else {
    node *newnode = new node;
    newnode->next = traverse;
    previous->next = newnode;
    newnode->quant = 1;
    newnode->size = size;
    return;
  }

}

void stock::sell(int size) {
  // If list is empty
  if(shoe_stock.head == NULL) {
    cout << "NO_STOCK" << endl;
    return;
  }

  // If head is need to be deleted
  if(size == shoe_stock.head->size) {
    if(shoe_stock.head->quant == 1) {
      node *traverse = shoe_stock.head->next;
      delete shoe_stock.head;
      shoe_stock.head = traverse;
    }
    else {
      shoe_stock.head->quant -= 1;
    }
    return;
  }

  // Move until find the correct place
  node *traverse = shoe_stock.head;
  node *previous = shoe_stock.head;
  while(traverse && traverse->size < size) {
    previous = traverse;
    traverse = traverse->next;
  }

  // If a node exists with exact size
  if (traverse && traverse->size == size) {
    if(traverse->quant > 1) {
      traverse->quant -= 1;
    }
    else {
      previous->next = traverse->next;
      delete traverse;
    }
  }
  else {
    cout << "NO_STOCK" << endl;
  }
}

void stock::current_stock() {
  node *traverse = shoe_stock.head;
  while(traverse) {
    cout << traverse->size << ':' << traverse->quant << endl;
    traverse = traverse->next;
  }
}

void stock::clear() {
  node *traverse = shoe_stock.head;
  while(traverse) {
    traverse = shoe_stock.head->next;
    delete shoe_stock.head;
    shoe_stock.head = traverse;
  }
}




int main(int argc, char *argv[]) {

  // Get file_name from command line
  if(argc != 2) {
    cerr << "One argument is expected!" << endl;
			exit(1);
  }
  const char* file_name = argv[1];

  shoe_stock.create();

  // Open file to read
  FILE *stock_records;
  if ( !(stock_records = fopen( file_name, "r+" ) ) ) {
    cerr << "File could not be opened" << endl;
    exit(1);
	}
  
  // Create a string to hold numbers and their sign  
  char num_string[4] = "\0\0\0"; 
  
  // Read characther by characther
  char read_char;
  while (1) {
		fread( &read_char, sizeof(char), 1, stock_records);  
    if ( feof(stock_records) ) break;

    // Possibilities for read_char:
    if(read_char == '-') { // Minus sign
      num_string[0] = '-';
    }

    else if(read_char - '0' >= 0 && read_char - '0' < 10) { //digit
      if(num_string[0] == '\0') {
        num_string[0] = read_char;
      }
      else if(num_string[0] == '-') {
        if(num_string[1] == '\0') {
          num_string[1] = read_char;
        }
        else {
          num_string[2] = read_char;
        }
      }
      else {
        num_string[1] = read_char;
      }
    }

    else { // whitespace OR newline
      // Convert num_string to int
      int num = atoi(num_string);
      // Reset num_string
      num_string[0] = '\0';
      num_string[1] = '\0';

      // Perform operation (add, sell, current)
      if(num == 0) {
        shoe_stock.current_stock();
      }
      else if(num < 0) {
        shoe_stock.sell(num * -1); // Send absolute
      }
      else {
        shoe_stock.add_stock(num);
      }
    }
	}

  // Check if there is one last 0
  //if(num_string[0] == 0) {
    shoe_stock.current_stock();
  //}


  shoe_stock.clear();
  return EXIT_SUCCESS;
}