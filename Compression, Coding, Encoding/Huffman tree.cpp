#include <iostream>
#include <string>
#include <vector>

struct Node {
    Node* l;
    Node* r;
    Node* p;
    bool vis = false;
};

std::vector<std::string> ans;

void build(std::string s, Node* root) {
    Node* cur = root;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'D') {
            if (!cur->l) {
                Node* a = new Node();
                a->p = cur;
                cur->l = a;
                cur = a;
            } else {
                Node* a = new Node();
                cur->r = a;
                a->p = cur;
                cur = a;
            }
        } else {
            while (cur->p) {
                if (cur == cur->p->r) {
                    cur = cur->p;
                } else {
                    cur = cur->p;
                    Node* a = new Node();
                    cur->r = a;
                    a->p = cur;
                    cur = a;
                    break;
                }
            }
        }
    }
}
void dfs(Node* a, std::string& s) {
    if (!a->l && !a->r) {
        ans.push_back(s);
        delete a;
        return;
    }
    a->vis = true;
    if (a->l) {
        if (!a->l->vis) {
            s.push_back('0');
            dfs(a->l, s);
            s.pop_back();
        }
    }
    if (a->r) {
        if (!a->r->vis) {
            s.push_back('1');
            dfs(a->r, s);
            s.pop_back();
        }
    }
    delete a;
}


int main() {
    int n;
    std::cin >> n;
    std::string s;
    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        Node* root = new Node();
        build(s, root);
        std::string a;
        dfs(root,a);
        std::cout<<ans.size()<<'\n';
        for (std::string str : ans) {
            std::cout<<str<<'\n';
        }
        ans.clear();
    }
    return 0;
}