/*1345. Jump Game IV
Hard

Given an array of integers arr, you are initially positioned at the first index of the array.

In one step you can jump from index i to index:
    i + 1 where: i + 1 < arr.length.
    i - 1 where: i - 1 >= 0.
    j where: arr[i] == arr[j] and i != j.

Return the minimum number of steps to reach the last index of the array.

Notice that you can not jump outside of the array at any time.

Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9.
Note that index 9 is the last index of the array.

Input: arr = [7]
Output: 0
Explanation: Start index is the last index. You don't need to jump.

Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: You can jump directly from index 0 to index 7 which is last index of the array.

Input: arr = [6,1,9]
Output: 2

Input: arr = [11,22,7,7,7,7,7,7,7,22,13]
Output: 3

Constraints:
    1 <= arr.length <= 5 * 104
    -108 <= arr[i] <= 108
*/

/*
class Solution {
public:
    int minJumps(vector<int>& arr) {

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


// start from the last index, gradually widen search window, till found 0 index
int minJumps_1_0(vector<int>& arr) {
    if (arr.size() == 1) { return 0; }
    int length = arr.size();

    unordered_map<int, unordered_set<int>> value_to_idx;
    for (int i = 0; i < length; i++) {
        auto find_value = value_to_idx.find(arr[i]);
        if (find_value == value_to_idx.end()) {
            value_to_idx.insert({arr[i], unordered_set<int> ()});
        }
        value_to_idx[arr[i]].insert(i);
    }

    if (value_to_idx.size() == length) { return length - 1; }

    /*for (auto i = value_to_idx.begin(); i != value_to_idx.end(); ++i) {
        cout << i->first << ": ";
        for (auto j = i->second.begin(); j != i->second.end(); ++j) {
            cout << *j << " ";
        }
        cout << "\n";
    }*/

    unordered_set<int> search_pool_1;
    unordered_set<int> search_pool_2;
    bool marked[length]; for (int i = 0; i < length; i++) { marked[i] = 0; }
    search_pool_1.insert(length - 1);
    marked[length - 1] = 1;
    int found = 0, counter = 0, from_1_to_2 = 1, curr_idx;
    while (found == 0) {
        if (from_1_to_2 == 1) {
            //  cout << "search_pool_1.size() = " << search_pool_1.size() << "\n";
            for (auto i = search_pool_1.begin(), erase_this = i; i != search_pool_1.end(); ) {
                curr_idx = *i;

                // do i need to add one to counter?
                if (curr_idx == 1) { found = 1; break; }

                if (marked[curr_idx - 1] == 0) {
                    search_pool_2.insert(curr_idx - 1);
                    //cout << "search_pool_2.insert(" << curr_idx - 1 << ")\n";
                    marked[curr_idx - 1] = 1;
                }

                if ((curr_idx + 1 < length) && (marked[curr_idx + 1] == 0)) {
                    search_pool_2.insert(curr_idx + 1);
                    marked[curr_idx + 1] = 1;
                }

                if (value_to_idx.find(arr[curr_idx]) != value_to_idx.end()) {
                    for (auto j = value_to_idx[arr[curr_idx]].begin(); j != value_to_idx[arr[curr_idx]].end(); ++j) {
                        if (marked[*j] == 0) {
                            if (*j == 0) { found = 1; break; }

                            search_pool_2.insert(*j);
                            marked[*j] = 1;
                        }
                    }

                    if (found == 1) { break; }

                    value_to_idx.erase(value_to_idx.find(arr[curr_idx]));
                }

                ++i;
                search_pool_1.erase(erase_this);
                erase_this = i;
            }

            //  cout << "search_pool_1.size() = " << search_pool_1.size() << "\n\n";

            from_1_to_2 = 0;
        }

        else {
            for (auto i = search_pool_2.begin(), erase_this = i; i != search_pool_2.end(); ) {
                curr_idx = *i;

                // do i need to add one to counter?
                if (curr_idx == 1) { found = 1; break; }

                if (marked[curr_idx - 1] == 0) {
                    search_pool_1.insert(curr_idx - 1);
                    marked[curr_idx - 1] = 1;
                }

                if ((curr_idx + 1 < length) && (marked[curr_idx + 1] == 0)) {
                    search_pool_1.insert(curr_idx + 1);
                    marked[curr_idx + 1] = 1;
                }

                if (value_to_idx.find(arr[curr_idx]) != value_to_idx.end()) {
                    for (auto j = value_to_idx[arr[curr_idx]].begin(); j != value_to_idx[arr[curr_idx]].end(); ++j) {
                        if (marked[*j] == 0) {
                            if (*j == 0) { found = 1; break; }

                            search_pool_1.insert(*j);
                            marked[*j] = 1;
                        }
                    }

                    if (found == 1) { break; }

                    value_to_idx.erase(value_to_idx.find(arr[curr_idx]));
                }

                ++i;
                search_pool_2.erase(erase_this);
                erase_this = i;
            }

            from_1_to_2 = 1;
        }

        counter++;
    }

    return counter;
}



