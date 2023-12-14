/*
 * HOW IS BUILDING UP, SORTING AN ARRAY AND THEN REMOVING DUPLICATES FASTER
 * THAN BUILDING UP A SET?????????????????????????????????????????
 * AND SO MUCH FASTER THAT NO TLE AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

int n,q,d;
int arr[200000], counts[400001] = {0}, fenwick[400000] = {0};

void fenwick_increase(int p, int delta) {
    for (; p <= d; p += p & (-p))
        fenwick[p] += delta;
}

int fenwick_sum(int p) {
    int res = 0;
    for (; p > 0; p -= p & (-p))
        res += fenwick[p];
    return res;
}


int main() {
    scanf("%d %d\n",&n,&q);

    vector<int> s;
    s.reserve(n);
    queue<tuple<bool,int,int>> queries;
    unordered_map<int,int> cc;

    for (int i = 0; i < n; ++i) {
        scanf("%d ",&arr[i]);
        s.push_back(arr[i]);
    }

    for (int i = 0; i < q; ++i) {
        char op;
        int a,b;
        scanf("%c %d %d\n",&op,&a,&b);

        if (op == '!') {
            s.push_back(b);
            queries.push({false,a,b});
            continue;
        }
        s.push_back(a);
        s.push_back(b);
        queries.push({true,a,b});
    }
    
    sort(s.begin(),s.end());
    s.erase(unique(s.begin(),s.end()),s.end());

    int k = 0;
    for (auto &e : s) {
        cc[e] = k++;
    }

    d = s.size();
    for (int i = 0; i < n; ++i) {
        fenwick_increase(cc[arr[i]]+1,1);
    }

    for (int i = 0; i < q; ++i) {
        auto e = queries.front();
        queries.pop();

        if (get<0>(e)) {
            int u,l;
            u = fenwick_sum(cc[get<2>(e)]+1);
            l = (cc[get<1>(e)] > 0) ? fenwick_sum(cc[get<1>(e)]) : 0;

            printf("%d ",u-l);
            continue;
        }

        fenwick_increase(cc[arr[get<1>(e)-1]]+1,-1);
        arr[get<1>(e)-1] = get<2>(e);
        fenwick_increase(cc[get<2>(e)]+1,1);
    }
    printf("\n");


    return 0;
}