
#include <iostream>
#include <time.h>

#include "ParseFile.h"
#include "HashTable.h"

using namespace std;

//function declaration
void LoadCourses(string filePath, HashTable& hashTable);


int main()
{
    HashTable courseTable = HashTable();
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

            //user inputted parameter checking
            cin >> userOption;
            if (userOption <= 0 || userOption > 4) {
                throw invalid_argument("Not a valid option");
            }

            switch (userOption) {
                //load file information into Hashtable
            case 1:
                ticks = clock();
                LoadCourses("D:/Joe/Documents/SchoolWork/CS-300 Data Structures and Algorithms/milestone/CoursePlanner/CoursePlanner/coursedoc.txt", courseTable);
                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                //courseTable.PrintAllUnsorted();
                //cout << "==========================================\n";
                break;

                //print sorted courses
            case 2:
            {
                ticks = clock();
                courseTable.PrintSorted();      
                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;
            }
                //print specific course
            case 3:
            {
                string userCourse;
                cout << "Enter course ID:";
                cin >> userCourse;

                //user input parameter checking
                if (userCourse.length() != 7) {
                    throw invalid_argument("Invalid length of characters");
                }

                courseTable.PrintCourse(userCourse);
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

/*function to load courses into a hashtable data structure
@param the filepath to get course data
@param the hashtable object passed by reference
*/
void LoadCourses(string filePath, HashTable& hashTable) {
    cout << "Loading file information from: " << filePath << endl;
    char sep = ',';

    Parser file = Parser(filePath, sep);
    file.ParseFile();

    
    try {

        for (unsigned int i = 0; i < file.getRowSize(); i++) {
            Course* aCourse = new Course();
            aCourse->_courseID = file._parsedCourses.at(i).at(0);       //grab courseID from col position 0 in 2d vector
            aCourse->_courseName = file._parsedCourses.at(i).at(1);     //grab courseName from col position 1 in 2d vector


            if (file.getColSize(i) > 2) {                               //if course has prereqs
                int colCounter = 2;                                     //prereqs will start at col index 2 of _parsedCourses
                while (colCounter < file.getColSize(i)) {                //iterate through rest of columns
                    aCourse->_prereqs.push_back(file._parsedCourses[i][colCounter]);    //add prereqs from 2d vector to aCourses' _prereqs vector
                    colCounter++;
                }
            }
            
            hashTable.Insert(*aCourse);         //call insert to add course to hashtable
            delete aCourse;                     //free memory for aCourse


        }

    }
    catch (exception& e) {
        cout << e.what() << endl;
    }


}

