/*1761. Minimum Degree of a Connected Trio in a Graph
Hard

You are given an undirected graph.
You are given an integer n which is the number of nodes in the graph and an array edges,
where each edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi.

A connected trio is a set of three nodes where there is an edge between every pair of them.

The degree of a connected trio is the number of edges
where one endpoint is in the trio, and the other is not.

Return the minimum degree of a connected trio in the graph,
or -1 if the graph has no connected trios.

Input: n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
Output: 3
Explanation:
There is exactly one trio, which is [1,2,3].
The edges that form its degree are bolded in the figure above.

Input: n = 7, edges = [[1,3],[4,1],[4,3],[2,5],[5,6],[6,7],[7,5],[2,6]]
Output: 0
Explanation:
There are exactly three trios:
1) [1,4,3] with degree 0.
2) [2,5,6] with degree 2.
3) [5,6,7] with degree 2.

Constraints:
    2 <= n <= 400
    edges[i].length == 2
    1 <= edges.length <= n * (n-1) / 2
    1 <= ui, vi <= n
    ui != vi
    There are no repeated edges.
*/

/*
class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {

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

using namespace std;
using namespace chrono;
// I UNDERSTAND IT WRONG
/*  Hope this works.
    ONLY 3 types of nodes:
        1. in graph & in trio
        2. in graph & NOT in trio
        3. NOT in graph


*/
int minTrioDegree_does_not_work (int n, vector<vector<int>>& edges) {
    // trivial cases

    int length = edges.size(), result = 0, isolated_points = 0;int test = 1;

    // better to use unordered_set when n is large, otherwise a plain array will be just fine
    bool remaining_points[n + 1]; for (int i = 1; i <= n; i++) { remaining_points[i] = 0; }

    unordered_map<int, unordered_set<int>> info;

    for (int i = 0; i < length; i++) {
        remaining_points[edges[i][0]] = 1, remaining_points[edges[i][1]] = 1;

        auto find_value = info.find(edges[i][0]);
        if (find_value == info.end()) { info.insert({edges[i][0], unordered_set<int> ()}); }
        info[edges[i][0]].insert(edges[i][1]);

        find_value = info.find(edges[i][1]);
        if (find_value == info.end()) { info.insert({edges[i][1], unordered_set<int> ()}); }
        info[edges[i][1]].insert(edges[i][0]);
    }

    for (int i = 1; i <= n; i++) { if (remaining_points[i] == 0) { isolated_points++; } }

    if (test > 0){
        for (auto i = info.begin(); i != info.end(); ++i) {
            cout << i->first << ": ";
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                cout << *j << " ";
            }
            cout << "\n";
        }

        cout << "\n";
    }

    // better to use unordered_set when n is large, otherwise a plain array will be just fine
    bool in_trio[n + 1]; for (int i = 1; i <= n; i++) { in_trio[i] = 0; }
    int mark_visited_1[n + 1];
    int mark_visited_2[n + 1];
    int mark_visited_3[n + 1];
    //int mark_visited_4[n + 1];

    if (test > 0) {
        cout << "\nremaining_points:\n";
        for (int p = 1; p <= n; p++) {
            cout << remaining_points[p] << " ";
        }

        cout << "\n\n";
    }

    // 1 -> 2 -> 3 -> 4 -> 1 cycling
    for (int i = 1, now_to, start_value, a_handy_temp, found_next; i <= n; ) {// note to update remaining_points and info
        for (int j = i; j <= n; j++) {
            if (remaining_points[j] == 1) {
                start_value = j;
                i = j;
                break;
            }
        }

        if (test > 0) { cout << "\nstart_value = " << start_value << "\n"; }

        now_to = 1, found_next = 0;
        for (int z = 1; z <= n; z++) { mark_visited_1[z] = -1; }
        for (int z = 1; z <= n; z++) { mark_visited_2[z] = -1; }
        for (int z = 1; z <= n; z++) { mark_visited_3[z] = -1; }
        //for (int z = 1; z <= n; z++) { mark_visited_4[z] = -1; }

        remaining_points[start_value] = 0;
        mark_visited_2[start_value] = 0;// starting from mark_visited_4 MERELY FOR CONVENIENCE

        for (auto l = info[start_value].begin(), m = l; l != info[start_value].end(); ) {
            a_handy_temp = *l;
            ++l;

            //remaining_points[a_handy_temp] = 0;
            mark_visited_3[a_handy_temp] = start_value;

            //info[a_handy_temp].erase(info[a_handy_temp].find(start_value));
            //if (info[a_handy_temp].size() == 0) { info.erase(info.find(a_handy_temp)); }

            info[start_value].erase(info[start_value].find(a_handy_temp));
        }

        // if (info[start_value].size() == 0) { info.erase(info.find(start_value)); }

        if (test > 0){
            for (auto p = info.begin(); p != info.end(); ++p) {
                cout << p->first << ": ";
                for (auto j = p->second.begin(); j != p->second.end(); ++j) {
                    cout << *j << " ";
                }
                cout << "\n";
            }
            cout << "\nmark_visited_1: ";
            for (int p = 1; p <= n; p++) { cout << mark_visited_1[p] << " "; }
            cout << "\nmark_visited_2: ";
            for (int p = 1; p <= n; p++) { cout << mark_visited_2[p] << " "; }
            cout << "\nmark_visited_3: ";
            for (int p = 1; p <= n; p++) { cout << mark_visited_3[p] << " "; }
            cout << "\n";

            cout << "\nremaining_points:\n";
            for (int p = 1; p <= n; p++) { cout << remaining_points[p] << " "; }
            cout << "\n";
        }

        while (now_to > 0) {// note that, mark_visited will save info of previous node
            found_next = 0;

            if (test > 0) { cout << "\nnow_to = " << now_to << "\n"; }

            if (now_to == 1) {  // 4 to 1
                for (int z = 1; z <= n; z++) { mark_visited_1[z] = 0; }

                for (int k = 1; k <= n; k++) {
                    if (mark_visited_3[k] >= 0) {
                        remaining_points[k] = 0;

                        for (auto l = info[k].begin(), m = l; l != info[k].end(); ) {
                            found_next = 1;

                            a_handy_temp = *l;
                            ++l;

                            //remaining_points[a_handy_temp] = 0;
                            mark_visited_1[a_handy_temp] = k;

                            //info[a_handy_temp].erase(info[a_handy_temp].find(k));
                            //if (info[a_handy_temp].size() == 0) { info.erase(info.find(a_handy_temp)); }

                            info[k].erase(info[k].find(a_handy_temp));

                            if (mark_visited_2[a_handy_temp] >= 0) {
                                in_trio[k] = 1;
                                in_trio[a_handy_temp] = 1;
                                in_trio[mark_visited_2[k]] = 1;
                                if (test > 0) { cout << "\nin_trio[" << k << "], in_trio[" << a_handy_temp << "], in_trio[" << mark_visited_2[k] << "]\n"; }
                            }
                        }

                        //if (info[k].size() == 0) { info.erase(info.find(k)); }
                    }
                }

                if (found_next == 0) { now_to = -1; }

                else { now_to = 2; }
            }

            else if (now_to == 2) { // 1 to 2
                for (int z = 1; z <= n; z++) { mark_visited_2[z] = 0; }

                for (int k = 1; k <= n; k++) {
                    if (mark_visited_1[k] >= 0) {
                        remaining_points[k] = 0;

                        for (auto l = info[k].begin(), m = l; l != info[k].end(); ) {
                            found_next = 1;

                            a_handy_temp = *l;
                            ++l;

                            //remaining_points[a_handy_temp] = 0;
                            mark_visited_2[a_handy_temp] = k;

                            //info[a_handy_temp].erase(info[a_handy_temp].find(k));
                            //if (info[a_handy_temp].size() == 0) { info.erase(info.find(a_handy_temp)); }

                            info[k].erase(info[k].find(a_handy_temp));


                            if (mark_visited_3[a_handy_temp] >= 0) {
                                in_trio[k] = 1;
                                in_trio[a_handy_temp] = 1;
                                in_trio[mark_visited_3[k]] = 1;
                                if (test > 0) { cout << "in_trio[" << k << "], in_trio[" << a_handy_temp << "], in_trio[" << mark_visited_3[k] << "]\n"; }
                            }
                        }

                        //if (info[k].size() == 0) { info.erase(info.find(k)); }
                    }
                }

                if (found_next == 0) { now_to = -1; }

                else { now_to = 3; }
            }

            /*else if (now_to == 3) { // 2 to 3
                for (int z = 1; z <= n; z++) { mark_visited_3[z] = 0; }

                for (int k = 1; k <= n; k++) {
                    if (mark_visited_2[k] >= 0) {

                        for (auto l = info[k].begin(), m = l; l != info[k].end(); ) {
                            found_next = 1;

                            a_handy_temp = *l;
                            ++l;

                            remaining_points[a_handy_temp] = 0;
                            mark_visited_3[a_handy_temp] = k;

                            info[a_handy_temp].erase(info[a_handy_temp].find(k));
                            if (info[a_handy_temp].size() == 0) { info.erase(info.find(a_handy_temp)); }

                            info[k].erase(info[k].find(a_handy_temp));

                            if (mark_visited_4[a_handy_temp] >= 0) {
                                in_trio[k] = 1;
                                in_trio[a_handy_temp] = 1;
                                in_trio[mark_visited_2[k]] = 1;
                            }
                        }

                        if (info[k].size() == 0) { info.erase(info.find(k)); }
                    }
                }

                if (found_next == 0) { now_to = -1; }

                else { now_to = 4; }
            }
*/
            else {  // 3 to 4
                for (int z = 1; z <= n; z++) { mark_visited_3[z] = 0; }

                for (int k = 1; k <= n; k++) {
                    if (mark_visited_2[k] >= 0) {
                        remaining_points[k] = 0;

                        for (auto l = info[k].begin(), m = l; l != info[k].end(); ) {
                            found_next = 1;

                            a_handy_temp = *l;
                            ++l;

                            //remaining_points[a_handy_temp] = 0;
                            mark_visited_3[a_handy_temp] = k;

                            //info[a_handy_temp].erase(info[a_handy_temp].find(k));
                            //if (info[a_handy_temp].size() == 0) { info.erase(info.find(a_handy_temp)); }

                            info[k].erase(info[k].find(a_handy_temp));


                            if (mark_visited_1[a_handy_temp] >= 0) {
                                in_trio[k] = 1;
                                in_trio[a_handy_temp] = 1;
                                in_trio[mark_visited_1[k]] = 1;
                                if (test > 0) { cout << "in_trio[" << k << "], in_trio[" << a_handy_temp << "], in_trio[" << mark_visited_1[k] << "]\n"; }
                            }
                        }

                        //if (info[k].size() == 0) { info.erase(info.find(k)); }
                    }
                }

                if (found_next == 0) { now_to = -1; }

                else { now_to = 1; }
            }

            if (test > 0){
                cout << "\nafter processing\n";
                cout << "found_next = " << found_next;
                cout << "\nremaining_points: ";
                for (int p = 1; p <= n; p++) { cout << remaining_points[p] << " "; }

                cout << "\n\ninfo:\n";
                for (auto p = info.begin(); p != info.end(); ++p) {
                    cout << p->first << ": ";
                    for (auto j = p->second.begin(); j != p->second.end(); ++j) {
                        cout << *j << " ";
                    }
                    cout << "\n";
                }
                cout << "\nmark_visited_1: ";
                for (int p = 1; p <= n; p++) { cout << mark_visited_1[p] << " "; }
                cout << "\nmark_visited_2: ";
                for (int p = 1; p <= n; p++) { cout << mark_visited_2[p] << " "; }
                cout << "\nmark_visited_3: ";
                for (int p = 1; p <= n; p++) { cout << mark_visited_3[p] << " "; }
                //cout << "\nmark_visited_4:\n";for (int p = 1; p <= n; p++) { cout << mark_visited_4[p] << " "; }
                cout << "\n\nthis round complete.\n\n";

                test++;
            }

            if (test > 10) { break; }
        }

        if (test > 10) { break; }
    }

    int trio_counter = 0;
    for (int i = 1; i <= n; i++) { if (in_trio[i] == 1) { trio_counter++; } }

    result = length - trio_counter - isolated_points;

    if (test > 0) {
        cout << "\n\ntrio_counter = " << trio_counter << "\n";
        cout << "isolated_points = " << isolated_points << "\n";
    }

    return result;
}

