#include <iostream>
#include <vector>
#include <math.h>
#include <string>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);


    int num_words;
    cin >> num_words;

    string pseudosentence;
    getline(cin, pseudosentence);

    for (int word = 0; word < num_words; ++word) {
        if (word > 0) cout << '\n';

        string zeroIndString;
        getline (cin, zeroIndString);

        string s = "$";
        s.append(zeroIndString);
        int n = s.length() - 1;


        int l = 1;
        bool found_repeat = false;
        while ((2*l - 1) <= n / 2) {
            for (int i = 1; i <= n - 3*l + 2; i += l) {

                int m = 0;
                vector<int> repeat_indexes;
                string block = s.substr(i, l);

                // TODO: implement this part properly
                for (int start = i + 2*l - 1; start < i + 4*l - 1; ++start) {
                    if (start > n) break;

                    string potential_repeat = s.substr(start, block.length());
                    if (block == potential_repeat) {
                        m++;
                        repeat_indexes.push_back(start);
                    }
                }

                for (int j = 0; j < m; ++j) {
                    int repeat_start = repeat_indexes[j];
                    int repeat_offset = repeat_start - i;

                    int left = 0;
                    // will typically terminate much earlier
                    for (int p = i - 1; p > 0; --p) {
                        if (s[p] == s[p + repeat_offset]) {
                            left++;
                        } else {
                            break;
                        }
                    }

                    int right = 0;
                    // will typically terminate much earlier
                    for (int p = repeat_start; p <= n; ++p) {
                        if (s[p] == s[p - repeat_offset]) {
                            right++;
                        } else {
                            break;
                        }
                    }

                    if (right + left >= repeat_offset) {
                        found_repeat = true;
                        cout << "YES";
                        break;
                    }
                }
                if (found_repeat) break;
            }
            if (found_repeat) break;
            l = 2 * l;
        }
        if (!found_repeat) cout << "NO";
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
