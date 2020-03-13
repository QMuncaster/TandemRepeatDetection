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

        string s;
        getline (cin, s);

        int n = s.length();
        int found_repeat = false;
        for (int i = 1; i <= n/2; ++i) {

            int count_matched = 0;
            for (int j = i; j < n; ++j) {
                if (s[j] == s[j - i]) {
                    count_matched++;

                    if (count_matched == i) {
                        found_repeat = true;
                        cout << "YES";
                        break;
                    }
                } else {
                    count_matched = 0;
                }
            }
            
            if (found_repeat) break;
        }

        if (!found_repeat) cout << "NO";
    }
    return 0;
}

/*
g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o tr_bf.out project/tr_bf.cpp
*/
