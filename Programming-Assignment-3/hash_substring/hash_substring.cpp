#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using std::string;
using std::vector;
typedef unsigned long long ull;

ull poly_hash(const string& s, ull p, ull x) {
    ull hash_ = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        hash_ = (hash_ * x + s[i]) % p;
    }
    return hash_;
}

vector<ull> precompute_hashes(const string& t, size_t p_len, ull p, ull x) {
    vector<ull> h(t.size() - p_len + 1);
    string s = t.substr(t.size() - p_len, p_len);
    h[t.size() - p_len] = poly_hash(s, p, x);
    ull y = 1;
    for (int i = 1; i <= p_len; ++i) {
        y = (y * x) % p;
    }
    for (int i = t.size() - p_len - 1; i >=0; --i) {
        h[i] = (x * h[i+1] + t[i] - y * t[i + p_len]) % p;
    }
    return h;
}

vector<int> rabin_karp(const string& t, const string& patt) {
    ull p = 1000000007;
    ull x = std::rand() % p;
    vector<int> result;
    ull p_hash = poly_hash(patt, p, x);
    vector<ull> h = precompute_hashes(t, patt.size(), p, x);
    for (int i = 0; i <= t.size() - patt.size(); ++i) {
        if (p_hash != h[i]) {
            continue;
        }
        bool is_equal = true;
        for (int j = 0; j < patt.size(); ++j) {
            if (patt[j] != t[i+j]) {
                is_equal = false;
                continue;
            }
        }
        if (is_equal)
            result.push_back(i);
    }
    return result;

}

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    //std::vector<int> ans;
    //for (size_t i = 0; i + s.size() <= t.size(); ++i)
    //    if (t.substr(i, s.size()) == s)
    //        ans.push_back(i);
    //return ans;
    return rabin_karp(t, s);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
