/*886. Possible Bipartition
Medium

Given a set of N people (numbered 1, 2, ..., N),
we would like to split everyone into two groups of any size.

Each person may dislike some other people,
and they should not go into the same group.

Formally, if dislikes[i] = [a, b],
it means it is not allowed to put the people numbered a and b into the same group.

Return true if and only if it is possible to split everyone into two groups in this way.

Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: group1 [1,4], group2 [2,3]

Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
Output: false

Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
Output: false

Constraints:
    1 <= N <= 2000
    0 <= dislikes.length <= 10000
    dislikes[i].length == 2
    1 <= dislikes[i][j] <= N
    dislikes[i][0] < dislikes[i][1]
    There does not exist i != j for which dislikes[i] == dislikes[j].
*/

/*
class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {

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


bool possibleBipartition_brute (int N, vector<vector<int>>& dislikes) {
    bool matrix[N + 1][N + 1];
    for (int i = 0; i <= N; i++) { for (int j = 0; j <= N; j++) { matrix[i][j] = 0; } }
    // -1 means not present in dislikes, 0 means in dislikes & visited, 1 means in dislikes & NOT visited
    int visited[N + 1]; for (int i = 0; i <= N; i++) { visited[i] = -1; }
    for (int i = 0; i < dislikes.size(); i++) {
        matrix[dislikes[i][0]][dislikes[i][1]] = 1;
        matrix[dislikes[i][1]][dislikes[i][0]] = 1;
        visited[dislikes[i][0]] = 1;
        visited[dislikes[i][1]] = 1;
    }

    bool bucket1[N + 1]; for (int i = 0; i <= N; i++) { bucket1[i] = 0; }
    bool bucket2[N + 1]; for (int i = 0; i <= N; i++) { bucket2[i] = 0; }

    bool can_be_done = 1, to_bucket_2 = 1;

    visited[dislikes[0][0]] = 0;
    deque<int> curr_window;

    curr_window.push_back(dislikes[0][0]);
    bucket1[dislikes[0][0]] = 1;
    visited[dislikes[0][0]] = 0;

    int curr_step;

    while (curr_window.size() > 0 && can_be_done == 1) {
        curr_step = curr_window.size();
        if (to_bucket_2 == 1) {
            while (curr_step > 0 && can_be_done == 1) {
                for (int i = 1; i <= N; i++) {
                    if (matrix[curr_window.front()][i] == 1) {
                        if (bucket1[i] == 1) {
                            can_be_done = 0;
                            break;
                        }

                        matrix[curr_window.front()][i] = 0;
                        bucket2[i] = 1;
                        visited[i] = 0;
                        curr_window.push_back(i);
                    }
                }

                curr_window.pop_front();
                curr_step--;
            }
            to_bucket_2 = 0;
        }

        else {
            while (curr_step > 0 && can_be_done == 1) {
                for (int i = 1; i <= N; i++) {
                    if (matrix[curr_window.front()][i] == 1) {
                        if (bucket2[i] == 1) {
                            can_be_done = 0;
                            break;
                        }

                        matrix[curr_window.front()][i] = 0;
                        bucket1[i] = 1;
                        visited[i] = 0;
                        curr_window.push_back(i);
                    }
                }

                curr_window.pop_front();
                curr_step--;
            }
            to_bucket_2 = 1;
        }

        cout << "curr_window.size() = " << curr_window.size() << "\n";
        if (curr_window.size() == 0) {
            for (int i = 1; i <= N; i++) {
                if (visited[1] > 0) {
                    curr_window.push_back(i);
                    cout << "curr_window.size() = " << curr_window.size() << "\n";
                    break;
                }
            }
        }
    }

    return can_be_done;
}


bool possibleBipartition_brute_1 (int N, vector<vector<int>>& dislikes) {
    if (dislikes.size() == 0 || N == 1) { return true; }
    bool matrix[N + 1][N + 1];
    for (int i = 0; i <= N; i++) { for (int j = 0; j <= N; j++) { matrix[i][j] = 0; } }

    bool visited[N + 1]; for (int i = 0; i <= N; i++) { visited[i] = 0; }
    for (int i = 0; i < dislikes.size(); i++) {
        matrix[dislikes[i][0]][dislikes[i][1]] = 1;
        matrix[dislikes[i][1]][dislikes[i][0]] = 1;
        matrix[dislikes[i][0]][0] = 1;
        matrix[dislikes[i][1]][0] = 1;
    }

    bool bucket1[N + 1]; for (int i = 0; i <= N; i++) { bucket1[i] = 0; }
    bool bucket2[N + 1]; for (int i = 0; i <= N; i++) { bucket2[i] = 0; }

    bool can_be_done = 1, from_1_to_2 = 1;

    visited[dislikes[0][0]] = 0;
    deque<int> curr_window;

    curr_window.push_back(dislikes[0][0]);
    bucket1[dislikes[0][0]] = 1;
    visited[dislikes[0][0]] = 1;

    int curr_step;

    while (curr_window.size() > 0 && can_be_done == 1) {
        curr_step = curr_window.size();
        if (from_1_to_2 == 1) {
            while (curr_step > 0 && can_be_done == 1) {
                for (int i = 1; i <= N; i++) {
                    if (matrix[curr_window.front()][i] == 1) {
                        if (bucket1[i] == 1) {
                            can_be_done = 0;
                            break;
                        }

                        matrix[curr_window.front()][i] = 0;
                        bucket2[i] = 1;
                        visited[i] = 1;
                        curr_window.push_back(i);
                    }
                }

                curr_window.pop_front();
                curr_step--;
            }

            from_1_to_2 = 0;
        }

        else {
            while (curr_step > 0 && can_be_done == 1) {
                for (int i = 1; i <= N; i++) {
                    if (matrix[curr_window.front()][i] == 1) {
                        if (bucket2[i] == 1) {
                            can_be_done = 0;
                            break;
                        }

                        matrix[curr_window.front()][i] = 0;
                        bucket1[i] = 1;
                        visited[i] = 1;
                        curr_window.push_back(i);
                    }
                }

                curr_window.pop_front();
                curr_step--;
            }

            from_1_to_2 = 1;
        }

        if (curr_window.size() == 0) {
            for (int i = 1; i <= N; i++) {
                if (visited[i] == 0) {
                    curr_window.push_back(i);
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    return can_be_done;
}


// almost brute, too slow
bool possibleBipartition_1_0 (int N, vector<vector<int>>& dislikes) {
    if (N == 1 || dislikes.size() == 0) { return true; }
    int length = dislikes.size();
    int test = 0;

    //vector<vector<int>> cache(N + 1, vector<int> ());
    bool cache[N + 1][N + 1]; for (int i = 0; i <= N; i++) {for (int j = 0; j <= N; j++) { cache[i][j] = 0; } }
    for (int i = 0; i < dislikes.size(); i++) {
        cache[dislikes[i][0]][dislikes[i][1]] = 1;
        cache[dislikes[i][1]][dislikes[i][0]] = 1;
        cache[dislikes[i][0]][0] = 1;
        cache[dislikes[i][1]][0] = 1;
    }

    if (test > 0) {
        for (int i = 1; i <= N; i++) {
            cout << i << ": ";
            for (int j = 0; j <= N; j++) {
                cout << cache[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool b1[N + 1]; for (int i = 0; i <= N; i++) { b1[i] = 0; }
    bool b2[N + 1]; for (int i = 0; i <= N; i++) { b2[i] = 0; }

    deque<int> curr_window;

    curr_window.push_back(dislikes[0][0]);
    b1[dislikes[0][0]] = 1;

    int this_step, counter = length, from_1_to_2 = 1;
    bool can_be_partitioned = 1;

    while (curr_window.size() > 0 && can_be_partitioned == 1 && counter > 0) {
        this_step = curr_window.size();
        if (from_1_to_2 == 1) {
            while (this_step > 0 && can_be_partitioned == 1) {
                for (int i = 1; i <= N; i++) {
                    if (cache[curr_window.front()][i] == 1) {
                        if (b1[i] == 1) {
                            if (test > 0) { cout << curr_window.front() << " " << i << "\n"; }
                            can_be_partitioned = 0;
                            break;
                        }

                        cache[curr_window.front()][i] = 0;
                        cache[i][curr_window.front()] = 0;

                        cache[curr_window.front()][0] = 0;

                        b2[i] = 1;

                        curr_window.push_back(i);

                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_1_to_2 = 0;
        }

        else {
            while (this_step > 0 && can_be_partitioned == 1) {
                for (int i = 1; i <= N; i++) {
                    if (cache[curr_window.front()][i] == 1) {
                        if (b2[i] == 1) {
                            if (test > 0) { cout << curr_window.front() << " " << i << "\n"; }
                            can_be_partitioned = 0;
                            break;
                        }

                        cache[curr_window.front()][i] = 0;
                        cache[i][curr_window.front()] = 0;

                        cache[curr_window.front()][0] = 0;

                        b1[i] = 1;

                        curr_window.push_back(i);

                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_1_to_2 = 1;
        }

        if (test > 0) {
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b1[i] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b2[i] << " "; }
            cout << "\n\n";
            cout << "curr_window.size() = " << curr_window.size() << "\n";
        }

        if (curr_window.size() == 0 && can_be_partitioned == 1 && counter > 0) {
            for (int i = 1; i < N; i++) {
                if (cache[i][0] > 0) {
                    curr_window.push_back(i);
                    //cout << "push_back " << i << "\n";

                    if (from_1_to_2 == 1) { b1[i] = 1; }

                    else { b2[i] = 1; }

                    cache[i][0] = 0;

                    break;
                }
            }
        }
    }

    return can_be_partitioned;
}

// WORKED, slow, while memory is excellent
//, auto &sp3, auto &ep3, auto &sp4, auto &ep4
bool possibleBipartition_1_0_0_1 (int N, vector<vector<int>>& dislikes) {
    if (N == 1 || dislikes.size() == 0) { return true; }
    int length = dislikes.size();
    int test = 0;
//sp3 = chrono::steady_clock::now();
    //vector<vector<int>> cache(N + 1, vector<int> ());
    bool cache[N + 1][N + 1]; for (int i = 0; i <= N; i++) {for (int j = 0; j <= N; j++) { cache[i][j] = 0; } }
    bool visited[N + 1]; for (int i = 0; i <= N; i++) { visited[i] = 1; }

    for (int i = 0; i < dislikes.size(); i++) {
        cache[dislikes[i][0]][dislikes[i][1]] = 1;
        cache[dislikes[i][1]][dislikes[i][0]] = 1;
        visited[dislikes[i][0]] = 0;
        visited[dislikes[i][1]] = 0;
    }
//ep3 = chrono::steady_clock::now();
    if (test > 0) {
        for (int i = 1; i <= N; i++) {
            cout << i << ": ";
            for (int j = 0; j <= N; j++) {
                cout << cache[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool b1[N + 1]; for (int i = 0; i <= N; i++) { b1[i] = 0; }
    bool b2[N + 1]; for (int i = 0; i <= N; i++) { b2[i] = 0; }

    deque<int> curr_window;

    curr_window.push_back(dislikes[0][0]);
    b1[dislikes[0][0]] = 1;

    int this_step, counter = length, from_1_to_2 = 1, search_start_idx = 1;
    bool can_be_partitioned = 1;
//sp4 = chrono::steady_clock::now();
    while (curr_window.size() > 0 && can_be_partitioned == 1 && counter > 0) {
        this_step = curr_window.size();
        if (from_1_to_2 == 1) {
            while (this_step > 0 && can_be_partitioned == 1) {
                for (int i = 1; i <= N; i++) {
                    if (cache[curr_window.front()][i] == 1) {
                        if (b1[i] == 1) {
                            if (test > 0) { cout << curr_window.front() << " " << i << "\n"; }
                            can_be_partitioned = 0;
                            break;
                        }

                        cache[curr_window.front()][i] = 0;
                        cache[i][curr_window.front()] = 0;

                        visited[curr_window.front()] = 1;

                        b2[i] = 1;

                        curr_window.push_back(i);

                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_1_to_2 = 0;
        }

        else {
            while (this_step > 0 && can_be_partitioned == 1) {
                for (int i = 1; i <= N; i++) {
                    if (cache[curr_window.front()][i] == 1) {
                        if (b2[i] == 1) {
                            if (test > 0) { cout << curr_window.front() << " " << i << "\n"; }
                            can_be_partitioned = 0;
                            break;
                        }

                        cache[curr_window.front()][i] = 0;
                        cache[i][curr_window.front()] = 0;

                        visited[curr_window.front()] = 1;

                        b1[i] = 1;

                        curr_window.push_back(i);

                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_1_to_2 = 1;
        }

        if (test > 0) {
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b1[i] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b2[i] << " "; }
            cout << "\n\n";
            cout << "curr_window.size() = " << curr_window.size() << "\n";
        }

        if (curr_window.size() == 0 && can_be_partitioned == 1 && counter > 0) {
            for (int i = search_start_idx; i < N; i++) {
                if (visited[i] == 0) {
                    search_start_idx = i;

                    curr_window.push_back(i);

                    visited[i] = 1;

                    if (from_1_to_2 == 1) { b1[i] = 1; }

                    else { b2[i] = 1; }

                    break;
                }
            }
        }
    }
//ep4 = chrono::steady_clock::now();
    return can_be_partitioned;
}

bool possibleBipartition_1_0_0_1_fast_table (int N, vector<vector<int>>& dislikes) {
    if (N == 1 || dislikes.size() == 0) { return true; }
    int length = dislikes.size();
    int test = 1;

    //vector<vector<int>> cache(N + 1, vector<int> ());
    int cache[N + 1][N + 1];
    for (int i = 0; i <= N; i++) {
        cache[i][0] = 0;
        for (int j = 1; j <= N; j++) { cache[i][j] = 0; }
    }

    bool visited[N + 1]; for (int i = 0; i <= N; i++) { visited[i] = 1; }

    sort(dislikes.begin(), dislikes.end(),
         [](const auto &a, const auto &b) {
            if (a[0] > b[0]) return a[0] < b[0];

            else return a[1] < b[1];
         });

    if (test > 0) {
        cout << "dislikes after sorting:\n";
        for (int i = 0; i < dislikes.size(); i++) {
            cout << dislikes[i][0] << " " << dislikes[i][1] << ", ";
        }
        cout << "\n";
    }

    int last_idx[N + 1]; for (int i = 0; i <= N; i++) { last_idx[i] = 0; }
    for (int i = 0; i < dislikes.size(); i++) {// in this section visited is used to record the last valid value
        if (last_idx[dislikes[i][0]] == 0) {
            cache[dislikes[i][0]][0] = dislikes[i][1];
        }
        else {
            cache[dislikes[i][0]][last_idx[dislikes[i][0]]] = dislikes[i][1];
        }

        last_idx[dislikes[i][0]] = dislikes[i][1];
        cache[dislikes[i][0]][dislikes[i][1]] = -1;


        if (last_idx[dislikes[i][1]] == 0) {
            cache[dislikes[i][1]][0] = dislikes[i][0];
        }
        else {
            cache[dislikes[i][1]][last_idx[dislikes[i][1]]] = dislikes[i][0];
        }

        last_idx[dislikes[i][1]] = dislikes[i][0];
        cache[dislikes[i][1]][dislikes[i][1]] = -1;

        visited[dislikes[i][0]] = 0;
        visited[dislikes[i][1]] = 0;
    }


    if (test > 0) {
        cout << "cache:\n";
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= N; j++) {
                cout << cache[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    if (test > 0) {
        for (int i = 1; i <= N; i++) {
            cout << i << ": ";
            for (int j = 0; j <= N; j++) {
                cout << cache[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool b[N + 1][2]; for (int i = 0; i <= N; i++) { b[i][0] = 0, b[i][1] = 0; }

    deque<int> curr_window;

    curr_window.push_back(dislikes[0][0]);
    b[dislikes[0][0]][0] = 1;

    int this_step, counter = length, from_0_to_1 = 1, search_start_idx = 1;
    bool can_be_partitioned = 1;

    while (curr_window.size() > 0 && can_be_partitioned == 1 && counter > 0) {
        this_step = curr_window.size();
        if (from_0_to_1 == 1) {
            while (this_step > 0 && can_be_partitioned == 1) {
                for (int i = cache[curr_window.front()][0]; i != -1; i = cache[curr_window.front()][i]) {
                    if (cache[curr_window.front()][i] == 1) {
                        if (b[i][0] == 1) {
                            if (test > 0) { cout << curr_window.front() << " " << i << "\n"; }
                            can_be_partitioned = 0;
                            break;
                        }

                        cache[curr_window.front()][i] = 0;
                        cache[i][curr_window.front()] = 0;

                        visited[curr_window.front()] = 1;

                        b[i][1] = 1;

                        curr_window.push_back(i);

                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_0_to_1 = 0;
        }

        else {
            while (this_step > 0 && can_be_partitioned == 1) {
                for (int i = cache[curr_window.front()][0]; i != -1; i = cache[curr_window.front()][i]) {
                    if (cache[curr_window.front()][i] == 1) {
                        if (b[i][1] == 1) {
                            if (test > 0) { cout << curr_window.front() << " " << i << "\n"; }
                            can_be_partitioned = 0;
                            break;
                        }

                        cache[curr_window.front()][i] = 0;
                        cache[i][curr_window.front()] = 0;

                        visited[curr_window.front()] = 1;

                        b[i][0] = 1;

                        curr_window.push_back(i);

                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_0_to_1 = 1;
        }

        if (test > 0) {
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b[i][0] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b[i][1] << " "; }
            cout << "\n\n";
            cout << "curr_window.size() = " << curr_window.size() << "\n";
        }

        if (curr_window.size() == 0 && can_be_partitioned == 1 && counter > 0) {
            for (int i = search_start_idx; i < N; i++) {
                if (visited[i] == 0) {
                    search_start_idx = i;

                    curr_window.push_back(i);

                    visited[i] = 1;

                    if (from_0_to_1 == 1) { b[i][0] = 1; }

                    else { b[i][1] = 1; }

                    break;
                }
            }
        }
    }

    return can_be_partitioned;
}




bool possibleBipartition_1_0_0_1_vector (int N, vector<vector<int>>& dislikes) {
    if (N == 1 || dislikes.size() == 0) { return true; }
    int length = dislikes.size();
    int test = 0;

    vector<vector<int>> cache(N + 1, vector<int> ());
    bool visited[N + 1]; for (int i = 0; i <= N; i++) { visited[i] = 1; }

    for (int i = 0; i < dislikes.size(); i++) {
        cache[dislikes[i][0]].push_back(dislikes[i][1]);
        cache[dislikes[i][1]].push_back(dislikes[i][0]);
        visited[dislikes[i][0]] = 0;
        visited[dislikes[i][1]] = 0;
    }

    if (test > 0) {
        for (int i = 1; i <= N; i++) {
            cout << i << ": ";
            for (int j = 0; j < cache[i].size(); j++) {
                cout << cache[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool b[N + 1][2]; for (int i = 0; i <= N; i++) { b[i][0] = 0, b[i][1] = 0; }

    deque<int> curr_window;

    curr_window.push_back(dislikes[0][0]);
    b[dislikes[0][0]][0] = 1;
    visited[dislikes[0][0]] = 1;

    int this_step, counter = length, from_0_to_1 = 1, search_start_idx = 1;
    bool can_be_partitioned = 1;

    if (test > 0) {
        cout << "visited:\n";
        for (int i = 1; i <= N; i++) { cout << visited[i] << " "; }
        cout << "\n";
        cout << "\nhere is goes:\n";
    }

    while (curr_window.size() > 0 && can_be_partitioned == 1 && counter > 0) {
        if (test > 0) { cout << "\nRound Start:\n"; }
        this_step = curr_window.size();
        if (from_0_to_1 == 1) {
            //cout << "~0!\n";
            while (this_step > 0 && can_be_partitioned == 1) {
                //cout << "~1!\n";
                for (int i = 0; i < cache[curr_window.front()].size(); i++) {
                    //cout << "~3!\n";
                    if (b[cache[curr_window.front()][i]][0] == 1) {
                        if (test > 0) { cout << curr_window.front() << " " << i << "\n"; }
                        can_be_partitioned = 0;
                        break;
                    }
                    if (visited[cache[curr_window.front()][i]] == 0) {
                        //cout << "~4!\n";

                        visited[cache[curr_window.front()][i]] = 1;
                        b[cache[curr_window.front()][i]][1] = 1;
                        if (test > 0) { cout << "push_back " << cache[curr_window.front()][i] << "\n"; }
                        curr_window.push_back(cache[curr_window.front()][i]);
                        counter--;
                    }
                }
                curr_window.pop_front();
                this_step--;
            }

            from_0_to_1 = 0;
        }

        else {
            while (this_step > 0 && can_be_partitioned == 1) {
                for (int i = 0; i < cache[curr_window.front()].size(); i++) {
                    if (b[cache[curr_window.front()][i]][1] == 1) {
                        if (test > 0) { cout << curr_window.front() << " " << i << "\n"; }
                        can_be_partitioned = 0;
                        break;
                    }

                    if (visited[cache[curr_window.front()][i]] == 0) {

                        visited[cache[curr_window.front()][i]] = 1;
                        b[cache[curr_window.front()][i]][0] = 1;
                        if (test > 0) { cout << "push_back " << cache[curr_window.front()][i] << "\n"; }
                        curr_window.push_back(cache[curr_window.front()][i]);
                        counter--;
                    }
                }
                curr_window.pop_front();
                this_step--;
            }

            from_0_to_1 = 1;
        }

        if (test > 0) {
            cout << "\nvisited:\n";
            for (int i = 1; i <= N; i++) { cout << visited[i] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b[i][0] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b[i][1] << " "; }
            cout << "\n\n";
            cout << "curr_window.size() = " << curr_window.size() << "\n";
            cout << "counter = " << counter << "\n";
            test++;
            if (test > 10) break;
        }

        if (curr_window.size() == 0 && can_be_partitioned == 1 && counter > 0) {
            for (int i = search_start_idx; i < N; i++) {
                if (visited[i] == 0) {
                    if (test > 0) { cout << "push_back " << i << "\n"; }

                    curr_window.push_back(i);

                    search_start_idx = i + 1;

                    visited[i] = 1;

                    if (from_0_to_1 == 1) { b[i][0] = 1; }

                    else { b[i][1] = 1; }

                    break;
                }
            }
        }
    }

    return can_be_partitioned;
}




bool possibleBipartition_1_1 (int N, vector<vector<int>>& dislikes) {
    if (N == 1 || dislikes.size() == 0) { return true; }
    int length = dislikes.size();
    int test = 0;

    int cache[N + 1][N + 1];
    for (int i = 1; i <= N; i++) {  for (int j = 1; j <= N; j++) { cache[i][j] = -1; } }
    for (int i = 1; i <= N; i++) { cache[i][0] = 0; }

    bool visited[N + 1]; for (int i = 0; i <= N; i++) { visited[i] = 1; }

    for (int i = 0; i < dislikes.size(); i++) {
        cache[dislikes[i][0]][0]++;
        cache[dislikes[i][0]][cache[dislikes[i][0]][0]] = dislikes[i][1];

        cache[dislikes[i][1]][0]++;
        cache[dislikes[i][1]][cache[dislikes[i][1]][0]] = dislikes[i][0];

        visited[dislikes[i][0]] = 0;
        visited[dislikes[i][1]] = 0;
    }

    if (test > 0) {
        for (int i = 1; i <= N; i++) {
            cout << i << ": ";
            for (int j = 1; j <= cache[i][0]; j++) {
                cout << cache[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool b1[N + 1]; for (int i = 0; i <= N; i++) { b1[i] = 0; }
    bool b2[N + 1]; for (int i = 0; i <= N; i++) { b2[i] = 0; }

    deque<int> curr_window;

    curr_window.push_back(dislikes[0][0]);
    visited[dislikes[0][0]] = 1;
    b1[dislikes[0][0]] = 1;

    int this_step, counter = length, from_1_to_2 = 1;
    bool can_be_partitioned = 1;

    if (test > 0) {
        cout << "\n";
        for (int i = 1; i <= N; i++) { cout << b1[i] << " "; }
        cout << "\n";
        for (int i = 1; i <= N; i++) { cout << b2[i] << " "; }
        cout << "\n\n";
        cout << "curr_window.size() = " << curr_window.size() << "\n";
    }

    while (curr_window.size() > 0 && can_be_partitioned == 1 && counter > 0) {
        this_step = curr_window.size();

        if (from_1_to_2 == 1) {
            //cout << "~1!\n";
            while (this_step > 0 && can_be_partitioned == 1) {
                //cout << "~1.2!\n";
                for (int i = 1; i <= cache[curr_window.front()][0]; i++) {
                    //cout << "~1.3!\n";
                    if (b1[cache[curr_window.front()][i]] == 1) {
                        //cout << "~!\n";
                        can_be_partitioned = 0;
                        break;
                    }

                    if (visited[cache[curr_window.front()][i]] == 0) {
                        //cout << "~1.4!\n";
                        visited[cache[curr_window.front()][i]] = 1;
                        curr_window.push_back(cache[curr_window.front()][i]);
                        b2[cache[curr_window.front()][i]] = 1;
                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_1_to_2 = 0;
        }

        else {
            //cout << "~2!\n";
            while (this_step > 0 && can_be_partitioned == 1) {
                //cout << "~2.1!\n";
                for (int i = 1; i <= cache[curr_window.front()][0]; i++) {
                    //cout << "~2.3!\n";
                    if (b2[cache[curr_window.front()][i]] == 1) {
                        //cout << "~!\n";
                        can_be_partitioned = 0;
                        break;
                    }

                    if (visited[cache[curr_window.front()][i]] == 0) {
                        //cout << "~2.4!\n";

                        visited[cache[curr_window.front()][i]] = 1;
                        curr_window.push_back(cache[curr_window.front()][i]);
                        b1[cache[curr_window.front()][i]] = 1;
                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_1_to_2 = 1;
        }

        if (test > 0) {
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b1[i] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b2[i] << " "; }
            cout << "\n\n";
            cout << "curr_window.size() = " << curr_window.size() << "\n";
        }

        if (curr_window.size() == 0 && can_be_partitioned == 1 && counter > 0) {
            for (int i = 1; i <= N; i++) {
                if (visited[i] == 0) {
                    curr_window.push_back(i);

                    visited[i] = 1;

                    if (from_1_to_2 == 1) { b1[i] = 1; }

                    else { b2[i] = 1; }

                    break;
                }
            }
        }
    }

    return can_be_partitioned;
}

bool possibleBipartition_1_1_1 (int N, vector<vector<int>>& dislikes) {
    if (N == 1 || dislikes.size() == 0) { return true; }
    int length = dislikes.size();
    int test = 0;

    int cache[N + 1][N + 1]; for (int i = 1; i <= N; i++) { cache[i][0] = 0; }
    for (int i = 1; i <= N; i++) {  for (int j = 1; j <= N; j++) { cache[i][j] = -1; } }

    bool visited[N + 1]; for (int i = 0; i <= N; i++) { visited[i] = 1; }

    for (int i = 0; i < dislikes.size(); i++) {
        cache[dislikes[i][0]][0]++;
        cache[dislikes[i][0]][cache[dislikes[i][0]][0]] = dislikes[i][1];

        cache[dislikes[i][1]][0]++;
        cache[dislikes[i][1]][cache[dislikes[i][1]][0]] = dislikes[i][0];

        visited[dislikes[i][0]] = 0;
        visited[dislikes[i][1]] = 0;
    }

    if (test > 0) {
        for (int i = 1; i <= N; i++) {
            cout << i << ": ";
            for (int j = 1; j <= cache[i][0]; j++) {
                cout << cache[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool b[N + 1][2]; for (int i = 0; i <= N; i++) { b[i][0] = 0, b[i][1] = 0; }

    deque<int> curr_window;

    curr_window.push_back(dislikes[0][0]);
    visited[dislikes[0][0]] = 1;
    b[dislikes[0][0]][0] = 1;

    int this_step, counter = length, from_0_to_1 = 1;
    bool can_be_partitioned = 1;

    if (test > 0) {
        cout << "\n";
        for (int i = 1; i <= N; i++) { cout << b[i][0] << " "; }
        cout << "\n";
        for (int i = 1; i <= N; i++) { cout << b[i][1] << " "; }
        cout << "\n\n";
        cout << "curr_window.size() = " << curr_window.size() << "\n";
    }

    while (curr_window.size() > 0 && can_be_partitioned == 1 && counter > 0) {
        this_step = curr_window.size();

        if (from_0_to_1 == 1) {
            while (this_step > 0 && can_be_partitioned == 1) {
                //cout << "~1.2!\n";
                for (int i = 1; i <= cache[curr_window.front()][0]; i++) {
                    //cout << "~1.3!\n";
                    if (b[cache[curr_window.front()][i]][0] == 1) {
                        //cout << "~!\n";
                        can_be_partitioned = 0;
                        break;
                    }

                    if (visited[cache[curr_window.front()][i]] == 0) {
                        //cout << "~1.4!\n";
                        visited[cache[curr_window.front()][i]] = 1;
                        curr_window.push_back(cache[curr_window.front()][i]);
                        b[cache[curr_window.front()][i]][1] = 1;
                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_0_to_1 = 0;
        }

        else {
            while (this_step > 0 && can_be_partitioned == 1) {
                //cout << "~2.1!\n";
                for (int i = 1; i <= cache[curr_window.front()][0]; i++) {
                    //cout << "~2.3!\n";
                    if (b[cache[curr_window.front()][i]][1] == 1) {
                        //cout << "~!\n";
                        can_be_partitioned = 0;
                        break;
                    }

                    if (visited[cache[curr_window.front()][i]] == 0) {
                        //cout << "~2.4!\n";

                        visited[cache[curr_window.front()][i]] = 1;
                        curr_window.push_back(cache[curr_window.front()][i]);
                        b[cache[curr_window.front()][i]][0] = 1;
                        counter--;
                    }
                }

                curr_window.pop_front();
                this_step--;
            }

            from_0_to_1 = 1;
        }

        if (test > 0) {
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b[i][0] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << b[i][1] << " "; }
            cout << "\n\n";
            cout << "curr_window.size() = " << curr_window.size() << "\n";
        }

        if (curr_window.size() == 0 && can_be_partitioned == 1 && counter > 0) {
            for (int i = 1; i <= N; i++) {
                if (visited[i] == 0) {
                    curr_window.push_back(i);

                    visited[i] = 1;

                    if (from_0_to_1 == 1) { b[i][0] = 1; }

                    else { b[i][1] = 1; }

                    break;
                }
            }
        }
    }

    return can_be_partitioned;
}



bool possibleBipartition_1_2_wont_work (int N, vector<vector<int>>& dislikes) {
    if (N == 1 || dislikes.size() == 0) { return true; }
    int length = dislikes.size(), temp;
    int test = 1;

    for (int i = 0; i < length; i++) {
        if (dislikes[i][0] > dislikes[i][1]) {
            temp = dislikes[i][0];
            dislikes[i][0] = dislikes[i][1];
            dislikes[i][1] = temp;
        }
    }

    sort(dislikes.begin(), dislikes.end(), [](const auto &a, const auto &b) { return a[0] < b[0]; });

    if (test > 0) {
        cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << dislikes[i][0] << " ";
        }
        cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << dislikes[i][1] << " ";
        }
        cout << "\n\n";
    }

    int start_idx = 0, curr_val = dislikes[start_idx][0];

    int search_ranges[N + 1][2]; for (int i = 0; i <= N; i++) { search_ranges[i][0] = -1, search_ranges[i][1] = -1; }
    search_ranges[dislikes[0][0]][0] = 0;

    for (int i = 0; i < length; i++) {
        if (dislikes[i][0] != dislikes[start_idx][0])  {
            search_ranges[dislikes[start_idx][0]][1] = i - 1;

            start_idx = i;

            search_ranges[dislikes[start_idx][0]][0] = i;
        }
    }

    search_ranges[dislikes[length - 1][0]][1] = length - 1;
    if (test > 0) {
        cout << "\n";
        for (int i = 1; i <= N; i++) {
            cout << search_ranges[i][1] << " ";
        }
        cout << "\n";
        for (int i = 1; i <= N; i++) {
            cout << search_ranges[i][0] << " ";
        }
        cout << "\n\n";
    }

    bool b1[N + 1]; for (int i = 0; i <= N; i++) { b1[i] = 0; }
    bool b2[N + 1]; for (int i = 0; i <= N; i++) { b2[i] = 0; }

    bool can_be_partitioned = 1;

    deque<int> curr_window;
    curr_window.push_back(dislikes[0][0]);
    b1[dislikes[0][0]] = 1;

    if (test > 0) {
        cout << "\n";
        for (int i = 1; i <= N; i++) {
            cout << b1[i] << " ";
        }
        cout << "\n";
        for (int i = 1; i <= N; i++) {
            cout << b2[i] << " ";
        }
        cout << "\n\n";
    }

    int counter = length, search_start_from = 0;
    int only_proceed_these_steps, left, right, from_1_to_2 = 1;

    while (counter > 0 && can_be_partitioned == 1) {
        only_proceed_these_steps = curr_window.size();

        if (from_1_to_2 == 1) {
            if (test > 0) { cout << "from_1_to_2 = " << from_1_to_2 << "\n"; }

            while (only_proceed_these_steps > 0) {
                left = search_ranges[curr_window.front()][0];
                right = search_ranges[curr_window.front()][1];

                if (test > 0) {
                    cout << "left = " << left << "\n";
                    cout << "right = " << right << "\n";
                }

                if (left >= 0) {
                    for (int i = left; i <= right; i++) {
                        if (b1[dislikes[i][1]] == 1) { can_be_partitioned = 0; break; }

                        b2[dislikes[i][1]] = 1;
                        if (test > 0) { cout << "curr_windw.push_back(" << dislikes[i][1] << ")\n"; }
                        curr_window.push_back(dislikes[i][1]);
                        counter--;
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }

                curr_window.pop_front();
                only_proceed_these_steps--;
            }

            from_1_to_2 = 0;
        }

        else {
            if (test > 0) { cout << "from_1_to_2 = " << from_1_to_2 << "\n"; }

            while (only_proceed_these_steps > 0) {
                left = search_ranges[curr_window.front()][0];
                right = search_ranges[curr_window.front()][1];

                if (left >= 0) {
                    for (int i = left; i <= right; i++) {
                        if (b2[dislikes[i][1]] == 1) { can_be_partitioned = 0; break; }

                        b1[dislikes[i][1]] = 1;
                        curr_window.push_back(dislikes[i][1]);
                        if (test > 0) { cout << "curr_windw.push_back(" << dislikes[i][1] << ")\n"; }

                        counter--;
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }

                curr_window.pop_front();
                only_proceed_these_steps--;
            }

            from_1_to_2 = 1;
        }

        if (test > 0) {
            cout << "curr_window.size() = " << curr_window.size() << "\n";
            cout << "search_start_from = " << search_start_from << "\n";
            cout << "counter = " << counter << "\n";

            cout << "\n";
            for (int i = 1; i <= N; i++) {
                cout << search_ranges[i][1] << " ";
            }
            cout << "\n";
            for (int i = 1; i <= N; i++) {
                cout << search_ranges[i][0] << " ";
            }
            cout << "\n";

            cout << "\n";
            for (int i = 1; i <= N; i++) {
                cout << b1[i] << " ";
            }
            cout << "\n";
            for (int i = 1; i <= N; i++) {
                cout << b2[i] << " ";
            }
            cout << "\n\n";

            test++;
            if (test > 10) break;
        }

        if (curr_window.size() == 0) {
            for (int i = search_start_from; i < length; i++) {
                if (search_ranges[i][0] >= 0) {
                    curr_window.push_back(i);
                    search_start_from = i;
                    //if (b1[dislikes[i] == )
                    break;
                }
            }
        }
    }

    return can_be_partitioned;
}

bool possibleBipartition_2 (int N, vector<vector<int>>& dislikes) {
    if (N == 1 || dislikes.size() == 0) { return true; }
    int length = dislikes.size(), temp;
    int test = 1;

    for (int i = 0; i < length; i++) {
        if (dislikes[i][0] > dislikes[i][1]) {
            temp = dislikes[i][0];
            dislikes[i][0] = dislikes[i][1];
            dislikes[i][1] = temp;
        }
    }

    sort(dislikes.begin(), dislikes.end(), [](const auto &a, const auto &b) { return a[0] < b[0]; });

    if (test > 0) {
        cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << dislikes[i][0] << " ";
        }
        cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << dislikes[i][1] << " ";
        }
        cout << "\n\n";
    }

    int start_idx = 0, curr_val = dislikes[start_idx][0];

    int search_ranges[N + 1][2]; for (int i = 0; i <= N; i++) { search_ranges[i][0] = -1, search_ranges[i][1] = -1; }
    search_ranges[dislikes[0][0]][0] = 0;

    for (int i = 0; i < length; i++) {
        if (dislikes[i][0] != dislikes[start_idx][0])  {
            search_ranges[dislikes[start_idx][0]][1] = i - 1;

            start_idx = i;

            search_ranges[dislikes[start_idx][0]][0] = i;
        }
    }

    search_ranges[dislikes[length - 1][0]][1] = length - 1;
    if (test > 0) {
        cout << "\n";
        for (int i = 1; i <= N; i++) {
            cout << search_ranges[i][1] << " ";
        }
        cout << "\n";
        for (int i = 1; i <= N; i++) {
            cout << search_ranges[i][0] << " ";
        }
        cout << "\n\n";
    }

    // -1 means not yet determined, 0 means in "0" bucket, 1 means in "1" bucket
    int b[N + 1]; for (int i = 0; i <= N; i++) { b[i] = -1; }

    bool can_be_partitioned = 1;

    deque<int> curr_window;
    curr_window.push_back(dislikes[0][0]);
    b[dislikes[0][0]] = 0;

    if (test > 0) {
        cout << "\nb:\n";
        for (int i = 1; i <= N; i++) {
            cout << b[i] << " ";
        }
        cout << "\n\n";
    }

    int counter = length, search_start_from = 1;
    int only_proceed_these_steps, left, right, from_0_to_1 = 1;

    while (counter > 0 && can_be_partitioned == 1) {
        only_proceed_these_steps = curr_window.size();

        if (from_0_to_1 == 1) {
            if (test > 0) { cout << "from_0_to_1 = " << from_0_to_1 << "\n"; }

            while (only_proceed_these_steps > 0) {
                left = search_ranges[curr_window.front()][0];
                right = search_ranges[curr_window.front()][1];

                if (test > 0) {
                    cout << "left = " << left << "\n";
                    cout << "right = " << right << "\n";
                }

                if (left >= 0) {
                    for (int i = left; i <= right; i++) {
                        if (b[dislikes[i][1]] == 0) {
                            if (test > 0) { cout << "b[dislikes[i][1]] = " << b[dislikes[i][1]] << "\n"; }
                            can_be_partitioned = 0; break; }

                        b[dislikes[i][1]] = 1;
                        if (test > 0) { cout << "curr_windw.push_back(" << dislikes[i][1] << ")\n"; }
                        curr_window.push_back(dislikes[i][1]);
                        counter--;
                        if (test > 0) { cout << "counter--\n"; }
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }

                curr_window.pop_front();
                only_proceed_these_steps--;
            }

            from_0_to_1 = 0;
        }

        else {
            if (test > 0) { cout << "from_0_to_1 = " << from_0_to_1 << "\n"; }

            while (only_proceed_these_steps > 0) {
                left = search_ranges[curr_window.front()][0];
                right = search_ranges[curr_window.front()][1];

                if (left >= 0) {
                    for (int i = left; i <= right; i++) {
                        if (b[dislikes[i][1]] == 1) {
                            if (test > 0) { cout << "b[dislikes[i][1]] = " << b[dislikes[i][1]] << "\n"; }
                            can_be_partitioned = 0; break; }

                        b[dislikes[i][1]] = 0;
                        curr_window.push_back(dislikes[i][1]);
                        if (test > 0) { cout << "curr_windw.push_back(" << dislikes[i][1] << ")\n"; }

                        counter--;
                        if (test > 0) { cout << "counter--\n"; }
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }

                curr_window.pop_front();
                only_proceed_these_steps--;
            }

            from_0_to_1 = 1;
        }

        if (test > 0) {
            cout << "curr_window.size() = " << curr_window.size() << "\n";
            cout << "search_start_from = " << search_start_from << "\n";

            cout << "\n";
            for (int i = 1; i <= N; i++) {
                cout << search_ranges[i][1] << " ";
            }
            cout << "\n";
            for (int i = 1; i <= N; i++) {
                cout << search_ranges[i][0] << " ";
            }
            cout << "\nb:\n";
            for (int i = 1; i <= N; i++) {
                cout << b[i] << " ";
            }
            cout << "\n\n";

            test++;
            if (test > 10) break;
        }

        if (curr_window.size() == 0) {
            for (int i = search_start_from; i <= N; i++) {
                if (search_ranges[i][0] >= 0) {
                    if (test > 0) { cout << "curr_window.push_back(" << i << ")\n"; }
                    curr_window.push_back(i);

                    if (b[i] == 0) from_0_to_1 = 1;
                    else if (b[i] == 1) from_0_to_1 = 0;

                    search_start_from = i;
                    break;
                }
            }
        }
    }

    return can_be_partitioned;
}

// WORKED, but slow too, use too much memory
//, auto &sp4, auto &ep4, auto &sp5, auto &ep5
bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
    if (N <= 2 || dislikes.size() == 0) { return true; }
    int length = dislikes.size();

    //sp4 = chrono::steady_clock::now();
    dislikes.reserve(length * 2);
    for (int i = 0; i < length; i++) { dislikes.push_back({dislikes[i][1], dislikes[i][0]}); }

    sort(dislikes.begin(), dislikes.end(),
        [](const auto &a, const auto &b) {
            if (a[0] == b[0]) return a[1] < b[1];
            return a[0] < b[0];
        });

    //ep4 = chrono::steady_clock::now();

    int test = 0;
    if (test > 0) {
        //cout << "length = " << length << "\n";
        for (int i = 0; i < dislikes.size(); i++) {
            cout << dislikes[i][0] << " " << dislikes[i][1] << ", ";
        }
        cout << "\n\n";
    }

    //sp5 = chrono::steady_clock::now();

    int search_ranges[N + 1][2];
    for (int i = 0; i <= N; i++) { search_ranges[i][0] = -1, search_ranges[i][1] = -1; }

    int left = 0, right = left;
    for (int idx; left < dislikes.size(); ) {
        while (right < dislikes.size() && dislikes[right][0] == dislikes[left][0]) { right++; }
        idx = dislikes[left][0];
        search_ranges[idx][0] = left;
        search_ranges[idx][1] = right - 1;
        left = right;
    }

    int b[N + 1]; for (int i = 0; i <= N; i++) { b[i] = -1; }

    bool can_be_partitioned = 1, not_0_but_1 = 1;

    int curr_idx = 0, counter = length, search_from = 0, how_many_steps_in_this_round;
    deque<int> curr_window;

    b[dislikes[0][0]] = 1;
    while (dislikes[curr_idx][0] == dislikes[0][0]) {
        curr_window.push_back(dislikes[curr_idx][1]);
        b[dislikes[curr_idx][1]] = 0;
        curr_idx++;
        counter--;
    }
    search_ranges[dislikes[0][0]][0] = -1;
    search_ranges[dislikes[0][0]][1] = -1;

    while (counter > 0 && can_be_partitioned == 1) {
        how_many_steps_in_this_round = curr_window.size();
        if (not_0_but_1 == 1) {
            if (test > 0) { cout << "not_0_but_1 = " << not_0_but_1 << "\n"; }
            while (how_many_steps_in_this_round > 0) {
                left = search_ranges[curr_window.front()][0];
                if (left >= 0) {
                    right = search_ranges[curr_window.front()][1];

                    if (test > 0) { cout << "left = " << left << ", right = " << right << "\n"; }

                    for (int i = left; i <= right; i++) {
                        if (search_ranges[dislikes[i][1]][0] >= 0){
                            if (test > 0) { cout << dislikes[i][0] << " " << dislikes[i][1] << "\n"; }
                            if (b[dislikes[i][1]] == 0) { can_be_partitioned = 0; break; }
                            b[dislikes[i][1]] = 1;
                            curr_window.push_back(dislikes[i][1]);
                            counter--;
                        }
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }
                curr_window.pop_front();
                how_many_steps_in_this_round--;
            }

            not_0_but_1 = 0;
        }

        else {
            if (test > 0) { cout << "not_0_but_1 = " << not_0_but_1 << "\n"; }

            while (how_many_steps_in_this_round > 0) {
                left = search_ranges[curr_window.front()][0];
                if (left >= 0) {
                    right = search_ranges[curr_window.front()][1];
                    if (test > 0) { cout << "left = " << left << ", right = " << right << "\n"; }

                    for (int i = left; i <= right; i++) {
                        if (search_ranges[dislikes[i][1]][0] >= 0) {
                            if (test > 0) { cout << dislikes[i][0] << " " << dislikes[i][1] << "\n"; }
                            if (b[dislikes[i][1]] == 1) { can_be_partitioned = 0; break; }
                            b[dislikes[i][1]] = 0;
                            curr_window.push_back(dislikes[i][1]);
                            counter--;
                        }
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }
                curr_window.pop_front();
                how_many_steps_in_this_round--;
            }

            not_0_but_1 = 1;
        }

        if (test > 0) {
            cout << "b:\n";
            for (int i = 1; i <= N; i++) { cout << b[i] << " "; }
            cout << "\n\nsearch_ranges:\n";
            for (int i = 1; i <= N; i++) { cout << search_ranges[i][0] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << search_ranges[i][1] << " "; }
            cout << "\ncounter = " << counter;
            cout << "\ncan_be_partitioned = " << can_be_partitioned << "\n\n";
        }

        if (curr_window.size() == 0 && counter > 0 && can_be_partitioned == 1) {
            for (int i = search_from; i < dislikes.size(); i++) {
                if (search_ranges[dislikes[i][0]][0] >= 0) {
                    curr_window.push_back(dislikes[i][0]);
                    search_from = i;
                    break;
                }
            }
        }
    }

    //ep5 = chrono::steady_clock::now();

    return can_be_partitioned;
}


void merge_sort (int a[][2], int length) {
    int b[length][2];
    for (int i = 0; i < length; i++) { b[i][0] = a[i][0], b[i][1] = a[i][1]; }

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        b[k][0] = a[i][0];
                        b[k][1] = a[i][1];
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
                            b[k][0] = a[i][0];
                            b[k][1] = a[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j][0];
                        b[k][1] = a[j][1];
                        j++, j_step++;
                    }

                    else if (a[i][0] <= a[j][0]) {
                        b[k][0] = a[i][0];
                        b[k][1] = a[i][1];
                        i++, i_step++;
                    }

                    else if (a[i][0] > a[j][0]) {
                        b[k][0] = a[j][0];
                        b[k][1] = a[j][1];
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
                        a[k][0] = b[i][0];
                        a[k][1] = b[i][1];
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
                            a[k][0] = b[i][0];
                            a[k][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k][0] = b[j][0];
                        a[k][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][0] <= b[j][0]) {
                        a[k][0] = b[i][0];
                        a[k][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][0] > b[j][0]) {
                        a[k][0] = b[j][0];
                        a[k][1] = b[j][1];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 1;
        }
    }

    if (from_a_to_b == 0) {
        for (int i = 0; i < length; i++) {
            a[i][0] = b[i][0], a[i][1] = b[i][1];
        }
    }
}

void merge_sort_range (int a[][2], int length, int left, int right) {
    int range_length = right - left + 1;
    int b[range_length][2];
    for (int i = 0; i < range_length; i++) { b[i][0] = a[i + left][0], b[i][1] = a[i + left][1]; }

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < range_length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < range_length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= range_length) {
                    for (int k = i; k < range_length; k++) {
                        b[k][0] = a[i + left][0];
                        b[k][1] = a[i + left][1];
                        i++;
                    }
                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= range_length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) {
                            break;
                        }

                        else {
                            b[k][0] = a[i + left][0];
                            b[k][1] = a[i + left][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j + left][0];
                        b[k][1] = a[j + left][1];
                        j++, j_step++;
                    }

                    else if (a[i + left][1] <= a[j + left][1]) {
                        b[k][0] = a[i + left][0];
                        b[k][1] = a[i + left][1];
                        i++, i_step++;
                    }

                    else if (a[i + left][1] > a[j + left][1]) {
                        b[k][0] = a[j + left][0];
                        b[k][1] = a[j + left][1];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 0;
        }

        else if (from_a_to_b == 0) {
            for (int i = 0, j = i + double_this_long_after_merge; i < range_length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= range_length) {
                    for (int k = i; k < range_length; k++) {
                        a[k + left][0] = b[i][0];
                        a[k + left][1] = b[i][1];
                        i++;
                    }
                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= range_length )||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) {
                            break;
                        }

                        else {
                            a[k + left][0] = b[i][0];
                            a[k + left][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k + left][0] = b[j][0];
                        a[k + left][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][1] <= b[j][1]) {
                        a[k + left][0] = b[i][0];
                        a[k + left][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][1] > b[j][1]) {
                        a[k + left][0] = b[j][0];
                        a[k + left][1] = b[j][1];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 1;
        }
    }

    if (from_a_to_b == 0) {
        for (int i = 0; i < range_length; i++) {
            a[i + left][0] = b[i][0], a[i + left][1] = b[i][1];
        }
    }
}

//, auto &sp3, auto &ep3, auto &sp4, auto &ep4
// blazing fast? NO.
bool possibleBipartition_linear_memory(int N, vector<vector<int>>& dislikes) {
    if (N <= 2 || dislikes.size() == 0) { return true; }
    int test = 0;
    int length = dislikes.size(), double_length = length * 2;
//sp3 = chrono::steady_clock::now();
    int longer_dislikes[double_length][2];
    for (int i = 0; i < length; i++) {
        longer_dislikes[i][0] = dislikes[i][0];
        longer_dislikes[i][1] = dislikes[i][1];

        longer_dislikes[i + length][0] = dislikes[i][1];
        longer_dislikes[i + length][1] = dislikes[i][0];
    }

    merge_sort(longer_dislikes, double_length);

    if (test > 0) {
        cout << "\nlonger_dislikes:\n";
        for (int i = 0; i < double_length; i++) {
            cout << longer_dislikes[i][0] << " " << longer_dislikes[i][1] << ", ";
        }
        cout << "\n\n";
    }

    for (int left = 0, right = left; left < double_length; ) {
        while (right < double_length && longer_dislikes[right][0] == longer_dislikes[left][0]) { right++; }

        merge_sort_range(longer_dislikes, double_length, left, right - 1);

        left = right;
    }

    //ep3 = chrono::steady_clock::now();

    if (test > 0) {
        cout << "\nlonger_dislikes:\n";
        for (int i = 0; i < double_length; i++) {
            cout << longer_dislikes[i][0] << " " << longer_dislikes[i][1] << ", ";
        }
        cout << "\n\n";
    }

    //sp4 = chrono::steady_clock::now();
    int search_ranges[N + 1][2];
    for (int i = 0; i <= N; i++) { search_ranges[i][0] = -1, search_ranges[i][1] = -1; }

    int left = 0, right = left;
    for (int idx; left < double_length; ) {
        while (right < double_length && longer_dislikes[right][0] == longer_dislikes[left][0]) { right++; }
        idx = longer_dislikes[left][0];
        search_ranges[idx][0] = left;
        search_ranges[idx][1] = right - 1;
        left = right;
    }

    int b[N + 1]; for (int i = 0; i <= N; i++) { b[i] = -1; }

    bool can_be_partitioned = 1, not_0_but_1 = 1;

    int curr_idx = 0, counter = length, search_from = 0, how_many_steps_in_this_round;
    deque<int> curr_window;

    b[longer_dislikes[0][0]] = 1;
    while (longer_dislikes[curr_idx][0] == longer_dislikes[0][0]) {
        curr_window.push_back(longer_dislikes[curr_idx][1]);
        b[longer_dislikes[curr_idx][1]] = 0;
        //cout << "b[" << longer_dislikes[curr_idx][1] << "] = 0\n";
        curr_idx++;
        counter--;
    }
    search_ranges[longer_dislikes[0][0]][0] = -1;
    search_ranges[longer_dislikes[0][0]][1] = -1;

    if (test > 0) {
        cout << "b:\n";
        for (int i = 1; i <= N; i++) { cout << b[i] << " "; }
        cout << "\n\nsearch_ranges:\n";
        for (int i = 1; i <= N; i++) { cout << search_ranges[i][0] << " "; }
        cout << "\n";
        for (int i = 1; i <= N; i++) { cout << search_ranges[i][1] << " "; }
        cout << "\ncounter = " << counter;

        cout << "\n\nlet's roll\n\n";
    }

    while (counter > 0 && can_be_partitioned == 1) {
        how_many_steps_in_this_round = curr_window.size();
        if (not_0_but_1 == 1) {
            if (test > 0) { cout << "not_0_but_1 = " << not_0_but_1 << "\n"; }
            while (how_many_steps_in_this_round > 0) {
                left = search_ranges[curr_window.front()][0];
                if (left >= 0) {
                    right = search_ranges[curr_window.front()][1];

                    if (test > 0) { cout << "left = " << left << ", right = " << right << "\n"; }

                    for (int i = left; i <= right; i++) {
                        if (search_ranges[longer_dislikes[i][1]][0] >= 0){
                            if (test > 0) { cout << longer_dislikes[i][0] << " " << longer_dislikes[i][1] << "\n"; }
                            if (b[longer_dislikes[i][1]] == 0) { can_be_partitioned = 0; break; }
                            b[longer_dislikes[i][1]] = 1;
                            curr_window.push_back(longer_dislikes[i][1]);
                            counter--;
                        }
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }
                curr_window.pop_front();
                how_many_steps_in_this_round--;
            }

            not_0_but_1 = 0;
        }

        else {
            if (test > 0) { cout << "not_0_but_1 = " << not_0_but_1 << "\n"; }

            while (how_many_steps_in_this_round > 0) {
                left = search_ranges[curr_window.front()][0];
                if (left >= 0) {
                    right = search_ranges[curr_window.front()][1];
                    if (test > 0) { cout << "left = " << left << ", right = " << right << "\n"; }

                    for (int i = left; i <= right; i++) {
                        if (search_ranges[longer_dislikes[i][1]][0] >= 0) {
                            if (test > 0) { cout << longer_dislikes[i][0] << " " << longer_dislikes[i][1] << "\n"; }
                            if (b[longer_dislikes[i][1]] == 1) { can_be_partitioned = 0; break; }
                            b[longer_dislikes[i][1]] = 0;
                            curr_window.push_back(longer_dislikes[i][1]);
                            counter--;
                        }
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }
                curr_window.pop_front();
                how_many_steps_in_this_round--;
            }

            not_0_but_1 = 1;
        }

        if (test > 0) {
            cout << "b:\n";
            for (int i = 1; i <= N; i++) { cout << b[i] << " "; }
            cout << "\n\nsearch_ranges:\n";
            for (int i = 1; i <= N; i++) { cout << search_ranges[i][0] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << search_ranges[i][1] << " "; }
            cout << "\ncounter = " << counter;
            cout << "\ncan_be_partitioned = " << can_be_partitioned << "\n\n";
        }

        if (curr_window.size() == 0 && counter > 0 && can_be_partitioned == 1) {
            for (int i = search_from; i < double_length; i++) {
                if (search_ranges[longer_dislikes[i][0]][0] >= 0) {
                    curr_window.push_back(longer_dislikes[i][0]);
                    search_from = i;
                    break;
                }
            }
        }
    }

    //ep4 = chrono::steady_clock::now();
    return can_be_partitioned;
}



// double top 2%
bool possibleBipartition_linear_memory_counting_sort(int N, vector<vector<int>>& dislikes) {
    if (N <= 2 || dislikes.size() == 0) { return true; }
    int test = 0;

    int length = dislikes.size();

    int value_counter[N + 1][2]; for (int i = 0; i <= N; i++) { value_counter[i][0] = 0, value_counter[i][1] = 0; }
    for (int i = 0; i < length; i++) { value_counter[dislikes[i][0]][0]++; value_counter[dislikes[i][1]][0]++; }
    for (int last_idx = 0, accumulated = 0; last_idx <= N; ) {
        while(last_idx <= N && value_counter[last_idx][0] == 0) { last_idx++; }
        if (last_idx <= N) {
            value_counter[last_idx][1] = accumulated;
            accumulated += value_counter[last_idx][0];
            last_idx++;
        }
    }

    if (test > 0) {
        cout << "\ncounter:\n";
        for (int i = 1; i <= N; i++) {
            cout << value_counter[i][0] << " " << value_counter[i][1] << ", ";
        }
        cout << "\n\n";
    }

    int double_length = length * 2;
    int longer_dislikes[double_length][2];
    for (int i = 0; i < length; i++) {
        longer_dislikes[value_counter[dislikes[i][0]][1]][0] = dislikes[i][0];
        longer_dislikes[value_counter[dislikes[i][0]][1]][1] = dislikes[i][1];
        value_counter[dislikes[i][0]][1]++;

        longer_dislikes[value_counter[dislikes[i][1]][1]][0] = dislikes[i][1];
        longer_dislikes[value_counter[dislikes[i][1]][1]][1] = dislikes[i][0];
        value_counter[dislikes[i][1]][1]++;
    }

    if (test > 0) {
        cout << "\nlonger_dislikes:\n";
        for (int i = 0; i < double_length; i++) {
            cout << longer_dislikes[i][0] << " " << longer_dislikes[i][1] << ", ";
        }
        cout << "\n\n";
    }

    /*bool itsOK = 1;
    for (int i = 0; i < double_length - 1; i++) {
        if (longer_dislikes[i][0] > longer_dislikes[i + 1][0]) {
            itsOK = 0;
            break;
        }
    }
    if (itsOK == 0) { cout << "-------------------------------------------------\n"; }*/

    int search_ranges[N + 1][2];
    for (int i = 0; i <= N; i++) { search_ranges[i][0] = -1, search_ranges[i][1] = -1; }

    int left = 0, right = left;
    for (int idx; left < double_length; ) {
        while (right < double_length && longer_dislikes[right][0] == longer_dislikes[left][0]) { right++; }
        idx = longer_dislikes[left][0];
        search_ranges[idx][0] = left;
        search_ranges[idx][1] = right - 1;
        left = right;
    }

    int b[N + 1]; for (int i = 0; i <= N; i++) { b[i] = -1; }

    bool can_be_partitioned = 1, not_0_but_1 = 1;

    int curr_idx = 0, counter = length, search_from = 0, how_many_steps_in_this_round;
    deque<int> curr_window;

    b[longer_dislikes[0][0]] = 1;
    while (longer_dislikes[curr_idx][0] == longer_dislikes[0][0]) {
        curr_window.push_back(longer_dislikes[curr_idx][1]);
        b[longer_dislikes[curr_idx][1]] = 0;
        //cout << "b[" << longer_dislikes[curr_idx][1] << "] = 0\n";
        curr_idx++;
        counter--;
    }
    search_ranges[longer_dislikes[0][0]][0] = -1;
    search_ranges[longer_dislikes[0][0]][1] = -1;

    if (test > 0) {
        cout << "b:\n";
        for (int i = 1; i <= N; i++) { cout << b[i] << " "; }
        cout << "\n\nsearch_ranges:\n";
        for (int i = 1; i <= N; i++) { cout << search_ranges[i][0] << " "; }
        cout << "\n";
        for (int i = 1; i <= N; i++) { cout << search_ranges[i][1] << " "; }
        cout << "\ncounter = " << counter;

        cout << "\n\nlet's roll\n\n";
    }

    while (counter > 0 && can_be_partitioned == 1) {
        how_many_steps_in_this_round = curr_window.size();
        if (not_0_but_1 == 1) {
            if (test > 0) { cout << "not_0_but_1 = " << not_0_but_1 << "\n"; }
            while (how_many_steps_in_this_round > 0) {
                left = search_ranges[curr_window.front()][0];
                if (left >= 0) {
                    right = search_ranges[curr_window.front()][1];

                    if (test > 0) { cout << "left = " << left << ", right = " << right << "\n"; }

                    for (int i = left; i <= right; i++) {
                        if (search_ranges[longer_dislikes[i][1]][0] >= 0){
                            if (test > 0) { cout << longer_dislikes[i][0] << " " << longer_dislikes[i][1] << "\n"; }
                            if (b[longer_dislikes[i][1]] == 0) { can_be_partitioned = 0; break; }
                            b[longer_dislikes[i][1]] = 1;
                            curr_window.push_back(longer_dislikes[i][1]);
                            counter--;
                        }
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }
                curr_window.pop_front();
                how_many_steps_in_this_round--;
            }

            not_0_but_1 = 0;
        }

        else {
            if (test > 0) { cout << "not_0_but_1 = " << not_0_but_1 << "\n"; }

            while (how_many_steps_in_this_round > 0) {
                left = search_ranges[curr_window.front()][0];
                if (left >= 0) {
                    right = search_ranges[curr_window.front()][1];
                    if (test > 0) { cout << "left = " << left << ", right = " << right << "\n"; }

                    for (int i = left; i <= right; i++) {
                        if (search_ranges[longer_dislikes[i][1]][0] >= 0) {
                            if (test > 0) { cout << longer_dislikes[i][0] << " " << longer_dislikes[i][1] << "\n"; }
                            if (b[longer_dislikes[i][1]] == 1) { can_be_partitioned = 0; break; }
                            b[longer_dislikes[i][1]] = 0;
                            curr_window.push_back(longer_dislikes[i][1]);
                            counter--;
                        }
                    }

                    search_ranges[curr_window.front()][0] = -1;
                    search_ranges[curr_window.front()][1] = -1;
                }
                curr_window.pop_front();
                how_many_steps_in_this_round--;
            }

            not_0_but_1 = 1;
        }

        if (test > 0) {
            cout << "b:\n";
            for (int i = 1; i <= N; i++) { cout << b[i] << " "; }
            cout << "\n\nsearch_ranges:\n";
            for (int i = 1; i <= N; i++) { cout << search_ranges[i][0] << " "; }
            cout << "\n";
            for (int i = 1; i <= N; i++) { cout << search_ranges[i][1] << " "; }
            cout << "\ncounter = " << counter;
            cout << "\ncan_be_partitioned = " << can_be_partitioned << "\n\n";
        }

        if (curr_window.size() == 0 && counter > 0 && can_be_partitioned == 1) {
            for (int i = search_from; i < double_length; i++) {
                if (search_ranges[longer_dislikes[i][0]][0] >= 0) {
                    curr_window.push_back(longer_dislikes[i][0]);
                    search_from = i;
                    break;
                }
            }
        }
    }

    return can_be_partitioned;
}

