#include <vector>
#include "HashTable.h"
#include "ParseFile.h"

using namespace std;

//default constructor
HashTable::HashTable() {
	_courseNodes.resize(_size);
}

//parameterized constructor
HashTable::HashTable(unsigned int size) {
	_courseNodes.resize(size);
}

//destructor
HashTable::~HashTable() {
	Node* curptr = nullptr;
	for (int i = 0; i < _size; i++) {
		curptr = _courseNodes.at(i);
		while (curptr != nullptr) {
			_courseNodes.at(i) = curptr->_next;
			delete curptr;
			curptr = _courseNodes.at(i);
		}
	}
}

/*function to hash the CourseID and return a key as an int
@param courseID as a string to be hashed
*/
unsigned int HashTable::Hash(string aCourseID) {

	string sub = aCourseID.substr(4, 3);			//take a substring of the course to hash
	unsigned int key = atoi(sub.c_str());			//convert substring to an int
	key = ((key*key * 33 / 1000) % 100) ;			//compute and return the key
	key = key % _size;

	//print statements for testing
	//cout << "courseID before hash: " << aCourseID << endl;
	//cout << "subscript: " << sub << endl;
	//cout << "atoi key: " << key << endl;
	//key = key * key;
	//cout << "key squared: " << key << endl;;
	//cout << "key modulo size: " << key << endl;
	return key;
}

/*function to insert a course into the hash table
@param a course object that needs to be added
*/
void HashTable::Insert(Course course) {
	//cout << "****" << course._courseID << "*****\n";
	unsigned int key = Hash(course._courseID);		//hash the courseID to determine the key
	//cout << "key:" << key << endl;
	Node* curNode = _courseNodes.at(key);			

	if (curNode == nullptr) {						//hashtable is empty, add course at the key
		//Node* newNode = new Node(course, key);
		_courseNodes.at(key) = new Node(course, key);
		//_courseNodes.insert(_courseNodes.begin() + key, newNode);
		//cout << "inside insert at 0\n";
		 //_courseNodes.at(key)->_course.DisplayCourse();
	}
	else {											//hashtable has an empty node pointer, add course at the key
		if (curNode->_key == UINT_MAX) {
			curNode->_key = key;
			curNode->_course = course;
			curNode->_next = nullptr;
		}
		else {										//hashtable is not empty, implement chaining technique
			while (curNode->_next != nullptr) {
				curNode = curNode->_next;
			}
			curNode->_next = new Node(course, key);			//add course at the end of the linked-list
			//cout << "inside insert at linkedlist\n";
			//_courseNodes.at(key)->_course.DisplayCourse();
		}
	
	}

}

/*function to search for a course given a courseID
@param pass in courseID by reference for the function calling search to keep the altered courseID
@return an empty course if course is not found or return the matching course*/
Course& HashTable::Search(string& courseID) {

	//if the user inputed courseID is in lower-case, convert them to upper-case
	for (unsigned int i = 0; i < 4; i++) {
		courseID.at(i) = toupper(courseID.at(i));
	}

	//determine the key by calling Hash()
	unsigned int key = Hash(courseID);
	Course emptyCourse = Course();

	//hashtable is empty, return an empty course
	if (_courseNodes.at(key) == nullptr) {
		return emptyCourse;
	}
	//return the course or traverse the linked-list until matching course is found and return it
	else {
		Node* curNode = _courseNodes.at(key);

		while (curNode != nullptr) {
			if (curNode->_course._courseID == courseID) {
				//cout << "key: " << curNode->_key << endl;
				return curNode->_course;
			}
			else {
				curNode = curNode->_next;
			}
		}
		if (curNode == nullptr) {
			return emptyCourse;
		}
		
	}
}