// I UNDERSTAND IT WRONG
int minTrioDegree_WRONG_brute(int n, vector<vector<int>>& edges) {
    // trivial cases

    int length = edges.size(); if (length <= 2) { return -1; }
    //int test = 1;

    bool info[n + 1][n + 1]; for (int i = 0; i <= n; i++) { for (int j = 0; j <= n; j++) { info[i][j] = 0; } }

    for (int i = 0; i < length; i++) {
        info[edges[i][0]][0] = 1;
        info[edges[i][1]][0] = 1;
        info[edges[i][0]][edges[i][1]] = 1;
        info[edges[i][1]][edges[i][0]] = 1;
    }

    bool in_trio[n + 1]; for (int i = 1; i <= n; i++) { in_trio[i] = 0; }

    for (int i = 1; i < n - 1; i++) {
        if (info[i][0] == 1) {// means line i is NOT empty

            for (int j = i + 1; j < n; j++) {

                // means line j is NOT empty & there is an edge between i & j
                if ((info[j][0] == 1) && (info[i][j] == 1)) {

                    for (int k = j + 1; k <= n; k++) {

                        // means line k is NOT empty, there is a j~k edge & an i~k edge
                        if ((info[k][0] == 1) && (info[j][k] == 1) && (info[i][k] == 1)) {
                            in_trio[i] = 1, in_trio[j] = 1, in_trio[k] = 1;
                        }
                    }
                }
            }
        }
    }

    int result = 0;
    bool record[n + 1]; for (int i = 1; i <= n; i++) { record[i] = 0; }

    bool trio_is_empty = 1;
    for (int i = 1; i <= n; i++) {
        if (in_trio[i] == 1) {
            trio_is_empty = 0;
            for (int j = 1; j <= n; j++) {
                if ((info[i][j] == 1) && (in_trio[j] == 0) && (record[j] == 0) && (i != j)) {
                    result++;
                    record[j] = 1;
                }
            }
        }
    }

    return (trio_is_empty == 0)? result: -1;
}

