// Lab7_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab7_vectors.cpp -o Lab7_vectors -std=c++11
//      or:  g++ Lab7_vectors.cpp -o Lab7_vectors -std=c++0x
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	vector<int> ivec1(5), ivec2;
	vector<double> dvec1{5.1}, dvec2(5,1.5);
	vector<string> svec1 = {"hello", "world"};
	// vector<myClass> myCvec;	// you can have vectors of objects
	// in general: vector<Type> vec;	// vector is a template

	for(int i = 0; i < ivec1.size(); i++)
		cout << ivec1[i] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:ivec1)	// This is equivalent to the above for loop
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec2)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:svec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
	cout << "Original size: " << ivec2.size() << endl;
	ivec2.push_back(50);
	cout << "New size: " << ivec2.size() << "\nAdded element: " << ivec2[0] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
// ***********************************************************************
// Try all the ways to initializa a vector shown in Table 3.4. Use the
// vectors above and/or declare new vectors.
// Some of those operations have already been used, but write your
// own examples.

// Do exercises 3.14 and 3.15 from Lippman (page 102)

// Try all the vector operations shown in table 3.5. Use the vectors above
// or define new ones. Try different types.
// ***********************************************************************

	//vector intializations
	vector<int> v1;
	vector<int> v2(ivec1);
	vector<int> v3 = ivec1;
	vector<int> v4(5, 10);
	vector<int> v5(6);
	vector<int> v6{1,2,3,4,5};
	vector<int> v7 = {1,2,3,4,5};

	//Excercise 3.14
	int i;
	cout << "Write a sequence of integers seperated by enters: " << endl;
	cin.clear();
	while(cin >> i) v1.push_back(i);
	
	cout << "\n" <<endl;

	

	for(int i = 0; i < v1.size(); i++) cout<< v1[i] << " ";

	//Excercise 3.15
	string word;
	vector<string> text;
	cout<< "\nWrite string: ";
	cin.clear();
	while(cin >> word) {
		if(word == "*") break;
		else text.push_back(word);
	}

	//operations in table 3.5  
	vector<int> v8;
	if(v8.empty()) cout << "Vector v8 is emtpty" << endl;

	cout<< v6[0] << " " <<v6.size() <<endl;
	v6.push_back(7);
	
	v6 = v7;
	if(v6 == v7) cout<< "v6 and v7 are equal" <<endl;
	v6 = {1,2,3};
	if(v6 != v7) cout<< "v6 and v7 are not equal" <<endl;
	

	return 0;
}
