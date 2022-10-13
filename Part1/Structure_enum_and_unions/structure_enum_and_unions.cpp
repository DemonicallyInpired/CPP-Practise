#include<iostream>
#include<math.h>
#include<cstring>
#include<memory>
#include<cstring>
using namespace std; 
struct Address{
  const char* name; 
  const char* town; 
  char states[2]; 
  int zip[4];
  Address(const char* name1, const char* town1, char* states1, const char* zip1): name{name1}, town{town1}{
    switch(strlen(states1)){
      case 0: case 1: 
        throw std::runtime_error{"cant have state abbreviation less than two character"}; 
      case 2: 
        states[0] = states1[0]; 
        states[1] = states1[1]; 
      break; 
      default: 
        throw std::runtime_error{"invalid length for states"}; 
    }
    switch(strlen(zip1)){
      case 0: case 1: case 2: 
        throw std::runtime_error{"invalid length for zip"}; 
      case 3:
        zip[0] = 0; 
        zip[1] = zip1[0] - '0'; 
        zip[2] = zip1[1] - '0'; 
        zip[3] = zip1[2] - '0'; 
      break; 
      case 4: 
        zip[0] = zip1[0] - '0'; 
        zip[1] = zip1[1] - '0'; 
        zip[2] = zip1[2] - '0'; 
        zip[3] = zip1[3] - '0'; 
        break; 
      default: 
        throw std::runtime_error{"invalid length"}; 
    }
  }
}; 
void AccessStruct_by_value(Address a1){
 cout << a1.name << " " << a1.town << " " << a1.states << " " << a1.zip[0] << a1.zip[1] << a1.zip[2] << a1.zip[3] << endl;
}
void AccessStruct_by_reference(Address& a1){
  cout << a1.name << " " << a1.town << " " << a1.states << " " << a1.zip[0] << a1.zip[1] << a1.zip[2] << a1.zip[3] << endl; 
}
void AccessStruct_by_rval_refernce(Address&& a1){
cout << a1.name << " " << a1.town << " " << a1.states << " " << a1.zip[0] << a1.zip[1] << a1.zip[2] << a1.zip[3] << endl; 
}
void AccessStruct_by_pointers(Address* a1){
  cout << a1->name << " " << a1->town << " " << a1->states << " " << a1->zip[0] << a1->zip[2] << a1->zip[3] << endl; 
  cout << (*a1).name << " " << (*a1).town << " " << (*a1).states << " " << (*a1).zip[0] << (*a1).zip[1] << (*a1).zip[2] << (*a1).zip[3] << endl; 
}
char states[]{"PZ"}; 
Address prev_address = Address{"something", "something_else", states, "1234"}; 
Address next_address(Address& currentAddress){
  Address next = currentAddress; 
  prev_address = next;
  return currentAddress; 
}
void use_addresses(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  char states[]{"NZ"}; 
  Address a1 = Address{"something", "something_else", states, "1234"}; 
  AccessStruct_by_value(a1); 
  AccessStruct_by_pointers(&a1); 
  AccessStruct_by_reference(a1); 
  AccessStruct_by_rval_refernce(Address{"something", "something_else", states, "123"}); 
  Address next_Address = next_address(a1); 
  AccessStruct_by_reference(next_Address); 
}
#ifdef incompleteDeclration
struct Tree{
  Tree* leftNode; 
  Tree* rightNode; 
}; 
#endif
//void use_trees(Tree* root);
struct Tree{
  Tree* leftNode; 
  Tree* rightNode; 
  int data;
  Tree(Tree* left, Tree* right, int data1): leftNode{left}, rightNode{right}, data{data1}{}; 
  ~Tree(){
    delete leftNode; 
    delete rightNode; 
  } 
};
void insertNode(Tree** root, int data, string direction){
  Tree* currNode = *root; 
  if(currNode == nullptr){
    Tree* newNode = new Tree{nullptr, nullptr, data}; 
    currNode = newNode; 
  }
  else if(direction == "left" && currNode != nullptr){
    while(currNode->leftNode){
      currNode = currNode->leftNode; 
    }
    Tree* newNode = new Tree{nullptr, nullptr, data}; 
    currNode->leftNode = newNode; 
  }
  else if(direction == "right" && currNode != nullptr){
    while(currNode->rightNode){
      currNode = currNode->rightNode; 
    }
    Tree* newNode = new Tree{nullptr, nullptr, data}; 
    currNode->rightNode = newNode; 
  }else{
    throw std::runtime_error{"invalid direction:: "}; 
  }
}
void Traversal_Tree(Tree** root, string direction){
  Tree* currNode = *root; 
  if(direction == "left"){
   while(currNode){
      cout << currNode->leftNode << " " << currNode->rightNode << " " << currNode->data << endl; 
      currNode = currNode->leftNode; 
    }  
  }
  else if(direction == "right"){
    while(currNode){
      cout << currNode->leftNode << " " << currNode->rightNode << " " << currNode->data << endl; 
      currNode = currNode->rightNode; 
    }
  }
  else{
    throw std::runtime_error{"cant have this direction:: "}; 
  }
}
void use_tree(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int level;
  Tree* root = new Tree{nullptr, nullptr, 123}; 
  cout << "Enter the no of levels" << endl;
  cin >> level; 
  for(int i = 0; i < level; i++){
    int data; string direction; 
    cout << "Enter the data and direction resp." << endl;
    cin >> data >> direction; 
    insertNode(&root, data, direction); 
  }
  Traversal_Tree(&root, "left"); 
}
struct somestruct{
  int data; //4
  char something; //4 + 1 + 3 = 8 
  int something_else; //8 + 4
  char something_there; //12 + 1 + 3 = 16
}; 
struct Arranged{
  char something; //1
  char something_else;//2 + 2 = 4 
  int data; //8
  int something_there; //12
};
float calc_percentage(float xelem, float yelem){
  return ((xelem / (yelem + xelem)) * 100); 
}