// start from the last index, gradually widen search window, till found 0 index
int minJumps_1_1(vector<int>& arr) {
    if (arr.size() == 1) { return 0; }
    int length = arr.size();

    unordered_multimap<int, int> value_to_idx;
    for (int i = 0; i < length; i++) { value_to_idx.insert({arr[i], i}); }

    //if (value_to_idx.size() == length) { return length - 1; }
    if (arr[0] == arr[length - 1]) { return 1; }

    unordered_set<int> search_pool_1;
    unordered_set<int> search_pool_2;
    bool marked[length]; for (int i = 0; i < length; i++) { marked[i] = 0; }

    search_pool_1.insert(length - 1);
    int found = 0, counter = 0, from_1_to_2 = 1, curr_idx;
    while (found == 0) {
        if (from_1_to_2 == 1) {
            //cout << "search_pool_1.size() = " << search_pool_1.size() << "\n";
            for (auto i = search_pool_1.begin(), erase_this = i; i != search_pool_1.end(); ) {
                curr_idx = *i;

                // do i need to add one to counter?
                if (curr_idx == 1) { found = 1; break; }

                if (marked[curr_idx - 1] == 0) {
                    search_pool_2.insert(curr_idx - 1);
                    //cout << "search_pool_2.insert(" << curr_idx - 1 << ")\n";
                    marked[curr_idx - 1] = 1;
                }

                if ((curr_idx + 1 < length) && (marked[curr_idx + 1] == 0)) {
                    search_pool_2.insert(curr_idx + 1);
                    marked[curr_idx + 1] = 1;
                }

                while (value_to_idx.find(arr[curr_idx]) != value_to_idx.end()) {
                    auto j = value_to_idx.find(arr[curr_idx]);

                    //cout << "j->second = " << j->second << "\n";

                    if (marked[j->second] == 0) {
                        if (j->second == 0) { found = 1; break; }

                        search_pool_2.insert(j->second);
                        marked[j->second] = 1;
                    }

                    value_to_idx.erase(j);
                }

                if (found == 1) { break; }

                ++i;
                search_pool_1.erase(erase_this);
                erase_this = i;
            }


            //cout << "search_pool_1.size() = " << search_pool_1.size() << "\n\n";
            from_1_to_2 = 0;
        }

        else {
            //cout << "search_pool_2.size() = " << search_pool_2.size() << "\n";
            for (auto i = search_pool_2.begin(), erase_this = i; i != search_pool_2.end(); ) {
                curr_idx = *i;

                // do i need to add one to counter?
                if (curr_idx == 1) { found = 1; break; }

                if (marked[curr_idx - 1] == 0) {
                    search_pool_1.insert(curr_idx - 1);
                    marked[curr_idx - 1] = 1;
                }

                if ((curr_idx + 1 < length) && (marked[curr_idx + 1] == 0)) {
                    search_pool_1.insert(curr_idx + 1);
                    marked[curr_idx + 1] = 1;
                }

                while (value_to_idx.find(arr[curr_idx]) != value_to_idx.end()) {
                    auto j = value_to_idx.find(arr[curr_idx]);

                    //cout << "j->second = " << j->second << "\n";

                    if (marked[j->second] == 0) {
                        if (j->second == 0) { found = 1; break; }

                        search_pool_1.insert(j->second);
                        marked[j->second] = 1;
                    }

                    value_to_idx.erase(j);
                }

                if (found == 1) { break; }

                ++i;
                search_pool_2.erase(erase_this);
                erase_this = i;
            }

            //cout << "search_pool_2.size() = " << search_pool_2.size() << "\n\n";

            from_1_to_2 = 1;
        }

        counter++;
    }

    return counter;
}



