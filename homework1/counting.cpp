#include"common.h"

/* counting sort for big integer and return wall clock time */
long countingSort(){
  clock_t st, et;
  long total_time;
  st = clock();
  vector<__int128> CS_array(int_array.size());
  vector<__int128> count(max_value + 1);
  for(int i = 0; i < int_array.size(); i++) count[int_array[i]]++;
  for(__int128 i = 1; i <= max_value; i++) count[i] += count[i - 1];
  for(int i = int_array.size() - 1; i >= 0; i--) {
    CS_array[count[int_array[i]] - 1] = int_array[i];
    count[int_array[i]]--;
  }
  for(int i = 0; i < int_array.size(); i++) int_array[i] = CS_array[i];
  et = clock();
  total_time = (long)(et - st);
  return total_time;
}

int main(){
  long ttime;
  getInput();
  ttime = countingSort();
  printArray(true);
  timeOutput(ttime);
}