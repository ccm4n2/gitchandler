// user.h

#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;

#ifndef USER_H_
#define USER_H_

class user{
	protected:
		string username;
		string password;
	public:
		user(string name, string pass);
		bool login(string name, string pass);
};

//constructs a user
user::user(string name, string pass){
	//cout<<"user created"<<endl;
	username = name;
	password = pass;
}

bool user::login(string name, string pass){
	if(!username.compare(name) && !password.compare(pass)) {
		cout<<"log in successful"<<endl;
		return true; //username and password entered match
	}
	else {
		//cout<<"log in unsuccessful"<<endl;
		return false; //do not match	
	}
}

#endif
