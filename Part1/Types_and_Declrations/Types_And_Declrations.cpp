#include<iostream>
#include<limits>
#include<math.h>
#include<cassert>
#include<vector>
#include<cstring>
#include<cassert>
#include<complex>
#include<algorithm>
using namespace std; 
void implementation_Defined(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  char a = 12; 
  cout << (int)a << endl; //well-defined char is atleast a byte on any given implementation meaing it can account for 256 different value either from -127 to 127 as in the singed char or 0 to 255 as in the unsinged char
  char b = 255; 
  cout << (int)b << endl; //implementation defiend depends on all bit one patter of char when extended to integer. 
}
void unspecified(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int* ptr = new int; //unspecified values; 
  cout << *ptr << endl; 
}
void undefined_behavior(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  const int sizes =2; 
  int arr[sizes]; 
  arr[3] = 4; 
  cout << arr[3] << endl; //overwriting unrelated data, can possibly trigger hardware error or exception
}
void check_assumptions(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  static_assert(sizeof(int) <= 4, "sizeof int is too small"); 
  cout << std::numeric_limits<int>::max() << " " << std::numeric_limits<int>::min() << endl; 
  cout << std::numeric_limits<char>::is_signed << endl; 
}
bool check_predicate(int a, int b){
  return(a > b) ? true: false; 
}
void Booleans(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  bool a = true; 
  bool b = false; 
  bool c = 12; 
  bool d{12!=0}; 
  cout << (a + b) << endl; 
  cout << (a - b) << endl; 
  cout << (a * b) << endl; 
  cout << (b/a) << endl; 
  cout << (d && c) << endl;
  cout << (d || c) << endl; 
  cout << (d ^ c) << endl; 
  cout << (c & a) << endl; 
  cout << (c | a) << endl; 
  cout << (c &= a) << endl; 
  cout << (c or_eq a) << endl; 
  cout << (c xor_eq a) << endl; 
}
bool is_open(FILE* fp){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  const int sizes = 1025; 
  if(fp != nullptr){
    char buffer[sizes]; 
    fread(buffer, sizeof(buffer), 1, fp); 
    fclose(fp); 
    return true; 
  }else{
    return false; 
  }
}
void use_is_open(){
  FILE* fp = fopen("something.txt", "r"); 
  bool res = is_open(fp); 
  cout << (res ? "opned" :"closed") << endl; 
}
void check_ptr(int* ptr){
  if(ptr != nullptr){
    cout << *ptr << endl; 
  }else{
    cout << "cant dereference the nullptr" << endl; 
  }
}
void check_ptr1(int* ptr1){
  if(ptr1){
    cout << *ptr1 << endl; 
  }else{
    cout << "cant dereference nullptr" << endl; 
  }
}
void ASCII(){
  for(char ch; cin >> ch;){
    cout << static_cast<int>(ch) << " "; 
    if(ch == 'z'){break;}
  }
  for(char a = 'A'; a < 'Z'; a++){cout << a << endl;}
  for(int i = 0; i <= 25; i++){cout << static_cast<char>('A' + i) << " ";}
  cout << endl; 
}
void cant_mix_char_pointers(char ch, signed char sc, unsigned char uc){
  char* ptr = &ch; //OK 
  signed char* ptr2 = &sc; //OK 
  unsigned char* ptr3 = &uc; 
  cout << *ptr << " " << *ptr2 << " " << *ptr2; 
  //ptr = ptr2; //error cant assign char* to signed char* 
  //ptr = ptr3; //error cant assign char* to unsigned char* 
 // ptr2 = ptr; //error cant assign signed char* to char* 
  //ptr2 = ptr3; //error cant assign signed char* unsigned char* 
  //ptr3 = ptr; //error cant assiign unsinged char* to char* 
  //ptr3 = ptr2; //error cant assign unsigned char* to signed char* 
}
void mixing_char_literals(char ch, signed char sc, unsigned char uc){
  ch = 255; //implementation defiend. 
  cout << (int)ch << endl; 
  ch = sc; //OK 
  cout << (int)ch << endl; 
  sc = ch; //OK 
  cout << (int)sc << endl; 
  sc = uc; //Implementation defeind if uc is too large. 
  cout << (int)sc << endl; 
  uc = ch; //OK conversion to unsigend. 
  cout << (int)uc << endl; 
  uc = sc; //OK conversion to unsigned. 
  cout << (int)uc << endl; 
}
void char_literals(int a, int b){
  cout << a << '\a' << b << endl; 
  cout << a << '\b' << b << endl; 
  cout << a << '\f' << b << endl; 
  cout << a << '\n' << b << endl; 
  cout << a << '\r' << b << endl; 
  cout << a << '\t' << b << endl; 
  cout << a << '\v' << b << endl; 
  cout << a << '\\' << b << endl; 
  cout << a << '\?' << b << endl; 
  cout << a << '\'' << b << endl; 
  cout << a << '\"' << b << endl; 
  cout << (int)'\12' << " " << (int)'\x12' << endl; 
  const char* embed = "s\x12\12\x2g";
  for(const char* start = embed; *start != '\0'; start += 1){
    cout << (int)*start << " "; 
  }
  cout << endl; 
 // const char* utf8 = u8"files//folder"; 
  //const char* rawutf8 = u8R"***("files//folder"")***"; 
  //const char16_t* utf16 = u"files//folder";
  //const char16_t* rawutf16 = uR"files//folder"; 
  //const char32_t* utf32 = U"files//folder"; 
  //const char32_t rawutf32 = UR"***("files//folder")***"; 
  //cout << utf8 << " " << rawutf8 << endl; 
  //cout << utf16 << " " << rawutf16 << endl; 
  //cout << utf32 << " " << rawutf32 << endl; 
}
void integral_literals(){
  int plainint = 12; 
  signed int random = -12; 
  unsigned int random1 = 123; 
  cout << plainint << " " << random << " " << random1 << endl; 
  cout << std::numeric_limits<int>::is_signed << endl; 
  short int shortin = 12; 
  long int longint = std::numeric_limits<int>::max(); 
  long long int randomlonglongint = 123; 
  cout << sizeof(shortin) << " " << sizeof(longint) << " " << sizeof(randomlonglongint) << endl; 
  int octal = 012; 
  int hexa = 0xFFFF; 
  cout << octal << " " << hexa << endl; 
  int16_t hexa1 = 0xFFFF; 
  cout << (hexa == 65535) << " " << (hexa1 == ((65535 % (int)pow(2, 16) - pow(2, 16)))) << endl; 
  int_least32_t least32bitint  = std::numeric_limits<int>::max(); 
  cout << sizeof(least32bitint) << endl; 
  int_fast16_t fastest16bitint = 123; 
  cout << sizeof(fastest16bitint) << endl; 
  uint_least32_t leastunsigned32bitsint = 123; 
  cout << sizeof(leastunsigned32bitsint) << endl; 
}
void floating_point_literals(){
  float randomfloat = std::numeric_limits<float>::max() + 2; 
  double randomdouble = std::numeric_limits<float>::max() + 2; 
  long long randomlonglong = std::numeric_limits<double>::max() + 2; 
  cout << randomfloat << " " << randomdouble << " " << randomlonglong << endl; 
}
void sizes(){
  cout << "Integral Litrals" << endl; 
  cout << (sizeof(char) <= sizeof(bool) && sizeof(bool) <= sizeof(short int) && sizeof(int) <= sizeof(long) && sizeof(long) <= sizeof(long long)) << endl; 
  cout << "Arthematic Types:: " << endl; 
  cout << (sizeof(int) <= sizeof(float) && sizeof(float) <= sizeof(double) && sizeof(double) <= sizeof(long) && sizeof(long) <= sizeof(long long)) << endl; 
  cout << "Generic Types:: " << endl; 
  cout << (sizeof(char) == sizeof(signed char) && sizeof(signed char) == sizeof(unsigned char)) << endl; 
}
template<class T>
void* allocate(size_t n){
  void* q = malloc(sizeof(T) * n); 
  return q; 
}
void use_allocate(){
  void* r = allocate<int>(12); 
  cout << reinterpret_cast<int*>(r) << endl; 
  int arr[2]{1, 2}; 
  ptrdiff_t diff = ((arr + 1) - arr); 
  cout << diff << endl; 
}
struct Person{
  char a; //1 
  int b; // 1 +3 = 4 + 4 = 8 
  char c; // 8 + 1 + 3 = 12 
  int d; //16
}; 
struct Person1{
  char d; //1 
  char b;//2 + 2 
  int a;//4 + 4 
  int c; //8 + 4
}; 
struct alignas(32) Person3{
  char a; 
  char b; 
  int c; 
  int d; 
}; 
void alignments(){
  auto ac = alignof(12); 
  auto ar = alignof('a');
  int arr[2]{1, 2}; 
  auto am = alignof(arr); 
  cout << ac << " " << ar << " " << am << endl; 
  int sizes1{}, sizes2{}; 
  for(int i = 0; i < 100; i++){
    sizes1 += sizeof(Person); 
    sizes2 += sizeof(Person1); 
  }
  cout << ((sizes1 > sizes2) ? "Space wasted by" : "") << ((sizes1 > sizes2) ? to_string(sizes1 - sizes2).c_str() : "0") << "bytes"; 
  cout << sizeof(Person3) << endl; 
}
template<class T>
void user(vector<T>& v1){
  const int bufmax = 1024; 
  int alignas(T) buffer[bufmax]; 
  const int minval = min((int)v1.size(), bufmax); 
  std::uninitialized_copy(v1.begin(), v1.begin() + minval, buffer); 
  for(size_t i = 0; i < bufmax; i++){cout << buffer[i] << " "; }
  cout << endl; 
}
void use_user(){
  vector<int>v1(12, 2);
  user(v1); 
}
struct somestruct; 
struct Date; 
int function(int a);
extern int no; 
extern int no; 
// extern short int no; //error type mismatch
// struct Date; //error redeclration in the same scope. 
const double pi{3.143}; 
template<class T>
void abs(T a){return(a >0) ? a : (-1 * a); }
using Cmplx = complex<int>; 
enum class something{SOMETHING, SOMETHING_ELSE}; 
struct Insane_structure_of_declration{
  //optinal prefix specifier such as virtual, extern, const, etc. 
  //base Types
  //optional declrator with name
  //function body or intializer; 
  //option suffix specifier such as noexcept, const, etc. 
  virtual void somefunction(int a, int b) noexcept; 
}; 
void postfix_declator_bind_much_tighter_than_prefix(){
  const char* somearray[]{"sommething", "something_else"}; //array of const char* 
  const char randomarrayofconstchars[]{"something"}; 
  const char (*somearray1)[]{&randomarrayofconstchars}; //Pointer to array of const char; 
  cout << *somearray << endl; 
  cout << *somearray1 << endl;
}
void declaring_multiple_names(){
  int arr[2]{1, 2}, *ptr; 
  ptr = arr; 
  cout << *ptr << endl; 
}
void local_Scope(int x, int y){
  int local; 
  //int x; //error function have their scope extends from the outermost block of the function declration. 
  cout << local << endl; 
  auto lambda = [&](int a, int b){return(a > b);};
  vector<int>somevec{12, 13, -1, 12, 22}; 
  sort(somevec.begin(), somevec.end(), lambda); 
  for(size_t i = 0; i != somevec.size(); i++){cout << somevec[i] << " "; }
  cout << endl; 
}
class class_scope{
private: 
  int x, y; 
public: 
  class_scope(int x1 = {}, int y1 = {}): x{x1}, y{y1}{}; 
  void display(){cout << x << " " << y << endl;}
};
int global_scope; 
//namespace namespace_scope{
  //int a; 
