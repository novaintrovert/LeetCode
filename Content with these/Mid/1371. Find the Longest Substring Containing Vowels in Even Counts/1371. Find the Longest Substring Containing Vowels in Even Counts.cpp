/*1371. Find the Longest Substring Containing Vowels in Even Counts
Medium

Given the string s, return the size of the longest substring containing each vowel an even number of times.
That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

Input: s = "eleetminicoworoep"
Output: 13
Explanation:
The longest substring is "leetminicowor" which contains two each of the vowels:
e, i and o and zero of the vowels: a and u.

Input: s = "leetcodeisgreat"
Output: 5
Explanation:
The longest substring is "leetc" which contains two e's.

Input: s = "bcbcbc"
Output: 6
Explanation:
In this case, the given string "bcbcbc" is the longest
because all vowels: a, e, i, o and u appear zero times.

Constraints:
    1 <= s.length <= 5 x 10^5
    s contains only lowercase English letters.
*/

/*
class Solution {
public:
    int findTheLongestSubstring(string s) {

    }
};
*/

#include<iostream>
#include<ctime>
#include<vector>
#include<random>
#include<chrono>
#include<stack>
#include<map>
#include<set>
#include<algorithm>
#include<string>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<deque>
#include<fstream>
#include<tuple>
#include<bitset>
#include<cstring>

using namespace std;
using namespace chrono;

int findTheLongestSubstring_brute(string s) {
    int max_length = 0, curr_max;

    int is_wanted[26]; for (int i = 0; i < 26; i++) { is_wanted[i] = -1; }
    is_wanted[0] = 0, is_wanted[4] = 1, is_wanted[8] = 2, is_wanted[14] = 3, is_wanted[20] = 4;

    bool is_odd[5];

    for (int i = 0, temp; i < s.size(); i++) {
        for (int m = 0; m < 5; m++) { is_odd[m] = 0; }
        curr_max = 0;

        for (int j = i; j < s.size(); j++) {
            if (is_wanted[s[j] - 97] >= 0) {
                if (is_odd[is_wanted[s[j] - 97]] == 0) {
                    is_odd[is_wanted[s[j] - 97]] = 1;
                }
                else {
                    is_odd[is_wanted[s[j] - 97]] = 0;
                }
            }

            if (is_odd[0] == 0 && is_odd[1] == 0 && is_odd[2] == 0 && is_odd[3] == 0 && is_odd[4] == 0) {
                temp = j - i + 1;
                if (temp > curr_max) { curr_max = temp; }
            }
        }

        if (curr_max > max_length) { max_length = curr_max; }
    }

    return max_length;
}

int findTheLongestSubstring_others(string s) {
    vector<int> earliest(32, -1);
    earliest[0] = 0;

    int mask = 0, best = 0, bit, i = 0;
    for (char c: s) {
        ++i;
        switch(c) {
            case 'a':
                bit = 1;
                break;
            case 'e':
                bit = 2;
                break;
            case 'i':
                bit = 4;
                break;
            case 'o':
                bit = 8;
                break;
            case 'u':
                bit = 16;
                break;
            default:
                bit = 0;
                break;
        }
        mask ^= bit;

        if (earliest[mask] != -1) {
            best = max(best, i-earliest[mask]);
        } else {
            earliest[mask] = i;
        }
    }
    return best;
}

int findTheLongestSubstring_1_0(string s) {
    int is_wanted[26]; for (int i = 0; i < 26; i++) { is_wanted[i] = -1; }
    is_wanted[0] = 0, is_wanted[4] = 1, is_wanted[8] = 2, is_wanted[14] = 3, is_wanted[20] = 4;
    int key[5]; key[0] = 1, key[1] = 2, key[2] = 4, key[3] = 8, key[4] = 16;

    int test = 0;

    bool is_positive[5]; for (int i = 0; i < 5; i++) { is_positive[i] = 1; }// is_positive[0] is not used

    int length = s.size();
    int transformed_string[length + 1];
    transformed_string[0] = 0;
    for (int i = 1; i <= length; i++) { transformed_string[i] = -1; }
    for (int i = 0; i < length; i++) {
        //cout << "i = " << i << "\n";
        if (is_wanted[s[i] - 97] < 0) {
            //cout << "~0\n";
            transformed_string[i + 1] = 0;
        }
// = {r, s, t, c, a, c, k, u, a, w}
        else {
            //cout << "~1\n";
            transformed_string[i + 1] = (is_positive[is_wanted[s[i] - 97]] == 1)? key[is_wanted[s[i] - 97]]: 0 - key[is_wanted[s[i] - 97]];
            is_positive[is_wanted[s[i] - 97]] ^= 1;// XOR operation
        }
        //for (int i = 0; i < 5; i++) { cout << is_positive[i] << " "; } cout << "\n";
        //for (int i = 0; i < length; i++) { cout << transformed_string[i] << " "; } cout << "\n";
    }

    if (test > 0) {cout << "\n";
    for (int i = 0; i <= length; i++) { cout << transformed_string[i] << " "; }
    cout << "\n\n";}

    for (int i = 1; i <= length; i++) { transformed_string[i] += transformed_string[i - 1]; }

    if (test > 0) {for (int i = 0; i <= length; i++) { cout << transformed_string[i] << " "; }
    cout << "\n\n";}

    int first_idx[32]; for (int i = 0; i < 32; i++) { first_idx[i] = -1; }
    for (int i = 0, counter = 0; i <= length && counter < 32; i++) {
        if (first_idx[transformed_string[i]] < 0) {
            first_idx[transformed_string[i]] = i;
            counter++;
        }
    }

    if (test > 0) {cout << "\n\n";
    for (int i = 0; i < 32; i++) {
        cout << first_idx[i] << " ";
        if ((i + 1) % 10 == 0) cout << "\n";
    }
    cout << "\n\n";}

    //i + 1 > curr_max
    int curr_max = 0;
    for (int i = length, counter = 0, temp; i > 0 && curr_max < i + 1; i--) {
        if (test > 0) {cout << "i = " << i << "\n";}
        if (first_idx[transformed_string[i]] >= 0) {
            if (test > 0) {cout << "---" << first_idx[transformed_string[i]] << "\n";}

            temp = i - first_idx[transformed_string[i]];

            /*if (first_idx[transformed_string[i]] == 0) {
                if (is_wanted[s[0] - 97] < 0) { temp++; }
            }*/

            if (temp > curr_max) {
                if (test > 0) {
                    cout << i << " " << first_idx[transformed_string[i]] << "\n";
                    cout << "curr_max = " << temp << "\n";
                }
                curr_max = temp;
            }
            first_idx[transformed_string[i]] = -1;
        }
    }

    if (test > 0) {cout << "\n\n";
    for (int i = 0; i < 32; i++) {
        cout << first_idx[i] << " ";
        if ((i + 1) % 10 == 0) cout << "\n";
    }
    cout << "\n\n";}

    return curr_max;
}

