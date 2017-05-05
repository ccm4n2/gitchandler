// menu_queue.h

#include<stdlib.h>
#include<string>
#include "menu_item.h"
using namespace std;

#ifndef MENU_QUEUE_H_
#define MENU_QUEUE_H_

class menu_queue{
	private:
		struct node{
			menu_item m;
			node *next;	
		};

        	node *rear;
        	node *front;

	public:
		menu_item top();
        	menu_queue();
		bool isEmpty();
		~menu_queue();
		void enqueue(menu_item item);
		void dequeue();
		void display();
		bool check_inside(int order);
		menu_queue delete_order(int order);
};

//constructor
menu_queue::menu_queue(){
    	rear = NULL;
    	front = NULL;
}

//returns top menu item
menu_item menu_queue::top(){
	return front->m;
}

//returns true if queue is empty
bool menu_queue::isEmpty(){
	if(front == NULL){
		return true;
	}
	return false;
}

//adds item to queue
void menu_queue::enqueue(menu_item item){
	node *temp = new node;
	temp->m = item;
	temp->next = NULL;
	if(front == NULL){
		front = temp;
	}
	else{
		rear->next = temp;
	}
	rear = temp;
}

//removes item from queue
void menu_queue::dequeue(){
	node *temp = new node;
	if(front == NULL){
        	cout<<"\nQueue is Emtpty\n";
	}
	else{
    		temp = front;
    		front = front->next;
        	delete temp;
	}
}

//displays entire queue
void menu_queue::display(){
	node *p = new node;
	p = front;
	if(front == NULL){
       		cout<<"\nNothing to Display\n";
	}
	else{
        	while(p!=NULL){
			cout<< p->m.order_number<<" ";
			p->m.print_name();
            		p = p->next;
        	}
    	}
}

//checks if specified order is inside queue returns true if it is
bool menu_queue::check_inside(int order){
	if(isEmpty()) return false;
	else{
		node* temp = new node;
		temp = front;
		while(temp!=NULL){
			if(order == temp->m.order_number){
				return true;
			}
			temp = temp->next;		
		}
	}
	return false;
}

//deletes order from queue if it exists
/**menu_queue menu_queue::delete_order(int order){
	if(check_inside(order)){
		node* temp = new node;
		menu_queue cq;
		temp = front;
		temp->m = front->m;
		while(temp!=NULL){
			if(order == temp->m.order_number){
				//do nothing
			}			
			else{
				cq.enqueue(temp->m);
			}
			temp = temp->next;		
		}
		return cq;
	}
	else{
		//do nothing
		cout<<"Specified Order not in queue"<<endl;
		return *this;
	}
}**/

//destructor
menu_queue::~menu_queue(){
	while(front!=NULL){
		dequeue();	
	}
}
#endif
