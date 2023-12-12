#include <iostream>
#include <vector>

using namespace std;


int main() {
    int n;
    scanf("%d\n",&n);

    vector<vector<int>> mi(n, vector<int>(n, 0));
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            mi[y][x] = (fgetc(stdin) == '.') ? 0 : 1;
        }
        volatile int tmp = fgetc(stdin);
    }

    for (int y = 0; y < n; ++y) {
        if (mi[y][0])
            break;
        dp[y][0] = 1;
    }

    for (int x = 0; x < n; ++x) {
        if (mi[0][x])
            break;
        dp[0][x] = 1;
    }

    for (int y = 1; y < n; ++y) {
        for (int x = 1; x < n; ++x) {
            if (mi[y][x])
                continue;
            dp[y][x] = dp[y-1][x] + dp[y][x-1];
            dp[y][x] %= 1000000007;
        }
    }

    printf("%d\n",dp[n-1][n-1]);

    return 0;
}