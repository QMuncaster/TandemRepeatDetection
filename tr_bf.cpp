#include <iostream>
#include <vector>
#include <math.h>
#include <string>
using namespace std;

// 0-indexed string s
bool has_square(string s) {
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int num_words;
    cin >> num_words;

    string pseudosentence;
    getline(cin, pseudosentence);

    for (int word = 0; word < num_words; ++word) {
        string s;
        getline (cin, s);

        if (word > 0) cout << '\n';

        if (has_square(s)) {
            cout << "YES";
        } else {
            cout << "NO";
        }
    }
    return 0;
}