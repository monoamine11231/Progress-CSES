#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, total = 0;
    scanf("%d\n",&n);

    vector<int> coins;
    coins.reserve(n);
    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ", &tmp);
        total += tmp;
        coins.push_back(tmp);
    }

    vector<vector<int>> dp(coins.size()+1, vector<int>(total+1, 0));

    for (int i = 0; i <= coins.size(); ++i)
        dp[i][0] = 1;
    for (int i = 1; i <= coins.size(); ++i) {
        for (int w = 1; w <= total; ++w) {
            dp[i][w] = dp[i-1][w];
            if (!dp[i][w] && w-coins[i-1] >= 0) {
                dp[i][w] = dp[i-1][w-coins[i-1]];
            }
        }
    }

    int num = 0;
    vector<int> sums;
    sums.reserve(total);
    for (int w = 1; w <= total; ++w) {
        if (!dp[coins.size()][w])
            continue;
        ++num;
        sums.push_back(w);
    }

    printf("%d\n", num);
    for (int s : sums) {
        printf("%d ", s);
    }
    printf("\n");

    return 0;
}