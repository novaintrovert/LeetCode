/*854. K-Similar Strings
Hard

Strings s1 and s2 are k-similar (for some non-negative integer k)
if we can swap the positions of two letters in s1 exactly k times so that the resulting string equals s2.

Given two anagrams s1 and s2, return the smallest k for which s1 and s2 are k-similar.

Input: s1 = "ab", s2 = "ba"
Output: 1

Input: s1 = "abc", s2 = "bca"
Output: 2

Input: s1 = "abac", s2 = "baca"
Output: 2

Input: s1 = "aabc", s2 = "abca"
Output: 2

Constraints:
    1 <= s1.length <= 20
    s2.length == s1.length
    s1 and s2 contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}.
    s2 is an anagram of s1.
*/

/*
class Solution {
public:
    int kSimilarity(string A, string B) {

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

int kSimilarity_brute_wrong(string A, string B) {
    int counter = 0;
    for (int i = 0; i < A.size(); i++) {
        if (B[i] != A[i]) {
            for (int j = i + 1; j < B.size(); j++) {
                if (B[j] == A[i]) {
                    B[j] = B[i];
                    B[i] = A[i];
                    cout << i << " " << j << "\n";
                    break;
                }
            }
            counter++;
        }
    }

    cout << "\n\n\n";

    return counter;
}

int kSimilarity_brute_wrong_1(string A, string B) {
    int test = 0;
    set<int> search_these;
    for (int i = 0; i < A.size(); i++) { if (B[i] != A[i]) { search_these.insert(i); } }

    if (test > 0) { for (auto i = search_these.begin(); i != search_these.end(); ++i) { cout << *i << " "; } cout << "\n"; }

    int counter = 0, found, temp;
    while (!search_these.empty()) {
        if (test > 0) {
            cout << "\nwhen it started\n";
            for (auto i = search_these.begin(); i != search_these.end(); ++i) {
                cout << *i << " ";
            } cout << "\n";
        }

        found = 0;

        for (auto i = next(search_these.begin()); i != search_these.end(); ++i) {
            if ((B[*i] == A[*search_these.begin()]) && (A[*search_these.begin()] == B[*i])) {
                found = 1;

                B[*i] = B[*search_these.begin()];
                B[*search_these.begin()] = A[*search_these.begin()];

                if (test > 0) { cout << "erase " << *i << "\n"; }
                search_these.erase(i);

                break;
            }
        }

        if (found == 0) {
            for (auto i = next(search_these.begin()); i != search_these.end(); ++i) {
                if (B[*i] == A[*search_these.begin()]) {
                    B[*i] = B[*search_these.begin()];
                    B[*search_these.begin()] = A[*search_these.begin()];

                    if (A[*i] == B[*i]) {
                        if (test > 0) { cout << "erase " << *i << "\n"; }
                        search_these.erase(i);
                    }

                    break;
                }
            }
        }


        if (test > 0) { cout << "erase " << *search_these.begin() << "\n"; }
        search_these.erase(search_these.begin());

        if (test > 0) {
            for (auto i = search_these.begin(); i != search_these.end(); ++i) {
                cout << *i << " ";
            } cout << "\none round complete\n\n";
        }

        counter++;
    }

    return counter;
}

int kSimilarity_brute(string &A, string &B) {
    int counter = 0, length = A.size(); int test = 0;

    if (test > 0) { cout << A << "\n" << B << "\n\nnow start:\n\n"; }

    bool idx[length];
    for (int i = 0; i < length; i++) {
        if (A[i] == B[i]) { idx[i] = 0; }

        else {idx[i] = 1; }
    }

    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            for (int j = i + 1; j < A.size(); j++) {
                if ((idx[j] == 1) && (A[j] == B[i]) && (B[j] == A[i])) {
                    B[j] = B[i];
                    B[i] = A[i];

                    idx[i] = 0;
                    idx[j] = 0;

                    counter++;

                    if (test > 0) { cout << "found~\n"; cout << A << "\n" << B << "\n\n"; }
                    break;
                }
            }
        }
    }

    for (int i = 0, found; i < A.size(); i++) {
        if (A[i] != B[i]) {
            found = 0;
            for (int j = i + 1; j < A.size(); j++) {
                if ((idx[j] == 1) && (A[j] == B[i]) && (B[j] == A[i])) {
                    found = 1;

                    B[j] = B[i];
                    B[i] = A[i];

                    idx[i] = 0;
                    idx[j] = 0;

                    counter++;

                    if (test > 0) { cout << "found~\n"; cout << A << "\n" << B << "\n\n"; }
                    break;
                }
            }

            if (found == 0) {
                for (int j = i + 1; j < A.size(); j++) {
                    if ((idx[j] == 1) && (B[j] == A[i])) {
                        B[j] = B[i];
                        B[i] = A[i];

                        idx[i] = 0;

                        counter++;

                        if (test > 0) { cout << A << "\n" << B << "\n\n"; }
                        break;
                    }
                }
            }
        }
    }

    if (test > 0) { cout << "\ndone\n\n"; }

    return counter;
}

int kSimilarity_dont_work(string A, string B) {
    vector<set<int>> A_record (6, set<int>());
    vector<set<int>> B_record (6, set<int>());
    //for (int i = 0; i < B.size(); i++) { record[B[i] - 97].push_back(i); }
    set<int> idx;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            idx.insert(i);
            A_record[A[i] - 97].insert(i);
            B_record[B[i] - 97].insert(i);
        }
    }

    int counter = 0;
    while (!idx.empty()) {

    }

    return 0;
}

int kSimilarity_not_correct(string &A, string &B) {
    int length = A.size(); int test = 0;

    int need_swap[length];
    for (int i = 0; i < length; i++) {
        if (A[i] != B[i]) { need_swap[i] = i; }

        else { need_swap[i] = -1; }
    }

    if (test > 0) { for (int i = 0; i < length; i++) { cout << need_swap[i] << " "; } cout << "\n"; }

    int counter = 0;
    bool found;
    for (int i = 0; i < length; i++) {
        if (need_swap[i] >= 0) {
            found = 0;

            for (int j = i + 1; j < length; j++) {
                if (need_swap[j] >= 0) {
                    if ((B[need_swap[j]] == A[i]) && (A[j] == B[need_swap[i]])) {
                        found = 1;
                        need_swap[j] = -1;
                        if (test > 0) { cout << "\n" << i << " " << j << "\n"; }
                        break;
                    }
                }
            }

            if (found == 0) {
                for (int j = i + 1; j < length; j++) {
                    if (need_swap[j] >= 0) {
                        if (B[need_swap[j]] == A[i]) {
                            if (test > 0) { cout << "\n" << i << " " << j << "\n"; }
                            need_swap[j] = need_swap[i];
                            break;
                        }
                    }
                }
            }

            counter++;
            need_swap[i] = -1;// unnecessary

            if (test > 0) { for (int m = 0; m < length; m++) { cout << need_swap[m] << " "; } cout << "\n"; }
        }
    }

    return counter;
}

int kSimilarity_still_not_correct(string A, string B) {
    int test = 0;
    int table[6][6];
    for (int i = 0; i < 6; i++) { for (int j = 0; j < 6; j++) { table[i][j] = 0; } }
    for (int i = 0; i < A.size(); i++) { if (A[i] != B[i]) { table[A[i] - 97][B[i] - 97]++; } }
    if (test > 0) {
        cout << "\n\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";
    }

    int counter = 0, min_count;

    if (test > 0) { cout << "stage one\n"; }

    for (int i = 0, min_count; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if ((table[i][j] > 0) && (table[j][i] > 0)) {
                min_count = min(table[i][j], table[j][i]);
                counter += min_count;
                table[i][j] -= min_count;
                table[j][i] -= min_count;

                if (test > 0) {
                    cout << "i = " << i << ", j = " << j << "\n";
                    cout << "1. counter += " << min_count << "\n";
                    cout << "counter = " << counter << "\n";
                    cout << "\n\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\n";
                    }
                    cout << "\n";
                }
            }
        }
    }

    if (test > 0) { cout << "stage two:\n"; }

    int path[6];
    int path_count, curr, temp;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            while (table[i][j] > 0) {
                if (test > 0) { cout << "i = " << i << ", j = " << j << "\n"; }

                for (int k = 0; k < 6; k++) { path[k] = -1; }
                path[i] = j;
                min_count = table[i][j];
                if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                curr = j;
                while (path[curr] < 0) {
                    for (int k = 0; k < 6; k++) {
                        if (table[curr][k] != 0) {
                            if (min_count > table[curr][k]) {
                                min_count = table[curr][k];
                                if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                            }

                            path[curr] = k;
                            curr = k;

                            break;
                        }
                    }
                }

                for (int k = curr; ; ) {
                    table[k][path[k]] -= min_count;
                    k = path[k];
                    if (k == curr) { break; }
                }

                if (test > 0) {
                    for (int k = 0; k < 6; k++) {
                        cout << path[k] << " ";
                    }
                    cout << "\ncurr = " << curr << "\n";
                    cout << "\n";
                }

                path_count = 0;

                while (path[curr] >= 0) {
                    path_count++;
                    temp = curr;
                    curr = path[curr];
                    path[temp] = -1;
                }

                counter += min_count * (path_count - 1);

                if (test > 0) {
                    cout << "path_count = " << path_count << "\n";
                    cout << "min_count = " << min_count << "\n";
                    cout << "2. counter += " << min_count * (path_count - 1) << "\n";
                    cout << "counter = " << counter << "\n";
                }

                if (test > 0) {
                    cout << "\nafter this step\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\n";
                    }
                    cout << "\n\n";
                }
            }
        }
    }

    return counter;
}

int kSimilarity_shitshitshit_dont_work_at_all(string A, string B) {
    int test = 1;
    int table[6][7];
    for (int i = 0; i < 6; i++) { for (int j = 0; j < 7; j++) { table[i][j] = 0; } }
    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            table[A[i] - 97][B[i] - 97]++;
            table[A[i] - 97][B[i] - 97]++;
            table[A[i] - 97][6]++;
            //count_total++;
        }
    }
    if (test > 0) {
        cout << "\n\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";
    }

    int result = 0, min_count;

    if (test > 0) { cout << "stage one\n"; }

    // dealing with pairs
    for (int i = 0, min_count; i < 6; i++) {
        for (int j = 0; (table[i][6] > 0) && (j < 6); j++) {
            if ((table[i][j] > 0) && (table[j][i] > 0)) {
                min_count = min(table[i][j], table[j][i]);
                result += min_count;
                //count_total -= min_count * 2;
                table[i][j] -= min_count;
                table[j][i] -= min_count;

                if (test > 0) {
                    cout << "i = " << i << ", j = " << j << "\n";
                    cout << "result += " << min_count << "\n";
                    cout << "result = " << result << "\n";
                    cout << "\n\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\n";
                    }
                    cout << "\n";
                }
            }
        }
    }

    if (test > 0) { cout << "stage two:\n"; }

    int start; for (int i = 0; i < 6; i++) { if (table[i][6] > 0) { start = i; break; } }

    int path[6][2];
    int path_count, curr, temp;
    stack<pair<int, int>> record;
    for (int i = 0; i < 6; i++) {
        /*if (table[start][i] > 0) {// take any of them start point
            while (table[i][j] > 0) {
                if (test > 0) { cout << "i = " << i << ", j = " << j << "\n"; }

                for (int k = 0; k < 6; k++) { path[k][0] = -1, path[k][1] = 0; }
                path[i] = j;
                min_count = table[i][j];
                if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                curr = j;
                while (path[curr] < 0) {
                    for (int k = 0; k < 6; k++) {
                        if (table[curr][k] != 0) {
                            if (min_count > table[curr][k]) {
                                min_count = table[curr][k];
                                if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                            }

                            path[curr] = k;
                            curr = k;

                            break;
                        }
                    }
                }

                for (int k = curr; ; ) {
                    table[k][path[k]] -= min_count;
                    k = path[k];
                    if (k == curr) { break; }
                }

                if (test > 0) {
                    for (int k = 0; k < 6; k++) {
                        cout << path[k] << " ";
                    }
                    cout << "\ncurr = " << curr << "\n";
                    cout << "\n";
                }

                path_count = 0;

                while (path[curr] >= 0) {
                    path_count++;
                    temp = curr;
                    curr = path[curr];
                    path[temp] = -1;
                }

                result += min_count * (path_count - 1);

                if (test > 0) {
                    cout << "path_count = " << path_count << "\n";
                    cout << "min_count = " << min_count << "\n";
                    cout << "counter += " << min_count * (path_count - 1) << "\n";
                    cout << "counter = " << counter << "\n";
                    cout << "\nafter this step\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\n";
                    }
                    cout << "\n\n";
                }
            }
        }*/
    }

    return result;
}

