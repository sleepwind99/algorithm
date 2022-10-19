#include "common.h"

/* merge sorted arrays */
void merge(int start, int half, int end) {
  int capa1 = half - start + 1;
  int capa2 = end - half;
  __int128 left[capa1], right[capa2];

  for (int i = 0; i < capa1; i++) left[i] = int_array[start + i];
  for (int i = 0; i < capa2; i++) right[i] = int_array[half + 1 + i];

  // left array index
  int i = 0;
  // right array index
  int j = 0;
  // int array index
  int k = start;

  while (i < capa1 && j < capa2) {
    int_array[k++] = left[i] <= right[j] ? left[i++] : right[j++];
    compare_count++;
  }

  while (i < capa1) int_array[k++] = left[i++];
  while (j < capa2) int_array[k++] = right[j++];
}

/* the insertion sort of the array from start index to end index */
void insertionSort(int start, int end, __int128 dn) {
  for (int i = start + 1; i <= end; i++) {
    __int128 temp = int_array[i];
    int j = i - 1;
    while (j >= start && (int_array[j] / dn) % 10 > (temp / dn) % 10) {
      int_array[j-- + 1] = int_array[j];
      compare_count++;
    }
    int_array[j + 1] = temp;
  }
}

/* tim sort with chunk size 32 */
void timSort(__int128 dn) {
  for (unsigned long long i = 0; i < int_array.size(); i += 32)
    insertionSort(i, min((i + 31), (int_array.size() - 1)), dn);
  for (int chunk = 32; chunk < int_array.size(); chunk = 2 * chunk) {
    for (unsigned long long start = 0; start < int_array.size(); start += 2 * chunk) {
      int half = start + chunk - 1;
      int end = min((start + 2 * chunk - 1), (int_array.size() - 1));
      if (half < end) merge(start, half, end);
    }
  }
}

/* radx with counting sort and default r is 10 */
long radixWithTim() {
  clock_t st, et;
  long total_time;
  st = clock();
  for (__int128 dn = 1; max_value / dn > 0; dn *= 10) timSort(dn);
  et = clock();
  total_time = (long)(et - st);
  return total_time;
}

int main() {
  long ttime;
  getInput();
  ttime = radixWithTim();
  printArray(true);
  timeOutput(ttime);
  cout << compare_count << endl;
}