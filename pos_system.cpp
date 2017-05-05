#include "chef.h"
#include "waiter.h"
#include "manager.h"
#include "user.h"
#include "menu_item.h"
#include "menu_queue.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int index;
char type;

int main(){

	//create items for menu	
	vector<string> spaghetti_and_meatballs{"1 cup spaghetti","1/2 cups marinara", "2 meatballs"};	
	vector<string> oven_baked_chicken{"1 oven roasted chicken breast", "1 tbsp special seasoning", 
				"3/4 cups mashed potatoes", "drizzle of brown gravy"};
	vector<string> chicken_fried_steak{"8oz battered and fried sirloin steak", "3/4 cup mashed potatoes", 					"1/4 white gravy"};
	menu_item m1("spaghetti_and_meatballs", spaghetti_and_meatballs, 12.50);
	menu_item m2("oven_baked_chicken", oven_baked_chicken, 15.00);
	menu_item m3("chicken_friend_steak", chicken_fried_steak, 13.95);
	
	//add items to menu
	vector<menu_item> menu;
	menu.push_back(m1);
	menu.push_back(m2);
	menu.push_back(m3);
	
	//create queues for order management
	menu_queue chef_queue;
	menu_queue cooked_queue;
	
	//users master list
	vector<waiter> wait_master;
	vector<chef> chef_master;
	vector<manager> man_master;	
	
	//first order number
	int order_number = 50;
	
	//read in users from file
	fstream file;
	file.open("user_database.txt", ios::in|ios::app);
	char c;
	string n;
	string pass;
	while(!file.eof()){
		file>>c;
		file>>n;
		file>>pass;
		//create waiter
		if(c=='w'){
			waiter w1(n, pass, menu, chef_queue, cooked_queue);
			wait_master.push_back(w1);
		}
		else if(c == 'c'){
			chef c1(n, pass, chef_queue, cooked_queue);
			chef_master.push_back(c1);
		}
		else if(c == 'm'){
			manager m1(n, pass, menu, chef_queue, cooked_queue, wait_master, chef_master);
			man_master.push_back(m1);
		}
	}
	file.close();
	
	//used to write to users file when new users are created
	ofstream output_file;
	output_file.open("user_database.txt", ios::app);

	//looping of program begins
	//master int for most out loop
	int master = 0;
	while(master!=1){
		//log in at top of program for program to begin
		beginning:
			string name;
			string pass;
			cout<<"Enter username: "<<endl;
			cin>>name;
			cout<<"Enter password: "<<endl;
			cin>>pass;
		
			int i;

			//checks if username exists and if password matches any users on any of the master lists
			for(i=0;i<wait_master.size();i++){
				//login successful
				if(wait_master[i].login(name, pass)){
					index = i;
					int j = 0;
					while(j!=1){
						//loops through all waiter actions
						cout<<"What action would you like to take input order (I), "<<endl;
						cout<<"print receipt (P), view menu (M), or logout (L)?"<<endl;
						cin>>type;
						switch(type){
							case 'I':
								wait_master[index].input_order(order_number);
								cout<<"order input complete"<<endl;
								order_number++;
								break;
							case 'P':
								try{
									wait_master[index].print_receipt();
									cout<<"receipt done printing"<<endl;
								}
								catch(int i)
								{
									cout<<"Print reciept failed: Order not cooked yet."<<endl;
								}
								catch(char c)
								{
									cout<<"Print reciept failed: Order does not exist."<<endl;
								}
								catch(double d)
								{
									cout<<"Print reciept failed: Order not completely cooked."<<endl;
								}
								break;
							case 'M':
								wait_master[index].view_menu();
								break;
							case 'L':
								cout<<"logging out"<<endl;
								j=1;
								break;
							default: 
								cout<<"Incorrect command entered, please try again"<<endl;
								cin.clear();
						    		cin.ignore(1000, '\n');
								break;
						}
					}
					goto logout;
				}
			}
			
			
			for(i=0;i<chef_master.size();i++){
				//login successful
				if(chef_master[i].login(name, pass)){
					index = i;
					int j = 0;
					//loops through all chef actions
					while(j!=1){
						cout<<"What action would you like to take: cook item (C), "<<endl; 							cout<<"view chef's queue (V), view ingredients of next item (I), "<<endl;
						cout<<"or logout (L)?"<<endl;
						cin>>type;
						switch(type){
							case 'C':
								chef_master[index].cook_item();
								break;
							case 'V':
								chef_master[index].view_cq();
								break;
							case 'I':
								chef_master[index].view_ingredients();
								break;
							case 'L':
								cout<<"logging out"<<endl;
								j = 1;
								break;
							default: 
								cout<<"Incorrect command entered, please try again"<<endl;
								cin.clear();
						    		cin.ignore(1000, '\n');
								break;
						}				
					}
					goto logout;
				}
			}

			for(i=0;i<man_master.size();i++){
				//login successful
				if(man_master[i].login(name, pass)){
					index = i;
					int j = 0;
					while(j!=1){
						//loops through all manager actions
						string name, password;
						cout<<"What action would you like to take input order (I), "<<endl;
						cout<<"print receipt (P), view menu (M), add user (U) or logout (L)?"<<endl;
						cin>>type;
						switch(type){
							case 'I':
								man_master[index].input_order(order_number);
								cout<<"order input complete"<<endl;
								order_number++;
								break;
							case 'P':
								try{
									man_master[index].print_receipt();
									cout<<"receipt done printing"<<endl;
									break;
								}
								catch(int i)
								{
									cout<<"Print reciept failed: Order not cooked yet."<<endl;
								}
								catch(char c)
								{
									cout<<"Print reciept failed: Order does not exist."<<endl;
								}
								catch(double d)
								{
									cout<<"Print reciept failed: Order not completely"; 
									cout<<" cooked."<<endl;
								}
								break;
							case 'M':
								man_master[index].view_menu();
								break;
							case 'U':
								cout<<"Enter username: ";
								cin>>name;
								cout<<"Enter password: ";
								cin>>password;
								cout<<"Would you like to create a chef (C) or a waiter"; 									cout<<" (W)?"<<endl;
								
								cin>>type;
								if(type == 'c' || type == 'C'){
									man_master[index].create_Chef(name, password);
									output_file<<'c'<<" "<<name<<" "<<password<<'\n';
									cout<<"Account successfully created."<<endl;
								}
								if(type == 'w' || type == 'W'){
									man_master[index].create_Waiter(name, password);
									output_file<<'w'<<" "<<name<<" "<<password<<'\n';
									cout<<"Account successfully created."<<endl;
								}
								break;
							case 'S':
								man_master[index].view_sales();
								break;
							case 'L':
								cout<<"logging out"<<endl;
								j = 1;
								break;
							default: 
								cout<<"Incorrect command entered, please try again"<<endl;
								cin.clear();
						    		cin.ignore(1000, '\n');
								break;
						}
					}
					goto logout;
				}
			}
			
			//no succesful login is this statement is reached	
			cout<<"login unsuccessful, please try again (t) or end program (e)"<<endl;
			char c;
			cin>>c;
			switch(c){
				case 't':
					goto beginning;
				case 'e':
					goto end;
				default:	
					cout<<"Error: Incorrect command entered, program will end"<<endl;
					goto end;			
			}
		
		//used to log ou people who were in system or to log into a different account
		logout:
			cout<<"log in as another user (A) or press any other button to end program."<<endl;
			cin>>type;
			switch(type){
				case 'A':
					goto beginning;
				default:
					cout<<"Program closing!"<<endl;
					goto end;
			
			}
		//break outermost loop
		end:
			master = 1;
	}
	
	//close file
	output_file.close();

	//end program
	return 0;
}