//
int minJumps_1_2(vector<int>& arr) {
    if (arr.size() == 1) { return 0; }
    int length = arr.size();

    unordered_multimap<int, int> value_to_idx;
    for (int i = 0; i < length; i++) { value_to_idx.insert({arr[i], i}); }

    if (arr[0] == arr[length - 1]) { return 1; }

    stack<int> search_pool_1;
    stack<int> search_pool_2;
    bool marked[length]; for (int i = 0; i < length; i++) { marked[i] = 0; }

    search_pool_1.push(length - 1);
    int found = 0, counter = 0, from_1_to_2 = 1, curr_idx;
    while (found == 0) {
        if (from_1_to_2 == 1) {
            while (!search_pool_1.empty()) {
                curr_idx = search_pool_1.top();

                if (curr_idx == 1) { found = 1; break; }

                if (marked[curr_idx - 1] == 0) {
                    search_pool_2.push(curr_idx - 1);
                    marked[curr_idx - 1] = 1;
                }

                if ((curr_idx + 1 < length) && (marked[curr_idx + 1] == 0)) {
                    search_pool_2.push(curr_idx + 1);
                    marked[curr_idx + 1] = 1;
                }

                while (value_to_idx.find(arr[curr_idx]) != value_to_idx.end()) {
                    auto j = value_to_idx.find(arr[curr_idx]);

                    if (marked[j->second] == 0) {
                        if (j->second == 0) { found = 1; break; }

                        search_pool_2.push(j->second);
                        marked[j->second] = 1;
                    }

                    value_to_idx.erase(j);
                }

                if (found == 1) { break; }

                search_pool_1.pop();
            }

            from_1_to_2 = 0;
        }

        else {
            while (!search_pool_2.empty()) {
                curr_idx = search_pool_2.top();

                if (curr_idx == 1) { found = 1; break; }

                if (marked[curr_idx - 1] == 0) {
                    search_pool_1.push(curr_idx - 1);
                    marked[curr_idx - 1] = 1;
                }

                if ((curr_idx + 1 < length) && (marked[curr_idx + 1] == 0)) {
                    search_pool_1.push(curr_idx + 1);
                    marked[curr_idx + 1] = 1;
                }

                while (value_to_idx.find(arr[curr_idx]) != value_to_idx.end()) {
                    auto j = value_to_idx.find(arr[curr_idx]);

                    if (marked[j->second] == 0) {
                        if (j->second == 0) { found = 1; break; }

                        search_pool_1.push(j->second);
                        marked[j->second] = 1;
                    }

                    value_to_idx.erase(j);
                }

                if (found == 1) { break; }

                search_pool_2.pop();
            }

            from_1_to_2 = 1;
        }

        counter++;
    }

    return counter;
}


//, auto &start_point_1, auto &end_point_1, auto &diff_1, auto &start_point_2, auto &end_point_2, auto &diff_2
int minJumps_1_3(vector<int>& arr) {
    if (arr.size() == 1) { return 0; } if (arr[0] == arr[arr.size() - 1]) { return 1; }
    int length = arr.size();

    unordered_multimap<int, int> value_to_idx;

    //start_point_1 = chrono::steady_clock::now();
    for (int i = 0; i < length; i++) { value_to_idx.insert({arr[i], i}); }
    //end_point_1 = chrono::steady_clock::now();
    //diff_1 += end_point_1 - start_point_1;

    deque<int> pool;
    bool marked[length]; for (int i = 0; i < length; i++) { marked[i] = 0; }

    pool.push_back(length - 1);
    int found = 0, counter = 0, curr_idx, count_this_round;

    //start_point_2 = chrono::steady_clock::now();
    while (found == 0) {
        count_this_round = pool.size();

        while (count_this_round > 0) {
            curr_idx = pool.front();

            if (curr_idx == 1) { found = 1; break; }

            if (marked[curr_idx - 1] == 0) {
                pool.push_back(curr_idx - 1);
                marked[curr_idx - 1] = 1;
            }

            if ((curr_idx + 1 < length) && (marked[curr_idx + 1] == 0)) {
                pool.push_back(curr_idx + 1);
                marked[curr_idx + 1] = 1;
            }

            while (value_to_idx.find(arr[curr_idx]) != value_to_idx.end()) {
                auto j = value_to_idx.find(arr[curr_idx]);

                if (marked[j->second] == 0) {
                    if (j->second == 0) { found = 1; break; }

                    pool.push_back(j->second);
                    marked[j->second] = 1;
                }

                value_to_idx.erase(j);
            }

            if (found == 1) { break; }

            pool.pop_front();

            count_this_round--;
        }

        counter++;
    }
    //end_point_2 = chrono::steady_clock::now();
    //diff_2 += end_point_2 - start_point_2;

    return counter;
}


