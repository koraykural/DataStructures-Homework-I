/* @Author
Student Name: Bekir Koray Kural
Student ID: 150170053
Date: 8.10.2019 */

#include <iostream>
#include <stdlib.h> 
#include <stdio.h>

using namespace std;

struct node{
  int  size;
  int  quant;
  node *next;
};

struct Stock{
  node *head;
  void add_stock(int);
  void sell(int);
  void current_stock();
  void clear();
} shoe_stock;




void Stock::add_stock(int size) {

  // List is empty
  if(shoe_stock.head == NULL) {
    node *newnode = new node;
    shoe_stock.head = newnode;
    newnode->next = NULL;
    newnode->quant = 1;
    newnode->size = size;
    return;
  }

  // Size is smaller than the current smallest size
  if(size < shoe_stock.head->size) {
    node *newnode = new node;
    newnode->next = shoe_stock.head;
    newnode->size = size;
    newnode->quant = 1;
    shoe_stock.head = newnode;
    return;
  }
  
  // Move until find the correct place
  node *traverse = shoe_stock.head;
  node *previous = NULL;
  while((traverse != NULL) && traverse->size < size) {
    previous = traverse;
    traverse = traverse->next;
  }

  // Size is larger than the current largest size
  if((traverse == NULL)) {
    node *newnode = new node;
    newnode->next = NULL;
    newnode->quant = 1;
    newnode->size = size;
    previous->next = newnode;
    return;
  }

  // A node exists with that exact size
  else if (traverse->size == size) {
    traverse->quant += 1;
    return;
  }

  // A node does not exist with that size
  else {
    node *newnode = new node;
    previous->next = newnode;
    newnode->next = traverse;
    newnode->quant = 1;
    newnode->size = size;
    return;
  }
}



void Stock::sell(int size) {

  // List is empty
  if(shoe_stock.head == NULL) {
    cout << "NO_STOCK" << endl;
    return;
  }

  // Head is sold
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
  node *previous = NULL;
  while((traverse != NULL) && traverse->size < size) {
    previous = traverse;
    traverse = traverse->next;
  }

  // If a node exists with exact size
  if ((traverse != NULL) && traverse->size == size) {
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



void Stock::current_stock() {
  node *traverse = shoe_stock.head;
  while(traverse) {
    cout << traverse->size << ':' << traverse->quant << endl;
    traverse = traverse->next;
  }
}



void Stock::clear() {
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

  // Open file to read
  FILE *stock_records;
  if ( !(stock_records = fopen( file_name, "r+" ) ) ) {
    cerr << "File could not be opened" << endl;
    exit(1);
	}


  shoe_stock.head = NULL;

  // Read instruction and perform operation for each, one by one
  int instruction;
  while (1) {
		fscanf(stock_records, "%d", &instruction); 

    if(instruction > 0) 
      shoe_stock.add_stock(instruction);
    else if(instruction < 0)
      shoe_stock.sell(instruction * -1); // Send absolute value
    else 
      shoe_stock.current_stock(); // Instruction == 0

    if ( feof(stock_records) ) break;
	}

  shoe_stock.clear();
  fclose(stock_records);

  return EXIT_SUCCESS;
}