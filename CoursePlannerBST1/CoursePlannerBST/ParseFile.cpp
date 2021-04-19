#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ParseFile.h"
using namespace std;

//default constructor
Parser::Parser() {
	_sep = ',';
	_file = "";
}

//parameterized constructor
Parser::Parser(string filePath, char separator) {
	_file = filePath;
}

/*function to open, grab each row and input into vector, and close file
*/
void Parser::OpenReadCloseFile() {
	ifstream inFS;		//create input file stream object

	inFS.open(_file);	//open file
	if (!inFS.is_open()) {	//make sure file is open, throw error if not
		throw runtime_error("Cannot open file");
	}

	string line;

	while (inFS.good()) {	//while file still has rows
		getline(inFS, line);	//get the row from file and store into line
		if (line != "") {		//if the line is not empty
			_rowsAsStrings.push_back(line.c_str()); //add line to row vector
		}
	}

	inFS.close(); //close the file

	if (_rowsAsStrings.size() == 0) {		//make sure vector has data from file
		throw runtime_error("No Data in file");
	}

	/*for (unsigned int i = 0; i < _rowsAsStrings.size(); i++) {	//print statement for _rowsAsStrings
		cout << _rowsAsStrings.at(i) << endl;
	}
	cout << endl;*/
}


/*function to parse the file:
*calls OpenReadCloseFile() to populate _rowsAsStrings vector
*then iterates through the vector and parses comma separated file and creates 2d vector _parsedCourses
*/
void Parser::ParseFile() {
	OpenReadCloseFile();

	vector<string>::iterator it;
	int rowCount = 0;
	string temp = "";


	for (it = _rowsAsStrings.begin(); it != _rowsAsStrings.end(); ++it) {	//iterate through _rowsAsStrings vector
		int subStart = 0;
		_parsedCourses.push_back(vector<string>());			//add empty vector of string to create 2d vector
		for (unsigned int i = 0; i != it->length(); ++i) {
			if (it->at(i) == ',') {							//parse through _rowsAsStrings and look for a comma
				temp = it->substr(subStart, i - subStart);	//create substring from subStart to the comma
				//cout << colCount << endl;
				//cout << temp << endl;
				_parsedCourses.at(rowCount).push_back(temp);	//add substring by pushing back to vector<string> initialized on line 66
				subStart = i + 1;								//increament subStart to position after comma.
			}
			else if (i == it->length() - 1) {					//if string is the last in the row
				temp = it->substr(subStart, it->length() - subStart);	//set temp to that substring
				_parsedCourses.at(rowCount).push_back(temp);			//add to the _parsedCourses vector's vector initialized on line 66
			}

		}
		rowCount++;
	}

	//print statement for checking contents of _parsedCourses
	/*for (unsigned int i = 0; i < _parsedCourses.size(); i++) {
		for (unsigned int j = 0; j < _parsedCourses.at(i).size(); j++) {
			cout << _parsedCourses.at(i).at(j) <<",";
		}
		cout << endl;
	}*/
}

/*function to ensure contents of each row has at least 2 parameters
*/
void Parser::CheckParamters() {
	for (unsigned int i = 0; i < _parsedCourses.size(); i++) {		//iterate through vector rows
		if (_parsedCourses.at(i).size() < 2) {						//check size of each row has at least 2 parameters
			cout << "Course on line " << i << " has less than two parameters\n";
		}
	}
}

/*function to ensure prereqs for each course has a matching course
*/
void Parser::CheckPrerequisite() {
	bool isFound = false;
	for (unsigned int i = 0; i < _parsedCourses.size(); i++) {		//iterate through _parsedCourses
		if (_parsedCourses.at(i).size() > 2) {						//if course has prereqs
			for (unsigned int j = 2; j < _parsedCourses.at(i).size(); j++) {	//for each prereq
				for (unsigned int k = 0; k < _parsedCourses.size(); k++) {	//iterate through _parsedCourses
					if (_parsedCourses.at(j) == _parsedCourses.at(k)) {		//if prereq matches base course 
						isFound = true;										//break
						break;
					}
				}
				if (isFound == false) {										//if prereq doesn't have a matching base course
					cout << "Prerequisite " << _parsedCourses.at(i).at(j) << " does not exist.\n";	//print the prereq that doesn't have a matching course
				}
			}
		}
	}
}