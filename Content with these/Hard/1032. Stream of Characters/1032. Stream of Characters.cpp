/*1032. Stream of Characters
Hard

Implement the StreamChecker class as follows:

    StreamChecker(words): Constructor, init the data structure with the given words.

    query(letter): returns true if and only if for some k >= 1,
    the last k characters queried (in order from oldest to newest,
    including this letter just queried) spell one of the words in the given list.

Example:
StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
streamChecker.query('a');          // return false
streamChecker.query('b');          // return false
streamChecker.query('c');          // return false
streamChecker.query('d');          // return true, because 'cd' is in the wordlist
streamChecker.query('e');          // return false
streamChecker.query('f');          // return true, because 'f' is in the wordlist
streamChecker.query('g');          // return false
streamChecker.query('h');          // return false
streamChecker.query('i');          // return false
streamChecker.query('j');          // return false
streamChecker.query('k');          // return false
streamChecker.query('l');          // return true, because 'kl' is in the wordlist

Note:
    1 <= words.length <= 2000
    1 <= words[i].length <= 2000
    Words will only consist of lowercase English letters.
    Queries will only consist of lowercase English letters.
    The number of queries is at most 40000.
*/

/*
class StreamChecker {
public:
    StreamChecker(vector<string>& words) {

    }

    bool query(char letter) {

    }
};
*/

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
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
#include <bits/stdc++.h>

using namespace std;
using namespace chrono;


class StreamChecker_I_DID_NOT_UNDERSTAND_IT_CORRECTLY {
public:
    unordered_set<char> existed;

    StreamChecker(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            auto find_it = existed.find(words[i][words[i].size() - 1]);
            if (find_it == existed.end()) {
                existed.insert(words[i][words[i].size() - 1]);
            }
        }
    }

    bool query(char letter) {
        auto find_it = existed.find(letter);
        if (find_it != existed.end()) { return true; }
        return false;
    }
};



// WHAT?! BRUTE IS FASTER THAN...?! ALL RIGHT THEN, IMPROVE BRUTE
// NO. brute got better performance bc in testing i made
// if (window.size() > max_length) { window.erase(window.begin()); }
// into
// if (window.size() > 10) { window.erase(window.begin()); }
// which will make this algorithm vulnerable to attack
class StreamChecker_brute {
public:
    int test = 0;
    int length, max_length = 0, max_idx = -1, counter;
    set<int> length_collection;
    unordered_map<int, unordered_set<string>> length_to_string;

    map<int, char> window;
    int timer = 0;
    string temp_string;

    StreamChecker_brute(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            length = words[i].size();
            if (length > max_length) { max_length = length, max_idx = i; }

            auto find_length = length_collection.find(length);
            if (find_length == length_collection.end()) {
                length_collection.insert(length);
                length_to_string.insert({length, unordered_set<string> ()});
            }

            auto find_word = length_to_string[length].find(words[i]);
            if (find_word == length_to_string[length].end()) {
                length_to_string[length].insert(words[i]);
            }
        }

        /*cout << "length_collection:\n";
        for (auto i = length_collection.begin(); i != length_collection.end(); ++i) {
            cout << *i << " ";
        }
        cout << "\n\n";

        cout << "length_to_string:\n";
        for (auto i = length_to_string.begin(); i != length_to_string.end(); ++i) {
            cout << i->first << ": ";
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                cout << *j << " ";
            }
            cout << "\n";
        }
        cout << "\nmax_length = " << max_length;
        cout << "\n\n";*/
    }

    bool query(char letter) {
        window.insert({timer, letter});
        timer++;
        if (window.size() > max_length) { window.erase(window.begin()); }

        if (test > 0) {
            cout << "window:\n";
            for (auto i = window.begin(); i != window.end(); ++i) {
                cout << i->second << " ";
            }
            cout << "\n\n";
        }

        for (auto i = length_collection.begin(); i != length_collection.end() && window.size() >= *i; ++i) {

            temp_string.clear();
            counter = *i;

            auto start_here = window.rbegin();
            while (start_here != window.rend() && counter > 0) {
                ++start_here;
                counter--;
            }

            start_here--;

            while (start_here != window.rbegin()){
                temp_string.push_back(start_here->second);
                start_here--;
            }

            temp_string.push_back(start_here->second);

            if (test > 0) { cout << "temp_string = " << temp_string << "\n"; }

            auto find_it = length_to_string[*i].find(temp_string);
            if (find_it != length_to_string[*i].end()) { return 1; }
        }

        return 0;
    }

    void check_window () {
        cout << "\nwindow:\n";
        for (auto i = window.begin(); i != window.end(); i++) {
            cout << i->second << " ";
        }
        cout << "\n";
    }
};

class StreamChecker_brute_1 {
public:
    int length, max_length = 0, counter;
    map<int, unordered_set<string>> length_to_string;
    map<int, char> window;

    int timer = 0;
    string temp_string;

    StreamChecker_brute_1(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            length = words[i].size();
            if (length > max_length) { max_length = length; }

            auto find_length = length_to_string.find(length);
            if (find_length == length_to_string.end()) {
                length_to_string.insert({length, unordered_set<string> ()});
            }

            auto find_word = length_to_string[length].find(words[i]);
            if (find_word == length_to_string[length].end()) {
                length_to_string[length].insert(words[i]);
            }
        }
    }

    bool query(char letter) {
        window.insert({timer, letter});
        timer++;
        if (window.size() > max_length) { window.erase(window.begin()); }

        for (auto i = length_to_string.begin(); i != length_to_string.end() && window.size() >= i->first; ++i) {
            temp_string.clear();
            counter = i->first;

            auto start_here = window.rbegin();
            while (start_here != window.rend() && counter > 1) {
                ++start_here;
                counter--;
            }

            while (start_here != window.rbegin()){
                temp_string.push_back(start_here->second);
                start_here--;
            }

            temp_string.push_back(start_here->second);

            auto find_it = length_to_string[i->first].find(temp_string);
            if (find_it != length_to_string[i->first].end()) { return 1; }
        }

        return 0;
    }

    void check_window () {
        cout << "\nwindow:\n";
        for (auto i = window.begin(); i != window.end(); i++) {
            cout << i->second << " ";
        }
        cout << "\n";
    }
};



// TOO SLOW
class StreamChecker_1_0 {
public:
    int test = 0;
    int length, max_length = 0, temp_idx;
    set<int> length_collection;
    unordered_map<int, unordered_set<string>> length_to_string;

    vector<char> window;
    bool first_round_complete = 0, found;
    int finish = 0;

    string temp_string;