// I UNDERSTAND IT WRONG
int minTrioDegree_WRONG(int n, vector<vector<int>>& edges) {
    // trivial cases

    int length = edges.size(); if (length <= 2) { return -1; }

    int result = 0, isolated_points = 0;

    int test = 1;

    // better to use unordered_set when n is large, otherwise a plain array will be just fine
    bool remaining_points[n + 1]; for (int i = 1; i <= n; i++) { remaining_points[i] = 0; }

    unordered_map<int, unordered_set<int>> info;
    bool info_bool[n + 1][n + 1]; for (int i = 1; i <= n; i++) { for (int j = 1; j <= n; j++) { info_bool[i][j] = 0; } }

    for (int i = 0; i < length; i++) {
        remaining_points[edges[i][0]] = 1, remaining_points[edges[i][1]] = 1;

        auto find_value = info.find(edges[i][0]);
        if (find_value == info.end()) { info.insert({edges[i][0], unordered_set<int> ()}); }
        info[edges[i][0]].insert(edges[i][1]);

        find_value = info.find(edges[i][1]);
        if (find_value == info.end()) { info.insert({edges[i][1], unordered_set<int> ()}); }
        info[edges[i][1]].insert(edges[i][0]);

        info_bool[edges[i][0]][edges[i][1]] = 1;
        info_bool[edges[i][1]][edges[i][0]] = 1;
    }

    for (int i = 1; i <= n; i++) { if (remaining_points[i] == 0) { isolated_points++; } }

    if (test > 0){
        cout << "\nisolated_points = " << isolated_points << "\n\n";
        for (auto i = info.begin(); i != info.end(); ++i) {
            cout << i->first << ": ";
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                cout << *j << " ";
            }
            cout << "\n";
        }

        cout << "\n";
    }

    // better to use unordered_set when n is large, otherwise a plain array will be just fine
    bool in_trio[n + 1]; for (int i = 1; i <= n; i++) { in_trio[i] = 0; }
    int mark_visited_1[n + 1];
    int mark_visited_2[n + 1];
    //int mark_visited_3[n + 1];

    if (test > 0) {
        cout << "\nremaining_points:\n";
        for (int p = 1; p <= n; p++) {
            cout << remaining_points[p] << " ";
        }

        cout << "\n\n";
    }

    // 1 -> 2 -> 3 -> 1 cycling
    for (int i = 1, now_to, a_handy_temp, found_next; i <= n; ) {// note to update remaining_points and info
        for (int j = i; j <= n; j++) { if (remaining_points[j] == 1) { i = j; break; } }

        if (remaining_points[i] == 0) { break; }

        for (int z = 1; z <= n; z++) { mark_visited_1[z] = -1; }
        for (int z = 1; z <= n; z++) { mark_visited_2[z] = -1; }
        //for (int z = 1; z <= n; z++) { mark_visited_3[z] = -1; }

        remaining_points[i] = 0, found_next = 0;//mark_visited_2[i] = 0,

        for (auto l = info[i].begin(); l != info[i].end(); ) {
            found_next = 1;
            a_handy_temp = *l;
            ++l;
            //mark_visited_3[a_handy_temp] = i;
            mark_visited_2[a_handy_temp] = i;

            info[i].erase(info[i].find(a_handy_temp));
            info[a_handy_temp].erase(info[a_handy_temp].find(i));
            if (info[a_handy_temp].size() == 0) { info.erase(info.find(a_handy_temp)); }
        }

        if (info[i].size() == 0) { info.erase(info.find(i)); }

        now_to = 1;

        if (test > 0){
            cout << "\nanother start point\n";
            cout << "\ninfo:\n";
            for (auto p = info.begin(); p != info.end(); ++p) {
                cout << p->first << ": ";
                for (auto j = p->second.begin(); j != p->second.end(); ++j) {
                    cout << *j << " ";
                }
                cout << "\n";
            }
            cout << "\nmark_visited_1: ";
            for (int p = 1; p <= n; p++) { cout << mark_visited_1[p] << " "; }
            cout << "\nmark_visited_2: ";
            for (int p = 1; p <= n; p++) { cout << mark_visited_2[p] << " "; }
            cout << "\n\n";
        }

        while (found_next == 1) {
            found_next = 0;

            if (now_to == 1) {
                if (test > 0){ cout << "now_to == 1\n"; }

                for (int z = 1; z <= n; z++) { mark_visited_1[z] = -1; }

                for (int j = 1; j <= n; j++) {
                    if (mark_visited_2[j] >= 0) {
                        remaining_points[j] = 0;

                        for (auto k = info[j].begin(), l = k; k != info[j].end(); ) {
                            found_next = 1;

                            a_handy_temp = *k;
                            ++k;

                            mark_visited_1[a_handy_temp] = j;

                            if (test > 0) {cout << "j = " << j << "\n"; cout << "a_handy_temp = " << a_handy_temp << "\n";}

                            // j < a_handy_temp because otherwise it will do the same operation 2 times
                            if (j < a_handy_temp) {
                                if ((mark_visited_2[a_handy_temp] >= 0) && (mark_visited_2[j] == mark_visited_2[a_handy_temp])) {
                                    if (test > 0) { cout << "ding --- 1!\n"; cout << a_handy_temp << " " << j << " " << mark_visited_2[j] << "\n";}

                                    in_trio[a_handy_temp] = 1, in_trio[j] = 1, in_trio[mark_visited_2[j]] = 1;
                                }

                                else if ((mark_visited_1[a_handy_temp] >= 0) && (mark_visited_1[j] >= 0)
                                    && (mark_visited_2[mark_visited_1[a_handy_temp]] == mark_visited_2[mark_visited_1[j]])) {

                                    if (test > 0) {cout << "ding --- 2!\n"; }

                                    cout << a_handy_temp << " " << mark_visited_1[a_handy_temp] << " " << mark_visited_1[j] << "\n";
                                    in_trio[a_handy_temp] = 1, in_trio[mark_visited_1[a_handy_temp]] = 1, in_trio[mark_visited_1[j]] = 1;
                                }
                            }

                            info[j].erase(info[j].find(a_handy_temp));
                            info[a_handy_temp].erase(info[a_handy_temp].find(j));
                            if (info[a_handy_temp].size() == 0) { info.erase(info.find(a_handy_temp)); }
                        }

                        if (info[j].size() == 0) { info.erase(info.find(j)); }
                    }
                }

                now_to = 2;
            }

            else {
                if (test > 0) { cout << "now_to == 2\n"; }

                for (int z = 1; z <= n; z++) { mark_visited_2[z] = -1; }

                for (int j = 1; j <= n; j++) {
                    if (mark_visited_1[j] >= 0) {
                        remaining_points[j] = 0;

                        cout << "~\n";

                        for (auto k = info[j].begin(), l = k; k != info[j].end(); ) {
                            found_next = 1;

                            cout << "~~now_to == 2\n";

                            a_handy_temp = *k;
                            ++k;

                            if (test > 0) { cout << "j = " << j << "\n"; cout << "a_handy_temp = " << a_handy_temp << "\n"; }

                            mark_visited_2[a_handy_temp] = j;

                            // j < a_handy_temp because otherwise it will do the same operation 2 times
                            if (j < a_handy_temp) {
                                if ((mark_visited_1[a_handy_temp] >= 0) && (mark_visited_1[j] == mark_visited_1[a_handy_temp])) {
                                    if (test > 0) { cout << "ding --- 1!\n";

                                    cout << a_handy_temp << " " << j << " " << mark_visited_1[j] << "\n"; }
                                    in_trio[a_handy_temp] = 1, in_trio[j] = 1, in_trio[mark_visited_1[j]] = 1;
                                }

                                else if ((mark_visited_2[a_handy_temp] >= 0) && (mark_visited_2[j] >= 0)
                                    && (mark_visited_1[mark_visited_2[a_handy_temp]] == mark_visited_1[mark_visited_2[j]])) {

                                    if (test > 0) { cout << "ding --- 2!\n";
                                    cout << a_handy_temp << " " << mark_visited_2[a_handy_temp] << " " << mark_visited_2[j] << "\n"; }
                                    in_trio[a_handy_temp] = 1, in_trio[mark_visited_2[a_handy_temp]] = 1, in_trio[mark_visited_2[j]] = 1;
                                }
                            }

                            info[j].erase(info[j].find(a_handy_temp));
                            info[a_handy_temp].erase(info[a_handy_temp].find(j));
                            if (info[a_handy_temp].size() == 0) { info.erase(info.find(a_handy_temp)); }
                        }

                        if (info[j].size() == 0) { info.erase(info.find(j)); }
                    }
                }

                now_to = 1;
            }

            if (test > 0) {
                cout << "\n\nafter processing\n";
                cout << "found_next = " << found_next;
                cout << "\nremaining_points: ";
                for (int p = 1; p <= n; p++) { cout << remaining_points[p] << " "; }

                cout << "\n\ninfo:\n";
                for (auto p = info.begin(); p != info.end(); ++p) {
                    cout << p->first << ": ";
                    for (auto j = p->second.begin(); j != p->second.end(); ++j) {
                        cout << *j << " ";
                    }
                    cout << "\n";
                }
                cout << "\nmark_visited_1: ";
                for (int p = 1; p <= n; p++) { cout << mark_visited_1[p] << " "; }
                cout << "\nmark_visited_2: ";
                for (int p = 1; p <= n; p++) { cout << mark_visited_2[p] << " "; }
                cout << "\n\nin_trio: ";
                for (int p = 1; p <= n; p++) { cout << in_trio[p] << " "; }
                cout << "\n\nthis round complete.\n\n\n\n";

                test++;
            }
            //if (test > 5) { break; }
        }
    }


    for (int i = 0; i < length; i++) {
        remaining_points[edges[i][0]] = 1, remaining_points[edges[i][1]] = 1;

        auto find_value = info.find(edges[i][0]);
        if (find_value == info.end()) { info.insert({edges[i][0], unordered_set<int> ()}); }
        info[edges[i][0]].insert(edges[i][1]);

        find_value = info.find(edges[i][1]);
        if (find_value == info.end()) { info.insert({edges[i][1], unordered_set<int> ()}); }
        info[edges[i][1]].insert(edges[i][0]);
    }

    /*int temp;
    //  WRONG there might be a tree part
    //  how about NOT clear info bit by bit,
    unordered_set<int> collect_result;
    for (int i = 1; i <= n; i++) {
        if (in_trio[i] == 1) {
            for (auto j = info[i].begin(); j != info[i].end(); ++j) {
                temp = *j;
                if (in_trio[temp] == 0) {
                    auto k = collect_result.find(temp);
                    if (k == collect_result.end()) {
                        collect_result.insert(temp);
                    }
                }
            }
        }
    }
*/



    bool record[n + 1]; for (int i = 1; i <= n; i++) { record[i] = 0; }

    for (int i = 1; i <= n; i++) {
        if (in_trio[i] == 1) {
            for (int j = 1; j <= n; j++) {
                if ((info_bool[i][j] == 1) && (in_trio[j] == 0) && (record[j] == 0) && (i != j)) {
                    result++;
                    record[j] = 1;
                }
            }
        }
    }

    return result;
}





