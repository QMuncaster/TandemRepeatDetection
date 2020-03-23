#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <unordered_map>
using namespace std;

/*
1 6
efbcabcdefabcdef

g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o tr_fast.o tr_fast.cpp
./tr_fast.o < temp

29
31
8
*/

// TODO: change to +33
// will assume chars start at "!", so will have to fix/remove some of the test files
const int CHAR_OFFSET = 97;
const double ALPHA = 0.99;
int c;
int kPowc;
vector<string> table;   // 0-indexed
vector<bool> is_square; // 0-indexed
vector<int> ptr;  // 1-indexed
vector<int> nxt; // 1-indexed

// 0-indexed string s
// O(n^2)
bool has_square_slow(string s) {
    int n = s.length();
    for (int i = 1; i <= n/2; ++i) {

        int count_matched = 0;
        for (int j = i; j < n; ++j) {
            if (s[j] == s[j - i]) {
                count_matched++;

                if (count_matched == i) {
                    return true;
                }
            } else {
                count_matched = 0;
            }
        }
    }
    return false;
}

void build_table(int n, int k) {
    c = ceil(log(pow(n, ALPHA)) / log(k));

    kPowc = pow(k, c);
    table = vector<string>(kPowc, "");

    for (int group_sz = pow(k, c - 1); group_sz > 0; group_sz = group_sz / k) {
        for (int i = 0; i < kPowc; ++i) {
            int group = (i / group_sz) % k;
            table[i] += (char) group + CHAR_OFFSET; 
        }
    }

    for (int i = 0; i < kPowc; ++i) {
        is_square.push_back(has_square_slow(table[i]));
    }
}

// s must be pseudo-one indexed, i.e. s[0] should be a dummy character
void build_ptr(string s, int n, int k) {
    int first = 0;
    for (int i = 0; i < kPowc; ++i) {
        if (s.substr(1, c) == table[i]) {
            first = i;
            break;
        }
    }

    ptr = vector<int>(n + 1);
    ptr[1] = first;
    for (int i = 2; i < n - c + 2; ++i) {
        int offset = (int) s[i - 1 + c] - CHAR_OFFSET;
        ptr[i] = (k * ptr[i - 1] + offset) % kPowc;
    }
}

void build_nxt(string s, int n) {
    nxt = vector<int>(n + 1, INT32_MAX);

    unordered_map<int, int> ptr_to_i;

    for (int i = n; i > 0; --i) {
        if (ptr_to_i.count(ptr[i])) {
            nxt[i] = ptr_to_i[ptr[i]];
        }

        ptr_to_i[ptr[i]] = i;
    }
}

// s must be pseudo-one indexed, i.e. s[0] should be a dummy character
bool has_square(string s) {
    int n = s.length() - 1;
    int l = 1;

    while ((2*l - 1) <= n / 2) {
        for (int i = 1; i <= n - 3*l + 2; i += l) {

            vector<int> repeats;
            string block = s.substr(i, l);
            int block_matches = 0;

            for (int pos = i + 2*l - 1; pos < i + 5*l - 2; ++pos) {
                if (pos > n) break;

                if (s[pos] == block[block_matches]) {
                    block_matches++;

                } else {
                    block_matches = 0;
                }

                if (block_matches == l) {
                    repeats.push_back(pos - l + 1);
                    block_matches = 0;
                }
            }

            for (size_t j = 0; j < repeats.size(); ++j) {
                int k = repeats[j];

                int suffix_match_length = 0;
                int lhp = i - 1;
                int rhp = k - 1;
                while (lhp > 0 && rhp > i + l - 1) {
                    if (s[lhp] == s[rhp]) {
                        suffix_match_length++;
                        lhp--;
                        rhp--;

                    } else {
                        break;
                    }
                }

                int prefix_match_length = 0;
                lhp = i + l;
                rhp = k + l;
                while (rhp <= n && lhp < k) {
                    if (s[lhp] == s[rhp]) {
                        prefix_match_length++;
                        lhp++;
                        rhp++;

                    } else {
                        break;
                    }
                }

                if (prefix_match_length + suffix_match_length >= k - i - l) {
                    return true;
                }
            }
        }
        l = 2 * l;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int num_words, alphabet_size;
    cin >> num_words >> alphabet_size;

    string pseudosentence;
    getline(cin, pseudosentence);

    for (int word = 0; word < num_words; ++word) {
        string zeroIndString;
        getline (cin, zeroIndString);

        string s = "$";
        s.append(zeroIndString);
        int n = s.length() - 1;

        if (word == 0) {
            build_table(n, alphabet_size);
        } else {
            cout << '\n';
        }
 
        build_ptr(s, n, alphabet_size);
        build_nxt(s, n);

        if (has_square(s)) {
            cout << "YES";
        } else {
            cout << "NO";
        }
    }

    return 0;
}
