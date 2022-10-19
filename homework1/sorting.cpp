#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<ctime>
#include<cstdlib>
#include<stdio.h>

using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::min;

//for using save the input integer
vector<__int128> int_array;
//for merge sort
vector<__int128> MS_array;
//for couting sort using on __int128
__int128 max_value = 0;
vector<__int128> tim_left;
vector<__int128> tim_right;

/*__int128 type output overload*/
std::ostream& operator<<(std::ostream& out, __int128 n) {
  string str;
  if(n == 0) return out << 0;
  while(n != 0){
    int temp = n % 10;
    str = std::to_string(temp) + str;
    n = (n - temp) / 10;
  }
  return out << str;
}

/* type change __int128 to string */
string __128tos(__int128 n){
  string str;
  if(n == 0) return std::to_string(0);
  while(n != 0){
    int temp = n % 10;
    str = std::to_string(temp) + str;
    n = (n - temp) / 10;
  }
  return str;
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

/* insertion sort and return wall clock time */
long insertionSort(){
  clock_t st, et;
  long total_time;
  st = clock();
  vector<__int128>::iterator i, j;
  __int128 key;
  for(i = int_array.begin() + 1; i != int_array.end(); i++){
    key = *i;
    for(j = i - 1; j >= int_array.begin() && *j > key; j--) *(j + 1) = *j;
    *(j + 1) = key;
  }
  et = clock();
  total_time = (long)(et - st);
  return total_time;
}

/* quick sort for recursive call */
void quickSort(int start, int end){
  srand(time(NULL));
	if(start >= end) return;
  //pivot is randomly choose.
	__int128 pivot = int_array[rand() % (end - start + 1) + start];
	int left = start;
	int right = end;
  while(left <= right){
    while(int_array[left] < pivot) left++;
    while(int_array[right] > pivot) right--;
    if(left <= right) {
      __int128 temp = int_array[left];
      int_array[left++] = int_array[right];
      int_array[right--] = temp;
    }
  }
  //recursive call
	quickSort(start, right);
	quickSort(left, end);
}

/* random pivot quick sort and return wall clock time */
long quickSort(){
  clock_t st, et;
  long total_time;
  st = clock();
  quickSort(0, int_array.size() - 1);
  et = clock();
  total_time = (long)(et - st);
  return total_time;
}

/* merge array */ 
void merge(int left, int right){
  //half of array index
  int half = (left + right) / 2;
  int l = left;
  int r = half + 1;
  //index of int_array
  int k = left;

  while(l <= half && r <= right)
    MS_array[k++] = int_array[l] <= int_array[r] ? int_array[l++] : int_array[r++];

  if(l > half)
    for(int i = r; i <= right; i++)MS_array[k++] = int_array[i];
  else
    for(int i = l; i <= half; i++)MS_array[k++] = int_array[i];
  //duplicate array
  for(int i = left; i <= right; i++)int_array[i] = MS_array[i];
}

/* merge sort for recursive call */
void merge_sort(int left, int right){
  if(left < right){
    int half = (left + right) / 2;
    merge_sort(left, half);
    merge_sort(half + 1, right);
    merge(left, right);
  }
}

/* merge sort and return wall clock time */
long mergeSort(){
  clock_t st, et;
  long total_time;
  st = clock();
  MS_array.resize(int_array.size());
  merge_sort(0, int_array.size() - 1);
  et = clock();
  total_time = (long)(et - st);
  return total_time;
}

/* counting sort for big integer and return wall clock time */
long countingSort(){
  clock_t st, et;
  long total_time;
  st = clock();
  vector<__int128> CS_array(int_array.size());
  vector<__int128> count(max_value + 1);
  for(int i = 0; i < int_array.size(); i++) count[int_array[i]]++;
  for(__int128 i = 1; i <= max_value; i++) count[i] += count[i - 1];
  for(int i = int_array.size() ; i >= 1; i--) {
    CS_array[count[int_array[i]]] = int_array[i];
    count[int_array[i]]--;
  }
  for(int i = 0; i < int_array.size(); i++) int_array[i] = CS_array[i];
  et = clock();
  total_time = (long)(et - st);
  return total_time;
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

void countingSort(__int128 dn = 1, int normdigit = 10){
  vector<__int128> CS_array(int_array.size());
  int count[normdigit] = { 0 };
  for (int i = 0; i < int_array.size(); i++) count[(int_array[i] / dn) % normdigit]++;
  for (int i = 1; i < normdigit; i++) count[i] += count[i - 1];
  for (int i = int_array.size(); i >= 1; i--) {
    CS_array[count[(int_array[i] / dn) % normdigit]] = int_array[i];
    count[(int_array[i] / dn) % normdigit]--;
  }
  for (int i = 0; i < int_array.size(); i++) int_array[i] = CS_array[i];
}

long radixWithCount(int normdigit = 10){
  clock_t st, et;
  long total_time;
  st = clock();
  for (__int128 dn = 1; max_value / dn > 0; dn *= normdigit) countingSort(dn, normdigit);
  et = clock();
  total_time = (long)(et - st);
  return total_time;
}


int main(){
  long ttime;
  getInput();
  ttime = quickSort();
  //ttime = mergeSort();
  //ttime = countingSort();
  //ttime = radixWithCount();
  //ttime = insertionSort();
  printArray(true);
  timeOutput(ttime);
}