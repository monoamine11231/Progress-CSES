#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    vector<vector<int>> dp(s1.size()+1, vector<int>(s2.size()+1, 0));

    for (int y = 0; y <= s1.size(); ++y)
        dp[y][0] = y;

    for (int x = 0; x <= s2.size(); ++x)
        dp[0][x] = x;

    for (int y = 1; y <= s1.size(); ++y) {
        for (int x = 1; x <= s2.size(); ++x) {
            dp[y][x] = min({
                dp[y][x-1] + 1,
                dp[y-1][x] + 1,
                dp[y-1][x-1] + (s1[y-1] != s2[x-1])
            });
        }
    }

    printf("%d\n", dp[s1.size()][s2.size()]);
    return 0;
}