int minTrioDegree_other_people(int n, vector<vector<int>>& edges) {
    vector<vector<int>> neighbours(n + 1);
    vector<vector<bool>> isConnected(n + 1, vector<bool>(n + 1, false));
    for(const auto& edge : edges){
        neighbours[edge[0]].push_back(edge[1]);
        neighbours[edge[1]].push_back(edge[0]);
        isConnected[edge[0]][edge[1]] = true;
        isConnected[edge[1]][edge[0]] = true;
    }
    auto comp = [&](int i, int j){return neighbours[i].size() < neighbours[j].size();};
    int ans = INT_MAX;
    for(int x = 1; x <= n; x++){
        sort(neighbours[x].begin(), neighbours[x].end(), comp);
        int t = neighbours[x].size();
        if(t < 2 || t + (int)neighbours[neighbours[x][0]].size() + (int)neighbours[neighbours[x][1]].size() - 6 >= ans){
            continue;
        }
        for(int j = 0; j < t - 1; j++){
            int y = neighbours[x][j];
            if(t + (int)neighbours[y].size() + (int)neighbours[neighbours[x][j+1]].size() - 6 >= ans){
                break;
            }
            for(int k = j + 1; k < t; k++){
                int z = neighbours[x][k];
                if(isConnected[y][z]){
                    ans = min(ans, t + (int)neighbours[y].size() + (int)neighbours[z].size() - 6);
                }
            }
        }
    }
    return ans == INT_MAX ? -1 : ans;
}

int minTrioDegree_other_people_2(int n, vector<vector<int>>& edges) {
    vector<vector<bool>> con(n + 1, vector<bool>(n + 1, false));
    vector<vector<int>> gra(n + 1);
    int ans = INT_MAX;
    for (auto &ed : edges) {
        con[ed[0]][ed[1]] = con[ed[1]][ed[0]] = true;
        gra[ed[0]].push_back(ed[1]);
        gra[ed[1]].push_back(ed[0]);
    }
    vector<int> vs;
    for (int v = 1; v <= n; ++v)
        if (gra[v].size() >= 2)
            vs.push_back(v);
    auto cmp = [&](int a, int b) {
        return gra[a].size() < gra[b].size();
    };
    sort(vs.begin(), vs.end(), cmp);
    for (int x : vs) {
        auto &yz = gra[x];
        int dx = yz.size();
        if (dx < 2) continue;
        if (dx >= ans - 4) break;
        sort(yz.begin(), yz.end(), cmp);
        for (int i = 0; i < dx - 1; ++i) {
            int dy = gra[yz[i]].size();
            if (dx + dy + gra[yz[i+1]].size() >= ans) break;
            for (int j = i + 1; j < dx; ++j) {
                int deg = dx + dy + gra[yz[j]].size();
                if (deg >= ans) break;
                if (con[yz[i]][yz[j]]) {
                    ans = deg;
                }
            }
        }
    }
    return ans == INT_MAX ? -1 : ans - 6;
}




