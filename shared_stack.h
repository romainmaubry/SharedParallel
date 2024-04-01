#pragma once

template<class T>
class SharedStack{
   public:
   T pop();
   void push(const T& value);
   size_t size();

};
