#include <string>
#include <vector>
#include <unordered_map>

std::vector<int> LZWcode(std::string& s) {
    std::unordered_map<std::string, int> m;
    std::vector<int> ans;
    int i = 0;
    int num = 0;
    while (i < s.size()) {
        num = int(s[i]);
        std::string c(1, s[i]);
        for (int j = i + 1; j < s.size(); ++j) {
            if (m.count(c + s[j])) {
                c += s[j];
                num = m[c];
            } else {
                m[c + s[j]] = m.size() + 128;
                break;
            }
        }
        i += c.length();
        ans.push_back(num);
    }
    return ans;
}

std::string LZWdecode(std::vector<int>& v) {
    std::unordered_map<int, std::string> m;
    std::string s;
    for (int i = 0; i < v.size(); ++i) {
        std::string c;
        if (v[i] < 128) {
            c = char(v[i]);
        } else {
            c = m[v[i]];
        }
        if (i + 1 < v.size()) {
            if (v[1 + i] < 128) {
                m[m.size() + 128] = c + char(v[i + 1]);
            } else {
                if (m.size() + 128 != v[i + 1]) m[m.size() + 128] = c + char(m[v[i + 1]][0]);
                else m[m.size() + 128] = c + c[0];
            }
        }
        s += c;
    }
    return s;
}
