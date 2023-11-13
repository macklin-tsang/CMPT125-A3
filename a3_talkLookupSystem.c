// Name: Macklin Tsang
// Student Number: 301567122
// Computing ID: mta149

// Program was written with help of CS Peer Tutor & Victor
// Program written with inspiration from Bing Sage AI GPT-4

// Include header file and libaries for functions
#include "a3_talklib.h"
#include <stdio.h>

// Main function for lookup system
// Decide program/library functions

void printBanner(){
	printf(
    "++++++++++++++++++++++++++++++++++\n"
    "+++++ CS TALKS LOOKUP SYSTEM +++++\n"
    "++++++++++ Macklin Tsang +++++++++\n"
    "++++++++++++ 301567122 +++++++++++\n"
    "++++++++++ mta149@sfu.ca +++++++++\n"
    "++++++++++++++++++++++++++++++++++\n"
    "Press numbers 1-5 for the following option and then enter:\n"
    "1) to load a talks file.\n"
    "2) to list talks sorted by duration.\n"
    "3) to list talks sorted by title.\n"
    "4) to look up a talk.\n"
    "5) to terminate the program.\n"
    "Option: "
        );
}

int main() {

    int option;
    int count;
    char filename[300];
    char searchBar[51];
    Talk** talks = NULL;
    int* searchMatches = NULL;

    do {
    
    printBanner();

    scanf("%d", &option);

    switch(option) {
        default:
            printf("Please enter a valid option.\n");
            break;
        case 1:
            if (talks!=NULL){fullClear(talks, count);}
            printf("Enter the full name of the talks file (with extensions): ");
            scanf("%s", filename);
            talks = loadTalksFile(filename, &count);
            break;
        case 2:
            if (talks == NULL){
                printf("No talks file have been loaded, please load a file.");
            } else {
                qsort(talks, count, sizeof(Talk*), compareTalksByDuration);
                displayEntries(talks, count);
            }
            break;
        case 3:
            if (talks == NULL){
                printf("No talks file have been loaded, please load a file.");
            } else {
                qsort(talks, count, sizeof(Talk*), compareTalksByTitle);
                displayEntries(talks, count);
            }
            break;
        case 4:
            if (talks == NULL){
                printf("No talks file have been loaded, please load a file.");
            } else {
                printf("What is the title of the talk, enter in part or as a whole (50 character max.)? ");
                scanf(" %[^\n]", searchBar);
                searchMatches = lookupTalkByTitle(talks, count, searchBar);
                if (searchMatches == NULL){
                    printf("No matches found.\n");
                    }
                else {
                    displaySearchResults(talks, searchMatches);
                    free(searchMatches);
                    }
            }
            break;
        case 5:
            if (talks!=NULL){
                fullClear(talks, count);
            }
            break;
        }
    } while(option != 5);
        
    return 0;
}