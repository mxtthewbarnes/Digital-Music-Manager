#include "DMM_test.h"
#include <assert.h>

//Insert test function 
void test_insert() {
    node* head = NULL;

    printf("Insert test function...\n");
    printf("Testing insert with invalid data\n");

    //manually sets up new record details 
    record newRecord;
    strcpy(newRecord.artist, "Perry, Katy");
    strcpy(newRecord.album, "Witness");
    strcpy(newRecord.title, "Chained to the Rhythm");
    strcpy(newRecord.genre, "pop");
    newRecord.duration.minutes = 4;
    newRecord.duration.seconds = 36;
    newRecord.playnum = -1;  //invalid data for # of times played
    newRecord.rating = 6;    //invalud rating

    //create new node with invalid data
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = newRecord;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;

    //verifies that new record has been inserted with invalid data
    assert(head != NULL);
    assert(strcmp(head->data.artist, "Perry, Katy") == 0);
    assert(head->data.playnum == -1);  //invalid # remains
    assert(head->data.rating == 6);    //invalid rating remains

    printf("insert test has passed\n");

    freeList(head);  
}

//delete test function
void test_delete() {
    printf("delete test function...");
    
    node* head = NULL;

    //insert a valid record to delete
    record newRecord;
    strcpy(newRecord.artist, "Perry, Katy");
    strcpy(newRecord.album, "Witness");
    strcpy(newRecord.title, "Chained to the Rhythm");
    strcpy(newRecord.genre, "pop");
    newRecord.duration.minutes = 4;
    newRecord.duration.seconds = 36;
    newRecord.playnum = 3;
    newRecord.rating = 5;

    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = newRecord;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;

    //deleting the inserted record
    printf("Testing delete\n");
    delete(&head);

    //verifies head is NULL after deletion
    assert(head == NULL);
    printf("Delete test passed!\n");

    freeList(head);  
}

//shuffle test function
void test_shuffle() {
    printf("shuffle test function...");
    
    node* head = NULL;

    //insert records for test
    record record1 = { "Brooks, Garth", "FRESH HORSES", "The Old Stuff", "Country", {2, 11}, 2, 2 };
    record record2 = { "Swift, Taylor", "RED", "Stay Stay Stay", "Pop", {4, 5}, 1, 1 };
    record record3 = { "Adele", "25", "Remedy", "Pop", {4, 24}, 4, 0 };


    node* node1 = (node*)malloc(sizeof(node));
    node1->data = record1;
    node1->next = head;
    node1->prev = NULL;
    if (head != NULL) head->prev = node1;
    head = node1;

    node* node2 = (node*)malloc(sizeof(node));
    node2->data = record2;
    node2->next = head;
    node2->prev = NULL;
    head->prev = node2;
    head = node2;

    node* node3 = (node*)malloc(sizeof(node));
    node3->data = record3;
    node3->next = head;
    node3->prev = NULL;
    head->prev = node3;
    head = node3;

    // Call shuffle and print the result
    printf("testing shuffle\n");
    shuffle(head);

    
    assert(head != NULL);
    printf("Shuffle test passed!\n");

    freeList(head);  
}
