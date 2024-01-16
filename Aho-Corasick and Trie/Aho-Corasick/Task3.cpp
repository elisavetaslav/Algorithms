#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

std::vector<std::string> dict;
size_t k = 0;

struct Node {
    std::map<char, Node*> e;
    bool term = false;
    bool vis = false;
    bool f = false;
    char c;
    int64_t num = 0;
    Node* suflink = nullptr;
    Node* termlink = nullptr;
    std::vector<Node*> aut;
    Node* parent = nullptr;

    Node() {
        aut.assign(26, nullptr);
    }
} root;

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
    if (!a->term) {
        a->term = true;
    }
    ++a->num;
}

Node* get_aut(Node* a, char c);

Node* get_suf(Node* a) {
    if (!a->suflink) {
        if (a == &root || a->parent == &root) {
            a->suflink = &root;
        } else {
            a->suflink = get_aut(get_suf(a->parent), a->c);
        }
    }
    return a->suflink;
}

Node *get_term(Node* a) {
    if (!a->termlink) {
        Node *u = get_suf(a);
        if (u == &root) {
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
    if (!a->aut[c - 'a']) {
        if (a->e.count(c)) {
            a->aut[c - 'a'] = a->e[c];
        } else {
            if (a == &root) {
                a->aut[c - 'a'] = &root;
            } else {
                a->aut[c - 'a'] = get_aut(get_suf(a), c);
            }
        }
    }
    return a->aut[c - 'a'];
}

void build() {
    Node* a = &root;
    std::queue<Node*> q;
    a->suflink = get_suf(a);
    for (int i = 0; i < 26; ++i) {
        a->aut[i] = get_aut(a, char(i + 97));
    }
    a->termlink = get_term(a);
    q.emplace(a);
    while (!q.empty()) {
        a = q.front();
        q.pop();
        for (auto [c, nod]: a->e) {
            if (!nod->suflink) {
                nod->suflink = get_suf(nod);
                for (int i = 0; i < 26; ++i) {
                    nod->aut[i] = get_aut(nod, char(i + 97));
                }
                nod->termlink = get_term(nod);
                q.push(nod);
            }
        }
    }
}

int64_t count(const std::string& s, int l, int r) {
    Node* a = &root;
    for (int i = l; i <= r; ++i) {
        if (a->e.end() == a->e.find(s[i])) {
            return 0;
        }
        a = a->e[s[i]];
    }
    if (!a->f && l == 0 && r == s.size() - 1) {
        a->f = true;
        return a->num - 1;
    } else if (!a->vis) {
        a->vis = true;
        return a->num;
    }
    return 0;
}

void clear(const std::string &s, int l, int r) {
    Node* a = &root;
    for (int i = l; i <= r; ++i) {
        if (a->e.find(s[i]) == a->e.end()) {
            return;
        }
        a = a->e[s[i]];
    }
    if (l == 0 && r == s.size() - 1) {
        a->f = false;
    } else {
        a->vis = false;
    }
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string s1;
        std::cin >> s1;
        dict.push_back(s1);
        add(s1);
    }
    build();

    for (const auto &s: dict) {
        for (int l = 0; l < s.size(); ++l) {
            for (int r = l; r < s.size(); ++r) {
                k += count(s, l, r);
            }
        }
        for (int l = 0; l < s.size(); ++l) {
            for (int r = l; r < s.size(); ++r) {
                clear(s, l, r);
            }
        }
    }
    std::cout << k;
    return 0;
}