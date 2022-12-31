#include<iostream>
using namespace std; 
template<typename In, typename Out, class T>
Out unintialized_move(In b, In e, Out oo, const T& val = T{}){
  for(;b!=e;++b, ++oo){
    new(static_cast<void*>(&*oo))T{std::move(*b)}; 
    b->~T(); 
  }
  return b; 
}
template<typename In, class T>
void destroy(In b, In e){
  for(;b!=e; b++){
    b->~T(); 
  }
}
template<class F, class T>
void unintialized_copy(F begin, F end, const T& val = T{}){
  F p; 
  try{
    for(p = begin; p != end; p++){
      ::new(static_cast<void*>(&*p))T{val}; 
    }
  }catch(...){
    for(T* staring = begin; staring != p; staring++){
      staring->~T(); 
    }
  }
}
template<class T, class A = allocator<T>>
struct Vector_base{
  T* elem; 
  T* last; 
  T* space; 
  A alloc; 
  Vector_base(size_t n, A alloc1): alloc{alloc1}, elem{alloc.allocate(n)}, last{elem + n}, space{elem + n}{}; 
  Vector_base(const Vector_base& v1) = delete; 
  Vector_base& operator=(const Vector_base& v1) = delete; 
  Vector_base(Vector_base&& v1): elem{v1.elem}, last{v1.last}, space{v1.space}, alloc{v1.alloc}{
    v1.elem = v1.space = v1.last = nullptr; 
  }
  Vector_base& operator=(Vector_base&& v1){
    swap(*this, v1); 
    return *this; 
  }
  T* begin()const{return elem;}
  T* end()const{return last;}
}; 
template<class T, class A = allocator<T>>
class Vector{
private: 
  Vector_base<T, A>vb;
  void destroy_elements(); 
public: 
  Vector(size_t n, const T& val = T{}, A alloc = A()): vb{n, alloc}{
    unintialized_copy(vb.begin(), vb.end(), val); 
  };
  Vector(const Vector& v1): vb{v1.size(), v1.vb.alloc}{
    unintialized_copy(begin(), end(), *v1.vb.elem); 
  }; 
  Vector& operator=(const Vector& v1){
    if(capacity() < v1.size()){
      Vector vvec{v1}; 
      swap(*this, vvec); 
      return *this; 
    } 
    if(this == &v1){return *this;}
    size_t v1_size = v1.size(); 
    size_t currvecsize = size(); 
    vb.alloc = v1.vb.alloc; 
    if(v1_size <= currvecsize){
      unintialized_copy(begin(), end(), *v1.vb.elem);
      for(T* starting = vb.elem + v1_size; starting != vb.space; starting++){
        starting->~T(); 
      }
    }else{
      unintialized_copy(begin(), begin()+currvecsize, *v1.vb.elem); 
      unintialized_copy(begin()+currvecsize, begin()+ v1_size, *v1.vb.elem); 
    }
    vb.space = vb.elem + v1_size; 
    return *this; 
  }; 
  Vector(Vector&& v1): vb{std::move(v1.vb)}{}; 
  Vector& operator=(Vector&& v1){
    swap(*this, v1); 
    return *this; 
  } 
  T& operator[](const int index){
    if(index < 0 || index > size()){throw std::runtime_error{"out of range access"};}
    return vb.elem[index]; 
  }
  T* begin()const{return vb.elem;}
  T* end()const{return vb.last;}
  size_t size()const{return vb.last - vb.elem;}
  size_t capacity()const{return vb.space - vb.elem;}
  void resize(size_t n, const T& val = T{}); 
  void reserve(size_t newalloc){
    if(newalloc <= capacity()) return; 
    Vector_base<T, A> b(newalloc, vb.alloc);
    unintialized_move(vb.elem, vb.last, b.elem, T{}); 
    swap(vb, b);  
  }
  void push_back(T elem); 
  void clear(){resize(0);}
  ~Vector(){destroy_elements();}
};
template<class T, class A>
void Vector<T, A>::destroy_elements(){
  for(T* starting = vb.begin(); starting != vb.end(); starting++){
    starting->~T(); 
  }
}
struct Points{
  int x, y; 
  Points(int x1 = {}, int y1 = {}): x{x1}, y{y1}{}; 
  friend ostream& operator<<(ostream& os, const Points& p1){
    os << p1.x << " " << p1.y << endl; 
    return os; 
  }
};
template<class T, class A>
void Vector<T, A>::resize(size_t newsize, const T& val){
  reserve(newsize); 
  if(size() < newsize){
    unintialized_copy(vb.elem, vb.elem + newsize, val); 
  }else{
    destroy(vb.elem + size(), vb.elem + newsize); 
  }
  vb.space = vb.last = vb.elem + newsize;
}
template<class T, class A>
void Vector<T, A>::push_back(T elem){
  if(capacity() == size()){
    reserve(size() ? size()*2 : 8); 
  }
  vb.alloc.construct(&vb.elem[size()], elem); //add element to the end; 
  ++vb.space; 
}
Vector<int, allocator<int>>v1(12); 
Vector<Points>p1(12, Points{12, 12}); 
Vector<int>v2{Vector<int>(12)}; 
Vector<Points>p2{Vector<Points, allocator<Points>>{12, Points{12, 12}}}; 
Vector<int, allocator<int>>v3{v2}; 
Vector<Points>p3{p2};
Vector<int>v4 = Vector<int>(13);
Vector<int>v5 = Vector<int>(13, -2); 
enum class Test_Cases{
  CONSTRUCT_N_DEFAULT_ELEMENTS, 
  COPY_CONSTRUCTOR, 
  MOVE_CONSTRUCTOR, 
  COPY_ASSIGNMENT, 
  MOVE_ASSIGNMENT, 
  SIZE, 
  CAPACITY, 
}; 
void log_error_message(int test_no, string description, string message){
  cout << "TEST# " << test_no << " : " << description << ": " << message << endl; 
}
void test(int test_no, string description, string message, Test_Cases t1){
  bool pass = true; 
  switch(t1){
    case Test_Cases::CONSTRUCT_N_DEFAULT_ELEMENTS: {
      for(size_t i = 0; i < v1.size(); i++){
        if(v1[i] != 0){
          pass = false; message = "failed with Type t = <" + string{typeid(v1).name()} + string{">"};
          log_error_message(test_no, description, message); 
          break;
        } 
      }
      for(size_t i = 0; i < p1.size(); i++){
        if(p1[i].x != 12 && p1[i].y != 12){
          pass = false; message = "failed with Type t = <" + string{typeid(p1).name()} + string{">"}; 
          log_error_message(test_no, description, message); 
          break; 
        }
      }
      break; 
    }
    case Test_Cases::SIZE: {
      if(v1.size() != 12 && p1.size() != 12){
        pass = false; message = "failed with OPS::SIZE"; 
        log_error_message(test_no, description, message); 
      }
      break; 
    }
    case Test_Cases::CAPACITY: {
      if(v1.capacity() != 12 && p1.capacity() != 12){
        pass = false; message = "failed with ops::SIZE"; log_error_message(test_no, description, message); 
      }
      break; 
    }
    case Test_Cases::MOVE_CONSTRUCTOR: {
      for(size_t i = 0; i < v1.size(); i++){
        if(v1[i] != 0){
          pass = false; message = "failed with type T=<" + string{typeid(v1).name()} + ">"; 
          log_error_message(test_no, description, message); 
          break; 
        }
      }
      for(size_t i = 0; i < p1.size(); i++){
        if(p1[i].x != 12 && p1[i].y != 12){
          pass = false; message = "failed with type T=<" + string{typeid(p1).name()} + ">"; 
          log_error_message(test_no, description,  message); 
          break; 
        }
      }
      break; 
    }
    case Test_Cases::COPY_CONSTRUCTOR: {
      for(size_t i = 0; i < v3.size(); i++){
        if(v3[i] != 0){
          pass = false; message = "failed with type T=<" + string{typeid(v3).name()} + ">"; 
          log_error_message(test_no, description, message);
          break; 
        }
      }
      for(size_t i = 0; i < p3.size(); i++){
        if(p3[i].x != 12 && p3[i].y != 12){
          pass = false; message = "failed with type T =<" + string{typeid(p3).name()}+  ">"; 
          log_error_message(test_no, description, message); 
          break; 
        }
      }
      break; 
    }
    case Test_Cases::COPY_ASSIGNMENT: {
      v4 = v5; 
      for(size_t i = 0; i < v4.size(); i++){
        if(v4[i] != -2){
          pass = false; message = "failed with type t=<" + string{typeid(v4).name()} + ">"; 
          log_error_message(test_no, description, message); 
          break; 
        }
      }
      for(size_t i = 0; i < p2.size(); i++){
        if(p2[i].x != 12 && p2[i].y != 12){
          pass = false; message = "failed with type T=<" + string{typeid(p2).name()} + ">"; 
          log_error_message(test_no, description, message); 
          break; 
        }
      }
      break; 
    }
    case Test_Cases::MOVE_ASSIGNMENT: {
      for(size_t i = 0; i < v4.size(); i++){
        if(v4[i]!=-2){
          pass = false; message = "failed with type T=<" + string{typeid(v4).name()} + ">"; 
          log_error_message(test_no, description, message); 
          break; 
        }
      }
    }
  }
  if(pass){
    cout << "TEST# " << test_no << " " << description << " All Test passed!" << endl; 
  }
}
void use_tests(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  test(1, "CONSTRUCT_N_DEFAULT_ELEMENTS", "", Test_Cases::CONSTRUCT_N_DEFAULT_ELEMENTS); 
  test(2, "SIZE", "", Test_Cases::SIZE); 
  test(3, "CAPACITY", "", Test_Cases::CAPACITY); 
  test(4, "MOVE_CONSTRUCTOR", "", Test_Cases::MOVE_CONSTRUCTOR); 
  test(5, "COPY_CONSTRUCTOR", "", Test_Cases::COPY_CONSTRUCTOR); 
  test(6, "COPY_ASSIGNMENT", "", Test_Cases::COPY_ASSIGNMENT); 
  test(7, "MOVE_ASSIGNMENT", "", Test_Cases::MOVE_ASSIGNMENT);
}
int main(){ 
  use_tests(); 
  return 0; 
}