const int N = 405, W = 64, inf = ~0u>>1;
bitset<N> c[N];
int counter[N], _d[N], id[N], rid[N];
inline bool cmp (int x, int y) { return counter[x] < counter[y]; }

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        int ans = inf;
        for (int i = 0 ; i < n; ++i) {
            counter[i] = 0, id[i] = i;
            c[i].reset();
        }

        for (auto &e: edges) {
            int x = --e[0], y = --e[1];// to put it back 1 bit?

            ++counter[x]; ++counter[y];
        }

        sort(id, id + n, cmp);// to get the index of the largest counter?

        for (int i = 0; i < n; ++i) {
            rid[id[i]] = i, _d[i] = counter[i];// there's some relation between rid and counter
        }

        for (int i = 0; i < n; ++i) {
            counter[i] = _d[id[i]];
        }

        for (auto &e: edges) {
            int x = rid[e[0]], y = rid[e[1]];
            if (x > y) { swap(x,y); }
            c[x].set(y,1);
        }

        for (int i = 0; i < n - 2; ++i) {
            if (counter[i] * 3 >= ans) break;

            for (int j = i + 1; j < n - 1; ++j) {

                if (c[i][j]) {
                    if (counter[i] + counter[j] * 2 >= ans) break;

                    int k = (c[i]&c[j])._Find_first();

                    if (k < n) ans = min(ans, counter[i] + counter[j] + counter[k]);
                }
            }
        }

        return (ans < inf)? ans - 6: -1;
    }
};






// passed but with lots of room for improvement
int minTrioDegree_1(int n, vector<vector<int>>& edges) {
    // trivial cases

    int length = edges.size(); if (length <= 2) { return -1; }
    //int test = 1;

    int counter[n + 1]; for (int i = 0; i <= n; i++) { counter[i] = 0; }
    bool info[n + 1][n + 1]; for (int i = 0; i <= n; i++) { for (int j = 0; j <= n; j++) { info[i][j] = 0; } }

    for (int i = 0; i < length; i++) {
        counter[edges[i][0]]++, counter[edges[i][1]]++;

        info[edges[i][0]][0] = 1, info[edges[i][1]][0] = 1;

        info[edges[i][0]][edges[i][1]] = 1;
        info[edges[i][1]][edges[i][0]] = 1;
    }

    bool no_trio = 1;
    int result = n * 3, temp;

    for (int i = 1; i < n - 1; i++) {
        if (info[i][0] == 1) {// means line i is NOT empty

            for (int j = i + 1; j < n; j++) {

                // means line j is NOT empty & there is an edge between i & j
                if ((info[j][0] == 1) && (info[i][j] == 1)) {

                    for (int k = j + 1; k <= n; k++) {

                        // means line k is NOT empty, there is a j~k edge & an i~k edge
                        if ((info[k][0] == 1) && (info[j][k] == 1) && (info[i][k] == 1)) {
                            no_trio = 0;
                            temp = counter[i] + counter[j] + counter[k] - 6;

                            if (temp < result) { result = temp; }
                        }
                    }
                }
            }
        }
    }

    return (no_trio == 0)? result: -1;
}





// decent performance yet still there are room for improvement
int minTrioDegree_1_1_1(int n, vector<vector<int>>& edges) {
    if (edges.size() <= 2) { return -1; }

    int counter[n + 1]; for (int i = 0; i <= n; i++) { counter[i] = 0; }
    bool info[n + 1][n + 1]; for (int i = 0; i <= n; i++) { for (int j = 0; j <= n; j++) { info[i][j] = 0; } }

    for (int i = 0; i < edges.size(); i++) {
        counter[edges[i][0]]++, counter[edges[i][1]]++;

        if (edges[i][0] < edges[i][1]) {
            info[edges[i][0]][edges[i][1]] = 1;
        }

        else {
            info[edges[i][1]][edges[i][0]] = 1;
        }
    }

    int result = n * 3, max_val = result - 9, temp;

    for (int i = 1; i < n - 1; i++) {
        if (counter[i] > 1) {// means line i is NOT empty
            temp = counter[i] - 6;

            for (int j = i + 1; j < n; j++) {

                // means line j is NOT empty & there is an edge between i & j
                if ((info[i][j] == 1) && (counter[j] > 1)) {
                    temp += counter[j];

                    for (int k = j + 1; k <= n; k++) {

                        // means line k is NOT empty, there is a j~k edge & an i~k edge
                        if ((info[j][k] == 1) && (info[i][k] == 1) && (counter[k] > 1)) {
                            temp += counter[k];

                            if (temp < result) {
                                result = temp;

                                if (result == 0) { break; }
                            }

                            temp -= counter[k];
                        }
                    }

                    if (result == 0) { break; }

                    temp -= counter[j];
                }
            }

            if (result == 0) { break; }
        }
    }

    return (result <= max_val)? result: -1;
}

int minTrioDegree_1_1_1_bitset(int n, vector<vector<int>>& edges) {
    if (edges.size() <= 2) { return -1; }
    if (n > 400) { cout << "Invalid Range\n"; return -1; }

    int counter[n + 1]; for (int i = 0; i <= n; i++) { counter[i] = 0; }
    vector<bitset<401>> info(n + 1, bitset<401> (0));

    for (int i = 0; i < edges.size(); i++) {
        counter[edges[i][0]]++, counter[edges[i][1]]++;

        if (edges[i][0] < edges[i][1]) {
            info[edges[i][0]][edges[i][1]] = 1;
        }

        else {
            info[edges[i][1]][edges[i][0]] = 1;
        }
    }

    int result = n * 3, max_val = result - 9, temp;

    for (int i = 1; i < n - 1; i++) {
        if (counter[i] > 1) {// means line i is NOT empty
            temp = counter[i] - 6;

            for (int j = i + 1; j < n; j++) {

                // means line j is NOT empty & there is an edge between i & j
                if ((info[i][j] == 1) && (counter[j] > 1)) {
                    temp += counter[j];

                    for (int k = j + 1; k <= n; k++) {

                        // means line k is NOT empty, there is a j~k edge & an i~k edge
                        if ((info[j][k] == 1) && (info[i][k] == 1) && (counter[k] > 1)) {
                            temp += counter[k];

                            if (temp < result) {
                                result = temp;

                                if (result == 0) { break; }
                            }

                            temp -= counter[k];
                        }
                    }

                    if (result == 0) { break; }

                    temp -= counter[j];
                }
            }

            if (result == 0) { break; }
        }
    }

    return (result <= max_val)? result: -1;
}

int minTrioDegree_1_1_1_bitset_new_delete(int n, vector<vector<int>>& edges) {
    if (edges.size() <= 2) { return -1; }
    if (n > 400) { cout << "Invalid Range\n"; return -1; }
    //const int bitset_size = n;

    int counter[n + 1]; for (int i = 0; i <= n; i++) { counter[i] = 0; }
    bitset<401> info[n + 1];

    //bitset<11>& bitset_ref = info[0];

    for (int i = 0; i < edges.size(); i++) {
        counter[edges[i][0]]++, counter[edges[i][1]]++;

        if (edges[i][0] < edges[i][1]) {
            //bitset_ref = info[edges[i][0]];
            info[edges[i][0]][edges[i][1]] = 1;
        }

        else {
            //bitset_ref = info[edges[i][1]];
            info[edges[i][1]][edges[i][0]] = 1;
        }
    }

    /*cout << "bitset:\n";
    for (int i = 1; i <= n; i++) {
        //bitset_ref = info[i];
        cout << info[i] << "\n";
    }
*/

    int result = n * 3, max_val = result - 9, temp;

    for (int i = 1; i < n - 1; i++) {
        if (counter[i] > 1) {// means line i is NOT empty
            temp = counter[i] - 6;

            for (int j = i + 1; j < n; j++) {
                if (counter[j] > 1){

                    //bitset_ref = info[i];
                    if (info[i][j] == 1) {
                        temp += counter[j];

                        for (int k = j + 1; k <= n; k++) {
                            if (counter[k] > 1) {

                                //bitset_ref = info[j];
                                if (info[j][k] == 1) {

                                    //bitset_ref = info[i];
                                    if (info[i][k] == 1) {
                                        temp += counter[k];

                                        if (temp < result) {
                                            result = temp;

                                            if (result == 0) { break; }
                                        }

                                        temp -= counter[k];
                                    }
                                }
                            }
                        }

                        if (result == 0) { break; }

                        temp -= counter[j];
                    }
                }
            }

            if (result == 0) { break; }
        }
    }

    //delete[] info;

    return (result <= max_val)? result: -1;
}



