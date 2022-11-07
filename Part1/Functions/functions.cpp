#define res_compilation true
#define FOREVER for(;;)
#define BEGIN {
#define END }
#define PRINT(x, y) cout << #x << x##y
#define SQUARE(x) x* x
#include<functional>
#include<math.h>
#include<iostream>
#include<map>
#include<cassert>
#include<vector>
#include<complex>
#include<cstring>
#include<cstdarg>
#include<algorithm>
using return_type = int; 
using namespace std; 
struct Person{
  int c; 
  Person(int c1): c{c1}{}; 
  virtual auto something(int a, int b) const noexcept [[noreturn]]->int{return(a + b + c);} 
}; 
void use_function_declrations(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  Person p1{12}; 
  cout << p1.something(12, 13) << endl;   
}
int improve_mantainibility(){
  map<string, int>pieces{{"King", 10}, {"Queen", 20}, {"Rook", 5}, {"Knight", 9}, {"Bishop", 6}, {"Pawn", 1}}; 
  string move;
  cout << "Enter the move" << endl; 
  cin >> move;
  bool present{false}; 
  for(auto& i: pieces){
    if(i.first == move){present == true; break;}
  }
  assert(present == false); 
  for(auto& i: pieces){if(i.first == move ){return i.second;}}
  return 0; 
}
void check_square(int nums, int margin){
  auto squares = [&](int a){return(a * a);}; 
  if(squares(nums) < nums){cout << "False " << endl;}else{cout << "True " << endl;}
}
void use_why_functions(){
  //improve mantability by breaking large piece of code into manageable chunk, can therefore be consider as the basic unit of computation in CPP much like how user-defined 
  //types are often considered as the basic unit of holding onto to the representation of data. 
  //prevent from introducing arbitary code in between other computation again and again thereby improving reusibility in the code. 
  //provide a layer of abstraction. 
  //prevent from using the traditional loop exit context most often in the code such as gotos and continue. Thereby making the code much more declrative and close to the user as opposed
  //to imparitive and close to the machine code.
  //Keep the function scope smaller, cause bugs tends to creep in when one cant see the entireity of what a function does in a single screen. 
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  #ifdef imporove_mantaibility
  map<string, int>pieces{{"King", 10}, {"Queen", 20}, {"Rook", 5}, {"Knight", 9}, {"Bishop", 6}, {"Pawn", 1}};
  string move; 
  cout << "Enter move"; 
  cin >> move; 
  bool present{false}; 
  for(std::pair<string, int>& i: pieces){
    if(i.first == move){present = true; break;}
  }
  assert(present == false); 
  int move{}; 
  for(auto& i: pieces){if(i.first == move){move = i.second;}
  if(move >= 20){cout << "Won" << endl;}else{cout << "lost " << endl;}
  #endif
  int move = improve_mantainibility(); 
  if(move >= 20){cout << "Won" << endl;}else{
    cout << "lost" << endl; 
  }
  int nums; 
  cout << "Enter the nums " << endl; 
  cin >> nums; 
  #ifdef redundant_code
  int nums; 
  cout << "Enter the number :: " << endl; 
  cin >> nums; 
  assert(nums * nums > 0); 
  if(nums * nums < 13){cout << "False " << endl;}else{cout << "True " << endl;}
  cout << "Enter the value of nums again " << endl; 
  cin >> nums; 
  assert(nums * nums > 0); 
  if(nums * nums > 14){cout << "True " << endl;}else{cout << "False " << endl;}
  #endif
  check_square(nums, 13); 
  check_square(nums, 14); 
}
return_type name_of_the_function(int argument1, bool argument2){
  return(argument1%argument2); 
}
#ifdef dont_allow_implicit_conversion_between_unrelated_types
void name_of_the_function(int argument1, string argument2){
  if(argument2 == to_string(argument1)){cout << "True " << endl;}
  else{cout << "False " << endl; }
}
name_of_the_function(12, 13); //error unrelated types. cant convert std::String to int; 
#endif
class someclass{
  int a1; 
public: 
  static int a; 
  //not associated with any representation of object of type someclass, consquently can have only single memory address throughout its lifetime and can be intialized only once, to presisit its value throughout the function call. 
  static int somefunction(){return a;}
  int somefunction(int a, int b)const{
    #ifdef errors
    a += b; //error cant modify objects in the given scope of the function
    #endif
    return(a > b) ? (a%b) : (b%a); 
  }
  virtual void somefunction1(){
    //have declration in the base class that can't be overriden in the derrived class; 
    int res =12; 
    string value = (res <= 12) ? "True" : "False"; 
    cout << value << endl; 
  }
  //has a function declration that is overriden in the derrived class. 
  virtual void somefunction2(int res = 1) final{
    cout << res << endl; 
  }
  someclass(int x1 = {}): a1{x1}{}; 
};
float somefunction3(int a, int b) noexcept{
  //function isn't allow to throw any exception, if thrown however, the compiler might involve in call std::terminate(), therefore, consquentially terminating the program without engaging in any error recovery mechanisms. 
  return(a / b); 
}
void somefunction4(bool severity) [[noreturn]]{
  //attribute specifier could be placed anywhere in the program indicates that the function doesnt return by normal mechanisms
  if(severity){exit(1);}
  else{throw std::runtime_error{"No Severity"}; }
}
int someclass::a = 12;
void function_declration_without_arguments_names(int a, int b, int); 
  //simplify maintainence and allows for improving the readibility of the code for the next programmer or planning ahead of the execution in somewhat of the sense that the arguments not named are often used to indicate that such argument can't be used in the scope of the function.  
void function_declration_without_arguments_names(int a, int b, int){
  cout << (((a + b) < 2) ? (a + b) : (a - b)) << endl;  
}
//function arguments name are not the part of function declration therefore, we can have different arguments names for multiple function declration within the same scope. 
int somefunction5(int a, int b); 
int somefunction5(int x, int y){return(x + y); }
void parts_of_function_declrations(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  const char* res = (name_of_the_function(12, 13) == 12 ? "True" : "False"); //function arguments are passed so to follow the copy intialization rule, meaning the formal arguments(parameters) are copied into the actual arguments while considering copy intializatiokn that allows narrowing amongst related types. 
  cout << res << endl; 
  cout << someclass::somefunction() << endl; 
  someclass c1{12}; 
  c1.somefunction1(); 
  c1.somefunction2();
  somefunction3(12, 3); 
  #ifdef errors
  somefunction3(12, 0);
  #endif
  //somefunction4(true); 
  function_declration_without_arguments_names(12, 13, 14); 
  cout << somefunction5(12, 13) << endl; 
}
void function_declrations(int, int, float); 
void function_declrations(int a, int b, float c); //OK multiple declration allowed in the same scope,
using PTOF = void(*)(int, int, float); 
void function_defintion(int x, int y, float c){
  float z = (c + x % y);
  cout << (z < 12 ? z : (z + 2)) << endl;
  PTOF p1 = &function_defintion; 
  cout << p1 << endl; //set aside memory to represent a function(definition); 
}
#ifdef follow_ODR
//cant have multiple definition in the same scope. 
void function_defintion(int a, int b, float c){
  float z = (a + b ^c); 
  cout << z << endl; 
}
#endif
void use_function_definition(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  function_defintion(12, 12, 13.2); 
}
//return type corresponding to the value returned from the function in traditional sense the return value is mentione before the function name if not using the explicit return using the indirection operation. 
int return_value_follow_copy_semantics(double f){
  return f; 
}
template<class Source, class Target>
Target narrow_cast(Source s){
  Target res = s; 
  if(s != res){
    throw std::runtime_error{"Narrow casting failed"}; 
  }
  return res; 
}
void somestring(string s){
  if(s.size() < 4){cerr << "strlen(s) <= 5"; }
}
auto explicit_return_value(int res)->float{
  //explicit return by indirection -> operator where auto indicate such intent for return type, mostly usefull in generic programming where return type of a function is deduced form the template arugments
  float calc = rand(); 

  return(calc < 2 ? calc : calc/2); 
}
template<class T, class V>
auto multiply(const vector<vector<T>>& m1, const vector<vector<V>>& v1)->vector<vector<decltype(T{} + V{})>>{
  vector<vector<decltype(T{} * V{})>>res; 
  assert(m1[0].size() == v1[0].size() && m1.size() == v1.size()); 
  for(size_t i = 0; i < m1.size(); i++){
    for(size_t j = 0; j < m1[0].size(); j++){
      res[i].push_back(m1[i][j] * v1[i][j]); 
    }
  }
  return res; 
}
void use_return_Values(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  float a = 12.3f; 
  try{
    auto res = narrow_cast<float, int>(return_value_follow_copy_semantics(a)); 
  }catch(std::runtime_error& r1){
    cerr << "copy intialization semantics allows narrowing:( " << endl; 
  }
  #ifdef doesnt_allow_conversion_between_unrelated_types
  somestring("something"); 
  #endif
  cout << typeid(explicit_return_value(2)).name() << endl; 
  vector<vector<double>>m1{{1, 2.2, 3, 4}, {3, 2, -4, 2}};
  vector<vector<int>>m2{{1, 2, 3, 4}, {4, 3, 2, 1}};  
#ifdef something
   auto res = multiply(m1, m2);
  for(size_t i = 0; i < res.size(); i++){
    for(size_t j = 0; j < res[0].size(); j++){cout << res[i][j] << " "; }
    cout << endl; 
  }
  #endif
}
inline void lay_out_body_inline(){
  double p = 12.3f; 
  int res = 12; 
  if(res <= 12){
    res = abs((int)(res - p));  
  }else{
    res = abs((int)(p - res)); 
  }
}
void without_inlined(){
 double p = 12.3f; 
  int res = 12; 
  if(res <= 12){
    res = abs((int)(res - p)); 
  }else{
    res = abs((int)(p - res)); 
  }
}
inline int fact(int n){
  if(n <= 0){return 1;}
  return n * fact(n-1); 
}
int factorial(int n){
  if(n <= 0){return 1;}else{return n * factorial(n - 1);}
}
void use_inline_functions(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  float start = clock(); 
  for(size_t i = 0; i < 100; i++){
    lay_out_body_inline(); 
  }
  float end = clock(); 
  cout << (end - start)/100 << endl; 
  start = clock(); 
  for(size_t i = 0; i < 100; i++){
    without_inlined(); 
  }
  end = clock(); 
  cout << (end - start)/100 << endl; 
  cout << "resursive functions are often implementation dependenet for the most of the case for inlining specially in case where the compiler may perform some clever optimization " << endl; 
  start = clock(); 
  int res = fact(12);
  end = clock(); 
  cout << (end - start)/100 << endl; 
  start = clock(); 
  int res1 = factorial(12); 
  end = clock(); 
  cout << (end - start)/100 << endl; 
}
constexpr int constexprfunction(){
  #ifdef errors
  int variable = 12; //cant have variables require runtime evaluation
  for(size_t i = 0; i < 12; i++){
    cout << i << endl; //cant have loops require runtime evaluatioln
  }
  varibale += 1; //modifying the object's value require runtime evaluation, hence cant be used in a constexpr function that can only be evaluated at compile itme. 
  #endif
  constexpr int x = 12; //OK constexpr doesnt require compile time evaluation paramter could be considered to be know at the compile time. 
  constexpr int y = 13; //OK constexpr, parameters could be considered to be know at the compile time. 
  return(x < y) ? x : y; 
}
/*constexpr const int use_constexpr_and_references(const int& s){
  constexpr int someres = s; 
  return someres; 
}*/
void use_constexpr_functions(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  constexpr int res = constexprfunction();
  cout << res << endl; 
  //Normally reference arguments cant be used in constexpr function however, const references are still as usefull as ever for such instance cause they wont require any runtime evaluatioln. 
  constexpr int someval = 12; 
  //cout << use_constexpr_and_references(someval) << endl; //OK const reference can bound to both lval and rval reference. 
  //constexpr int something = use_constexpr_and_references(someval);  
  //cout << something << endl; 
}
constexpr const int conditional_evauluations(int i){
  return(i < 12) ? i : throw std::runtime_error{"cant have this"}; 
}
void use_condition_evaluations(){
  constexpr int res = conditional_evauluations(11); 
  try{
    int something = conditional_evauluations(13); 
  }catch(std::runtime_error& r1){
    cerr << r1.what() << endl; 
  }
}
void use_no_return_functions() [[noreturn]]{
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  cout << "Enter the value of i " << endl; 
  int i; 
  cin >> i; 
  try{
    if(i < 12){
      exit(1); 
    }else{
      throw std::runtime_error{"something wrong"}; 
    }
  }catch(std::runtime_error& r1){
    cerr << r1.what() << endl; 
  }
}
int using_static_recursively(int n){
  static int n1 = n; 
  int res = using_static_recursively(n1-1); //affect of using static variable recursively within a function is undefined. 
  if(res <= 0){return 1;} else{return res;}
}

void use_local_variables_and_statics(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
 int a = 10; 
  while(a--){
    int local{}; 
    static int static_value{}; //is intialized only once, have same mem address throughout the lifeftime, can presist its value throughout the function call.  
    cout << "local:: " <<  local++ << " " << "static " << static_value++ << endl;  
  }
  #ifdef errors
  cout << using_static_recursively(12) << endl; 
  #endif
}
size_t arguments_parsing_by_value(char* first, char* last, char value){
  size_t count{}; 
  bool found{false}; 
  while(first != last){
    if(*first == value){found = true; return count;}
    count += 1; first++;
  }
  if(!found){return -1;}
}
void use_arguments_parsing(){
  char somenames[]{"something"}; 
  const int sizes = strlen(somenames); 
  char* last = &somenames[sizes]; 
  int index = arguments_parsing_by_value(somenames, last, 'n'); //modify the copy of the arguments passed not the actual arguments meaning last reamains the same. 
}
void refernce_arguments(int& a, int& b){
  a += 1; 
  b += 1; 
}
class someclass1{
private: 
  int a; 
  float b; 
  char ch; 
  string s; 
public: 
  someclass1(int a1 = {}, float b1 = {}, char ch1 = {}, string s1 = {}): a{a1}, b{b1}, ch{ch1}, s{s1}{}; 
  friend ostream& operator <<(ostream& os, const someclass1& s1){
    os << s1.a << " " << s1.b << " " << s1.ch << s1.s << endl; 
    return os; 
  }
}; 
void use_refernce_for_larger_representation_of_object(const someclass1& s1){
  cout << s1; //use const reference when we dont need to modify the object in the given scope or when the only intention of reference is to allow optimization for reading object as opposing to copying. 
}
void use_const_reference_for_type_conversions(const float& f){
  if(f < 12){cout << f << endl;}
  else{cout << f + 12 << endl; }
}
void use_reference_arguments(){
  cout << __FUNCTION__ << " " << __LINE__ << '\n' ; 
  int a =12; 
  int b = 13; 
  refernce_arguments(a, b); //modify the actual value being refereneced. 
  cout << a << " " << b << endl; 
  someclass1 s1{12, 12.3f, 'a', "something"}; 
  use_refernce_for_larger_representation_of_object(s1); 
  double d = 12.33; 
  use_const_reference_for_type_conversions(d); //implicit conversion to double prevent change of the values or modification of soon to disappear temporory holding the reference. 
}
void array_arguments(int arr[], size_t N){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  for(size_t i = 0; i < N; i++){
    cout << arr[i] << " "; 
  }
}
void array_arguments1(int* arr, int N){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  for(size_t i = 0; i < N; i++){
    cout << *(arr + i) << " "; //arrays are never passed by the value rather pointer to the first element. 
  }
}
void use_array_arguments(){
  int arr[3]{1, 2, 3}; 
  array_arguments(arr, 5); 
  array_arguments1(arr, 5); 
}
void check_severity(int severity ...){
  va_list va; 
  va_start(va, severity); 
  for(;;){
    char* p = va_arg(va, char*);
    if(p == nullptr){break;}
    cerr <<p << '\n';
  }
  if(severity){cout << "True" << endl;}
}
template<class T>
void another_unspecified_arguments(int severity, std::initializer_list<T>errs){
  for(auto& i: errs){cerr << i << '\n' << endl;}
  if(severity){cout << "True " << endl;}
}
class Default_arguments{
private: 
  int x1, x2;
public: 
  static int default_args; 
  #ifdef not_default
  Default_arguments(int x, int x21): x1{x}, x2{x21}{}; 
  Default_arguments(): x1{}, x2{}{};   
  Default_arguments(int xx): x1{xx}, x2{}{}; 
  #endif
  Default_arguments(int x = {}): x1{x}{};
  friend ostream& operator <<(ostream& os, const Default_arguments& d1){
    os << d1.x1 << " " << d1.x2; 
    return os; 
  }
  int f(int x1 = default_args){cout << x1 << endl;}
  #ifdef errors_can_use_default_arguments_only_as_trailing_args
  void default_args_functions(int x1, char* p = nullptr, int c);
  void default_args_functions1(int x1 = int{}, int z); 
  #endif
  void default_args_functions(int x1, int y1 = int{}, const char* p = nullptr){
    if(p && strlen(p) > 2){cout << p << endl;}else{cout << "cant derefernce nullptr " << endl;}
  }
  #ifdef cant_have_overloaded_function_with_default_args_having_different_value_in_the_same_scope
  void default_args_functions(int x1, int y1 = 2, const char* p = nullptr); 
  #endif
};
int Default_arguments::default_args = 12; //default value; 
void use_default_arguments(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  Default_arguments d1; 
  cout << d1 << endl; 
  d1.f(); //f(12); 
  d1.default_args = 9; 
  d1.f(); //maybe f(9); //avoid changing default args in the same scope cause that can introduce subtle context-dependencies. 
  d1.default_args_functions(12); 
  d1.default_args_functions(12, 13, "something"); 
}
int power(int a, int b){
  for(size_t i = 0; i < b; i++){
    a *= a; 
  }
  return a; 
}
#ifdef ambiguous_overload //two or more function overload possible at the highest level of the overloaded function scope. 
int power(int a, long int b){
  ans = 1; 
  for(size_t i = 0; i < b; i++){ans *= a;}
  return ans; 
}
#endif
//x = a ^ b
//log(x) = b * log(a)
//x = e ^ (b * log(a))
double power(int a, double b){
  double ans =1; 
  for(float i = 0; i < (b * log(a)); i++){
    ans*= 2.71; 
  }
  return ans; 
}
template<class T>
double power(complex<T>c1, int exponent){
  int ans = 1; 
  for(size_t i = 0; i < exponent; i++){
    ans *= i; 
  }
  return ans; 
}
double power(double base, double exponent ...){
  va_list va; 
  va_start(va, exponent);
  double ans{1}, remainder{exponent}; 
  for(;;){
    int res = va_arg(va, int); 
    if(static_cast<int>(res) == static_cast<int>('#')){break;}
    remainder += res; 
  }
  for(double i = 0; i < remainder * log(base); i++){
    ans *= 2.71; 
  }

  return ans; 
}
//dont consider return type in overload match to prevent subtle context dependecies 
namespace ns{
  void somefunctionoverload(int a, int b, int c){
    cout << (a + b + c) << endl; 
  }
  //OK overloaded within the same scope. 
  void somefunctionoverload(int a, int b){
  cout << (a + b) << endl; 
  }
}; 
void somefunctionoverload(int a, int b){
  cout << (a + b); 
}
class Base_class{
  int x; 
public: 
  void f(int& res){
    x += res; 
    cout << x << endl; 
  }
  void f1(int& res){
    x += res; 
    cout << x << endl; 
  }
  Base_class(int x1 = {}) :x{x1}{}; 
}; 
class Derrived_class: public Base_class{
  int x; 
public: 
  //Base and derrived class provide their own scope meaning there is no overload between f from base and f from Derrived in the given isntance. 
  void f(int& res, int c){
    x += (res + c); 
    cout << x << endl; 
  }
  Derrived_class(int x1 = {}): x{x1}{}; 
}; 
void use_overloaded_functions(){
  cout << __FUNCTION__ << " " << __LINE__ << '\n'; 
  //int res = power(2.2, 2); //implicit conversion of double to int call not allowed for call power(int, double), preffer safe promotion over unsafe conversions; 
  int res = power(2, 2.2); 
  int res1 = power('c', 2); //OK implicit conversion of c to int. 
  int res2 = power(static_cast<int>('a'), 2); //explicit type conversions. 
  double res3 = power(2.2, 2.2, 3.44, 2.32, '#'); 
  cout << res << " " << res1 << " " << res2 << " " << res3 << endl; 
  #ifdef function_overload_only_within_same_overloaded_scope
  somefunctionoverload(12, 13, 14); 
  #endif
  ns::somefunctionoverload(12, 13, 14); 
  ns::somefunctionoverload(12, 13); 
  somefunctionoverload(12, 13); 
  Derrived_class d1{12}; 
  int someres =12;
  #ifdef errors
  d1.f(someres);
  #endif
  d1.f(someres, 12); 
  d1.f1(someres); 
}
using Cmp = int(*)(const void*, const void*); 
void use_pointer_to_functions(void* base, size_t n, size_t sz, Cmp comparator){
  for(int gap = n/2; gap > 0; gap /= 2){
    for(int i = gap; i != n; i++){
      for(int j = i-gap; j >= 0; j-= gap){
        char* b = static_cast<char*>(base); 
        char* pj = b + j * sz; 
        char* pjg = b + (j + gap) * sz; 
        if(comparator(pj, pjg) > 0){
          for(int k = 0; k != sz; k++){
            char temp = pj[k]; 
            pj[k] = pjg[k]; 
            pjg[k] = temp; 
          }
        }
      }
    }
  }
}
struct Records{
  const char* name; 
  int no; 
  friend ostream& operator <<(ostream& os, const Records& r1){
    os << r1.name << " " << r1.no; 
    return os; 
  }
};
int compare1(const void* a, const void* b){
  return strcmp(static_cast<const Records*>(a)->name, static_cast<const Records*>(b)->name); 
}
int compare2(const void* a, const void* b){
  return reinterpret_cast<const Records*>(a)->no - reinterpret_cast<const Records*>(b)->no; 
}
void print_records(vector<Records>& r1){
  for(auto& i: r1){cout << i;}
}
void sort_records(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  vector<Records> r1{
    {"something", 12}, 
    {"abs", 13}, 
    {"bcz", 110}, 
    {"rr", -12}
  }; 
  use_pointer_to_functions(&r1[0], r1.size(), sizeof(Records), &compare1);  
  print_records(r1); 
  use_pointer_to_functions(&r1[0], 4, sizeof(r1[0]), &compare2);
  print_records(r1); 
}
void paramaterizing_using_lambdas(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
   vector<Records> r1{
    {"something", 12}, 
    {"abs", 13}, 
    {"bcz", 110}, 
    {"rr", -12}
  };
  sort(r1.begin(), r1.end(), [&](const Records c1, const Records c2)->int{
    int res = strcmp(c1.name, c2.name); 
    return res; 
  });
  print_records(r1);
  sort(r1.begin(), r1.end(), [&](const Records c1, const Records c2)->bool{return c1.no > c2.no;}); 
  print_records(r1); 
}
void use_macros(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int count{1}; 
  FOREVER
    BEGIN 
      PRINT(12, 13);
      count += 1; 
      if(count > 2){break;}
    END
    int x = 2; 
    int y =  10;
    cout << "Dangerous macros expanded as string literals " << endl; 
    cout << SQUARE(x + y) << endl; //treated as x+y*y+x => (10 * 4 + 10) when expanded 
}
void use_conditional_compilations(){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  int res = 12; 
  int res1 = 13;  
  #ifdef res_compilation
  res += (res - res1); 
  #endif
  cout << res << endl; 
  #ifndef somecompilation
  res -= 13; 
  #endif
  cout << res << endl; 
}
void use_predifined_macros(){}
int main(int argc, char* argv[]){
  use_function_declrations(); 
  use_why_functions(); 
  parts_of_function_declrations();
  use_function_definition(); 
  use_return_Values(); 
  use_inline_functions(); 
  use_constexpr_functions();
  use_condition_evaluations(); 
  use_no_return_functions(); 
  use_local_variables_and_statics(); 
  use_reference_arguments();
  use_array_arguments(); 
  try{
    switch(argc){
      case 0: case 1: 
        throw std::runtime_error{"unexpected arguments"};
      case 2:
        check_severity(0, argv[0], argv[1], nullptr); 
        break;
      case 3: 
        check_severity(1, argv[0], argv[1], argv[2], nullptr); 
        break; 
      default: {
        char message[]{"called with"};
        check_severity(1, argv[0], message, to_string(argc-1).c_str(), string{"arguments"}.c_str(), nullptr);
      }
    }
  }catch(std::runtime_error& r1){cerr << r1.what() << endl;}
  try{
    switch(argc){
      case 0: case 1: 
        throw std::runtime_error{"unexpected Arguments"}; 
      case 2: 
        another_unspecified_arguments<char*>(0, {argv[0], argv[1]});
        break; 
      case 3: 
        another_unspecified_arguments<char*>(1, {argv[0], argv[1], argv[2]}); 
        break; 
      default: 
        another_unspecified_arguments<const char*>(1, {"called with", to_string(argc-1).c_str(), "arguments"});
    }
  }catch(std::runtime_error& r1){cerr << r1.what() << endl; }
  sort_records();
  paramaterizing_using_lambdas();
  use_default_arguments(); 
  use_overloaded_functions(); 
  use_macros();
  use_conditional_compilations(); 
  return 0; 
}
