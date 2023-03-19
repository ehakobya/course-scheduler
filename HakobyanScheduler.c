/**
* Edgar Hakobyan
*
* Completion time: (estimation of hours spent on this program)
*
* @author Edgar Hakobyan, Acuna
* @version 1.0
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//MACROS: CONSTANTS


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES


////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES

typedef enum { SER=0, EGR=1, CSE=2, EEE=3 } Subject;

typedef struct CourseNode {
    Subject subject;
    int courseNumber;
    char teacher[1024];
    int creditHours;

    struct CourseNode * next;
} CourseNode;

//place to store course information
struct CourseNode * course_collection = NULL;

////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS
void branching(char option);
void course_insert(struct CourseNode* head, int subject, int courseNumber, int credits, char *teacher);
void schedule_print(struct CourseNode *head);
void course_drop();
void schedule_load();
void schedule_save();

/**
 * A function that converts enum to string
 * @param subject enum variable
 * @return String representation of the enum
 */
const char *getSubject(Subject subject) {
    switch (subject) {
        case SER: return "SER";
        case EGR: return "EGR";
        case CSE: return "CSE";
        case EEE: return "EEE";
    }
}

/**
 * A function to desplay the entire linked list for testing and debugging purposes.
 * @param head a pointer to the front of the linked list
 */
void displayList(struct CourseNode *head) {
    struct CourseNode *iter = head;
    while (iter != NULL) {
        printf("| %s:%d | ---> ", getSubject(iter->subject), iter->courseNumber);
        iter = iter->next;
    }
}

//main entry point. Starts the program by displaying a welcome and beginning an 
//input loop that displays a menu and processes user input. Pressing q quits.      
int main() {


//	char input_buffer;
//
//	printf("\n\nWelcome to ASU Class Schedule\n");
//
//	//TODO: stuff goes here...
//
//	//menu and input loop
//	do {
//		printf("\nMenu Options\n");
//		printf("------------------------------------------------------\n");
//		printf("a: Add a class\n");
//		printf("d: Drop a class\n");
//		printf("s: Show your classes\n");
//		printf("q: Quit\n");
//		//printf("\nTotal Credits: %d\n\n", TODO);
//		printf("Please enter a choice ---> ");
//
//		scanf(" %c", &input_buffer);
//
//		branching(input_buffer);
//	} while (input_buffer != 'q');
//
//	//TODO: stuff goes here...

	return 0;
}

//takes a character representing an inputs menu choice and calls the appropriate
//function to fulfill that choice. display an error message if the character is
//not recognized.
void branching(char option) {
	switch (option) {
	case 'a':
		//TODO
		break;

	case 'd':
		//TODO
		break;

	case 's':
		//TODO
		break;

	case 'q':
		// main loop will take care of this.
		break;

	default:
		printf("\nError: Invalid Input.  Please try again...");
		break;
	}
}