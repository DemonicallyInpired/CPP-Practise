#include<iostream>
#include<math.h>
#include<map>
#include<sstream>
#include<vector>
#include<limits>
#include<cstring>
using namespace std; 

enum class Kind: char{
  name, value, 
  plus = '+', minus = '-', mul = '*', div = '/', 
  lp = '(', rp = ')', print = ';', assign = '=', end
}; 
struct Token{
  Kind kind; 
  double numberval; 
  string stringval; 
};
int count; 
int errors(const string& s){
  count += 1; 
  cerr << s << endl; 
  return count; 
}
class Token_Stream{
private: 
  istream* is; 
  bool owns; 
  Token ct = {Kind::end}; 
public: 
  Token_Stream(istream* is1): is{is1}, owns{true}{}; 
  Token_Stream(istream& is1): is{&is1}, owns{false}{}; 
  
  void close(){if(owns){delete is;}}
  void setinputstrem(istream* is1){is = is1; owns = true;}
  void setinpustream(istream& is1){is = &is1; owns = false;}
  const Token& current(){return ct;}
  Token Lowlevelget(); 
  Token get(); 
  ~Token_Stream(){close(); }
}; 
Token Token_Stream::Lowlevelget(){
  char ch; 
  do{
    if(!is->get(ch)){return ct = {Kind::end};}
  }while(ch != '\n' && isspace(ch)); 
  switch(ch){
    case '\n': case ';': 
      return ct = {Kind::print}; 
    case '+': case '-': case '*': case '/': case '(': case ')': 
      return ct = {static_cast<Kind>(ch)}; 
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.': {
      is->putback(ch); 
      *is >> ct.numberval; 
      ct.kind = Kind::value; 
      return ct; 
    }
    default: {
      ct.stringval = ch; 
      if(isalpha(ch)){
        while(is->get(ch) && isalnum(ch)){
          ct.stringval += ch; 
        }
        is->putback(ch); 
        return ct = {Kind::name}; 
      }
    }
  }
}
Token Token_Stream::get(){
  char ch =0;
  is->putback(ch); 
  *is >> ch; 
  switch(ch){
    case 0: 
      return ct = {Kind::end}; 
    case '+': case '-': case '*': case '/': case '(': case ')': case ';': 
      return ct = {static_cast<Kind>(ch)}; 
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.': {
      is->putback(ch); 
      *is >> ct.numberval; 
      ct.kind = Kind::value; 
      return ct; 
    }
    default: {
      is->putback(ch); 
      *is >> ct.stringval; 
      ct.kind =Kind::name; 
      return ct; 
    }
  }
}
map<string, double>table; 
Token_Stream ts{cin}; 
double expr(bool get); 
double prim(bool get){
  if(get){ts.get();}
  switch(ts.current().kind){
    case Kind::value: {
      double v = ts.current().numberval; 
      ts.get(); 
      return v; 
    }
    case Kind::name: {
      double& v = table[ts.current().stringval]; 
      if(ts.get().kind == Kind::assign){v = expr(true);}
      return v; 
    }
    case Kind::minus: 
      return -prim(true); 
    case Kind::lp: {
      auto e = expr(true);
      if(ts.get().kind != Kind::rp){return errors("Expected a '('"); }
      ts.get(); 
      return e; 
    }
    default: 
      return errors("Expected a primary"); 
  }
}
double term(bool get){
  double left = prim(get); 
  for(;;){
    switch(ts.current().kind){
      case Kind::mul: 
        left *= prim(true);
        break; 
      case Kind::div: {
        if(auto d = prim(true)){
          left /= d; 
          break; 
        }else{
          return errors("Zero division error"); 
        }
      }
      default: 
        return left; 
    }
  }
}
double expr(bool get){
  double left = term(get); 
  for(;;){
    switch(ts.current().kind){
      case Kind::plus: 
        left += term(true); 
        break; 
      case Kind::minus: 
        left -= term(true); 
        break; 
      default: 
        return left; 
    }
  }
}
void calculate(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  for(;;){
    ts.get(); 
    if(ts.current().kind == Kind::end){break;}
    if(ts.current().kind == Kind::rp){continue;}
    cout << expr(false) << endl; 
  }
}
string precedence_and_max_munching_rule(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int a = 12, b = 13, c = 143; 
  int res = a = b + 1 > 2 ? 2 : 3; //expcet for assignment and uniary operator all the other operators are left-associative. 
  string s = (res == 2 ? "True" : "False"); 
  cout << s << endl; 
  int x =12; 
  x+++1; //Tokens are composed so as to consider maximum no of character possible meaning x+++1 is treated as x++ + 143
  cout << (a or b) << endl; 
  cout << (a and b) << endl; 
  cout << (a xor b) << endl; 
  cout << (a and_eq b) << endl; 
  cout << (a or_eq b) << endl; 
  cout << (a xor_eq b) << endl; 
  return s;  
}
void results(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  float r =12.3f; 
  double d = 13.3e+2f; 
  long int r1 =12; 
  bool a =12; 
  char c ='A'; 
  auto r2 = (r + d + r1 + a + c); //the result of an expression is going to be that of the longest operand type or the type most capable of representing such literlas.  
  cout << typeid(r).name() << endl; 
  int x = 12, y = 13; 
  int j = x = y; //Whenever plausible the result of an expression taking lval value operands is an lval expression. 
  int* ptr = &++x; //OK ++x is an lval value. 
  #ifdef errors
  int* ptr1 = &x++; //error x++ is a temporory(rval).
  int& r = (x < y ? x : 1); //error 1 is not an lval.
  int&& r1 = (x < y ? x : 1); //error x is not an rval. 
  #endif
  int* ptr2 = &(x < y ? x : y); //OK still an lval. 
  int&& rval = (x < y ? 1 :2); //OK
  cout << j << " " << *ptr << " " << *ptr2 << " " << " " << rval << endl; 
  #ifdef not_to_throw_exceptions
  cout << (d / 0) << endl; //Division by zero and runtime range checking are often not garunteed to throw an standard expcetion :(
  #endif
  int count = 0; 
  while(true){
    if(count < 0){break;}
    count += 1; 
  }
  cout << "count exceed the numeric_limits of an integgral literals:: " << count << endl; 
}
void order_of_evaluations(int a, int b){
  cout << (a + b) << endl; 
}
void use_order_of_evaluations(){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  vector<int>r{1,2, 3, 4}; 
  int randomval = 1; 
  r[++randomval] = randomval; //unspecified wheter the user meant r[2] = 2 or r[2] = 1; 
  cout << randomval << " " << r[randomval] << endl; 
  order_of_evaluations(r[randomval], randomval); //context dependent expression. Unspeicified wheter the arguments are evaluated from left to right or right to left.
  int rsomeval = (randomval, randomval + 1); 
  cout << rsomeval << endl; //RH operand is always evaluated first in an expression. 
  int* ptr = &randomval; 
  //Preffers short circuit evaluation meaning the second operand is going to be evaluated only if the fist is true for && and vice versa for or. 
  if(ptr && *ptr == 2){cout << "True" << endl;}else{cout << "False" << endl;} 
}
void operator_precedence(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int i = 12; 
  int maxint =std::numeric_limits<int>::max();
  if(i <= 0 || maxint >= i){cout << "True " << endl;}else{cout << "False " << endl;}
  if(i <= 0 || (0 || maxint) >= i){cout << "True " << endl;}else{cout << "False " << endl;}
  if((i <= 0) || (maxint >= i)){cout << "True " << endl;}else{cout << "False " << endl;}
  if(maxint >= 13 >= i){cout << "True " << endl;}else{cout << "False " << endl;}
  if(maxint >= 13 && 13 >= i){cout << "True " << endl;}else{cout << "False " << endl; }
  int mask = 012; //10; 
  cout << (0 & mask == 0) << endl; //interpreted as 12 & (mask == 0) cause == has higher precedence than &
  cout << ((0 & mask) == 0) << endl; 
}
void Temporory_Objects(string& s1, string& s2, string& s3){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  const char* cs = (s1 + s2).c_str(); //cs points to a temporory whose lifetime is that of an expressioin of which its a part. 
  if(strlen(cs) <= strlen((s2 + s3).c_str())){cout << *cs << endl;}else{cout << "False " << endl;}//pontential error cs might points to deallocated storage. 
  const string& rval = s1 + s2; //OK bound to a reference lifetime is that of that of the reference. 
  string ss = s2 + s3; 
  if(rval.size() < ss.size()){cout << rval << endl;}else{cout << "False " << endl; }
  string&& rvalref1 = std::move(string{s2 + s3}); //explicit construction
  cout << rvalref1 << endl; 
}
void use_temporory_objects(){
  string s1 = "something"; 
  string s2 = "something_Else"; 
  string s3 = "something_there_else"; 
  Temporory_Objects(s1, s2, s3); 
}
constexpr int sqrt_helper(int sq, int d, int a){
  return sq <= a ? sqrt_helper(sq + d, d + 2, a): d; 
}
constexpr int isqrt(int x){
  return sqrt_helper(1, 3, x)/2 - 1; 
}
constexpr int const_expressions(){
  #ifdef randomerrors
  cout << __FUNCTION__ << " " << __LINE__ << endl; //a constexpr function can only be used as a pure value function. 
  #endif
  constexpr int r = 12; //allow compile time evaluation and hence can be used only with something that can be evaluated at compile time. 
  int randomval = 12; 
  constexpr int r1 = r; //OK 
  #ifdef errors_present
  constexpr int r2 = randomval; //error cant be evaluated a compile time. 
  //error require runtime evaluation. 
  for(size_t i= 0; i < 12; i++){
    cout << i << endl; 
  }
  constexpr int constvsconstexp = somevalues; //error cant be evaluated with compile time.  
  #endif
  const int somevalues = randomval; //const can be initialized with something that is not constexpr.
  return(randomval <= r) ? r :randomval; //OK the alternative not selected may not be a constexpr and may not even require compile time evaluatiokn. 
}
void use_constexprs(){
  cout << __LINE__ << " " << __FUNCTION__ << endl; 
  const_expressions(); 
  cout << isqrt(12) << endl; 
  cout << isqrt(255) << endl; 
}
constexpr double square(int x){
  return x * x; 
}
//user define types that can be used as constexprs(should have a constexpr constructor meaning each of the constructor elements shoudl be initialized with a constexpr and the body of the constructor should be empty); 
class Literal_types{
private: 
  int x, y; 
public:
  constexpr Literal_types(int x1, int y1): x{x1}, y{y1}{};
  constexpr float calc_distance(int x1, int y1) const{
    return sqrt(square(x - x1) + square(y - y1)); 
  }
}; 
void use_Literal_Types(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  constexpr Literal_types l1{12, 13};
  int distance = l1.calc_distance(12, 13);
  cout << distance << endl; 
  distance = l1.calc_distance(-12, -13); 
  cout << distance << endl; 
}
int main(int argc, char* argv[]){
  switch(argc){
    case 1: 
      return errors("Too few arguments"); 
    case 2: 
      ts.setinputstrem(new istringstream{argv[1]}); 
      break; 
    default: 
      return errors("Too many arguments"); 
  }
  table["pi"] = 3.14; 
  table["e"] = 2.71; 
  calculate(); 
  precedence_and_max_munching_rule(); 
  results(); 
  use_order_of_evaluations(); 
  operator_precedence(); 
  use_temporory_objects();
  use_constexprs();
  use_Literal_Types(); 
  return count; 
}
