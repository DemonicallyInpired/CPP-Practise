#define level 1
#include<iostream>
#include<cstring>
#include<map>
#include<math.h>
#include<new>
#include<initializer_list>
#include<vector>
#include<algorithm>
#include<cassert>
#include<functional>
using namespace std; 
string reverse(string a){
  char* start = &a[0]; 
  char* end = &a[a.size()-1];
  while(start <= end){
    char temp = *start; 
    *start = *end; 
    *end = temp; 
    start += 1; 
    end -= 1; 
  }
  return a; 
}
string decTo_hex(int a){
  int k = 0; 
  while(pow(2, k) < a){
    k += 1; 
  }
  map<int, string>hexmapping{{10, "a"}, {11, "b"}, {12, "c"}, {13, "d"}, {14, "e"}, {15, "f"}}; 
  string res;
  while(a > 0){
    if(a < 0){
      throw std::runtime_error{"out of range"}; 
    }
    if(a <= 9){
      return to_string(a);  
    }else{
      while(a > 0){
        if(a%16 <= 9){res += to_string(a%16);}else{
          res += hexmapping[a%16];
        }
        a = (a - (a%16))/16;
      }
    }
  }
  while(res.size() < 32){
    res += to_string(0); 
  }
  return reverse(res); 
}
enum class Operations{AND, OR, NOT, XOR, AND_EQ, OR_EQ, XOR_EQ}; 
void Bitwise_operators(int digit1, int digit2, Operations ops){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  int a = 12; // 1100
  int b = 0xFFFF; //Implemenation-defined. 
  int res = (a >> 29) & b; //often used to treat storage as the bitarray or to extract bits from the words. 
  cout << res << endl; 
  #ifdef errors
    cout << (ops &= ops) << endl; //error enum class cant implicity converts to intgers
    cout << (static_cast<int>(ops) |= static_cast<int>(ops)) << endl; //OK explicit type conversions.   
  #endif
  switch(ops){
    case Operations::AND: 
      cout << (digit1 & digit2) << endl; 
      break;
    case Operations::OR:
      cout << (digit1  | digit2) << endl; 
      break; 
    case Operations::NOT: 
      cout << ~(digit1) << endl; 
      break; 
    case Operations::XOR: 
      cout << (digit1 ^ digit2) << endl; 
      break; 
    case Operations::AND_EQ: 
      cout << (digit1 &= digit2) << endl; 
      break; 
    case Operations::OR_EQ: 
      cout << (digit1 |= digit2) << endl; 
      break; 
    case Operations::XOR_EQ: 
      cout << (digit1 ^= digit2) << endl; 
      break; 
  }
}
void use_bitiwise_operators(int a, int b){
  map<string, Operations>ops{{"AND", Operations::AND}, {"OR", Operations::OR}, {"NOT", Operations::NOT}, {"XOR", Operations::XOR}, {"AND_EQ", Operations::AND_EQ}, {"OR_EQ", Operations::AND_EQ}, {"XOR_EQ", Operations::XOR_EQ}}; 
  for(auto& i: ops){
    cout << i.first << " "; 
    Bitwise_operators(a, b, i.second); 
  }
}
void logical_operators(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  bool a =true; 
  bool b{false}; 
  bool c = 12; 
  bool d{0}; 
  if(a && c){ //logical operators are often used to evaluated some sort of logical operations as the part of the logical expression meaning they are used to check logical predicate resulting in either of true or false. 
    cout << (a || b) << endl; 
  }
  int res = (a && b);//implicit conversion of bool to int in an arthematic expression. 
  cout << res << endl; 
}
void my_copy(char* to, const char* from){
  float start = clock(); 
  int len = 0; 
  while(len < strlen(from)){
    to[len] = from[len];
    len += 1; 
  }
  cout << to << " " << from << endl; 
  float end = clock(); 
  cout << (end - start)/100 << endl; 
}
void my_copy1(char* to, const char* from){
  float start = clock(); 
  while((*to++ = *from++) != '\0'); 
  cout << to << " " << from << endl; 
  float end = clock(); 
  cout << (end - start)/100 << endl; 
}
void my_copy2(char* to, const char* from){
  float start = clock(); 
  while(*to++ =  *from++); 
  cout << to << " " << from << endl; 
  float end = clock(); 
  cout << (end - start)/100 << endl; 
}
void increment_and_decrement_operators(){
  int a = 12; 
  a = a + 1; 
  cout << (a == 13 ? "True" : "False") << endl; 
  a += 1; 
  cout << (a == 14 ? "True" : "False") << endl; 
  int z = ++a; //use the old value equivalent to (z = (a = a + 1))
  cout << (z == 15 ? "True" : "False") << endl; 
  int z1 = a++; //use the old value meaning we can still assign the old value before using it. equivalent to (z1 = (t1 = a, a+1, t1)); 
  cout << (z1 == 15 ? "True" : "False") << endl; 
  cout << (a == 16 ? "True" : "False") << endl; 
  const char* somestring = "something"; 
  const int sizes = strlen(somestring); 
  char res[sizes]{}; 
  my_copy(res, somestring); 
  my_copy1(res, somestring); 
  my_copy2(res, somestring); 
}
void free_store(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int* ptr = new int; 
  cout << *ptr << endl; //doesn't default intialized. 
  //never use object allocated on the free-store within local scope owing to the fact that they can easily result in memory leak if any sort of an exception is to be thrown before the call to delete. or a function returns before the call to delete. 
  try{
    int x = 12; 
    if(x < 13){
      throw std::runtime_error{"Memory leaked"}; 
    }
  }catch(std::runtime_error& r1){
    cout << r1.what() << endl; 
    delete ptr; //destroy object allocated on the free store or dynamically allocated. 
  }
  int* arr = new int[2]{1, 2}; 
  //delete arr; //error no instance of the overloaded operator of delete with argument delete(size_t sz, int[]); 
  delete[]arr; //determines the size of the entire array to be deallocated. 
  delete ptr; 
}
void problems_with_freestore(){
  int* premature_deletion = new int{12}; 
  delete premature_deletion; 
  cout << *premature_deletion << endl; //might point to unrelated location that might be used by other objects, therefore could lead to corrupting the concerned object. 
  delete premature_deletion; //double deletion to unrelated location, can also lead to corruption of memory location. 
  int* leaked_object; //could result in dangling pointer and hence cuddling up the entire memory space for objects to be allocated on the free_store. 
}
void check_alloc(){
  float start = clock(); 
  for(;;){
    try{
      int* ptr = new int[200]; 
    }catch(std::bad_alloc& b1){
      cerr << b1.what() << endl; 
    }
  }
  float end = clock(); 
  cout << (end - start)/1000; 
}
void check_alloc1() noexcept{
  for(;;){
    int* arr = new(nothrow) int[200]; 
  }
}
class SomeClass{
private: 
  int x, y; 
public: 
  SomeClass() = default; 
  SomeClass(int x1, int y1): x{x1}, y{y1}{}; 
  void* operator new(size_t sz){
    cout << "called operator new" << endl; 
    void* allocate = malloc(sizeof(SomeClass) * sz); 
    return allocate; //untype and raw memory; 
  }
  void* operator new[](size_t sz){
    cout << "called operator new[]" << endl; 
    void* allocate = malloc(sizeof(SomeClass) * sz); 
    return allocate; 
  }
  void* operator new(size_t sz, nothrow_t&) noexcept{
    cout << "called operator new(nothrow_t&)" << endl; 
    void* alloc = nullptr; 
    try{
      alloc = malloc(sizeof(SomeClass) * sz);
    }catch(std::bad_alloc){
      return nullptr; 
    }
    return alloc; 
  }
  void operator delete(void* ptr){
    cout << "called delete" << endl; 
    if(ptr){
      free(ptr);
    }
  }
  void operator delete[](void* ptr){
    cout << "called delete[]" << endl; 
    if(ptr){ptr = nullptr;}
  }
  void* operator new(size_t sz, void* ptr){
    cout << "called with placement new" << endl; 
    void* q = malloc(sizeof(SomeClass) * sz); 
    ptr = q; 
    return ptr; 
  }
  void operator delete(void* ptr, void* ptr1){
    cout << "called placement delete" << endl; 
    if(ptr){
      free(ptr); 
    }
    ptr1 = nullptr; 
  }
}; 
void use_overload_new_operators(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  SomeClass* s1 = new SomeClass{1, 2}; 
  SomeClass* s2 = new SomeClass[2]{SomeClass{1, 2}, SomeClass{2, 2}}; 
  SomeClass* s3 = new(s1) SomeClass{1, 2};  
  delete s1; 
  delete[] s2; 
  delete s3; 
}
struct SomePerson{
  int a; 
  string b; 
}; 
template<class T>
T do_square(T x){
  return x * x; 
}
void list_intializers(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
//  vector<double>d1{1, 2, 3.2}; 
  //const double temp[] {double{1}, double{2}, 3.2}; 
  //const initializer_list<double> res(temp, sizeof(temp)/sizeof(double)); 
  std::initializer_list<int>r1{1, 2, 3}; 
  for(auto& i: r1){
    cout << i << endl; 
    #ifdef initializer_list_are_immutable
      i = 12;   
    #endif
  }
  SomePerson s1{1, "Something"}; //direct intialization. 
  SomePerson s2 = SomePerson{1, "Something"}; //qualified list intialization. 
  SomePerson* s3 = new SomePerson{1, "Something"}; //construct object of type somePerson on free store with qualified list based constructor. 
  delete s3; 
  //other use explicit conversions; 
  double res = do_square(double{2.2}); 
  cout << res << endl; 
}
template<class K, class V>
class SomeMap{
private: 
  map<K, V>m1; 
public: 
  SomeMap(map<K, V>m2): m1{m2}{};
  int count{}; 
  int operator[](const std::pair<K, V>index){
    for(auto& i: m1){
      count += 1; 
      if(i.first == index.first && i.second == index.second){
        return count; 
      }
    }
    throw std::runtime_error{"Index not FOund"}; 
  }
}; 
int high_value(std::initializer_list<int> values){
  int high = std::numeric_limits<int>::min(); 
  if(values.size() == 0){return high;}
  for(auto& i: values){
    if(i > high){
      high = i; 
    }
  }
  return high; 
}
void use_high(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  std::initializer_list<int>l1{-1, 2, 3, 4}; 
  cout << high_value(l1) << endl; 
}
void unqualified_list(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int v{12}; //direct intialization. 
  int v1 = {12}; //copy intialization. 
  vector<int>res{1, 2}; 
  map<int, string>m2{{1, "something"}, {2, "Something_else"}}; 
  SomeMap<int, string>something{m2}; 
  int resultant = something[{2, "Something_else"}]; 
  cout << resultant << endl; 
  #ifdef somerrors
  v1 += {13}; //can be used on the RHS of {}-intializer; 
  #endif  
  cout << v1 << endl; 
  #ifdef errors12
  {v} = 13; //cant use {}-intializer on the left hand side of an initializer. 
  #endif
  do_square(double{12}); //function arguments. 
}
#ifdef cant_deduce_type_of_unqualified_list_from_template_arguments
template<class T>
void funct(T something){
  cout << typeif(something).name() << endl; 
}
#endif
class Lambdas{
private: 
  int m;
public: 
  int operator()(int x){
    return(x%m == 0) ? (x = 0) : (x = 1); 
  }
  Lambdas(int m1): m{m1}{}; 
  Lambdas() = default; 
}; 
class Lambdas1{
private: 
  int x, y; 
public: 
  bool operator()(int x1, int y1){
    return(x1 > y1); 
  }
  Lambdas1(int x1, int y1): x{x1}, y{y1}{}; 
  Lambdas1() = default; 
}; 
void Lambdas_and_expressions(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  Lambdas1 l2; 
  vector<int>something{1, 2, 3, 4, 13, 15, 20, 14, 22};
  Lambdas l1{2};
  for_each(something.begin(), something.end(), l1);
  for(size_t i = 0; i < something.size(); i++){cout << something[i] << " "; }
  cout << endl; 
  sort(something.begin(), something.end(), l2); 
  for(size_t i = 0; i < something.size(); i++){cout << something[i] << " "; }
  cout << endl; 
}
template<class T>
void swapping(T& a, T& b){
  T temp = static_cast<T&&>(a); 
  a = static_cast<T&&>(b); 
  b = temp; 
}
bool greatefunction(int a, int b){
  return(a > b); 
}
void sorting(vector<int>::iterator begining, vector<int>::iterator ending, bool(*cmp)(int, int)){ 
  for(auto it = begining; it != ending; it++){
    for(auto it1 = begining + 1; it1 != ending; it1++){
      int res = cmp(*it, *it1); 
      if(res){swapping(*it, *it1);}
    }
  }
}
void Alternative_to_lambdas(){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  vector<int>something{1, 2, -3, 4}; 
  bool (*PTOF)(int, int) = &greatefunction;
  cout << "original:: " << 1 << " " << 2 << " " << -3 << 4 << endl; 
  sorting(something.begin(), something.end(), PTOF);
  for(auto& i: something){cout << i << " "; }
  //other alternative use function argument passsing or iterative approaches. 
  #ifdef errors
  auto somecmp = [&](int a, int b)->bool{return(a > b) ? true: somecmp(a + 1, b);} //cant use somecmp before deducing the types. 
  #endif
  #ifdef OK
  std::function<bool>(int, int)cmparator = [&](int a, int b){
    return(a > b) ? true: compartor(a + 1, b); 
  }
  #endif
}
void captures(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  bool sensitive{}; 
  #ifdef level
  sensitive = true; 
  #endif
  int a{1}, b{1}; 
  //capture everything by referecens: 
  auto res = [&]()->int{
    if(sensitive){
      a += b; 
    }
    return a; 
  };
  a = res();   
  cout << (a == 2 ? "True" : "False") << endl; 
  //caputer everything by value
  auto res1 = [=]()->int{
    if(sensitive){
      //a += b; //error assignment to read only variable a caputred by value, not reference and hence not allowed to be modified in the given scope of lambda;  
    }
    return a; 
  }; 
  a = res1(); 
  cout << (a == 2 ? "True" : "False") << endl; 
  //caputre some of the enclosing enviorment variable/identifier by value and rest by reference
  auto res2 = [&, a, b](int c)->int{
    if(sensitive){
      //a += b; 
    }
    return a; 
  }; 
  a = res2(3); 
  cout << (a == 2 ? "True" : "False") << endl; 
  //capture some of enclosing env. variable/indentifier by reference and rest by value
  auto res3 = [=, &a, &b]()->int{
    if(sensitive){
      a += b; 
    }
    return a; 
  }; 
  a = res3(); 
  cout << (a == 3 ? "True" : "False") << endl; 
}
class Lambdas_and_this{
private: 
  int x; 
public: 
  Lambdas_and_this() = default; 
  Lambdas_and_this(int x1): x{x1}{};
  void somefunction(){
    //auto res = [&this](int c)->bool{return(x < c);}; //warning avoid caputring this by reference. cause members are accessed by this pointer and hence in cases where lambda outlive its caller it may actuall leads to reffering to unreelated memory location as soon as the class itself goes out of the scope. 
    //cout << res(3) << endl; 
    auto res1 = [this](int d)->bool{return(x < d); }; //much safe.  
    cout << res1(14) << endl; 
  }
}; 
void lambda_and_this(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  Lambdas_and_this l1{13}; 
  l1.somefunction(); 
}
class Traditional_lambdas{
private: 
  int x; 
public: 
  bool operator()(int a, int b) const{
    //x += 2; //error cant modify caputred indentifier in the given scope. 
    return(a + b < x); 
  }
  Traditional_lambdas() = default; 
  Traditional_lambdas(int x1): x{x1}{}; 
}; 
void mutable_lambdas(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  Traditional_lambdas l1{12}; 
  cout << l1(12, 13) << endl; 
  float random = 12.3f; 
  auto res = [&](int c){
    //random += 2; //error cant modify captured random in the given scope.
    cout << (random == c ? "True" : "False") << endl; 
  }; 
  res(12.3); 
  auto mutable_lambda = [&](int c)mutable{
    random += 4; 
  }; 
  cout << (random == 16.3 ? "True" : "False") << endl; 
}
void randomcall(int a){
  cout << a << endl; 
}
void call_and_return(){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  int something = 21; 
  [&]{randomcall(something);}; //OK return type deduced to be int, can skip the argument list if no arguments are given. 
  auto z1 = [=](){return something;}; //return type is int; 
  #ifdef errors
  auto z2 = [&](){if(something < 12){return 1;}else{return 2.3;}}; //error body too compilicate to deduce return type. 
  #endif
  auto z3 = [something](int a)->bool{
    return(something < 31); 
  }; //OK Explicit deduction. 
}
template<class Source, class Target>
Target narrow_cast(Source v){
  auto res = static_cast<Target>(v); 
  if(res != v){throw std::runtime_error{"Narrow Cast failed"}; }
  return res; 
}
void use_narrow_cast(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  double d = narrow_cast<int, double>(12);
  cout << d << endl;
  #ifdef narrowing
  int r = narrow_cast<double, int>(12.3);  
  cout << r << endl; 
  #endif
  #ifdef errors
  int* r = narrow_cast<int, int*>(12); //error conversion between unrelated types, static_cast only allows conversion between related types. 
  #endif
  #ifdef errors
  char ch = narrow_cast<int, char>(65); //can throw potential narrowing. 
  #endif
  #ifdef errors
  int random = narrow_cast<char, int>('A'); //error conversion between unrelated types.  
  cout << random << endl;
  #endif
}
void construction_based_cast(){
  int a = double{12}; //OK doesnt lead to narrowing and loosing any information
  double d = int{12}; //narrowing; 
  int r = int{}; //Explicit intention for default construction for the object of given type, 
  cout << a << " " << d << " " << r << endl; 
}
struct Person{
  int a; 
  float b; 
  friend ostream& operator << (ostream& os, Person p1){
    os << p1.a << " " << p1.b << endl; 
    return os; 
  }
}; 
void named_cast_conversions(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  cout << "used for not so well-defined type casting ... Such as casting amongst unknow types, etc." << endl; 
  int a = 12; 
  cout << static_cast<bool>(a) << endl; //conversion between related types. 
  cout << static_cast<int>(a) << endl; 
  cout << static_cast<float>(a) << endl;
  Person* p1 = reinterpret_cast<Person*>(0xAFFF);
  vector<int>v1{1, 2, 3, 4};
  Person* p2 = dynamic_cast<Person*>(&(*p1)); 
  int *const ptr = &a; 
  int* ptr1 = const_cast<int*>(ptr); 
  cout << (ptr == ptr1) << endl;
  double a1 = (double)12; //more dangerous than any named cast owing to the fact that the type of conversion performed(relatively safe and portable between same types, non-portable amongst different types, and const_conversion amongst pointer to different type may not be explicit and is often hard to spot in large programs)
  double a2 = double(12); //function style conversion may be non-portable amongst different implemenation but is often equivalent to (T)e
  cout << typeid(a1).name() << " " << typeid(a2).name() << endl; 
}
int main(){
  use_bitiwise_operators(12, 13); 
  logical_operators(); 
  increment_and_decrement_operators(); 
  use_overload_new_operators(); 
  list_intializers(); 
  list_intializers(); 
  unqualified_list();
  use_high();
  Lambdas_and_expressions();
  Alternative_to_lambdas(); 
  captures(); 
  lambda_and_this(); 
  mutable_lambdas(); 
  call_and_return(); 
  use_narrow_cast(); 
  construction_based_cast(); 
  named_cast_conversions(); 
  //funct(std::initializer_list<int>{1, 2, 3, 4}); 
  //funct(vector<int>{1, 2, 3}); 
  return 0; 
}
