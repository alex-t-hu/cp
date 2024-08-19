// generic segment tree for sums, when it is compressed into the array

#include <bits/stdc++.h>
using namespace std;

#define MAXSEG 30000
int N;
int a[MAXSEG];

// set element i to x
void update(int i, int x, int lo = 0, int hi = -1, int node = 0) {
    if (hi == -1) hi = N - 1;
    if (lo == hi) {
        a[node] = x;
        return;
    }
    int mid = (lo + hi) / 2;
    update(i, x, lo, mid, 2 * node + 1);
    update(i, x, mid + 1, hi, 2 * node + 2);
    a[node] = a[2 * node + 1] + a[2 * node + 2];
}

// get sum from [l, r]
int query(int l, int r, int lo = 0, int hi = -1, int node = 0) {
    if (hi == -1) hi = N - 1;
    if (l > hi || r < lo) return 0;
    if (l <= lo && hi <= r) return a[node];
    int mid = (lo + hi) / 2;
    return query(l, r, lo, mid, 2 * node + 1) + query(l, r, mid + 1, hi, 2 * node + 2);
}