int findTheLongestSubstring_1_1(string s) {
    int length = s.size();

    int is_wanted[26]; for (int i = 0; i < 26; i++) { is_wanted[i] = -1; }
    is_wanted[0] = 0, is_wanted[4] = 1, is_wanted[8] = 2, is_wanted[14] = 3, is_wanted[20] = 4;

    int key[5]; key[0] = 1, key[1] = 2, key[2] = 4, key[3] = 8, key[4] = 16;

    bool is_positive[5]; for (int i = 0; i < 5; i++) { is_positive[i] = 1; }

    int transformed_string[length + 1];
    transformed_string[0] = 0; for (int i = 1; i <= length; i++) { transformed_string[i] = -1; }

    for (int i = 0; i < length; i++) {
        if (is_wanted[s[i] - 97] < 0) { transformed_string[i + 1] = 0; }
        else {
            transformed_string[i + 1] = (is_positive[is_wanted[s[i] - 97]] == 1)? key[is_wanted[s[i] - 97]]: 0 - key[is_wanted[s[i] - 97]];

            is_positive[is_wanted[s[i] - 97]] ^= 1;
        }
    }

    for (int i = 1; i <= length; i++) { transformed_string[i] += transformed_string[i - 1]; }

    int first_idx[32]; for (int i = 0; i < 32; i++) { first_idx[i] = -1; }
    for (int i = 0, counter = 0; i <= length && counter < 32; i++) {
        if (first_idx[transformed_string[i]] < 0) {
            first_idx[transformed_string[i]] = i;
            counter++;
        }
    }

    int curr_max = 0;
    for (int i = length, temp; i > 0 && curr_max < i + 1; i--) {
        if (first_idx[transformed_string[i]] >= 0) {
            temp = i - first_idx[transformed_string[i]];

            if (temp > curr_max) { curr_max = temp; }

            first_idx[transformed_string[i]] = -1;
        }
    }

    return curr_max;
}


//  I WILL MOST LIKELY TO RUN INTO ALL KINDS OF PROBLEMS IF I DO NOT BUILD A BRUTEFORCE & TEST A BIT
//  NO MATTER HOW CONFIDENT I MIGHT HAVE ON THAT ALGORITHM
int main(){
    srand(time(0));int length = 500000, lower_range = 97, upper_range = 122, display = 0, input = 1;
    string wtf = "";
    string w1, w2;
    auto sp1 = chrono::steady_clock::now(); auto ep1 = chrono::steady_clock::now(); auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now(); auto ep2 = chrono::steady_clock::now(); auto dif2 = ep2 - sp2;

for (int m = 1; m <= 1000; m++) {if (m % 100 == 0) {cout << "m = " << m << "\n";}

    if (input == 1) {
        wtf.reserve(length);
        for (int i = 0; i < length; i++) {
            wtf.push_back(rand() % (upper_range - lower_range + 1) + lower_range);
        }
    }
    if (display == 1) {
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    w1 = wtf, w2 = wtf;

    sp1 = chrono::steady_clock::now();
    int s = findTheLongestSubstring_others(w1);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;
    //cout << "s = " << s << "\n";

    sp2 = chrono::steady_clock::now();
    int ss = findTheLongestSubstring_1_1(w2);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;
    //cout << "ss = " << ss << "\n";

    if (s != ss) {
        cout << "\nm = " << m << "\n\n" << wtf;
        cout << "\n\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n\n";
        cout << "s = " << s << "\n";
        cout << "ss = " << ss << "\n";
        break;
    }

wtf.clear();}

cout << duration <double, milli> (dif1).count() << " ms" << "\n";
cout << duration <double, milli> (dif2).count() << " ms" << "\n";

    return 0;
}


    /*sort(begin(a),
         end(a),
         [](const auto &m, const auto &n){
            return m[1] < n[1];
            }
        );*/