// BLAZING FAST
bool possibleBipartition_linear_memory_counting_sort_shink_a_bit(int N, vector<vector<int>>& dislikes) {
    if (N <= 2 || dislikes.size() == 0) { return true; }

    int length = dislikes.size();

    // count sort start
    int count_sort_helper[N + 1]; for (int i = 0; i <= N; i++) { count_sort_helper[i] = 0; }
    for (int i = 0; i < length; i++) { count_sort_helper[dislikes[i][0]]++; count_sort_helper[dislikes[i][1]]++; }

    for (int last_idx = 0, accumulated = 0, temp; last_idx <= N; ) {
        while(last_idx <= N && count_sort_helper[last_idx] == 0) { last_idx++; }

        if (last_idx <= N) {
            temp = accumulated;
            accumulated += count_sort_helper[last_idx];
            count_sort_helper[last_idx] = temp;
            last_idx++;
        }
    }

    int double_length = length * 2;
    int longer_dislikes[double_length][2];
    for (int i = 0; i < length; i++) {
        longer_dislikes[count_sort_helper[dislikes[i][0]]][0] = dislikes[i][0];
        longer_dislikes[count_sort_helper[dislikes[i][0]]][1] = dislikes[i][1];
        count_sort_helper[dislikes[i][0]]++;

        longer_dislikes[count_sort_helper[dislikes[i][1]]][0] = dislikes[i][1];
        longer_dislikes[count_sort_helper[dislikes[i][1]]][1] = dislikes[i][0];
        count_sort_helper[dislikes[i][1]]++;
    }
    // count sort finish

    // record search ranges of values
    // search_ranges has 2 uses:
    //      1. if PRESENT & NOT YET VISITED, record "where to find (in longer_dislikes) that value range"
    //      2. if NOT PRESENT or VISITED, value == -1 to PREVENT unnecessary search
    int search_ranges[N + 1][2];
    for (int i = 0; i <= N; i++) { search_ranges[i][0] = -1, search_ranges[i][1] = -1; }

    int left = 0, right = left;
    for (int idx; left < double_length; ) {
        while (right < double_length && longer_dislikes[right][0] == longer_dislikes[left][0]) { right++; }

        idx = longer_dislikes[left][0];
        search_ranges[idx][0] = left;
        search_ranges[idx][1] = right - 1;
        left = right;
    }
    // range recording complete

    // now try to split all items by saving "0" or "1" into b
    int b[N + 1]; for (int i = 0; i <= N; i++) { b[i] = -1; }

    bool can_be_partitioned = 1, not_0_but_1 = 1;

    int curr_idx = 0, counter = length, search_from = 0, how_many_steps_in_this_round;
    deque<int> curr_window;

    // manually do the 1st step
    b[longer_dislikes[0][0]] = 1;
    while (longer_dislikes[curr_idx][0] == longer_dislikes[0][0]) {
        curr_window.push_back(longer_dislikes[curr_idx][1]);
        b[longer_dislikes[curr_idx][1]] = 0;
        curr_idx++;
        counter--;
    }
    search_ranges[longer_dislikes[0][0]][0] = -1;
    search_ranges[longer_dislikes[0][0]][1] = -1;
    // 1st step complete

    // now start rolling
    while (counter > 0 && can_be_partitioned == 1) {
        how_many_steps_in_this_round = curr_window.size();
        if (not_0_but_1 == 1) {
            while (how_many_steps_in_this_round > 0) {
                left = search_ranges[curr_window.front()][0];
                if (left >= 0) {// if curr_window.front() is PRESENT & NOT YET VISITED
                    right = search_ranges[curr_window.front()][1];

                    for (int i = left; i <= right; i++) {
                        if (search_ranges[longer_dislikes[i][1]][0] >= 0){
                            if (b[longer_dislikes[i][1]] == 0) { can_be_partitioned = 0; break; }

                            b[longer_dislikes[i][1]] = 1;
                            curr_window.push_back(longer_dislikes[i][1]);
                            counter--;
                        }
                    }

                    search_ranges[curr_window.front()][0] = -1;// we will NOT EVER visit curr_window.front() again
                }
                curr_window.pop_front();
                how_many_steps_in_this_round--;
            }

            not_0_but_1 = 0;
        }

        else {
            while (how_many_steps_in_this_round > 0) {
                left = search_ranges[curr_window.front()][0];
                if (left >= 0) {
                    right = search_ranges[curr_window.front()][1];
                    for (int i = left; i <= right; i++) {
                        if (search_ranges[longer_dislikes[i][1]][0] >= 0) {
                            if (b[longer_dislikes[i][1]] == 1) { can_be_partitioned = 0; break; }
                            b[longer_dislikes[i][1]] = 0;
                            curr_window.push_back(longer_dislikes[i][1]);
                            counter--;
                        }
                    }

                    search_ranges[curr_window.front()][0] = -1;
                }
                curr_window.pop_front();
                how_many_steps_in_this_round--;
            }

            not_0_but_1 = 1;
        }

        if (curr_window.size() == 0 && counter > 0 && can_be_partitioned == 1) {
            for (int i = search_from; i < double_length; i++) {
                if (search_ranges[longer_dislikes[i][0]][0] >= 0) {
                    curr_window.push_back(longer_dislikes[i][0]);
                    search_from = i;
                    break;
                }
            }
        }
    }

    return can_be_partitioned;
}




