#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

std::vector<std::vector<int>> v;
std::vector<int> dict;

struct Node {
    std::map<char, Node *> e;
    bool term = false;
    std::vector<int> num;
    char c;
    Node* suflink = nullptr;
    Node* termlink = nullptr;
    std::vector<Node*> aut;
    Node* parent = nullptr;
    Node() {
        aut.assign(26, nullptr);
    }
}root;

void add(const std::string& s) {
    Node* a = &root;
    for (char c : s) {
        if (!a->e.count(c)) {
            a->e[c] = new Node();
        }
        a->e[c]->c = c;
        a->e[c]->parent = a;
        a = a->e[c];
    }
    a->num.push_back(dict.size()-1);
    a->term = true;
}

Node* get_aut(Node* a, char c);
Node* get_suf(Node* a) {
    if (!a->suflink) {
        if (a==&root || a->parent == &root) {
            a->suflink = &root;
        } else {
            a->suflink = get_aut(get_suf(a->parent), a->c);
        }
    }
    return a->suflink;
}

Node* get_term(Node* a) {
    if (!a->termlink) {
        Node* u = get_suf(a);
        if (u==&root) {
            a->termlink = &root;
        } else {
            if (u->term) {
                a->termlink = u;
            } else {
                a->termlink = get_term(u);
            }
        }
    }
    return a->termlink;
}

Node* get_aut(Node* a, char c) {
    if (!a->aut[c-'a']) {
        if (a->e.count(c)) {
            a->aut[c-'a'] = a->e[c];
        } else {
            if (a==&root) {
                a->aut[c-'a'] = &root;
            } else {
                a->aut[c-'a'] = get_aut(get_suf(a), c);
            }
        }
    }
    return a->aut[c-'a'];
}
void build() {
    Node* a = &root;
    std::queue<Node*> q;
    a->suflink = get_suf(a);
    for (int i = 0; i < 26; ++i) {
        a->aut[i] = get_aut(a, char(i+97));
    }
    a->termlink = get_term(a);
    q.emplace(a);
    while (!q.empty()) {
        a = q.front();
        q.pop();
        for (auto [c, nod] : a->e) {
            if (!nod->suflink) {
                nod->suflink = get_suf(nod);
                for (int i = 0; i < 26; ++i) {
                    nod->aut[i] = get_aut(nod, char(i+97));
                }
                nod->termlink = get_term(nod);
                q.push(nod);
            }
        }
    }
}

void go(Node* a, int j) {
    while (a!=&root) {
        if (a->term) {
            for (int i = 0; i < a->num.size(); ++i) {
                v[a->num[i]].push_back(j - dict[a->num[i]] + 1);
            }
        }
        a = get_suf(a);
    }
}

void find(const std::string& s){
    Node* a = &root;
    for (int i = 0; i < s.size(); ++i) {
        a = get_aut(a, s[i]);
        go(a, i+1);
    }
}

int main() {
    std::string s;
    std::cin >> s;
    int n;
    std::cin >> n;
    v.assign(n, std::vector<int>(0));
    for (int i = 0; i < n; ++i) {
        std::string s1;
        std::cin >> s1;
        dict.push_back(s1.length());
        add(s1);
    }
    build();
    find(s);
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i].size() << ' ';
        for (int j : v[i]) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
