#include <iostream>
#include <unordered_map>


int main() {
    int n,x;
    scanf("%d %d\n",&n,&x);

    int c[100];
    std::unordered_map<int, bool> h;
    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ", &tmp);
        c[i] = tmp;
        h[tmp] = 1;
    }

    int dp[x+1];
    for (int i = 1; i <= x; ++i) {
        dp[i] = h[i];
        for (int j = 0; j < n; ++j) {
            if (i <= c[j])
                continue;
            dp[i] += dp[i-c[j]];
            dp[i] %= 1000000007;
        }
    }

    printf("%d\n", dp[x]);

    return 0;
}