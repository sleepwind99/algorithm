#include"common.h"

/* insertion sort and return wall clock time */
long insertionSort(){
  clock_t st, et;
  long total_time;
  st = clock();
  vector<__int128>::iterator i, j;
  __int128 key;
  for(i = int_array.begin() + 1; i != int_array.end(); i++){
    key = *i;
    for(j = i - 1; j >= int_array.begin() && *j > key; j--){
      *(j + 1) = *j;
      compare_count++;
    }
    *(j + 1) = key;
  }
  et = clock();
  total_time = (long)(et - st);
  return total_time;
}

int main(){
  long ttime;
  getInput();
  ttime = insertionSort();
  printArray(true);
  timeOutput(ttime);
  cout << compare_count << endl;
}