    StreamChecker_1_0(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            length = words[i].size();
            if (length > max_length) { max_length = length; }

            auto find_length = length_collection.find(length);
            if (find_length == length_collection.end()) {
                length_collection.insert(length);
                length_to_string.insert({length, unordered_set<string> ()});
            }

            auto find_word = length_to_string[length].find(words[i]);
            if (find_word == length_to_string[length].end()) {
                length_to_string[length].insert(words[i]);
            }
        }

        window.reserve(max_length);
        for (int i = 0; i < max_length; i++) { window.push_back('a'); }

        if (test > 0) {
            cout << "length_collection:\n";
            for (auto i = length_collection.begin(); i != length_collection.end(); ++i) { cout << *i << " "; }
            cout << "\n\n";

            cout << "length_to_string:\n";
            for (auto i = length_to_string.begin(); i != length_to_string.end(); ++i) {
                cout << i->first << ": ";
                for (auto j = i->second.begin(); j != i->second.end(); ++j) { cout << *j << " "; }
                cout << "\n";
            }
            cout << "\nmax_length = " << max_length;
            cout << "\n\n";
        }
    }

    bool query(char letter) {
        if (test > 0) { cout << "\nletter = " << letter << "\nfinish = " << finish << "\n"; }

        window[finish] = letter;
        found = 0;

        if (test > 0) {
            cout << "window:\n";
            for (int i = 0; i < max_length; i++) { cout << window[i] << " "; }
            cout << "\nfinish = " << finish << "\n\n";
        }

        if (first_round_complete == 1) {
            for (auto i = length_collection.begin(); i != length_collection.end(); ++i) {
                temp_string.clear();

                if (test > 0) { cout << "*i = " << *i << "\n"; }

                if (*i > finish + 1) {
                    for (int j = max_length - (*i - finish - 1); j < max_length; j++) { temp_string.push_back(window[j]); }

                    if (test > 0) { cout << "temp_string = " << temp_string << "\n"; }

                    for (int j = 0; j <= finish; j++) { temp_string.push_back(window[j]); }
                }

                else { for (int j = finish + 1 - *i; j <= finish; j++) { temp_string.push_back(window[j]); } }

                if (test > 0) { cout << "temp_string = " << temp_string << "\n"; }

                auto find_string = length_to_string[*i].find(temp_string);
                if (find_string != length_to_string[*i].end()) { found = 1; break; }
            }
        }

        else if (finish + 1 >= *length_collection.begin()) {
            for (auto i = length_collection.begin(); i != length_collection.end() && finish + 1 >= *i; ++i) {
                temp_string.clear();
                temp_idx = *i;

                if (test > 0) { cout << "*i = " << *i << "\n"; }

                for (int j = finish - temp_idx + 1; j <= finish; j++) {
                    temp_string.push_back(window[j]);
                }

                if (test > 0) { cout << "temp_string = " << temp_string << "\n"; }

                auto find_string = length_to_string[temp_idx].find(temp_string);
                if (find_string != length_to_string[temp_idx].end()) { found = 1; break; }
            }
        }

        finish++;
        if (finish == max_length) {
            if (first_round_complete == 0) { first_round_complete = 1; }
            finish = 0;
        }

        if (test > 0) { cout << "\n-------------end of this query--------------\nfinish = " << finish << "\n\n"; }

        return found;
    }

    void check_window() {
        cout << "\nwindow window window:\n";
        for (int i = 0; i < window.size(); i++) {
            cout << window[i] << ", ";
        }
        cout << "\n\n";
    }
};

// FASTER THAN 1_0, BUT STILL TOO SLOW
class StreamChecker {
public:
    int test = 0;
    int length, max_length = 0, double_max_length, temp_idx;
    map<int, unordered_set<string>> length_to_string;

    bool choose_0_not_1 = 1;
    bool found;

    string input_string_0;
    string input_string_1;
    string temp_string;

    StreamChecker(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            length = words[i].size();
            if (length > max_length) { max_length = length; }

            auto find_length = length_to_string.find(length);
            if (find_length == length_to_string.end()) {
                length_to_string.insert({length, unordered_set<string> ()});
            }

            auto find_word = length_to_string[length].find(words[i]);
            if (find_word == length_to_string[length].end()) {
                length_to_string[length].insert(words[i]);
            }
        }

        double_max_length = max_length * 2;

        if (test > 0) {
            /*cout << "length_collection:\n";
            for (auto i = length_collection.begin(); i != length_collection.end(); ++i) { cout << *i << " "; }
            cout << "\n\n";*/

            cout << "length_to_string:\n";
            for (auto i = length_to_string.begin(); i != length_to_string.end(); ++i) {
                cout << i->first << ": ";
                for (auto j = i->second.begin(); j != i->second.end(); ++j) { cout << *j << " "; }
                cout << "\n";
            }
            cout << "\nmax_length = " << max_length;
            cout << "\n\n";
        }
    }

    bool query(char letter) {
        if (test > 0) { cout << "\nletter = " << letter << "\n"; }
        found = 0;

        /*input_string_0.push_back(letter);

        for (auto i = length_collection.begin(); i != length_collection.end() && input_string_0.size() >= *i; ++i) {
            temp_idx = *i;

            temp_string = input_string_0.substr(input_string_0.size() - temp_idx, temp_idx);

            auto find_string = length_to_string[temp_idx].find(temp_string);
            if (find_string != length_to_string[temp_idx].end()) { found = 1; break; }
        }*/

        if (choose_0_not_1 == 1) {
            input_string_0.push_back(letter);

            for (auto i = length_to_string.begin(); i != length_to_string.end() && input_string_0.size() >= i->first; ++i) {
                temp_idx = i->first;

                temp_string = input_string_0.substr(input_string_0.size() - temp_idx, temp_idx);

                auto find_string = length_to_string[temp_idx].find(temp_string);
                if (find_string != length_to_string[temp_idx].end()) { found = 1; break; }
            }

            if (input_string_0.size() > double_max_length) {
                input_string_1 = input_string_0.substr(input_string_0.size() - max_length, input_string_0.size());
                input_string_0.clear();
                choose_0_not_1 = 0;
            }
        }

        else {
            input_string_1.push_back(letter);

            for (auto i = length_to_string.begin(); i != length_to_string.end() && input_string_1.size() >= i->first; ++i) {
                temp_idx = i->first;

                temp_string = input_string_1.substr(input_string_1.size() - temp_idx, temp_idx);

                auto find_string = length_to_string[temp_idx].find(temp_string);
                if (find_string != length_to_string[temp_idx].end()) { found = 1; break; }
            }

            if (input_string_1.size() > double_max_length) {
                input_string_0 = input_string_1.substr(input_string_1.size() - max_length, input_string_1.size());
                input_string_1.clear();
                choose_0_not_1 = 1;
            }
        }

        return found;
    }
};



