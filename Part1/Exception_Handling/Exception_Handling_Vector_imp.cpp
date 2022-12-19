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
struct Vector_base{
  A alloc; 
  T* elem; 
  T* space; 
  T* last; 
  Vector_base(const A& a, size_t n): alloc{a}, elem{alloc.allocate(n)}, space{elem + n}, last{elem + n}{}; 
  ~Vector_base(){alloc.deallocate(elem, last - elem);}
  Vector_base(const Vector_base& v1) = delete; //since vector_base is explicitly designed to represent memeory for Vector class, which can be used anywhere copy operations are deleted operation for such calss. 
  Vector_base& operator = (const Vector_base& v1) = delete; 
  Vector_base(Vector_base&& v1): alloc{v1.alloc}, 
                                 elem{v1.elem},
                                 last{v1.last}, 
                                 space{v1.space}{
    v1.elem = v1.space = v1.last = v1.alloc = nullptr; 
  }//Properly transffer ownership after the move operations. 
  Vector_base& operator=(Vector_base&& v1){
    swap(*this, v1); 
    return *this; 
  } 
};

template<class T, class A = allocator<T>>
class Vector{
private: 
  Vector_base<T, A>vb; 
  void destroy_elems(){
  for(T* p = vb.elem; p != vb.last; p++){
      p->~T(); 
    }
    vb.space = vb.elem; 
  }; 
public: 
  Vector(size_t n, const T& val = T(), A a = A()): vb{a, n}{
    unintialized_copy1(vb.elem, vb.elem + n, val); 
  }
  Vector(const Vector& v1); 
  Vector(Vector&& v1): vb{std::move(v1.vb)}{};   
  Vector& operator=(Vector& v1){
    swap(*this, v1); 
    return *this; 
  }
  size_t size(){return vb.space  - vb.elem;}
  size_t capacity(){return vb.last - vb.elem;}
  void resize(size_t n, const T&  = T{}); 
  void reserve(size_t n); 
  void push_back(const T& value); 
  T& operator [](const int index){
    if(index < 0 || index > size()){throw std::out_of_range{"out of range"};}
    return vb.elem[index]; 
  }
  ~Vector(){
    destroy_elems(); 
  }
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
