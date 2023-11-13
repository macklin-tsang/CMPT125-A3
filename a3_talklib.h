#ifndef _A3_Q1_H_
#define _A3_Q1_H_

#include <stdlib.h> //needed for handling dynamic memory
#include <string.h> //needed for some string functions

//the structure used for holding one talk entry
typedef struct {
	short hours;
	short minutes;
	short seconds;
	char* title;
	char* overview;
} Talk;

//Creates a Talk struct variable storing three shorts representing 
// hours, minutes, and seconds respectively, a char* array representing a title,
// and a char* array representing an overview
//Returns the address of the dynamically (i.e., uses malloc) created variable
//For example:
//Given the code (title and overview are Cstrings sotring the proper information):
//Talk* talk = createTalk(1, 27, 10, title, overview);
//printf("%dh%dm%ds\n%s\n%s\n", talk->hours, talk->minutes, talk->seconds, 
//      talk->title, talk->overview);
//will result in an output like this:
//1h27m10s
//AI in Retail: Personalizing the Shopping Experience
//Explore how AI is reshaping the retail industry, focusing on personalized
// recommendations, inventory management, and customer engagement. Discuss the
// potential to enhance customer satisfaction and optimize operations using
// AI-powered solutions.
Talk* createTalk(short hours, short minutes, short seconds,
                            const char* title, const char* overview);


//Releases the memory created to store the 2 members title and overview using
// the address of a Talk struct variable
//Note that the talk parameter can be NULL
// and if this is the case the function should do nothing.
//Also, this function does not release the memory used for the Talk struct variable,
// but only those used by the members title and overview. 
// To release all the memory dynamically allocated for the struct variable, you should
// call the free() function with the address of this struct variable right after the
// function returns.
void clearTalk(Talk* talk);

//helper function to look up a talk entry by title (Cstring)
//returns a dynamic array storing all the indexes with the containing the input as substring,
// NULL if not found
//To make the size known to the caller, put a -1 as the last item. For example,
// if items at indexes 2, 4, 6 contain the input as substring, the array would be {2, 4, 6, -1}
int* lookupTalkByTitle(Talk **array, int size, const char* title);

//helper function for qsort to compare talks by duration
int compareTalksByDuration(const void *p1, const void *p2);

//helper function for qsort to compare talks by title (Cstring)
int compareTalksByTitle(const void *p1, const void *p2);

Talk** loadTalksFile(char* filename, int* count);

void displayEntries(Talk** talk, int used);

void displaySearchResults(Talk** talk, int* searchMatches);

int fullClear(Talk** talk, int count);

#endif
