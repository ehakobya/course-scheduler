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
//GLOBAL VARIABLES
int totalCreditHours;
typedef enum { SER=3, EGR=2, CSE=0, EEE=1 } Subject;

////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES
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
void course_drop(Subject subject, int courseNumber);
void schedule_print();
//void displayList();
void schedule_load(char *filename);
void schedule_save(char *fileName);
const char *enumToString(Subject subject);

////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS

/**
 * Main entry point. Starts the program by displaying a welcome and begining and
 * input loop that displays a menu and processes user input. Pressing q quits
 * @return
 */
int main() {

	char input_buffer;
    char* filename = "list.txt";

	printf("\n\nWelcome to ASU Class Schedule\n");

	//TODO: stuff goes here...

	//menu and input loop
	do {
		printf("\nMenu Options\n");
		printf("------------------------------------------------------\n");
		printf("a: Add a class\n");
		printf("d: Drop a class\n");
		printf("s: Show your classes\n");
		printf("q: Quit\n");
		printf("\nTotal Credits: %d\n\n", totalCreditHours);
		printf("Please enter a choice ---> ");

		scanf("%c", &input_buffer);

		branching(input_buffer);

	} while (input_buffer != 'q');

    schedule_save(filename);
	return 0;
}

/**
 * Takes a character representing an inputs menu choice and calls the appropriate
 * function to fullfill that choice. Displays an error message if the character is
 * not recognized.
 * @param option input menu option
 */
void branching(char option) {
    Subject subject;
    int courseNumber;
    char teacher[1024];
    int creditHours;

	switch (option) {
	case 'a':
            printf("\nWhat is the subject? (SER=0, EGR=1, CSE=2, EEE=3)?");
            scanf("&d", &subject);
            printf("\nWhat is the number (e.g. 240)?");
            scanf("&d", &courseNumber);
            printf("\nHow many credits is the class (e.g. 3)?");
            scanf("&d", &creditHours);
            printf("\nWhat is the name of the teacher?");
            scanf("&s", &teacher);
            course_insert(subject, courseNumber, creditHours, teacher);
		break;

	case 'd':
            printf("\nWhat is the subject? (SER, EGR, CSE, EEE)?");
            scanf("&d", &subject);
            printf("\nWhat is the number (e.g. 240)?");
            scanf("&d", &courseNumber);
            course_drop(subject, courseNumber);
		break;

	case 's':
		    schedule_print();
		break;

	case 'q':
		// main loop will take care of this.
		break;

	default:
		printf("\nError: Invalid Input.  Please try again...");
		break;
	}
}

/**
 * Takes inputs from the user, creates a new course, and inserts the course into the list of course.<br>
 * Isertion of the courses keeps the list sorted at all times by ordering with subject then coruse number.
 * @param subject an input value from the user e.g. CSE
 * @param courseNumber an input value from the user e.g. 240
 * @param credits an input value from the user e.g. 3
 * @param teacher an input value from the user e.g. Acuna
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
        totalCreditHours = totalCreditHours + newNode->creditHours;
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
                    // insertion in the middle
                    newNode->next = current->next;
                    current->next = newNode;
                    totalCreditHours = totalCreditHours + newNode->creditHours;
                    break;
                }
            }
            current = current->next;
        }
        // insertion at the end
        newNode->next = current->next;
        current->next = newNode;
        totalCreditHours = totalCreditHours + newNode->creditHours;
    }
}

/**
 * Takes inputs from the user, searches the list for the course, and removes it from the list.
 * @param subject  an input value from the user
 * @param courseNumber an input value from the user
 */
void course_drop(Subject subject, int courseNumber) {
    struct CourseNode *head = course_collection;
    struct CourseNode *temp = head, *prev;

    if (temp != NULL && temp->subject == subject && temp->courseNumber == courseNumber) {
        course_collection = temp->next;
        totalCreditHours = totalCreditHours - temp->creditHours;
        free(temp);
        return;
    }
    while (temp != NULL && temp->subject != subject) {
        prev = temp;
        temp = temp->next;
    }
    while (temp != NULL && temp->courseNumber != courseNumber) {
        prev = temp;
        temp = temp->next;
    }

    //TODO : Solve error when course does not exist
    if (temp == NULL || temp->subject != subject && temp->courseNumber != courseNumber){
        printf("ERROR! %s%d doesn't exist\n", enumToString(temp->subject), temp->courseNumber);
        return;
    } else {
        prev->next = temp->next;
        totalCreditHours = totalCreditHours - temp->creditHours;
        free(temp);
        return;
    }
}
//
//    else {
//        current = head;
//        while (current->next != NULL && current->next->subject <= newNode->subject) {
//            if (current->next->subject < newNode->subject) {
//                current = current->next;
//            } else if (current->next->subject == newNode->subject) {
//                if (current->next->courseNumber < newNode->courseNumber) {
//                    current = current->next;
//                } else {
//                    // insertion in the middle
//                    newNode->next = current->next;
//                    current->next = newNode;
//                    break;
//                }
//            }
//            current = current->next;
//        }
//        // insertion at the end
//        newNode->next = current->next;
//        current->next = newNode;

//
//    struct CourseNode *head = course_collection;
//    struct CourseNode *temp = head;
//    struct CourseNode *prev;
//
//    // 3 Cases - deletion from the front, deletion from the middle, deletion from the end
//    // deletion from the front
//    if (temp->next != NULL && temp->subject == subject && temp->courseNumber == courseNumber) {
//        // move head to next node and delete current head
//        head = temp->next;
//        free(temp);
//        return;
//    } else {
//        while (temp->next != NULL) {
//            if (temp->next->subject != subject) {
//                prev = temp;
//                temp = temp->next;
//            } else {
//                if (temp->next->courseNumber != courseNumber) {
//                    prev = temp;
//                    temp = temp->next;
//                } else {
//                    printf("ERROR! %s%d doesn't exist\n", enumToString(temp->subject), temp->courseNumber);
//                    break;
//                }
//            }
//
//        }
//
//        if (temp == NULL) {
//            printf("ERROR! %s%d doesn't exist\n", enumToString(temp->subject), temp->courseNumber);
//            return;
//        }
//        prev->next = temp->next;
//        free(temp);
//        return;
//    }
//}

/**
 * Converts enum to string.
 * @param subject enum variable
 * @return String representation of the enum
 */
const char* enumToString(Subject subject) {
    switch (subject) {
        case SER: return "SER";
        case EGR: return "EGR";
        case CSE: return "CSE";
        case EEE: return "EEE";
    }
}

/**
 * Displays contents of the linked list in simple manner. Used for testing and debugging.
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
        printf("\n");
    }
}

/**
 * Prints the student's class schedule.
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

/**
 * Loads file contents and stores them into the linked list. Performs sorting while loading each course.
 * @param filename input file name. Used for creating/loading a file to save data
 */
void schedule_load(char *fileName) {

    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file");
    }


}

/**
 * Saves the contents of the linked list to a file.
 * @param fileName input file name. Used for creating/loading a file to save data
 */
void schedule_save(char *fileName) {
    struct CourseNode *iter = course_collection;
    FILE *file;
    file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }
    // iterate over list and write to file
    while (iter) {
        fprintf(file, "%s%d/t%d/t%s\n", enumToString(iter->subject),
                iter->courseNumber, iter->creditHours, iter->teacher);
        iter = iter->next;
    }
    fclose(file); // close file after writing
}