int kSimilarity_still___fuck(string A, string B) {
    int test = 1;

    int edge_counter = 0;

    int table[6][7];// table[i][6] counts how many different indexes are in this row is non zero
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            table[i][j] = 0;
        }
    }
    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            // if table[A[i] - 97][B[i] - 97] is 0 before this step, new index found, index counter++
            if (table[A[i] - 97][B[i] - 97] == 0) { table[A[i] - 97][6]++; }

            table[A[i] - 97][B[i] - 97]++;
            edge_counter++;
        }
    }

    if (test > 0) {
        cout << "\ninitial table:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\t" << table[i][6] << "\n";
        }
        cout << "\n\n";
    }

    int result = 0, min_count;

    if (test > 0) { cout << "stage one: deal with pairs\n"; }
    // deal with pairs
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            if ((table[i][j] > 0) && (table[j][i] > 0)) {
                min_count = min(table[i][j], table[j][i]);
                result += min_count;

                table[i][j] -= min_count;
                table[j][i] -= min_count;

                if (table[i][j] == 0) { table[i][6]--; }
                if (table[j][i] == 0) { table[j][6]--; }

                edge_counter -= min_count * 2;

                if (test > 0) {
                    cout << "i = " << i << ", j = " << j << "\n";
                    cout << "result += " << min_count << "\n";
                    cout << "result = " << result << "\n";
                    cout << "\nafter this step:\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\t" << table[i][6] << "\n";
                    }
                    cout << "\n";
                }
            }
        }
    }

    if (test > 0) { cout << "stage two:\n"; }
    int path[6];
    int outer_triangle_start_idx = 1, second_idx, third_idx;
    while (edge_counter > 0) {
        if (test > 0) { cout << "try to find outer triangles:\n"; }
        while (outer_triangle_start_idx >= 0) {
            outer_triangle_start_idx = -1;

            for (int i = 0; i < 6; i++) {
                if (table[i][6] == 1) {
                    outer_triangle_start_idx = i;

                    second_idx = 0;// there's only one non-empty number in this row --- (table[i][6] == 1)
                    while (table[outer_triangle_start_idx][second_idx] == 0) { second_idx++; }
                    if (test > 0) { cout << "second_idx = " << second_idx << "\n"; }

                    third_idx = -1;
                    for (int m = 0; m < 6; m++) {
                        if ((table[second_idx][m] > 0) && (table[m][outer_triangle_start_idx] > 0)) {
                            third_idx = m;
                            break;
                        }
                    }

                    if (test > 0) { cout << "third_idx = " << third_idx << "\n"; }

                    if (third_idx >= 0) {
                        min_count = table[i][second_idx];
                        if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                        if (min_count > table[third_idx][i]) { min_count = table[third_idx][i]; }

                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }

                        table[i][second_idx] -= min_count;
                        table[second_idx][third_idx] -= min_count;
                        table[third_idx][i] -= min_count;

                        if (table[i][second_idx] == 0) { table[i][6]--; }
                        if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                        if (table[third_idx][i] == 0) { table[third_idx][6]--; }

                        edge_counter -= min_count * 3;

                        result += min_count * 2;

                        if (test > 0) {
                            cout << "result += " << min_count * 2 << "\n";
                            cout << "result = " << result << "\n";
                            cout << "\nafter this step\n";
                            for (int i = 0; i < 6; i++) {
                                for (int j = 0; j < 6; j++) {
                                    cout << table[i][j] << " ";
                                }
                                cout << "\n";
                            }
                            cout << "\n\n";
                        }
                    }

                    outer_triangle_start_idx = -1;
                }
            }
        }

        if (test > 0) { cout << "done with tring to find outer triangles:\n"; }
        for (int i = 0, path_count, curr, temp; i < 6; i++) {
            if (table[i][6] > 0) {
                for (int j = i + 1; j < 6; j++) {
                    if (table[i][j] > 0) {
                        if (test > 0) { cout << "i = " << i << ", j = " << j << "\n"; }

                        for (int k = 0; k < 6; k++) { path[k] = -1; }
                        path[i] = j;
                        min_count = table[i][j];
                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                        curr = j;
                        while (path[curr] < 0) {
                            for (int k = 0; k < 6; k++) {
                                if (table[curr][k] != 0) {
                                    if (min_count > table[curr][k]) {
                                        min_count = table[curr][k];
                                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                                    }

                                    path[curr] = k;
                                    curr = k;

                                    break;
                                }
                            }
                        }

                        for (int k = curr; ; ) {
                            table[k][path[k]] -= min_count;
                            k = path[k];
                            if (k == curr) { break; }
                        }

                        if (test > 0) {
                            for (int k = 0; k < 6; k++) {
                                cout << path[k] << " ";
                            }
                            cout << "\ncurr = " << curr << "\n";
                            cout << "\n";
                        }

                        path_count = 0;

                        while (path[curr] >= 0) {
                            path_count++;
                            temp = curr;
                            curr = path[curr];
                            path[temp] = -1;
                        }

                        result += min_count * (path_count - 1);
                        edge_counter -= min_count * path_count;

                        if (test > 0) {
                            cout << "path_count = " << path_count << "\n";
                            cout << "min_count = " << min_count << "\n";
                            cout << "result += " << min_count * (path_count - 1) << "\n";
                            cout << "result = " << result << "\n";
                            cout << "\nafter this step\n";
                            for (int i = 0; i < 6; i++) {
                                for (int j = 0; j < 6; j++) {
                                    cout << table[i][j] << " ";
                                }
                                cout << "\t" << table[i][6] << "\n";
                            }
                            cout << "\n\n";
                        }
                    }
                }
            }
        }
    }

    return result;
}
int kSimilarity_no_test(string A, string B) {
    int edge_counter = 0;

    int table[6][7];// table[i][6] counts how many different indexes are in this row is non zero
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            table[i][j] = 0;
        }
    }
    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            // if table[A[i] - 97][B[i] - 97] is 0 before this step, new index found, index counter++
            if (table[A[i] - 97][B[i] - 97] == 0) { table[A[i] - 97][6]++; }

            table[A[i] - 97][B[i] - 97]++;
            edge_counter++;
        }
    }

    int result = 0, min_count;

    // deal with pairs
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            if ((table[i][j] > 0) && (table[j][i] > 0)) {
                min_count = min(table[i][j], table[j][i]);
                result += min_count;

                table[i][j] -= min_count;
                table[j][i] -= min_count;

                if (table[i][j] == 0) { table[i][6]--; }
                if (table[j][i] == 0) { table[j][6]--; }

                edge_counter -= min_count * 2;
            }
        }
    }

    int path[6];
    int outer_triangle_start_idx = 1, second_idx, third_idx;
    while (edge_counter > 0) {
        while (outer_triangle_start_idx >= 0) {
            outer_triangle_start_idx = -1;

            for (int i = 0; i < 6; i++) {
                if (table[i][6] == 1) {
                    outer_triangle_start_idx = i;

                    second_idx = 0;// there's only one non-empty number in this row --- (table[i][6] == 1)
                    while (table[outer_triangle_start_idx][second_idx] == 0) { second_idx++; }

                    third_idx = -1;
                    for (int m = 0; m < 6; m++) {
                        if ((table[second_idx][m] > 0) && (table[m][outer_triangle_start_idx] > 0)) {
                            third_idx = m;
                            break;
                        }
                    }

                    if (third_idx >= 0) {
                        min_count = table[i][second_idx];
                        if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                        if (min_count > table[third_idx][i]) { min_count = table[third_idx][i]; }

                        table[i][second_idx] -= min_count;
                        table[second_idx][third_idx] -= min_count;
                        table[third_idx][i] -= min_count;

                        if (table[i][second_idx] == 0) { table[i][6]--; }
                        if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                        if (table[third_idx][i] == 0) { table[third_idx][6]--; }

                        edge_counter -= min_count * 3;

                        result += min_count * 2;
                    }

                    outer_triangle_start_idx = -1;
                }
            }
        }

        for (int i = 0, path_count, curr, temp; i < 6; i++) {
            if (table[i][6] > 0) {
                for (int j = i + 1; j < 6; j++) {
                    if (table[i][j] > 0) {
                        for (int k = 0; k < 6; k++) { path[k] = -1; }
                        path[i] = j;
                        min_count = table[i][j];
                        curr = j;
                        while (path[curr] < 0) {
                            for (int k = 0; k < 6; k++) {
                                if (table[curr][k] != 0) {
                                    if (min_count > table[curr][k]) {
                                        min_count = table[curr][k];
                                    }

                                    path[curr] = k;
                                    curr = k;

                                    break;
                                }
                            }
                        }

                        for (int k = curr; ; ) {
                            table[k][path[k]] -= min_count;
                            k = path[k];
                            if (k == curr) { break; }
                        }

                        path_count = 0;

                        while (path[curr] >= 0) {
                            path_count++;
                            temp = curr;
                            curr = path[curr];
                            path[temp] = -1;
                        }

                        result += min_count * (path_count - 1);
                        edge_counter -= min_count * path_count;
                    }
                }
            }
        }
    }

    return result;
}



