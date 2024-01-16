#include <iostream>
#include <string>
#include <vector>

struct Node {
    std::vector<Node *> e;
    bool term = false;
    bool vis = false;
    int k = 0;
    int count = 0;

    Node() {
        e.assign(26, nullptr);
    }
};

void build(std::string &s, Node *root) {
    Node *a = root;
    for (char c: s) {
        if (a->e[int(c) - 97]) {
            a = a->e[int(c) - 97];
        } else {
            a->e[int(c) - 97] = new Node();
            a = a->e[int(c) - 97];
        }
        ++a->k;
    }
    ++a->count;
    a->term = true;
}

void find(int k, Node *a, std::string &s) {
    for (int i = 0; i < 26; ++i) {
        if (a->e[i]) {
            if (k - (a->e[i]->k) > 0) {
                k -= a->e[i]->k;
            } else {
                s.push_back(char(97 + i));
                find(k, a->e[i], s);
                break;
            }
        }
    }
}


void dfs(Node* now, int& k, std::string& tout, bool& f) {
    for (int i = 0; i < 26; ++i) {
        if (now->e[i]) {
            if (now->e[i]->k>=k) {
                tout.push_back(char(97+i));
                k -= now->e[i]->count;
                if (k<=0) {
                    f = true;
                    return;
                }
                dfs(now->e[i], k, tout, f);
                if (f) return;
            } else {
                k -= now->e[i]->k;
            }
        }
    }
}
int main() {
    int n;
    std::cin >> n;
    Node *root = new Node();
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (x == 1) {
            std::string s;
            std::cin >> s;
            build(s, root);
        } else {
            int y;
            std::cin >> y;
            std::string s = "";
            Node* a = root;
            bool f = 0;
            dfs(a,y, s, f);
            std::cout << s<<'\n';
        }
    }
    return 0;
}