void merge_sort (int a[], int index[], int length) {
    int b[length]; for (int i = 0; i < length; i++) { b[i] = a[i]; }
    int index_1[length]; for (int i = 0; i < length; i++) { index_1[i] = index[i]; }

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        b[k] = a[i];
                        index_1[k] = index[i];
                        i++;
                    }

                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) { break; }

                        else {
                            b[k] = a[i];
                            index_1[k] = index[i];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k] = a[j];
                        index_1[k] = index[j];
                        j++, j_step++;
                    }

                    else if (a[i] <= a[j]) {
                        b[k] = a[i];
                        index_1[k] = index[i];
                        i++, i_step++;
                    }

                    else if (a[i] > a[j]) {
                        b[k] = a[j];
                        index_1[k] = index[j];
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
                        index[k] = index_1[i];
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
                            index[k] = index_1[i];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k] = b[j];
                        index[k] = index_1[j];
                        j++, j_step++;
                    }

                    else if (b[i] <= b[j]) {
                        a[k] = b[i];
                        index[k] = index_1[i];
                        i++, i_step++;
                    }

                    else if (b[i] > b[j]) {
                        a[k] = b[j];
                        index[k] = index_1[j];
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
            a[i] = b[i];
            index[i] = index_1[i];
        }
    }
}

int minJumps_1_4(vector<int>& arr) {
    if (arr.size() == 1) { return 0; } if (arr[0] == arr[arr.size() - 1]) { return 1; }
    int length = arr.size();

    //  sorted_array, together with idx, function like a flattened multi_map
    int sorted_array[length]; for (int i = 0; i < length; i++) { sorted_array[i] = arr[i]; }
    int idx[length]; for (int i = 0; i < length; i++) { idx[i] = i; }
    merge_sort(sorted_array, idx, length);

    int count_diff_nums = 1;
    for (int i = 1; i < length; i++) { if (sorted_array[i] != sorted_array[i - 1]) { count_diff_nums++; } }
    if (count_diff_nums == length) { return length - 1; }

    unordered_map<int, int> value_to_idx;
    value_to_idx.insert({sorted_array[0], 0});
    for (int i = 1; i < length; i++) {
        if (sorted_array[i] != sorted_array[i - 1]) {
            value_to_idx.insert({sorted_array[i], i});
        }
    }

    deque<int> pool;
    bool marked[length]; for (int i = 0; i < length - 1; i++) { marked[i] = 0; }

    pool.push_back(length - 1);
    marked[length - 1] = 1;
    int found = 0, counter = 0, start_idx, curr_idx, count_this_round;

    while (found == 0) {
        count_this_round = pool.size();

        while (count_this_round > 0) {
            curr_idx = pool.front();

            if (curr_idx == 1) { found = 1; break; }

            if (marked[curr_idx - 1] == 0) {
                pool.push_back(curr_idx - 1);
                marked[curr_idx - 1] = 1;
            }

            if ((curr_idx + 1 < length) && (marked[curr_idx + 1] == 0)) {
                pool.push_back(curr_idx + 1);
                marked[curr_idx + 1] = 1;
            }

            auto erase_this = value_to_idx.find(arr[curr_idx]);
            if (erase_this != value_to_idx.end()) {
                start_idx = erase_this->second;

                for (int j = start_idx; (j < length) && (sorted_array[j] == sorted_array[start_idx]); j++) {
                    if (marked[idx[j]] == 0) {
                        if (idx[j] == 0) { found = 1; break; }

                        pool.push_back(idx[j]);
                        marked[idx[j]] = 1;
                    }
                }

                if (found == 1) { break; }

                value_to_idx.erase(erase_this);
            }

            pool.pop_front();

            count_this_round--;
        }

        counter++;
    }

    return counter;
}


