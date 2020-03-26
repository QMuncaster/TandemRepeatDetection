#include <iostream>
#include <vector>
#include <math.h>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    int N = 20;
    int str_length = 20;
    int alphabet_size = 20;

    if (argc == 1) {
        cout << "Usage: ./generate.out num_words word_length alphabet_size\n"
                "Uses random ASCII chars starting with !\n"
                "Max alphabet size is 94\n"
                "Proceeding with defaults\n\n";
    }       

    if (argc > 1) {
        N = stoi(argv[1]);
    }

    if (argc > 2) {
        str_length = stoi(argv[2]);
    }

    if (argc > 3) {
        alphabet_size = stoi(argv[3]);
        if (alphabet_size > 94) return 1;
    }

    cout << N << " ! " << alphabet_size;
    for (int i = 0; i < N; ++i) {
        string out;
        for (int c = 0; c < str_length; ++c) {
            // shift chars to begin at '!'
            out.push_back((char) (rand() % alphabet_size + 33));
        }

        cout << '\n' << out;
    }

    return 0;
}