/* LOGIC BEHIND LAZY PROPOGATION*/

// Update the node when you visit it.
// Once you update, propogate the update downwards.
// There will be a corresponding lazy nodes for each nodes in a segment tree with initial value being 0.

// Rules for range updates:
// Traverse in seg tree and update prev remaining updates and check:
//   1. if the node completely overlap:
//          update the node, lazy propogate down and return.
//   2. if partially overlaps:
//          traverse left and right and node = left + right
//   3. no overlap:
//          return


// Template for sum range queries:
#include <bits/stdc++.h>
using namespace std;

void build(int ind, int low, int high, vector<int>& v, pair<int, int> seg[]) {
    if (low == high) {
        seg[ind] = { v[low], 0 };
        return;
    }

    int mid = low + (high - low) / 2;
    build(2 * ind + 1, low, mid, v, seg);
    build(2 * ind + 2, mid + 1, high, v, seg);
    seg[ind] = { seg[2 * ind + 1].first + seg[2 * ind + 2].first, 0 };
}

void update(int ind, int low, int high, int l, int r, int val, pair<int, int> seg[]) {
    // First thing we always do is update the pending updates and propogate downwards
    if (seg[ind].second != 0) {
        seg[ind].first += (high - low + 1) * seg[ind].second;
        if (low != high) {
            seg[2 * ind + 1].second += seg[ind].second;
            seg[2 * ind + 2].second += seg[ind].second;
        }
        seg[ind].second = 0;
    }

    // Check for overlaps:
    // 1. Complete overlap -> update the node and propogate downwards.
    // 2. Partial overlap -> traverse left and right and left + right.
    // 3. No overlap -> return

    // Complete overlap
    if (l <= low && high <= r) {
        seg[ind].first += (high - low + 1) * val;
        if (low != high) {
            seg[2 * ind + 1].second += val;
            seg[2 * ind + 2].first += val;
        }
    }
    // No overlap
    else if (l > high || r < low) return;
    // Partial overlap
    else {
        int mid = low + (high - low) / 2;
        update(2 * ind + 1, low, mid, l, r, val, seg);
        update(2 * ind + 2, mid + 1, high, l, r, val, seg);
        seg[ind] = { seg[2 * ind + 1].first + seg[2 * ind + 2].first, seg[ind].second };
    }
}

int query(int ind, int low, int high, int l, int r, pair<int, int> seg[]) {
    // Similar to update function, first update the pending updates:
    if (seg[ind].second != 0) {
        seg[ind].first += (high - low + 1) * seg[ind].second;
        if (low != high) {
            seg[2 * ind + 1].second += seg[ind].second;
            seg[2 * ind + 2].second += seg[ind].second;
        }
        seg[ind].second = 0;
    }

    // Similar to the normal segment tree query.
    // Complete overlap:
    if (l <= low && high <= r) return seg[ind].first;
    // No overlap:
    else if (r < low || high < l) return 0;
    // Partial overlap:
    else {
        int mid = low + (high - low) / 2;
        int left = query(2 * ind + 1, low, mid, l, r, seg);
        int right = query(2 * ind + 2, mid + 1, high, l, r, seg);
        return left + right;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    pair<int, int> seg[4 * n];

    build(0, 0, n - 1, v, seg);
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
            int l, r, val;
            cin >> l >> r >> val;
            update(0, 0, n - 1, l, r, val, seg);
        }
    }
}

int main() {
    solve();
    return 0;
}