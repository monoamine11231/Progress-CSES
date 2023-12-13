#include <iostream>
#include <algorithm>

using namespace std;

int arr[200000];
int64_t fenwick[200001] = {0};
int n;


void fenwick_update(int p, int delta) {
    for (int i = p; i <= n; i += i&(-i))
        fenwick[i] += delta;
}

int fenwick_query(int p) {
    int res = 0;
    for (int x = p; x > 0; x -= x&(-x))
        res += fenwick[x];
    return res;
}


int fenwick_upper_bound(int v) {
    int s = 1, e = n;

    while (s < e) {
        int m = s + (e-s)/2;

        if (fenwick_query(m) < v) {
            s = m + 1;
            continue;
        }

        e = m;
    }

    return s;
}

int main() {
    scanf("%d\n",&n);
    for (int i = 0; i < n; ++i) {
        scanf("%d ",&arr[i]);
        fenwick_update(i+1,1);
    }

    for (int i = 0; i < n; ++i) {
        int p;
        scanf("%d ",&p);

        int j = fenwick_upper_bound(p);
        // printf("p: %d\tj: %d\tupper bound: %d\n",p,j,fenwick_query(j));
        printf("%d\n",arr[j-1]);
        fenwick_update(j, -1);
    }

    return 0;
}