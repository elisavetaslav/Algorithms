#include <iostream>
#include <string>
#include <vector>

struct Node {
    std::vector<Node*> e;
    bool term = false;
    bool vis = false;
    int k = 0;
    int count = 0;

    Node() {
        e.assign(26, nullptr);
    }
};


bool build(char c, Node* a) {
    bool f = false;
    if (a->e[int(c)-97]) {
        a= a->e[int(c)-97];
    } else {
        a->e[int(c) - 97] = new Node();
        f = true;
    }
    return f;
}



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, p, count = 0;
    char c;
    std::cin >> n;
    Node *root = new Node();
    std::vector<Node*> v(n+2, nullptr);
    v[1] = root;
    for (int i = 1; i < n + 1; ++i) {
        std::cin >> p >> c;
        if (build(c, v[p])) {
            ++count;
        }
        v[i+1] = v[p]->e[int(c)-97];
        std::cout<<count<<'\n';
    }
    return 0;
}