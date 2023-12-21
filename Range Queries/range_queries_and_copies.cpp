#include <iostream>
#include <vector>


using namespace std;
using ll = int64_t;

struct node {
    node *l;
    node *r;
    ll v;

    node(node *l, node *r, ll v) : l(l), r(r), v(v) {}      /* Initialize manually */
    node(ll v) : l(nullptr), r(nullptr), v(v) {}            /* Final leaf */
    node(node *l, node *r) : l(l), r(r), v(l->v + r->v) {}  /* Merge */
};

vector<node*> versions;

int n,q,arr[400000];

node* build() {
    auto build_help = [](auto &&self, int segment_start, int segment_end) {
        if (segment_start == segment_end)
            return new node({arr[segment_start]});
    
        int segment_mid = segment_start + (segment_end - segment_start) / 2;
        
        node *resl, *resr;
        resl = self(self, segment_start, segment_mid);
        resr = self(self, segment_mid+1, segment_end);

        return new node({resl,resr});
    };

    return build_help(build_help, 0, n-1);
}

ll query(int version, int l, int r) {
    auto query_help = [=](auto &&self, node *node, int segment_start, int segment_end) {
        if (r < segment_start || segment_end < l)
            return static_cast<ll>(0);

        if (l <= segment_start && segment_end <= r)
            return node->v;

        int segment_mid = segment_start + (segment_end - segment_start) / 2;

        ll resl = self(self, node->l, segment_start, segment_mid);
        ll resr = self(self, node->r, segment_mid+1, segment_end);

        return resl + resr;
    };

    return query_help(query_help, versions[version], 0, n-1);
}

void update(int version, int pos, int value) {
    auto update_help = [=](auto &&self, node *n, int segment_start, int segment_end) {
        if (segment_start == segment_end) {
            return new node({value});
        }

        int segment_mid = segment_start + (segment_end - segment_start) / 2;
        if (segment_start <= pos && pos <= segment_mid) {
            return new node({self(self, n->l, segment_start, segment_mid), n->r});
        }

        return new node({n->l, self(self, n->r, segment_mid+1, segment_end)});
    };
    versions[version] = update_help(update_help, versions[version], 0, n-1);
}


int main() {
    scanf("%d %d\n",&n,&q);

    for (int i = 0; i < n; ++i) {
        scanf("%d ", &arr[i]);
    }

    versions.push_back(build());

    int options[3];
    for (int i = 0; i < q; ++i) {
        char op;
        scanf("%c",&op);
        switch (op) {
        case '1':
            scanf(" %d %d %d\n", &options[0],&options[1],&options[2]);

            update(options[0]-1, options[1]-1, options[2]);
            break;
        case '2':
            scanf(" %d %d %d\n", &options[0],&options[1],&options[2]);

            printf("%ld\n", query(options[0]-1,options[1]-1,options[2]-1));
            break;
        case '3':
            scanf(" %d\n", &options[0]);

            versions.push_back(versions[options[0]-1]);
            break;
        default:
            break;
        }
    }


    return 0;
};