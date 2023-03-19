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

typedef enum { SER=3, EGR=2, CSE=0, EEE=1 } Subject;

typedef struct CourseNode {
    Subject subject;
    int courseNumber;
    char teacher[1024];
    int creditHours;

    struct CourseNode * next;
} CourseNode;

//place to store course information
struct CourseNode *course_collection = NULL;

////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS
void branching(char option);
void course_insert(int subject, int courseNumber, int credits, char *teacher);
void schedule_print();
void course_drop();
void schedule_load();
void schedule_save();
const char *enumToString(Subject subject);


/**
 * A function that performs course insertion to the list while keeping the list sorted at all times.<br>
 * The list is sorted in ascending order, ordered by subject then course number.
 * @param head a pointer to the front of the linked list
 * @param subject an input value from the user
 * @param courseNumber and input value from the user
 * @param teacher an input value from the user
 */
void course_insert(int subject, int courseNumber, int credits, char *teacher) {

    struct CourseNode *newNode = (struct CourseNode*) malloc(sizeof (struct CourseNode));
    struct CourseNode *current;
    struct CourseNode *head;
    head = course_collection;

    // insert passed information to the new node.
    newNode->subject = subject;
    newNode->courseNumber = courseNumber;
    newNode->creditHours = credits;
    strcpy(newNode->teacher, teacher);


//    if (head == NULL) {
//        newNode->next = course_collection;
//        course_collection = newNode;
//    }
//
//    else {
//        current = head;
//        while (current->next != NULL) {
//            if (current->subject == newNode->subject) {
//                if (newNode->next > current->next) {
//                    current = current->next;
//                } else {
//                    newNode->next = current->next;
//                    current->next = newNode;
//                }
//            }
//            current = current->next;
//        }
//        // insertion at the end
//        current->next = newNode;
//    }

    // 3 Cases - insertion at front, insertion in middle, insertion at end
    // insertion in the beginning of the list

    if (head == NULL || head->subject >= newNode->subject) {
        newNode->next = course_collection;
        course_collection = newNode;
    }
    else {
        current = head;
        while (current->next != NULL && current->next->subject <= newNode->subject) {
            if (current->next->subject < newNode->subject) {
                current = current->next;
            } else if (current->next->subject == newNode->subject) {
                if (current->next->courseNumber < newNode->courseNumber) {
                    current = current->next;
                } else {
                    newNode->next = current->next;
                    current->next = newNode;
                    break;
                }
            }
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

/**
 * A function that converts enum to string.
 * @param subject enum variable
 * @return String representation of the enum
 */
const char *enumToString(Subject subject) {
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
void displayList() {
    struct CourseNode *iter = course_collection;
    if (iter == NULL) {
        printf("List is empty");
    } else {
        while (iter != NULL) {
            printf("| %s:%d | ---> ", enumToString(iter->subject), iter->courseNumber);
            iter = iter->next;
        }
    }
}

/**
 * A function that prints the student's class schedule.
 */
void schedule_print() {
    struct CourseNode *iter = course_collection;
    printf("Class Schedule\n");
    printf("--------------------------------\n");
    if (iter == NULL) {
        printf("List is empty");
    } else {
        while (iter != NULL) {
            printf("%s%d\t%d\t%s\n", enumToString(iter->subject), iter->courseNumber, iter->creditHours, iter->teacher);
            iter = iter->next;
        }
    }
}

//main entry point. Starts the program by displaying a welcome and beginning an 
//input loop that displays a menu and processes user input. Pressing q quits.      
int main() {

    // insert test data
    char teacher1[9] = "Teacher1";
    char teacher2[9] = "Teacher2";
    char teacher3[9] = "Teacher3";
    char teacher4[9] = "Teacher4";

    // mock data to test
    course_insert(SER, 3, 3, teacher2);
    course_insert(SER, 1, 3, teacher2);
    course_insert(EEE, 1, 3, teacher2);
    course_insert(CSE, 3, 3, teacher3);
    course_insert(CSE, 1, 3, teacher3);
    course_insert(EGR, 2, 3, teacher3);

    displayList();
    schedule_print();





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