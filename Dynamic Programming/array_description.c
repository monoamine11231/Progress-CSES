#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef unsigned long u64;

int main() {
    int n,m,t,p = 0;
    scanf("%d %d\n",&n,&m);

    u64 dp[102] = {0};

    u64 counter = 1;
    bool prev_was_zero = false; 
    for (int i = 1; i <= n; ++i, p = t) {
        scanf("%d ", &t);

        int a = t-p;
        a *= (a < 0) ? -1 : 1;
        if (a > 1 && p && t) {
            printf("0\n");
            return 0;
        }

        if (t) {
            if (prev_was_zero) {
                counter *= dp[t-1]+dp[t+0]+dp[t+1];
                counter %= 1000000007UL;
            }
            memset(dp, 0, sizeof(dp));
            dp[t] = 1;
            prev_was_zero = false;
            continue;
        }

        if (i == 1) {
            for (int i = 1; i <= m; ++i)
                dp[i] = 1;
        } else {
            u64 ndp[102] = {0};
            for (int j = 1; j <= m; ++j) {
                ndp[j] = dp[j-1] + dp[j+0] + dp[j+1];
                ndp[j] %= 1000000007UL;
            }
            memcpy(dp, ndp, sizeof(dp));
        }

        prev_was_zero = true;
    }

    if (prev_was_zero) {
        u64 scounter = 0;
        for (int j = 1; j <= m; ++j) {
            scounter += dp[j];
        }
        counter *= scounter;
        counter %= 1000000007UL;
    }

    printf("%lu\n", counter);

    return 0;
}