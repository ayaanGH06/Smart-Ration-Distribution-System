// ration.h
#ifndef RATION_H
#define RATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCTURE DEFINITIONS

// Node for Stack and Queue
typedef struct node {
    int data;
    struct node *next;
} node;

// Stack for undo operation
typedef struct stack {
    node* top;
} stack;

// Queue for distribution order
typedef struct queue {
    node* front;
    node* rear;
} queue;

// Family node (BST)
typedef struct family {
    int ID;
    char name[50];
    char type;     // 'B' = BPL, 'A' = APL
    int members;
    int allocated;
    int issued;
    struct family *left;
    struct family *right;
} family;

//  GLOBAL VARIABLE DECLARATIONS 
extern family *root;          // BST root node
extern queue issue_queue;     // global queue
extern stack issued_stack;    // global stack
extern int nextFamilyID;      // auto ID counter
extern int totalRationStock;  // total available ration
extern int totalAllocated;    // total ration allocated

// FUNCTION DECLARATIONS

// Stack operations
node* push(stack* s, int value);
int pop(stack* s);

// Queue operations
void enqueue(queue* q, int value);
void dequeue(queue* q);
int queue_peek_front(queue* q);
int queue_is_empty(queue* q);

// BST operations
family* create_family(int id, char name[], char type, int members);
family* insert_family(family* root, int id, char name[], char type, int members);
family* search_family(family* root, int id);
void inorder_display(family* root);
void display_allocated_families(family* root);

// System functions
void register_family();
void allocate_ration();
void add_to_queue();
void issue_next_ration();
void undo_last_issue();
void show_families();
void show_menu();
void disp_allocated();
void total_allocated_stock();
void init_stock();

#endif