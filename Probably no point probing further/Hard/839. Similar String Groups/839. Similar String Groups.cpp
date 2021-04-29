/*839. Similar String Groups
Hard

Two strings X and Y are similar if we can swap two letters (in different positions) of X,
so that it equals Y. Also two strings X and Y are similar if they are equal.

For example, "tars" and "rats" are similar (swapping at positions 0 and 2),
and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".

Together, these form two connected groups by similarity:
{"tars", "rats", "arts"} and {"star"}.
Notice that "tars" and "arts" are in the same group even though they are not similar.
Formally, each group is such that
a word is in the group if and only if it is similar to at least one other word in the group.

We are given a list strs of strings where every string in strs is an anagram of every other string in strs.
How many groups are there?

Input: strs = ["tars","rats","arts","star"]
Output: 2

Input: strs = ["omv","ovm"]
Output: 1

Constraints:
    1 <= strs.length <= 300
    1 <= strs[i].length <= 300
    strs[i] consists of lowercase letters only.
    All words in strs have the same length and are anagrams of each other.
*/

/*
class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {

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

int numSimilarGroups_brute_NOT_WORKING(vector<string>& strs) {
    int length = strs.size(), word_length = strs[0].size();
    int next_group_category = 1, temp, counter;
    int test = 1;

    stack<int> similar;
    //int first_similar_idx;
    unordered_set<int> existed;

    int category[length]; category[0] = 0;
    for (int i = 1; i < length; i++) { category[i] = -1; }

    for (int i = 1; i < length; i++) {
        if (test > 0) { cout << "i = " << i << "\n"; }
        // next_group_category = 0;
        //first_similar_idx = -1;

        for (int j = 0; j < i; j++) {
            counter = 0;

            // if (next_group_category == category[j]) { next_group_category++; }

            for (int k = 0; k < word_length; k++) {
                if (strs[i][k] != strs[j][k]) { counter++; }

                if (counter > 2) { break; }
            }

            if (counter == 2) {
                //if (first_similar_idx < 0) { first_similar_idx = category[j]; }
                similar.push(j);
                if (test > 0) { cout << "push " << j << "\n"; }
            }
        }

        if (test > 0) {
            cout << "next_group_category = " << next_group_category << "\n";
            // cout << "first_similar_idx = " << first_similar_idx << "\n";
        }

        if (similar.size() == 0) { category[i] = next_group_category; }

        else {
            while (!similar.empty()) {
                category[similar.top()] = next_group_category;
                similar.pop();
            }
            category[i] = next_group_category;
        }

        if (test > 0) {
            for (int m = 0; m < length; m++) { cout << category[m] << " "; }
            cout << "\n";
        }
        next_group_category++;
    }

    int result = 0;

    for (int i = 0; i < length; i++) {
        if (existed.find(category[i]) == existed.end()) {
            result++;
            existed.insert(category[i]);
        }
    }

    return result;
}


int numSimilarGroups_brute(vector<string>& strs) {
    int length = strs.size(), word_length = strs[0].size();
    int counter;
    int test = 0;

    bool similar[length][length];
    for (int i = 0; i < length; i++) { for (int j = 0; j < length; j++) { similar[i][j] = 0; } }

    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            counter = 0;

            for (int k = 0; k < word_length; k++) {
                if (strs[i][k] != strs[j][k]) { counter++; }

                if (counter > 2) { break; }
            }

            if (counter <= 2) { similar[i][j] = 1; }//, similar[j][i] = 1
        }
    }

/*
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 1 0 0
0 0 1 0 0 0 0 0 0 0
0 0 0 1 0 1 0 0 0 0
0 0 0 0 1 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
*/

    if (test > 0) {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                cout << similar[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";
    }

    counter = length;
    int category = 1, start_from = 0, this_round;
    deque<int> curr_window;
    curr_window.push_back(0);
    int visited[length];
    visited[0] = 1;
    counter--;
    for (int i = 1; i < length; i++) { visited[i] = -1; }

    while (counter > 0) {
        this_round = curr_window.size();

        while (this_round > 0) {
            for (int i = start_from; i < length; i++) {
                if (visited[i] < 0 && (similar[curr_window.front()][i] == 1 || similar[i][curr_window.front()] == 1)) {
                    visited[i] = visited[curr_window.front()];
                    counter--;
                    curr_window.push_back(i);
                }
            }
            curr_window.pop_front();
            this_round--;
        }

        if (counter > 0 && curr_window.size() == 0) {
            category++;
            for (int i = start_from; i < length; i++) {
                if (visited[i] < 0) {
                    curr_window.push_back(i);
                    visited[i] = category;
                    counter--;
                    start_from = i + 1;
                    break;
                }
            }
        }

        if (test > 0) {
            cout << "counter = " << counter << "\n";
            cout << category << "\n";
            for (int i = 0; i < length; i++) { cout << visited[i] << " "; } cout << "\n";
        }
    }

    return category;
}


