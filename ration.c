#include "ration.h"

// GLOBAL VARIABLES 
family *root = NULL;          // Root of BST
queue issue_queue;            // Queue for ration distribution
stack issued_stack;           // Stack for undo operation
int nextFamilyID = 1;         // Auto-incrementing family ID
int totalRationStock = 0;     // Total available ration
int totalAllocated = 0;       // Total ration allocated so far

// STACK FUNCTIONS 

// Push ID onto stack
node* push(stack* s, int value) {
    node* new = malloc(sizeof(node));
    new->data = value;
    new->next = s->top;
    s->top = new;
    return s->top;
}

// Pop ID from stack (returns -1 if empty)
int pop(stack* s) {
    if (s->top == NULL) return -1;
    node* prisoner = s->top;
    int val = prisoner->data;
    s->top = prisoner->next;
    free(prisoner);
    return val;
}

// QUEUE FUNCTIONS

// Add a family ID to queue (enqueue)
void enqueue(queue* q, int value) {
    node* new = malloc(sizeof(node));
    new->data = value;
    new->next = NULL;
    if (q->front == NULL && q->rear == NULL) {
        q->front = q->rear = new;
        return;
    }
    new->next = q->rear;
    q->rear = new;
}

// Remove a family ID from queue (dequeue)
void dequeue(queue* q) {
    node * lost_soul = q->front;
    if (lost_soul == NULL) return;
    if (lost_soul == q->rear) {
        free(lost_soul);
        q->front = q->rear = NULL;
        return;
    }
    node* temp = q->rear;
    while (temp->next != q->front)
        temp = temp->next;
    free(q->front);
    q->front = temp;
    q->front->next = NULL;
}

// View the next family in queue (front)
int queue_peek_front(queue* q) {
    if (q->front == NULL) return 0;
    return q->front->data;
}

// Check if queue is empty
int queue_is_empty(queue* q) {
    return (q->front == NULL && q->rear == NULL);
}

// BST FUNCTIONS 

// Create a new family node
family* create_family(int id, char name[], char type, int members) {
    family* new = malloc(sizeof(family));
    new->ID = id;
    strcpy(new->name, name);
    new->type = type;
    new->members = members;
    new->allocated = 0;
    new->issued = 0;
    new->left = new->right = NULL;
    return new;
}

// Insert family into BST based on ID
family* insert_family(family* root, int id, char name[], char type, int members) {
    if (root == NULL)
        return create_family(id, name, type, members);

    if (id < root->ID)
        root->left = insert_family(root->left, id, name, type, members);
    else if (id > root->ID)
        root->right = insert_family(root->right, id, name, type, members);

    return root;
}

// Search family by ID
family* search_family(family* root, int id) {
    if (root == NULL || root->ID == id)
        return root;
    if (id < root->ID)
        return search_family(root->left, id);
    return search_family(root->right, id);
}

// Display BST in sorted order (inorder traversal)
void inorder_display(family* root) {
    if (root == NULL) return;
    inorder_display(root->left);
    printf("%d\t%-10s\t%c\t%d\t%d\t%s\n",
           root->ID, root->name, root->type, root->members,
           root->allocated, root->issued ? "Received" : "Pending");
    inorder_display(root->right);
}

// Display only families that have been allocated ration
void display_allocated_families(family* root) {
    if (root == NULL) return;
    display_allocated_families(root->left);
    if (root->allocated > 0) {
        printf("%d\t%-10s\t%c\t%d\t%d\t%s\n",
               root->ID, root->name, root->type, root->members,
               root->allocated, root->issued ? "Received" : "Pending");
    }
    display_allocated_families(root->right);
}

// SYSTEM FUNCTIONS

// Initialize total ration stock
void init_stock() {
    printf("\nEnter Total Ration Stock Available: ");
    fflush(stdout);
    if (scanf("%d", &totalRationStock) != 1) {
        printf("Invalid input. Setting default stock to 5000 units.\n");
        totalRationStock = 5000;
    }
    printf("\n Total stock set to %d units.\n", totalRationStock);
}

// Register a new family (auto ID generation)
void register_family() {
    char name[50], type;
    int members;

    printf("\nEnter Family Name: ");
    scanf("%s", name);
    printf("Enter Family Type (B for BPL / A for APL): ");
    scanf(" %c", &type);
    printf("Enter Number of Family Members: ");
    scanf("%d", &members);

    if (type >= 'a' && type <= 'z') type -= 32;

    int id = nextFamilyID++;
    root = insert_family(root, id, name, type, members);

    printf("\n Family Registered Successfully!\n");
    printf("   Name: %s | Type: %c | Members: %d | Assigned ID: %d\n",
           name, type, members, id);
}