//  really?! do i really need a dfs?! fuck
//  i need a dfs in this particular problem
int kSimilarity_not_working(string A, string B) {
    int test = 0;
    int edge_counter = 0;

    int table[6][7];// table[i][6] counts how many different indexes are in this row is non zero
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            table[i][j] = 0;
        }
    }
    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            // if table[A[i] - 97][B[i] - 97] is 0 before this step, new index found, index counter++
            if (table[A[i] - 97][B[i] - 97] == 0) { table[A[i] - 97][6]++; }

            table[A[i] - 97][B[i] - 97]++;
            edge_counter++;
        }
    }

    if (test > 0) {
        cout << "\ninitial table:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\t" << table[i][6] << "\n";
        }
        cout << "\n\n";
    }

    int result = 0, min_count;

    if (test > 0) { cout << "stage one: deal with pairs\n"; }
    // deal with pairs
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            if ((table[i][j] > 0) && (table[j][i] > 0)) {
                min_count = min(table[i][j], table[j][i]);
                result += min_count;

                table[i][j] -= min_count;
                table[j][i] -= min_count;

                if (table[i][j] == 0) { table[i][6]--; }
                if (table[j][i] == 0) { table[j][6]--; }

                edge_counter -= min_count * 2;

                if (test > 0) {
                    cout << "i = " << i << ", j = " << j << "\n";
                    cout << "result += " << min_count << "\n";
                    cout << "result = " << result << "\n";
                    cout << "\nafter this step:\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\t" << table[i][6] << "\n";
                    }
                    cout << "\n";
                }
            }
        }
    }

    if (test > 0) { cout << "stage two:\n"; }
    int path[6];
    int max_triangle = 0;
    //stack<pair<int, int>> path;
    //stack<int> value;
    int outer_triangle_start_idx = 1, second_idx, third_idx = 0;
    while (edge_counter > 0) {
        if (test > 0) { cout << "try to find outer triangles:\n"; }
        while (edge_counter > 0 && third_idx >= 0) {
            third_idx = -1;

            for (int i = 0; i < 6; i++) {
                //cout << "i = " << i << "\n";
                outer_triangle_start_idx = -1;
                if (table[i][6] == 1) {
                    outer_triangle_start_idx = i;

                    second_idx = 0;// there's only one non-empty number in this row --- (table[i][6] == 1)
                    while (second_idx < 6 && table[outer_triangle_start_idx][second_idx] == 0) { second_idx++; }
                    if (test > 0) { cout << "second_idx = " << second_idx << "\n"; }

                    third_idx = -1;
                    if (second_idx < 6) {
                        for (int m = 0; m < 6; m++) {
                            if ((table[second_idx][m] > 0) && (table[m][outer_triangle_start_idx] > 0)) {
                                third_idx = m;
                                break;
                            }
                        }
                    }

                    else { outer_triangle_start_idx = -1; }

                    if (test > 0) { cout << "third_idx = " << third_idx << "\n"; }

                    if (third_idx >= 0) {
                        min_count = table[i][second_idx];
                        if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                        if (min_count > table[third_idx][i]) { min_count = table[third_idx][i]; }

                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }

                        table[i][second_idx] -= min_count;
                        table[second_idx][third_idx] -= min_count;
                        table[third_idx][i] -= min_count;

                        if (table[i][second_idx] == 0) { table[i][6]--; }
                        if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                        if (table[third_idx][i] == 0) { table[third_idx][6]--; }

                        edge_counter -= min_count * 3;

                        result += min_count * 2;

                        if (test > 0) {
                            cout << "result += " << min_count * 2 << "\n";
                            cout << "result = " << result << "\n";
                            cout << "\nafter this step\n";
                            for (int i = 0; i < 6; i++) {
                                for (int j = 0; j < 6; j++) {
                                    cout << table[i][j] << " ";
                                }
                                cout << "\n";
                            }
                            cout << "\n\n";
                        }
                    }
                }
            }
        }

        if (test > 0) { cout << "done with tring to find outer triangles:\n"; }
        for (int i = 0, path_count, curr, temp; i < 6; i++) {
            if (table[i][6] > 0) {
                for (int j = i + 1; j < 6; j++) {
                    if (table[i][j] > 0) {
                        //if (test > 0) { cout << "i = " << i << ", j = " << j << "\n"; }

                        for (int k = 0; k < 6; k++) { path[k] = -1; }
                        path[i] = j;
                        min_count = table[i][j];
                        //if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                        curr = j;

                        while (path[curr] < 0) {
                            for (int k = 0; k < 6; k++) {
                                if (table[curr][k] != 0) {
                                    if (min_count > table[curr][k]) {
                                        min_count = table[curr][k];
                                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                                    }

                                    path[curr] = k;
                                    curr = k;

                                    break;
                                }
                            }
                        }

                        //cout << "~0!\n";

                        for (int k = curr; ; ) {
                            table[k][path[k]] -= min_count;
                            k = path[k];
                            if (k == curr) { break; }
                        }

                        //cout << "~1!\n";

                        if (test > 0) {
                            for (int k = 0; k < 6; k++) {
                                cout << path[k] << " ";
                            }
                            cout << "\ncurr = " << curr << "\n";
                            cout << "\n";
                        }

                        path_count = 0;

                        //cout << "~2!\n";

                        while (path[curr] >= 0) {
                            path_count++;
                            temp = curr;
                            curr = path[curr];
                            path[temp] = -1;
                        }

                        result += min_count * (path_count - 1);
                        edge_counter -= min_count * path_count;

                        if (test > 0) {
                            cout << "path_count = " << path_count << "\n";
                            cout << "min_count = " << min_count << "\n";
                            cout << "result += " << min_count * (path_count - 1) << "\n";
                            cout << "result = " << result << "\n";
                            cout << "\nafter this step\n";
                            for (int i = 0; i < 6; i++) {
                                for (int j = 0; j < 6; j++) {
                                    cout << table[i][j] << " ";
                                }
                                cout << "\t" << table[i][6] << "\n";
                            }
                            cout << "\n\n";
                        }
                    }
                }
            }
        }
    }

    return result;
}

