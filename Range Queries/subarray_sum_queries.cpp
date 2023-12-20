/*
 * If knowing how to solve maximum subarray sum using divide
 * ...and conquer, then you know how to solve this. Same
 * ...principle,you just store everything you need inside
 * ...a range node for the segment tree, and update it 
 * ...accordingly when merging the two nodes (ranges)
 */

#include <iostream>
#include <algorithm>

using namespace std;

struct node {
    int64_t sum;        /* Sum */
    int64_t mss;        /* Maximum subarray sum */
    int64_t mincps;     /* Maximum incresing prefix sum (left to right prefix sum ) */
    int64_t mdecps;     /* Maximum decreasing prefix sum (right to left prefix sum) */
};


node t[400000];
int n,m;

node combine(const node &l, const node &r) {
    node res;
    
    res.mss = max({l.mss, l.mdecps+r.mincps, r.mss});
    res.mincps = max(l.mincps, l.sum + r.mincps);
    res.mdecps = max(r.mdecps, r.sum+l.mdecps);
    res.sum = l.sum + r.sum;

    return res;
}

void segtree_update(int p, int x) {
    p += n;
    t[p].mdecps = x;
    t[p].mincps = x;
    t[p].sum = x;
    t[p].mss = x;

    for (; p /= 2; )
        t[p] = combine(t[p*2], t[p*2+1]);
}

int64_t segtree_query(int l, int r) {
    l += n;
    r += n;

    node resl,resr;
    resl = resr = {0,0,0,0};

    for (; l < r; l /= 2, r /= 2) {
        if (l & 1) {
            resl = combine(resl, t[l++]);            
        }

        if (r & 1) {
            resr = combine(t[--r], resr);
        }
    }

    return max({resl.mss, resl.mdecps+resr.mincps, resr.mss});
}

int main() {
    scanf("%d %d\n",&n,&m);

    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ",&tmp);

        t[n+i].sum = tmp;
        t[n+i].mss = tmp;
        t[n+i].mincps = tmp;
        t[n+i].mdecps = tmp;
    }

    for (int i = n - 1; i > 0; --i) {
        t[i] = combine(t[i*2+0],t[i*2+1]);
    }

    for (int i = 0; i < m; ++i) {
        int k,x;
        scanf("%d %d\n",&k,&x);

        segtree_update(k-1,x);
        printf("%ld\n", segtree_query(0,n));
    }

    return 0;
};