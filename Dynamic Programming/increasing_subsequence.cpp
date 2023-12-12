#include <iostream>
#include <vector>
#include <set>

using namespace std;


int main() {
    int n, v[200000], dp[200000];
    scanf("%d\n",&n);
    
    for (int i = 0; i < n; ++i) {
        scanf("%d\n", &v[i]);
    }
    set<int> a;
    a.insert(v[0]);
    for (int i = 1; i < n; ++i) {
        auto p = a.lower_bound(v[i]);
        if (p == a.end()) {
            a.insert(v[i]);
            continue;
        }

        // printf("v[i]=%d \t *p=%d\n", v[i], *p);
        if (*p <= v[i])
            continue;

        a.erase(p);
        a.insert(v[i]);
    }

    printf("%d\n",a.size());
    return 0;
}