//}
namespace namespacescope_1{
#ifdef namespace_error
  void randomval(){cout << a << endl;} //error a not accessible within the given namespace; 
#endif
}
void use_class_scope(){
  class_scope c1{12, 13}; 
  //cout << c1.x << " " << c1.y << endl; //error x and y only accessible within the class scope. 
  c1.display(); 
}
int xvalues = 12; 
void shadowing(){
  int xvalues = 14; 
  cout << "using local declration:: " << xvalues << endl; 
  {
    int xvalues = 15; 
    cout << "using locally hidden declration:: " << xvalues << endl; 
  }
  cout << xvalues << endl; 
  int someval = someval; 
  cout << someval << endl; //A good compiler should rant when an object is used before being intialized. 
}
complex<int> someval(int a, int b){
  complex<int>res{a, b}; 
  return res; 
}
void initializations(){
  int a = 12; //direct intialization allows narrowing
  int randomval{12}; //list-intialization doesn't allow narrowing
  int someval(12); //function based or constructor based intialization can be confused with such overloaded function taking same arguments of the type of the the identifier. 
  complex<int>somevals{12, 13}; 
  vector<int>randomvec(99); //allows constructor based alternatives for intialization; 
 // vector<string>s1("Hello", 12);//error no instance of constructor taking in a string and int as argument found for vector<string>; 
}
class default_values{
  int x; string s; 
public: 
  default_values(int x1 = {}, string s1 = {"Empty string"}): x{x1}, s{s1}{}; 
  void use_defaults(){cout << x  << " " << s << endl;}
}; 
void missing_intializers(){
  static int randomstatic; 
  cout << randomstatic << endl; 
  int a; 
  cout << a << endl; //undefined values; 
  int* ptr = new int; //undefined values; 
  cout << *ptr << endl; 
  int a1{}; //default intialized to the most suitable representation of 0 ;
  cout << a1 << endl; 
  int* ptr1 = new int{}; 
  cout << *ptr1 << endl; 
  const char* ptr2 = new char; 
  const char* ptr3 = new char{}; 
  cout << ptr2 << " " << ptr3 << endl; 
  delete ptr1; delete ptr2; delete ptr3; 
  default_values d1; 
  d1.use_defaults(); 
}
void statement_scope(){
  for(int i= 0; i < 12; i++){cout << i << endl;}
  vector<int>somevec(12, 2); 
  for(size_t i = 0; i < somevec.size(); i++){cout << somevec[i] << " "; }
  std::initializer_list<int>rlist{1, 2, 3, 4}; 
  for(auto& i: rlist){cout << i << " "; }
  cout << endl; 
}
void auto_type_specifiers(){
  auto ac = 12; 
  cout << typeid(ac).name() << endl; 
  auto ar = "something"; 
  cout << typeid(ar).name() << endl; 
  auto am = 'c'; 
  cout << typeid(am).name() << endl; 
  vector<int>somevec{1, 2, 3, 4}; 
  for(vector<int>::iterator it1 = somevec.begin(); it1 != somevec.end(); it1++){cout << *it1 << endl;}
  for(auto& i: somevec){cout << i << " "; }
  cout << endl; 
  vector<vector<int>>randomvector{{1, 2}, {2, 2, 23, 4}, {1, 2, 3, 4}}; 
  for(size_t i = 0; i < randomvector.size(); i++){
    for(size_t j = 0; j < randomvector[i].size(); j++){
      cout << randomvector[i][j] << " ";  
    }
    cout << endl; 
  }

  for(auto& i: randomvector){
    for(auto& j: i){cout << j << " "; }
    cout << endl; 
  }
  int somecheck = 12; 
  int& somevaluescheck = somecheck; 
  auto &rcheck = somecheck; 
  auto a1check = somevaluescheck; //The type of an expression is never a reference cause reference are never implicity dereferenced in an expression. 
  cout << typeid(rcheck).name() << endl; 
  for(const auto& a: randomvector){
    for(const auto& a2: a){cout << a2 << " "; }
    cout << endl; 
  }
  auto somevalues{12}; 
  cout << typeid(somevalues).name() << endl; //not int but intializer_list<int>; //always use auto with direct intialization. 
  //auto x3{1, 2, 3}; 
 // auto randomxvalues{1, 2, 3, 4, 2.2}; //error cant deduce types.  
}
template<class U, class V>
auto mul(vector<U>& v1, vector<V>& v2)->vector<decltype(U{} + V{})>{
  vector<decltype(U{} + V{})>res; 
  assert(v1.size() == v2.size()); 
  for(size_t i = 0; i < v1.size(); i++){
    res.push_back(v1[i] * v2[i]); 
  }
  return res; 
}
void use_mul(){
  vector<int>v1{1, 2, 3, 4}; 
  vector<double>v2{2.2, 3.2, 2.32, 3.23}; 
  auto res = mul(v1, v2); 
  for(size_t i = 0; i < res.size(); i++){cout << typeid(res[i]).name() << endl;}
}
template<class T>
void type_aliases(){
  //using int32_t = int; //insulating the implementation details from the code; 
  vector<int>v1{1, 2, 3, 4, 5}; 
  using veciterator = vector<int>::iterator; 
  for(veciterator it = v1.begin(); it != v1.end(); it++){cout << *it << endl;}
  using PTOF = bool(*)(int, int); //Pointer to function taking int and int arguments and return a bool. 
  using Pchar = char*;  
  Pchar p1 =nullptr; //reffer to char* | for good or bad type aliases reffer to the type for which they have been declared as alias rather than differnt type. 
  using templatevalue = T;  //using template aliases. 
  templatevalue res = T{}; 
  cout << res << endl; 
  using lvalref = int&; 
  using rlavlref = lvalref&; //refernce to reference can only be created with type alises. 
  //unsigned Pchar c1 = 'c'; //error cant apply type specifier to a type alias. 
}
int main(){
  implementation_Defined(); 
  unspecified(); 
  check_assumptions(); 
  #ifdef check_undefined
  undefined_behavior(); 
  #endif
  Booleans(); 
  use_is_open(); 
  check_ptr(nullptr);
  check_ptr1(nullptr); 
  char_literals(12, 13); 
  cant_mix_char_pointers('a', 12, 255); 
  mixing_char_literals('a', 2, 'c'); 
  ASCII(); 
  sizes(); 
  use_allocate(); 
  alignments(); 
  use_user(); 
  postfix_declator_bind_much_tighter_than_prefix(); 
  declaring_multiple_names(); 
  local_Scope(12, 13); 
  use_class_scope(); 
  initializations(); 
  missing_intializers();
  auto_type_specifiers(); 
  use_mul(); 
  type_aliases<int>(); 
  return 0; 
}
