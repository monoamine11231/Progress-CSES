#include <iostream>
#include <unordered_map>


int main() {
    int n,x;
    scanf("%d %d\n",&n,&x);

    int max_c = 0;
    int c[100];
    std::unordered_map<int, bool> h;
    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d", &tmp);
        c[i] = tmp;
        h[tmp] = true;

        max_c = std::max(max_c, tmp);
    }

    int dp[x+1];
    for (int i = 1; i <= x; ++i) {
        if (h[i]) {
            dp[i] = 1;
            continue;
        }

        int minimal = INT32_MAX;
        for (int j = 0; j < n; ++j) {
            if (i <= c[j] || dp[i-c[j]] == -1)
                continue;
            minimal = std::min(minimal, dp[i-c[j]]);
        }

        if (minimal == INT32_MAX) {
            dp[i] = -1;
            continue;
        }
        dp[i] = minimal+1;
    }
    printf("%d\n", dp[x]);

    return 0;
}