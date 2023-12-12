#include <iostream>
#include <set>

using namespace std;
int main() {
    int n;
    scanf("%d\n", &n);
    set<int> d;


    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d ", &tmp);

        d.insert(tmp);
    }

    printf("%d\n", d.size());

    return 0;
}