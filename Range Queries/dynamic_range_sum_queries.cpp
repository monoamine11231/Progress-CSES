#include <iostream>

using namespace std;

int n,q;
uint64_t t[400000];

void update(int p, int v) {
    p += n;
    t[p] = v;
    for (; p > 1; p /= 2)
        t[p/2] = t[p] + t[p^1];
}

uint64_t query(int l, int r) {
    l += n;
    r += n;

    uint64_t res = 0;
    for (; l < r; l /= 2, r /= 2) {
        if (l & 1) {
            res += t[l++];
        }

        if (r & 1) {
            res += t[--r];
        }
    }

    return res;
}

int main() {
    scanf("%d %d\n",&n,&q);

    for (int i = n; i < 2*n; ++i) {
        int tmp;
        scanf("%d ",&tmp);
        t[i] = tmp;
    }

    for (int i = n-1; i > 0; --i)
        t[i] = t[2*i+0] + t[2*i+1];

    for (int i = 0; i < q; ++i) {
        char op;
        int a,b;
        scanf("%c %d %d\n",&op,&a,&b);

        if (op == '1') {
            update(a-1,b);
            continue;
        }

        printf("%lu\n",query(a-1,b));
    }

    return 0;
}