int kSimilarity_unfinished_draft(string A, string B) {
    int test = 1;
    int edge_counter = 0;

    int table[6][6];// table[i][6] counts how many different indexes are in this row is non zero
    for (int i = 0; i < 6; i++) { for (int j = 0; j < 7; j++) { table[i][j] = 0; } }
    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            // if table[A[i] - 97][B[i] - 97] is 0 before this step, new index found, index counter++
            if (table[A[i] - 97][B[i] - 97] == 0) { table[A[i] - 97][6]++; }

            table[A[i] - 97][B[i] - 97]++;
            edge_counter++;
        }
    }

    if (test > 0) {
        cout << "\ninitial table:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\t" << table[i][6] << "\n";
        }
        cout << "\n\n";
    }

    int result = 0, min_count;

    if (test > 0) { cout << "stage one: deal with pairs\n"; }
    // deal with pairs
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            if ((table[i][j] > 0) && (table[j][i] > 0)) {
                min_count = min(table[i][j], table[j][i]);
                result += min_count;

                table[i][j] -= min_count;
                table[j][i] -= min_count;

                if (table[i][j] == 0) { table[i][6]--; }
                if (table[j][i] == 0) { table[j][6]--; }

                edge_counter -= min_count * 2;

                if (test > 0) {
                    cout << "i = " << i << ", j = " << j << "\n";
                    cout << "result += " << min_count << "\n";
                    cout << "result = " << result << "\n";
                    cout << "\nafter this step:\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\t" << table[i][6] << "\n";
                    }
                    cout << "\n";
                }
            }
        }
    }

    if (test > 0) { cout << "stage two:\n"; }
    int path[6];
    int max_triangle = 0;
    stack<pair<pair<int, int>, pair<int, int>>> history;// position 1, position 2, value, 1st 2nd or 3rd point
    int triangle_start_idx = 1, second_idx, third_idx;

    int stack_length = (6 * (6 - 1)) / 2;
    int curr_max_path[stack_length][2];
    for (int i = 0; i < stack_length; i++) {
        curr_max_path[i][0] = -1;
        curr_max_path[i][1] = -1;
        curr_max_path[i][2] = -1;
    }

    int curr_idx = -1, curr_triangle = 0, done;
    // probably do not need to initialize curr_path
    int curr_path[stack_length][2];// [i][0] is value, [i][1] is counter
    for (int i = 0; i < stack_length; i++) {
        curr_path[i][0] = -1;
        curr_path[i][1] = -1;
        curr_path[i][2] = -1;
    }

    while (edge_counter > 0) {
        if (test > 0) { cout << "\ntry to find outer triangles:\n"; }
        while (triangle_start_idx >= 0) {
            triangle_start_idx = -1;

            for (int i = 0; i < 6; i++) {
                if (table[i][6] == 1) {
                    triangle_start_idx = i;

                    second_idx = 0;// there's only one non-empty number in this row --- (table[i][6] == 1)
                    while (table[triangle_start_idx][second_idx] == 0) { second_idx++; }
                    if (test > 0) { cout << "second_idx = " << second_idx << "\n"; }

                    third_idx = -1;
                    for (int m = 0; m < 6; m++) {
                        if ((table[second_idx][m] > 0) && (table[m][triangle_start_idx] > 0)) {
                            third_idx = m;
                            break;
                        }
                    }

                    if (test > 0) { cout << "third_idx = " << third_idx << "\n"; }

                    if (third_idx >= 0) {
                        min_count = table[i][second_idx];
                        if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                        if (min_count > table[third_idx][i]) { min_count = table[third_idx][i]; }

                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }

                        table[i][second_idx] -= min_count;
                        table[second_idx][third_idx] -= min_count;
                        table[third_idx][i] -= min_count;

                        if (table[i][second_idx] == 0) { table[i][6]--; }
                        if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                        if (table[third_idx][i] == 0) { table[third_idx][6]--; }

                        edge_counter -= min_count * 3;

                        result += min_count * 2;

                        if (test > 0) {
                            cout << "result += " << min_count * 2 << "\n";
                            cout << "result = " << result << "\n";
                            cout << "\nafter this step\n";
                            for (int i = 0; i < 6; i++) {
                                for (int j = 0; j < 6; j++) {
                                    cout << table[i][j] << " ";
                                }
                                cout << "\n";
                            }
                            cout << "\n\n";
                        }
                    }

                    triangle_start_idx = -1;
                }
            }
        }

        if (test > 0) { cout << "\ntry to find MAX triangles:\n"; }
        /*for (int i = 0; i < 6; i++) { if (table[i][6] > 1) { triangle_start_idx = i; } }
        bool first_probe = 1;
        while (true) {
            if (first_probe == 1) {
                third_idx = -1;
                for (int i = 0; i < 6; i++) {
                    if (table[triangle_start_idx][i] > 0) {
                        for (int j = 0; j < 6; j++) {
                            if (table[i][j] > 0 && table[j][triangle_start_idx] > 0) {
                                second_idx = i, third_idx = j;
                                break;
                            }
                        }
                    }
                }

                if (third_idx >= 0) {
                    min_count = table[triangle_start_idx][second_idx];
                    if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                    if (min_count > table[third_idx][triangle_start_idx]) { min_count = table[third_idx][triangle_start_idx]; }

                    if (test > 0) { cout << "min_count = " << min_count << "\n"; }

                    curr_idx++;
                    curr_path[curr_idx][0] = triangle_start_idx, curr_path[curr_idx][1] = min_count;
                    curr_idx++;
                    curr_path[curr_idx][0] = second_idx, curr_path[curr_idx][1] = min_count;
                    curr_idx++;
                    curr_path[curr_idx][0] = third_idx, curr_path[curr_idx][1] = min_count;

                    table[triangle_start_idx][second_idx] -= min_count;
                    table[second_idx][third_idx] -= min_count;
                    table[third_idx][triangle_start_idx] -= min_count;

                    if (table[triangle_start_idx][second_idx] == 0) { table[triangle_start_idx][6]--; }
                    if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                    if (table[third_idx][triangle_start_idx] == 0) { table[third_idx][6]--; }

                    result += min_count * 2;

                    if (test > 0) {
                        cout << "result += " << min_count * 2 << "\n";
                        cout << "result = " << result << "\n";
                        cout << "\nafter this step\n";
                        for (int i = 0; i < 6; i++) {
                            for (int j = 0; j < 6; j++) {
                                cout << table[i][j] << " ";
                            }
                            cout << "\n";
                        }
                        cout << "\n\n";
                    }
                }

                else {
                    if (curr_triangle > max_triangle) {
                        max_triangle = curr_triangle;
                        for (int i = 0; i < stack_length; i++) {
                            if (curr_path[i][0] >= 0) {
                                curr_max_path[i][0] = curr_path[i][0];
                                curr_max_path[i][1] = curr_path[i][1];
                            }
                            else {
                                curr_path[i][0] = -1;
                                curr_path[i][1] = -1;
                            }
                        }
                    }

                    first_probe = 0;
                }

                triangle_start_idx = -1;
            }
            else {

            }
        }*/

        // modify it & try to make it work
        for (int i = 0, path_count, curr, temp; i < 6; i++) {
            if (table[i][6] > 0) {
                for (int j = i + 1; j < 6; j++) {
                    if (table[i][j] > 0) {
                        if (test > 0) { cout << "i = " << i << ", j = " << j << "\n"; }

                        for (int k = 0; k < 6; k++) { path[k] = -1; }
                        path[i] = j;
                        min_count = table[i][j];
                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                        curr = j;
                        while (path[curr] < 0) {
                            for (int k = 0; k < 6; k++) {
                                if (table[curr][k] != 0) {
                                    if (min_count > table[curr][k]) {
                                        min_count = table[curr][k];
                                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                                    }

                                    path[curr] = k;
                                    curr = k;

                                    break;
                                }
                            }
                        }

                        for (int k = curr; ; ) {
                            table[k][path[k]] -= min_count;
                            k = path[k];
                            if (k == curr) { break; }
                        }

                        if (test > 0) {
                            for (int k = 0; k < 6; k++) {
                                cout << path[k] << " ";
                            }
                            cout << "\ncurr = " << curr << "\n";
                            cout << "\n";
                        }

                        path_count = 0;

                        while (path[curr] >= 0) {
                            path_count++;
                            temp = curr;
                            curr = path[curr];
                            path[temp] = -1;
                        }

                        result += min_count * (path_count - 1);
                        edge_counter -= min_count * path_count;

                        if (test > 0) {
                            cout << "path_count = " << path_count << "\n";
                            cout << "min_count = " << min_count << "\n";
                            cout << "result += " << min_count * (path_count - 1) << "\n";
                            cout << "result = " << result << "\n";
                            cout << "\nafter this step\n";
                            for (int i = 0; i < 6; i++) {
                                for (int j = 0; j < 6; j++) {
                                    cout << table[i][j] << " ";
                                }
                                cout << "\t" << table[i][6] << "\n";
                            }
                            cout << "\n\n";
                        }
                    }
                }
            }
        }

        if (test > 0) { cout << "\ndone with tring to find triangles:\n"; }
        for (int i = 0, path_count, curr, temp; i < 6; i++) {
            if (table[i][6] > 0) {
                for (int j = i + 1; j < 6; j++) {
                    if (table[i][j] > 0) {
                        if (test > 0) { cout << "i = " << i << ", j = " << j << "\n"; }

                        for (int k = 0; k < 6; k++) { path[k] = -1; }
                        path[i] = j;
                        min_count = table[i][j];
                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                        curr = j;
                        while (path[curr] < 0) {
                            for (int k = 0; k < 6; k++) {
                                if (table[curr][k] != 0) {
                                    if (min_count > table[curr][k]) {
                                        min_count = table[curr][k];
                                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                                    }

                                    path[curr] = k;
                                    curr = k;

                                    break;
                                }
                            }
                        }

                        for (int k = curr; ; ) {
                            table[k][path[k]] -= min_count;
                            k = path[k];
                            if (k == curr) { break; }
                        }

                        if (test > 0) {
                            for (int k = 0; k < 6; k++) {
                                cout << path[k] << " ";
                            }
                            cout << "\ncurr = " << curr << "\n";
                            cout << "\n";
                        }

                        path_count = 0;

                        while (path[curr] >= 0) {
                            path_count++;
                            temp = curr;
                            curr = path[curr];
                            path[temp] = -1;
                        }

                        result += min_count * (path_count - 1);
                        edge_counter -= min_count * path_count;

                        if (test > 0) {
                            cout << "path_count = " << path_count << "\n";
                            cout << "min_count = " << min_count << "\n";
                            cout << "result += " << min_count * (path_count - 1) << "\n";
                            cout << "result = " << result << "\n";
                            cout << "\nafter this step\n";
                            for (int i = 0; i < 6; i++) {
                                for (int j = 0; j < 6; j++) {
                                    cout << table[i][j] << " ";
                                }
                                cout << "\t" << table[i][6] << "\n";
                            }
                            cout << "\n\n";
                        }
                    }
                }
            }
        }
    }

    return result;
}

