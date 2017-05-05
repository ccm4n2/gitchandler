// manager.h

#include<stdlib.h>
#include<string>
#include "waiter.h"
#include "user.h"
#include "chef.h"
#include<vector>
using namespace std;

#ifndef MANAGER_H_
#define MANAGER_H_

class manager: public waiter{
	protected:
		vector<waiter>* wait_list;
		vector<chef>* chef_list;
	public:
		manager(string name, string pass, vector<menu_item> m, menu_queue &cq, menu_queue &rq, vector<waiter> &waiters, 				vector<chef> &chefs);
		~manager();
		void create_Waiter(string name, string pass);
		void create_Chef(string name, string pass);
		void view_sales();
		menu_queue cancel_order();
};

//constructor
manager::manager(string name, string pass, vector<menu_item> m, menu_queue &cq, menu_queue &rq, vector<waiter> &waiters, 				vector<chef> &chefs): waiter(name, pass, m, cq, rq){
	wait_list = &waiters;
	chef_list = &chefs;	
}


//destructor
manager::~manager(){
	//deletes manager
}

//create new waiter in system
void manager::create_Waiter(string name, string pass){	
	waiter wtemp(name, pass, menu, *chef_queue, *receipt_queue);
	wait_list->push_back(wtemp);
}

//create new chef in system
void manager::create_Chef(string name, string pass){	
		chef ctemp(name, pass, *chef_queue, *receipt_queue);
		chef_list->push_back(ctemp);
}

//view total sales figure of all waiters
void manager::view_sales(){
	int i;
	for(i=0;i<wait_list->size();i++){
		(*wait_list)[i].print_name();
		cout<<" "<<(*wait_list)[i].total_sales<<endl;
	}
}

//cancels order from chef queue
/**menu_queue manager::cancel_order(){
		
	cout<<"what order number do you need to cancel?"<<endl;
	int num;
	

	while(!(cin>>num)){
		cout<<"Invalid input, please try again: ";
		cin.clear(); //clear bad input flag
    		cin.ignore(1000, '\n');
	}


	return chef_queue->delete_order(num);
}**/

#endif
