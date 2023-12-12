#include <iostream>


int main() {
    int N;
    scanf("%d\n",&N);

    int dp[8] = {0,1,2,4,8,16,32};
    if (N <= 6) {
        printf("%d\n", dp[N]);
        return 0;
    }

    for (int i = 7; i <= N; ++i) {
        int tmp = 0;

        for (int j = 1; j <= 6; ++j) {
            tmp += dp[j];
            tmp %= 1000000007;

            dp[j] = dp[j+1];
        }
        dp[6] = tmp;
    }
    printf("%d\n", dp[6]);

    return 0;
}