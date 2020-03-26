#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <unordered_map>
#include <time.h>
using namespace std;
typedef long long ll;

const double ALPHA = 0.99;
int CHAR_OFFSET = 97;
ll c;
ll kPowc;
vector<string> table;   // 0-indexed
vector<bool> is_square; // 0-indexed
vector<ll> ptr; // 1-indexed
vector<ll> nxt; // 1-indexed

// 0-indexed string s
// O(n^2)
bool has_square_slow(string s) {
    ll n = s.length();
    for (ll i = 1; i <= n/2; ++i) {

        ll count_matched = 0;
        for (ll j = i; j < n; ++j) {
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

void build_table(ll n, ll k) {
    c = ceil(log(pow(n, ALPHA)) / log(k));

    kPowc = pow(k, c);
    table = vector<string>(kPowc, "");

    for (ll group_sz = pow(k, c - 1); group_sz > 0; group_sz = group_sz / k) {
        for (ll i = 0; i < kPowc; ++i) {
            ll group = (i / group_sz) % k;
            table[i] += (char) group + CHAR_OFFSET; 
        }
    }

    for (ll i = 0; i < kPowc; ++i) {
        is_square.push_back(has_square_slow(table[i]));
    }
}

// s must be pseudo-one indexed, i.e. s[0] should be a dummy character
void build_ptr(string s, ll n, ll k) {
    ll first = 0;
    for (ll i = 0; i < kPowc; ++i) {
        if (s.substr(1, c) == table[i]) {
            first = i;
            break;
        }
    }

    ptr = vector<ll>(n + 1, INT32_MAX);
    ptr[1] = first;
    for (ll i = 2; i < n - c + 2; ++i) {
        ll offset = (ll) s[i - 1 + c] - CHAR_OFFSET;
        ptr[i] = (k * ptr[i - 1] + offset) % kPowc;
    }
}

void build_nxt(ll n) {
    nxt = vector<ll>(n + 1, INT32_MAX);
    unordered_map<ll, ll> ptr_to_i;

    for (ll i = n; i > 0; --i) {
        if (ptr_to_i.count(ptr[i])) {
            nxt[i] = ptr_to_i[ptr[i]];
        }

        ptr_to_i[ptr[i]] = i;
    }
}

// s must be pseudo-one indexed, i.e. s[0] should be a dummy character
bool has_square_one_it(string s, ll n, ll l) {
    if (l < 1) return false;

    for (ll i = 1; i <= n - 3*l + 2; i += l) {

        vector<ll> repeats;
        string block = s.substr(i, l);
        ll block_matches = 0;

        for (ll pos = i + 2*l - 1; pos < i + 5*l - 2; ++pos) {
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
            ll k = repeats[j];

            ll suffix_match_length = 0;
            ll lhp = i - 1;
            ll rhp = k - 1;
            while (lhp > 0 && rhp > i + l - 1) {
                if (s[lhp] == s[rhp]) {
                    suffix_match_length++;
                    lhp--;
                    rhp--;

                } else {
                    break;
                }
            }

            ll prefix_match_length = 0;
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
    return false;
}

// s must be pseudo-one indexed, i.e. s[0] should be a dummy character
bool has_square(string s, ll n) {
    for (ll i = 1; i < n - c + 2; ++i) {
        if (is_square[ptr[i]]) {
            return true;
        }
    }

    if (has_square_one_it(s, n, c / 4)) return true;
    if (has_square_one_it(s, n, c / 2)) return true;

    ll l = c;
    while ((2*l - 1) <= n / 2) {
        for (ll i = 1; i <= n - 3*l + 2; i += l) {

            vector<ll> repeats;
            string block = s.substr(i, l);

            // first re-appearance of c in [i + 2l - 1, i + 4l - 2]
            ll f = i;
            while (f < i + 2*l - 1) {
                f = nxt[f];
            }
            if (f > i + 4*l - 2) continue;

            while (f <= i + 4*l - 2) {
                // check if matches block in chunks of c
                ll matches = c;
                ll f_block = f + c;
                while (matches < l) {
                    if (ptr[f] == ptr[i + matches]) {
                        f_block += c;
                        matches += c;

                    } else {
                        break;
                    }
                }
                if (matches == l) {
                    repeats.push_back(f_block - l);
                }

                // repeat for next occurrence
                while (f <= f_block) {
                    f = nxt[f];
                }
            }

            for (size_t j = 0; j < repeats.size(); ++j) {
                ll k = repeats[j];

                ll suffix_match_length = 0;
                ll lhp = i - c;
                ll rhp = k - c;
                while (lhp > 0 && rhp > i + l - 1) {
                    if (ptr[lhp] == ptr[rhp]) {
                        suffix_match_length += c;
                        lhp -= c;
                        rhp -= c;

                    } else if (s[lhp + c - 1] == s[rhp + c - 1]) {
                        suffix_match_length++;
                        lhp--;
                        rhp--;
                    
                    } else {
                        break;
                    }
                }

                ll prefix_match_length = 0;
                lhp = i + l;
                rhp = k + l;
                while (rhp <= n && lhp < k) {
                    if (ptr[lhp] == ptr[rhp]) {
                        prefix_match_length += c;
                        lhp += c;
                        rhp += c;

                    } else if (s[lhp] == s[rhp]) {
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
    // ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll num_words, alphabet_size;
    char base;
    cin >> num_words >> base >> alphabet_size;
    CHAR_OFFSET = (ll) base;

    string pseudosentence;
    getline(cin, pseudosentence);

    for (ll word = 0; word < num_words; ++word) {
        string zeroIndString;
        getline (cin, zeroIndString);

        time_t prev_timer, timer;
        time(&prev_timer);
        double seconds;

        string s = "$";
        s.append(zeroIndString);
        ll n = s.length() - 1;

        time(&timer);
        cout << endl;
        seconds = difftime(timer,prev_timer);
        printf ("%.f ", seconds);
        cout << "finished appending\n";
        time(&prev_timer);

        if (word == 0) {
            build_table(n, alphabet_size);
        } else {
            cout << '\n';
        }

        time(&timer);
        seconds = difftime(timer,prev_timer);
        printf ("%.f ", seconds);
        cout << "finished building table\n";
        time(&prev_timer);
 
        build_ptr(s, n, alphabet_size);

        // for (size_t i = 0; i < ptr.size(); ++i) {
        //     if (ptr[i] < 0 || (ptr[i] > table.size() - 1 && ptr[i] != INT32_MAX)) {
        //         cout << ptr[i] << endl;
        //         cout << "WTF" << endl;
        //         return 1;
        //     }
        // }


        time(&timer);
        seconds = difftime(timer,prev_timer);
        printf ("%.f ", seconds);
        cout << "finished building ptr\n";
        time(&prev_timer);

        build_nxt(n);

        time(&timer);
        seconds = difftime(timer,prev_timer);
        printf ("%.f ", seconds);
        cout << "finished building nxt\n";
        time(&prev_timer);

        if (has_square(s, n)) {
            cout << "YES";
        } else {
            cout << "NO";
        }
        time(&timer);
        seconds = difftime(timer,prev_timer);
        cout << '\n';
        printf ("%.f ", seconds);
        cout << "finished running has_square\n";
        time(&prev_timer);

        

    }

    return 0;
}