int minTrioDegree_1_1_1_1(int n, vector<vector<int>>& edges) {
    if (edges.size() <= 2) { return -1; }

    int info[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {// j might as well start with i
        info[i][0] = 0;
        for (int j = i; j <= n; j++) { info[i][j] = 0; }
    }

    int counter[n + 1]; for (int i = 0; i <= n; i++) { counter[i] = 0; }
    for (int i = 0; i < edges.size(); i++) {
        counter[edges[i][0]]++, counter[edges[i][1]]++;

        if (edges[i][0] < edges[i][1]) {
            info[edges[i][0]][edges[i][1]] = 1;
        }

        else {
            info[edges[i][1]][edges[i][0]] = 1;
        }
    }

    for (int i = 1, last_idx; i <= n; i++) {
        if (counter[i] > 0) {
            last_idx = 0;
            for (int j = i + 1; j <= n; j++) {
                if (info[i][j] > 0) {
                    info[i][last_idx] = j;
                    last_idx = j;
                }

                if (j == n) { info[i][last_idx] = -1; }
            }
        }

        else { info[i][0] = -1; }
    }

    int result = n * 3, max_val = result - 9, temp;

    /*for (int i = 0; i <= n; i++) {
        cout << i << ": ";
        for (int j = 0; j <= n; j++) {
            cout << info[i][j] << " ";
        }
        cout << "\n";
    }*/

    for (int i = 1; i < n - 1; i++) {
        if ((counter[i] > 1) && (info[i][0] > 0)) {// means line i is NOT empty
            temp = counter[i] - 6;

            for (int j = info[i][0]; j < n; ) {

                if ((counter[j] > 1) && (info[j][0] > 0)) {
                    temp += counter[j];

                    for (int k = info[j][0]; k <= n; ) {

                        if ((counter[k] > 1) && (info[i][k] != 0)) {
                            temp += counter[k];

                            if (temp < result) {
                                result = temp;

                                if (result == 0) { break; }
                            }

                            temp -= counter[k];
                        }

                        if (info[j][k] == -1) { break; } else { k = info[j][k]; }
                    }

                    if (result == 0) { break; }
                    temp -= counter[j];
                }

                if (info[i][j] == -1) { break; } else { j = info[i][j]; }
            }

            if (result == 0) { break; }
        }
    }

    return (result <= max_val)? result: -1;
}







//  merely a customized stable merge sort which sort array a[] along with its index
void merge_sort (int a[], int index[], int length) {
    int b[length]; for (int i = 0; i < length; i++) { b[i] = a[i]; }
    int c[length]; for (int i = 0; i < length; i++) { c[i] = index[i]; }

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        b[k] = a[i];
                        c[k] = index[i];
                        i++;
                    }
                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) {
                            break;
                        }

                        else {
                            b[k] = a[i];
                            c[k] = index[i];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k] = a[j];
                        c[k] = index[j];
                        j++, j_step++;
                    }

                    else if (a[i] <= a[j]) {
                        b[k] = a[i];
                        c[k] = index[i];
                        i++, i_step++;
                    }

                    else if (a[i] > a[j]) {
                        b[k] = a[j];
                        c[k] = index[j];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 0;
        }

        else if (from_a_to_b == 0) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        a[k] = b[i];
                        index[k] = c[i];
                        i++;
                    }
                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) {
                            break;
                        }

                        else {
                            a[k] = b[i];
                            index[k] = c[i];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k] = b[j];
                        index[k] = c[j];
                        j++, j_step++;
                    }

                    else if (b[i] <= b[j]) {
                        a[k] = b[i];
                        index[k] = c[i];
                        i++, i_step++;
                    }

                    else if (b[i] > b[j]) {
                        a[k] = b[j];
                        index[k] = c[j];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 1;
        }
    }

    if (from_a_to_b == 0) {
        for (int i = 0; i < length; i++) { a[i] = b[i]; index[i] = c[i]; }
    }
}

//  learned from an algo - FUCK I MISSED IT - what MATTERS is RELATIVE RELATION
//  SORT according to COUNTER, and ONLY search in promising points
//  if my algo can do better?
//  YES! MY CODE DO BETTER!
//  My code got NO LENGTH RESTRAINTS - 400!
int minTrioDegree_1_1_1_1_with_sorted_counter(int n, vector<vector<int>>& edges) {
    if (edges.size() <= 2) { return -1; } //int test = 0;

    int counter[n + 1]; counter[0] = -1; for (int i = 1; i <= n; i++) { counter[i] = 0; }
    for (int i = 0; i < edges.size(); i++) { counter[edges[i][0]]++, counter[edges[i][1]]++; }

    int index[n + 1]; for (int i = 0; i <= n; i++) { index[i] = i; }
    merge_sort(counter, index, n + 1);
    /*if (test > 0) {
        cout << "\ncounter:\n"; for (int i = 0; i <= n; i++) { cout << counter[i] << " "; }
        cout << "\nindex:\n"; for (int i = 0; i <= n; i++) { cout << index[i] << " "; }
    }*/

    int mapping[n + 1]; mapping[0] = -1;
    for (int i = 1; i <= n; i++) { mapping[index[i]] = i; }
    /*if (test > 0) {
        cout << "\nmapping:\n";
        for (int i = 0; i <= n; i++) { cout << mapping[i] << " "; }
        cout << "\n";
    }*/

    int info[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        // we ONLY NEED to search indexes that are LARGER than current index, ignore the other half
        for (int j = i + 1; j <= n; j++) {// note that j started with i + 1
            info[i][j] = 0;
        }
    }

    for (int i = 0; i < edges.size(); i++) {
        if (mapping[edges[i][0]] < mapping[edges[i][1]]) {
            info[mapping[edges[i][0]]][mapping[edges[i][1]]] = 1;
        }

        else {
            info[mapping[edges[i][1]]][mapping[edges[i][0]]] = 1;
        }
    }
    /*cout << "\ninfo:\n";
    for (int i = 0; i <= n; i++) {
        cout << i << ": ";
        for (int j = 0; j <= n; j++) {
            cout << info[i][j] << " ";
        }
        cout << "\n";
    }*/

    for (int i = 1, last_idx; i <= n; i++) {//  record next index to avoid scanning empty info, end with -1
        if (counter[i] > 1) {
            last_idx = 0;

            for (int j = i + 1; j <= n; j++) {
                if (info[i][j] > 0) {
                    info[i][last_idx] = j;
                    last_idx = j;
                }

                if (j == n) { info[i][last_idx] = -1; }
            }
        }
    }
    /*if (test > 0) {
        cout << "\ninfo:\n";
        for (int i = 0; i <= n; i++) {
            cout << i << ": ";
            for (int j = 0; j <= n; j++) {
                cout << info[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }*/

    int result = n * 3, max_val = result - 3, start_idx = 0, temp;
    int second_must_be_no_larger_than, third_must_be_no_larger_than;

    for (int i = 1; i < n - 1; i++) { if (counter[i] > 1) { start_idx = i; break; } }
    //  cout << "start_idx = " << start_idx << "\n";

    if (start_idx > 0) {
        for (int i = start_idx; i < n - 1; i++) {
            //if (test > 0) { cout << "i = " << i << "\n"; }
            if (counter[i] * 3 >= result) { break; }

            if (info[i][0] > 0) {
                temp = counter[i];
                second_must_be_no_larger_than = (result - counter[i]) / 2;

                for (int j = info[i][0]; (j > 0) && (j < n) && (counter[j] <= second_must_be_no_larger_than); j = info[i][j]) {
                    //if (test > 0) { cout << "j = " << j << "\n"; }
                    if (info[j][0] > 0) {
                        temp += counter[j];
                        third_must_be_no_larger_than = result - counter[i] - counter[j];

                        for (int k = info[j][0]; (k > 0) && (k <= n) && (counter[k] < third_must_be_no_larger_than); k = info[j][k]) {
                            //if (test > 0) { cout << "k = " << k << "\n"; }
                            if (info[i][k] != 0) {
                                temp += counter[k];

                                if (temp < result) {
                                    result = temp;
                                    //if (test > 0) { cout << "i = " << i << ", j = " << j << ", k = " << k << "\n"; }
                                }

                                temp -= counter[k];
                            }
                        }

                        temp -= counter[j];
                    }
                }
            }
        }
    }

    return (result <= max_val)? result - 6: -1;
}





