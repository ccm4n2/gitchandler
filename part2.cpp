//lab10 part 2

#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Signal{
	public:
		int length;
		double max_value, average;
		vector<double> data;
		void set_average();

	
		void operator+(double a);
		void operator*(double a);
		void statistics();
		void normalize();
		void center();
		void sig_info();
		void save_file(string str);
		Signal();
		Signal(int n);
		Signal(string str);
		Signal(int max, vector<double> data1);
		~Signal();
};

//Signal functions

void Signal::sig_info(){
	std::cout<<"Length: "<< length <<" Maximum value: "<< max_value << " Average value: " << average << "\n"<<std::endl;
}

void Signal::save_file(string str){
	ofstream output_file;
	output_file.open(str.c_str());
	output_file<<length<<" "<<max_value<<"\n";
	int i;
	for(i=0;i<length;i++){
		output_file<< data[i]<< "\n";
	}
	output_file.close();
}

void Signal::operator+(double a){
	max_value = 0;
	int i;
	for(i=0;i<length;i++){
		data[i] += a;
		if(data[i]>= max_value) max_value = data[i];
	}
	set_average();
}

void Signal::operator*(double a){
	if(a == 0) throw Signal();
	max_value = 0;
	int i;
	for(i=0;i<length;i++){
		data[i] *= a;
		if(data[i]>= max_value) max_value = data[i];
	}
	set_average();
}

void Signal::statistics(){
	std::cout<<"Maximum value: "<< max_value << " Average value: " << average << "\n" <<std::endl;
}

void Signal::normalize(){
	operator+(-average);
}

void Signal::center(){
	operator*(1/max_value);
	
}

Signal::Signal(int max, vector<double> data1){
	max_value = max;
	data = data1;
	length = data1.size();
	set_average();
}

Signal::Signal(){
	length = 0;
	max_value = 0;
	average = 0;
}

Signal::Signal(int n){
	char str[15];
	if(n<10){
		sprintf(str, "Raw_data_0%d.txt", n);
	}
	else{
		sprintf(str, "Raw_data_%d.txt", n);
	}
	try{
	std::ifstream in_file (str, std::ifstream::in);
	if(in_file.is_open()==true){
		in_file>>length;
		in_file>>max_value;
		
		//reading data into array	
		int i;
		double d;
		for(i=0;i<length;i++){	
			in_file >> d;
			data.push_back(d);
		}
		set_average();
		in_file.close();
	}
	else{
		throw (0);
	}
	}
	catch(...){
		throw (0);	
	}
}

Signal::Signal(string str){
	//checking for specified signal file and reading length and max if available
	std::ifstream in_file(str.c_str(), std::ifstream::in);
	if(in_file.is_open()==true){
		in_file>>length;
		in_file>>max_value;
				
		//reading data into array	
		int i;
		double d;
		for(i=0;i<length;i++){	
			in_file >> d;
			data.push_back(d);
		}
		
		set_average();
		in_file.close();
	}
	else{
		throw "bad file name";
	}
}

Signal::~Signal(){
	
}

void Signal::set_average(){
	double total = 0;
	int i;
	for(i = 0; i<data.size();i++) total += data[i];

	average = total/data.size();
}

//non-member addition function
Signal operator+(const Signal &s1, const Signal &s2){
	if(s1.length == s2.length){
		int i;
		vector<double> data1;
		for(i=0;i<s1.length;i++) data1.push_back(s1.data[i]+s2.data[i]);
		double max;

		if(s1.max_value >=s2.max_value) max = s1.max_value;
		else max = s2.max_value;
		
		Signal s3(max, data1);
		return s3;
	}
	else{
		cout<<"Signals could not be added not the same length"<<endl;
		return NULL;	
	}
}

//main running functions
int main(int argc, char *argv[]){
	char c[5];
	char file_name[50];
	int n;
	

	//demonstrates addition operator
	Signal add1(1);
	Signal add2(2);
	Signal sum = operator+(add1, add2);
	int i;
	std::cout<<sum.max_value<<std::endl;
	for(i=0;i<sum.length;i++) std::cout<<sum.data[i]<<std::endl;


	Signal *s2 = NULL;
	if(argc == 1){
		//no command line inputs
		std::cout<<"Would you like to Enter a file name (name) or file number (num)?\n";
		std::cin>>c;
		
		//name
		if(strcmp(c, "name")==0){
			std::cout<<"Please enter filename\n";
			std::cin>>file_name;
			try{
				Signal s1(file_name);
				s2 = &s1;
			}
			catch(const char* s){
				cout << "Invalid file name entered, program terminated" << endl;
				return 0;			
			}
		}
		
		//number
		else if(strcmp(c, "num")==0){
			std::cout<<"Please enter file number\n";
			std::cin>>n;
			try{
				Signal s1(n);
				s2 = &s1;
			}
			catch(const int s){
				cout << "Invalid file number entered, program terminated" << endl;
				return 0;			
			}
		}
		
		//default file
		else{
			std::cout<<"Default File being opening, proper command not input by user"<<std::endl;
			Signal s1;
			s2 = &s1;
		}
	}
	
	//command line inputs
	else{
		//number
		if(strcmp(argv[1], "-n") == 0){
			n = atoi(argv[2]);
			try{
				Signal s1(n);
				s2 = &s1;
			}
			catch(const int s){
				cout << "Invalid file number entered, program terminated" << endl;
				return 0;			
			}
		}
		
		//name
		else if(strcmp(argv[1], "-f") == 0){
			char* name;
			name = argv[2];
			try{
				Signal s1(file_name);
				s2 = &s1;
			}
			catch(const char* s){
				cout << "Invalid file name entered, program terminated" << endl;
				return 0;			
			}
		}
		
		//default
		else{
			std::cout<<"Default File being opening, proper command not input by user"<<std::endl;
			Signal s1;
			s2 = &s1;
		}
	}
	
	//while loop so user can do what they want with the signal
	int w = 0;
	char operation;
	while(w==0){
		std::cout<<"What would you like to do with the following Signal? \nCenter(C) Normalize(N) Offset(O) Scale(S) Stats(s) Write to file(W) Info(I) End(E)\n"<<std::endl;
		std::cin>>operation;
		
		switch(operation){
			case 'C':
				s2->center();
				break;
			case 'N':
				s2->normalize();
				break;
			case 'S':
				double scalar;
				std::cout<<"Scale by what number? \n"<<std::endl;
				std:cin>>scalar;
				try{	
					*s2*(scalar);
				}
				catch(Signal & s3){
					cout<< "Cannot scale by zero data not scaled"<< endl;
				}
				catch(...){
					cout<< "general exception caught data not scaled"<<endl;
				}
				break;
			case 'O':
				double offset;
				std::cout<<"Offset by what number? \n"<<std::endl;
				std::cin>>offset;
				*s2+(offset);
				break;
			case 's':
				s2->statistics();
				break;
			case 'W':
				char name[20];
				std::cout<<"Enter new file name \n"<<std::endl;
				std::cin>>name;
				s2->save_file(name);
				break;
			case 'I':
				s2->sig_info();
				break;
			case 'E':
				w++;
				break;
			default:
				std::cout<<"Invalid action entered please try again"<<std::endl;
				break;
		}
	}
	
	return 0;
}
