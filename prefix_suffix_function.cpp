// https://codeforces.com/problemset/problem/432/D

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
int z[MAXN], p[MAXN], c[MAXN];

void z_function (string& s) {
    z[0] = s.size();
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); i++) {
        int k = i + max(0, min (r - i, z[i - l]));
        while (k < s.size() && s[k] == s[k - i]) k++;
        z[i] = k - i;
        if (k > r) {
            r = k;
            l = i;
        }
    }
}

void kmp (string& s) {
    p[0] = 0;
    for (int i = 1; i < s.size(); i++) {
        int k = p[i - 1];
        while (k > 0 && s[k] != s[i]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            k++;
        }
        p[i] = k;
    }
}

int main () {
    string s; cin >> s;

    kmp(s);
    z_function(s);

    set<pair<int, int>> st;
    for (int i = 0; i < s.size(); i++) {
        c[z[i]]++;
    }
    
    for (int i = s.size() - 1; i >= 0; i--) {
        c[i] += c[i + 1];
    }

    vector<pair<int, int>> v;
    int largest_prefix_suffix = p[s.size() - 1];
    v.push_back({largest_prefix_suffix, c[largest_prefix_suffix]});
    for (int i = 1; i < largest_prefix_suffix; i++) {
        if (i + z[i] >= largest_prefix_suffix) {
            int l = largest_prefix_suffix - i;
            v.push_back({l, c[l]});
        }
    }
    v.push_back({s.size(), 1});

    sort(v.begin(), v.end());

    cout << v.size() << "\n";
    for (auto x : v) {
        cout << x.first << " " << x.second << "\n";
    }
}