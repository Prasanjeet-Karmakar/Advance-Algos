// Z-Algorithm is used for string matching algorithm.
// It consists of z-array which returns the longest substring that from i index which is equal to prefix of the the string of same size.
// It will take O(n^2) when using trivial approach:
/*
    vector<int> z(n);
    for(int i=1 : n) {
        while(i+z[i] < n && str[z[i]] == str[z[i] + i]) z[i]++;
    }
*/

// But it can be optimised using mathematical terms:
// Lets take a range [l,r] => represents the rightmost range which has already been computed.
// So if my i is between l and r we dont need to recompute the z[i] using trivial algo rather we use the precomputed z values.
// Else we use the trivial algo.


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> solve(string s) {
    ll n = s.size();
    vector<ll> z(n);
    ll l = 0, r = 0;

    for (ll i = 1; i < n; ++i) {
        if (i > r) {
            l = r = i;
            while (r < n && s[r] == s[r - l]) r++;
            z[i] = r - l;
            r--;
        }
        else {
            if (i + z[i - l] <= r) z[i] = z[i - l];
            else {
                l = i;
                while (r < n && s[r] == s[r - l]) r++;
                z[i] = r - l;
                r--;
            }
        }
    }

    return z;
}

int main() {
    string s;
    cin >> s;
    vector<ll> v = solve(s);
    for (ll& i : v) cout << i << " ";
    return 0;
}