int minJumps_1_4_1(vector<int>& arr) {
    if (arr.size() == 1) { return 0; } if (arr[0] == arr[arr.size() - 1]) { return 1; }
    int length = arr.size();

    //  sorted_array, together with idx, function like a flattened multi_map
    int sorted_array[length]; for (int i = 0; i < length; i++) { sorted_array[i] = arr[i]; }
    int idx[length]; for (int i = 0; i < length; i++) { idx[i] = i; }
    merge_sort(sorted_array, idx, length);

    int count_diff_nums = 1;
    for (int i = 1; i < length; i++) { if (sorted_array[i] != sorted_array[i - 1]) { count_diff_nums++; } }
    if (count_diff_nums == length) { return length - 1; }

    unordered_map<int, int> value_to_idx;
    value_to_idx.insert({sorted_array[0], 0});
    for (int i = 1; i < length; i++) { if (sorted_array[i] != sorted_array[i - 1]) { value_to_idx.insert({sorted_array[i], i}); } }

    deque<int> pool;
    pool.push_back(length - 1);

    bool marked[length]; for (int i = 0; i < length - 1; i++) { marked[i] = 0; }
    marked[length - 1] = 1;

    int found = 0, counter = 0, start_idx, curr_idx, count_this_round;
    while (found == 0) {
        count_this_round = pool.size();

        while (count_this_round > 0) {
            curr_idx = pool.front();

            if (curr_idx == 1) { found = 1; break; }

            if (marked[curr_idx - 1] == 0) {
                pool.push_back(curr_idx - 1);
                marked[curr_idx - 1] = 1;
            }

            if ((curr_idx + 1 < length) && (marked[curr_idx + 1] == 0)) {
                pool.push_back(curr_idx + 1);
                marked[curr_idx + 1] = 1;
            }

            auto erase_this = value_to_idx.find(arr[curr_idx]);
            if (erase_this != value_to_idx.end()) {
                start_idx = erase_this->second;

                for (int j = start_idx; (j < length) && (sorted_array[j] == sorted_array[start_idx]); j++) {
                    if (marked[idx[j]] == 0) {
                        if (idx[j] == 0) { found = 1; break; }

                        pool.push_back(idx[j]);
                        marked[idx[j]] = 1;
                    }
                }

                if (found == 1) { break; }

                value_to_idx.erase(erase_this);
            }

            pool.pop_front();

            count_this_round--;
        }

        counter++;
    }

    return counter;
}





int main(){
    srand(time(0));int length = 20000, lower_range = -4000, upper_range = 4000, display = 0, input = 1;
    vector<int> wtf;
    // = {3, 4, 6, 5};

    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;

for (int m = 1; m <= 100; m++) {if (m % 10 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){
        wtf.reserve(length);
        for(int i = 0; i < length; i++){
            wtf.push_back(rand()%(upper_range - lower_range + 1) + lower_range);
        }
        //k = rand()%(upper_range - lower_range + 1) + lower_range;
    }
    if (display == 1){
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    vector<int> wtf1(wtf); vector<int> wtf2(wtf); vector<int> wtf3(wtf);

    start_point_1 = chrono::steady_clock::now();
    int s = minJumps_1_2(wtf1);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;
    //cout << "s = " << s << "\n";

    start_point_2 = chrono::steady_clock::now();
    int ss = minJumps_1_3(wtf2);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;
    //cout << "ss = " << ss << "\n";

    start_point_3 = chrono::steady_clock::now();
    //int sss = minJumps_1_3(wtf3, start_point_1, end_point_1, diff_1, start_point_2, end_point_2, diff_2);
    int sss = minJumps_1_4_1(wtf3);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;

    if (ss != sss) {
        cout << "s = " << s << "\n";
        cout << "ss = " << ss << "\n";
        cout << "sss = " << sss << "\n";
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
        break;
    }

wtf.clear();}
cout << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << duration <double, milli> (diff_2).count() << " ms" << "\n";
cout << duration <double, milli> (diff_3).count() << " ms" << "\n";

    return 0;
}




