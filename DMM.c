//Menu function. Simply prints out the menu to user.
//menu is accessed through switch statement in main().
void menu() {
    printf("\tMain Menu:\n");
    printf("\t(1) load\n");
    printf("\t(2) store\n");
    printf("\t(3) display\n");
    printf("\t(4) insert\n");
    printf("\t(5) delete\n");
    printf("\t(6) edit\n");     
    printf("\t(7) sort\n");
    printf("\t(8) rate\n");
    printf("\t(9) play\n");
    printf("\t(10) shuffle\n");
    printf("\t(11) exit\n");
}


//Load() takes csv file and pointer to the head of doubly linked list as parameters.
// This function opens file for reading, reads each line, and parses the information into the 
// record struct. Each record as inserted at the front of the doubly linked list. 
//  
void load(const char* filename, node** head) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {                     //opening file
        printf("Could not open file.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        record data = { "", "", "", "", {0, 0}, 0, 0 };  

        char* token;

        token = strtok(line, ",");
        strcpy(data.artist, token);

        token = strtok(NULL, ",");
        strcpy(data.album, token);

        token = strtok(NULL, ",");
        strcpy(data.title, token);

        token = strtok(NULL, ",");
        strcpy(data.genre, token);
            
        token = strtok(NULL, ",");
        data.duration.minutes = atoi(token);        //parsing information using strtok() and tokenization

        token = strtok(NULL, ",");
        data.duration.seconds = (token != NULL) ? atoi(token) : 0;

        token = strtok(NULL, ",");
        data.playnum = (token != NULL) ? atoi(token) : 0;

        token = strtok(NULL, ",");
        data.rating = (token != NULL) ? atoi(token) : 0;

        node* newnode = (node*)malloc(sizeof(node));
        newnode->data = data;               
        newnode->next = *head;                  //inserting new records to front of list. 
        newnode->prev = NULL;

        if (*head != NULL) {
            (*head)->prev = newnode;
        }
        *head = newnode;
    }

    fclose(file);
}



//store() takes file and a pointer to the head of a list as parameters..
//This function essentially writes the data from the doubly linked list to csv file. 
//
void store(const char* filename, node* head) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not open file for writing.\n");       //opens file for writing 
        return;
    }

    node* ptr = head;           //node* ptr = head: initializes pointer used to naviagte the list. 
    while (ptr != NULL) {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d\n",ptr->data.artist, ptr->data.album, ptr->data.title, ptr->data.genre, ptr->data.duration.minutes,ptr->data.duration.seconds, ptr->data.playnum, ptr->data.rating);
        //writes information from the current node to the csv file. 
        
        //Moved to next node in list 
        ptr = ptr->next;
    }
    fclose(file);
}


//display() takes only one parameter: the pointer to the head of the list. 
//this function prints one of two options posed to user: (1) Print all records or 
// (2) Print all records that match an artist.
//user prints either 1 or 2.
//Option 1 traverses the doubly linked list and prints all of the stored 'record' info.
//Option 2 asks user for artists name and scans list for matches.
void display(node* head) {
    int choice;
    printf("Choose one of the following:\n\t");
    printf("1. Print all records\n\t");
    printf("2. Print records by artist\n\t");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        node* ptr = head;
        while (ptr != NULL) {               //prints all records in current node
            printf("Artist: %s, Album: %s, Title: %s, Genre: %s, Duration: %d:%d, Played: %d, Rating: %d\n",
                ptr->data.artist,
                ptr->data.album,
                ptr->data.title,
                ptr->data.genre,
                ptr->data.duration.minutes,
                ptr->data.duration.seconds,
                ptr->data.playnum,
                ptr->data.rating);
            ptr = ptr->next;
        }
    }
    else if (choice == 2) {
        char artistName[100];
        printf("Enter artist name: ");
        fgets(artistName, sizeof(artistName), stdin);
        artistName[strcspn(artistName, "\n")] = 0;

        node* ptr = head;
        int found = 0;//Used to track whether or not records were found. found = 1 IFF matchings records are found
        while (ptr != NULL) {
            if (strcmp(ptr->data.artist, artistName) == 0) {
                printf("Artist: %s, Album: %s, Title: %s, Genre: %s, Duration: %d:%d, Played: %d, Rating: %d\n",
                    ptr->data.artist,
                    ptr->data.album,
                    ptr->data.title,
                    ptr->data.genre,
                    ptr->data.duration.minutes,
                    ptr->data.duration.seconds,
                    ptr->data.playnum,
                    ptr->data.rating);
                found = 1; //see comment - line 141
            }
            ptr = ptr->next;        //proceeds to next node and repeats 
        }
        if (!found) {
            printf("No records found for artist: %s\n", artistName);
        }
    }
    else {
        printf("Invalid number, please select 1 or 2.\n");
    }
}



