#include<iostream>
#include<string>
#include<math.h>

using namespace std;

int main()
{
  string s1, s2;
  int *a, *b;
  cin >> s1;
  cin >> s2;

  int len1 = s1.length();
  int len2 = s2.length();
  int shortLen = len1 <= len2 ? len1 : len2;
  int longLen = len1 > len2 ? len1 : len2;

  a = new int[shortLen];
  b = new int[shortLen];

  for (int i = longLen; i >= 0; i--) {
    for (int j = shortLen; j >= 0; j--) {
      if (s1[i] == s2[j]) a[j] = 1 + b[j+1];
      else a[j] = max(b[j], a[j+1]);
    }
  }
}
