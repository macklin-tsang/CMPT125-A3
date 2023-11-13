// Name: Macklin Tsang
// Student Number: 301567122
// Computing ID: mta149

// Program was written with help of CS Peer Tutor 
// Also written with inspiration from Bing Sage AI GPT-4

// Include header file and libaries for functions
#include "a3_talklib.h"
#include <stdio.h>

//Creates a Talk struct variable storing three shorts representing 
//hours, minutes, and seconds respectively, a char* array representing a title,
//and a char* array representing an overview
//Returns the address of the dynamically (i.e., uses malloc) created variable

Talk* createTalk(short hours, short minutes, short seconds,
                            const char* title, const char* overview) {
								
	Talk* newTalk = malloc(sizeof(Talk));
	if (newTalk == NULL) return NULL;

	newTalk->hours = hours;
	newTalk->minutes = minutes;
	newTalk->seconds = seconds;

	// strlen + 1 for null terminating character
	newTalk->title = malloc(sizeof(char)*strlen(title)+1);
	newTalk->overview = malloc(sizeof(char)*strlen(overview)+1);

	// Deep copy into struct variables
	strcpy(newTalk->title, title);
	strcpy(newTalk->overview, overview);

	return newTalk;
}

//Releases the memory created to store the 2 members title and overview using
// the address of a Talk struct variable
//Note that the talk parameter can be NULL
// and if this is the case the function should do nothing.

void clearTalk(Talk* talk) {
    if (talk == NULL) return;
	free(talk->title);
	free(talk->overview);
}

//helper function to look up a talk entry by title (Cstring)
//returns a dynamic array storing all the indexes with the containing the input as substring,
// NULL if not found
//To make the size known to the caller, put a -1 as the last item. For example,
// if items at indexes 2, 4, 6 contain the input as substring, the array would be {2, 4, 6, -1}
int* lookupTalkByTitle(Talk **array, int size, const char* title){
    int trackIndex = 0;
    int* matches = malloc((sizeof(int)*size+1));
    if (matches == NULL) {
        printf("Failed to allocate.\n");
        return NULL;
    }

    for (int i = 0; i < size; i++){
        if (strstr(array[i]->title, title) != NULL){
            matches[trackIndex] = i;
            trackIndex++;
        }
    }

    matches[trackIndex] = -1;

    if (trackIndex == 0){
        return NULL;
    }
    
    return matches;
}

//helper function for qsort to compare talks by duration
int compareTalksByDuration(const void *p1, const void *p2){
	Talk* talk1 = *(Talk**)p1;
	Talk* talk2 = *(Talk**)p2;

    if (talk1->hours != talk2->hours){
        return(talk1->hours - talk2->hours);
    }
    if (talk1->minutes != talk2->minutes){
        return(talk1->minutes - talk2->minutes);
    }

    return (talk1->seconds - talk2->seconds);
}

//helper function for qsort to compare talks by title (Cstring)
int compareTalksByTitle(const void *p1, const void *p2){
	Talk* talk1 = *(Talk**)p1;
	Talk* talk2 = *(Talk**)p2;
	return(strcmp(talk1->title , talk2->title));
}

Talk** loadTalksFile(char* filename, int* count){
    FILE* filePtr = fopen(filename, "r");
    // Check if the file can be opened successfully
    if (filePtr == NULL) {
        printf("Failed to open.\n");
        return NULL;
    }

    // Talk pointer memory allocation
    int capacity = 16;
    int used = 0;
    Talk** talk = malloc(sizeof(Talk*)*capacity);

    // Check if allocation is successful
    if (talk == NULL) {
        printf("Failed to allocate.\n");
        return NULL;
    }

    char inputBuffer[301];

    // Reading lines until end of file
    // 15 is for the **Duration:** text and null terminator
    // returns null if end of file
    while (fgets(inputBuffer, 15, filePtr) != NULL){ 

        short hours;
        short minutes;
        short seconds;
        char title[301]; // stores up to 300 chars
        char overview[301]; // stores up to 300 chars

        // Scan the duration and store respective time units
        fscanf(filePtr, "%hd hour, %hd minutes, %hd seconds\n", 
        &hours, &minutes, &seconds);

        // Reads "**Talk Title:**"
        fgets(inputBuffer, 17, filePtr);

        // Reads & stores title (up to 300 characters)
        fgets(title, 301, filePtr);

        // Reads "**Overview:**"
        fgets(inputBuffer, 15, filePtr);
        
        // Reads & stores overview (up to 300 characters)
        fgets(overview, 301, filePtr);

        // Reads the "---" separator
        fgets(inputBuffer, 5, filePtr);

        // Process to remove quotations from title
        // Shift each title index to the left to remove 1st quote
        for (int i = 0; i<strlen(title); i++){
            title[i] = title[i+1];
        }
        
        // Null terminator to remove 2nd quote
        title[strlen(title)-2] = '\0';

        // Call function to store info into respective talk index struct
        talk[used] = createTalk(hours, minutes, seconds, title, overview);

        used++;

        // Dynamic array, if we reach max capacity, double our max cap
        // Increase cap by realloc
        if (used == capacity){
            capacity *= 2;
            talk = (Talk**)realloc(talk, sizeof(Talk*)*capacity);
            
            // Check if reallocation is successful
            if (talk == NULL) {
                printf("Failed to reallocate.\n");
                return NULL;
            }
        }
    }

    printf("%d entries read.\n", used);

	*count = used;

    fclose(filePtr);

	return talk;
}

void displayEntries(Talk** talk, int used){
	for (int i = 0; i < used; i++){
        printf("Talk #%d\n", i+1); // since talk is 0-indexed, talk # start at 1
        printf("%hdh%hdm%hds\n%s\n%s", talk[i]->hours, talk[i]->minutes, 
        talk[i]->seconds, talk[i]->title, talk[i]->overview);
        printf("==========================================================\n");
    }
}

void displaySearchResults(Talk** talk, int* searchMatches){
    // find a better way to do this
    int tracker = 0;
    
    while (searchMatches[tracker] != -1){
        int searchIndex = searchMatches[tracker];
        printf("Talk #%d\n", tracker+1);
        printf("%hdh%hdm%hds\n%s\n%s", talk[searchIndex]->hours, talk[searchIndex]->minutes, 
        talk[searchIndex]->seconds, talk[searchIndex]->title, talk[searchIndex]->overview);
        printf("==========================================================\n");
        tracker++;
    }
}

int fullClear(Talk** talk, int count){

	for (int i = 0; i < count; i++){
        clearTalk(talk[i]);// Free allocated memory for title and overview array
        free(talk[i]);// Free respective talk struct index
    }

	free(talk);

	return -1;
}
