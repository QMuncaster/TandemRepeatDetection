#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <tuple>
using namespace std;

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

    int num_words;
    cin >> num_words;

    string pseudosentence;
    getline(cin, pseudosentence);

    for (int word = 0; word < num_words; ++word) {
        string zeroIndString;
        getline (cin, zeroIndString);

        string s = "$";
        s.append(zeroIndString);

        if (word > 0) cout << '\n';

        if (has_square(s)) {
            cout << "YES";
        } else {
            cout << "NO";
        }
    }

    return 0;
}

/*
g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o tr.o tr.cpp
g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o tr_bf.o tr_bf.cpp

YES EXAMPLES
4
abcabab
eabaebae
abcabsabs
xzyabcdabcd

NO EXAMPLES
4
eabaebad
abcabsabr
asdfghjkl;lkjhgfdsa
oiusoiuoikdajfoiuwqrgqiglukdsjfkldsa

in:
4
dbadc
bbbda
bcadc
bcdaa

ans:
NO
YES
NO
YES

*/
