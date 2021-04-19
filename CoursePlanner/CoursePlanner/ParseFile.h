#ifndef _PARSEFILE_H_
#define _PARSEFILE_H_

#include <vector>
#include <string>

using namespace std;

class Parser {
public:
	//constructors
	Parser();
	Parser(string filePath, char separator = ',');
	//~Parser();
	//public member function declarations
	void OpenReadCloseFile();
	void ParseFile();
	void CheckParamters();
	void CheckPrerequisite();
	int getRowSize() { return _parsedCourses.size(); }
	int getColSize(int row) { return _parsedCourses.at(row).size(); }
	
	//public data members
	std::vector<std::vector<std::string>> _parsedCourses;
	

private:
	//private data members
	char _sep;
	string _file;
	std::vector<std::string> _rowsAsStrings;

};

#endif