
#include <iostream>
#include <time.h>
#include <ctype.h>

#include "ParseFile.h"
#include "BST.h"

using namespace std;

//function declarations
void LoadCourses(string filePath, BST& tableBST);


int main()
{
    BST courseTable = BST();
    clock_t ticks;
    bool isDone = false;

    while (!isDone) {
        try {
            int userOption;

            cout << "=======================================================\n"
                << "Welcome to the course planner.\n"
                << "-------------------------------------------------------\n"
                << "1. Load Data Structure.\n"
                << "2. Print Course List.\n"
                << "3. Print Course.\n"
                << "4. Exit\n"
                << "-------------------------------------------------------\n";
            cout << "What would you like to do?\n";

            cin >> userOption;
            //parameter checking
            if (userOption <= 0 || userOption > 4) {                                   
                throw invalid_argument("Not a valid option");
            }

            switch (userOption) {
                //load file information into binary search tree
            case 1:
                ticks = clock();
                LoadCourses("D:/Joe/Documents/SchoolWork/CS-300 Data Structures and Algorithms/milestone/CoursePlannerBST1/CoursePlannerBST/coursedoc.txt", courseTable);
                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;

                //Print in-order
            case 2:
            {
                ticks = clock();
                courseTable.PrintInOrder();
                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;
            }

                //Print a specified course
            case 3:
            {
                string userCourse;
                cout << "Enter course ID:";
                cin >> userCourse;
                //convert lowercase to upper case
                char c;
                userCourse.c_str();
                for (unsigned int i = 0; i < 4; i++) {
                    if (tolower(userCourse.at(i)) != 0) {
                        c = userCourse.at(i);
                        userCourse.at(i) = toupper(c);
                    }
                }
                //user input parameter checking
                if (userCourse.length() != 7) {
                    throw invalid_argument("Invalid length of characters");
                }

                courseTable.PrintACourse(userCourse);
                break;
            }
            case 4:
                isDone = true;
                break;
            }
        }
        catch (invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

}


/*function to load courses from external file to BST object
@param file path name
@param BST object by reference
*/
void LoadCourses(string filePath, BST& tableBST) {
    cout << "Loading file information from: " << filePath << endl;
    char sep = ',';

    Parser file = Parser(filePath, sep);
    file.ParseFile();


    try {

        for (unsigned int i = 0; i < file.getRowSize(); i++) {
            Course* aCourse = new Course();
            aCourse->_courseID = file._parsedCourses.at(i).at(0);       //grab courseID from col position 0 in 2d vector
            aCourse->_courseName = file._parsedCourses.at(i).at(1);     //grab courseName from col position 1 in 2d vector

            //print statement to check if course was extracted correctly
           // cout << endl << "------------" << aCourse->_courseID << aCourse->_courseName << "---------------" << endl;;

            if (file.getColSize(i) > 2) {           //if course has prereqs
                int colCounter = 2;                 //prereqs will start at col index 2 of _parsedCourses
                while (colCounter < file.getColSize(i)) {   //iterate through rest of columns
                    aCourse->_prereqs.push_back(file._parsedCourses[i][colCounter]);  //add prereqs from 2d vector to aCourses' _prereqs vector
                    colCounter++;
                }
            }

            tableBST.Insert(*aCourse);      //call insert to add course to binary tree
            delete aCourse;                 //free memory for aCourse


        }

    }
    catch (exception& e) {
        cout << e.what() << endl;
    }


}

