#include<iostream>
#include<vector>
#include<iterator>
#include<cstring>
using namespace std;
/**
 * declration, 
 * expression-list
 *  {statement list}
 *  function
 *  try {statement-list} handler list
 *  case const expression : statement
 *  default: statement
 *  break; 
 *  continue; 
 *  goto identifer: statement list
 *  selection statement: 
 *  if(condition) statement
 *  else statement
 *  switch(condition) statement
 *  Iterative statement
 *  for(for init statement condition; expression list) stement list
 *  do{statement-list} while(expression); 
 *  while(expression) statement-list
 *  for(intit declration: statemtn) statemt
**/
void statement_are_used_to_determine_order_of_declrations(int a, int b, int c){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  a = b + c; 
  if(a){
    cout << (b + c) << endl; 
  }
}
void compound_statement(){}; //{} by iteself is a statement often reffers to as the empty or the compound statement. 
struct Buffer_overflow{
  const char* somestring;
  Buffer_overflow(const string& s1): somestring{s1.c_str()}{}; 
  virtual void what(){
    cerr << somestring << "(" << __LINE__ << ")" << endl; 
  }
}; 
void declration_as_a_statemtn(vector<string>& v1, int i, char* somestring){
  //The reason for providing declration as the statement or in other words, to allow intialization to be used as a statement is to prevent errors that would otherwise arise owing to unitializerd variables and to enable single assignment style of the programming where the value of an identfier is not changed after intialization, such as while using consts. 
  if(somestring == nullptr){
    return; 
  }
  if(i < 0 || i > v1.size()){
    throw Buffer_overflow{"Buffer Overlfow"}; 
  }
  if(somestring == v1[i].c_str()){
    cout << "Equals" << endl; 
  }
}
void use_declration_as_statement(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  vector<string>random{"something", "Something_else"}; 
  char somestring[] = "Something_else"; 
  declration_as_a_statemtn(random, 2, nullptr); 
  try{
    declration_as_a_statemtn(random, 3, somestring); 
  }catch(Buffer_overflow& b1){b1.what();}
  declration_as_a_statemtn(random, 1, somestring); 
}
string randomstring(int gensize){
  string s; 
  for(size_t i = 0; i < gensize; i++){
    s += to_string((int)rand()); 
  }
  return s; 
}
void user_defined_types_with_direct_intialization_with_an_intilier_can_lead_to_better_performance(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  string gen_string = randomstring(1000); 
  float start_time = clock(); 
  string s1; 
  s1 =  gen_string; 
  float endTime = clock(); 
  cout << ((endTime - start_time)/100) << endl; 
  start_time = 0; 
  endTime = 0;
  start_time = clock();
  string random_strings{gen_string}; 
  endTime = clock(); 
  cout << ((endTime - start_time)/100) << endl; 
}
void using_statement_to_give_intializer_a_desired_values(){
  constexpr int maxval = 1024; 
  int buff[maxval]; 
  int count{}; 
  for(int i; cin >> i;){
    if((i < 0) || (i > maxval)){
      throw Buffer_overflow{"Buffer Overflow"}; 
    }
    buff[count++] = i; 
  }
}
void use_statement_to_give_intializer_a_desired_values(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  try{
    using_statement_to_give_intializer_a_desired_values(); 
  }catch(Buffer_overflow& b1){
    b1.what(); 
  }
}
void selection_statements_if(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  int somepredicate = 12; 
  if((bool)(somepredicate != 0)){
    cout << "silly way converting the predicate to an equivalent logical value" << endl; 
  }
  if(somepredicate){
    cout << "implicitly converts the integral value to its equivalent boolean value " << endl; 
  }else{
    cout << "executes this control flow if the if predicate is not true:: " << endl; 
  }
  if(somepredicate){
    int x = 12; //introduce x in the scope of if branch. 
    ++x; 
    cout << x << endl; 
  }else{
    #ifdef erros
    cout << x << endl; //error x not declared in the given scope. 
    #endif
  }
  enum someval{INT, STR}; 
  enum class someval1{INT, STR}; 
  if(INT){ //OK implict conversion to int and then boolean
    cout << INT << endl; 
  }
  #ifdef somerros
  if(someval1::INT){
    cout << static_cast<int>(someval1::INT) << endl; //error doesnt implicitly converts to integral value. 
  }
  #endif
  #ifdef sommerrors
  if(somepredicate) int x = 12; //error the branch of if statement can't be just a declration, if you need to introduce a declration enclose such statements in a {}
  #endif
  if(somepredicate){
    int x = 12; 
    cout << x << endl; 
  }
}
void action1(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
}
void action2(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
}
enum class somerandomenum{INT, STR, FLOAT}; 
void selection_statements_switch_case(somerandomenum r1){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  bool sompredicate = static_cast<int>(somerandomenum::INT);
  //check against each of the logical construct when the notion of checking the value of a constant against a set of expression is explicit. 
  if(sompredicate){
    cout << "somepredicate" << endl; 
  }
  if(sompredicate-1){
    cout << "somepredicate-1" << endl; 
  }else{
    cout << "done:: " << endl; 
  }
  switch(r1){
    case somerandomenum::INT: 
      cout << static_cast<int>(somerandomenum::INT) << endl; 
      //fall through is intentional
    case somerandomenum::STR: 
      cout << static_cast<int>(somerandomenum::STR) << endl; 
      break; 
    //Not specifying default to check against each of the enumerators. 
  }
  #ifdef errors
  switch(r1){
    case somerandomenum::INT: 
      int x = 1;
    case somerandomenum::STR: 
      x++; //error cant bypass the declration of x in the given scope introudce such declration in a blcok. 
      break; //using break to terminate a case lable, alternatively a return statement can also be used. 
    case somerandomenum::FLOAT: 
      return static_cast<int>(somerandomenum::FLOAT) << endl; 
  }
  #endif
  enum Actions{AC1, AC2}; 
  Actions r2 = Actions::AC1; 
  switch(r2){
    case AC1: //OK implicitly converts to a const integral expression.
      action1(); 
     break;
    case AC2: 
      action2(); 
      break; 
    default: 
      //used to indicate the fact that all the valid alternatives have been used or alternatively to deal with erros. 
      cerr << "Error Flase value" << endl; 
   }
}
void use_selction_statements_switch_case(){
  selection_statements_switch_case(somerandomenum::INT); 
}
bool prim(int x){
  return(x < 12) ? true: false; 
}
void declration_in_conditons(){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  if(auto d = prim(12)){
    cout << "d" << endl; 
  }else{
    cout << "It is usually best to introduce the indentifier in the smallest scope possible so as to prevent any missue of unintialized variable and to further modification of such indentiifer before its intentded use" << endl; 
    cout << "One of the greate example of doing so is to introduce an identifier in a condition statements." << endl; 
    cout << "Such identifier are declrated in the outtermost block of the given statements and the value of the statement is the value of the identifier" << endl; 
    cout << "Since they are declrared in the outtermost block of if statement they are also accessible within the else block" << endl; 
  }
}
template<class T, size_t N>
class randomarray{
public: 
  randomarray(T* elem1): elem{elem1}{}; 
  T& operator[](const int index){
    if(index < 0 || index > N){
      throw std::out_of_range{"Array index out of bound"}; 
    }
    return elem[index]; 
  }
  T* begin() {
    return &elem[0]; 
  }
  T* end(){
    return &elem[N]; 
  }
  size_t size(){
    return N; 
  }
private: 
  T* elem; 
}; 
void range_for(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  cout << "a.) Range for loops are delibrate simple construct whiich gives access to all the values within the range of a container with a begin and end:: " << endl; 
  cout << "b.) Looks for begin and end iterator pointing to the begining and the end of the container in the enclosing scope of container definition or the enclosing scope where container is defined:: " << endl; 
  cout << "c.) If not found begin and end anywhere errors out with a syntax error for not traversing in a speicifed range:: " << endl; 
  cout << "d.) For built-in sequences of fixed length such as array the begin and end are explicitly calcuated by taking the pointer to the begining and end while considering the no of elements or intializer for such sequences:: " << endl; 
  cout << "e.) For user defined types one can explicitly define a begin and end for using the consequent range for loop:: " << endl; 
  cout << "f.) Since range for loops are simple construct we cant use them to traverse multiple ranges of the same sequences at the same time such as while using double pointers, for whcih case revert back to normal iterative for loop::" << endl;   
  vector<int>begin_end_defined{1, 2, 3, 4}; 
  vector<string>randomstring{"something", "something_else"}; 
  for(auto it: begin_end_defined){
    cout << it << " "; 
  }
  cout << endl; 
  for(const auto& it: randomstring){
    cout << it << " "; 
  }
  int arr[3]{1, 2, 3}; 
  randomarray<int, 3>arr1{arr}; 
  #ifdef errors
  for(auto& it: arr2){cout << it << " "; } //error begin and end not defined for the sequence. 
  #endif
  for(auto& it: arr1){cout << it << " "; }//OK defined by the user. 
  for(auto& it: arr){cout << it << endl;}//OK implicitly determined. 
  
}
template<class T>
void swapping(T& a, T& b){
  T temp = std::move(a);  
  a = std::move(b);  
  b = temp; 
}
void for_statements(){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  cout << "a.) For loops are used to traverse more complicated range and most often find more fimilar place in earlier context:: " <<endl; 
  cout << "b.) A for loop has a loop intializer, a looping condition(usually an expression) and update loop variable each of which are explicitly provided upfront in a single line" << endl; 
  cout << "c.) continue to execute untill the termination condition is true" << endl; 
  cout << "d.) The intializer declared in for loop has its scope extends from the point of declration inside of statement to the end of the loop of which its a part:: " << endl; 
  cout << "e.) If expression that is supposed to increment/decrement the loop variable is omitted we must update it elsewhere, typically inside of the loop body" << endl; 
  cout << "f.) We can also omitt the termiation condition for which we must somehow termiante the loop preferrably inside of the loop body such as by using loop exit statements, and an incrementer declared outside of the loop body" << endl; 
  char somestring[]{"somestring"}; 
  size_t length = strlen(somestring);
  for(size_t i = 0, j = length; i < j; i++, --j){
    swapping(somestring[i], somestring[j]); 
  }
  cout << somestring << endl; 
}
char to_upper(char a){
  if(isalpha(a)){
    return static_cast<char>(a - 32); 
  }
  return a; 
}
void while_statements(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  char somestring[]{"randomstring123@!"}; 
  int length = strlen(somestring); 
  while(length != -1){
    somestring[length] = to_upper(somestring[length]); 
    length -= 1; 
  }
  cout << somestring << endl; 
}
void do_while_statements(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  cout << "Do while statement executes the given statement at least once, and then till the condition is satisfied. As usual do while statement are subtle source of error cause they assumes a statement is true at least onece, if its not:: " << endl; 
  cout << "As usually the other construct of the do while statement remain the same, and one should avoid using them in almost all of the context" << endl;
  const char* somestring = ""; 
  int length = strlen(somestring); 
  do{
    to_upper(somestring[length]); 
  }while(length--); 
  cout << somestring << endl; 
}
void loop_exits(){
  cout << __FUNCTION__ << " " << __LINE__ << endl; 
  vector<vector<int>>TwoDVec{{1, 2, 3}, {2, 4, 5}, {8, 9}}; 
  for(size_t i = 0; i < TwoDVec.size(); i++){
    for(size_t j = 0; j < TwoDVec[i].size(); j++){
      if(TwoDVec[i][j] == TwoDVec[j][i]){
        cout << "breaking at:: " << i << "," << j << endl; 
        break; //breaking out of the innermost loop only not the entirety of the loop. 
      }
      cout << i << "," << j << endl; 
    }
  }
  for(size_t i = 0; i < TwoDVec.size(); i++){
    for(size_t j = 0; j < TwoDVec[i].size(); j++){
      if(TwoDVec[i][j] == TwoDVec[j][i]){cout << "continuing at " << i << ',' << j << endl; continue;} //dont execute rest of the statements continue to the start of the outtermost loop; 
      cout << i << ',' << j << endl; 
    }
  }
}
void gotos(){
  cout << __FUNCTION__ << " " << __LINE__ << endl;
  cout << "a.) Mostly usefull to jump both in and out of block within the function in which label for such goto stataement is declared the scope of such lable is that of the function in which its being declared." << endl; 
  cout << "b.) can be used to break from the outtermost loop(without returning like a return statement) and unlike break which breaks out of the innermost loop only:: " << endl; 
  cout << "C.) Doesn't have many uses in higher level programming and mostly found use in case where the code is to be generated rather than written directly by a person for instace while using some parser generator" << endl; 
  cout << "D.) Cant jump past an intializer or into an exception handler:: " << endl; 
  #ifdef erros
  try{
    int r; 
    cout << "Enter the value of r:: " << endl; 
    cin >> r; 
    if(r == 13){throw std::runtime_error{"something is wrong"}; }
  }catch(std::runtime_error& r1){
    goto execute; 
    cerr << r1.what() << endl; 
  }
  char someval = 'A';
  switch(someval){
    case 'B':
      cout << "Something" << endl; 
    case 'A': 
      {
        goto execute; 
        int r = 123; 
      }
    default: 
      cerr << "Not found!!" << endl; 
  }
  #endif
  for(size_t i = 1; i < 1e+3; i++){
    for(size_t j = 0; j < 1e+3; j++){
      if(i == j){goto execute;}
    }
  }
  execute: for(size_t i = 0; i < 12; i++){cout << "#DONE" << " " << i << endl;} 
}
int main(){
  statement_are_used_to_determine_order_of_declrations(12, 13, 4); 
  compound_statement(); 
  use_declration_as_statement(); 
  user_defined_types_with_direct_intialization_with_an_intilier_can_lead_to_better_performance(); 
  use_statement_to_give_intializer_a_desired_values(); 
  selection_statements_if(); 
  use_selction_statements_switch_case(); 
  declration_in_conditons(); 
  range_for();
  for_statements(); 
  while_statements(); 
  do_while_statements();
  loop_exits(); 
  gotos(); 
  return 0; 
}
