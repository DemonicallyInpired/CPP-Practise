#include<iostream>
#include<vector>
using namespace std; 
template<class T>
void unintialized_copy1(T* beg, T* end, const T& val){
  T* p{}; 
  try{
    for(p = beg; p != end; p++){
      ::new(p)T{val}; 
    }
  }catch(...){
    for(T* start = beg; start != p; start++){
      start->~T(); 
    }
    throw; 
  }
}
template<class T, class A = allocator<T>>
class Vector{
private: 
  T* elem; 
  T* last; 
  T* space; 
  A alloc; 
public: 
  Vector(size_t n, const T& val = T(), A a = A()): alloc{a}{
    elem = alloc.allocate(n); 
    last = space = (elem + n); 
    try{
      unintialized_copy1(elem, last, val); 
  }catch(...){
      alloc.deallocate(elem, n); 
      throw; 
    }
  }
  Vector(const Vector& v1); 
  Vector(Vector&& v1); 
  size_t size(){return space  - elem;}
  size_t capacity(){return last - elem;}
  void resize(size_t n, const T&  = T{}); 
  void reserve(size_t n); 
  void push_back(const T& value); 
  T& operator [](const int index){
    if(index < 0 || index > size()){throw std::out_of_range{"out of range"};}
    return elem[index]; 
  }
  ~Vector(){}
};
class Points{
  private: 
    int x, y; 
  public: 
    Points(int a1 = 12, int b1 = 12): x{a1}, y{b1}{}; 
    friend ostream& operator <<(ostream& os, Points& p1){
      os << "{" << p1.x << "," << p1.y << "}" << endl; 
      return os; 
    }
}; 
int main(){
  Vector<Points>v1(12); 
  for(size_t i = 0; i < 12; i++){cout << v1[i];}
  return 0; 
}
