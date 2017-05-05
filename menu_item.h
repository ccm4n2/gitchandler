// menu_item.h

#include<stdlib.h>
#include<string>
#include<vector>
using namespace std;

#ifndef MENU_ITEM_H_
#define MENU_ITEM_H_

class menu_item{
	public:
		string name;
		vector<string> ingredients;
		vector<int> customization;
		menu_item(string name1, vector<string> ingred);
		menu_item();
		~menu_item();
		void print();
		void print_name();
};

//create menu item
menu_item::menu_item(string name1, vector<string> ingred){
	name = name1;
	//cout<<name<<endl;
	ingredients = ingred;
	int i;
	for(i=0;i<ingredients.size();i++){
		//default is all ingredients are wanted	
		customization.push_back(1);
	}
}

//default constructor
menu_item::menu_item(){
	//leave vectors empty
}

//destructor
menu_item::~menu_item(){
	
}

//add ingredient to item
void menu_item::add_ingredient(string s){
	ingredients.push_back(s);
	customization.push_back(1);
}

//print ingredients
void menu_item::print(){
	int i;
	cout<< name << endl;
	for(i=0;i<ingredients.size();i++){
		cout << i << " " << ingredients[i] << endl;
	}
}

//prints only name
void menu_item::print_name(){
	cout<<name<<endl;
}

#endif
