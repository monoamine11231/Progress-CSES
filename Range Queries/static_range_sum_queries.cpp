#include <iostream>

int n,q;
uint64_t t[400000];

uint64_t query(int l, int r) {
    l += n;
    r += n;

    uint64_t res = 0;

    while (l < r) {

        if (l & 1) {
            res += t[l++];
        }

        if (r & 1) {
            res += t[--r];
        }

        l /= 2;
        r /= 2;
    }

    return res;
}

int main() {
    scanf("%d %d\n",&n,&q);

    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ", &tmp);
        t[n+i] = tmp;
    }

    for (int i = n-1; i > 0; --i) {
        t[i] = t[2*i + 0] + t[2*i + 1];
    }

    for (int i = 0; i < q; ++i) {
        int a,b;
        scanf("%d %d\n",&a,&b);
        printf("%lu\n",query(a-1,b));
    }


    return 0;
}