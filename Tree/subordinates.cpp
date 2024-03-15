#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct node {
    int id;
    node *parent;
    vector<node*> children;

    node() : parent(nullptr) {};
};

int N;
node a[200001];
int subs[200001] = {0};


int trace(node *root) {
    int sum = root->children.size();
    for (auto *e : root->children) {
        if (!e->children.size())
            continue;

        sum += trace(e);
    }
    subs[root->id] = sum;
    return sum;
}

int main() {
    a[1].id = 1;

    scanf("%d\n",&N);
    for (int i = 2; i <= N; ++i) {
        int p;
        scanf("%d ", &p);

        a[i].parent = a+p;
        a[i].id = i;
        a[p].children.push_back(a+i);  
    }

    trace(a+1);

    for (int i = 1; i <= N; ++i)
        printf("%d ", subs[i]);
    printf("\n");
    return 0;
}