void compare_mem(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  float mem1{}; 
  float mem2{}; 
  for(size_t i = 0; i < 100000; i++){
    mem1 += sizeof(somestruct); 
    mem2 += sizeof(Arranged); 
  }
  cout << "Memory wastage by:: " << to_string((int)calc_percentage(mem1, mem2) - (int)calc_percentage(mem2, mem1)) << "%" << endl;
}
struct Point{
  int x, y;
  friend ostream& operator <<(ostream& os, Point p1){
    os << "{" << p1.x << "," << p1.y << "}" << endl; 
    return os; 
  }
}; 

struct Array_of_Ponits{
  Point p1[3]; 
  friend ostream& operator <<(ostream& os, Array_of_Ponits& a1){
    for(size_t i = 0; i < 3; i++){
      os << '{' << a1.p1[i].x << "," << a1.p1[i].y << endl; 
    }
    return os; 
  }
}; 
void use_Array_of_structs(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  Array_of_Ponits p1{Point{1, 2}, Point{2, 2}, Point{3, 3}}; 
  for(size_t i = 0; i < 3; i++){
    cout << p1.p1[i].x << " " << p1.p1[i].y << endl; 
  }
  cout << p1; 
}
template<class T, size_t N>
struct Arrays{
  T* arr;  
  Arrays(T* arr1): arr{arr1}{}; 
  size_t sizes() const {return N;}
  T operator[](const int index){
    if(index >= 0 && index < N){
      return arr[index]; 
    }
    throw std::out_of_range{"array index out of range"}; 
  }
  friend ostream& operator <<(ostream& os, Arrays<T, N>& p){
    for(size_t i = 0; i < p.sizes(); i++){
      os << p.arr[i]; 
    }
    return os; 
  }
};
void use_some_array(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int arr[3]{1, 2, 3};
  Point arrrandompoints[3]{Point{1, 2}, Point{3, 3}, Point{2, 2}}; 
  Arrays<int, 3>arr1{arr};  
  Arrays<int, 3>arr2 = arr1; 
  for(size_t i = 0; i < arr1.sizes(); i++){cout << arr1[i] << endl;}
  Arrays<Point, 3> arrrandom{arrrandompoints};
  cout << arrrandom; 
}
struct somestruct1{
  int x, y; 
}; 
struct somestruct2{
  int x, y; 
}; 
void Two_structs_are_different_types(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  somestruct1 s1; 
  #ifdef mad
  somestruct2 s2 = s1; 
  #endif
  #ifdef moremad
  int randomval = s; 
  #endif
}
template<class T>
void my_copy(T* to, T* from, int count){
  if(std::is_pod<T>::value){
    cout << "copied with POD:: " << endl; 
    std::memcpy(to, from, count * sizeof(T)); 
  }else{
    cout << "copied with NonPOD(s)" << endl; 
    for(size_t i = 0; i < count; i++){
      to[i] = from[i]; 
    }
  }
  for(size_t i = 0; i < count; i++){
    cout << to[i] << " "; 
  }
  cout << endl; 
}
class PODS{
private: 
  int _mx, _my; 
public: 
  PODS(int x1, int y1): _mx{x1}, _my{y1}{}; 
  PODS() = default;
  friend ostream& operator<<(ostream& os, PODS& p1){
    os << p1._mx << " " << p1._my << endl; 
    return os; 
  }
}; 
class NotPODs{
private: 
  int _mx; int _my; 
public: 
  NotPODs(int x1 = {}, int y1 = {}): _mx{x1} ,_my{y1}{}; 
  friend ostream& operator<<(ostream& os, NotPODs& n1){
    os << n1._mx << " " << n1._my << endl; 
    return os; 
  }
}; 
void use_my_copy(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  PODS p1[3]{PODS{1, 2}, PODS{2, 2}, PODS{3, 3}}; 
  PODS p3[3]{}; 
  NotPODs p2[3]{NotPODs{2, 2}, NotPODs{2, 2}, NotPODs{2, 2}};
  NotPODs p4[3]{}; 
  my_copy<PODS>(p3, p1, 3);
  my_copy<NotPODs>(p4, p2, 3); 
}
enum class Type{STR, NUMS}; 
struct Emp{
  int number; 
  string name; 
  Type t1; 
}; 
void use_emp_wastage(Emp e1){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  //clearly teh name and the number are never used simmultaneously in the given context and hence the space is wasted. 
  if(e1.t1 == Type::STR){cout << e1.name << endl;}
  else{cout << e1.number << endl; }
  cout << sizeof(Emp) << endl; 
}
//union can be thought of as a user-defined type, much like struct where each of the members are allocated at the memory address conequenlty, we can access only a member at a time. Therefore, it pragmatically depends on the program to ensure what is being written through is exactly what is being read while exploiting a union cause defying the same could lead to undefined behavior cause different types of objects may be allocated at different word-bit boundary, hence accessing an object with an otherwise, unspecified word-bit boundary can lead to undefined behaviors. 
union someEmp{
  const char* name; 
  int no = 13; //OK can have atmost one in class intializer; 
  #ifdef someerror
  string somename; //error user-defined sematic are deleted for union types. 
  #endif
  //OK can have static member function
  static int somefunction(){
    return 2; 
  }
  #ifdef anotherError
  int nostatic(){return -12;}
  #endif
  #ifdef cant_have_virtual_member_function
  virtual void somefunction(){cout << name << " " << no << endl;}
  #endif
}; 
struct Emp1{
  someEmp e1; 
  Type t1; 
}; 
void use_emp_without_Wastage(Emp1 e1){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  if(e1.t1 == Type::NUMS){
    cout << e1.e1.no << endl; 
  }else{
    cout << e1.e1.name << endl; 
  }
  cout << sizeof(Emp1) << endl; 
  //The size of the union is the size of it largest data member, consequently for the most of the cases where one often avoid using such data members of unions, some space is still wasted to represents such object. 
  cout << (sizeof(someEmp) == std::max(sizeof(int), sizeof(const char*)) ? "True" : "False") << endl; 

}
void use_emps(){
  Emp e1{123, "something", Type::NUMS}; 
  someEmp e2{"something"}; 
  Emp1 e3{e2, Type::STR}; 
  cout << e2.no << endl; //undefined ensure what is being read through is actually what is being written through. 
  someEmp erandom{"something_else"}; 
  #ifdef cant_have_move_and_copy_semantics
  erandom = e3; 
  #endif
  use_emp_wastage(e1); 
  use_emp_without_Wastage(e3); 
}
class Discriminated_unioins{
private: 
  Type t1; 
  union{
    int no; 
    string name; 
  }; 
public: 
  int get_nums()const; 
  string get_string()const; 
  void set_no(int n1);
  void set_string(const string& s1);
  Discriminated_unioins& operator=(const Discriminated_unioins& d1); //copy operator
  Discriminated_unioins(const Discriminated_unioins& d1); 
  Discriminated_unioins(Type t2, int n1): t1{t2}, no{n1}{}; 
  Discriminated_unioins(Type t2, string s1): t1{t2}, name{s1}{}; 
  ~Discriminated_unioins(){
    if(t1 == Type::STR){
      name.~basic_string(); 
    }
  }; 
};  
struct Bad_entry{
  const char* message; 
  virtual void what(){
    cerr << message << endl; 
  }
  Bad_entry(const string& message1): message{message1.c_str()}{}; 
}; 
int Discriminated_unioins::get_nums()const{
  if(t1 != Type::NUMS){
    throw Bad_entry{"cant assign string to nums"}; 
  }
  return no; 
}
string Discriminated_unioins::get_string()const{
  if(t1 == Type::STR){
    return name; 
  }
  throw Bad_entry{"cant assign int to string"}; 
}
void Discriminated_unioins::set_no(int n1){
  if(t1 == Type::STR){
    name.~basic_string(); 
    t1 = Type::NUMS; 
  }
  no = n1; 
}
void Discriminated_unioins::set_string(const string& s1){
  if(t1 == Type::STR){
    name = s1; 
  }else{
    new(&name)string{s1}; 
    t1 = Type::STR; 
  }
}
Discriminated_unioins& Discriminated_unioins::operator=(const Discriminated_unioins& d1){
  if(t1 == Type::STR && d1.t1 == Type::STR){
    name = d1.name; 
    return *this; 
  }
  if(t1 == Type::STR){name.~basic_string();}
  switch(d1.t1){
    case Type::NUMS: {
      no = d1.no; 
      break; 
    }
    case Type::STR: {
      new(&name)string{d1.name}; 
      t1 = Type::STR; 
      break; 
    }
  }
  return *this; 
}
Discriminated_unioins::Discriminated_unioins(const Discriminated_unioins& d1){
  if(t1 == Type::STR && d1.t1 == Type::STR){
    name = d1.name; 
  }
  if(t1 == Type::STR){
    name.~basic_string(); 
  }
  switch(d1.t1){
    case Type::NUMS: 
      {
        no = d1.no;
        t1 = Type::NUMS; 
        break; 
      }
    case Type::STR: 
      {
        new(&name)string{d1.name}; 
        t1 = Type::STR; 
        break; 
      }
  }
}
void use_discriminated_unions(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  
  Discriminated_unioins d1{Type::NUMS, 12}; 
  Discriminated_unioins d2 = d1; 
  cout << d1.get_nums() << endl;
//  cout << d1.get_string() << endl; 
  cout << d2.get_nums() << endl; 
  //cout << d2.get_string() << endl; 
  d1.set_no(13); 
  cout << d1.get_nums() << endl; 
  d1.set_string("something"); 
  cout << d1.get_string() << endl;  
}
enum class Symbolic_constants{
  RED, 
  GREEN = 5, 
  BLUE, 
}; 
enum class explict_cosntant: char{
  RED = 'r', 
  GREEN = 'g', 
  BLUE = 'b'
}; 
enum Symbolic_constants1{
  RED, GREEN, BLUE
}; 
void Enumerators(Symbolic_constants c1){
  #ifdef erros
  Symbolic_constants c1 = 12; 
  Symbolic_constants c2 = 13; 
  RED = 123; //Tightly scopped i.e. acessible within the enumerator scope only and hence doesn't lead to any namespace pollution
  GREEN = 133; 
  #endif
  //Integral constant used to represents symbolic constant within a program as opposed to resorting to magic numbers: has range(-2^k to 2^k) for (-ve integer) and(0 to 2^k for positive integers) where k is the least no of bits required to represent largest enumerator; 
  Symbolic_constants c11 = Symbolic_constants::RED; 
  Symbolic_constants c2 = Symbolic_constants::GREEN; 
  Symbolic_constants c3 = Symbolic_constants::BLUE; 
  cout << static_cast<int>(c11) << " " << static_cast<int>(c2) << " " << static_cast<int>(c3) << endl; 
  Symbolic_constants c4 = static_cast<Symbolic_constants>(12); //OK Explicit-caste; 
  cout << static_cast<int>(c4) << endl; 
  int r = static_cast<int>(c4); //OK Explicit cast allowed; 
  cout << r << endl; 
  switch(c1){
    case Symbolic_constants::RED: 
      cout << static_cast<int>(Symbolic_constants::RED) << endl; 
      break; 
    case Symbolic_constants::GREEN: 
      cout << static_cast<int>(Symbolic_constants::GREEN) << endl; 
      break; 
    default: //avoid using default with enums to account for all enumerator as specified in the declrations. 
      cout << "dont match" << endl; 
  }
  cout << RED << endl; //OK available within the enclosing scope; Thereby can lead to namespace pollution; 
  #ifdef namespace_pollution
  int RED = 143; 
  #endif
  int random = RED; //OK can implicitly converts to integral type; 
  cout << random << endl; 
  int pp = static_cast<Symbolic_constants1>(133); 
  cout << pp << endl; //range decided in the same fashion as mention above. 
  //since the enum class doesn't implicitly converts to integral type much like the plain enums, we can't really perform any sort of bitwise operator on such types without explicit conversion to the required integral types. 
  #ifdef errror_With_bitwise
  cout << (c11 & c2) << endl; 
  #endif
  cout << (static_cast<int>(c11) & static_cast<int>(c2)) << endl; 
}
void use_Enumerators(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  Symbolic_constants c1{Symbolic_constants::RED}; 
  Enumerators(c1); 
}
int main(){
  use_addresses();
  use_tree();
  compare_mem();
  use_some_array();   
  Two_structs_are_different_types();
  use_my_copy();
  use_emps(); 
  use_discriminated_unions(); 
  use_Enumerators(); 
  return 0; 
}
