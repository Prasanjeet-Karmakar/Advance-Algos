#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M 1000000007
ll mini = 1e9 + 1e8;

void build(int i, int lvl, int low, int high, vector<int>& v, vector<int>& seg) {
    if (low == high) {
        seg[i] = v[low];
        return;
    }

    int mid = low + (high - low) / 2;
    build(2 * i + 1, lvl - 1, low, mid, v, seg);
    build(2 * i + 2, lvl - 1, mid + 1, high, v, seg);
    if (lvl & 1) seg[i] = seg[2 * i + 1] | seg[2 * i + 2];
    else seg[i] = seg[2 * i + 1] ^ seg[2 * i + 2];
}

void update(int i, int lvl, int low, int high, int ind, int val, vector<int>& seg) {
    if (low == high) {
        seg[i] = val;
        return;
    }

    int mid = low + (high - low) / 2;
    if (ind <= mid) update(2 * i + 1, lvl - 1, low, mid, ind, val, seg);
    else update(2 * i + 2, lvl - 1, mid + 1, high, ind, val, seg);
    if (lvl & 1) seg[i] = seg[2 * i + 1] | seg[2 * i + 2];
    else seg[i] = seg[2 * i + 1] ^ seg[2 * i + 2];
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> v(pow(2, n));
    for (int i = 0; i < pow(2, n); ++i) cin >> v[i];
    vector<int> seg(4 * pow(2, n));
    build(0, n, 0, (1 << n) - 1, v, seg);
    for (int i = 0; i < m; ++i) {
        int ind, val;
        cin >> ind >> val;
        update(0, n, 0, (1 << n) - 1, ind - 1, val, seg);
        cout << seg[0] << endl;
    }
}

int main() {
    solve();
    return 0;
}