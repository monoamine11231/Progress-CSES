#include <iostream>


int n,q;
int dp[1000][1000] = {0};

int main() {
    scanf("%d %d\n",&n,&q);

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            char c;
            scanf("%c ", &c);
            dp[y][x] = (c == '*');
        }
    }

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            int t = (y > 0) ? dp[y-1][x] : 0;
            int tl = (y > 0 && x > 0) ? dp[y-1][x-1] : 0;
            int l = (x > 0) ? dp[y][x-1] : 0;

            dp[y][x] += t + l - tl; 
        }
    }

    for (int i = 0; i < q; ++i) {
        int y1,x1,y2,x2;
        scanf("%d %d %d %d\n",&y1,&x1,&y2,&x2);

        int p1,p2,p3,p4;
        p1 = dp[y2-1][x2-1];
        p2 = (x1-2 >= 0) ? dp[y2-1][x1-2] : 0;
        p3 = (y1-2 >= 0) ? dp[y1-2][x2-1] : 0;
        p4 = (x1-2 >= 0 && y1-2 >= 0) ? dp[y1-2][x1-2] : 0;

        printf("%d\n", p1-p2-p3+p4);
    }

    // for (int y = 0; y < n; ++y) {
    //     for (int x = 0; x < n; ++x) {
    //         printf("%d\t", dp[y][x]);
    //     }
    //     printf("\n");
    // }

    return 0;
}