// waiter.h

#include<stdlib.h>
#include<string>
#include "user.h"
#include<vector>
#include "menu_item.h"
#include "menu_queue.h"
using namespace std;

#ifndef WAITER_H_
#define WAITER_H_

class waiter: public user{
	public:
		double total_sales;
		void view_menu();
		void input_order(int num);
		vector<menu_item> menu;
		menu_queue* chef_queue;
		menu_queue* receipt_queue;
		void print_receipt();
		void print_name();
		waiter(string name, string pass, vector<menu_item> m, menu_queue &cq, menu_queue &rq);
		~waiter();
};

//constructor, utilizes the user construtor
waiter::waiter(string name, string pass, vector<menu_item> m, menu_queue &cq, menu_queue &rq): user(name, pass){
	menu = m;
	chef_queue = &cq;
	receipt_queue = &rq;
	total_sales = 0;
}

//destructor
waiter::~waiter(){
	//cout<<"waiter deleted"<<endl;
	//deletes waiter
}

//push order to queue for chef
void waiter::input_order(int num){
	cout<<"how many items were ordered? (Max 10)"<<endl;
	int j;
	int i;
	cin>>j;

	while(j <= 0 || j > 10){
	cout<<"Invalid number of items, please try again: ";
	cin.clear(); //clear bad input flag
    	cin.ignore(1000, '\n');
	cin>>j;
	}

	for(i=1;i<=j;i++){
		cout<< "Please enter corresponding number for item in order" <<endl;
		int k;
		cin>>k;
		while(k < 1 || k > menu.size()){
			cout<<"invalid menu item number: please try again: "<<endl;
			cin.clear(); //clear bad input flag
    			cin.ignore(1000, '\n');
			cin>>k; 		
		}
		menu_item m1 = menu[k-1];
		m1.change_order_num(num);
		chef_queue->enqueue(m1);
	}
}

//prints receipt for specified order number
void waiter::print_receipt(){
	
	cout<<"what order number do you need a receipt for?"<<endl;
	int num;
	

	while(!(cin>>num)){
	cout<<"Invalid input, please try again: ";
	cin.clear(); //clear bad input flag
    	cin.ignore(1000, '\n');
	cin>>num;
	}




	if (receipt_queue->isEmpty()){
		if(chef_queue->check_inside(num)){
			throw (1);		
		}
		throw 'c';
	}

	if(receipt_queue->check_inside(num) && chef_queue->check_inside(num))
		throw (2.7);	
	double total = 0;
	while(num == receipt_queue->top().order_number){
		menu_item m = receipt_queue->top();
		total += m.price;
		m.print_name();
		receipt_queue->dequeue();
		if(receipt_queue->isEmpty()){
			break;		
		}
	}
	cout<<"total = $"<<total<<endl;
	total_sales+=total;
}

//view items on menu
void waiter::view_menu(){
	int i;
	for(i = 0;i<menu.size();i++){
		cout<< i+1 << ") ";
		menu[i].print_name();
	}
}

//prints name
void waiter::print_name(){
	cout<<username;
}

#endif
