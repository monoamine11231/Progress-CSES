#include <iostream>

using namespace std;

#define LOG(X) cout << #X << "\t|\t" << X << endl; 

int n,q;
struct pi {
    int plus;
    int minus;
};

pi t[400000] = {{0,0}};

void segtree_update(int p, int v, int o) {
    p += n;
    t[p].minus = v-o;
    t[p].plus = v+o;
    for (; p > 1; p/=2) {
        t[p/2].minus = min(t[p].minus,t[p^1].minus);
        t[p/2].plus = min(t[p].plus,t[p^1].plus);
    }
}

int segtree_query(int l, int r, int pi::* member) {
    l += n;
    r += n;
    int res = INT32_MAX;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res = min(res, t[l++].*member);
        if (r & 1)
            res = min(res, t[--r].*member);
    }

    return res;
}

int main() {
    scanf("%d %d\n",&n,&q);

    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ",&tmp);

        t[n+i].minus = -(i+1)+tmp;
        t[n+i].plus = (i+1)+tmp;
    }

    for (int i = n - 1; i > 0; --i) {
        t[i].minus = min(t[i*2+0].minus,t[i*2+1].minus);
        t[i].plus = min(t[i*2+0].plus,t[i*2+1].plus);
    }

    for (int i = 0; i < q; ++i) {
        char op;
        scanf("%c",&op);
        if (op == '1') {
            int k,x;

            scanf(" %d %d\n",&k,&x);

            segtree_update(k-1,x,k);
            continue;
        }

        int k;
        scanf(" %d\n",&k);

        int a = segtree_query(0,k, &pi::minus);
        int b = segtree_query(k,n, &pi::plus);
        printf("%d\n",min(a+k,b-k));
    }

    return 0;
}