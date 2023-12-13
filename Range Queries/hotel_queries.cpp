/*
 * PROBLEM SIMPLIFICATION:
 * Fast query of the first element in an UNSORTED array
 * ...where the element is K or larger and where updates
 * ...on the array can be performed. This is implemented
 * ...using a max segment tree and binary search on it.  
*/

#include <iostream> 

using namespace std;
 
int n,m;
int r[200000], t[400000] = {0};


void segtree_update(int p, int v) {
    p += n;
    t[p] = v;
    for (; p > 1; p /= 2)
        t[p/2] = max(t[p],t[p^1]);
}

int segtree_query(int r) {
    int res = -1, l = n;
    r += n;
    ++r;

    for (; l < r; l /= 2, r /= 2) {
        if (l & 1)
            res = max(res, t[l++]);
        if (r & 1)
            res = max(res, t[--r]);
    }

    return res;
}

int segtree_lower_bound(int v) {
    int s = 0, e = n-1;

    while (s < e) {
        int mid = s + (e-s) / 2;

        if (segtree_query(mid) < v) {
            s = mid + 1;
            continue;
        }

        e = mid;
    }

    if (s < n && segtree_query(s) < v)
        ++s;

    return s;
}


int main() {
    scanf("%d %d\n",&n,&m);
 
    for (int i = 0; i < n; ++i) {
        scanf("%d ",&t[n+i]);
    }
 
    for (int i = 0; i < m; ++i) {
        scanf("%d ",&r[i]);
    }

    for (int i = n-1; i > 0; --i)
        t[i] = max(t[i*2 + 0], t[i*2 + 1]);


    for (int i = 0; i < m; ++i) {
        int l = segtree_lower_bound(r[i]);

        if (l == n) {
            printf("0 ");
            continue;
        }

        printf("%d ", l+1);
        segtree_update(l,t[n+l]-r[i]);
    }
    printf("\n");
 
    return 0;
}