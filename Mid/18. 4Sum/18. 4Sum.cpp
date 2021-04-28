/*18. 4Sum
Medium

Given an array nums of n integers and an integer target,
are there elements a, b, c, and d in nums such that a + b + c + d = target?
Find all unique quadruplets in the array which gives the sum of target.

Notice that the solution set must not contain duplicate quadruplets.

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Input: nums = [], target = 0
Output: []

Constraints:
    0 <= nums.length <= 200
    -109 <= nums[i] <= 109
    -109 <= target <= 109
*/

/*
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

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
#include <cassert>

using namespace std;
using namespace chrono;

vector<vector<int>> fourSum_brute(vector<int>& nums, int target) {
    int length = nums.size();vector<vector<int>> result;int test = 0;
    if (length < 4) { return result; }
    if (length == 4) {
        if (nums[0] + nums[1] + nums[2] + nums[3] == target) {
            result.push_back(vector<int> {nums[0], nums[1], nums[2], nums[3]});
        }

        return result;
    }

    nums.push_back(-2147483648);//NOTE THIS!!!
    nums.push_back(2147483647);//NOTE THIS!!!

    sort(nums.begin(), nums.end());
    if (test > 0) { for (int i = 0; i <= length + 1; i++) { cout << nums[i] << ", "; } cout << "\n\n"; }

    long long int sum;

    int left = nums[0], right = nums[length + 1], second_must_not_be_equals_to, third_must_not_be_equals_to;
    for (int i = 1; i < length - 2; i++) { // first
        if (test > 0) { cout << "\nnums[i] = " << nums[i] << "\n"; }
        if (nums[i] != nums[i - 1]) {
            for (int j = length; j > i + 2; j--) { // last
                if (test > 0) { cout << "\n\tnums[j] = " << nums[j] << "\n"; }
                if (nums[j] != nums[j + 1]) {

                    second_must_not_be_equals_to = -2147483648;
                    for (int k = i + 1; k < j - 1; k++) { // second
                        if (test > 0) { cout << "\n\t\tnums[k] = " << nums[k] << "\n"; }
                        if (nums[k] != second_must_not_be_equals_to) {

                            third_must_not_be_equals_to = -2147483648;
                            for (int m = k + 1; m < j; m++) { // third
                                if (test > 0) { cout << "\n\t\t\tnums[m] = " << nums[m] << "\n"; }
                                if (nums[m] != third_must_not_be_equals_to) {
                                    sum = nums[i], sum += nums[j], sum += nums[k], sum += nums[m];

                                    if (sum == target) {
                                        result.push_back(vector<int> {nums[i], nums[k], nums[m], nums[j]});
                                        if (test > 0) { cout << "\t\t\tpush_back\n"; }
                                    }

                                    if (sum > target) { break; }
                                }

                                third_must_not_be_equals_to = nums[m];
                            }

                            second_must_not_be_equals_to = nums[k];
                        }
                    }
                }
            }
        }
    }

    return result;
}



vector<vector<int>> fourSum_1(vector<int>& nums, int target) {//version 1.0
    int length = nums.size();
    int test = 0;
    vector<vector<int>> result;
    if (length < 4) { return result; }
    if (length == 4) {
        if (nums[0] + nums[1] + nums[2] + nums[3] == target) {
            result.push_back(vector<int> {nums[0], nums[1], nums[2], nums[3]});
        }

        return result;
    }

    nums.push_back(-2147483648);//NOTE THIS!!!
    nums.push_back(2147483647);//NOTE THIS!!!

    sort(nums.begin(), nums.end());

    if (test > 0) { for (int i = 0; i <= length + 1; i++) { cout << nums[i] << ", "; } cout << "\n\n"; }

    long long int long_temp;
    long_temp = nums[1], long_temp += nums[2], long_temp += nums[3], long_temp += nums[4];
    if (target < long_temp) { return result; }
    long_temp = nums[length - 3], long_temp += nums[length - 2], long_temp += nums[length - 1], long_temp += nums[length];
    if (target > long_temp) { return result; }

    long_temp = target, long_temp -= nums[length - 2], long_temp -= nums[length - 1], long_temp -= nums[length];
    int start_idx = 1;
    for (; start_idx < length - 2; start_idx++) {
        if (nums[start_idx] >= long_temp) { break; }
    }

    if (test > 0) { cout << "start_idx = " << start_idx << "\n"; }

    long long int curr_smallest_4_sum = nums[start_idx - 1];
    curr_smallest_4_sum += nums[start_idx], curr_smallest_4_sum += nums[start_idx + 1], curr_smallest_4_sum += nums[start_idx + 2];
    long long int curr_largest_4_sum, search_val;
    int left, mid, right, second_must_not_be;

    //if we keep NOT processing identical nums[i], then the rest is just dff 3sum problems with various boundary conditions
    for (int i = start_idx; i < length - 2; i++) { // 1st num, leftmost

        //no point in further exploring if current smallest sum is larger than target
        curr_smallest_4_sum -= nums[i - 1], curr_smallest_4_sum += nums[i + 3];
        if (test > 0) { cout << nums[i] << "\ncurr_smallest_4_sum = " << curr_smallest_4_sum << "\n"; }
        if (curr_smallest_4_sum > target) { break; }

        if (nums[i] != nums[i - 1]) { // nums.push_back(-2147483648) make this part easier
            curr_largest_4_sum = nums[i], curr_largest_4_sum += nums[length - 1];
            curr_largest_4_sum += nums[length], curr_largest_4_sum += nums[length + 1];

            for (int j = length; j > i + 2; j--) { // 4th num, rightmost
                //no point in further exploring if, with GIVEN nums[i], current largest is smaller than target
                curr_largest_4_sum -= nums[j + 1], curr_largest_4_sum += nums[j - 2];
                if (test > 0) { cout << "\t" << nums[j] << "\n\tcurr_largest_4_sum = " << curr_largest_4_sum << "\n"; }
                if (curr_largest_4_sum < target) { break; }

                if (nums[j] != nums[j + 1]) { // nums.push_back(2147483647) make this part easier
                    //find 2 values within nums[i] & nums[j], that sums to target - nums[i] - nums[j]
                    long_temp = target;
                    long_temp -= nums[i], long_temp -= nums[j];
                    if (test > 0) { cout << "\n\t\tlong_temp = " << long_temp << "\n"; }

                    second_must_not_be = -2147483648;
                    for (int k = i + 1; k < j - 1; k++) { // 2nd num
                        if (test > 0) { cout << "\n\t\t" << nums[k] << "\n"; }

                        if (nums[k] != second_must_not_be) {
                            if (nums[k] + nums[k + 1] > long_temp) { break; }
                            if (nums[k] + nums[j - 1] < long_temp) { continue; }

                            search_val = long_temp, search_val -= nums[k];

                            if (test > 0) { cout << "\t\tsearch_val = " << search_val << "\n"; }

                            left = k + 1, right = j - 1;
                            if (nums[left] < search_val) {
                                while (left < right) {
                                    mid = left + (right - left) / 2;

                                    if (nums[mid] < search_val) {left = mid + 1;}

                                    else {right = mid;}
                                }
                            }
//-13, -8, 10, 11,
                            if (test > 0) { cout << "\t\t\tnums[left] = " << nums[left] << "\n"; }

                            if (nums[left] == search_val) {
                                result.push_back (vector<int> {nums[i], nums[k], nums[left], nums[j]});

                                if (test > 0) { cout << "\t\t\tpush_back\n"; }
                            }

                            second_must_not_be = nums[k];
                        }
                    }

                    if (test > 0) { cout << "\n"; }
                }
            }

            if (test > 0) { cout << "\n"; }
        }
    }

    return result;
}

vector<vector<int>> fourSum_1_0_1(vector<int>& nums, int target) {//version 1.0.1
    int length = nums.size();
    vector<vector<int>> result;
    if (length < 4) { return result; }
    if (length == 4) {
        if (nums[0] + nums[1] + nums[2] + nums[3] == target) {
            result.push_back(vector<int> {nums[0], nums[1], nums[2], nums[3]});
        }

        return result;
    }

    nums.push_back(-2147483648);//NOTE THIS!!!
    nums.push_back(2147483647);//NOTE THIS!!!

    sort(nums.begin(), nums.end());

    long long int long_temp;
    long_temp = nums[1], long_temp += nums[2], long_temp += nums[3], long_temp += nums[4];
    if (target < long_temp) { return result; }
    long_temp = nums[length - 3], long_temp += nums[length - 2], long_temp += nums[length - 1], long_temp += nums[length];
    if (target > long_temp) { return result; }

    long_temp = target, long_temp -= nums[length - 2], long_temp -= nums[length - 1], long_temp -= nums[length];
    int start_idx = 1;
    for (; start_idx < length - 2; start_idx++) {
        if (nums[start_idx] >= long_temp) { break; }
    }

    long long int curr_smallest_4_sum = nums[start_idx - 1];
    curr_smallest_4_sum += nums[start_idx], curr_smallest_4_sum += nums[start_idx + 1], curr_smallest_4_sum += nums[start_idx + 2];
    long long int curr_largest_4_sum, search_val;
    int left, mid, right, second_must_not_be;

    //if we keep NOT processing identical nums[i], then the rest is just dff 3sum problems with various boundary conditions
    for (int i = start_idx; i < length - 2; i++) { // 1st num, leftmost

        //no point in further exploring if current smallest sum is larger than target
        curr_smallest_4_sum -= nums[i - 1], curr_smallest_4_sum += nums[i + 3];
        if (curr_smallest_4_sum > target) { break; }

        if (nums[i] != nums[i - 1]) { // nums.push_back(-2147483648) make this part easier
            curr_largest_4_sum = nums[i], curr_largest_4_sum += nums[length - 1];
            curr_largest_4_sum += nums[length], curr_largest_4_sum += nums[length + 1];

            for (int j = length; j > i + 2; j--) { // 4th num, rightmost

                //no point in further exploring if, with GIVEN nums[i], current largest is smaller than target
                curr_largest_4_sum -= nums[j + 1], curr_largest_4_sum += nums[j - 2];
                if (curr_largest_4_sum < target) { break; }

                if (nums[j] != nums[j + 1]) { // nums.push_back(2147483647) make this part easier
                    //find 2 values within nums[i] & nums[j], that sums to target - nums[i] - nums[j]
                    long_temp = target;
                    long_temp -= nums[i], long_temp -= nums[j];

                    second_must_not_be = -2147483648;
                    for (int k = i + 1; k < j - 1; k++) { // 2nd num

                        if (nums[k] != second_must_not_be) {
                            if (nums[k] + nums[k + 1] > long_temp) { break; }
                            if (nums[k] + nums[j - 1] < long_temp) { continue; }

                            search_val = long_temp, search_val -= nums[k];

                            left = k + 1, right = j - 1;
                            if (nums[left] < search_val) {
                                while (left < right) {
                                    mid = left + (right - left) / 2;

                                    if (nums[mid] < search_val) {left = mid + 1;}

                                    else {right = mid;}
                                }
                            }

                            if (nums[left] == search_val) {
                                result.push_back (vector<int> {nums[i], nums[k], nums[left], nums[j]});
                            }

                            second_must_not_be = nums[k];
                        }
                    }
                }
            }
        }
    }

    return result;
}


//OTHERS 1
vector<vector<int>> twoSum(vector<int>& nums, int target, int start){
    /*cout<<"twoSum, target="<<target<<", start="<<start<<endl;
    cout<<" nums=";
    for(int v : nums)
        cout<<v<<" ";
    cout<<endl;*/

    vector<vector<int>> res;
    int lo = start, hi = nums.size() - 1;
    while(lo < hi){
        if ((lo != start && nums[lo - 1]==nums[lo]) || (target > nums[lo] + nums[hi])) { lo++; }

        else if ((hi != int(nums.size()) - 1 && nums[hi] == nums[hi + 1]) || (target < nums[lo] + nums[hi])) { hi--; }

        else if(target == nums[lo]+nums[hi]) {
            //cout<<"twoSum, adding nums[lo]="<<nums[lo]<<", nums[hi]="<<nums[hi]<<endl;
            res.push_back({nums[lo++], nums[hi--]});
        }

        else assert(0);
    }
    return res;
}