// Allocate monthly ration to a family
void allocate_ration() {
    int id;
    printf("\nEnter Family ID to Allocate Ration: ");
    scanf("%d", &id);

    family* f = search_family(root, id);
    if (f == NULL) {
        printf(" Family not found.\n");
        return;
    }

    // Check if already allocated
    if (f->allocated > 0) {
        printf(" ERROR: Ration already allocated to this family!\n");
        printf("   Current allocation: %d units\n", f->allocated);
        return;
    }

    int base = 10;
    int multiplier = (f->type == 'B') ? 2 : 1;
    int required = base * f->members * multiplier;

    // Check if enough stock is available
    if (totalAllocated + required > totalRationStock) {
        printf(" ERROR: STOCK EMPTY!\n");
        printf("   Required: %d units | Available: %d units\n", 
               required, totalRationStock - totalAllocated);
        return;
    }

    f->allocated = required;
    f->issued = 0;
    totalAllocated += required;

    printf(" Ration Allocated: %d units for %s (ID: %d)\n",
           f->allocated, f->name, f->ID);
    printf("   Remaining stock: %d units\n", totalRationStock - totalAllocated);
}

// Add family to the queue for distribution
void add_to_queue() {
    int id;
    printf("\nEnter Family ID to Add to Queue: ");
    scanf("%d", &id);

    family* f = search_family(root, id);
    if (f == NULL) {
        printf(" Family not found.\n");
        return;
    }
    if (f->allocated == 0) {
        printf(" ERROR: Please allocate ration first.\n");
        return;
    }
    if (f->issued) {
        printf(" ERROR: Ration already distributed to this family!\n");
        printf("   Family %s (ID: %d) has already received their ration.\n", 
               f->name, f->ID);
        return;
    }

    enqueue(&issue_queue, id);
    printf(" %s added to distribution queue.\n", f->name);
}

// Distribute ration to next family in queue
void issue_next_ration() {
    if (queue_is_empty(&issue_queue)) {
        printf(" No families waiting in queue.\n");
        return;
    }

    int id = queue_peek_front(&issue_queue);
    family* f = search_family(root, id);
    if (f == NULL) {
        dequeue(&issue_queue);
        return;
    }

    f->issued = 1;
    push(&issued_stack, id);
    dequeue(&issue_queue);

    printf(" Ration Issued Successfully!\n");
    printf("   %s (ID: %d) received %d units.\n",
           f->name, f->ID, f->allocated);
}

// Undo the last ration issue (Stack pop)
void undo_last_issue() {
    int id = pop(&issued_stack);
    if (id == -1) {
        printf(" No transaction to undo.\n");
        return;
    }

    family* f = search_family(root, id);
    if (f != NULL) {
        f->issued = 0;
        enqueue(&issue_queue, id);
        printf(" Undone last issue for %s (ID: %d)\n", f->name, f->ID);
    }
}

// Display all family records (BST traversal)
void show_families() {
    if (root == NULL) {
        printf("\nNo families registered yet.\n");
        return;
    }

    printf("\n Registered Families:\n");
    printf("ID\tName\t\tType\tMembers\tAllocated\tStatus\n");
    printf("-----------------------------------------------------------\n");
    inorder_display(root);
}

// Display only families that have been allocated ration
void disp_allocated() {
    if (root == NULL) {
        printf("\nNo families registered yet.\n");
        return;
    }

    printf("\n Families with Allocated Ration:\n");
    printf("ID\tName\t\tType\tMembers\tAllocated\tStatus\n");
    printf("-----------------------------------------------------------\n");
    display_allocated_families(root);
}

// Display total stock information
void total_allocated_stock() {
    printf("\n============================================\n");
    printf("  RATION STOCK SUMMARY\n");
    printf("============================================\n");
    printf("Total Stock Available:  %d units\n", totalRationStock);
    printf("Total Allocated:        %d units\n", totalAllocated);
    printf("Remaining Stock:        %d units\n", totalRationStock - totalAllocated);
    printf("============================================\n");
}

// Print main menu
void show_menu() {
    printf("\n============================================\n");
    printf("  SMART RATION DISTRIBUTION SYSTEM\n");
    printf("============================================\n");
    printf("1. Register New Family\n");
    printf("2. Allocate Monthly Ration\n");
    printf("3. Add Family to Distribution List\n");
    printf("4. Distribute Ration (Next in Line)\n");
    printf("5. Undo Last Distribution\n");
    printf("6. View All Family Records\n");
    printf("7. View Families with Allocated Ration\n");
    printf("8. View Stock Summary\n");
    printf("9. Exit System\n");
    printf("--------------------------------------------\n");
    printf("Select an option: ");
}