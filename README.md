# Smart Ration Distribution System

A comprehensive C-based application for managing and distributing monthly rations to families using advanced data structures including Binary Search Trees (BST), Queues, and Stacks.

##  Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Data Structures Used](#data-structures-used)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Ration Allocation Formula](#ration-allocation-formula)
- [Menu Options](#menu-options)
- [File Structure](#file-structure)
- [Example Workflow](#example-workflow)
- [Error Handling](#error-handling)

##  Overview

The Smart Ration Distribution System is designed to efficiently manage ration allocation and distribution for families classified as BPL (Below Poverty Line) and APL (Above Poverty Line). The system ensures fair distribution, tracks inventory, and provides comprehensive reporting features.

##  Features

- **Family Registration** with auto-generated unique IDs
- **Smart Allocation** based on family type (BPL/APL) and member count
- **Stock Management** with real-time inventory tracking
- **Queue-based Distribution** ensuring first-come-first-served fairness
- **Undo Functionality** for last ration issue using Stack
- **Comprehensive Reporting** for all families and allocated families
- **Duplicate Prevention** to avoid re-allocation or re-distribution
- **Stock Empty Alert** when insufficient ration is available

##  Data Structures Used

### 1. Binary Search Tree (BST)
- **Purpose**: Store and manage family records
- **Key**: Family ID (sorted)
- **Operations**: Insert, Search, Inorder Traversal
- **Advantage**: O(log n) search time for efficient family lookup

### 2. Queue (Linked List Implementation)
- **Purpose**: Maintain distribution order (FIFO)
- **Operations**: Enqueue, Dequeue, Peek, isEmpty
- **Usage**: Families waiting for ration distribution

### 3. Stack (Linked List Implementation)
- **Purpose**: Track issued rations for undo operation (LIFO)
- **Operations**: Push, Pop
- **Usage**: Undo last distribution transaction

##  System Requirements

- GCC Compiler (or any C compiler)
- Terminal/Command Prompt
- Operating System: Linux, macOS, or Windows

##  Installation

1. **Clone or download the project files**
```bash
# Create a project directory
mkdir ration_system
cd ration_system
```

2. **Ensure you have all three files**
- `ration.h` - Header file with declarations
- `ration.c` - Implementation file
- `main.c` - Main program file

3. **Compile the program**
```bash
gcc main.c ration.c -o ration_system
```

4. **Run the program**
```bash
./ration_system
```

### Alternative Compilation Methods

**Method 2: Separate Compilation**
```bash
gcc -c ration.c -o ration.o
gcc -c main.c -o main.o
gcc ration.o main.o -o ration_system
./ration_system
```

**Method 3: Using Makefile**
```makefile
CC = gcc
CFLAGS = -Wall -g

ration_system: main.o ration.o
	$(CC) $(CFLAGS) main.o ration.o -o ration_system

main.o: main.c ration.h
	$(CC) $(CFLAGS) -c main.c

ration.o: ration.c ration.h
	$(CC) $(CFLAGS) -c ration.c

clean:
	rm -f *.o ration_system
```

Then run:
```bash
make
./ration_system
```

##  Usage

### Initial Setup
When you start the program, you'll be prompted to enter the total ration stock available:
```
Enter Total Ration Stock Available: 5000
```

### Main Menu
```
============================================
  SMART RATION DISTRIBUTION SYSTEM
============================================
1. Register New Family
2. Allocate Monthly Ration
3. Add Family to Distribution List
4. Distribute Ration (Next in Line)
5. Undo Last Distribution
6. View All Family Records
7. View Families with Allocated Ration
8. View Stock Summary
9. Exit System
```

##  Ration Allocation Formula

```
Allocated Ration = Base Amount × Number of Members × Multiplier
```

Where:
- **Base Amount**: 10 units per person
- **Multiplier**:
  - **BPL (Below Poverty Line)**: 2 → 20 units per person
  - **APL (Above Poverty Line)**: 1 → 10 units per person

### Examples:
- BPL family with 4 members: `10 × 4 × 2 = 80 units`
- APL family with 4 members: `10 × 4 × 1 = 40 units`
- BPL family with 5 members: `10 × 5 × 2 = 100 units`
- APL family with 3 members: `10 × 3 × 1 = 30 units`

##  Menu Options

### 1. Register New Family
- Prompts for family name, type (B/A), and number of members
- Automatically assigns unique Family ID
- Stores in BST

### 2. Allocate Monthly Ration
- Requires Family ID
- Calculates ration based on formula
- Checks for available stock
- **Error Checks**:
  - Family not found
  - Already allocated
  - Insufficient stock (STOCK EMPTY)

### 3. Add Family to Distribution List
- Adds family to queue for distribution
- **Error Checks**:
  - Family not found
  - Ration not allocated yet
  - Already received ration

### 4. Distribute Ration (Next in Line)
- Issues ration to first family in queue (FIFO)
- Marks family as "Received"
- Pushes to undo stack
- Removes from queue

### 5. Undo Last Distribution
- Reverses the last distribution
- Returns family to queue
- Marks as "Pending"

### 6. View All Family Records
- Displays all registered families in sorted order (by ID)
- Shows allocation and distribution status

### 7. View Families with Allocated Ration
- Filters and displays only families with `allocated > 0`
- Uses recursive BST traversal with condition checking

### 8. View Stock Summary
- Total stock available
- Total allocated
- Remaining stock

### 9. Exit System
- Safely exits the program

## 📁 File Structure

```
ration_system/
│
├── ration.h          # Header file with structure definitions and function declarations
├── ration.c          # Implementation of all functions
├── main.c            # Main program with menu loop
└── README.md         # This file
```

### Key Components in Files:

**ration.h**
- Structure definitions (node, stack, queue, family)
- Global variable declarations
- Function prototypes

**ration.c**
- Global variable initialization
- Stack operations (push, pop)
- Queue operations (enqueue, dequeue, peek, isEmpty)
- BST operations (create, insert, search, display)
- System functions (register, allocate, issue, undo, reports)

**main.c**
- Main function with menu loop
- Initialization of global data structures
- User input handling

##  Example Workflow

### Sample Session:
```
1. Initialize stock: 2000 units
2. Register Family: Kumar, BPL, 5 members → ID: 1
3. Register Family: Sharma, APL, 3 members → ID: 2
4. Register Family: Patel, BPL, 4 members → ID: 3

5. Allocate to Kumar (ID: 1) → 100 units allocated
6. Allocate to Sharma (ID: 2) → 30 units allocated
7. Allocate to Patel (ID: 3) → 80 units allocated

8. Add Kumar to queue
9. Add Sharma to queue
10. Add Patel to queue

11. Distribute to Kumar → Status: Received
12. Distribute to Sharma → Status: Received

13. View Stock Summary:
    Total: 2000 | Allocated: 210 | Remaining: 1790

14. Undo last distribution (Sharma)
15. Sharma back in queue with "Pending" status
```

##  Error Handling

The system includes comprehensive error handling for:

### Stock Management Errors
- **Stock Empty**: When trying to allocate more than available stock
- **Invalid Stock Input**: Sets default to 5000 units

### Family Registration Errors
- **Invalid Input**: Validates family type (B/A only)

### Allocation Errors
- **Family Not Found**: Invalid Family ID
- **Already Allocated**: Prevents duplicate allocation
- **Insufficient Stock**: Shows required vs available units

### Queue Errors
- **Not Allocated**: Cannot add to queue without allocation
- **Already Distributed**: Prevents re-entry to queue
- **Empty Queue**: No families waiting for distribution

### Undo Errors
- **No Transaction**: Stack is empty, nothing to undo

##  Learning Outcomes

This project demonstrates:
- **Data Structure Implementation**: BST, Queue, Stack from scratch
- **Memory Management**: Dynamic allocation and deallocation
- **Modular Programming**: Separation of concerns with header files
- **Algorithm Design**: Recursive tree traversal, FIFO/LIFO operations
- **Real-world Application**: Practical government system simulation

##  Contributing

Feel free to fork this project and submit pull requests for improvements such as:
- Additional family information fields
- Advanced reporting features
- File I/O for data persistence
- GUI implementation

##  License

This project is open-source and available for educational purposes.

##  Author

Created as a data structures project demonstrating practical applications of BST, Queue, and Stack.

---

**Note**: This is a console-based application. All data is stored in memory and will be lost when the program exits. For persistent storage, consider adding file I/O operations.
