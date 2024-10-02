#include "DMM.h"
#include "DMM_test.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    
                 /*   ----------------------
                        Test functions
                     ----------------------     */
                        //test_insert();
                        // test_delete();
                         //test_shuffle();
    
    node* head = NULL;
    int choice;

    do {
        menu();
        printf("\n\tEnter your choice: \n\t");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            load("musicPlayList.csv", &head);
            break;
        case 2:
            store("musicPlayList.csv", head);
            break;
        case 3:
            display(head);
            break;
        case 4:
            insert(&head);
            break;
        case 5:
            delete(&head);
            break;
        case 6:
            edit(head);
            break;
        case 7:
            sort(&head);
            break;
        case 8:
            rate(head);
            break;
        case 9:
            play(head);
            break;
        case 10:
            shuffle(head);
            break;
        case 11:
            exitProgram(head);
            break;
        default:
            printf("Please select a number 1-11.\n");
        }
    } while (choice != 11);

    return 0;
}
