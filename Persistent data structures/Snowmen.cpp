#include <iostream>
#include <vector>

struct Node {
    int64_t weight = 0;
    Node* head = nullptr;
    Node* clon = nullptr;
};

void snowball(std::vector<Node*>& v) {
    int t, m;
    std::cin >> t >> m;
    Node* a = new Node;
    a->clon = v[t];
    if (m!=0) {
        a->weight = a->clon->weight + m;
        a->head = a->clon;
    } else {
        a->weight = a->clon->head->weight;
        if (a->weight!=0) a->head = a->clon->head->head;

    }
    v.push_back(a);
}
int main() {
    int n;
    std::cin >> n;
    std::vector<Node*> v;
    v.push_back(new Node);
    for (int i = 0; i < n; ++i) {
        snowball(v);
    }
    int64_t sum = 0;
    for (int i = 0; i <= n; ++i) {
        sum += v[i]->weight;
    }
    std::cout << sum;
    return 0;
}
