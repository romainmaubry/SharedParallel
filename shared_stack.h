#pragma once
#include <stack>
#include <mutex>

template<class T>
class SharedStack{
  public:
    T pop();
    void push(const T& value);
    size_t size();

  private:

    std::mutex m;
    std::stack<T> stack;

};

template<class T> size_t SharedStack<T>::size(){
  std::lock_guard<std::mutex> lock(m);
  return stack.size(); 
}

template<class T> T SharedStack<T>::pop(){
  std::lock_guard<std::mutex> lock(m);
  if(stack.empty())throw;
  T value=std::move(stack.top());
  stack.pop(); 
  return std::move(value); 
}

template<class T> void SharedStack<T>::push(const T &value){
  std::lock_guard<std::mutex> lock(m);
  stack.emplace(value);
}