class StreamChecker_worked_1_0 {
public:
    int test = 0;

    // max length of words[i]. determine length of curr_letters
    int max_length = 0, unidentical_lengths;

    // temp helper
    bool found = 0;
    int length, temp, temp_sum, counter;
    char temp_letter;
    string temp_string;

    // mirror of words
    vector<string> words_words;

    // record & maintaining the current letters under consideration
    bool first_round_complete = 0;
    int finish = 0;
    vector<char> curr_letters;

    // sum[i].first is sum of the most recent N letters, N = sum[i].second
    vector<pair<int, int>> sum;

    // record all known sums in words
    // proceed further only when some sum is present in this to avoid unnecessary query
    unordered_map<int, unordered_set<int>> existed_sum_to_length;

    // the big map
    map<int, unordered_map<char, unordered_map<int, unordered_set<int>>>> length_lastLetter_sum_string;

    StreamChecker_worked_1_0(vector<string>& words) {
        words_words.reserve(words.size());

        for (int i = 0; i < words.size(); i++) {
            words_words.push_back(words[i]);

            length = words[i].size();
            if (length > max_length) { max_length = length; }

            temp = 0;
            for (int j = 0; j < length; j++) { temp += words[i][j]; }

            auto check_existed = existed_sum_to_length.find(temp);
            if (check_existed == existed_sum_to_length.end()) {
                existed_sum_to_length.insert({temp, unordered_set<int>()});
            }
            existed_sum_to_length[temp].insert(length);

            auto find_length = length_lastLetter_sum_string.find(length);
            if (find_length == length_lastLetter_sum_string.end()) {
                length_lastLetter_sum_string.insert({length, unordered_map<char, unordered_map<int, unordered_set<int>>> ()});
            }

            temp_letter = words[i][length - 1];

            auto find_last_letter = length_lastLetter_sum_string[length].find(temp_letter);
            if (find_last_letter == length_lastLetter_sum_string[length].end()) {
                length_lastLetter_sum_string[length].insert({temp_letter, unordered_map<int, unordered_set<int>> ()});
            }

            auto find_sum = length_lastLetter_sum_string[length][temp_letter].find(temp);
            if (find_sum == length_lastLetter_sum_string[length][temp_letter].end()) {
                length_lastLetter_sum_string[length][temp_letter].insert({temp, unordered_set<int> ()});
            }

            length_lastLetter_sum_string[length][temp_letter][temp].insert(i);
        }

        curr_letters.resize(max_length, 'a');

        unidentical_lengths = length_lastLetter_sum_string.size();

        sum.resize(unidentical_lengths, {0, 0});

        temp = 0;
        for (auto i = length_lastLetter_sum_string.begin(); i != length_lastLetter_sum_string.end(); ++i) {
            sum[temp].second = i->first;
            temp++;
        }

        //display_info();
    }

