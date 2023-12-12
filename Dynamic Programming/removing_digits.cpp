#include <iostream>


int main() {
    int n,k = 0;
    scanf("%d\n",&n);

    while (n) {
        int maximal = -1;
        for (int i = n; i > 0; i /= 10) {
            maximal = std::max(maximal, i%10);
        }
        ++k;
        n -= maximal;
    }
    printf("%d\n",k);

    return 0;
}