vector<vector<int>> kSum (vector<int>& nums, int target, int start, int k) {
    //cout<<"kSum, k="<<k<<endl;
    vector<vector<int>> res;
    if ((start == int(nums.size())) || (nums[start] * k > target) || (nums[nums.size() - 1] * k < target)) { return res; }

    if (k == 2) { return twoSum(nums, target, start); }

    assert(k > 2);
    for(int i = start; i < int(nums.size()); i++){
        if (i == start || nums[i - 1] != nums[i]) {
            for (auto& set : kSum(nums, target - nums[i], i + 1, k - 1)) {
                res.push_back({nums[i]});
                res.back().insert(end(res.back()), begin(set), end(set));
            }
        }
    }
    return res;
}

vector<vector<int>> fourSum_others_1 (vector<int>& nums, int target) {
    sort(begin(nums), end(nums));
    return kSum(nums, target, 0, 4);
}
//OTHERS 1 END



int main() {
    int temp0, temp1;
    srand(time(0));int target = 0, length = 1000, lower_range = -1000000000, upper_range = 1000000000, input = 1;
    vector<int> wtf;
    // = {-1,0,1,2,-1,-4,-2,-3,3,0,4};

    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;


for (int m = 1; m <= 10000; m++) {if (m % 100 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){
        wtf.reserve(length);
        for(int i = 0; i < length; i++){ wtf.push_back(rand()%(upper_range - lower_range + 1) + lower_range); }
        target = rand()%(upper_range - lower_range + 1) + lower_range;
    }
    if (input == 2){
        wtf.reserve(length);
        for(int i = 0; i < length; i++){
            temp0 = rand() % 3;
            if (temp0 == 2) {wtf.push_back(1000000000);}
            else if (temp0 == 1) {wtf.push_back(0);}
            else {wtf.push_back(-1000000000);}
        }
        temp1 = rand() % 3;
        if (temp1 == 2) {target = 1000000000;}
        else if (temp1 == 1) {target = 0;}
        else {target = -1000000000;}
    }

    vector<int> wtf1(wtf);vector<int> wtf2(wtf);vector<int> wtf3(wtf);

    start_point_1 = chrono::steady_clock::now();
    vector<vector<int>> s = fourSum_1 (wtf1, target);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    start_point_2 = chrono::steady_clock::now();
    vector<vector<int>> ss = fourSum_1_0_1 (wtf2, target);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    start_point_3 = chrono::steady_clock::now();
    vector<vector<int>> sss = fourSum_others_1 (wtf3, target);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;

    //cout << "s.size() = " << s.size() << "\n";
/*
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
            cout << "m = " << m << "\n";
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
*/
wtf.clear();}

cout << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << duration <double, milli> (diff_2).count() << " ms" << "\n";
cout << duration <double, milli> (diff_3).count() << " ms" << "\n";

    return 0;
}




