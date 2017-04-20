#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <sys/mman.h>
#include <sys/types.h> shut
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class Message{
	protected:
		char message[50];
	public:
		Message();
		Message(char str[]);
		~Message();
		void print();
};

//constructor prompts user for input
Message::Message(){
	cout<<"What would you like the message to be?\n"<<endl;
	cin>>message;
}

//constructor user input parameter
Message::Message(char str[]){
	stpcpy(message, str);
}

//destructor deallocates memory pointed to by message
Message:: ~Message(){


}

//print method
void Message::print(){
	cout<< message <<endl;
}

//----------------------------------------------------------------------------
//morsecodeMessage class and functions below

class morseCodeMessage : public Message{
	private:
		string morse_message;
	public:
		int MorseCodeToLights();
		void print();
		void translate();
		morseCodeMessage();
		morseCodeMessage(char str[]);
		~morseCodeMessage();
};

//puts the morse code to lights
int morseCodeMessage::MorseCodeToLights(){
	int fd;		// for the file descriptor of the special file we need to open.
	unsigned long *BasePtr;		// base pointer, for the beginning of the memory page (mmap)
	unsigned long *PBDR, *PBDDR;	// pointers for port B DR/DDR

	fd = open("/dev/mem", O_RDWR|O_SYNC);	// open the special file /dem/mem
	if(fd == -1){
		printf("\n error\n");
		return (-1);  // failed open
	}

	// We need to map Address 0x80840000 (beginning of a memory page)
	// An entire memory page is mapped. We need to point to the beginning of the page.
	BasePtr = (unsigned long*)mmap(NULL,getpagesize(),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x80840000);
	if(BasePtr == MAP_FAILED){
		printf("\n Unable to map memory space \n");
		return (-2);
	}  // failed mmap

	// To access other registers in the page, we need to offset the base pointer to reach the
	// corresponding addresses. Those can be found in the board's manual.
	PBDR = BasePtr + 1;		// Address of port B DR is 0x80840004
	PBDDR = BasePtr + 5;	// Address of port B DDR is 0x80840014

	*PBDDR |= 0x20;			// configures port B7 as output (Green LED)
	*PBDDR &= 0xFFFFFFFE;	// configures port B0 as input (first push button). You could use: &= ~0x01

	int i;
	for(i=0;i<morse_message.length();i++){
		if(morse_message[i] == '.'){
			*PBDDR |= 0x20;			// red LED for dot

			*PBDR |= 0x20;	// ON: write a 1 to port B0. Mask all other bits.
			sleep(1);
			*PBDR &= ~0x20;
			sleep(1);
		}
		else if(morse_message[i] == '-'){
			*PBDDR |= 0x40;			// yellow LED for dash

			*PBDR |= 0x40;	// ON: write a 1 to port B0. Mask all other bits.
			sleep(1);
			*PBDR &= ~0x40;
			sleep(1);
		}
		else{
			*PBDDR |= 0x80;			// green LED for end of word

			*PBDR |= 0x80;	// ON: write a 1 to port B0. Mask all other bits.
			sleep(1);
			*PBDR &= ~0x80;
			sleep(1);
		}
	}

	//green LED for end of last word
	*PBDDR |= 0x80;			// green LED for end of word

	*PBDR |= 0x80;	// ON: write a 1 to port B0. Mask all other bits.
	sleep(1);
	*PBDR &= ~0x80;
	sleep(1);

	close(fd);	// close the special file
	return 0;
}

//translates message into morse code
void morseCodeMessage::translate(){

	//array used for the translation
	string morseCode[] = {".-", "-...", "-.-.", "-..", ".", "..-.",
							"--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
							".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
							"-.--", "--.."};

	char ch;
	morse_message = "";

	//translates into morse code and input into morse_message string
	for(int i = 0; i<strlen(message);i++){
		ch = toupper(message[i]);
		if(isspace(message[i])){
			morse_message += " ";
		}
		else morse_message += morseCode[ch - 'A'];
	}
}

//constructor
morseCodeMessage::morseCodeMessage() : Message(){
	translate();
}

//constructor
morseCodeMessage::morseCodeMessage(char str[]) : Message(str){
	translate();
}

//prints english message and morse code message
void morseCodeMessage::print(){
	cout<<message<<"\n"<<morse_message<<endl;
}

//destructor
morseCodeMessage::~morseCodeMessage(){

}

//--------------------------------------------------------------
///Message stack class and functions below

class messageStack{
	public:
		messageStack(const Message m);
		~messageStack();
		void push(const Message m);
		Message pop();
		void print_stack();
		bool isEmpty();


	private:
		//stack node with reference to next element
		struct StackNode{
			Message m;
			StackNode *next;

			//stack node constructor
			StackNode(Message element, StackNode *nextNode): m(element), next(nextNode){}
		};

		StackNode *top;
};

//stack constructor
messageStack::messageStack(const Message m){
	top = NULL;
	push(m);
}

//stack destructor
messageStack::~messageStack(){
	while(!isEmpty()){
		pop();
	}
}

//push element onto stack and have next node be previous top of stack
void messageStack::push(const Message m){
	top = new StackNode(m, top);
}

//pop element from stack
Message messageStack::pop(){
	if(!isEmpty()){
		StackNode *topNode = top;
		Message m1 = top->m;
		top = top->next;
		delete topNode;
		return m1;
	}
	return NULL;
}

//is empty boolean
bool messageStack::isEmpty(){
	if(top==NULL){
		return true;
	}
	else return false;
}

//prints all elements in stack
void messageStack::print_stack(){
	cout<<"printing stack"<<endl;
	StackNode *topNode = top;
	while(topNode != NULL){
		topNode->m.print();
		topNode = topNode->next;
	}
}



int main(){

	//create messages
	Message m1;
	Message m2("message2");
	morseCodeMessage m3("hey friend");

	//print morse code print
	m3.print();

	//print message print
	m2.print();

	//push to stack
	messageStack stack(m1);
	stack.push(m2);
	stack.push(m3);

	//print stack
	stack.print_stack();

	int j = m3.MorseCodeToLights();


	//morseCodeMessage m1("hey buddy");
	//m1.MorseCodeToLights();
	return 0;
}

