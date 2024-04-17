#pragma once
#include <stack>
#include <mutex>
#include <atomic>

// Thread safe stack
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

//Lock free stack
template<class T>
class LfStack{
  private:
    struct node{
      T value;
      node* next;
      node(const T &val):value(val){}

    };
    std::atomic<node*> head;

  public:
    T pop();
    void push(const T& value);
    size_t size();

  private:

    std::mutex m;
    std::stack<T> stack;

};

template<class T> size_t LfStack<T>::size(){
  std::lock_guard<std::mutex> lock(m);
  return stack.size(); 
}

template<class T> T LfStack<T>::pop(){
  node* old_head=head.load();
  while(old_head!=nullptr && !head.compare_exchange_weak(old_head,old_head->next));
  if(old_head==nullptr)throw;
  T tmp=old_head->value;
  delete old_head;
  return std::move(tmp);
}

template<class T> void LfStack<T>::push(const T &value){
  node* new_node=new node(value);
  new_node->next=head.load();
  while(!head.compare_exchange_weak(new_node->next,new_node));
}

//Lock free stack with smart pointer
template<class T>
class LfSStack{
  private:
    struct node{
      T value;
      std::shared_ptr<node> next;
    };
    std::shared_ptr<node> head;

  public:
    T pop();
    void push(const T& value);
    size_t size();

  private:

    std::mutex m;
    std::stack<T> stack;

};

template<class T> size_t LfSStack<T>::size(){
  std::lock_guard<std::mutex> lock(m);
  return stack.size(); 
}

template<class T> T LfSStack<T>::pop(){
  std::shared_ptr<node> old_head=std::atomic_load(&head);
  while(old_head!=nullptr && !std::atomic_compare_exchange_weak(&head,&old_head,old_head->next));
  if(old_head==nullptr)throw;
  return std::move(old_head->value);
}

template<class T> void LfSStack<T>::push(const T &value){
  auto new_node=std::make_shared<node>();
  new_node->value=value;
  new_node->next=std::atomic_load(&head);
  while(!std::atomic_compare_exchange_weak(&head,&(new_node->next),new_node));
}

