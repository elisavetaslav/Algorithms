#include <bits/stdc++.h>

using namespace std;

class mystack {
public:
    mystack(mystack *d, int64_t v) : a_(v), p_(d) {
        size_ = p_->size_ + 1;
    }

    mystack() = default;

    mystack *push(int64_t a) {
        return new mystack(this, a);
    }

    mystack *pop() {
        if (this->size() <= 0) return nullptr;
        return p_;
    }

    int64_t top() {
        if (this->size() <= 0) return 0;
        return a_;
    }

    size_t size() {
        return size_;
    }

private:
    size_t size_ = 0;
    int64_t a_ = 0;
    mystack *p_ = nullptr;
};

void my_swap(mystack *&one, mystack *&two) {
    mystack *st = one;
    one = two;
    two = st;
}

class pers_queue {
public:
    pers_queue() {
        for (int i = 0; i < 5; ++i) {
            stacks.push_back(new mystack());
        }
    }

    pers_queue(vector<mystack *> other_stacks) : stacks(other_stacks.begin(), other_stacks.end()) {
    }

    pers_queue(bool f, bool ff, size_t cc, vector<mystack *> other_stacks) : stacks(other_stacks.begin(),
                                                                                    other_stacks.end()) {
        f_c = f;
        f_rec = ff;
        c = cc;
    }

    pers_queue(pers_queue *other) : stacks(other->stacks.begin(), other->stacks.end()) {
        f_c = other->f_c;
        f_rec = other->f_rec;
        c = other->c;
    }

    void func(mystack *&one, mystack *&two) {
        int64_t a = one->top();
        two = two->push(a);
        one = one->pop();
    }

    pers_queue *update() {
        vector<mystack *> st(stacks.begin(), stacks.end());
        bool f = f_c;
        size_t new_c = c;
        size_t k = 3;
        while (!f && st[0]->size() != 0) {
            if (k == 0) break;
            func(st[0], st[4]);
            --k;
        }
        while (st[2]->size() != 0) {
            if (k == 0) break;
            f = true;
            func(st[2], st[0]);
            --k;
        }
        while (st[4]->size() != 0) {
            if (k == 0) break;
            int64_t a = st[4]->top();
            st[4] = st[4]->pop();
            if (new_c != 0) {
                st[0] = st[0]->push(a);
                --new_c;
            }
            --k;
        }
        if (st[4]->size() == 0) {
            my_swap(st[2], st[3]);
        }
        return new pers_queue(f, f_rec, new_c, st);
    }

    pers_queue *is_ok() {
        pers_queue *ptr = this->update();
        bool f = ptr->stacks[4] ? ptr->stacks[4]->size() > 0 : false;
        return new pers_queue(ptr->f_c, f, ptr->c, ptr->stacks);
    }

    pers_queue *was_copy() {
        if ((stacks[2] ? stacks[2]->size() : 0) <= (stacks[0] ? stacks[0]->size() : 0)) {
            return new pers_queue(f_c, false, c, stacks);
        }
        vector<mystack *> st(stacks.begin(), stacks.end());
        st[1] = st[0];
        pers_queue *ptr = new pers_queue(false, true, stacks[0] ? stacks[0]->size() : 0, st);
        return ptr->is_ok();
    }

    pers_queue *push(int64_t a) {
        vector<mystack *> st(stacks.begin(), stacks.end());
        if (f_rec) {
            st[3] = stacks[3]->push(a);
            pers_queue *q = new pers_queue(f_c, f_rec, c, st);
            return q->is_ok();
        }
        st[2] = stacks[2]->push(a);
        pers_queue *q = new pers_queue(f_c, f_rec, c, st);
        return q->was_copy();
    }

    pers_queue *pop() {
        vector<mystack *> st(stacks.begin(), stacks.end());
        if (!f_rec) {
            st[0] = stacks[0]->pop();
            pers_queue *q = new pers_queue(f_c, f_rec, c, st);
            return q->was_copy();
        }
        size_t new_c = c;
        st[1] = stacks[1]->pop();
        if (c != 0) {
            --new_c;
        } else {
            st[0] = st[0]->pop();
        }
        pers_queue *q = new pers_queue(f_c, f_rec, new_c, st);
        return q->is_ok();
    }

    int64_t top() {
        if (f_rec) {
            return stacks[1]->top();
        }
        return stacks[0]->top();
    }

private:
    size_t c = 0;
    vector<mystack *> stacks;
    bool f_c = false;
    bool f_rec = false;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n;
    cin >> n;
    vector<pers_queue *> versions(n + 1);
    versions[0] = new pers_queue();
    for (size_t i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (x == 1) {
            size_t t;
            int64_t m;
            cin >> t >> m;
            versions[i] = versions[t]->push(m);
        } else {
            size_t t;
            cin >> t;
            cout << versions[t]->top() << '\n';
            versions[i] = versions[t]->pop();   //pop надо дебажить
        }
    }
    return 0;
}
