#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <algorithm>

#include "shared_stack.h"

// Modify the stack
void ModifyStack(SharedStack<double> &stack,size_t ithread){
  //std::cout<<"From thread:"<<ithread<<std::endl;	
  stack.push(5.0);
  stack.pop();
}

//Test thread safe stack
void TestStack(){
  SharedStack<double> stack;
  size_t nthreads=50;
  std::vector<std::thread> t(nthreads);
  
  //Create threads
  for(size_t i=0;i<nthreads;i++){
    t[i]=std::thread(ModifyStack,std::ref(stack),i);
  }

  //Join threads
  std::for_each(t.begin(),t.end(),std::mem_fn(&std::thread::join));

  std::cout<<"stack.size()="<<stack.size()<<std::endl;
}

int main(int arc,char*argv[]){
  TestStack();
}
