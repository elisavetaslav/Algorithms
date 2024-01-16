#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <vector>


struct Node {
    std::unordered_map<char, Node*> e;
    std::unordered_map<char, Node*> auto_link;
    Node* suf;
    Node* terml;
    int p;
    bool term;

    Node() {
        suf = nullptr;
        terml = nullptr;
        p = -1;
        term = false;
    }
};

std::string s;
const int64_t MOD = 1e9 + 7;
int m;

struct Trie {
    Node* root = new Node();

    void build() {
        root->suf = root;
        std::queue<Node*> qu;

        for (char a: s) {
            if (root->e.count(a)) {
                root->e[a]->suf = root;
                root->auto_link[a] = root->e[a];
                qu.push(root->e[a]);
            } else
                root->auto_link[a] = root;
        }

        while (!qu.empty()) {
            Node* cur_state = qu.front();
            qu.pop();
            for (char letter: s) {
                if (cur_state->e.count(letter)) {
                    Node *temp = cur_state->suf;
                    while (temp->e.count(letter) == 0 && temp != root)
                        temp = temp->suf;
                    if (temp->e.count(letter))
                        cur_state->e[letter]->suf = temp->e[letter];
                    else
                        cur_state->e[letter]->suf = root;
                    cur_state->auto_link[letter] = cur_state->e[letter];
                    qu.push(cur_state->e[letter]);
                } else
                    cur_state->auto_link[letter] = cur_state->suf->auto_link[letter];
            }

            if (cur_state->suf->p >= 0) {
                cur_state->terml = cur_state->suf;
            } else {
                cur_state->terml = cur_state->suf->terml;
            }
            if (cur_state->terml != nullptr) {
                cur_state->term = true;
            }
        }
    }

public:


    void build(std::vector<std::string>& patterns) {
        for (int i = 0; i < patterns.size(); i++) {
            Node* cur = root;
            for (char letter: patterns[i]) {
                if (cur->e.count(letter))
                    cur = cur->e[letter];
                else {
                    Node* new_child = new Node();
                    cur->e.insert({letter, new_child});
                    cur = new_child;
                }
            }
            cur->p = i;
            cur->term = true;
        }
        build();
    }

    void dfs(Node* now, std::unordered_map<Node*, int64_t[100]> &dp, int len) {
        if (len == m) {
            dp[now][0] = 1;
            return;
        }
        int64_t ans = 0;
        for (char letter: s) {
            if (!now->auto_link[letter]->term) {
                if (!dp[now->auto_link[letter]][m - len - 1])
                    dfs(now->auto_link[letter], dp, len + 1);
                ans += dp[now->auto_link[letter]][m - len - 1];
                ans %= MOD;
            }
        }
        dp[now][m - len] = ans;
    }
};


int main() {
    int n, p;
    std::cin >> n >> m >> p;
    std::cin >> s;
    Trie trie;
    std::vector<std::string> banned;
    for (int i = 0; i < p; ++i) {
        std::string word;
        std::cin >> word;
        banned.emplace_back(word);
    }
    trie.build(banned);
    std::unordered_map<Node *, int64_t[100]> dp;
    trie.dfs(trie.root, dp, 0);
    std::cout << dp[trie.root][m];
    return 0;
}