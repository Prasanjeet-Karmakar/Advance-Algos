#include<bits/stdc++.h>
using namespace std;

vector<int> manacherOdd(string s) {
  int n = s.size();
  s = "$" + s + "^";
  vector<int> p(n + 2);
  int l = 1, r = 1;
  for (int i = 1; i <= n; ++i) {
    p[i] = max(0, min(r - i, p[l + (r - i)]));
    while (s[i - p[i]] == s[i + p[i]]) p[i]++;

    if (i + p[i] > r) {
      l = i - p[i], r = i + p[i];
    }
  }

  return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacherEven(string s) {
  string t;
  for (char c : s) {
    t += string("#") + c;
  }
  auto res = manacherOdd(t + "#");
  return vector<int>(begin(res) + 1, end(res) - 1);
}

int main() {
  string s;
  cin >> s;

  vector<int> dOdd = manacherOdd(s); // representing palindromes of odd length.
  for (int i = 0; i < dOdd.size(); ++i) cout << dOdd[i] << " ";
  cout << endl;
  // for even length palindromes, rather than solving for the edges cases of even length,
  // which will increase the complexity, we simply add a special character in between 
  // each of the characters and apply the manacher's odd algo.
  string t;
  cin >> t;
  vector<int> even = manacherEven(t);

  // d[2i] = 2d_even[i] + 1 and d[2i+1] = 2d_odd[i]
  // where d denotes the Manacher array for odd length palindrome in #-joined string
  // while d_odd and d_even correpond to the arrays defined.
  for (int i = 0; i < even.size(); i++) cout << even[i] << " ";
  return 0;
}