    bool query(char letter) {
        if (test > 0) {
            cout << "\n\nQUERY\n\n";
            cout << "letter = " << letter << "\n";
            cout << "finish = " << finish << "\n";
            cout << "before subtraction:\n";
            for (int i = 0; i < sum.size(); i++) { cout << sum[i].first << " " << sum[i].second << ", "; }
            cout << "\n\ncurr_letters:\n";
            for (int i = 0; i < curr_letters.size(); i++) { cout << curr_letters[i] << " "; }
            cout << "\n";
        }

        // subtract last letters from sum[i]
        if (first_round_complete == 0) {
            for (int i = 0; i < sum.size(); i++) {
                if (sum[i].second <= finish) {
                    sum[i].first -= curr_letters[finish - sum[i].second];

                    if (test > 0) { cout << "\nsum[" <<i << "].first -= curr_letters[" << finish - sum[i].second << "]\n"; }
                }
            }
        }

        else {
            for (int i = 0; i < sum.size(); i++) {
                if (sum[i].second <= finish) {
                    sum[i].first -= curr_letters[finish - sum[i].second];
                    if (test > 0) { cout << "\nsum[" << i << "].first -= curr_letters[" << finish - sum[i].second << "]\n"; }
                }

                else {
                    sum[i].first -= curr_letters[max_length - (sum[i].second - finish)];
                    if (test > 0) { cout << "\nsum[" << i << "].first -= curr_letters[" << max_length - (sum[i].second - finish) << "]\n"; }
                }
            }
        }

        if (test > 0) {
            cout << "\nafter subtraction:\n";
            for (int i = 0; i < sum.size(); i++) {
                cout << sum[i].first << " " << sum[i].second << ", ";
            }
            cout << "\n\ncurr_letters:\n";

            for (int i = 0; i < curr_letters.size(); i++) {
                cout << curr_letters[i] << " ";
            }
            cout << "\n";
        }

        // put letter in curr_letters
        curr_letters[finish] = letter;
        finish++;
        if (finish == max_length) { finish = 0; first_round_complete = 1; }

        if (test > 0) {
            cout << "\nafter updating:\n";
            cout << "finish = " << finish << "\n";
            for (int i = 0; i < curr_letters.size(); i++) {
                cout << curr_letters[i] << " ";
            }
            cout << "\n\n";
        }

        // add letter to sum and check if the sum existed in existed_sum
        found = 0;
        for (int i = 0; i < sum.size(); i++) {
            sum[i].first += letter;

            if (found == 0) {// we won't need to do more query if already found one
                temp_sum = sum[i].first;

                auto check_existed = existed_sum_to_length.find(temp_sum);
                if (check_existed != existed_sum_to_length.end()) {

                    for (auto j = existed_sum_to_length[temp_sum].begin();
                        j != existed_sum_to_length[temp_sum].end() && found == 0;
                        ++j) {

                        length = *j;

                        if ((first_round_complete == 0 && length <= finish) || first_round_complete == 1) {

                            auto find_letter = length_lastLetter_sum_string[length].find(letter);
                            if (find_letter != length_lastLetter_sum_string[length].end()) {

                                auto find_sum = length_lastLetter_sum_string[length][letter].find(temp_sum);
                                if (find_sum != length_lastLetter_sum_string[length][letter].end()) {

                                    for (auto k = length_lastLetter_sum_string[length][letter][temp_sum].begin();
                                        k != length_lastLetter_sum_string[length][letter][temp_sum].end() && found == 0;
                                        ++k) {

                                        if (test > 0) {
                                            cout << "\ncompare: " << words_words[*k] << "\n";
                                            cout << "curr_letters:\n";
                                            for (int q = 0; q < curr_letters.size(); q++) { cout << curr_letters[q] << " "; }
                                            cout << "\nmax_length = " << max_length << "\n";
                                            cout << "length = " << length << "\n";
                                            cout << "finish = " << finish << "\n";
                                        }

                                        found = compare(length, finish, words_words[*k]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (test > 0) {
            cout << "after updating sum:\n";
            for (int i = 0; i < sum.size(); i++) {
                cout << sum[i].first << " " << sum[i].second << ", ";
            }
            cout << "\n\n";
        }

        return found;
    }

    bool compare(int length, int finish, string &original_string) {
        bool same = 1;

        if (first_round_complete == 1) {
            if (length <= finish) {
                for (int i = finish - length, j = 0; j < length; i++, j++) {
                    if (curr_letters[i] != original_string[j]) {
                        same = 0; break;
                    }
                }
            }

            else {
                for (int i = 0, j = length - finish; i < finish; i++, j++) {
                    if (curr_letters[i] != original_string[j]) {
                        same = 0; break;
                    }
                }

                if (same == 1) {
                    for (int i = max_length - (length - finish), j = 0; j < length - finish; i++, j++) {
                        if (curr_letters[i] != original_string[j]) {
                            same = 0; break;
                        }
                    }
                }
            }
        }

        else {// length must be no larger than finish
            for (int i = finish - length, j = 0; j < length; i++, j++) {
                if (curr_letters[i] != original_string[j]) { same = 0; break; }
            }
        }

        return same;
    }

    void display_info () {
        cout << "\nwords_words:\n";
        for (int i = 0; i < words_words.size(); i++) { cout << words_words[i] << " "; }
        cout << "\n\nexisted_sum_to_length:\n";
        for (auto i = existed_sum_to_length.begin(); i != existed_sum_to_length.end(); ++i) {
            cout << i->first << ": ";
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                cout << *j << " ";
            }
            cout << "\n";
        }
        cout << "\nlength_lastLetter_sum_string:\n";
        for (auto i = length_lastLetter_sum_string.begin(); i != length_lastLetter_sum_string.end(); ++i) {
            cout << i->first << ":\n";
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                cout << "  " << j->first << "\n";
                for (auto k = j->second.begin(); k != j->second.end(); ++k) {
                    cout << "    " << k->first << "\n";
                    for (auto m = k->second.begin(); m != k->second.end(); ++m) {
                        cout << "      " << words_words[*m] << "\n";
                    }
                }
            }
        }
        cout << "\n";

    }


};

// medium change. shrink 2 big table to 1 table
class StreamChecker_worked_1_1 {
public:
    int test = 0;

    int max_length = 0;

    bool found = 0;
    int length, temp;
    char last_letter, first_letter;
    string temp_string;

    // mirror of words
    vector<string> words_words;

    // record & maintaining the current letters under consideration
    bool first_round_complete = 0;
    int finish = 0;
    vector<char> curr_letters;

    unordered_map<char, map<int, unordered_map<char, unordered_set<int>>>> lastLetter_length_firstLetter_idx;

    StreamChecker_worked_1_1(vector<string>& words) {
        words_words.reserve(words.size());

        for (int i = 0; i < words.size(); i++) {
            words_words.push_back(words[i]);

            length = words[i].size();
            if (length > max_length) { max_length = length; }

            last_letter = words[i][length - 1];

            auto find_lastLetter = lastLetter_length_firstLetter_idx.find(last_letter);
            if (find_lastLetter == lastLetter_length_firstLetter_idx.end()) {
                lastLetter_length_firstLetter_idx.insert({last_letter, map<int, unordered_map<char, unordered_set<int>>> ()});
            }

            auto find_length = lastLetter_length_firstLetter_idx[last_letter].find(length);
            if (find_length == lastLetter_length_firstLetter_idx[last_letter].end()) {
                lastLetter_length_firstLetter_idx[last_letter].insert({length, unordered_map<char, unordered_set<int>> ()});
            }

            first_letter = words[i][0];

            auto find_firstLetter = lastLetter_length_firstLetter_idx[last_letter][length].find(first_letter);
            if (find_firstLetter == lastLetter_length_firstLetter_idx[last_letter][length].end()) {
                lastLetter_length_firstLetter_idx[last_letter][length].insert({first_letter, unordered_set<int> ()});
            }

            lastLetter_length_firstLetter_idx[last_letter][length][first_letter].insert(i);
        }

        curr_letters.resize(max_length, 1);

        /*unidentical_lengths = length_lastLetter_sum_string.size();

        sum.resize(unidentical_lengths, {0, 0});

        temp = 0;
        for (auto i = length_lastLetter_sum_string.begin(); i != length_lastLetter_sum_string.end(); ++i) {
            sum[temp].second = i->first;
            temp++;
        }*/

        //display_info();
    }

    bool query(char letter) {
        if (test > 0) {
            cout << "\n\nQUERY\n\n";
            cout << "letter = " << letter << "\n";
            cout << "finish = " << finish << "\n";
            cout << "\ncurr_letters:\n";
            for (int i = 0; i < curr_letters.size(); i++) { cout << curr_letters[i] << " "; }
            cout << "\n";
        }

        // put letter in curr_letters
        curr_letters[finish] = letter;
        finish++;
        if (finish == max_length) { finish = 0; first_round_complete = 1; }

        if (test > 0) {
            cout << "\nafter updating:\n";
            cout << "finish = " << finish << "\n";
            for (int i = 0; i < curr_letters.size(); i++) { cout << curr_letters[i] << " "; }
            cout << "\n\n";
        }

        // add letter to sum and check if the sum existed in existed_sum
        found = 0;

        auto find_lastLetter = lastLetter_length_firstLetter_idx.find(letter);
        if (find_lastLetter != lastLetter_length_firstLetter_idx.end()) {
            for (auto i = lastLetter_length_firstLetter_idx[letter].begin();
                i != lastLetter_length_firstLetter_idx[letter].end() && found == 0;
                ++i) {

                for (auto j = i->second.begin(); j != i->second.end() && found == 0; ++j) {

                    if ((i->first <= finish && curr_letters[finish - i->first] == j->first)
                        || (i->first > finish && curr_letters[max_length - (i->first - finish)] == j->first)) {

                        for (auto k = j->second.begin(); k != j->second.end() && found == 0; ++k) {
                            found = compare(i->first, words_words[*k]);
                        }
                    }
                }
            }
        }

        return found;
    }

    bool compare(int length, string &original_string) {
        bool same = 1;

        if (first_round_complete == 1) {
            if (length <= finish) {
                for (int i = finish - length, j = 0; j < length; i++, j++) {
                    if (curr_letters[i] != original_string[j]) {
                        same = 0; break;
                    }
                }
            }

            else {
                for (int i = 0, j = length - finish; i < finish; i++, j++) {
                    if (curr_letters[i] != original_string[j]) {
                        same = 0; break;
                    }
                }

                if (same == 1) {
                    for (int i = max_length - (length - finish), j = 0; j < length - finish; i++, j++) {
                        if (curr_letters[i] != original_string[j]) {
                            same = 0; break;
                        }
                    }
                }
            }
        }

        else {// length must be no larger than finish
            for (int i = finish - length, j = 0; j < length; i++, j++) {
                if (curr_letters[i] != original_string[j]) { same = 0; break; }
            }
        }

        return same;
    }

    void display_info () {
        cout << "\nwords_words:\n";
        for (int i = 0; i < words_words.size(); i++) { cout << words_words[i] << " "; }
        /*cout << "\nlength_lastLetter_sum_string:\n";
        for (auto i = length_lastLetter_sum_string.begin(); i != length_lastLetter_sum_string.end(); ++i) {
            cout << i->first << ":\n";
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                cout << "  " << j->first << "\n";
                for (auto k = j->second.begin(); k != j->second.end(); ++k) {
                    cout << "    " << k->first << "\n";
                    for (auto m = k->second.begin(); m != k->second.end(); ++m) {
                        cout << "      " << words_words[*m] << "\n";
                    }
                }
            }
        }*/
        cout << "\n";

    }


};

// medium change. replace "map" table with a vector
class StreamChecker_worked_1_2 {
public:
    int test = 0;

    bool found = 0;
    int max_length = 0, length;;
    char last_letter, first_letter;
    string temp_string;

    // mirror of words
    vector<string> words_words;

    // record & maintaining the current letters under consideration
    int finish = 0;
    bool first_round_complete = 0;
    vector<char> curr_letters;

    // lastLetter_and_length_firstLetter_idx_triplets is too long a name, i'll call it "data" then
    vector<vector<vector<int>>> data;

    StreamChecker_worked_1_2(vector<string>& words) {
        words_words.reserve(words.size());
        data.resize(26, vector<vector<int>> ());


        for (int i = 0; i < words.size(); i++) {
            words_words.push_back(words[i]);

            length = words[i].size();
            if (length > max_length) { max_length = length; }

            last_letter = words[i][length - 1];
            first_letter = words[i][0];

            data[last_letter - 97].push_back({length, first_letter, i});
        }

        for (int i = 0; i < data.size(); i++) {
            sort(data[i].begin(), data[i].end(), [](const auto &a, const auto &b){ return a[0] < b[0]; });
        }

        curr_letters.resize(max_length, 1);
    }

    bool query(char letter) {
        if (test > 0) {
            cout << "\n\nQUERY\n\n";
            cout << "letter = " << letter << "\n";
            cout << "finish = " << finish << "\n";
            cout << "\ncurr_letters:\n";
            for (int i = 0; i < curr_letters.size(); i++) { cout << curr_letters[i] << " "; }
            cout << "\n";
        }

        // put letter in curr_letters
        curr_letters[finish] = letter;
        finish++;
        if (finish == max_length) { finish = 0; first_round_complete = 1; }

        if (test > 0) {
            cout << "\nafter updating:\n";
            cout << "finish = " << finish << "\n";
            for (int i = 0; i < curr_letters.size(); i++) { cout << curr_letters[i] << " "; }
            cout << "\n\n";
        }

        // add letter to sum and check if the sum existed in existed_sum
        found = 0;

        if (data[letter - 97].size() > 0) {

            for (int i = 0; i < data[letter - 97].size() && found == 0; i++) {

                if ((data[letter - 97][i][0] <= finish && curr_letters[finish - data[letter - 97][i][0]] == data[letter - 97][i][1])
                  || (data[letter - 97][i][0] > finish && curr_letters[max_length - (data[letter - 97][i][0] - finish)] == data[letter - 97][i][1])) {

                    found = compare_it(data[letter - 97][i][0], words_words[data[letter - 97][i][2]]);
                }
            }
        }

        return found;
    }

    bool compare_it(int length, string &original_string) {
        bool same = 1;

        if (first_round_complete == 1) {
            if (length <= finish) {
                for (int i = finish - length, j = 0; j < length; i++, j++) {
                    if (curr_letters[i] != original_string[j]) {
                        same = 0; break;
                    }
                }
            }

            else {
                for (int i = 0, j = length - finish; i < finish; i++, j++) {
                    if (curr_letters[i] != original_string[j]) {
                        same = 0; break;
                    }
                }

                if (same == 1) {
                    for (int i = max_length - (length - finish), j = 0; j < length - finish; i++, j++) {
                        if (curr_letters[i] != original_string[j]) {
                            same = 0; break;
                        }
                    }
                }
            }
        }

        else {// length must be no larger than finish
            for (int i = finish - length, j = 0; j < length; i++, j++) {
                if (curr_letters[i] != original_string[j]) { same = 0; break; }
            }
        }

        return same;
    }

    void display_info () {
        cout << "\nwords_words:\n";
        for (int i = 0; i < words_words.size(); i++) { cout << words_words[i] << " "; }
        cout << "\n";
    }


};

// minor change. in "compare", replace &string into index in words_words
class StreamChecker_worked_1_3 {
public:
    bool found = 0;
    int max_length = 0, length;;
    char last_letter, first_letter;
    string temp_string;

    // mirror of words
    vector<string> words_words;

    // record & maintaining the current letters under consideration
    int finish = 0;
    bool first_round_complete = 0;
    vector<char> curr_letters;

    // lastLetter_and_length_firstLetter_idx_triplets is too long a name, i'll call it "data" then
    vector<vector<vector<int>>> data;

    StreamChecker_worked_1_3(vector<string>& words) {
        words_words.reserve(words.size());
        data.resize(26, vector<vector<int>> ());

        //sort(words.begin(), words.end(), [](auto const &a, const auto &b){ return a.size() < b.size(); });

        for (int i = 0; i < words.size(); i++) {
            words_words.push_back(words[i]);

            length = words[i].size();
            if (length > max_length) { max_length = length; }

            last_letter = words[i][length - 1];
            first_letter = words[i][0];

            data[last_letter - 97].push_back({length, first_letter, i});
        }

        for (int i = 0; i < data.size(); i++) {
            sort(data[i].begin(), data[i].end(), [](const auto &a, const auto &b){ return a[0] < b[0]; });
        }

        curr_letters.resize(max_length, 1);
    }

    bool query(char letter) {
        // put letter in curr_letters
        curr_letters[finish] = letter;
        finish++;
        if (finish == max_length) { finish = 0; first_round_complete = 1; }

        // add letter to sum and check if the sum existed in existed_sum
        found = 0;

        if (data[letter - 97].size() > 0) {

            for (int i = 0; i < data[letter - 97].size() && found == 0; i++) {

                if ((data[letter - 97][i][0] <= finish && curr_letters[finish - data[letter - 97][i][0]] == data[letter - 97][i][1])
                  || (data[letter - 97][i][0] > finish && curr_letters[max_length - (data[letter - 97][i][0] - finish)] == data[letter - 97][i][1])) {

                    found = compare_it(data[letter - 97][i][0], data[letter - 97][i][2]);
                }
            }
        }

        return found;
    }

    bool compare_it(int length, int index) {
        bool same = 1;

        if (first_round_complete == 1) {
            if (length <= finish) {
                for (int i = finish - length, j = 0; j < length; i++, j++) {
                    if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
                }
            }

            else {
                for (int i = 0, j = length - finish; i < finish; i++, j++) {
                    if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
                }

                if (same == 1) {
                    for (int i = max_length - (length - finish), j = 0; j < length - finish; i++, j++) {
                        if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
                    }
                }
            }
        }

        else if (length <= finish){// length must be no larger than finish
            for (int i = finish - length, j = 0; j < length; i++, j++) {
                if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
            }
        }

        else { return 0; }

        return same;
    }

    void display_info () {
        cout << "first_round_complete = " << first_round_complete << "\n";
        cout << "finish = " << finish << "\ncurr_letter:\n";
        for (int i = 0; i < curr_letters.size(); i++) { cout << curr_letters[i] << " ";}
        cout << "\n";
    }
};

// minor change. in "compare", comparing backwards
class StreamChecker_worked_1_3_1 {
public:
    bool found = 0;
    int max_length = 0, length;;
    char last_letter, first_letter;
    string temp_string;

    // mirror of words
    vector<string> words_words;

    // record & maintaining the current letters under consideration
    int finish = 0;
    bool first_round_complete = 0;
    vector<char> curr_letters;

    // lastLetter_and_length_firstLetter_idx_triplets is too long a name, i'll call it "data" then
    vector<vector<vector<int>>> data;

    StreamChecker_worked_1_3_1(vector<string>& words) {
        words_words.reserve(words.size());
        data.resize(26, vector<vector<int>> ());

        //sort(words.begin(), words.end(), [](auto const &a, const auto &b){ return a.size() < b.size(); });

        for (int i = 0; i < words.size(); i++) {
            words_words.push_back(words[i]);

            length = words[i].size();
            if (length > max_length) { max_length = length; }

            last_letter = words[i][length - 1];
            first_letter = words[i][0];

            data[last_letter - 97].push_back({length, first_letter, i});
        }

        for (int i = 0; i < data.size(); i++) {
            sort(data[i].begin(), data[i].end(), [](const auto &a, const auto &b){ return a[0] < b[0]; });
        }

        curr_letters.resize(max_length, 1);
    }

    bool query(char letter) {
        // put letter in curr_letters
        curr_letters[finish] = letter;
        finish++;
        if (finish == max_length) { finish = 0; first_round_complete = 1; }

        // add letter to sum and check if the sum existed in existed_sum
        found = 0;

        if (data[letter - 97].size() > 0) {

            for (int i = 0; i < data[letter - 97].size() && found == 0; i++) {

                if ((data[letter - 97][i][0] <= finish && curr_letters[finish - data[letter - 97][i][0]] == data[letter - 97][i][1])
                  || (data[letter - 97][i][0] > finish && curr_letters[max_length - (data[letter - 97][i][0] - finish)] == data[letter - 97][i][1])) {

                    found = compare_it(data[letter - 97][i][0], data[letter - 97][i][2]);
                }
            }
        }

        return found;
    }

    bool compare_it(int length, int index) {
        bool same = 1;

        if (first_round_complete == 1) {
            if (length <= finish) {
                for (int i = finish - 1, j = length - 1; j >= 0; i--, j--) {
                    if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
                }
            }

            else {
                for (int i = finish - 1, j = length - 1; i >= 0; i--, j--) {
                    if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
                }

                if (same == 1) {
                    for (int i = max_length - 1, j = length - finish - 1; j >= 0; i--, j--) {
                        if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
                    }
                }
            }
        }

        else {// length must be no larger than finish
            for (int i = finish - 1, j = length - 1; j >= 0; i--, j--) {
                if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
            }
        }

        return same;
    }

};


// too slow
class StreamChecker_worked_1_4 {
public:
    bool found = 0;
    int max_length = 0;
    int length, first_letter, last_letter, temp_index;

    // mirror of words
    vector<string> words_words;

    // record & maintaining the current letters under consideration
    int finish = 0;
    bool first_round_complete = 0;
    vector<char> curr_letters;

    map<int, unordered_map<char, unordered_map<char, unordered_set<int>>>> diffLengths_firstLetter_lastLetter_idx;
    vector<int> mapping;

    StreamChecker_worked_1_4(vector<string>& words) {
        words_words.reserve(words.size());

        sort(words.begin(), words.end(), [](auto const &a, const auto &b){ return a.size() < b.size(); });
        //for (int i = 0; i < words.size(); i++) { cout << words[i] << "\n"; }

        max_length = words[words.size() - 1].size();

        length = words[0].size();
        mapping.push_back(length);
        for (int i = 0; i < words.size(); i++) {
            words_words.push_back(words[i]);

            if (length < words[i].size()) {
                length = words[i].size();
                mapping.push_back(length);

                diffLengths_firstLetter_lastLetter_idx.insert({length, unordered_map<char, unordered_map<char, unordered_set<int>>> ()});
            }

            first_letter = words[i][0];
            auto find_firstLetter = diffLengths_firstLetter_lastLetter_idx[length].find(first_letter);
            if (find_firstLetter == diffLengths_firstLetter_lastLetter_idx[length].end()) {
                diffLengths_firstLetter_lastLetter_idx[length].insert({first_letter, unordered_map<char, unordered_set<int>> ()});
            }

            last_letter = words[i][length - 1];
            auto find_lastLetter = diffLengths_firstLetter_lastLetter_idx[length][first_letter].find(last_letter);
            if (find_lastLetter == diffLengths_firstLetter_lastLetter_idx[length][first_letter].end()) {
                diffLengths_firstLetter_lastLetter_idx[length][first_letter].insert({last_letter, unordered_set<int> ()});
            }

            diffLengths_firstLetter_lastLetter_idx[length][first_letter][last_letter].insert(i);
        }

        curr_letters.resize(max_length, 1);
    }

    bool query(char letter) {
        // put letter in curr_letters
        curr_letters[finish] = letter;
        finish++;
        if (finish == max_length) { finish = 0; first_round_complete = 1; }

        found = 0;

        if (first_round_complete == 0) {
            for (int i = 0; mapping[i] <= finish && found == 0; i++) {
                length = mapping[i];
                first_letter = curr_letters[finish - length];

                auto find_firstLtter = diffLengths_firstLetter_lastLetter_idx[length].find(first_letter);
                if (find_firstLtter != diffLengths_firstLetter_lastLetter_idx[length].end()) {

                    auto find_lastLetter = diffLengths_firstLetter_lastLetter_idx[length][first_letter].find(letter);
                    if (find_lastLetter != diffLengths_firstLetter_lastLetter_idx[length][first_letter].end()) {

                        for (auto j = diffLengths_firstLetter_lastLetter_idx[length][first_letter][letter].begin();
                            j != diffLengths_firstLetter_lastLetter_idx[length][first_letter][letter].end() && found == 0;
                            ++j) {

                            found = compare_it(length, *j);
                        }
                    }
                }
            }
        }

        else {// first_round_complete == 1
            temp_index = 0;
            for (int i = 0; mapping[i] <= finish && found == 0; i++, temp_index++) {
                length = mapping[i];
                first_letter = curr_letters[finish - length];

                auto find_firstLtter = diffLengths_firstLetter_lastLetter_idx[length].find(first_letter);
                if (find_firstLtter != diffLengths_firstLetter_lastLetter_idx[length].end()) {

                    auto find_lastLetter = diffLengths_firstLetter_lastLetter_idx[length][first_letter].find(letter);
                    if (find_lastLetter != diffLengths_firstLetter_lastLetter_idx[length][first_letter].end()) {

                        for (auto j = diffLengths_firstLetter_lastLetter_idx[length][first_letter][letter].begin();
                            j != diffLengths_firstLetter_lastLetter_idx[length][first_letter][letter].end() && found == 0;
                            ++j) {

                            found = compare_it(length, *j);
                        }
                    }
                }
            }

            for (int i = temp_index; i < mapping.size() && found == 0; i++) {
                length = mapping[i];
                first_letter = curr_letters[max_length - (length - finish)];

                auto find_firstLtter = diffLengths_firstLetter_lastLetter_idx[length].find(first_letter);
                if (find_firstLtter != diffLengths_firstLetter_lastLetter_idx[length].end()) {

                    auto find_lastLetter = diffLengths_firstLetter_lastLetter_idx[length][first_letter].find(letter);
                    if (find_lastLetter != diffLengths_firstLetter_lastLetter_idx[length][first_letter].end()) {

                        for (auto j = diffLengths_firstLetter_lastLetter_idx[length][first_letter][letter].begin();
                            j != diffLengths_firstLetter_lastLetter_idx[length][first_letter][letter].end() && found == 0;
                            ++j) {

                            found = compare_it(length, *j);
                        }
                    }
                }
            }
        }

        return found;
    }

    bool compare_it(int length, int index) {
        bool same = 1;

        if (first_round_complete == 1) {
            if (length <= finish) {
                for (int i = finish - length, j = 0; j < length; i++, j++) {
                    if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
                }
            }

            else {
                for (int i = 0, j = length - finish; i < finish; i++, j++) {
                    if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
                }

                if (same == 1) {
                    for (int i = max_length - (length - finish), j = 0; j < length - finish; i++, j++) {
                        if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
                    }
                }
            }
        }

        else {// length must be no larger than finish
            for (int i = finish - length, j = 0; j < length; i++, j++) {
                if (curr_letters[i] != words_words[index][j]) { same = 0; break; }
            }
        }

        return same;
    }

};



// EXCELLENT PERFORMANCE
class StreamChecker_tries {
public:
    struct trie {
        //bool leaf;
        int index;
        trie* child[26];
    };

    trie* create_node() {
        trie* temp = new trie();
        //temp->leaf = false;
        temp->index = -1;
        memset(temp->child, NULL, sizeof temp->child);
        return temp;
    }

    void insert_reversed_string(trie* root, string &s, int idx) {
        //cout << "\ninsert " << s << "\n";
        for (int i = s.size() - 1; i >= 0 ; i--) {
            //cout << s[i] << " ";
            if (root->child[s[i] - 97] == nullptr) {
                root->child[s[i] - 'a'] = create_node();
            }

            root = root->child[s[i] - 'a'];
            if (i == 0) { root->index = idx; }
        }

        //root->leaf = true;
    }

    void print(trie* root) {
        cout << root->index << ", ";
        int found = 0;
        for (int i = 0; i < 26; i++) {
            if (root->child[i] != nullptr) {
                found = 1;
                cout << (char)('a' + i) << " ";
                print(root->child[i]);
            }
        }

        if (found == 0) {cout << "\n";}
    }

    trie* root = create_node();

    int test = 0;
    int max_length = 0, length, finish = 0;
    bool first_round_complete = 0, found, done;
    vector<char> curr_letters;

    StreamChecker_tries(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            insert_reversed_string(root, words[i], i);

            if (words[i].size() > max_length) { max_length = words[i].size(); }
        }

        curr_letters.resize(max_length, 1);

        if (test > 0) {
            cout << "\n\n" << root->index << "\n\n";
            print(root);
        }
    }

    bool query(char letter) {
        // put letter in curr_letters
        if (test > 0) { cout << "\nQUERY\nletter = " << letter << "\n"; }
        //cout << letter;
        curr_letters[finish] = letter;

        found = 0, done = 0;
// = {"w", "qylh", "hvcz", "u", "u", "nlp", "gaiv", "fzwx", "tv", "li"};
//zluhz ubcyj kr
///zdy frhyb ljodv repir ebrym tuv
        if (test > 0) { cout << "finish = " << finish << "\nenter the maze?\n"; }
        if (root->child[letter - 'a'] != nullptr) {
            if (test > 0) { cout << "round start\n"; }

            trie* temp = root->child[letter - 'a'];

            if (test > 0) { cout << "temp->index = " << temp->index << "\n"; }

            if (temp->index >= 0) {
                if (test > 0) { cout << "~00\n"; }
                found = 1;
            }

            else if (first_round_complete == 0) {
                if (test > 0) { cout << "~1\n"; }
                for (int i = finish - 1; i >= 0 && done == 0; i--) {

                    if (temp->child[curr_letters[i] - 'a'] != nullptr) {
                        if (test > 0) { cout << curr_letters[i] - 'a' << " "; }

                        temp = temp->child[curr_letters[i] - 'a'];

                        if (temp->index >= 0) {
                            if (test > 0) { cout << "~1~1\n"; }
                            found = 1; break;
                        }
                    }

                    else { done = 1; break; }
                }
            }

            else {// first_round_complete == 1;
                if (test > 0) { cout << "~2\n"; }
                //(int i = finish - 1; i >= 0; i--)(int i = finish - 1; ; )
                for (int i = finish - 1; i >= 0 && done == 0; i--) {

                    //if (temp->index >= 0) { found = 1; break; }
                    if (test > 0) {
                        cout << "i = " << i << "\n";
                        cout << curr_letters[i] << "\n";
                    }

                    if (temp->child[curr_letters[i] - 'a'] != nullptr) {
                        if (test > 0) { cout << curr_letters[i] - 'a' << " "; }
                        temp = temp->child[curr_letters[i] - 'a'];

                        if (temp->index >= 0) {
                            if (test > 0) { cout << "~2~2\n"; }
                            found = 1; break;
                        }
                    }

                    else { done = 1; break; }

                    /*if (i == finish + 1) { break; }
                    if (i == 0) { i = max_length - 1; }
                    else { i--; }*/

                }

                if (found == 0) {
                    for (int i = max_length - 1; i > finish && done == 0; i--) {
                        if (test > 0) {
                            cout << "i = " << i << "\n";
                            cout << curr_letters[i] << "\n";
                        }

                        //if (temp->index >= 0) { found = 1; break; }

                        if (temp->child[curr_letters[i] - 'a'] != nullptr) {
                            temp = temp->child[curr_letters[i] - 'a'];

                            if (temp->index >= 0) {
                                if (test > 0) { cout << "~3\n"; }
                                found = 1; break;
                            }
                        }

                        else { done = 1; break; }
                    }
                }
            }
        }

        finish++;
        if (finish == max_length) { finish = 0; first_round_complete = 1; }

        if (test > 0) { cout << "\nfound = " << found << "\n"; }
        return found;
    }

    void check_tries () { print(root); }

    void display_info () {
        cout << "first_round_complete = " << first_round_complete << "\n";
        cout << "finish = " << finish << "\ncurr_letter:\n";
        for (int i = 0; i < curr_letters.size(); i++) { cout << curr_letters[i] << " ";}
        cout << "\n";
    }

};



//std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int main(){
    srand(time(0)); int temp, temp0, temp1, temp2;
    int length = 5000, word_length = 2000, lower_range = 97, upper_range = 122, display = 0, input = 1;
    bool aa, bb, cc;
    vector<string> wtf;
    // = {"cd","f","kl"};
    string temp_string;
    auto sp1 = chrono::steady_clock::now(); auto ep1 = chrono::steady_clock::now(); auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now(); auto ep2 = chrono::steady_clock::now(); auto dif2 = ep2 - sp2;
    auto sp3 = chrono::steady_clock::now(); auto ep3 = chrono::steady_clock::now(); auto dif3 = ep3 - sp3;

    //zluhzubcyjkrzdyfrhybljodvrepirebrymtuv
    string input_string = "zdyfrhybljodvrepirebrymtuv";

//for (int m = 0; m < 50; m++) { if ((m + 1)%100 == 0) {cout << "m = " << m << "\n";}
    if (input == 1){//rand()%(upper_range - lower_range + 1) + lower_range
        for(int i = 0; i < length; i++){
            temp_string.clear();
            temp = rand() % word_length + 1;
            for (int j = 0; j < temp; j++) {
                temp_string.push_back(rand() % (122 - 97 + 1) + 97);
            }
            wtf.push_back(temp_string);
        }
    }
    if (display == 1){
        cout << "wtf:\n{";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "\"" << wtf[i] << "\", ";
        }
        cout << "};\n";
    }

    vector<string> wtf0(wtf); vector<string> wtf1(wtf); vector<string> wtf2(wtf);

    sp1 = chrono::steady_clock::now();
    StreamChecker_worked_1_2 a = StreamChecker_worked_1_2(wtf0);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;

    sp2 = chrono::steady_clock::now();
    StreamChecker_worked_1_3 b = StreamChecker_worked_1_3(wtf1);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;


    sp3 = chrono::steady_clock::now();
    StreamChecker_tries c = StreamChecker_tries(wtf2);
    ep3 = chrono::steady_clock::now();
    dif3 += ep3 - sp3;


    //input_string.size()
//1; y <= 500
for (int y = 1; y <= 1000000; y++) { if (y % 100000 == 0) { cout << "y = " << y << "\n"; }
    temp = rand()%(122 - 97 + 1) + 97;//input_string[y - 1];
    //
    temp0 = temp, temp1 = temp, temp2 = temp;

    sp1 = chrono::steady_clock::now();
    aa = a.query(temp0);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;
    //cout << "aa = " << aa << "\n";

    sp2 = chrono::steady_clock::now();
    bb = b.query(temp1);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;
    //b.check_window();
    //cout << "bb = " << bb << "\n";

    sp3 = chrono::steady_clock::now();
    cc = c.query(temp2);
    ep3 = chrono::steady_clock::now();
    dif3 += ep3 - sp3;
    //c.display_info();
    //cout << "" << cc << "";

    if (aa != bb || aa != cc) {
        cout << "\n\n\nletter = " << (char)temp << "\n";

        cout << "\n\n";
        cout << "1_3 display_info:\n";
        b.display_info();
        cout << "\n\ntries display_info:\n";
        c.display_info();
        cout << "\n\n";
        c.check_tries();
        cout << "\n\n";

        cout << "y = " << y << "\n";
        cout << "\n\naa = " << aa << "\nbb = " << bb << "\ncc = " << cc << "\n";

        cout << "wtf:\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "\"" << wtf[i] << "\", ";
        }
        cout << "};\n";

        //a.check_window();

        break;
    }

}

    /*for (int i = 0; i < input_char.size(); i++) {
        cout << "\ni = " << i << "\n\n";
        sp1 = chrono::steady_clock::now();
        aa = a.query(input_char[i]);
        ep1 = chrono::steady_clock::now();
        dif1 += ep1 - sp1;
        cout << "aa = " << aa << "\n";

        sp2 = chrono::steady_clock::now();
        bb = b.query(input_char[i]);
        ep2 = chrono::steady_clock::now();
        dif2 += ep2 - sp2;
        cout << "bb = " << bb << "\n";

        if (aa != bb) {
            cout << "something is wrong.\n\naa = " << aa << "\nbb = " << bb << "\n";
            cout << input_char[i] << "\n";
            break;
        }
    }*/

//wtf.clear();}


cout << duration <double, milli> (dif1).count() << " ms" << "\n";
cout << duration <double, milli> (dif2).count() << " ms" << "\n";
cout << duration <double, milli> (dif3).count() << " ms" << "\n";

    return 0;
}