int numSimilarGroups_brute_improved(vector<string>& strs) {
    int length = strs.size(), word_length = strs[0].size();
    int counter;

    bool similar[length][length + 1];
    for (int i = 0; i < length; i++) { for (int j = 0; j <= length; j++) { similar[i][j] = 0; } }

    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            counter = 0;

            for (int k = 0; k < word_length; k++) {
                if (strs[i][k] != strs[j][k]) { counter++; }

                if (counter > 2) { break; }
            }

            if (counter <= 2) { similar[i][j] = 1, similar[j][i] = 1; }
        }
    }

    int category = 1, start_from = 1, this_round;

    deque<int> curr_window;
    curr_window.push_back(0);
    similar[0][length] = 1;

    counter = length - 1;

    while (counter > 0) {
        this_round = curr_window.size();

        while (this_round > 0) {
            for (int i = start_from; i < length; i++) {
                if (similar[i][length] == 0 && similar[curr_window.front()][i] == 1) {
                    similar[i][length] = 1;
                    counter--;
                    curr_window.push_back(i);
                }
            }
            curr_window.pop_front();
            this_round--;
        }

        if (counter > 0 && curr_window.size() == 0) {
            category++;
            for (int i = start_from; i < length; i++) {
                if (similar[i][length] == 0) {
                    curr_window.push_back(i);
                    similar[i][length] = 1;
                    counter--;
                    start_from = i + 1;
                    break;
                }
            }
        }
    }

    return category;
}



int numSimilarGroups_brute_improved_1(vector<string>& strs) {
    int length = strs.size(); if (length == 1) { return 1; }
    int word_length = strs[0].size(); if (word_length == 1) { return 1; }
    int counter, i, j, k;

    bool similar[length][length + 1]; for (i = 0; i < length; i++) { for (j = 0; j <= length; j++) { similar[i][j] = 0; } }

    for (i = 0; i < length - 1; i++) {
        for (j = i + 1; j < length; j++) {
            counter = 0;

            for (k = 0; k < word_length; k++) {
                if (strs[i][k] != strs[j][k]) { counter++; }

                if (counter > 2) { break; }
            }

            if (counter <= 2) { similar[i][j] = 1, similar[j][i] = 1; }
        }
    }

    int category = 1, start_from = 1, this_round;
    bool need_to_proceed;

    deque<int> curr_window;
    curr_window.push_back(0);
    similar[0][length] = 1;

    counter = length - 1;

    while (counter > 0) {
        this_round = curr_window.size();

        while (this_round > 0) {
            need_to_proceed = 1;
            for (i = start_from; i < length; i++) {
                if (similar[i][length] == 0) {

                    if (similar[curr_window.front()][i] == 1) {
                        similar[i][length] = 1;
                        counter--;
                        curr_window.push_back(i);
                    }

                    else if (need_to_proceed == 1) {
                        start_from = i;
                        need_to_proceed = 0;
                    }
                }
            }

            curr_window.pop_front();
            this_round--;
        }

        if (curr_window.size() == 0 && counter > 0) {
            category++;
            for (i = start_from; i < length; i++) {
                if (similar[i][length] == 0) {
                    curr_window.push_back(i);
                    similar[i][length] = 1;
                    counter--;
                    start_from = i + 1;
                    break;
                }
            }
        }
    }

    return category;
}