int kSimilarity_promising_lead_but(string A, string B) {
    int edge_counter = 0;

    int table[6][7];// table[i][6] counts how many different indexes are in this row is non zero
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            table[i][j] = 0;
        }
    }
    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            // if table[A[i] - 97][B[i] - 97] is 0 before this step, new index found, index counter++
            if (table[A[i] - 97][B[i] - 97] == 0) { table[A[i] - 97][6]++; }

            table[A[i] - 97][B[i] - 97]++;
            edge_counter++;
        }
    }

    int result = 0, min_count;

    // deal with pairs
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            if ((table[i][j] > 0) && (table[j][i] > 0)) {
                min_count = min(table[i][j], table[j][i]);
                result += min_count;

                table[i][j] -= min_count;
                table[j][i] -= min_count;

                if (table[i][j] == 0) { table[i][6]--; }
                if (table[j][i] == 0) { table[j][6]--; }

                edge_counter -= min_count * 2;
            }
        }
    }

    int path[6];
    int outer_triangle_start_idx = 1, second_idx, third_idx;
    while (edge_counter > 0) {
        while (outer_triangle_start_idx >= 0) {
            outer_triangle_start_idx = -1;

            for (int i = 0; i < 6; i++) {
                if (table[i][6] == 1) {
                    outer_triangle_start_idx = i;

                    second_idx = 0;// there's only one non-empty number in this row --- (table[i][6] == 1)
                    while (table[outer_triangle_start_idx][second_idx] == 0) { second_idx++; }

                    third_idx = -1;
                    for (int m = 0; m < 6; m++) {
                        if ((table[second_idx][m] > 0) && (table[m][outer_triangle_start_idx] > 0)) {
                            third_idx = m;
                            break;
                        }
                    }

                    if (third_idx >= 0) {
                        min_count = table[i][second_idx];
                        if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                        if (min_count > table[third_idx][i]) { min_count = table[third_idx][i]; }

                        table[i][second_idx] -= min_count;
                        table[second_idx][third_idx] -= min_count;
                        table[third_idx][i] -= min_count;

                        if (table[i][second_idx] == 0) { table[i][6]--; }
                        if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                        if (table[third_idx][i] == 0) { table[third_idx][6]--; }

                        edge_counter -= min_count * 3;

                        result += min_count * 2;
                    }

                    outer_triangle_start_idx = -1;
                }
            }
        }

        for (int i = 0, path_count, curr, temp; i < 6; i++) {
            if (table[i][6] > 0) {
                for (int j = i + 1; j < 6; j++) {
                    if (table[i][j] > 0) {
                        for (int k = 0; k < 6; k++) { path[k] = -1; }
                        path[i] = j;
                        min_count = table[i][j];
                        curr = j;
                        while (path[curr] < 0) {
                            for (int k = 0; k < 6; k++) {
                                if (table[curr][k] != 0) {
                                    if (min_count > table[curr][k]) {
                                        min_count = table[curr][k];
                                    }

                                    path[curr] = k;
                                    curr = k;

                                    break;
                                }
                            }
                        }

                        for (int k = curr; ; ) {
                            table[k][path[k]] -= min_count;
                            k = path[k];
                            if (k == curr) { break; }
                        }

                        path_count = 0;

                        while (path[curr] >= 0) {
                            path_count++;
                            temp = curr;
                            curr = path[curr];
                            path[temp] = -1;
                        }

                        result += min_count * (path_count - 1);
                        edge_counter -= min_count * path_count;
                    }
                }
            }
        }
    }

    return result;
}




