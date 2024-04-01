#include <iostream>
#include "shared_stack.h"


void TestStack(){
	SharedStack<double> stack;
	stack.push(5.0);
	stack.pop();
	std::cout<<"stack.size()"<<stack.size()<<std::endl;
}

int main(int arc,char*argv[]){
TestStack();

}
