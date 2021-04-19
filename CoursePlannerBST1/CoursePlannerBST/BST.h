#ifndef _BST_H_
#define _BST_H_

#include <string>
#include <vector>
#include <iostream>

#include "BST.h"

using namespace std;

//structure for the Courses
struct Course {
	//data members
	string _courseID;
	string _courseName;
	vector<string> _prereqs;

	//constructor
	Course() {
		this->_courseID = "";
		this->_courseName = "";
	}
	//copy constructor
	Course(const Course& aCourse) {
		this->_courseID = aCourse._courseID;
		this->_courseName = aCourse._courseName;
		this->_prereqs = aCourse._prereqs;
	}

	//function to print out the course
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

class BST {
public:
	BST();
	void Insert(Course aCourse);
	int GetNumPrereqs(string courseID);
	Course Search(string aCourse);
	void PrintACourse(string courseID);
	void PrintInOrder();

private:
	//structure for the Node
	struct Node {
		Course course;
		Node* left;
		Node* right;

		Node() {
			this->course = Course();
			this->left = nullptr;
			this->right = nullptr;
		}
		Node(Course aCourse) : Node() {
			this->course = aCourse;
		}
	};

	void InOrder(Node* aNode);

	Node* root;
};














#endif