//edit() takes one parameter: the pointer to head of doubly linekd list. 
//This function prompts user for an artists name. It then edits each record in the doubly linked list based on
//the name given by the user. 
//If multiple records match the name given by the user, the user is prompted to choose which one to edit.
//The user is then prompted to enter new details for the selected record.
void edit(node* head) {
    char artist[100];
    printf("Enter artist name to edit: ");
    fgets(artist, sizeof(artist), stdin);
    artist[strcspn(artist, "\n")] = 0;

    node* ptr = head;
    int count = 0;
    node* matches[100] = { NULL };          //array to store pointers to matching records

    //begins traversing list and matching records to artists name given by user
    while (ptr != NULL) {
        if (strcmp(ptr->data.artist, artist) == 0) {
            //print record info if artist matches 
            printf("\nRecord %d:\n", count + 1);
            printf("Artist: %s\n", ptr->data.artist);
            printf("Album: %s\n", ptr->data.album);
            printf("Title: %s\n", ptr->data.title);
            printf("Genre: %s\n", ptr->data.genre);
            printf("Duration: %d:%d\n", ptr->data.duration.minutes, ptr->data.duration.seconds);
            printf("Play Count: %d\n", ptr->data.playnum);
            printf("Rating: %d\n", ptr->data.rating);
            
            //store pointer to the matching record in the matches array
            matches[count] = ptr;
            count++;
        }
        ptr = ptr->next;
    }


    //prints message and exits function if no records are found
    if (count == 0) {
        printf("no records found for: %s\n", artist);
        return;
    }

    int choice = 0;
    //if multiple records are found, function asks user which one to edit.
    if (count > 1) {
        printf("\n\tMultiple records were found\n\tWhich one do you want to edit ( 1 to %d): ", count);
        scanf("%d", &choice);
        getchar();
        
        //checks to make sure number entered by user is valid (1-{count})
        if (choice < 1 || choice > count) {
            printf("Invalid choice\n");
            return;
        }
    }

    node* recordEdit = matches[choice - 1]; //select the record to edit based on user choice or the only match.

    //promots user to enter new info for selected record. 
    printf("\nEnter new artist name: ");
    fgets(recordEdit->data.artist, sizeof(recordEdit->data.artist), stdin);
    recordEdit->data.artist[strcspn(recordEdit->data.artist, "\n")] = 0;

    printf("Enter new album title: ");
    fgets(recordEdit->data.album, sizeof(recordEdit->data.album), stdin);
    recordEdit->data.album[strcspn(recordEdit->data.album, "\n")] = 0;

    printf("Enter new song title: ");
    fgets(recordEdit->data.title, sizeof(recordEdit->data.title), stdin);
    recordEdit->data.title[strcspn(recordEdit->data.title, "\n")] = 0;

    printf("Enter new genre: ");
    fgets(recordEdit->data.genre, sizeof(recordEdit->data.genre), stdin);
    recordEdit->data.genre[strcspn(recordEdit->data.genre, "\n")] = 0;

    printf("Enter new song length (minutes seconds, separated by space): ");
    scanf("%d %d", &recordEdit->data.duration.minutes, &recordEdit->data.duration.seconds);

    printf("Enter new play count: ");
    scanf("%d", &recordEdit->data.playnum);

    printf("Enter new rating (1-5): ");
    scanf("%d", &recordEdit->data.rating);

    printf("\nRecord updated successfully.\n");
}



//sort() takes on paramater: the pointer to the head of doubly linked list 
//this function sorts the doubly linked list according to criteria selected by user
//sorting options given to user: 
//1. artist name
//2. artist title
//3. rating
//4. # of times played

