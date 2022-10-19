#include<iostream>
#include<vector>
#include<string>
#include<ctime>

using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::min;

//for using save the input integer
vector<__int128> int_array;
//for couting sort using on __int128
__int128 max_value = 0;
unsigned long long compare_count = 0;

/*__int128 type output overload*/
std::ostream& operator<<(std::ostream& out, __int128 n){
  string str;
  if(n == 0) return out << 0;
  while(n != 0){
    int temp = n % 10;
    str = std::to_string(temp) + str;
    n = (n - temp) / 10;
  }
  return out << str;
}

/* type change string to __int128 */
__int128 sto128(string str){
  __int128 n = 0;
  for(int i = 0; i < str.size(); i++){
    char v = str[i];
    n = (10 * n) + (v - '0');
  }
  return n;
}

/* get input and saving to int_array */
void getInput(){
  __int128 temp;
  while(true){
    string str = "null";
    cin >> str;
    if(str == "null") break;
    temp = sto128(str);
    if(temp > max_value) max_value = temp;
    int_array.push_back(temp);
  }
}

/* output sorted array */
void printArray(bool on){
  if(on)
    for (vector<__int128>::iterator iter = int_array.begin(); iter != int_array.end(); iter++) cout << *iter << endl;
  else return;
}


/* output wall clock time in ms, s, m */
void timeOutput(long t){
  if(t < CLOCKS_PER_SEC * 10) cout << t << "ms" << endl;
  else if(t >= CLOCKS_PER_SEC * 10 && t < CLOCKS_PER_SEC * 60) 
    cout << double(t) / CLOCKS_PER_SEC << "s" << endl;
  else cout << double(t) / (CLOCKS_PER_SEC * 60) << "m" << endl;
}