//  WORKED!!!
int kSimilarity_1_0(string A, string B) {
    int test = 0;
    int edge_counter = 0;

    int table[6][7];// table[i][6] counts how many different indexes are in this row is non zero
    for (int i = 0; i < 6; i++) { for (int j = 0; j < 7; j++) { table[i][j] = 0; } }
    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            // if table[A[i] - 97][B[i] - 97] is 0 before this step, new index found, index counter++
            if (table[A[i] - 97][B[i] - 97] == 0) { table[A[i] - 97][6]++; }

            table[A[i] - 97][B[i] - 97]++;
            edge_counter++;
        }
    }

    if (test > 0) {
        cout << "\ninitial table:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\t" << table[i][6] << "\n";
        }
        cout << "\n\n";
    }

    int result = 0, min_count;

    if (test > 0) { cout << "stage one: deal with pairs\n"; }
    // deal with pairs
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            if ((table[i][j] > 0) && (table[j][i] > 0)) {
                min_count = min(table[i][j], table[j][i]);
                result += min_count;

                table[i][j] -= min_count;
                table[j][i] -= min_count;

                if (table[i][j] == 0) { table[i][6]--; }
                if (table[j][i] == 0) { table[j][6]--; }

                edge_counter -= min_count * 2;

                if (test > 0) {
                    cout << "i = " << i << ", j = " << j << "\n";
                    cout << "result += " << min_count << "\n";
                    cout << "result = " << result << "\n";
                    cout << "\nafter this step:\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\t" << table[i][6] << "\n";
                    }
                    cout << "\n";
                }
            }
        }
    }

    if (test > 0) { cout << "\n"; }

    int first_idx = 1, second_idx, third_idx = 0;

    if (test > 0) { cout << "stage two: try to find outer triangles:\n"; }
    while (edge_counter > 0 && third_idx >= 0) {
        third_idx = -1;

        for (int i = 0; i < 6; i++) {
            if (table[i][6] == 1) {
                first_idx = i;

                second_idx = 0;// there's only one non-empty number in this row --- (table[i][6] == 1)
                while (table[first_idx][second_idx] == 0) { second_idx++; }
                if (test > 0) { cout << "second_idx = " << second_idx << "\n"; }

                third_idx = -1;
                for (int m = 0; m < 6; m++) {
                    if (table[second_idx][m] > 0 && table[m][first_idx] > 0) {
                        third_idx = m;
                        break;
                    }
                }

                if (test > 0) { cout << "third_idx = " << third_idx << "\n"; }

                if (third_idx >= 0) {
                    min_count = table[i][second_idx];
                    if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                    if (min_count > table[third_idx][i]) { min_count = table[third_idx][i]; }

                    if (test > 0) { cout << "min_count = " << min_count << "\n"; }

                    table[i][second_idx] -= min_count;
                    table[second_idx][third_idx] -= min_count;
                    table[third_idx][i] -= min_count;

                    if (table[i][second_idx] == 0) { table[i][6]--; }
                    if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                    if (table[third_idx][i] == 0) { table[third_idx][6]--; }

                    edge_counter -= min_count * 3;

                    result += min_count * 2;

                    if (test > 0) {
                        cout << "result += " << min_count * 2 << "\n";
                        cout << "result = " << result << "\n";
                        cout << "\nafter this step\n";
                        for (int i = 0; i < 6; i++) {
                            for (int j = 0; j < 6; j++) {
                                cout << table[i][j] << " ";
                            }
                            cout << "\t" << table[i][6] << "\n";
                        }
                        cout << "\n\n";
                    }
                }

                //first_idx = -1;
            }
        }
    }


    if (test > 0) { cout << "stage three: try to extract most triangles:\n"; }
    int max_triangle = 0, temp;
    vector<vector<int>> path_with_max_triangle;
    vector<vector<int>> history;// coordinate 1, coordinate 2, value, 1st/2nd/3rd point
    history.push_back({-1, -1, 0, 0});
    int proceed_not_going_back = 1;// 1 proceed; 2 proceed at the last triangle & replace it;
    bool found;
    while (edge_counter > 0 && history.size() > 0) {
        found = 0;
        //  find triangle
        //      with no prev info
        //      with prev info, only try points after curr_points
        if (proceed_not_going_back == 1) {// no prev info
            first_idx = -1, second_idx = -1, third_idx = -1;
            if (test > 0) { cout << "~0!\n"; }

            for (int i = 0; i < 6 && found == 0; i++) {
                if (table[i][6] > 0) {
                    if (test > 0) { cout << "~0.1!\n"; }
                    first_idx = i;

                    for (int j = 0; j < 6 && found == 0; j++) {
                        if (j != first_idx && table[i][j] > 0) {
                            if (test > 0) { cout << "~0.2!\n"; }
                            second_idx = j;

                            for (int k = 0; k < 6; k++) {
                                if (k != first_idx && k != second_idx && table[j][k] > 0 && table[k][i] > 0) {//  if found, proceed, push_back values into vector
                                    if (test > 0) { cout << "~0.3!\n"; }
                                    third_idx = k;

                                    min_count = table[i][second_idx];
                                    if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                                    if (min_count > table[third_idx][i]) { min_count = table[third_idx][i]; }

                                    if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                                    history.push_back({i, j, k, min_count});

                                    table[i][second_idx] -= min_count;
                                    table[second_idx][third_idx] -= min_count;
                                    table[third_idx][i] -= min_count;

                                    if (table[i][second_idx] == 0) { table[i][6]--; }
                                    if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                                    if (table[third_idx][i] == 0) { table[third_idx][6]--; }

                                    found = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if (found == 0) {
                if (history.size() - 1 > path_with_max_triangle.size()) {

                    temp = path_with_max_triangle.size();
                    for (int i = 1; i < history.size(); i++) {
                        if (i - 1 < temp) {
                            path_with_max_triangle[i - 1][0] = history[i][0];
                            path_with_max_triangle[i - 1][1] = history[i][1];
                            path_with_max_triangle[i - 1][2] = history[i][2];
                            path_with_max_triangle[i - 1][3] = history[i][3];
                        }
                        else {
                            path_with_max_triangle.push_back({history[i][0], history[i][1], history[i][2], history[i][3]});
                        }
                    }
                }
                proceed_not_going_back = 2;
            }
        }

        else {//with prev info, try to find
            first_idx = history[history.size() - 1][0];
            if (first_idx >= 0) {
                second_idx = history[history.size() - 1][1];
                third_idx = history[history.size() - 1][2];
                min_count = history[history.size() - 1][3];

                if (table[first_idx][second_idx] == 0) { table[first_idx][6]++; }
                if (table[second_idx][third_idx] == 0) { table[second_idx][6]++; }
                if (table[third_idx][first_idx] == 0) { table[third_idx][6]++; }

                table[first_idx][second_idx] += min_count;
                table[second_idx][third_idx] += min_count;
                table[third_idx][first_idx] += min_count;

                if (test > 0) {
                    cout << "\nafter rolling back\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\t" << table[i][6] << "\n";
                    }
                    cout << "\n";
                }

                for (int i = second_idx + 1; i < 6 && found == 0; i++) {
                    if (i != first_idx && table[first_idx][i] > 0) {
                        second_idx = i;

                        for (int k = 0; k < 6; k++) {
                            if (k != first_idx && k != second_idx && table[second_idx][k] > 0 && table[k][first_idx] > 0) {//  if found, proceed, push_back values into vector
                                third_idx = k;

                                min_count = table[first_idx][second_idx];
                                if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                                if (min_count > table[third_idx][first_idx]) { min_count = table[third_idx][first_idx]; }

                                if (test > 0) { cout << "min_count = " << min_count << "\n"; }

                                history[history.size() - 1][0] = first_idx;
                                history[history.size() - 1][1] = second_idx;
                                history[history.size() - 1][2] = third_idx;
                                history[history.size() - 1][3] = min_count;

                                table[first_idx][second_idx] -= min_count;
                                table[second_idx][third_idx] -= min_count;
                                table[third_idx][first_idx] -= min_count;

                                if (table[first_idx][second_idx] == 0) { table[first_idx][6]--; }
                                if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                                if (table[third_idx][first_idx] == 0) { table[third_idx][6]--; }

                                found = 1;
                                break;
                            }
                        }

                    }
                }
            }

            if (found == 0) {
                if (history.size() - 1 > path_with_max_triangle.size()) {
                    temp = path_with_max_triangle.size();
                    for (int i = 1; i < history.size(); i++) {
                        if (i - 1 < temp) {
                            path_with_max_triangle[i - 1][0] = history[i][0];
                            path_with_max_triangle[i - 1][1] = history[i][1];
                            path_with_max_triangle[i - 1][2] = history[i][2];
                            path_with_max_triangle[i - 1][3] = history[i][3];
                        }
                        else {
                            path_with_max_triangle.push_back({history[i][0], history[i][1], history[i][2], history[i][3]});
                        }
                    }
                }
                history.pop_back();
            }

            else { proceed_not_going_back = 1; }
        }

        if (test > 0) {
            cout << "found = " << found << "\n";
            cout << "\nafter this step\n";
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    cout << table[i][j] << " ";
                }
                cout << "\t" << table[i][6] << "\n";
            }
            cout << "\n";
            cout << "history:\n";
            for (int i = 0; i < history.size(); i++) {
                cout << history[i][0] << " ";
                cout << history[i][1] << " ";
                cout << history[i][2] << " ";
                cout << history[i][3] << ";\n";
            }
            cout << "\npath_with_max_triangle:\n";
            for (int i = 0; i < path_with_max_triangle.size(); i++) {
                cout << path_with_max_triangle[i][0] << " ";
                cout << path_with_max_triangle[i][1] << " ";
                cout << path_with_max_triangle[i][2] << " ";
                cout << path_with_max_triangle[i][3] << ";\n";
            }
            cout << "\none round complete\n\n\n\n";

            test++;
            if (test > 10) break;
        }
    }

    if (history.size() > 1) {
        for (int i = 1; i < history.size(); i++) {
            first_idx = history[i][0];
            second_idx = history[i][1];
            third_idx = history[i][2];
            min_count = history[i][3];

            if (table[first_idx][second_idx] == 0) { table[first_idx][6]++; }
            if (table[second_idx][third_idx] == 0) { table[second_idx][6]++; }
            if (table[third_idx][first_idx] == 0) { table[third_idx][6]++; }

            table[first_idx][second_idx] += min_count;
            table[second_idx][third_idx] += min_count;
            table[third_idx][first_idx] += min_count;
        }
    }

    if (test > 0) {
        cout << "right before the end of 3rd stage:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\t" << table[i][6] << "\n";
        }
        cout << "\n";
    }

    for (int i = 0; i < path_with_max_triangle.size(); i++) {
        first_idx = path_with_max_triangle[i][0];
        second_idx = path_with_max_triangle[i][1];
        third_idx = path_with_max_triangle[i][2];
        min_count = path_with_max_triangle[i][3];

        table[first_idx][second_idx] -= min_count;
        table[second_idx][third_idx] -= min_count;
        table[third_idx][first_idx] -= min_count;

        if (table[first_idx][second_idx] == 0) { table[first_idx][6]--; }
        if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
        if (table[third_idx][first_idx] == 0) { table[third_idx][6]--; }

        result += min_count * 2;
        if (test > 0) { cout << "result += " << min_count * 2 << "\n"; }
        edge_counter -= min_count * 3;
    }

    if (test > 0) {
        cout << "\nresult = " << result << "\n\n";

        cout << "after 3rd stage:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\t" << table[i][6] << "\n";
        }
        cout << "\n\n";
    }

    int path[6];
    if (test > 0) { cout << "stage four: probe long lines:\n"; }
    while (edge_counter > 0) {
        for (int i = 0, path_count, curr, temp; i < 6; i++) {
            if (table[i][6] > 0) {
                for (int j = i + 1; j < 6; j++) {
                    if (table[i][j] > 0) {
                        //if (test > 0) { cout << "i = " << i << ", j = " << j << "\n"; }

                        for (int k = 0; k < 6; k++) { path[k] = -1; }
                        path[i] = j;
                        min_count = table[i][j];
                        //if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                        curr = j;

                        while (path[curr] < 0) {
                            //cout << "path[curr] = " << path[curr] << "\n";
                            for (int k = 0; k < 6; k++) {
                                if (table[curr][k] != 0) {
                                    if (min_count > table[curr][k]) {
                                        min_count = table[curr][k];
                                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                                    }

                                    path[curr] = k;
                                    curr = k;

                                    break;
                                }
                            }
                        }

                        //cout << "~0!\n";

                        for (int k = curr; ; ) {
                            table[k][path[k]] -= min_count;
                            k = path[k];
                            if (k == curr) { break; }
                        }

                        //cout << "~1!\n";

                        if (test > 0) {
                            for (int k = 0; k < 6; k++) {
                                cout << path[k] << " ";
                            }
                            cout << "\ncurr = " << curr << "\n";
                            cout << "\n";
                        }

                        path_count = 0;

                        //cout << "~2!\n";

                        while (path[curr] >= 0) {
                            path_count++;
                            temp = curr;
                            curr = path[curr];
                            path[temp] = -1;
                        }

                        result += min_count * (path_count - 1);
                        edge_counter -= min_count * path_count;

                        if (test > 0) {
                            cout << "path_count = " << path_count << "\n";
                            cout << "min_count = " << min_count << "\n";
                            cout << "result += " << min_count * (path_count - 1) << "\n";
                            cout << "result = " << result << "\n";
                            cout << "\nafter this step\n";
                            for (int i = 0; i < 6; i++) {
                                for (int j = 0; j < 6; j++) {
                                    cout << table[i][j] << " ";
                                }
                                cout << "\t" << table[i][6] << "\n";
                            }
                            cout << "\n\n";
                        }
                    }
                }
            }
        }
    }

    return result;
}



