/*398. Random Pick Index
Medium

Given an integer array nums with possible duplicates,
randomly output the index of a given target number.
You can assume that the given target number must exist in the array.

Implement the Solution class:
    Solution(int[] nums) Initializes the object with the array nums.
    int pick(int target) Picks a random index i from nums where nums[i] == target.
    If there are multiple valid i's, then each index should have an equal probability of returning.


Input
["Solution", "pick", "pick", "pick"]
[[[1, 2, 3, 3, 3]], [3], [1], [3]]
Output
[null, 4, 0, 2]

Explanation
Solution solution = new Solution([1, 2, 3, 3, 3]);
solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(1); // It should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.

Constraints:
    1 <= nums.length <= 2 * 104
    -231 <= nums[i] <= 231 - 1
    target is an integer from nums.
    At most 104 calls will be made to pick.
*/

/*
class Solution {
public:
    Solution(vector<int>& nums) {

    }

    int pick(int target) {

    }
};
*/

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
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

// others SUCKS
class Solution_others {
    vector<int> a;
public:
    Solution_others(vector<int>& nums): a(nums) {

    }

    int pick(int target) {
        int count=0, val=0;

        for(int i=0; i<a.size(); ++i){
            if(a[i] == target){
                count++;
                if(rand()%count == 0)
                    val = i;
            }
        }
        return val;
    }
};


class Solution_1 {
public:
    unordered_map<int, vector<int>> value_to_idx;
    int bucket_size, return_this_idx;

    Solution_1(vector<int>& nums) {
        srand(time(0));
        for (int i = 0; i < nums.size(); i++) {
            auto find_value = value_to_idx.find(nums[i]);

            if (find_value == value_to_idx.end()) {
                value_to_idx.insert({nums[i], vector<int>()});
            }

            value_to_idx[nums[i]].push_back(i);
        }
    }

    int pick(int target) {
        bucket_size = value_to_idx[target].size();
        return_this_idx = rand() % bucket_size;
        return value_to_idx[target][return_this_idx];
    }
};

class Solution {
public:
    vector<pair<int, int>> value_and_idx;
    int bucket_size, return_this_idx, left, right;

    unordered_map<int, pair<int, int>> value_to_idx_range;

    Solution(vector<int>& nums) {
        value_and_idx.reserve(nums.size());
        for (int i = 0; i < nums.size(); i++) { value_and_idx.push_back({nums[i], i}); }

        sort(value_and_idx.begin(), value_and_idx.end(),
             [](const auto &a, const auto &b) {
                return a.first < b.first;
             });

        left = 0, right = left;
        while (left < value_and_idx.size()) {
            while (right < value_and_idx.size() && value_and_idx[right].first == value_and_idx[left].first) { right++; }

            value_to_idx_range.insert({value_and_idx[left].first, {left, right - 1}});

            left = right;
        }

        /*cout << "value_and_idx:\n";
        for (int i = 0; i < value_and_idx.size(); i++) {
            cout << value_and_idx[i].first << " " << value_and_idx[i].second << ", ";
        }
        cout << "\n\n";

        for (auto i = value_to_idx_range.begin(); i != value_to_idx_range.end(); i++) {
            cout << i->first << ": " << i->second.first << ", " << i->second.second << "\n";
        }
        cout << "\n\n";*/
    }

    int pick(int target) {
        left = value_to_idx_range[target].first;
        right = value_to_idx_range[target].second;
        bucket_size = right - left;

        if (bucket_size > 0) { return_this_idx = rand() % (bucket_size + 1); }

        else { return_this_idx = 0; }

        return value_and_idx[left + return_this_idx].second;
    }
};


/*  std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);*/

//  I WILL MOST LIKELY TO RUN INTO ALL KINDS OF PROBLEMS IF I DO NOT BUILD A BRUTEFORCE & TEST A BIT
//  NO MATTER HOW CONFIDENT I MIGHT HAVE ON THAT ALGORITHM
int main(){
    srand(time(0));int length = 10000, lower_range = -100000000, upper_range = 100000000, display = 0, input = 1;
    vector<int> wtf;
    vector<int> pool;
    unordered_set<int> record;

    auto sp1 = chrono::steady_clock::now(); auto ep1 = chrono::steady_clock::now(); auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now(); auto ep2 = chrono::steady_clock::now(); auto dif2 = ep2 - sp2;
    auto sp3 = chrono::steady_clock::now(); auto ep3 = chrono::steady_clock::now(); auto dif3 = ep3 - sp3;
    int temp, pool_size, target;

    if (input == 1) {
        wtf.reserve(length);

        for (int i = 0; i < length; i++) {
            temp = rand() % (upper_range - lower_range + 1) + lower_range;
            wtf.push_back(temp);
            auto find_it = record.find(temp);
            if (find_it == record.end()) { record.insert(temp);}
        }

        for (auto i = record.begin(); i != record.end(); ++i) { pool.push_back(*i); }

        pool_size = pool.size();
    }
    if (display == 1) {
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    vector<int> wtf1(wtf); vector<int> wtf2(wtf); vector<int> wtf3(wtf); vector<int> wtf4(wtf);

    sp1 = chrono::steady_clock::now();
    Solution_others* obj0 = new Solution_others(wtf);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;

    sp2 = chrono::steady_clock::now();
    Solution_1* obj1 = new Solution_1(wtf);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;

    sp3 = chrono::steady_clock::now();
    Solution* obj2 = new Solution(wtf);
    ep3 = chrono::steady_clock::now();
    dif3 += ep3 - sp3;
    /*int counter[7]; for (int i = 0; i < 7; i++) { counter[i] = 0; }
    int param_1;

    for (int i = 0; i < 5000; i++) {
        param_1 = obj->pick(3);
        counter[param_1]++;
    }

    cout << "display:\n";
    for (int i = 0; i < 7; i++) {
        cout << i << ": " << counter[i] << "\n";
    }
    cout << "\n\n";*/

for (int m = 1; m <= 10000; m++) {if (m % 10000 == 0) {cout << "m = " << m << "\n";}
    temp = rand() % pool_size;
    target = pool[temp];

    sp1 = chrono::steady_clock::now();
    int s = obj0->pick(target);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;

    sp2 = chrono::steady_clock::now();
    int ss = obj1->pick(target);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;

    sp3 = chrono::steady_clock::now();
    int sss = obj2->pick(target);;
    ep3 = chrono::steady_clock::now();
    dif3 += ep3 - sp3;
}

    delete obj0; delete obj1; delete obj2;

cout << duration <double, milli> (dif1).count() << " ms" << "\n";
cout << duration <double, milli> (dif2).count() << " ms" << "\n";
cout << duration <double, milli> (dif3).count() << " ms" << "\n";

    return 0;
}


    /*sort(begin(a),
         end(a),
         [](const auto &m, const auto &n){
            return m[1] < n[1];
            }
        );*/