// same as 1.1.1 except it is calculate result in one go every time a trio is found
int minTrioDegree_1_1_2(int n, vector<vector<int>>& edges) {
    if (edges.size() <= 2) { return -1; }

    int counter[n + 1]; for (int i = 0; i <= n; i++) { counter[i] = 0; }
    bool info[n + 1][n + 1]; for (int i = 0; i <= n; i++) { for (int j = 0; j <= n; j++) { info[i][j] = 0; } }

    for (int i = 0; i < edges.size(); i++) {
        counter[edges[i][0]]++, counter[edges[i][1]]++;

        if (edges[i][0] < edges[i][1]) {
            info[edges[i][0]][edges[i][1]] = 1;
        }

        else {
            info[edges[i][1]][edges[i][0]] = 1;
        }
    }

    int result = n * 3, max_val = result - 9, temp;

    for (int i = 1; i < n - 1; i++) {
        if (counter[i] > 0) {// means line i is NOT empty

            for (int j = i + 1; j < n; j++) {

                // means line j is NOT empty & there is an edge between i & j
                if (info[i][j] == 1) {
                    for (int k = j + 1; k <= n; k++) {

                        // means line k is NOT empty, there is a j~k edge & an i~k edge
                        if ((info[j][k] == 1) && (info[i][k] == 1)) {
                            temp = counter[i] + counter[j] + counter[k] - 6;

                            if (temp < result) { result = temp; }
                        }
                    }
                }
            }
        }
    }

    return (result <= max_val)? result: -1;
}




// use vector to ... performance is not promising so far
int minTrioDegree_1_2_1(int n, vector<vector<int>>& edges) {
    if (edges.size() <= 2) { return -1; }

    int counter[n + 1]; for (int i = 0; i <= n; i++) { counter[i] = 0; }
    vector<vector<int>> info(n + 1, vector<int> ());

    for (int i = 0; i < edges.size(); i++) {
        counter[edges[i][0]]++, counter[edges[i][1]]++;

        if (edges[i][0] < edges[i][1]) {
            info[edges[i][0]].push_back(edges[i][1]);
        }

        else {
            info[edges[i][1]].push_back(edges[i][0]);
        }
    }

    /*for (int i = 1; i <= n; i++) {
        if (counter[i] > 1) {
            sort(info[i].begin(), info[i].end());
        }
    }*/

    /*for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int j = 0; j < info[i].size(); j++) {
            cout << info[i][j] << " ";
        }
        cout << "\n";
    }*/

    int result = n * 3, max_val = result - 9, temp;
    bool existed[n + 1];

    for (int i = 1; i < n - 1; i++) {
        if (counter[i] > 0) {// means line i is NOT empty
            for (int z = i + 1; z <= n; z++) { existed[z] = 0; }
            for (int z = 0; z < info[i].size(); z++) { existed[info[i][z]] = 1; }

            //cout << "i = " << i << "\n"; for (int z = 1; z <= n; z++) { cout << existed[z] << " "; } cout << "\n";

            temp = counter[i] - 6;

            for (int j = 0; j < info[i].size(); j++) {
                temp += counter[info[i][j]];

                for (int k = 0; k < info[info[i][j]].size(); k++) {
                    if (existed[info[info[i][j]][k]] == 1) {
                        temp += counter[info[info[i][j]][k]];

                        if (temp < result) { result = temp; }

                        temp -= counter[info[info[i][j]][k]];
                    }
                }

                temp -= counter[info[i][j]];
            }
        }
    }

    return (result <= max_val)? result: -1;
}

// too slow
int minTrioDegree_1_2_1_1(int n, vector<vector<int>>& edges) {
    if (edges.size() <= 2) { return -1; }

    int counter[n + 1]; for (int i = 0; i <= n; i++) { counter[i] = 0; }
    vector<unordered_set<int>> info(n + 1, unordered_set<int> ());
    //bool info[n + 1][n + 1]; for (int i = 0; i <= n; i++) { for (int j = 0; j <= n; j++) { info[i][j] = 0; } }

    for (int i = 0; i < edges.size(); i++) {
        counter[edges[i][0]]++, counter[edges[i][1]]++;

        if (edges[i][0] < edges[i][1]) {
            info[edges[i][0]].insert(edges[i][1]);
        }

        else {
            info[edges[i][1]].insert(edges[i][0]);
        }
    }

    int result = n * 3, max_val = result - 9, temp;

    for (int i = 1; i < n - 1; i++) {
        if (counter[i] > 0) {// means line i is NOT empty
            temp = counter[i] - 6;

            for (auto j = info[i].begin(); j != info[i].end(); ++j) {
                temp += counter[*j];

                for (auto k = info[*j].begin(); k != info[*j].end(); ++k) {
                    auto l = info[i].find(*k);
                    if (l != info[i].end()) {
                        temp += counter[*k];

                        if (temp < result) { result = temp; }

                        temp -= counter[*k];
                    }
                }

                temp -= counter[*j];
            }
        }
    }

    return (result <= max_val)? result: -1;
}


