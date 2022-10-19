#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main()
{
  string s1, s2;
  int *dp, *dpminus;

  //read string 
  cin >> s1;
  cin >> s2;
  
  //extending strings for botton-up algorithm
  s1 = "0" + s1;
  s2 = "0" + s2;

  //assign short and long string lengths
  int shortLen = s1.length() <= s2.length() ? s1.length() : s2.length();
  int longLen = s1.length() > s2.length() ? s1.length() : s2.length();

  //array for dynamic programming
  dp = new int[shortLen];
  //temporary array storing i-1 in the dp array
  dpminus = new int[shortLen];

  //array initial
  for(int i = 0; i < shortLen; i++) dpminus[i] = 0;
  dp[0] = 0;

  for (int i = 1; i < longLen; i++){
    for (int j = 1; j < shortLen; j++){
      if(s1[i] == s2[j]) dp[j] = dpminus[j-1] + 1;
      else dp[j] = max(dpminus[j], dp[j-1]);
    }
    for(int j = 1; j < shortLen; j++) dpminus[j] = dp[j];
  }
  cout << dp[shortLen - 1] << endl;
  return 0;
}

