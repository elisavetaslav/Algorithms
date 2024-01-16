#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

int n;

struct Node {
    int a = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int al) {
        a = al;
    }
    Node(Node* x) {
        a = x->a;
        left = x->left;
        right = x->right;
    }
};

std::vector<Node*> version;

void build(std::vector<Node*>& v, int now, int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    build(v, now * 2 + 1, l, mid);
    build(v, now * 2 + 2, mid + 1, r);
    v[now] = new Node((v[now * 2 + 1] ? v[now * 2 + 1]->a : 0) + (v[now * 2 + 2] ? v[now * 2 + 2]->a : 0));
    v[now]->left = v[now * 2 + 1];
    v[now]->right = v[now * 2 + 2];
}

Node* set_v(Node* root, int l, int r, int pos, int val) {
    if (l == r) {
        auto u = new Node(val);
        return u;
    }
    int mid = (l + r) / 2;
    Node *a = new Node(root);
    if (pos <= mid) {
        a->left = set_v(root->left, l, mid, pos, val);
    } else {
        a->right = set_v(root->right, mid + 1, r, pos, val);
    }
    a->a = (a->left ? a->left->a : 0) + (a->right ? a->right->a : 0);
    return a;
}


int get_v(Node* root, int left, int right, int& k) {
    if (root->a < k || left == right) {
        k -= root->a;
        return right;
    }
    int mid = (left + right) / 2;
    int a = get_v(root->left, left, mid, k);
    if (k > 0) {
        a = get_v(root->right, mid + 1, right, k);
    }
    return a;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m, q;
    std::cin >> n >> m;
    int lg = ceil(log2(static_cast<double>(n)));
    lg = 1 << lg;
    std::vector<int> a(n);
    std::unordered_set<int> s;
    std::unordered_map<int, std::vector<int>> map;
    std::vector<Node *> b(lg * 2 - 1);
    for (int i = 0; i < n; ++i) { // если не встречалось раньше a_i, то b_i = 1 и создаем первое дерево отрезков
        int al, aa;
        std::cin >> al;
        a[i] = al;
        map[al].emplace_back(i);
        if (s.count(al) == 0) aa = 1;
        else aa = 0;
        s.insert(al);
        b[lg - 1 + i] = new Node(aa);
    }
    s.clear();

    build(b, 0, 0, lg - 1); //строим дерево отрезков
    Node *root = b[0];
    b.clear();
    std::vector<int> d(n, -1);
    for (int i = 0; i < n; ++i) {
        auto u = find(map[a[i]].begin(), map[a[i]].end(), i) - map[a[i]].begin();
        if (u + 1 < map[a[i]].size()) {
            d[i] = map[a[i]][u + 1];
        }
    }

    std::cin >> q;

    version.emplace_back(root);
    for (int l = 0; l < n; ++l) {
        if (d[l] < 0) {
            version.emplace_back(set_v(version[version.size() - 1], 0, lg - 1, l, 0));
        } else {
            Node *node = set_v(version[version.size() - 1], 0, lg - 1, d[l], 1);
            version.emplace_back(set_v(node, 0, lg - 1, l, 0));
        }
    }


    int p = 0;
    for (int i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;
        int l = (x + p) % n;
        int k = (y + p) % m + 1;
        int ans = get_v(version[l], 0, lg - 1, k);
        if (k > 0) {
            std::cout << '0' << '\n';
            p = 0;
        } else {
            std::cout << ans + 1 << '\n';
            p = ans + 1;
        }
    }
    return 0;
}