int kSimilarity_1_1(string A, string B) {
    int test = 1;
    int edge_counter = 0;

    int table[6][7];// table[i][6] counts how many different indexes are in this row is non zero
    for (int i = 0; i < 6; i++) { for (int j = 0; j < 7; j++) { table[i][j] = 0; } }
    for (int i = 0; i < A.size(); i++) {
        if (A[i] != B[i]) {
            // if table[A[i] - 97][B[i] - 97] is 0 before this step, new index found, index counter++
            if (table[A[i] - 97][B[i] - 97] == 0) { table[A[i] - 97][6]++; }

            table[A[i] - 97][B[i] - 97]++;
            edge_counter++;
        }
    }

    if (test > 0) {
        cout << "\ninitial table:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\t" << table[i][6] << "\n";
        }
        cout << "\n\n";
    }

    int result = 0, min_count;

    if (test > 0) { cout << "\nstage one: deal with pairs\n"; }
    for (int i = 0; i < 6; i++) {// deal with pairs
        for (int j = i + 1; j < 6; j++) {
            if (table[i][j] > 0 && table[j][i] > 0) {
                min_count = min(table[i][j], table[j][i]);
                result += min_count;

                table[i][j] -= min_count;
                table[j][i] -= min_count;

                if (table[i][j] == 0) { table[i][6]--; }
                if (table[j][i] == 0) { table[j][6]--; }

                edge_counter -= min_count * 2;

                if (test > 0) {
                    cout << "i = " << i << ", j = " << j << "\n";
                    cout << "result += " << min_count << "\n";
                    cout << "result = " << result << "\n";
                    cout << "\nafter this step:\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\t" << table[i][6] << "\n";
                    }
                    cout << "\n";
                }
            }
        }
    }

    int first_idx, second_idx, third_idx = 0, temp;

    if (test > 0) { cout << "\nstage two: deal with outer triangles:\n"; }
    while (edge_counter > 0 && third_idx >= 0) {// deal with outer triangles
        third_idx = -1;

        for (int i = 0; i < 6; i++) {
            if (table[i][6] == 1) {
                first_idx = i, second_idx = 0, third_idx = -1;

                /*  there's only one non-empty number in this row because table[i][6] == 1.

                    normally "second_idx < 6 && " should be added in below while loop
                    but if the table is CONSISTENT, then we won't need to*/
                while (table[first_idx][second_idx] == 0) { second_idx++; }
                if (test > 0) { cout << "second_idx = " << second_idx << "\n"; }

                for (int m = 0; m < 6; m++) {
                    if (table[second_idx][m] > 0 && table[m][first_idx] > 0) {
                        third_idx = m;
                        break;
                    }
                }
                if (test > 0) { cout << "third_idx = " << third_idx << "\n"; }

                if (third_idx >= 0) {
                    min_count = table[first_idx][second_idx];
                    if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                    if (min_count > table[third_idx][first_idx]) { min_count = table[third_idx][first_idx]; }

                    if (test > 0) { cout << "min_count = " << min_count << "\n"; }

                    table[first_idx][second_idx] -= min_count;
                    table[second_idx][third_idx] -= min_count;
                    table[third_idx][first_idx] -= min_count;

                    if (table[first_idx][second_idx] == 0) { table[first_idx][6]--; }
                    if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                    if (table[third_idx][first_idx] == 0) { table[third_idx][6]--; }

                    edge_counter -= min_count * 3;

                    result += min_count * 2;

                    if (test > 0) {
                        cout << "result += " << min_count * 2 << "\n";
                        cout << "result = " << result << "\n";
                        cout << "\nafter this step\n";
                        for (int i = 0; i < 6; i++) {
                            for (int j = 0; j < 6; j++) {
                                cout << table[i][j] << " ";
                            }
                            cout << "\t" << table[i][6] << "\n";
                        }
                        cout << "\n";
                    }
                }
            }
        }
    }

    if (test > 0) { cout << "stage three: try to extract most triangles:\n"; }
    vector<vector<int>> path_with_max_triangle;
    vector<vector<int>> history;// coordinate 1, coordinate 2, value, 1st/2nd/3rd point
    history.push_back({-1, -1, 0, 0});
    bool found, proceed_not_going_back = 1;// 1 proceed forward, 0 proceed at the last triangle & replace it
    while (edge_counter > 0 && history.size() > 0) {
        found = 0;
        /*  find triangle

                with no prev info
                     --- proceed_not_going_back = 1

                with prev info, only try points after curr_points
                     --- proceed_not_going_back = 0
        */

        if (proceed_not_going_back == 1) {// no prev info
            for (int i = 0; i < 6 && found == 0; i++) {// first idx
                if (table[i][6] > 0) {

                    for (int j = 0; j < 6 && found == 0; j++) {// second idx
                        if (j != i && table[i][j] > 0) {

                            for (int k = 0; k < 6; k++) {// third idx
                                if (k != i && k != j && table[j][k] > 0 && table[k][i] > 0) {//  if found, proceed, push_back values into vector
                                    min_count = table[i][j];
                                    if (min_count > table[j][k]) { min_count = table[j][k]; }
                                    if (min_count > table[k][i]) { min_count = table[k][i]; }

                                    if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                                    history.push_back({i, j, k, min_count});

                                    table[i][j] -= min_count;
                                    table[j][k] -= min_count;
                                    table[k][i] -= min_count;

                                    if (table[i][j] == 0) { table[i][6]--; }
                                    if (table[j][k] == 0) { table[j][6]--; }
                                    if (table[k][i] == 0) { table[k][6]--; }

                                    found = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if (found == 0) {
                if (history.size() - 1 > path_with_max_triangle.size()) {

                    temp = path_with_max_triangle.size();
                    for (int i = 1; i < history.size(); i++) {
                        if (i - 1 < temp) {
                            path_with_max_triangle[i - 1][0] = history[i][0];
                            path_with_max_triangle[i - 1][1] = history[i][1];
                            path_with_max_triangle[i - 1][2] = history[i][2];
                            path_with_max_triangle[i - 1][3] = history[i][3];
                        }
                        else {
                            path_with_max_triangle.push_back({history[i][0], history[i][1], history[i][2], history[i][3]});
                        }
                    }
                }
                proceed_not_going_back = 0;
            }
        }

        else {//with prev info, try to find
            first_idx = history[history.size() - 1][0];
            if (first_idx >= 0) {
                second_idx = history[history.size() - 1][1];
                third_idx = history[history.size() - 1][2];
                min_count = history[history.size() - 1][3];

                if (table[first_idx][second_idx] == 0) { table[first_idx][6]++; }
                if (table[second_idx][third_idx] == 0) { table[second_idx][6]++; }
                if (table[third_idx][first_idx] == 0) { table[third_idx][6]++; }

                table[first_idx][second_idx] += min_count;
                table[second_idx][third_idx] += min_count;
                table[third_idx][first_idx] += min_count;

                if (test > 0) {
                    cout << "\nafter rolling back\n";
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < 6; j++) {
                            cout << table[i][j] << " ";
                        }
                        cout << "\t" << table[i][6] << "\n";
                    }
                    cout << "\n";
                }

                for (int i = second_idx + 1; i < 6 && found == 0; i++) {
                    if (i != first_idx && table[first_idx][i] > 0) {
                        second_idx = i;

                        for (int k = 0; k < 6; k++) {
                            if (k != first_idx && k != second_idx && table[second_idx][k] > 0 && table[k][first_idx] > 0) {//  if found, proceed, push_back values into vector
                                third_idx = k;

                                min_count = table[first_idx][second_idx];
                                if (min_count > table[second_idx][third_idx]) { min_count = table[second_idx][third_idx]; }
                                if (min_count > table[third_idx][first_idx]) { min_count = table[third_idx][first_idx]; }

                                if (test > 0) { cout << "min_count = " << min_count << "\n"; }

                                history[history.size() - 1][0] = first_idx;
                                history[history.size() - 1][1] = second_idx;
                                history[history.size() - 1][2] = third_idx;
                                history[history.size() - 1][3] = min_count;

                                table[first_idx][second_idx] -= min_count;
                                table[second_idx][third_idx] -= min_count;
                                table[third_idx][first_idx] -= min_count;

                                if (table[first_idx][second_idx] == 0) { table[first_idx][6]--; }
                                if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
                                if (table[third_idx][first_idx] == 0) { table[third_idx][6]--; }

                                found = 1;
                                break;
                            }
                        }

                    }
                }
            }

            if (found == 0) {
                if (history.size() - 1 > path_with_max_triangle.size()) {
                    temp = path_with_max_triangle.size();
                    for (int i = 1; i < history.size(); i++) {
                        if (i - 1 < temp) {
                            path_with_max_triangle[i - 1][0] = history[i][0];
                            path_with_max_triangle[i - 1][1] = history[i][1];
                            path_with_max_triangle[i - 1][2] = history[i][2];
                            path_with_max_triangle[i - 1][3] = history[i][3];
                        }
                        else {
                            path_with_max_triangle.push_back({history[i][0], history[i][1], history[i][2], history[i][3]});
                        }
                    }
                }
                history.pop_back();
            }

            else { proceed_not_going_back = 1; }
        }

        if (test > 0) {
            cout << "found = " << found << "\n";
            cout << "\nafter this step\n";
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    cout << table[i][j] << " ";
                }
                cout << "\t" << table[i][6] << "\n";
            }
            cout << "\n";
            cout << "history:\n";
            for (int i = 0; i < history.size(); i++) {
                cout << history[i][0] << " ";
                cout << history[i][1] << " ";
                cout << history[i][2] << " ";
                cout << history[i][3] << ";\n";
            }
            cout << "\npath_with_max_triangle:\n";
            for (int i = 0; i < path_with_max_triangle.size(); i++) {
                cout << path_with_max_triangle[i][0] << " ";
                cout << path_with_max_triangle[i][1] << " ";
                cout << path_with_max_triangle[i][2] << " ";
                cout << path_with_max_triangle[i][3] << ";\n";
            }
            cout << "\none round complete\n\n\n\n";

            test++;
            if (test > 10) break;
        }
    }

    if (history.size() > 1) {
        for (int i = 1; i < history.size(); i++) {
            first_idx = history[i][0];
            second_idx = history[i][1];
            third_idx = history[i][2];
            min_count = history[i][3];

            if (table[first_idx][second_idx] == 0) { table[first_idx][6]++; }
            if (table[second_idx][third_idx] == 0) { table[second_idx][6]++; }
            if (table[third_idx][first_idx] == 0) { table[third_idx][6]++; }

            table[first_idx][second_idx] += min_count;
            table[second_idx][third_idx] += min_count;
            table[third_idx][first_idx] += min_count;
        }
    }

    if (test > 0) {
        cout << "right before the end of 3rd stage:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\t" << table[i][6] << "\n";
        }
        cout << "\n";
    }

    for (int i = 0; i < path_with_max_triangle.size(); i++) {
        first_idx = path_with_max_triangle[i][0];
        second_idx = path_with_max_triangle[i][1];
        third_idx = path_with_max_triangle[i][2];
        min_count = path_with_max_triangle[i][3];

        table[first_idx][second_idx] -= min_count;
        table[second_idx][third_idx] -= min_count;
        table[third_idx][first_idx] -= min_count;

        if (table[first_idx][second_idx] == 0) { table[first_idx][6]--; }
        if (table[second_idx][third_idx] == 0) { table[second_idx][6]--; }
        if (table[third_idx][first_idx] == 0) { table[third_idx][6]--; }

        result += min_count * 2;
        if (test > 0) { cout << "result += " << min_count * 2 << "\n"; }
        edge_counter -= min_count * 3;
    }

    if (test > 0) {
        cout << "\nresult = " << result << "\n\n";

        cout << "after 3rd stage:\n";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cout << table[i][j] << " ";
            }
            cout << "\t" << table[i][6] << "\n";
        }
        cout << "\n\n";
    }

    int path[6];
    if (test > 0) { cout << "stage four: probe long lines:\n"; }
    while (edge_counter > 0) {
        for (int i = 0, path_count, curr, temp; i < 6; i++) {
            if (table[i][6] > 0) {

                for (int j = i + 1; j < 6; j++) {
                    if (table[i][j] > 0) {
                        if (test > 0) { cout << "i = " << i << ", j = " << j << "\n"; }

                        for (int k = 0; k < 6; k++) { path[k] = -1; }

                        path[i] = j;
                        min_count = table[i][j];
                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                        curr = j;

                        while (path[curr] < 0) {
                            for (int k = 0; k < 6; k++) {
                                if (table[curr][k] != 0) {
                                    if (min_count > table[curr][k]) {
                                        min_count = table[curr][k];
                                        if (test > 0) { cout << "min_count = " << min_count << "\n"; }
                                    }

                                    path[curr] = k;
                                    curr = k;

                                    break;
                                }
                            }
                        }

                        for (int k = curr; ; ) {
                            table[k][path[k]] -= min_count;
                            k = path[k];
                            if (k == curr) { break; }
                        }

                        if (test > 0) {
                            for (int k = 0; k < 6; k++) { cout << path[k] << " "; }
                            cout << "\ncurr = " << curr << "\n";
                            cout << "\n";
                        }

                        path_count = 0;

                        while (path[curr] >= 0) {
                            path_count++;
                            temp = curr;
                            curr = path[curr];
                            path[temp] = -1;
                        }

                        result += min_count * (path_count - 1);
                        edge_counter -= min_count * path_count;

                        if (test > 0) {
                            cout << "path_count = " << path_count << "\n";
                            cout << "min_count = " << min_count << "\n";
                            cout << "result += " << min_count * (path_count - 1) << "\n";
                            cout << "result = " << result << "\n";
                            cout << "\nafter this step\n";
                            for (int i = 0; i < 6; i++) {
                                for (int j = 0; j < 6; j++) {
                                    cout << table[i][j] << " ";
                                }
                                cout << "\t" << table[i][6] << "\n";
                            }
                            cout << "\n\n";
                        }
                    }
                }
            }
        }
    }

    return result;
}