// same as 1.2.1 except for using "unordered" something. performance not good
int minTrioDegree_1_2_2(int n, vector<vector<int>>& edges) {
    if (edges.size() <= 2) { return -1; }

    int counter[n + 1]; for (int i = 0; i <= n; i++) { counter[i] = 0; }
    vector<vector<int>> info(n + 1, vector<int> ());

    for (int i = 0; i < edges.size(); i++) {
        counter[edges[i][0]]++, counter[edges[i][1]]++;

        if (edges[i][0] < edges[i][1]) {
            info[edges[i][0]].push_back(edges[i][1]);
        }

        else {
            info[edges[i][1]].push_back(edges[i][0]);
        }
    }

    /*for (int i = 1; i <= n; i++) {
        if (counter[i] > 1) {
            sort(info[i].begin(), info[i].end());
        }
    }*/

    /*for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int j = 0; j < info[i].size(); j++) {
            cout << info[i][j] << " ";
        }
        cout << "\n";
    }*/

    int result = n * 3, max_val = result - 9;
    bool existed[n + 1];

    for (int i = 1, sum, idx1, idx2; (i < n - 1) && (result != 0); i++) {
        if (counter[i] > 1) {// means line i is NOT empty
            for (int z = i + 1; z <= n; z++) { existed[z] = 0; }
            for (int z = 0; z < info[i].size(); z++) { existed[info[i][z]] = 1; }

            //cout << "i = " << i << "\n"; for (int z = 1; z <= n; z++) { cout << existed[z] << " "; } cout << "\n";

            sum = counter[i] - 6;

            for (int j = 0; (j < info[i].size()) && (result != 0); j++) {
                idx1 = info[i][j];
                if (counter[idx1] > 1) {
                    sum += counter[idx1];

                    for (int k = 0; k < info[idx1].size(); k++) {
                        idx2 = info[idx1][k];
                        if ((existed[idx2] == 1)&&(counter[idx2] > 1)) {

                            sum += counter[idx2];

                            if (sum < result) {
                                result = sum;

                                if (result == 0) { break; }
                            }

                            sum -= counter[idx2];
                        }
                    }

                    sum -= counter[idx1];
                }
            }
        }
    }

    return (result <= max_val)? result: -1;
}





int main(){
    srand(time(0));int n = 500, length = 80000, display = 0, input = 1;
    vector<vector<int>> wtf;
    // = {{6,5},{4,3},{5,1},{1,4},{2,3},{4,5},{2,6},{1,3}};

    // = {{5,2},{4,1},{2,4},{1,5}};
    // = {{3,2},{2,1}};
    // = {{1,2},{2,3},{2,4},{5,1}};
    // = {{1,2},{2,3},{3,4},{4,1},{1,3},{4,2},{2,5}};5
    // = {{1,2},{2,3},{3,4},{4,2},{5,3},{4,6},{7,4},{4,9},{4,8},{8,9}};9
    // = {{1,3},{4,1},{4,3},{2,5},{5,6},{6,7},{7,5},{2,6}};n = 7
    // = {{1,2},{1,3},{3,2},{4,1},{5,2},{3,6}};n = 6

    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;
    auto start_point_4 = chrono::steady_clock::now();auto end_point_4 = chrono::steady_clock::now();auto diff_4 = end_point_4 - start_point_4;
    auto start_point_5 = chrono::steady_clock::now();auto end_point_5 = chrono::steady_clock::now();auto diff_5 = end_point_5 - start_point_5;
    auto start_point_6 = chrono::steady_clock::now();auto end_point_6 = chrono::steady_clock::now();auto diff_6 = end_point_6 - start_point_6;
    auto start_point_7 = chrono::steady_clock::now();auto end_point_7 = chrono::steady_clock::now();auto diff_7 = end_point_7 - start_point_7;

    bool record_matrix[n + 1][n + 1]; for (int i = 1; i <= n; i++) { for (int j = 1; j <= n; j++) { record_matrix[i][j] = 0; } }
    int temp1, temp2;

for (int m = 1; m <= 100; m++) {if (m % 10 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){//  rand()%(upper_range - lower_range + 1) + lower_range
        wtf.reserve(length);

        for(int i = 0; i < length; i++) {
            while (true) {
                temp1 = rand()%(n - 1 + 1) + 1;
                temp2 = rand()%(n - 1 + 1) + 1;
                while (temp1 == temp2) { temp2 = rand()%(n - 1 + 1) + 1; }
                if (record_matrix[temp1][temp2] == 0) { break; }
            }

            wtf.push_back({temp1, temp2});
            record_matrix[temp1][temp2] = 1;
            record_matrix[temp2][temp1] = 1;
        }
    }
    if (display == 1){
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{";
            for (int j = 0; j < wtf[i].size(); j++) {
                cout << wtf[i][j];if (j < wtf[i].size() - 1) {cout << ",";}
            }
            cout << "},";
        }
        cout << "}\n";
    }

    vector<vector<int>> wtf1(wtf);vector<vector<int>> wtf2(wtf);vector<vector<int>> wtf3(wtf);vector<vector<int>> wtf4(wtf);
    vector<vector<int>> wtf5(wtf);vector<vector<int>> wtf6(wtf);vector<vector<int>> wtf7(wtf);vector<vector<int>> wtf8(wtf);

    start_point_1 = chrono::steady_clock::now();
    int a = 0;//minTrioDegree_other_people(n, wtf1);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;
    //cout << "s = " << s << "\n";

    start_point_4 = chrono::steady_clock::now();
    int b = 0;//minTrioDegree_other_people_2(n, wtf2);
    end_point_4 = chrono::steady_clock::now();
    diff_4 += end_point_4 - start_point_4;

    start_point_2 = chrono::steady_clock::now();
    int c = minTrioDegree_1_1_1(n, wtf3);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;
    //cout << "ss = " << ss << "\n";

    start_point_3 = chrono::steady_clock::now();
    int d = minTrioDegree_1_1_1_1_with_sorted_counter(n, wtf4);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;

    start_point_5 = chrono::steady_clock::now();
    int e = minTrioDegree_1_1_1_1(n, wtf5);
    end_point_5 = chrono::steady_clock::now();
    diff_5 += end_point_5 - start_point_5;
    //cout << "ss = " << ss << "\n";

    start_point_6 = chrono::steady_clock::now();
    int f = 0;//minTrioDegree_1_1_1_bitset_new_delete(n, wtf6);
    end_point_6 = chrono::steady_clock::now();
    diff_6 += end_point_6 - start_point_6;

    Solution gg;
    start_point_7 = chrono::steady_clock::now();
    int g = 0;//gg.minTrioDegree(n, wtf7);
    end_point_7 = chrono::steady_clock::now();
    diff_7 += end_point_7 - start_point_7;

    /*if ((a != f)||(b != d)||(c != f)||(e != g)) {
        cout << "\nm = " << m << "\n\n";
        cout << "a = " << a << "\n";
        cout << "b = " << b << "\n";
        cout << "c = " << c << "\n";
        cout << "d = " << d << "\n";
        cout << "e = " << e << "\n";
        cout << "f = " << f << "\n";
        cout << "g = " << g << "\n";
        cout << "\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{";
            for (int j = 0; j < wtf[i].size(); j++) {
                cout << wtf[i][j];if (j < wtf[i].size() - 1) {cout << ",";}
            }
            cout << "},";
        }
        cout << "}\n";
        break;
    }
*/
for (int i = 1; i <= n; i++) { for (int j = 1; j <= n; j++) { record_matrix[i][j] = 0; } }

wtf.clear();}

cout << "other  : " << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << "1_1_1  : " << duration <double, milli> (diff_2).count() << " ms" << "\n";
cout << "sorted : " << duration <double, milli> (diff_3).count() << " ms" << "\n";
cout << "other_2: " << duration <double, milli> (diff_4).count() << " ms" << "\n";
cout << "1_1_1_1: " << duration <double, milli> (diff_5).count() << " ms" << "\n";
cout << "new_del: " << duration <double, milli> (diff_6).count() << " ms" << "\n";
cout << "let's c: " << duration <double, milli> (diff_7).count() << " ms" << "\n";

    return 0;
}




