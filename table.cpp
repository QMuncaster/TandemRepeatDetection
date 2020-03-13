#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <iomanip>
#include <unordered_map>
using namespace std;

const vector<char> chars = {'a', 'b', 'c', 'd', 'e',
                            'f', 'g', 'h', 'i', 'j',
                            'k', 'l', 'm', 'n', 'o',
                            'p', 'q', 'r', 's', 't',
                            'u', 'v', 'w', 'x', 'y',
                            'z'};
int k = 3;  // alphabet size
int c = 2;  // generated string size
string input_string = "abcabcabc";

// usage:
// ./table.out input_string k c

/*
./table.out efbcabcdefabcdef 6 2
*/
int main(int argc, char *argv[])
{
    if (argc > 1) {
        input_string = argv[1];
    }

    if (argc > 2) {
        k = stoi(argv[2]);
    }

    if (argc > 3) {
        c = stoi(argv[3]);
    }

    int kPowc = pow(k, c);
    vector<string> table(kPowc, "");

    for (int group_sz = pow(k, c - 1); group_sz > 0; group_sz = group_sz / k) {
        for (int i = 0; i < kPowc; ++i) {
            int group = (i / group_sz) % k;
            table[i] += chars[group]; 
        }
    }

    for (size_t i = 0; i < table.size(); ++i) {
        cout << setw(3) << i << ' ';
        cout << table[i];
        cout << endl;
    }
    cout << endl;

    int N = input_string.length();
    vector<int> ptr(N, -1);
    
    for (int i = 0; i < kPowc; ++i) {
        if (input_string.substr(0, c) == table[i]) {
            ptr[0] = i;
            break;
        }
    }

    for (int i = 0; i <= N - c; ++i) {
        ptr[i+1] = (k * ptr[i] + input_string[i+c] - 'a')%kPowc; // TODO: unhardcode to 'a'
    }

    vector<int> nxt(N, INT32_MAX);
    unordered_map<int, int> ptr_to_si;

    for (int i = N - c + 1; i >= 0; --i) {
        if (ptr_to_si[ptr[i]]) {
            nxt[i] = ptr_to_si[ptr[i]];
        }

        ptr_to_si[ptr[i]] = i + 1;
    }

    for (size_t i = 0; i < ptr.size(); ++i) {
        cout << setw(2) << i + 1 << ' ';
        cout << setw(2) << input_string[i] << ' ';
        cout << setw(3) << ptr[i] << ' ';

        string nxt_val = (nxt[i] == INT32_MAX) ? "I" : to_string(nxt[i]);
        cout << setw(3) << nxt_val;
        cout << endl;
    }
    cout << endl;

    return 0;
}

/*
file=table && g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o table.out project/${file}.cpp
*/
