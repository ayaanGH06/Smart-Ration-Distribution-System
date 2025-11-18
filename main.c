#include "ration.h"

int main() {
    issue_queue.front = issue_queue.rear = NULL;
    issued_stack.top = NULL;

    // Initialize total ration stock at startup
    printf("============================================\n");
    printf("  SMART RATION DISTRIBUTION SYSTEM\n");
    printf("============================================\n");
    init_stock();

    int choice;
    while (1) {
        show_menu();
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1: register_family(); break;
            case 2: allocate_ration(); break;
            case 3: add_to_queue(); break;
            case 4: issue_next_ration(); break;
            case 5: undo_last_issue(); break;
            case 6: show_families(); break;
            case 7: disp_allocated(); break;
            case 8: total_allocated_stock(); break;
            case 9:
                printf("\n Exiting System. Thank you!\n");
                return 0;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}