#include"common.h"

/* quick sort for recursive call */
void quickSort(int start, int end){
	if(start >= end) return;
	__int128 pivot = int_array[start];
	int left = start;
	int right = end;
  while(left <= right){
    while(int_array[left] < pivot){
      compare_count++;
      left++;
    }
    while(int_array[right] > pivot){
      compare_count++;
      right--;
    }
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

int main(){
  long ttime;
  getInput();
  ttime = quickSort();
  printArray(true);
  timeOutput(ttime);
  cout << compare_count << endl;
}