#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;


#define contains(v, k) (find(v.begin(), v.end(), k)!=v.end())

int main() {
    /*
    5   12  8   1   |   (4) (8) (5) (3)
    13  -1  13  9   |   (9) (x) (9) (8)
    */

    int n, x;
    int h[1000], s[1000];
    scanf("%d %d\n", &n,&x);

    vector<vector<int>> dp(n+1, vector<int>(x+1, 0));

    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ", &tmp);
        h[i] = tmp;
    }

    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ", &tmp);
        s[i] = tmp;
    }

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= x; ++w) {
            if (h[i-1] <= w) {
                dp[i][w] = max(dp[i-1][w-h[i-1]]+s[i-1], dp[i-1][w]);
                continue;
            }
            dp[i][w] = dp[i-1][w];
        }
    }

    printf("%d\n", dp[n][x]);

    return 0;
}