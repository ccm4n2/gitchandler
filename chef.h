// chef.h

#include<stdlib.h>
#include<string>
#include "user.h"
#include "menu_queue.h"
using namespace std;

#ifndef CHEF_H_
#define CHEF_H_

class chef: public user{
	public:
		chef(string name, string pass, menu_queue &cq, menu_queue &rq);
		menu_queue* chef_queue;
		menu_queue* receipt_queue;
		void view_cq();
		void cook_item();
		void view_ingredients();
};

//chef constructor
chef::chef(string name, string pass, menu_queue &cq, menu_queue &rq) : user(name, pass){
	chef_queue = &cq;
	receipt_queue = &rq;
}

//view queue of food that needs to be cooked
void chef::view_cq(){
	chef_queue->display();
}

//view ingredients of top menu item on queue, basically the next item that must be cooked
void chef::view_ingredients(){
	menu_item m = chef_queue->top();
	m.print();
}

//cook top item on cq and push to rq
void chef::cook_item(){
	if(chef_queue->isEmpty()){
		cout<<"No items in chef queue to cook, tell waiters to place orders"<<endl;
	}
	else{
		menu_item m = chef_queue->top();
		chef_queue->dequeue();
		receipt_queue->enqueue(m);
	}
}

#endif
