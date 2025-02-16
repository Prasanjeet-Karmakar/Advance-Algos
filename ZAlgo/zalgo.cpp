#include <bits/stdc++.h>
using namespace std;

vector<int> zAlgo(string s, int n) {
  vector<int> z(s.size());
  int l = 0, r = 0;
  for (int i = 1; i < s.size(); ++i) {
    if (r < i) {
      l = r = i;
      while (r < s.size() && s[r - l] == s[r]) r++;
      z[i] = r - l;
      r--;
    }
    else {
      if (i + z[i - l] <= r) z[i] = z[i - l];
      else {
        l = i;
        while (r < s.size() && s[r] == s[r - l]) r++;
        z[i] = r - l;
        r--;
      }
    }
  }

  return z;
}

int main() {
  string s, pattern;
  cin >> s >> pattern;
  string concat = pattern + "$" + s;
  vector<int> z = zAlgo(concat, concat.size());
  for (int i = 0; i < z.size(); ++i) {
    if (z[i] == pattern.size()) cout << i - pattern.size() - 1 << " ";
  }

  return 0;
}