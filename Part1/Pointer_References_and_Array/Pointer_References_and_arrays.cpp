#include<iostream>
#include<cstring>
#include<map>
#include<vector>
using namespace std;
using PTOF = void(*)(); 
template<class T>
void pointers(){
  T something = T{}; 
  T* pointer_to_something = &something; 
  cout << *pointer_to_something << endl;
  T something_else; 
  pointer_to_something = &something_else; 
  cout << *pointer_to_something << " " << pointer_to_something << endl; 
  int randomarray[2]{1, 2}; 
  int (*pointerto_array)[2]{&randomarray}; 
  cout << **pointerto_array << endl; 
}
void use_pointer_to_functions(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  PTOF p1 = &pointers<int>;  
  p1(); 
}
void use_pointers(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  pointers<int>(); 
  use_pointer_to_functions(); 
}
void* voidstars(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int something = 12;
  void* ptr = &something; 
  void* r = reinterpret_cast<void*>(0XFFFF); 
  r = ptr; 
  cout << (r == ptr) << endl; 
  cout << *reinterpret_cast<int*>(r) << " " << r << endl; 
  cout << *reinterpret_cast<double*>(r) << endl; //undefined behavior type casting into pointer to unrelated type that isn't the type of the intended object being pointed  to. 
  return r; 
}
template<class T>
void* allocate(size_t sizes, T value = T{}){
  void* ptr = malloc(sizeof(T)* sizes); 
  T* someptr = reinterpret_cast<T*>(ptr); 
  *someptr = value; 
  return someptr;   
}
void use_allocate(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int somevalue =12; 
  int* something = reinterpret_cast<int*>(allocate<int>(4, somevalue));  
  cout << *something << endl; 
  //Pointer to a function or Pointer to a member cant be assigned with a void* 
}
template<class T>
void nullptrs(){
  T* ptr = nullptr;
  T* ptr1{}; 
  cout << (ptr == ptr1) << endl; 
  const char* something = nullptr; 
  cout << (ptr == something) << endl; 
  cout << (*ptr) << endl; //error derferencing a nullptr; 
  T* something_else_ptr = 0; //could be confused with the overloaded istance of function where a function is overloaded to accept either an integer or pointer. 
  T* something_else_ptr1 = NULL; //Might have different interpretation across differnt languages for instance in C it is often treated as 0L, while in CPP it is often treated as void*(0) which makes it illegal in CPP. 
  T* sometihng_else_ptr2 = nullptr; //OK doesnt have any tendencies to be unsafe as the ohter alternatives. 
}
template<class T>
void Arrays(const int sizes){
  //Fixed length sequence of object of similar type in memory, meaning the size of an array should be const bound, if you want a variable length sequence use std::array, valarray or vector
  T arr[sizes]{}; 
  cout << (arr == &arr[0]) << endl; //array name converts to teh pointer to the fist element in slightest provocation therfore we cant really pass arrays by value in interface such as function's arguments. 
  for(size_t i = 0; i < sizes; i++){
    cout << arr[i] << " "; 
    cout << (arr + i) << " " << *(arr + i) << endl; 
  }
  T arr1[sizes]{};
 // arr = arr1; //error array doesn't provide any copy or move constructor for any given types. Meaning we cant have array assignment even if the array happens to have same no of elements of the same type. 
}
size_t getlength(const char* somestring){
  int count{}; 
  for(const char* start = somestring; *start != '\0'; start += 1){
    count += 1; 
  }
  return count; 
}
void printlength(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  cout << getlength("") << endl; 
  cout << strlen("") << endl; 
  cout << getlength("something") << endl; 
  cout << strlen("something") << endl; 
  cout << sizeof("") << endl; 
  cout << sizeof("something") << endl;   
}
const char* string_literals1(int i){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  //  char* somestring = "something"; //error but accepted pre C++11, owing to the fact that having string literal immutable is not only obvious but allows for significant optimzations in the way the string literals are used and accesed. 
  //cout << somestring << endl; 
  char modifiable_string_literals[]{"something"}; 
  modifiable_string_literals[2] = 'R'; 
  cout << modifiable_string_literals << endl;
  cout << getlength(modifiable_string_literals) << endl; 
  const char* name1 = "something"; 
  const char* name2 = "something"; 
  cout << name1 << " " << name2 << " " << (name1 == name2) << endl; //implementation-defined wheter the two same c-styled string literals are stroed at the same memory address or not. (== here compares the address, not the value pointed to)
  const char* concatenate = "abcdefghijklmnoq"
    "rstuvwxyz"; 
  cout << concatenate << endl; 
  char names[]{"James\000Bond"};
  #ifdef check_strcpy
  char* something_ptr = nullptr; 
  strcpy(something_ptr, names); 
  cout << something_ptr << endl; 
  #endif
  cout << names << " " << strlen(names) << endl; 
  if(i <= 12){
    return "range error"; //statically allocate can return from a funuction without losing its value. 
  }
  return "range error again"; 
}
void use_string_literals(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  const char* somenames = "something"; 
  string_literals1(12); 
}
void raw_string_literals(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  const char* raw_String = R"***("some string has been therfore
    random")***";
  const char* equivalen_string_literals = "something has been ther\n\t\trandom"; 
  cout << raw_String << endl; 
  cout << equivalen_string_literals << endl; 
  const char* plainstring_literals = "files\\folder"; 
  const char* plainraw_String_literals = R"("files\\folder")"; 
  const char* utf8_string_literals = u8"files\\folder"; 
  const char* raw_utf8_string_literals = u8R"***("files\\folder")***"; 
  const char16_t* utf_16_string_literals = u"files\\folder"; 
  const char16_t* raw_utf_16_string_literals = uR"***("files\\folder")***"; 
  const char32_t* utf32_string_literals = U"files\\folder"; 
  const char32_t* raw_utf32_string_literals = UR"***("files\\folder")***"; 
  cout << plainstring_literals << " " << plainraw_String_literals << endl; 
  cout << utf8_string_literals << " " << raw_utf8_string_literals << endl; 
  cout << utf_16_string_literals << " " << raw_utf_16_string_literals << endl; 
  cout << utf32_string_literals << " " << raw_utf32_string_literals << endl; 
}
template<class T>
int calc_bytes(T* ending, T* begining){
  return reinterpret_cast<char*>(ending) - reinterpret_cast<char*>(begining); 
}
void pointer_and_Array(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  //The name of the array coverts to the pointer to the first element on the slightest provocation. 
  //Therefore, we loose our tendecy to keep track of the size of the array without explicitly specifying the same. 
  //Thus, traversing the array within a well-specified range becomes the inherit responsibilty of the porgrammer. 
  //Secondly, since the name of the array converts to the pointer to the first element, this essentially means wen can't actually pass the copy of an array as an argument to function or std library function such as strlen, stcmp, etc, and each of them will recieve the pointer to the first elem of the array
  //Therefore, we need some mechanism to keep track of the size of the array, and should never pass array by value to esnure traversal within a well-specified range. 
  int v[]{1, 2, 3, 4}; 
  cout << ((v[0] == 0[v] && 0[v] == *(v + 0) && *(v + 0) == *(0 + v)) == 1 ? "True" : "False") << endl; 
  cout << v << " " << *v << " " << (v == &v[0]) << endl;
  map<int, int*>m1; 
  for(size_t i = 0; i < 4; i++){
    m1.insert({v[i], v+i}); 
  }
  for(auto it = m1.begin(); it != m1.end(); it++){
    cout << it->first << " " << it->second << endl;  
  }
  int* randomvalues = &v[5]; //Taking the address one past the bound of the array eleme is allowed and povital for some of the algorithns, however, taking an address beyond that and reading and writing through the same could have undefined behavior. 
  cout << randomvalues << endl;
  cout << calc_bytes ((++m1.begin())->second, m1.begin()->second); 
}
void Traversal1D(int arr[10]){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  for(size_t i = 0; i < 11; i++){
    cout << arr[i] << " "; //undefined behavior accessing array index out of the bound and passing array by value. 
  }
  cout << endl; 
}
void Traversal1D(int arr[], size_t N){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  for(size_t i = 0; i < N; i++){cout << arr[i] << " "; }
  cout << endl; 
}
void MoreSane1D(int* arr, size_t N){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  for(size_t i = 0; i < N; i++){cout << *(arr + i) << " "; }
  cout << endl; 
}
void TwoDTraversal(int arr[2][3]){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  for(size_t i = 0; i < 2; i++){
    for(size_t j = 0; j < 3; j++){
      cout << arr[i][j] << " "; 
    }
    cout << endl; 
  }
}
void MoreSaneTwoDTraversal(int arr[][3], int dim1){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  for(size_t i = 0; i < dim1; i++){
    for(size_t j = 0; j < 3; j++){
      cout << arr[i][j] << " "; 
    }
    cout << endl; 
  }
}
void MostSane2D(int* arr, int dim1, int dim2){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  for(size_t i = 0; i != dim1; i++){
    for(size_t j = 0; j != dim2; j++){
      cout << arr[i + j * dim1] << " "; 
    }
    cout << endl; 
  }
}
void use_arrays(){
  int arr[10]{1, 2, 3, 4}; 
  int arr1[2]{1, 2}; 
  int arr2[2][3]{{1, 2, 3}, {4, 5, 6}}; 
  Traversal1D(arr); 
  Traversal1D(arr1, 3); //still undefined traversal out of the bound. 
  MoreSane1D(arr, 10); 
  TwoDTraversal(arr2); 
  MoreSaneTwoDTraversal(arr2, 2); 
  MostSane2D(&arr2[0][0], 2, 3);  
}
void pointer_and_constants(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  int something = 12; 
  const int something_Else = 12; 
  const int* ptr = &something; //pointer to const int, OK can assign to unrestricted value. 
  const int* ptr1 = &something_Else; 
  cout << *ptr << " " << *ptr1 << endl; 
  //*ptr1 = 13; //error cant modify const int in the given scope. 
  int const* ptr2 = &something_Else; //same int const taken as the part of the base type. (read from right to left)
  int* const ptr3 = &something; //const pointer to the int makes the pointer constant but not the object pointed to, mean such pointer can't be assigned with other pointer. 
  //ptr3 = ptr2; //error cant assign const pointer to other pointer. 
  cout << *ptr2 << " " << *ptr3 << endl; 
  #ifdef erros
  int* const ptr4 = &something_Else; //error assign unrestricted pointer to a const value. 
  #endif
  const int* const ptr5 = &something_Else; //OK const pointer to const int. 
  cout << *ptr5 << endl; 
}
template<class T>
class Pointer_and_ownership{
private: 
  T* elem; 
  bool owns; 
public: 
  Pointer_and_ownership(T* elem1 = {}, bool owns1 = {}): elem{elem1}, owns{owns1}{}; 
  void close(){if(owns){delete elem;}}
  ~Pointer_and_ownership(){close();}
}; 
void use_pointers_and_ownership(){
  int i =0; 
  while(i >= 0){
   int* ptr = new int{12}; 
   Pointer_and_ownership p1{ptr, true}; 
   int* ptr1 = reinterpret_cast<int*>(0xFFFF); 
   Pointer_and_ownership p2{ptr1, false};
    i += 1; 
  }
}
void references(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  //other way of reffering to an object much like an addressing mechnanimsm while taking into the consideration that the reference themselves are not objects. 
  //A reference must always be linked to an object and always reffers to the same object throughout the lifetime
  //A refernce thus, in general sense could be considered as a pointer to a constant object as long as one remembers that they can't be manupulated the way the real objects can be. 
  //Since the reference themselves are not onject we cant have array or pointer to a reference and whatever operatiokn that is to be performed on a reference is eventually reflected okn the object being refernecdd. 
  //A refernce in the general sense of it can be either an lval value refernce or a rval reference. Where the lval reference reffers to an object that has identity in the memory and whose value we need to preserve, while an rval refernce reffers to the object whose valueu we dont really need to preserve and hence we can the expensive copy operation into a relatively cheap move operations using an rval refernce for such objects. 
  int something = 12; 
  int& lvalref = something; 
  cout << lvalref << endl; 
  lvalref += 1; 
  cout << something << endl; 
  int&& rval_Ref = 13; 
  rval_Ref += 1; 
  cout << rval_Ref << endl; 
  int* ptr =  &lvalref; 
  *ptr = 13; 
  cout << something << endl; 
}
void next1(int& someref){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  //avoid modifying the function arguments; Doing so is relatively, obscured and could be hard to get by.. 
  someref += 1; 
}
int next(int n){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int res = n + 1; 
  return res; 
}
void use_ref(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int something = 13; 
  next1(something); 
  cout << something << endl;
  int something_Else = next(something); 
  cout << something_Else << endl; 
}
struct somePerson{
  int a; //4
  float b;//4 + 4 = 8 
  char c; //8 + 1 = 9 + 3 = 12
  int d; //12 + 4 = char16_
}; 
//Pass lval refernce as a function if you know that you're gonna change such argument only. 
void use_somePerson(const somePerson& p1){
  cout << sizeof(p1) << endl; 
}
template<class T>
void swapping(T& a, T& b){
  T temp = static_cast<T&&>(a); 
  a = static_cast<T&&>(b); 
  b = a; 
}
template<class T>
void swapping1(T& a, T& b){
  T temp = std::move(a); 
  a = std::move(b); 
  b = temp; 
}
void use_swapping(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  vector<int>v1{1, 2, 3, 4, -12, 2, 0, 12}; 
  vector<int>v2{1, 2, -2, 2, -2, 2, -2, 2}; 
  swapping(v1, v2); 
  for(auto& i: v1){cout << v1[i] << " "; }
  cout << endl; 
  for(size_t i = 0; i < v2.size(); i++){
    cout << v2[i] << " "; 
  }
  cout << endl; 
}
//since an lavl refernce reffers to an object that has indeitiy and whose value we need to preserve, we can't actually bind an lval reference to an rval reference or vice versa
string use_lval_ref(string& fname, string& lname){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  string full_name = fname + " " + lname; 
  return full_name; 
}
string use_rval_ref(string&& fname, string&& lname){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  return lname + " " + fname; 
}
void cant_bind_lval_to_rval(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  string fname = "something"; 
  string lname = "something_Else"; 
  #ifdef wrong
  cout << use_rval_ref(fname, lname) << endl; 
  cout << use_lval_ref("soemthing", "something_else") << endl; 
  #endif
  cout << use_lval_ref(fname, lname) << endl; 
  cout << use_rval_ref("something", "something_else") << endl; 
}
//use refernce as a return type where the returned object is expensive to copy, and can be used on both left hand side and right hand side of an assignment such as result form a [] operator. 
//use const lval refernce where we cant change the object being reffered. 
template<class K, class V>
class Maps{
  vector<pair<K, V>>elem;
public: 
  pair<K, V>* begin() noexcept{return &elem[0]; }
  pair<K, V>* end() noexcept{return &elem[0] + elem.size();}
  V& operator[](const K& key){
    for(auto& i: elem){
      if(i.first == key){return i.second;}
    }
    elem.push_back({key, V{}}); 
    return elem.back().second; 
  }
  pair<K, V> operator[](int index) const{
    return elem[index]; 
  }
  friend ostream& operator <<(ostream& os, Maps<K, V>& m1){
    for(auto& i: m1){
      os << i.first << "," << i.second; 
    }
    return os; 
  }
  Maps(vector<std::pair<K, V>>& m1): elem{m1}{}; 
  Maps(vector<std::pair<K, V>>&& m1): elem{m1}{}; 
}; 
void use_maps(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  vector<pair<string, int>>m1{{"something", 1}, {"something_else", 2}}; 
  Maps<string, int>m2{m1}; 
  for(auto& i: m2){cout << i.first << " " << i.second;}
  cout << m2 << endl; 
}
template<class T>
void reference_to_refernce(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  //reffernce collapse(can only be acchieved via template aliases)
  using lvalref = T&; 
  using llvalref = lvalref&; 
  using lrvalref = llvalref&&; 
  using rvalref = T&&; 
  using rlvalref = rvalref&; 
  using rrvalref = rvalref&&; 
  using rrvalreflvalref = rrvalref&; 
  cout << typeid(llvalref).name() << endl; 
  cout << typeid(lrvalref).name() << endl; 
  cout << typeid(rlvalref).name() << endl; 
  cout << typeid(rrvalref).name() << endl;
  cout << typeid(rrvalreflvalref).name() << endl; 
}
void use_refernce_if_you_want_an_indentifier_being_bound_to_single_object_throught_its_lifetime(char& something){
  //foreever
  #ifdef foreever
  while(something != 0){something += 1;}
  #endif
}
void use_pointer_if_you_want_it_to_bind_to_different_objects_throughtout_the_lifetime(char* something){
  while(*something++); 
}
class Points{
  int x, y; 
public: 
  Points(int x1, int y1): x{x1}, y{y1}{};
  Points operator+(Points& p1){
    Points res{x + p1.x, y + p1.y}; 
    return res; 
  }
  Points operator-(Points* p1){
    Points res{x - p1->x, y - p1->y}; 
    return res; 
  }
  friend ostream& operator <<(ostream& os, const Points& p1){
    os << p1.x << "," << p1.y; 
    return os; 
  }
}; 
void use_reference_if_you_need_to_overload_a_operation_on_user_defined_type(){
  Points p1{12, 13}; 
  Points p2{13, 13}; 
  Points p4 = p1-&p2; 
  Points p5 = p1 + p2; 
  cout << p4 << endl; 
  cout << p5 << endl; 
}
void use_pointer_vs_ref(){
  cout << __FUNCTION__ << " " << __LINE__; 
  char sequence[] = "something"; 
  char something_else = 'R'; 
  //use_refernce_if_you_want_an_indentifier_being_bound_to_single_object_throught_its_lifetime(something_else); 
  use_pointer_if_you_want_it_to_bind_to_different_objects_throughtout_the_lifetime(sequence); 
  use_reference_if_you_need_to_overload_a_operation_on_user_defined_type(); 
}

int main(){
  use_pointers(); 
  voidstars();
  use_allocate(); 
  Arrays<int>(12); 
  printlength(); 
  use_string_literals();
  raw_string_literals();
  pointer_and_Array(); 
  use_arrays();
  pointer_and_constants(); 
  #ifdef delay
  use_pointers_and_ownership(); 
  #endif
  use_maps(); 
  reference_to_refernce<int>(); 
  use_pointer_vs_ref(); 
  return 0; 
}
