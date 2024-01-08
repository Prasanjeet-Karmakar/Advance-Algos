// Sum of digits of all the numbers between a and b.
// 0 <= a <= b <= 10^9.
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll mod = 1e9 + 7;

ll dp[16][160][2];
ll solve2(int i, int sum, int isEnd, vector<int>& nums) {
    if (i == nums.size()) return sum;
    if (dp[i][sum][isEnd] != -1) return dp[i][sum][isEnd];
    int lim = isEnd ? nums[i] : 9;

    ll ans = 0;
    for (int j = 0; j <= lim; ++j) {
        ans += solve2(i + 1, sum + j, isEnd && (j == lim), nums);
    }

    return dp[i][sum][isEnd] = ans;
}

ll solve1(ll a) {
    vector<int> nums;
    ll b = a;
    while (b != 0) {
        nums.push_back(b % 10);
        b /= 10;
    }
    reverse(nums.begin(), nums.end());

    memset(dp, -1, sizeof(dp));
    return solve2(0, 0, 1, nums);
}
void solve() {
    ll a, b;
    cin >> a >> b;
    if (a == -1 && b == -1) return;

    cout << solve1(b) - solve1(a - 1) << endl;
}

int main() {
    ll t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}