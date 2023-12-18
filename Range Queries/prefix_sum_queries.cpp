/* 
 * PROBLEM SIMPLIFICATION:
 * Non-commutative segment tree which holds two
 * ...values. The sum of the range and the best
 * ...prefix sum. When merging two ranges and
 * ...want to find the best prefix sum in that
 * ...merged range, you need to perform
 * ...`max(left_range.best_prefix,left_range.sum+right_range.best_prefix)`
 */


#include <iostream>

using namespace std;

struct pi {
    int64_t sum;
    int64_t prefix;
};

int n,q;
pi t[2*200000] = {{0,0}};

void segtree_update(int p, int v) {
    p+=n;
    t[p].sum = v;
    t[p].prefix = v;

    for (; p /= 2; ) {
        t[p].prefix = max(t[p*2].prefix, t[p*2].sum+t[p*2+1].prefix);
        t[p].sum = t[p*2].sum + t[p*2 + 1].sum;
    }
}

int64_t segtree_sum(int l, int r) {
    l += n;
    r += n;

    pi resl, resr;
    resl = resr = {0,0};
    for (; l < r; l /= 2, r /= 2) {
        if (l & 1) {
            resl.prefix = max(resl.prefix, resl.sum+t[l].prefix);
            resl.sum += t[l].sum;
            ++l;
        }

        if (r & 1) {
            --r;
            resr.prefix = max(t[r].prefix, t[r].sum + resr.prefix);
            resr.sum += t[r].sum;
        }
    }
    
    return max(resl.prefix, resl.sum+resr.prefix);
}

int main() {
    scanf("%d %d\n",&n,&q);
    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ",&tmp);
        t[n+i].sum = tmp;
        t[n+i].prefix = tmp;
    }

    for (int i = n - 1; i > 0; --i) {
        t[i].sum = t[i*2+0].sum + t[i*2+1].sum;
        t[i].prefix = max(t[i*2+0].prefix, t[i*2+0].sum+t[i*2+1].prefix);
    }

    for (int i = 0; i < q; ++i) {
        char op;
        int a,b;
        scanf("%c %d %d\n",&op,&a,&b);

        if (op == '1') {
            segtree_update(a-1,b);
            continue;
        }
        printf("%ld\n",segtree_sum(a-1,b));
    }

    return 0;
}