void sort(node** head) {
    if (*head == NULL) {
        printf("List is empty.\t\n");       //simply checks if list is empty
        return;
    }

    int choice;
    printf("Select a sort method:\t\n");
    printf("1. Sort by artist (A-Z)\t\n");
    printf("2. Sort by album title (A-Z)\t\n");     //presents sorting options to user 
    printf("3. Sort by rating (1-5)\t\n");
    printf("4. Sort by times played (largest-smallest)\t\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); 

    int nodeSwap;   //tracks whether any nodes were swapped during a pass through the list
    node* ptr1;
    node* lptr = NULL;      //tracks last sorted node for bubble sort 

    //bubble sort for doubly linked list sort 
    do {
        nodeSwap = 0;        
        ptr1 = *head;

        while (ptr1->next != lptr) {        //traverses list until lptr which is the sorted portion
            int compare = 0;

            
            switch (choice) {
            case 1: //sort by artist
                compare = strcmp(ptr1->data.artist, ptr1->next->data.artist);
                break;
            case 2: //sort by album title
                compare = strcmp(ptr1->data.album, ptr1->next->data.album);
                break;
            case 3: //sort by rating (ascending order)
                compare = (ptr1->data.rating > ptr1->next->data.rating) ? 1 : (ptr1->data.rating < ptr1->next->data.rating) ? -1 : 0;
                break;
            case 4: //sort by times played (descending order)
                compare = (ptr1->data.playnum < ptr1->next->data.playnum) ? 1 : (ptr1->data.playnum > ptr1->next->data.playnum) ? -1 : 0;
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
                return;
            }

            //swap if the order is incorrect
            if (compare > 0) {
                record ptemp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = ptemp;
                nodeSwap = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (nodeSwap);

    printf("Records sorted successfully.\n");
}


//rate() takes on paramter: the pointer to the head of doubly linked list 
//This function allow user to update ratings for specific songs in list
//User is prompted for artist and song name. If record matches are found, 
//user can enter rating from 1-5. 

void rate(node* head) {
    char artist[100], title[100];

    printf("Enter artist name: ");
    fgets(artist, sizeof(artist), stdin);       
    artist[strcspn(artist, "\n")] = 0;
                                            //prompts user for artist & song
    printf("Enter song title: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    //begins traversing list to find matches 
    node* ptr = head;
    while (ptr != NULL) {
        //match found v
        if (strcmp(ptr->data.artist, artist) == 0 && strcmp(ptr->data.title, title) == 0) {
            int new_rating;
            printf("ptr rating: %d\n", ptr->data.rating);
            printf("Enter new rating (1-5): ");     //user enters rating
            scanf("%d", &new_rating);
            getchar();

            if (new_rating >= 1 && new_rating <= 5) {
                ptr->data.rating = new_rating;          //updates rating
                printf("Rating updated successfully.\n");
            }
            else {
                printf("Invalid rating. Please enter a value between 1 and 5.\n");
            }
            return;
        }
        ptr = ptr->next;
    }

    printf("no records were found for : %s and title: %s.\n", artist, title);
}


//play() takes one paramter: the pointer to the head of doubly linked list 
//This function begins "playing" songs in the doubly linked list beginning first with the song chosen by user. 
//Function can skip to next song in list when user presses enter.

void play(node* head) {
    if (head == NULL) {
        printf("No songs available to play.\n");
        return;
    }

    char title[100];
    printf("Enter song to begin playng from: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    //traversing list to find song to start form 
    node* ptr = head;
    while (ptr != NULL) {
        if (strcmp(ptr->data.title, title) == 0) {
            while (ptr != NULL) {
                //display song details 
                printf("Now playing: %s - %s\n", ptr->data.artist, ptr->data.title);
                printf("Album: %s\n", ptr->data.album);
                printf("Genre: %s\n", ptr->data.genre);
                printf("Song length: %d:%02d\n", ptr->data.duration.minutes, ptr->data.duration.seconds);
                printf("Times played: %d\n", ptr->data.playnum);
                printf("Rating: %d\n\n", ptr->data.rating);

                printf("Press enter to play next song");
                getchar();
                printf("\033[H\033[J");

                ptr = ptr->next;
            }
            break;
        }
        ptr = ptr->next;
    }

    printf("All songs have been played.\n");
}

//void() takes one parameter: pointer to head of doubly linked list 
//This function uses the Fischer-yates shuffle algorithm to shuffle songs within the doubly linked list. 
//The function first counts the number of nodes, stores them in an array, shuffles the array,
//and then prints the shuffled order of the songs.
void shuffle(node* head) {
    if (head == NULL) {
        printf("No songs to shuffle.\n");
        return;  
    }

    
    int size = 0;
    node* ptr = head;                           //counts the number of nodes in list 
    while (ptr != NULL) {
        size++;
        ptr = ptr->next;
    }

    
    node** nodes_array = malloc(size * sizeof(node*));  //Allocates memory for the array of node pointers
    if (nodes_array == NULL) {
        printf("Memory allocation failed for shuffle\n");
        return;
    }

    
    ptr = head;                             //populate the array with pointers to the nodes
    for (int i = 0; i < size; i++) {
        nodes_array[i] = ptr;
        ptr = ptr->next;
    }

    
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);               //fischer-yates shuffle algorithm 
        node* ptemp = nodes_array[i];
        nodes_array[i] = nodes_array[j];
        nodes_array[j] = ptemp;
    }

    //displays shuffled order
    printf("Shuffle order:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - %s\n", i + 1, nodes_array[i]->data.artist, nodes_array[i]->data.title);
    }

    free(nodes_array);
}


//delete() takes one paramter: the pointer to head of doubly linked list
//This function prompts user for title of song and deletes it from doubly linked list 
void delete(node** head) {
    char title[100];

    printf("Enter song title to delete: ");     //gets song to delete
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    node* ptr = *head;
    while (ptr != NULL) {
        //checks to see if current nodes title matches that of the users 
        if (strcmp(ptr->data.title, title) == 0) {
            if (ptr->prev != NULL) {
                ptr->prev->next = ptr->next;
            }
            else {
                *head = ptr->next;
            }
            if (ptr->next != NULL) {
                ptr->next->prev = ptr->prev;
            }
            free(ptr);
            printf("Record deleted.\n");
            return;
        }
        ptr = ptr->next;
    }

    printf("No record was found with the title: %s\n", title);
}


//insert() takes one parameter: pointer to head of doubly linked list
//THis function inserts new song record at front of the doubly linked list
//user is prompted to enter details for the new song, which is stored
//in a new node and inserted at the beginning of the list.
void insert(node** head) {
   
    record newRecord;

    printf("Enter artist name: ");
    fgets(newRecord.artist, sizeof(newRecord.artist), stdin);
    newRecord.artist[strcspn(newRecord.artist, "\n")] = 0;

    printf("Enter album title: ");
    fgets(newRecord.album, sizeof(newRecord.album), stdin);
    newRecord.album[strcspn(newRecord.album, "\n")] = 0;

    printf("Enter song title: ");
    fgets(newRecord.title, sizeof(newRecord.title), stdin);
    newRecord.title[strcspn(newRecord.title, "\n")] = 0;

    printf("Enter genre: ");
    fgets(newRecord.genre, sizeof(newRecord.genre), stdin);
    newRecord.genre[strcspn(newRecord.genre, "\n")] = 0;

    printf("Enter song length (minutes seconds, separated by space): ");
    scanf("%d %d", &newRecord.duration.minutes, &newRecord.duration.seconds);
    getchar();

    printf("Enter number of times played: ");
    scanf("%d", &newRecord.playnum);
    getchar();

    printf("Enter rating 1-5: ");
    scanf("%d", &newRecord.rating);
    getchar();

    //creates new node to store the new record 
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = newRecord;
    newnode->next = *head;
    newnode->prev = NULL;

    if (*head != NULL) {
        (*head)->prev = newnode;
    }
    *head = newnode;

    printf("Record inserted successfully.\n");
}

void freeList(node* head) {
    node* ptr = head;
    while (ptr != NULL) {
        node* nextNode = ptr->next;
        free(ptr);
        ptr = nextNode;
    }
}

void exitProgram(node* head) {
    store("musicPlayList.csv", head);
    freeList(head);
    printf("Closing program.\n");
    exit(0);
}
