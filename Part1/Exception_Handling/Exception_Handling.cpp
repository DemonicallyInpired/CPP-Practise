#include<iostream>
#include<vector>
#include<limits>
#include<cstring>
#include<sstream>
#define CURRENT_MODE Assert::Mode::_throw
#define CURRENT_LEVEL 12 
#include<exception>
using namespace std; 
using terminate_handler = void(*)(); 
class Out_of_Range{
private: 
  int start, end; 
public: 
  Out_of_Range(int start1 = {}, int end1 = {}) try: start{start1}, end{end1}{
    if(start >= end){
      throw std::runtime_error{"start <= end"}; 
    }
  } catch(std::runtime_error& r1){
    throw r1; 
  };
  virtual const char* what(){
    return "start <= end";  
  }
  ~Out_of_Range(){}
};
void taskmaster(vector<int>errorcodes, int errono){
  for(vector<int>::iterator it1 = errorcodes.begin(); it1 != errorcodes.end(); it1++){
    if(*it1 == errono){
      throw Out_of_Range{13, 12}; 
    }
  }
}
void use_Error_handling(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  Out_of_Range r1{12, 13}; 
  try{
    Out_of_Range r2{13, 12}; 
  }catch(std::runtime_error& r2){
    cerr << r2.what() << endl; 
  }
  catch(...){cerr << "Done with Error Handling ... " << endl; }
  vector<int>v1{-1, 2, 13, 12, 15, 102}; 
  try{
    taskmaster(v1, 102);
  }catch(Out_of_Range& r1){
    cerr << r1.what() << endl; 
  }catch(...){
    cerr << "out of range error" << endl; 
  }
}
#ifdef someerrors
void Traditional_Exception_Handling_Terminate_the_Program(int start, int end, string message){
  if(start <= end){
    //unconditionally termiate the program. 
    std::abort(); 
  }else{
    //System call to terminate the program. 
    exit(1); 
  }
}
#endif
int error_state{};  
int return_error_values(int a, int b){
  if(a >= b){return error_state = std::numeric_limits<int>::max();}
  return 0; 
}
std::pair<int, string> return_error_State1(int a, int b){
  std::pair<int, string>error_state{}; 
  if(a >= b){
    error_state.first = 123; 
    error_state.second = "range error"; 
  }
  return error_state; 
}
string call_error_handler_functions(int start, int end, string message){
  if(end <= start){return message;}
  return string{};
}
void use_traditional_Error_handling(){
  cout << __FUNCTION__ << " " << __LINE__ << endl;  
  //Traditional_Exception_Handling_Terminate_the_Program(12, 13, "Range errors(start <= end)"); 
  return_error_values(13, 12);
  if(error_state){
    cerr << "Error Encountered... " << endl; 
  }
  pair<int, string>res = return_error_State1(13, 12); 
  if(res.first){cerr << res.second << endl; }
}
struct Tree{
  Tree* leftNode; 
  Tree* rightNode; 
  int data; 
}; 
Tree* findNode(Tree* root, int data){
  Tree* currNode = root;
  if(!(root)){
    return nullptr; 
  }
  if(currNode->data == data){
    throw currNode; 
  }
  if(currNode->leftNode){
    findNode(currNode->leftNode, data); 
    if(currNode->rightNode){
      findNode(currNode->rightNode, data); 
    }
  }else{
    findNode(currNode->rightNode, data); 
    if(currNode->leftNode){findNode(currNode->leftNode, data); }
  }
}
void use_alternative_view_of_exceptions(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  Tree* root = new Tree{nullptr, nullptr, 123};
  root->leftNode = new Tree{nullptr, nullptr, 111}; 
  root->leftNode->rightNode = new Tree{nullptr, nullptr, 100}; 
  try{
    findNode(root, 111); 
  }catch(Tree* q){
    cout << q->leftNode << " " << q->rightNode << " " << q->data << endl; 
  }
}
class MimicingRaii{
  private: 
    int x, y; 
    string res; 
public: 
  MimicingRaii(int x1, int y1, string s1 = {}): x{x1}, y{y1}, res{s1}{}; 
  MimicingRaii() = default;
  bool invalid(){
    return(x >= y || res.size() > 1); 
  }
  friend ostream& operator <<(ostream& os, MimicingRaii& m1){
    os << "{" << m1.x << "," << m1.y << "}" << endl; 
    return os; 
  }
  ~MimicingRaii(){cout << "called destructor " << endl; }
};
void use_when_cant_use_exceptions(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  MimicingRaii m1{13, 12}; 
  if(m1.invalid()){
    m1.~MimicingRaii(); 
  }else{
    cout << m1 << endl; 
  }
}
bool h(int code){
  return code ? true: false; 
}
int string_size(string somestring){
  return somestring.size();  
}
bool Exceptions_and_Efficiency(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  char* somestring = new char[20]{"something"}; 
  if(h(1)){
    if(string_size(somestring)){
      free(somestring); 
      return(true); 
    }else{
      free(somestring); 
      return(false); 
    }
  }else{
    free(somestring); 
    return(false); 
  }
}
void somefunction(int somecode) noexcept{
  int intmaxing = std::numeric_limits<int>::max(); 
  int count{100}; 
  for(;;){
    count += 1; 
    if(count > 1e+3){break;}
    if(intmaxing < somecode){
      intmaxing = rand(); 
    }
  }
  cout << intmaxing << endl; 
}
void Exception_Garuntees(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  //Basic Exception Safe Garuntees; (Ensures that for all of the standard operations, invariants are maintained and no resources are leadked)
  //Ensure for basic operation for std::library such as assignment after destruction of an object, etc. 
  try{
    int* ptr = new int{12}; 
    delete ptr; //realising the resource before throwing any exception
    throw std::runtime_error{"something went wrong"}; 
  }catch(std::runtime_error& r1){
    cerr << r1.what(); 
  }
  //strong garuntee(In addition to the basic garuntee, all operation are meant to be implemented so as to leave the program in a valid state if an exception is being thrown or to have no effect on the state of the program at all.)
  //ensured for basic operations on container types such insert, push_back, pop, etc. 
  int count{}; 
  for(;;){
    count += 1; 
    if(count >= 1e+3){break;}
    try{
      int* ptr = new int[1024]{};
    }catch(std::bad_alloc& b1){
      cerr << b1.what() << endl; 
    }
  }
  //No throw garuntee for some operation such as swapping of cotainer types, in addition to basic garuntees ensure that hte operation is not intended to throw. 
  somefunction(123); 
}
class File_ptr{
private:
  FILE* fp; 
public: 
  File_ptr(const char* name, const char* mode): fp{fopen(name, mode)}{
    if(fp == nullptr){throw std::runtime_error{"cant open the file line:: " + to_string(__LINE__)}; }
  }; 
  File_ptr(string name, string mode): fp{fopen(name.c_str(), mode.c_str())}{}; 
  explicit File_ptr(FILE* fp1): fp{fp1}{
    if(fp == nullptr){throw std::runtime_error{"file ptr error"};}
  }
  operator FILE*(){return fp;}
  ~File_ptr(){fclose(fp);}
  void read_files(){
    char buffer[2000]{};  
    if(fp){
      fread(buffer, sizeof(buffer), 1, fp);
      cout << buffer << endl; 
    }else{
      throw std::runtime_error{"cant open file"}; 
    }
  }
};
void Exception_and_Resource_Mangement(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  File_ptr fp1{"Exception_Handling.cpp", "r"};
  fp1.read_files(); 

}
template<typename T>
struct Finally_Actions{
  Finally_Actions(T f): clean{f}{}; 
  ~Finally_Actions(){clean();}
  T clean; 
}; 
template<class T>
Finally_Actions<T> finally_actions(T f){
  return Finally_Actions<T>(f); 
}
void use_finally(){
  int* ptr = new int{12}; 
  char* buff = (char*)malloc(sizeof(char) * 1024); 
  auto ac1 = finally_actions([&]{
                               delete ptr; 
                               free(buff); 
                               cout << "Good Bye Cruel World!!" << endl; 
                             }); 
  int var =0; 
  auto ac2 = finally_actions([&](){
                               cout << "call to action2 var == " << var << endl; 
                             });  
  cout << "Var == " << var << endl; 
}
namespace Assert{
  enum class Mode: int {_ignore, _terminate, _throw};
  constexpr Mode currMode = CURRENT_MODE; 
  constexpr int currlevel = CURRENT_LEVEL;
  constexpr int default_level = 1; 
  constexpr bool level(int n){
    return(n <= CURRENT_LEVEL); 
  }
  struct Error: runtime_error{
    Error(const string& message): runtime_error{message}{}; 
  };
  string compose(const char* filename, const char* message, int lineno){ 
    stringstream s("(");
    s << filename << ":" << "{" << message << "," << to_string(lineno) << ")"; 
    return s.str(); 
  }
  template<bool condtion = level(default_level), class Except = Error>
  void dynamic_assertion(bool assertions, const char* message = "Dynamic Assertion failed"){
    if(assertions){return;}
    switch(CURRENT_MODE){
      case Mode::_ignore: return; 
      case Mode::_terminate: std::terminate(); 
      case Mode::_throw: throw std::runtime_error{compose(__FILE__, message, __LINE__)}; 
    }
  }
  void dynamic_assertions(bool b){
    return dynamic_assertion<true, Error>(b); 
  }
}
class NoCopy{
private:
 string message;  
public:
  NoCopy(string message1): message{message1}{}; 
  NoCopy(NoCopy& c1) = delete; //No copy operation cant be used as an exception object. 
  virtual void what(){cerr << message << endl; }
}; 
class CopyClass{
private: 
  string message; 
public: 
  CopyClass(string message1 = {}): message{message1}{}
  virtual void what(){cerr << message << endl;}
}; 
void throw_Exceptions(){
  try{
    int r; 
    cout << "Enter the value of r " << endl; 
  }catch(NoCopy& n1){ //error no copy operation defined for the object of given type. 
    n1.what(); 
  }catch(CopyClass& c1){c1.what(); }
}
void Enforcing_Invariants_and_assertions(int n){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  try{
    Assert::dynamic_assertion<Assert::level(2), Assert::Error>(n <= 2 || n >= 12); 
  }catch(std::runtime_error& r1){cerr << r1.what() << endl; } 
}
struct Minimial_Error{}; 
void Exception_and_stack_unwinding1(){
  string s1{"Not"}; 
  throw Minimial_Error{}; 
  string s2{"No call to destructor"}; 
}
void Exception_and_stack_unwinding2(){
  try{
    string s1 = "out"; 
    Exception_and_stack_unwinding1(); 
  }catch(Minimial_Error){}
}
void Exception_and_stack_unwinding(){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  string name{"something"}; 
  try{
    string s1 = "in"; 
    Exception_and_stack_unwinding2(); 
  }catch(Minimial_Error){}
}
class Out_of_range: std::out_of_range {
private: 
  int start, end;
  const string& message = "start<=end"; 
public: 
  Out_of_range(int s1, int e1, string m1 = {}): std::out_of_range{m1}{}; 
  virtual void what(){cerr << message << endl;}
};
void Exception_and_std_hierarichy(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int start, end; 
  cout << "Enter the value of start and end " << endl; 
  cin >> start >> end; 
  try{
   if(start <= end){
      throw Out_of_range{start, end}; 
    }else{
     throw Out_of_range{start, end, "something went wrong"}; 
    }
  }catch(std::out_of_range){cerr << "Done!" << endl; }
  catch(Out_of_range& r1){r1.what(); }
}
double compute()noexcept{
  throw std::runtime_error{"something went wrong"}; 
} 
void use_Noexcept_functions(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  try{
    compute(); 
  }catch(...){}
  
}
void somenoexceptfunction(int a, int b) noexcept{
  if(a < b){cout << a << endl;}
else{
    throw std::runtime_error{"terminating the program... "}; 
  }
}
class somePOD{
  int x, y; 
public: 
  somePOD(int x1, int y1): x{x1}, y{y1}{cout << x << " " << y << endl;};
  somePOD() = default;  
  ~somePOD() = default; 
};
class out_of_range_class{
public: 
  out_of_range_class(int x1, int y1): start{x1}, end{y1}{
    if(start < end){throw std::runtime_error{"start <= end"};}
  else{cout << "start == " << start << " " << "end == " << end << endl;}
  }
  virtual const char* what(){
    string somestring = to_string(__LINE__) + ": out of range error"; 
    return somestring.c_str(); 
  }
  out_of_range_class() = default; 
private: 
  int start, end; 
}; 
template<class T>
void use_Noexcept_operators() noexcept(std::is_pod<T>() == false){
  cout << __LINE__ << " " << __FUNCTION__ << endl;
  try{
    int x1, y1; 
    cin >> x1 >> y1; 
    out_of_range_class(x1, y1); 
  }catch(out_of_range_class& o1){cerr << o1.what() << endl;}
}
class Exceptionthrow1{
  int a, b; 
public: 
  Exceptionthrow1(int a1, int b1): a{a1}, b{b1}{
    if(a%2 == 0 || b%2 == 1){
      throw std::runtime_error{"cant have this"}; 
    }
  }; 
  Exceptionthrow1() = default; 
}; 
class Exceptionthrow2: public Exceptionthrow1{}; 
#ifdef cpp14
void someExceptionSpecifications(int a, int b) throw(Exceptionthrow1, Exceptionthrow2){
  try{
    throw Exceptionthrow1{12, 13}; 
  }catch(std::runtime_error){cerr << "Handled..." << endl;}
}
#endif
void use_Exception_Specifications(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
}
struct Coersion_Error{
  string message = "Coersion_Error"; 
  Coersion_Error(string s1 = {}): message{s1}{};
  virtual void what(){cerr << "coersion Error " << endl;}
};
struct Coersion_Error_1 : public Coersion_Error{
  string message = "Coersion Error"; 
  Coersion_Error_1(string s1 = {}): message{s1}{}; 
  virtual void what(){cerr << "some other Exceptions... " << endl;}
};
void catch_and_rethrow(int* arr, size_t N){
  try{
    if(N < 0 || N > (int) std::numeric_limits<int>::max()/2){throw std::out_of_range{"out of range"};}
  }
  catch(std::exception& e1){
    throw; 
  }
} 
void use_catch_and_rethrow(){
  try{
    int arr[3]{1, 2, 3}; 
    catch_and_rethrow(arr, -3);
    //Exception sliced ... 
  }catch(std::out_of_range& r1){cout << r1.what() << endl;}
}
vector<std::pair<int, string>> stringlengths(const vector<std::pair<int, string>>& c1){
  for(size_t i = 0; i < c1.size(); i++){
    if(c1[i].first < c1[i].second.size()){
      string message = "invalid string at" + to_string(i); 
      throw std::runtime_error{message.c_str()}; 
    }
  }
  return c1; 
}
void use_catch_every_exceptions(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  vector<std::pair<int, string>>* c1 = new vector<std::pair<int, string>>{{3, "abc"}, {4, "abcde"}, {5, "abc"}}; 
  try{ 
    vector<std::pair<int, string>> v1 = stringlengths(*c1); 
    cout << (v1.size() ? "DONE!" : "FAILED") << endl; 
  }catch(...){
    cerr << "failed, realeasing resources ... " << endl; 
    delete c1; 
  }
}
void use_multiple_Exception_Handler(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  vector<int>v1; 
  int i, r; cin >> i; 
  try{
     for(int k = 0; k < i; k++){ 
      cin >> r; 
      v1.push_back(r); 
      if(r%3 == 0){cout << "Throwing std::exceptions ... " << endl; throw std::exception{}; }
      else if(r%3 == 1){cout << "Throwing std::runtime_errors ... " << endl;throw std::out_of_range{"runtime_error"}; }
    else{cout << "Throwing std::out_of_range errors ... " << endl;throw std::out_of_range{"out of range"};}
    }
  }catch(std::exception& e1){
    cerr << e1.what() << endl; //
  }catch(std::out_of_range& r1){cout << r1.what() << endl;} //never called derrived from std::exception
  catch(std::runtime_error& r1){cout << r1.what() << endl;} //never caught order in which handled matters!!
  try{
     for(int k = 0; k < i; k++){ 
      cin >> r; 
      v1.push_back(r); 
      if(r%3 == 0){cout << "Throwing std::exceptions ... " << endl; throw std::exception{}; }
      else if(r%3 == 1){cout << "Throwing std::runtime_errors ... " << endl;throw std::out_of_range{"runtime_error"}; }
    else{cout << "Throwing std::out_of_range errors ... " << endl;throw std::out_of_range{"out of range"};}
    }
  }catch(std::runtime_error& e1){
    cerr << e1.what() << endl; //
  }catch(std::out_of_range& r1){cout << r1.what() << endl;} //never called derrived from std::exception
  catch(std::exception& r1){cout << r1.what() << endl;} //never caught order in which handled matters!!

}
void catching_Exceptions(){
  //Exception caught is the same type for which the expcection is being thrown.
  int a =12; 
  string b= "13";
  try{
   if(typeid(a).name() != typeid(b).name()){
      throw Coersion_Error{"something went wrong"}; 
    }else{
      a += stoi(b); 
      cout << a << endl; 
    }
  }catch(Coersion_Error c1){c1.what();}
  //Exception caught is the reference for an object for which the exception is being thrown. 
  try{
    if(typeid(a).name() != typeid(b).name()){
      b += to_string(a); 
      cout << b << endl; 
    }else{
      throw Coersion_Error{"something else went wrong"}; 
    }
  }catch(Coersion_Error& c1){
    c1.what(); 
  }
  //Exception caught is an unambiguous public base of the type for which hte expception is being thrown.   
  try{
    if(typeid(a).name() == typeid(b).name()){
      a += stoi(b); 
      cout << a << endl; 
    }else{
      throw Coersion_Error_1{"throwing coerion error 1"}; 
    }
  }catch(Coersion_Error c1){c1.what();}
  //The Exception being caugth is the pointer to the object for which the expcetion is being thrown. 
  int arr[12]{1, 2, 3, -2};
  int minimum = std::numeric_limits<int>::min(); 
  try{
    for(size_t i = 0; i < 12; i++){
      if(arr[i] < minimum){
        minimum = arr[i]; 
      }
    }
    if(minimum ^ std::numeric_limits<int>::min() == 0){
      Coersion_Error c1{"something wrong"}; 
      Coersion_Error* c2 = &c1; 
      throw c2; 
    }
  }catch(Coersion_Error* c1){c1->what();}
  int x1; 
  //Try and catch block introduce their own scope meaning whatever declared within the try block is only accessible within that block but not the catch block. 
  try{
    int r1 = 12; 
    throw std::runtime_error{"something went wrong... "}; 
  }catch(std::runtime_error& r2){
    r2.what(); int k = 13;
    #ifdef someerror
    cout << r1 << endl;
    #endif
  }
  use_catch_and_rethrow(); 
  use_catch_every_exceptions(); 
  use_multiple_Exception_Handler(); 
}
void use_catching_exceptions(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  catching_Exceptions(); 
}
enum class Kind:char{INT, STR};
class Function_Try_Block{
private:
  Kind k2; 
  int no = 12; 
  string s = "somestring"; 
public: 
  Function_Try_Block(Kind k1, int n1) try: k2{k1}, no{n1}{
    if(k2 == Kind::STR){throw std::runtime_error{"Incorrect Assignments"};}
  }catch(std::runtime_error& r1){cerr << r1.what() << endl; throw;}
  Function_Try_Block(Kind k1, string s1) try: k2{k1}, s{s1}{
    if(k2 == Kind::INT){throw std::runtime_error{"cant have this ... "};}
  }catch(...){cerr << "cant have this... " << endl; throw;}
}; 
void use_function_try_block(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  try{
    Function_Try_Block f1{Kind::INT, "133"};
  }catch(std::runtime_error& r1){cout << r1.what() << endl;}
  catch(...){cout << "caught with Exception All" << endl;}
}
[[noreturn]] void my_handler(){
  cerr << "Terminating the program... " << endl; 
  std::terminate(); 
}
void dnagerous_terminate_handler(){
  terminate_handler old = set_terminate(my_handler); 
  cout << "Restoring old terminate handler" << endl; 
  set_terminate(old); //restore old terminate handler. 
}
void use_terminations(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  dnagerous_terminate_handler(); 

}
int main(){
  use_Error_handling(); 
  use_traditional_Error_handling(); 
  use_alternative_view_of_exceptions(); 
  use_when_cant_use_exceptions(); 
 // use_Heriraical_Exception_Handling(); 
  Exceptions_and_Efficiency(); 
  Exception_Garuntees(); 
  Enforcing_Invariants_and_assertions(3);
  Exception_and_Resource_Mangement(); 
  throw_Exceptions(); 
  Exception_and_stack_unwinding2();
  Exception_and_std_hierarichy();
  #ifdef termination_of_program
  use_Noexcept_functions(); 
  #endif
  use_Noexcept_operators<somePOD>(); 
  use_finally();
  #ifdef cpp14
  use_Exception_Specifications(); 
  #endif
  use_catching_exceptions(); 
  use_function_try_block(); 
  use_terminations(); 
  return 0; 
}