/* 0 5 2 4 1 3
// 0 5 2 4 1 3
// 0 5 2 4 1 3
// 0 5 2 4 1 3
// 0 5 2 4 1 3
// 0 5 2 4 1 3

012345
345120

0 1 0 0 0 1
0 0 1 1 0 0
1 0 0 0 1 0
1 0 0 0 0 0
0 1 0 0 0 0
0 0 1 0 0 0



0 1 0 0 0 0
0 0 1 1 0 0
0 0 0 0 1 0
1 0 0 0 0 0
0 1 0 0 0 0
0 0 0 0 0 0

222



aabcde
cdaeba

abcd
dabc

abcde
eabcd

*/

/*std::ios::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);*/

//  I WILL MOST LIKELY TO RUN INTO ALL KINDS OF PROBLEMS IF I DO NOT BUILD A BRUTEFORCE & TEST A BIT
//  NO MATTER HOW CONFIDENT I MIGHT HAVE ON THAT ALGORITHM
int main(){
    srand(time(0));int length = 30, display = 0, input = 0;
    string wtf0 = "aefabcdebcdf";
    string wtf1 = "bcadfbeaefcd";
/*"abcdeabcdeabcdeabcde"
"aaaabbbbccccddddeeee"

"aabbccddee"
"cdacbeebad"

"ccfafcdaddefeebbaccb"
"dcacafeeecbafddbccfb"

"bccaba"
"abacbc"

"cdebcdeadedaaaebfbcf"
"baaddacfedebefdabecc"

"abcdefabcdefabcdef"
"edcfbebceafcfdabad"

"abcdefabcdefabcdef"
"bcbecadfbeaafefcdd"

*/

    auto sp1 = chrono::steady_clock::now(); auto ep1 = chrono::steady_clock::now(); auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now(); auto ep2 = chrono::steady_clock::now(); auto dif2 = ep2 - sp2;
string wtf00; string wtf10;
string wtf01; string wtf11;
int counter0[6]; int counter1[6];int how_many_of_this_char, temp;
for (int m = 1; m <= 1; m++) {if (m % 10000 == 0) {cout << "m = " << m << "\n";}
    if (input == 1) {// rand() % (upper_range - lower_range + 1) + lower_range
        for (int i = 0; i < 6; i++) { counter0[i] = 0; }
        for (int i = 0; i < 6; i++) { counter1[i] = 0; }
        how_many_of_this_char = length;
        //cout << "~0\n";
        for (int i = 0; (i < 6) && (how_many_of_this_char > 0); i++) {
            temp = rand() % (how_many_of_this_char - 0 + 1) + 0;
            counter0[i] = temp;
            counter1[i] = temp;
            how_many_of_this_char -= temp;
        }

        //for (int i = 0; i < 6; i++) { cout << counter0[i] << " "; } cout << "\n";
        //for (int i = 0; i < 6; i++) { cout << counter1[i] << " "; } cout << "\n";

        if (how_many_of_this_char > 0) {
            counter0[5] += how_many_of_this_char;
            counter1[5] += how_many_of_this_char;
        }

        //cout << "~1\n";
        //for (int i = 0; i < 6; i++) { cout << counter0[i] << " "; } cout << "\n";
        //for (int i = 0; i < 6; i++) { cout << counter1[i] << " "; } cout << "\n";

        for (int i = 0; i < length; i++) {
            temp = rand() % 6;
            while (counter0[temp] == 0) { temp = rand() % 6; }
            wtf0.push_back(temp + 97);
            counter0[temp]--;
        }
        //cout << "~2\n";
        for (int i = 0; i < length; i++) {
            temp = rand() % 6;
            while (counter1[temp] == 0) { temp = rand() % 6; }
            wtf1.push_back(temp + 97);
            counter1[temp]--;
        }
        //cout << "input prepared\n";
    }
    if (display == 1) { cout << "\n" << wtf0 << "\n" << wtf1 << "\n"; }

    wtf00 = wtf0; wtf10 = wtf1;
    wtf01 = wtf0; wtf11 = wtf1;

    sp1 = chrono::steady_clock::now();
    int s = kSimilarity_1_0(wtf00, wtf10);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;
    if (display == 1) { cout << "s = " << s << "\n"; }

    sp2 = chrono::steady_clock::now();
    int ss = kSimilarity_1_1(wtf01, wtf11);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;
    if (display == 1) { cout << "ss = " << ss << "\n"; }

    if (s != ss) {
        cout << "\nm = " << m << "\n";
        cout << wtf0 << "\n" << wtf1 << "\n\n";
        cout << "s = " << s << "\n";
        cout << "ss = " << ss << "\n";
        break;
    }

wtf0.clear();
wtf1.clear();
}
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
