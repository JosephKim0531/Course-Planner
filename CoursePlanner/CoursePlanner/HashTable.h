#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

//structure to hold course information
struct Course {
	string _courseID;
	string _courseName;
	vector<string> _prereqs;

	Course() {
		this->_courseID = "";
		this->_courseName = "";
	}

	Course(const Course& aCourse) {
		this->_courseID = aCourse._courseID;
		this->_courseName = aCourse._courseName;
		this -> _prereqs = aCourse._prereqs;

	}


	//function to output the course information
	void DisplayCourse() {
		cout << this->_courseID << ": " << this->_courseName;
		if (_prereqs.size() > 0) {
			cout << ": ";
			for (unsigned int i = 0; i < this->_prereqs.size(); i++) {
				if (i == this->_prereqs.size() - 1) {
					cout << this->_prereqs.at(i) << endl;
				}
				else {
					cout << this->_prereqs.at(i) << ", ";
				}
			}
		}
		else {
			cout << endl;
		}
		
	}
};


class HashTable {
	//public member functions
public:
	HashTable();
	HashTable(unsigned int size);
	virtual ~HashTable();
	void Insert(Course course);
	Course& Search(string& courseID);
	void PrintCourse(string courseID);
	void PrintAllUnsorted();
	void PrintSorted();

	//private data members and functions
private:
	struct Node {
		Course _course;
		unsigned int _key;
		Node* _next;

		Node() {
			this->_key = UINT_MAX;
			this->_next = nullptr;
		}
		Node(Course aCourse) : Node() {
			this->_course = aCourse;
		}
		Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
			this->_key = aKey;
		}

		Node(const Node& otherNode) {
			this->_course = otherNode._course;
			this->_key = otherNode._key;
			this->_next = nullptr;
		}

	};

	int _size = 7;

	unsigned int Hash(string aCourseID);

	vector<Node*> _courseNodes; //vector structure for the hash table

	vector<Course*> _vectorCourses;	//vector structure for course objects that will be utilized for sorting

	void CreateCourseVector();
	int Partition(int low, int high);
	void QuickSort(int low, int high);
};



#endif