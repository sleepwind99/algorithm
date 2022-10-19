#include"common.h"

//extra array for merge sort 
vector<__int128> MS_array;

/* merge array */ 
void merge(int left, int right){
  //half of array index
  int half = (left + right) / 2;
  int l = left;
  int r = half + 1;
  //index of int_array
  int k = left;

  while(l <= half && r <= right){
    MS_array[k++] = int_array[l] <= int_array[r] ? int_array[l++] : int_array[r++];
    compare_count++;
  }

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
  MS_array.resize(int_array.size());
  clock_t st, et;
  long total_time;
  st = clock();
  merge_sort(0, int_array.size() - 1);
  et = clock();
  total_time = (long)(et - st);
  return total_time;
}

int main(){
  long ttime;
  getInput();
  ttime = mergeSort();
  printArray(true);
  timeOutput(ttime);
  cout << compare_count << endl;
}