// Lab7_strings.cpp
// This program shows some simple string examples, and asks for simple tasks.
// Reference: Lippman, section 3.2

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab7_strings.cpp -o Lab7_strings -std=c++11
//      or:  g++ Lab7_strings.cpp -o Lab7_strings -std=c++0x
// Some initialization methods and other things are not supported by the old standard. 

#include <iostream>
#include <string>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	string s1, s2("Hello"), s3 = "World";
	cout << "\nEnter a word:" << endl;
	cin >> s1;
	cin.ignore();	// to consume the '\n' character. Otherwise, you may get issues with
					// the getline() below. Try commenting this out. Any issues?
	
	string s4(s1);
	
	cout << s1 << endl
		 << s2 << endl
		 << s3 << endl
		 << s4 << endl;
	
	s1 = s2 + s3;
	cout << s1 << endl;

// ***********************************************************************
// Try all the operations in Table 3.2 using the strings above and
// using new strings that you may declare.
// Some of those operations have already been used, but write your
// own examples.
// ***********************************************************************

// -----------------------------------------------------------------------
	
	//writing to output stream
	cout<< s3<<endl;

	//reading to a string
	string s5;
	cout << "\nEnter a word:" << endl;
	cin >> s5;
	cin.ignore();

	//get line	
	string line;
	cout << "\nEnter some text:" << endl;
	getline(cin, line);
	cout << line << endl;

	//empty
	string s6;
	if(s6.empty()){
		cout<< "String is empty!"<<endl;		
	}

	//size
	cout<<"Size of s5: "<<s5.size()<<endl;

	//char and concatenation
	cout<<"first char in s5: "<<s5[0]<< ". Concatenation of s5 and s1: " << s5 + s1<<endl;

	//replacement and comparisons
	s1 = s5;
	if(s1==s5){
		cout<<"strings are equal!"<<endl;	
	}
	
	cout << "\nEnter some text, finish it with an &:" << endl;
	getline(cin, line, '&');	// the delimiter can be any character
	cout << line << endl;

// ***********************************************************************
// Use a "Range for" (Lippman, page 93) and operations in table 3.3 to:
// 1) change the case of the letters in your input line above (upper to
//    lowercase and vice-versa).
// 2) Replace any whitespace with a dot ('.').
// Print the converted text.
// ***********************************************************************

	for(auto &c : line){
		if(islower(c)) c = toupper(c);
		else if(isupper(c)) c = tolower(c);
		else if(isspace(c)) c = '.';
		else	;
	}
			
	cout<<line<<endl;
	return 0;
}
