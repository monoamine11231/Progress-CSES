#include <iostream>
#include <algorithm>


int main() {
    int n,x;
    scanf("%d %d\n",&n,&x);

    int c[100];
    int dp[1000001] = {0};
    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ", &tmp);
        c[i] = tmp;
        // if (tmp <= x)
            // dp[tmp] = 1;
    }
    dp[0] = 1;
    // std::sort(c,c+n);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i <= x; ++i) {
            if (i - c[j] < 0)
                continue;
            // printf("dp[%d-%d] = %d\n", i, c[j], dp[i-c[j]]);
            dp[i] += dp[i-c[j]];
            dp[i] %= 1000000007;
        }
        printf("\n");
    }

    printf("%d\n", dp[x]);

    return 0;
}