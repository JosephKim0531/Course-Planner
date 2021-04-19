#include <string>
#include <vector>
#include <iostream>

#include "BST.h"

using namespace std;


//default constructor
BST::BST() {
	this->root = nullptr;
}

/*function to add a node to the tree
@param a course to be inserted
*/
void BST::Insert(Course aCourse) {
	Node* curNode = root;

	if (curNode == nullptr) {		//empty binary search tree
		root = new Node(aCourse);	//add the course as the root node
	}
	else {							//the binary search tree is not empty
		while (curNode != nullptr) {
			if (aCourse._courseID < curNode->course._courseID) {		//if aCourse's courseID is less than the courseID of the current node, go left
				if (curNode->left == nullptr) {						//if the left pointer is empty, add aCourse to the left
					curNode->left = new Node(aCourse);
					curNode = nullptr;
				}
				else {
					curNode = curNode->left;						//else advance curNode to the left
				}
			}
			else {							//aCourse's courseID is greater than or equal to curNode's courseID
				if (curNode->right == nullptr) {		//if curNode->right is empty, add aCourse to the right
					curNode->right = new Node(aCourse);
					curNode = nullptr;
				}
				else {
					curNode = curNode->right;			//else advance curNode to the right
				}
			}
		}
	}
}

/*function to search for a course in the tree
@param a courseID to search for
@return an empty course or the matched course
*/
Course BST::Search(string courseID) {
	Node* curNode = root;

	if (curNode == nullptr) {
		Course tempCourse = Course();
		return tempCourse;
	}
	else {
		while (curNode != nullptr) {
			if (curNode->course._courseID == courseID) {
				return curNode->course;
			}
			else if (courseID < curNode->course._courseID) {
				curNode = curNode->left;
			}
			else {
				curNode = curNode->right;
			}
		}
	}
}

int BST::GetNumPrereqs(string courseID) {
	Course theCourse = Search(courseID);
	
	if (theCourse._courseID == "") {
		return -1;
	}
	else {
		return theCourse._prereqs.size();
	}
}

void BST::PrintACourse(string courseID) {
	Course theCourse = Search(courseID);

	if (theCourse._courseID == "") {
		cout << "Course does not exist\n";
	}
	else {
		theCourse.DisplayCourse();
	}
}

void BST::InOrder(Node* aNode) {
	Node* curNode = aNode;

	if (curNode == nullptr) {
		return;
	}
	InOrder(curNode->left);
	curNode->course.DisplayCourse();
	InOrder(curNode->right);
}

void BST::PrintInOrder() {
	Node* curNode = root;

	if (curNode == nullptr) {
		cout << "Empty List\n";
	}
	InOrder(curNode);
	
	
}