// Implementation of segment trees for min query problems.
// Can be tweaked for all types of segment trees problems -> min, max, sum

#include <bits/stdc++.h>
using namespace std;

// Building the segment tree -> T.C = O(n) since we are not exploring all the depths every time.
// The max size of segment tree that will suffice the entire build is found out to be 4*n. It has a big mathematical proof.
void build(int ind, int low, int high, int arr[], int seg[]) {
    if (low == high) {
        seg[ind] = arr[low];
        return;
    }

    int mid = low + (high - low) / 2;
    build(2 * ind + 1, low, mid, arr, seg);
    build(2 * ind + 2, mid + 1, high, arr, seg);
    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
}

// 3 Cases :
// No overlap -> (low > r) or (high < l) we simply return INT_MAX or INT_MIN or 0 according to the type of query.
// Complete overlap -> (l <= low && high <= r) return seg[ind]
// Partial Overlap -> (low < l && r < high) solve both left and right and return according to the type of query.
int query(int ind, int low, int high, int l, int r, int seg[]) {
    // No overlap.
    if (low > r || high < l) return INT_MAX; // min range query.
    // Complete overlap.
    if (l <= low && high <= r) return seg[ind];
    // Partial overlap.
    else {
        int mid = low + (high - low) / 2;
        int left = query(2 * ind + 1, low, mid, l, r, seg);
        int right = query(2 * ind + 2, mid + 1, high, l, r, seg);

        return min(left, right);
    }
}

// For point update, when we update the value at a particular index and no we need to update the seg tree accordingly.
void update(int ind, int low, int high, int i, int val, int seg[]) {
    if (low == high) {
        seg[ind] = val;
        return;
    }

    int mid = low + (high - low) / 2;
    if (i <= mid) update(2 * ind + 1, low, mid, i, val, seg);
    else update(2 * ind + 2, mid + 1, high, i, val, seg);

    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
}

void solve() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i) cin >> arr[i];
    int seg[4 * n];
    build(0, 0, n - 1, arr, seg);
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n - 1, l, r, seg) << endl;
        }
        else {
            int ind, val;
            cin >> ind >> val;
            update(0, 0, n - 1, ind, val, seg);
            arr[ind] = val;
        }
    }
}

int main() {
    solve();
    return 0;
}