/*function to print a given course
@param courseID to search for and print if there is a matching course
*/
void HashTable::PrintCourse(string courseID) {
	Course aCourse = Search(courseID);		//call Search() to find the course
	if (aCourse._courseID == courseID) {	//if a match is found
		aCourse.DisplayCourse();			//display the course
	}
	else {
		cout << "Course was not found\n";	//course was not found
	}

}

/*function to print courses as is in the hashtable
*/
void HashTable::PrintAllUnsorted() {
	 
	for (unsigned int i = 0; i < _courseNodes.size(); i++) {	//iterate over the hashtable's vector
		//cout << "inside the loop\n";
		Node* curNode = _courseNodes.at(i);		
		//cout << "inside loop: " << i << endl;
		//if (curNode != nullptr) {
			//cout << curNode->_course._courseID << curNode->_course._courseName << endl;

			while (curNode != nullptr) {		//iterate over each linked-list
				//cout << "inside the linkedlist\n";
				//cout << curNode->_course._courseID << curNode->_course._courseName << endl;
				curNode->_course.DisplayCourse();		//display the course
				//cout << endl;
				curNode = curNode->_next;				//advance the pointer
			//}
		}
	}
}


/*function to create a course vector in preparation for sorting*/
void HashTable::CreateCourseVector() {
	Node* curNode = nullptr;

	//copy hashtable's courses into a vector of course pointers
	for (unsigned int i = 0; i < _courseNodes.size(); i++) {	//iterate over the hashtable
		curNode = _courseNodes.at(i);
		if (curNode != nullptr) {								//for the first node pointer in the hash table
			Course* coursePtr = new Course(curNode->_course);	//create new Course object pointer
			_vectorCourses.push_back(coursePtr);				//add course object pointer to vector of courses

			while (curNode->_next != nullptr) {					//iterate over each linked-list
				curNode = curNode->_next;						
				Course* coursePtr = new Course(curNode->_course);	//create a new course and its pointer
				_vectorCourses.push_back(coursePtr);				//add course object pointer to vector of courses
			}
			
		}	
	}

	/*Print statements for testing
	for (unsigned int i = 0; i < _vectorCourses.size(); i++) {
		Course* current = _vectorCourses.at(i);
		current->DisplayCourse();
	}
	cout << "======================================\n";*/
}

/*function to partition the course object vector based on the courseIDs
@param two integers to specify the indices 
@return the end of the low partition
*/
int HashTable::Partition(int low, int high) {
	int midpoint = low + (high - low) / 2;									//determine midpoint
	string pivot = _vectorCourses.at(midpoint)->_courseID.c_str();			//set pivot value to courseID at pivot
	bool isDone = false;
	Course* temp = nullptr;

	while (!isDone) {
		while (pivot > _vectorCourses.at(low)->_courseID.c_str()) {			//increment low while courseID at low is less than pivot
			++low;
		}
		while (pivot < _vectorCourses.at(high)->_courseID.c_str()) {		//decrement high while courseID at high is greater than pivot
			--high;
		}
		if (low >= high) {													//break if low greater than or equal to high
			isDone = true;
		}
		else {																//else swap course pointers at low and high
			temp = _vectorCourses.at(low);
			_vectorCourses.at(low) = _vectorCourses.at(high);
			_vectorCourses.at(high) = temp;
			++low;
			--high;
		}
	}

	return high;

}

/*function to sort course object vectors
@param two int indices to designate the start and end
*/
void HashTable::QuickSort(int low, int high) {
	if (low >= high) {				//base case
		return;
	}
	int mid = Partition(low, high);	//partition and set the midpoint
	QuickSort(low, mid);			
	QuickSort(mid + 1, high);
}

/*function to print the sorted course objects
*/
void HashTable::PrintSorted() {
	CreateCourseVector();
	QuickSort(0, _vectorCourses.size()-1);

	for (unsigned int i = 0; i < _vectorCourses.size(); i++) {
		Course* curCourse = _vectorCourses.at(i);
		curCourse->DisplayCourse();
	}
}