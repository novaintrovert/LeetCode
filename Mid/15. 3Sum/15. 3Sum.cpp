/*15. 3Sum
Medium

Given an array nums of n integers,
are there elements a, b, c in nums such that a + b + c = 0?
Find all unique triplets in the array which gives the sum of zero.

Notice that the solution set must not contain duplicate triplets.

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]

Input: nums = []
Output: []

Input: nums = [0]
Output: []

Constraints:
    0 <= nums.length <= 3000
    -105 <= nums[i] <= 105
*/

/*
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

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

using namespace std;
using namespace chrono;

vector<vector<int>> threeSum_brute(vector<int>& nums) {
    int length = nums.size(); vector<vector<int>> result; if (length < 3) { return result; }
    if (length == 3) {
        if (nums[0] + nums[1] + nums[2] == 0) { result.push_back(vector<int> {nums[0], nums[1], nums[2]}); }

        return result;
    }

    sort(nums.begin(), nums.end());
    if ((nums[0] > 0) || (nums[length - 1] < 0)) { return result; }

    unordered_map<int, unordered_set<int>> record;

    int second_must_be_no_less_than, second_must_be_no_larger_than, third, temp;
    for (int i = 0; (i < length) && (nums[i] <= 0); i++) {
        second_must_be_no_less_than = 0 - nums[i] - nums[length - 1];
        second_must_be_no_larger_than = 0 - nums[i];

        for (int j = i + 1; (j < length) && (nums[j] <= second_must_be_no_larger_than); j++) {
            if (nums[j] >= second_must_be_no_less_than) {
                third = 0 - nums[i] - nums[j];

                for (int k = j + 1; k < length; k++) {
                    if (nums[k] == third) {
                        auto find_it = record.find(nums[i]);

                        if (find_it == record.end()) {
                            result.push_back(vector<int> {nums[i], nums[j], third});
                            record.insert({nums[i], unordered_set<int> ()});
                            record[nums[i]].insert(nums[j]);
                        }

                        else {
                            auto find_it_2 = record[nums[i]].find(nums[j]);
                            if (find_it_2 == record[nums[i]].end()) {
                                result.push_back(vector<int> {nums[i], nums[j], third});
                                record[nums[i]].insert(nums[j]);
                            }
                        }
                    }

                    if (nums[k] > third) { break; }
                }
            }
        }
    }

    return result;
}

vector<vector<int>> threeSum_1_0(vector<int>& nums) {
    int length = nums.size();
    int test = 0;
    vector<vector<int>> result;
    if (length < 3) { return result; }
    if (length == 3) {
        if (nums[0] + nums[1] + nums[2] == 0) { result.push_back(vector<int> {nums[0], nums[1], nums[2]}); }

        return result;
    }

    sort(nums.begin(), nums.end());
    if ((nums[0] > 0) || (nums[length - 1] < 0)) { return result; }

    if (test > 0) {
        cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << nums[i] << ", ";
        }
        cout << "\n";
    }

    int range_length = nums[length - 1] - nums[0] + 1;

    int num_counter[range_length]; for (int i = 0; i < range_length; i++) { num_counter[i] = 0; }
    for (int i = 0; i < length; i++) { num_counter[nums[i] - nums[0]]++; }

    if (test > 0) {
        cout << "\n";
        for (int i = 0; i < range_length; i++) {
            cout << num_counter[i] << ", ";
        }
        cout << "\n";
    }

    unordered_map<int, unordered_set<int>> record;

    if (test > 0) { cout << "\n"; }

    int second_must_be_no_less_than, second_must_be_no_larger_than, third, temp;
    for (int i = 0; (i < length - 2) && (nums[i] <= 0); i++) {
        second_must_be_no_less_than = 0 - nums[i] - nums[length - 1];
        second_must_be_no_larger_than = 0 - nums[i];

        if (test > 0) {
            cout << nums[i] << "~\n";
            cout << "second_must_be_no_less_than = " << second_must_be_no_less_than << "\n";
            cout << "second_must_be_no_larger_than = " << second_must_be_no_larger_than << "\n";
        }

        for (int j = i + 1; (j < length - 1) && (nums[j] <= second_must_be_no_larger_than); j++) {
            if (test > 0) { cout << "\n\t" << nums[j] << "~\n"; }

            if (nums[j] >= second_must_be_no_less_than) {
                third = 0 - nums[i] - nums[j];
                temp = third - nums[0];

                if (num_counter[temp] > 0) {
                    if ((third > nums[j])
                        || ((third == nums[j]) &&
                            (((num_counter[temp] > 1) && (nums[i] < nums[j]))
                           ||((num_counter[temp] > 2) && (nums[i] == nums[j]))))) {
                        auto find_it = record.find(nums[i]);

                        if (find_it == record.end()) {
                            result.push_back(vector<int> {nums[i], nums[j], third});

                            if (test > 0) { cout << "\npush_back " << nums[i] << ", " << nums[j] << ", " << third << "\n"; }

                            record.insert({nums[i], unordered_set<int> ()});
                            record[nums[i]].insert(nums[j]);
                        }

                        else {
                            auto find_it_2 = record[nums[i]].find(nums[j]);
                            if (find_it_2 == record[nums[i]].end()) {
                                result.push_back(vector<int> {nums[i], nums[j], third});

                                if (test > 0) { cout << "\npush_back " << nums[i] << ", " << nums[j] << ", " << third << "\n"; }

                                record[nums[i]].insert(nums[j]);
                            }
                        }
                    }
                }
            }
        }

        if (test > 0) {
            cout << "\ndisplay record:\n";
            for (auto p = record.begin(); p != record.end(); ++p) {
                cout << p->first << " - ";
                for (auto q = p->second.begin(); q != p->second.end(); ++q) {
                    cout << *q << ", ";
                }
                cout << "\n";
            }
        }
    }


    if (test > 0) { cout << "\nresult.size() = " << result.size() << "\n"; }
    return result;
}


void merge_sort (vector<int> &blah) {//20200823, somewhat a bit better
    const int length = blah.size();
    vector<int> auxiliary(blah);
    int from_blah_to_auxiliary = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < length) {
        if (from_blah_to_auxiliary == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        auxiliary[k] = blah[i];
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
                            auxiliary[k] = blah[i];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        auxiliary[k] = blah[j];
                        j++, j_step++;
                    }

                    else if (blah[i] <= blah[j]) {
                        auxiliary[k] = blah[i];
                        i++, i_step++;
                    }

                    else if (blah[i] > blah[j]) {
                        auxiliary[k] = blah[j];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_blah_to_auxiliary = 0;
        }

        else if (from_blah_to_auxiliary == 0) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        blah[k] = auxiliary[i];
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
                            blah[k] = auxiliary[i];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        blah[k] = auxiliary[j];
                        j++, j_step++;
                    }

                    else if (auxiliary[i] <= auxiliary[j]) {
                        blah[k] = auxiliary[i];
                        i++, i_step++;
                    }

                    else if (auxiliary[i] > auxiliary[j]) {
                        blah[k] = auxiliary[j];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_blah_to_auxiliary = 1;
        }
    }

    if (from_blah_to_auxiliary == 0) {
        for (int i = 0; i < length; i++) {
            blah[i] = auxiliary[i];
        }
    }
}


// CURRENT BEST
vector<vector<int>> threeSum_1_1(vector<int>& nums) {// version 1.1
    int length = nums.size();
    vector<vector<int>> result;
    if (length < 3) { return result; }
    if (length == 3) {
        if (nums[0] + nums[1] + nums[2] == 0) { result.push_back(vector<int> {nums[0], nums[1], nums[2]}); }

        return result;
    }

    sort(nums.begin(), nums.end());
    if ((nums[0] > 0) || (nums[length - 1] < 0)) { return result; }

    int range_length = nums[length - 1] - nums[0] + 1;
    int num_counter[range_length]; for (int i = 0; i < range_length; i++) { num_counter[i] = 0; }
    for (int i = 0; i < length; i++) { num_counter[nums[i] - nums[0]]++; }

    int last_left_value = -2147483648, last_right_value = 2147483647;
    int temp_val, temp_idx;

    for (int i = 0; (i < length - 2) && (nums[i] < 0); i++) {
        if (nums[i] != last_left_value) {

            for (int j = length - 1; (j > 0) && (nums[j] > 0); j--) {
                if (nums[j] != last_right_value) {

                    temp_val = 0 - nums[i] - nums[j];
                    temp_idx = temp_val - nums[0];

                    if ((temp_idx >= 0) && (temp_idx < range_length) && (num_counter[temp_idx] > 0)) {
                        if (((temp_val < nums[j]) && ((temp_val > nums[i]) || ((temp_val == nums[i]) && (num_counter[temp_idx] > 1))))
                            || ((temp_val == nums[j]) && (num_counter[temp_idx] > 1))) {

                            result.push_back({nums[i], temp_val, nums[j]});
                        }
                    }

                    if (temp_val > nums[j]) { break; }

                    last_right_value = nums[j];
                }
            }

            last_left_value = nums[i];
            last_right_value = 2147483647;
        }
    }

    if (num_counter[0 - nums[0]] > 2) { result.push_back({0, 0, 0}); }

    return result;
}



int main() {
    srand(time(0));int length = 20, lower_range = -200, upper_range = 200, display = 0, input = 1;
    vector<int> wtf;
    // = {-1,0,1,2,-1,-4,-2,-3,3,0,4};

    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;

for (int m = 1; m <= 1000000; m++) {if (m % 100000 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){
        wtf.reserve(length);
        for(int i = 0; i < length; i++){ wtf.push_back(rand()%(upper_range - lower_range + 1) + lower_range); }
    }
    if (display == 1){
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    vector<int> wtf1(wtf);vector<int> wtf2(wtf);

    start_point_1 = chrono::steady_clock::now();
    vector<vector<int>> s = threeSum_1_0 (wtf1);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    start_point_2 = chrono::steady_clock::now();
    vector<vector<int>> ss = threeSum_1_1 (wtf2);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;


    if (s.size() != ss.size()) {
        cout << "size error\n";
        cout << "m = " << m << "\n\n";
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";

        cout << "\ns:\n";
        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j < s[i].size(); j++) {
                cout << s[i][j] << ", ";
            }cout << "\n";
        }cout << "\n";

        cout << "\nss:\n";
        for (int i = 0; i < ss.size(); i++) {
            for (int j = 0; j < ss[i].size(); j++) {
                cout << ss[i][j] << ", ";
            }cout << "\n";
        }cout << "\n";

        break;

        break;
    }
    else {
        int all_good = 1;

        for (int i = 0; (i < s.size()) && (all_good == 1); i++) {
            if (s[i].size() != ss[i].size()) { cout << "fucking size error\n"; all_good = 0; break; }

            else {
                for (int j = 0; j < s[i].size(); j++) {
                    if (s[i][j] != ss[i][j]) {
                        all_good = 0;
                        break;
                    }
                }
            }
        }

        if (all_good == 0) {
            cout << " = {";
            for (int i = 0; i < wtf.size(); i++) {
                cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
            }
            cout << "}\n";

            cout << "\ns:\n";
            for (int i = 0; i < s.size(); i++) {
                for (int j = 0; j < s[i].size(); j++) {
                    cout << s[i][j] << ", ";
                }cout << "\n";
            }cout << "\n";

            cout << "\nss:\n";
            for (int i = 0; i < ss.size(); i++) {
                for (int j = 0; j < ss[i].size(); j++) {
                    cout << ss[i][j] << ", ";
                }cout << "\n";
            }cout << "\n";

            break;
        }
    }

wtf.clear();}

cout << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << duration <double, milli> (diff_2).count() << " ms" << "\n";

    return 0;
}