//  I WILL MOST LIKELY TO RUN INTO ALL KINDS OF PROBLEMS IF I DO NOT BUILD A BRUTEFORCE & TEST A BIT
//  NO MATTER HOW CONFIDENT I MIGHT HAVE ON THAT ALGORITHM
int main(){
    srand(time(0));int N = 10, display = 0, input = 1;
    vector<vector<int>> wtf;
    // = {{4,7},{4,8},{5,6},{1,6},{3,7},{2,5},{5,8},{1,2},{4,9},{6,10},{8,10},{3,6},{2,10},{9,10},{3,9},{2,3},{1,9},{4,6},{5,7},{3,8},{1,8},{1,7},{2,4}};
    // = {{1,2},{3,4},{4,5},{3,5}};
    // = {{5,9},{5,10},{5,6},{5,7},{1,5},{4,5},{2,5},{5,8},{3,5}};10

    auto sp1 = chrono::steady_clock::now(); auto ep1 = chrono::steady_clock::now(); auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now(); auto ep2 = chrono::steady_clock::now(); auto dif2 = ep2 - sp2;
    auto sp3 = chrono::steady_clock::now(); auto ep3 = chrono::steady_clock::now(); auto dif3 = ep3 - sp3;
    auto sp4 = chrono::steady_clock::now(); auto ep4 = chrono::steady_clock::now(); auto dif4 = ep4 - sp4;
    auto sp5 = chrono::steady_clock::now(); auto ep5 = chrono::steady_clock::now(); auto dif5 = ep5 - sp5;
    auto sp6 = chrono::steady_clock::now(); auto ep6 = chrono::steady_clock::now(); auto dif6 = ep6 - sp6;

    bool already[N + 1][N + 1];
    int length, temp0, temp1, max_counter = (N * (N - 1) / 2 < 100000)? N * (N - 1) / 2: 100000;

for (int m = 1, temp; m <= 1000000; m++) {if (m % 100000 == 0) {cout << "m = " << m << "\n";}

    if (input == 1) {//rand() % (upper_range - lower_range + 1) + lower_range
        for (int i = 1; i <= N; i++) { for (int j = 1; j <= N; j++) { already[i][j] = 0; } }

        length = rand() % (max_counter - 0 + 1) + 0;

        for (int i = 0; i < length; i++) {
            temp0 = rand() % (N - 1 + 1) + 1;
            temp1 = rand() % (N - 1 + 1) + 1;
            while (already[temp0][temp1] == 1 || already[temp1][temp0] == 1 || temp0 == temp1) {
                temp0 = rand() % (N - 1 + 1) + 1;
                temp1 = rand() % (N - 1 + 1) + 1;
            }
            already[temp0][temp1] = 1;
            already[temp1][temp0] = 1;
            wtf.push_back({temp0, temp1});
        }
    }
    if (display == 1) {
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{" << wtf[i][0] << ", " << wtf[i][1] << "}";
            if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    for (int i = 0; i < wtf.size(); i++) {
        if (wtf[i][0] > wtf[i][1]) {
            temp = wtf[i][0];
            wtf[i][0] = wtf[i][1];
            wtf[i][1] = temp;
        }
    }
    vector<vector<int>> wtf1(wtf);vector<vector<int>> wtf2(wtf);vector<vector<int>> wtf3(wtf);
    vector<vector<int>> wtf4(wtf);vector<vector<int>> wtf5(wtf);vector<vector<int>> wtf6(wtf);

    sp1 = chrono::steady_clock::now();
    bool s = possibleBipartition_1_0(N, wtf1);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;
    if (display == 1) {cout << "s = " << s << "\n";}

    sp2 = chrono::steady_clock::now();
    bool ss = possibleBipartition_1_0_0_1(N, wtf2);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;
    if (display == 1) {cout << "ss = " << ss << "\n";}

    sp3 = chrono::steady_clock::now();
    bool sss = possibleBipartition(N, wtf3);
    ep3 = chrono::steady_clock::now();
    dif3 += ep3 - sp3;
    if (display == 1) {cout << "sss = " << sss << "\n";}

    sp4 = chrono::steady_clock::now();
    bool ssss = possibleBipartition_linear_memory_counting_sort(N, wtf4);//, sp5, ep5, sp6, ep6
    ep4 = chrono::steady_clock::now();
    dif4 += ep4 - sp4;
    if (display == 1) {cout << "ssss = " << ssss << "\n";}

    sp5 = chrono::steady_clock::now();
    bool sssss = possibleBipartition_linear_memory_counting_sort_shink_a_bit(N, wtf5);
    ep5 = chrono::steady_clock::now();
    dif5 += ep5 - sp5;
    if (display == 1) {cout << "sssss = " << sssss << "\n";}

    dif6 += ep6 - sp6;

    if (s != ss || s != sss || s != ssss || s != sssss) {
        cout << "m = " << m << "\n";
        cout << "s = " << s << "\n";
        cout << "ss = " << ss << "\n";
        cout << "sss = " << sss << "\n";
        cout << "ssss = " << ssss << "\n";
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{" << wtf[i][0] << ", " << wtf[i][1] << "}";
            if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
        break;
    }

wtf.clear();}
cout << duration <double, milli> (dif1).count() << " ms" << "\n";
cout << duration <double, milli> (dif2).count() << " ms" << "\n";
cout << duration <double, milli> (dif3).count() << " ms" << "\n";
cout << duration <double, milli> (dif4).count() << " ms" << "\n";
cout << duration <double, milli> (dif5).count() << " ms" << "\n";
cout << duration <double, milli> (dif6).count() << " ms" << "\n";

    return 0;
}



