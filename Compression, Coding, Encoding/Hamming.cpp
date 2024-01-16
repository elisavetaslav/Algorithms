#include <string>

std::string Hamming(std::string& s) {
    std::string ans;
    int a = 1, c = 0, i = 1;
    while (c != s.size()) {
        if (i == a) {
            a *= 2;
            ans.push_back('.');
        } else {
            ans.push_back(s[c]);
            ++c;
        }
        ++i;
    }
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i] == '.') {
            int j = i;
            int sum = 0;
            while (j < ans.size()) {
                for (int l = std::max(j, i + 1); l < std::min(static_cast<int>(ans.size()), j + i + 1); ++l) {
                    sum ^= ans[l] == '1' ? 1 : 0;
                }
                j += (i + 1) * 2;
            }
            ans[i] = sum == 1 ? '1' : '0';
        }
    }
    return ans;
}


std::string DeHamming(std::string& s) {
    int k = 0;
    int a = 1;
    for (int i = 0; i < s.size(); ++i) {
        if (i + 1 == a) {
            a *= 2;
            int j = i;
            int sum = 0;
            while (j < s.size()) {
                for (int l = j; l < std::min(static_cast<int>(s.size()), j + i + 1); ++l) {
                    sum ^= s[l] == '1' ? 1 : 0;
                }
                j += (i + 1) * 2;
            }
            if (sum != 0) k += i + 1;
        }
    }
    if (k != 0) s[k - 1] = s[k - 1] == '1' ? '0' : '1';
    std::string ans;
    a = 1;
    for (int i = 0; i < s.size(); ++i) {
        if (i + 1 == a) {
            a *= 2;
        } else {
            ans.push_back(s[i]);
        }
    }
    return ans;
}