// decent
int numSimilarGroups_brute_improved_2(vector<string>& strs) {
    int length = strs.size(); if (length == 1) { return 1; }
    int word_length = strs[0].size(); if (word_length == 1) { return 1; }
    int counter, i, j, k;
    int test = 1;

    bool similar[length][length + 1]; for (i = 0; i < length; i++) { for (j = 0; j <= length; j++) { similar[i][j] = 0; } }

    for (i = 0; i < length - 1; i++) {
        for (j = i + 1; j < length; j++) {
            counter = 0;

            for (k = 0; k < word_length; k++) {
                if (strs[i][k] != strs[j][k]) { counter++; }

                if (counter > 2) { break; }
            }

            if (counter <= 2) { similar[i][j] = 1; }
        }
    }

    cout << "\n";
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            cout << similar[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";

    int category = 1, start_from = 1, this_round;
    bool need_to_proceed;

    deque<int> curr_window;
    curr_window.push_back(0);
    similar[0][length] = 1;

    counter = length - 1;

    while (counter > 0) {
        this_round = curr_window.size();

        while (this_round > 0) {
            need_to_proceed = 1;
            for (i = curr_window.front() + 1; i < length; i++) {
                if (similar[i][length] == 0 && similar[curr_window.front()][i] == 1) {//  || similar[i][curr_window.front()] == 1
                    similar[i][length] = 1;
                    counter--;
                    curr_window.push_back(i);
                }
            }

            for (i = start_from; i < curr_window.front(); i++) {
                if (similar[i][length] == 0) {
                    if (similar[i][curr_window.front()] == 1) {
                        similar[i][length] = 1;
                        counter--;
                        curr_window.push_back(i);
                    }
                    else if (need_to_proceed == 1) {
                        start_from = i;
                        need_to_proceed = 0;
                    }
                }
            }

            curr_window.pop_front();
            this_round--;
        }

        if (curr_window.size() == 0 && counter > 0) {
            category++;
            for (i = start_from; i < length; i++) {
                if (similar[i][length] == 0) {
                    curr_window.push_back(i);
                    similar[i][length] = 1;
                    counter--;
                    start_from = i + 1;
                    break;
                }
            }
        }

        if (test > 0) {
            cout << "\ncategory = " << category << "\n";
            cout << "\nstart_from = " << start_from << "\n";
            for (int i = 0; i < length; i++) {
                cout << similar[i][length] << " ";
            }
            cout << "\n";
            test++;
        }
    }

    return category;
}

// decent
int numSimilarGroups_brute_improved_2_1_vector(vector<string>& strs) {
    int length = strs.size(); if (length == 1) { return 1; }
    int word_length = strs[0].size(); if (word_length == 1) { return 1; }
    int counter, i, j, k;
    int test = 1;

    vector<vector<int>> similar(length, vector<int> ());
    bool visited[length]; for (int i = 0; i < length; i++) { visited[i] = 0; }

    for (i = 0; i < length - 1; i++) {
        for (j = i + 1; j < length; j++) {
            counter = 0;

            for (k = 0; k < word_length; k++) {
                if (strs[i][k] != strs[j][k]) { counter++; }

                if (counter > 2) { break; }
            }

            if (counter <= 2) {
                similar[i].push_back(j);
                similar[j].push_back(i);
            }
        }
    }

    if (test > 0) {
        cout << "\n";
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < similar[i].size(); j++) {
                cout << similar[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";
    }

    int category = 1, start_from = 1, this_round;
    bool need_to_proceed;

    deque<int> curr_window;
    curr_window.push_back(0);
    visited[0] = 1;

    counter = length - 1;

    while (counter > 0) {
        this_round = curr_window.size();

        while (this_round > 0) {
            need_to_proceed = 1;
            for (i = 0; i < similar[curr_window.front()].size(); i++) {
                if (visited[similar[curr_window.front()][i]] == 0) {
                    visited[similar[curr_window.front()][i]] = 1;
                    counter--;
                    curr_window.push_back(similar[curr_window.front()][i]);
                }
            }

            curr_window.pop_front();
            this_round--;
        }

        if (curr_window.size() == 0 && counter > 0) {
            category++;
            for (i = start_from; i < length; i++) {
                if (visited[i] == 0) {
                    curr_window.push_back(i);
                    visited[i] = 1;
                    counter--;
                    start_from = i + 1;
                    break;
                }
            }
        }

        if (test > 0) {
            cout << "\ncategory = " << category << "\n";
            cout << "\nstart_from = " << start_from << "\n";
            for (int i = 0; i < length; i++) {
                cout << visited[i] << " ";
            }
            cout << "\n";
            test++;
        }
    }

    return category;
}





int numSimilarGroups(vector<string>& strs) {
    int length = strs.size(), word_length = strs[0].size();
    int counter;
    int test = 0;

    bool similar[length][length];
    for (int i = 0; i < length; i++) { for (int j = 0; j < length; j++) { similar[i][j] = 0; } }

    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            counter = 0;

            for (int k = 0; k < word_length; k++) {
                if (strs[i][k] != strs[j][k]) { counter++; }

                if (counter > 2) { break; }
            }

            if (counter <= 2) { similar[i][j] = 1, similar[j][i] = 1; }
        }
    }

    if (test > 0) {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                cout << similar[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";
    }

    int visited[length]; visited[0] = 1;
    for (int i = 1; i < length; i++) { visited[i] = 0; }

    deque<int> curr_window;
    curr_window.push_back(0);
    counter = 1;
    int start_from = 0, these_steps_this_round, last_idx, category = 1;

    while (counter < length) {
        these_steps_this_round = curr_window.size();
        last_idx = curr_window.front();
        if (test > 0) { cout << "last_idx = " << last_idx << "\n"; }

        while (these_steps_this_round > 0) {
            for (int i = start_from; i < length; i++) {
                if (visited[i] < 1 && similar[curr_window.front()][i] == 1) {
                    visited[i] = visited[last_idx];
                    counter++;
                    curr_window.push_back(i);
                }
            }

            curr_window.pop_front();

            these_steps_this_round--;
        }

        if (counter < length && curr_window.size() == 0) {
            category++;
            for (int i = start_from; i < length; i++) {
                if (visited[i] < 1) {
                    visited[i] = category;
                    curr_window.push_back(i);
                    start_from = i;
                    counter++;
                }
            }
        }

        if (test > 0) {
            cout << "start_from = " << start_from << "\n";
            cout << "counter = " << counter << "\n";
            cout << category << "\n";
            for (int i = 0; i < length; i++) { cout << visited[i] << " "; }
            cout << "\n";
            test++;
            if (test > 10) break;
        }
    }

    return category;
}

/*
abcde
adcbe
bdcae
ebdca
abdce
eadcb
["kccomwcgcs","socgcmcwkc","sgckwcmcoc","coswcmcgkc","cowkccmsgc","cosgmccwkc","sgmkwcccoc","coswmccgkc","kowcccmsgc","kgcomwcccs"]
*/

//  I WILL MOST LIKELY TO RUN INTO ALL KINDS OF PROBLEMS IF I DO NOT BUILD A BRUTEFORCE & TEST A BIT
//  NO MATTER HOW CONFIDENT I MIGHT HAVE ON THAT ALGORITHM

int main(){
    srand(time(0));int length = 50, display = 0, input = 0;
    vector<string> wtf = {"ajdidocuyh","djdyaohuic","ddjyhuicoa","djdhaoyuic","ddjoiuycha","ddhoiuycja","ajdydocuih","ddjiouycha","ajdydohuic","ddjyouicha"};
    // = {"kccomwcgcs","socgcmcwkc","sgckwcmcoc","coswcmcgkc","cowkccmsgc","cosgmccwkc","sgmkwcccoc","coswmccgkc","kowcccmsgc","kgcomwcccs"};
    // = {"koqnn","knnqo","noqnk","nqkon"};
    // = {"adcbe","eadcb","abcde","bdcae","ebdca","abdce"}

    auto sp1 = chrono::steady_clock::now(); auto ep1 = chrono::steady_clock::now(); auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now(); auto ep2 = chrono::steady_clock::now(); auto dif2 = ep2 - sp2;

//
    //vector<int> bloody_array;
    string initial_string = "abqrstcdelmzuvwnopfghixyjk";
    string temp_string;
    char temp_char;
    int temp1, temp2, which_one;
    //bool record[initial_string.size()][initial_string.size()];
    //for (int i = 0; i < initial_string.size(); i++) { for (int i = 0; i < initial_string.size(); i++) { record[i][j] = 0; } }
for (int m = 1; m <= 1; m++) {if (m % 1000 == 0) {cout << "m = " << m << "\n";}
    if (input == 1) {//rand() % (upper_range - lower_range + 1) + lower_range;
        wtf.push_back(initial_string);
        for (int k = 1; k < length; k++) {
            which_one = rand() % wtf.size();
            temp_string = wtf[which_one];
            temp1 = rand() % initial_string.size();
            temp2 = rand() % initial_string.size();
            while (temp1 == temp2) {
                temp1 = rand() % initial_string.size();
                temp2 = rand() % initial_string.size();
            }

            temp_char = temp_string[temp1];
            temp_string[temp1] = temp_string[temp2];
            temp_string[temp2] = temp_char;

            wtf.push_back(temp_string);
        }
    }
    if (display == 1) {
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "\"" << wtf[i] << "\"";if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    vector<string> wtf1(wtf); vector<string> wtf2(wtf);

    sp1 = chrono::steady_clock::now();
    int s = numSimilarGroups_brute(wtf1);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;
    cout << "s = " << s << "\n\n";

    sp2 = chrono::steady_clock::now();
    int ss = numSimilarGroups_brute_improved_2(wtf2);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;
    cout << "ss = " << ss << "\n\n";

    if (s != ss) {
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "\"" << wtf[i] << "\"";if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }


wtf.clear();}
cout << duration <double, milli> (dif1).count() << " ms" << "\n";
cout << duration <double, milli> (dif2).count() << " ms" << "\n";

    return 0;
}

