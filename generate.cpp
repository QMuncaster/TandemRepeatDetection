#include <iostream>
#include <vector>
#include <math.h>
#include <string>
using namespace std;

const vector<char> chars = {'a', 'b', 'c', 'd', 'e',
                            'f', 'g', 'h', 'i', 'j',
                            'k', 'l', 'm', 'n', 'o',
                            'p', 'q', 'r', 's', 't',
                            'u', 'v', 'w', 'x', 'y',
                            'z'};
const int alphabet_size = 26;

// usage:
// ./generate.out number_of_words word_length
int main(int argc, char *argv[])
{
    int N = 100;
    if (argc > 1) {
        N = stoi(argv[1]);
    }

    int str_length = 5;
    if (argc > 2) {
        str_length = stoi(argv[2]);
    }

    cout << N;
    for (int i = 0; i < N; ++i) {
        string out;
        for (int c = 0; c < str_length; ++c) {
            out.push_back(chars[rand() % alphabet_size]);
        }

        cout << '\n' << out;
    }

    return 0;
}

/*
file=generate
g++ -W -Wall -pedantic --std=c++17 -ggdb3 -o generate.out project/${file}.cpp
*/
