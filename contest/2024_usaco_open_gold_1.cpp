#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin>>N>>K;
    deque<pair<int, int>> q;
    bool arrow_from_top = false;
    string s1, s2; std::cin>>s1>>s2;
    long long ans = 0;

    for (int i = 0; i < s1.size(); i++) {

        if (s1[i] != s2[i]) {
            if (q.empty()) {
                arrow_from_top = (s1[i] == '1');
            }
            if ( ((s1[i] == '1') && !arrow_from_top) || ((s1[i] == '0') && arrow_from_top) ) {
                ans ++;
                if (q.back().second == 1) {
                    q.pop_back();
                } else {
                    q.back().second --;
                }
            } else {
                q.push_front({i, 1});
            } 
        }
        if (!q.empty() && q.back().first == i - K) {
            if (q.front().first == i) {
                q.front().second += q.back().second;
            } else {
                q.emplace_front(i, q.back().second);
            }
            ans += q.back().second;
            q.pop_back();
        }
    }

    std::cout << ans << "\n";
}