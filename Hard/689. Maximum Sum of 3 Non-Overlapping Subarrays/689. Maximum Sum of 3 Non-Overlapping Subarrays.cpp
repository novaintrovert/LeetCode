/*689. Maximum Sum of 3 Non-Overlapping Subarrays
Hard

In a given array nums of positive integers,
find three non-overlapping subarrays with maximum sum.

Each subarray will be of size k,
and we want to maximize the sum of all 3*k entries.

Return the result as a list of indices representing the starting position of each interval (0-indexed).
If there are multiple answers, return the lexicographically smallest one.

Input: [1,2,1,2,6,7,5,1], 2
Output: [0, 3, 5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

Note:
    nums.length will be between 1 and 20000.
    nums[i] will be between 1 and 65535.
    k will be between 1 and floor(nums.length / 3).
*/

/*
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {

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


//"return the lexicographically smallest one"
void merge_sort (vector<vector<int>> &a) {//20200823, somewhat a bit better
    const int length = a.size();
    vector<vector<int>> b(a);
    int from_a_to_b = 1, double_this_long_after_merge = 1;
    while (double_this_long_after_merge < length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        b[k] = a[i];
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
                            i++, i_step++;
                        }
                    }
                    else if (i_step == double_this_long_after_merge) {
                        b[k] = a[j];
                        j++, j_step++;
                    }
                    else if (a[i][0] < a[j][0]) {
                        b[k] = a[i];
                        i++, i_step++;
                    }
                    else if (a[i][0] >= a[j][0]) {
                        b[k] = a[j];
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
                            i++, i_step++;
                        }
                    }
                    else if (i_step == double_this_long_after_merge) {
                        a[k] = b[j];
                        j++, j_step++;
                    }
                    else if (b[i][0] < b[j][0]) {
                        a[k] = b[i];
                        i++, i_step++;
                    }
                    else if (b[i][0] >= b[j][0]) {
                        a[k] = b[j];
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
        }
    }
}

vector<int> maxSumOfThreeSubarrays_brute(vector<int>& nums, int k) {
    int length = nums.size();
    vector<vector<int>> k_sum(length - k + 1, vector<int> (2, 0));

    int test_timer = -1;
    int sum = 0;for (int i = 0; i < k; i++) {sum += nums[i];}

    k_sum[0][0] = sum, k_sum[0][1] = 0;
    for (int i = 1; i < length - k + 1; i++) {
        sum -= nums[i - 1];
        sum += nums[i + k - 1];
        k_sum[i][0] = sum;
        k_sum[i][1] = i;
    }

    merge_sort (k_sum);

    if (test_timer >= 0) {for (int i = 0; i < k_sum.size(); i++) {cout << k_sum[i][0] << " " << k_sum[i][1] << "\n";}}

    int max_sum = 0, idx1, idx2, idx3;
    int first_must_be_larger_than_this = -1;


    for (int i = length - k + 1 - 1, curr_sum; i > 1; i--) {
        if (test_timer >= 0) {cout << "i = " << i << "\n";}

        if (k_sum[i][0] <= first_must_be_larger_than_this) {break;}

        else {
            for (int j = i - 1, time_to_exit = 0; j > 0; j--) {
                if (abs(k_sum[j][1] - k_sum[i][1]) < k) {continue;}

                if (test_timer >= 0) {cout << "\tj = " << j << "\n";}
                for (int m = j - 1; m >= 0; m--) {
                    if ((abs(k_sum[m][1] - k_sum[j][1]) < k)||(abs(k_sum[m][1] - k_sum[i][1]) < k)) {continue;}
                    else {
                        if (test_timer >= 0) {cout << "\t\tm = " << m << "\n";}
                        curr_sum = k_sum[i][0] + k_sum[j][0] + k_sum[m][0];
                        if (curr_sum > max_sum) {
                            max_sum = curr_sum;
                            first_must_be_larger_than_this = max_sum / 3;
                            idx1 = k_sum[i][1], idx2 = k_sum[j][1], idx3 = k_sum[m][1];
                        }
                        //if (curr_sum <= max_sum) {time_to_exit = 1;}break;
                    }
                }

                //if (time_to_exit != 0) {time_to_exit = 0;break;}
            }
        }
    }


    vector<int> result = {idx1, idx2, idx3};
    int temp;
    if (result[0] > result[1]) {temp = result[0], result[0] = result[1], result[1] = temp;}
    if (result[0] > result[2]) {temp = result[0], result[0] = result[2], result[2] = temp;}
    if (result[1] > result[2]) {temp = result[1], result[1] = result[2], result[2] = temp;}

    return result;
}

vector<int> maxSumOfThreeSubarrays_brute_1(vector<int>& nums, int k) {
    int length = nums.size();
    vector<vector<int>> k_sum(length - k + 1, vector<int> (2, 0));

    int test_timer = -1;
    int sum = 0;for (int i = 0; i < k; i++) {sum += nums[i];}

    k_sum[0][0] = sum, k_sum[0][1] = 0;
    for (int i = 1; i < length - k + 1; i++) {
        sum -= nums[i - 1];
        sum += nums[i + k - 1];
        k_sum[i][0] = sum;
        k_sum[i][1] = i;
    }

    merge_sort (k_sum);

    if (test_timer >= 0) {for (int i = 0; i < k_sum.size(); i++) {cout << k_sum[i][0] << " " << k_sum[i][1] << "\n";}}

    int max_sum = 0, min_num = k_sum[0][0], idx1 = 0, idx2 = 0, idx3 = 0;
    int first_must_be_larger_than_this = 0, second_must_be_larger_than_this = 0;

    for (int i = length - k + 1 - 1, curr_sum; i > 1; i--) {
        //if (test_timer >= 0) {cout << "i = " << i << "\n";}
        if (k_sum[i][0] < first_must_be_larger_than_this) {break;}

        second_must_be_larger_than_this = (max_sum - k_sum[i][0]) / 2;

        for (int j = i - 1, time_to_exit = 0; j > 0; j--) {
            if (k_sum[j][0] < second_must_be_larger_than_this) {break;}

            if (abs(k_sum[j][1] - k_sum[i][1]) < k) {continue;}

                //if (test_timer >= 0) {cout << "\tj = " << j << "\n";}
            for (int m = j - 1; m >= 0; m--) {

                if ((abs(k_sum[m][1] - k_sum[j][1]) < k)||(abs(k_sum[i][1] - k_sum[m][1]) < k)) {continue;}

                //if (test_timer >= 0) {cout << "\t\tm = " << m << "\n";}
                curr_sum = k_sum[i][0] + k_sum[j][0] + k_sum[m][0];
                if (curr_sum > max_sum) {
                    max_sum = curr_sum;
                    first_must_be_larger_than_this = max_sum / 3;
                    idx1 = k_sum[i][1], idx2 = k_sum[j][1], idx3 = k_sum[m][1];
                }
                //else {time_to_exit = 1;}
                break;
            }

            //if (time_to_exit != 0) {time_to_exit = 0;break;}
        }
    }

    vector<int> result = {idx1, idx2, idx3};
    int temp;
    if (result[0] > result[1]) {temp = result[0], result[0] = result[1], result[1] = temp;}
    if (result[0] > result[2]) {temp = result[0], result[0] = result[2], result[2] = temp;}
    if (result[1] > result[2]) {temp = result[1], result[1] = result[2], result[2] = temp;}

    return result;
}

vector<int> maxSumOfThreeSubarrays_brute_2(vector<int>& nums, int k) {
    int length = nums.size();if (length < 3) {return vector<int> ();}
    vector<vector<int>> k_sum(length - k + 1, vector<int> (2, 0));

    int test_timer = -1;
    int sum = 0;for (int i = 0; i < k; i++) {sum += nums[i];}

    k_sum[0][0] = sum, k_sum[0][1] = 0;
    for (int i = 1; i < length - k + 1; i++) {
        sum -= nums[i - 1];
        sum += nums[i + k - 1];
        k_sum[i][0] = sum;
        k_sum[i][1] = i;
    }

    merge_sort (k_sum);
    //cout << "sorted\n";

    if (test_timer >= 0) {for (int i = 0; i < k_sum.size(); i++) {cout << k_sum[i][0] << " " << k_sum[i][1] << "\n";}}

    int max_sum = 0, min_num = k_sum[0][0], idx1 = 0, idx2 = 0, idx3 = 0;
    int first_must_be_larger_than_this = 0, second_must_be_larger_than_this = 0, third_must_be_larger_than_this = 0;

    for (int i = length - k, curr_sum; i > 1; i--) {
        //if (i % (length/100) == 0) {cout << "i = " << i << "\n";}
        //if (test_timer >= 0) {cout << "i = " << i << "\n";}

        if (k_sum[i][0] <= first_must_be_larger_than_this) {break;}

        second_must_be_larger_than_this = (max_sum - k_sum[i][0]) / 2;

        for (int j = i - 1, time_to_exit = 0; j > 0; j--) {
            if (k_sum[j][0] < second_must_be_larger_than_this) {break;}

            if (abs(k_sum[j][1] - k_sum[i][1]) < k) {continue;}

            third_must_be_larger_than_this = max_sum - k_sum[i][0] - k_sum[j][0];

            //if (test_timer >= 0) {cout << "\tj = " << j << "\n";}
            for (int m = j - 1; m >= 0; m--) {
                if (k_sum[m][0] <= third_must_be_larger_than_this) {break;}

                if ((abs(k_sum[m][1] - k_sum[j][1]) < k)||(abs(k_sum[i][1] - k_sum[m][1]) < k)) {continue;}

                //if (test_timer >= 0) {cout << "\t\tm = " << m << "\n";}
                curr_sum = k_sum[i][0] + k_sum[j][0] + k_sum[m][0];
                if (curr_sum > max_sum) {
                    max_sum = curr_sum;
                    first_must_be_larger_than_this = max_sum / 3;
                    idx1 = k_sum[i][1], idx2 = k_sum[j][1], idx3 = k_sum[m][1];
                }

                break;
            }
        }
    }

    vector<int> result = {idx1, idx2, idx3};
    int temp;
    if (result[0] > result[1]) {temp = result[0], result[0] = result[1], result[1] = temp;}
    if (result[0] > result[2]) {temp = result[0], result[0] = result[2], result[2] = temp;}
    if (result[1] > result[2]) {temp = result[1], result[1] = result[2], result[2] = temp;}

    return result;
}

void merge_sort_1 (int a[][2], int length) {//20200823, somewhat a bit better
    int b[length][2];
    for (int i = 0; i < length; i++) {b[i][0] = a[i][0], b[i][1] = a[i][1];}

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        b[k][0] = a[i][0], b[k][1] = a[i][1];
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
                            b[k][0] = a[i][0], b[k][1] = a[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j][0], b[k][1] = a[j][1];
                        j++, j_step++;
                    }

                    else if (a[i][0] < a[j][0]) {
                        b[k][0] = a[i][0], b[k][1] = a[i][1];
                        i++, i_step++;
                    }

                    else if (a[i][0] >= a[j][0]) {
                        b[k][0] = a[j][0], b[k][1] = a[j][1];
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
                        a[k][0] = b[i][0], a[k][1] = b[i][1];
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
                            a[k][0] = b[i][0], a[k][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k][0] = b[j][0], a[k][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][0] < b[j][0]) {
                        a[k][0] = b[i][0], a[k][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][0] >= b[j][0]) {
                        a[k][0] = b[j][0], a[k][1] = b[j][1];
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

vector<int> maxSumOfThreeSubarrays_brute_3(vector<int>& nums, int k) {
    int length = nums.size();if (length < 3) {return vector<int> ();}
    int k_sum[length - k + 1][2];

    int test_timer = -1;
    int sum = 0;for (int i = 0; i < k; i++) {sum += nums[i];}

    k_sum[0][0] = sum, k_sum[0][1] = 0;
    for (int i = 1; i < length - k + 1; i++) {
        sum -= nums[i - 1];
        sum += nums[i + k - 1];
        k_sum[i][0] = sum;
        k_sum[i][1] = i;
    }

    merge_sort_1 (k_sum, length - k + 1);
    //cout << "sorted\n";

    if (test_timer >= 0) {for (int i = 0; i < length - k + 1; i++) {cout << "idx " << i << " --- " << k_sum[i][0] << " " << k_sum[i][1] << "\n";}}

    int max_sum = 0, min_num = k_sum[0][0], idx1 = 0, idx2 = 0, idx3 = 0;
    int first_must_be_larger_than_this = 0, second_must_be_larger_than_this = 0, third_must_be_larger_than_this = 0;

    for (int i = length - k, curr_sum; i > 1; i--) {

        if (test_timer >= 0) {cout << "i = " << i << "\n";}
        if (k_sum[i][0] < first_must_be_larger_than_this) {break;}

        second_must_be_larger_than_this = (max_sum - k_sum[i][0]) / 2;

        for (int j = i - 1, time_to_exit = 0; j > 0; j--) {
            if (k_sum[j][0] < second_must_be_larger_than_this) {break;}

            if (abs(k_sum[j][1] - k_sum[i][1]) < k) {continue;}//cout << "^";

            third_must_be_larger_than_this = max_sum - k_sum[i][0] - k_sum[j][0];

            if (test_timer >= 0) {cout << "\tj = " << j << "\n";}
            for (int m = j - 1; m >= 0; m--) {
                if (test_timer >= 0) {cout << "\t\tm = " << m << "\n";}
                if (k_sum[m][0] < third_must_be_larger_than_this) {
                    break;
                }

                if ((abs(k_sum[m][1] - k_sum[j][1]) < k)||(abs(k_sum[i][1] - k_sum[m][1]) < k)) {continue;}//cout << ".";

                if (k_sum[m][0] > third_must_be_larger_than_this) {
                    max_sum = k_sum[i][0] + k_sum[j][0] + k_sum[m][0];
                    first_must_be_larger_than_this = max_sum / 3;
                    idx1 = k_sum[i][1], idx2 = k_sum[j][1], idx3 = k_sum[m][1];
                }

                else if (k_sum[i][1] + k_sum[j][1] + k_sum[m][1] < idx1 + idx2 + idx3) {
                    //this part will make sure that it find the correct result with input
                    // = {1, 3, 3, 2, 3, 2, 2, 3, 3, 1} k = 3
                    //if (test_timer >= 0) {cout << "\t\t\tmie~~~mie~~~\n";}
                    idx1 = k_sum[i][1], idx2 = k_sum[j][1], idx3 = k_sum[m][1];
                }

                break;
            }
        }
    }

    vector<int> result = {idx1, idx2, idx3};
    int temp;
    if (result[0] > result[1]) {temp = result[0], result[0] = result[1], result[1] = temp;}
    if (result[0] > result[2]) {temp = result[0], result[0] = result[2], result[2] = temp;}
    if (result[1] > result[2]) {temp = result[1], result[1] = result[2], result[2] = temp;}

    return result;
}

vector<int> maxSumOfThreeSubarrays_brute_4(vector<int>& nums, int k) {
    int length = nums.size();if (length < 3) {return vector<int> ();}
    int k_sum[length - k + 1][2];

    //int test_timer = -1;
    int sum = 0;for (int i = 0; i < k; i++) {sum += nums[i];}

    k_sum[0][0] = sum, k_sum[0][1] = 0;
    for (int i = 1; i < length - k + 1; i++) {
        sum -= nums[i - 1];
        sum += nums[i + k - 1];
        k_sum[i][0] = sum;
        k_sum[i][1] = i;
    }

    merge_sort_1 (k_sum, length - k + 1);

    int max_sum = 0, min_num = k_sum[0][0], idx1 = 0, idx2 = 0, idx3 = 0;
    int first_must_be_larger_than_this = 0, second_must_be_larger_than_this = 0, third_must_be_larger_than_this = 0;

    //int idx_cache[length - k + 1];for (int i = 0; i < length - k + 1; i++) {idx_cache[i] = -1;}
    //int m_idx_cache[length - k + 1];for (int i = 0; i < length - k + 1; i++) {m_idx_cache[i] = -1;}

    for (int i = length - k; i > 1; i--) {
        if (k_sum[i][0] <= first_must_be_larger_than_this) {break;}

        second_must_be_larger_than_this = (max_sum - k_sum[i][0]) / 2;

        //if (idx_cache[i] == -1) {next_j = i - 1;}else {next_j = idx_cache[i];}

        for (int j = i - 1; j > 0; j--) {
            if (k_sum[j][0] < second_must_be_larger_than_this) {break;}

            if (abs(k_sum[j][1] - k_sum[i][1]) < k) {continue;}

            //if (idx_cache[j] == -1) {next_m = j - 1;}else {next_m = idx_cache[j];}

            third_must_be_larger_than_this = max_sum - k_sum[i][0] - k_sum[j][0];

            for (int m = j - 1; m >= 0; m--) {
                if (k_sum[m][0] <= third_must_be_larger_than_this) {break;}
                if ((abs(k_sum[m][1] - k_sum[j][1]) < k)||(abs(k_sum[i][1] - k_sum[m][1]) < k)) {continue;}

                max_sum = k_sum[i][0] + k_sum[j][0] + k_sum[m][0];
                first_must_be_larger_than_this = max_sum / 3;
                idx1 = k_sum[i][1], idx2 = k_sum[j][1], idx3 = k_sum[m][1];

                break;
            }
        }
    }

    vector<int> result = {idx1, idx2, idx3};
    int temp;
    if (result[0] > result[1]) {temp = result[0], result[0] = result[1], result[1] = temp;}
    if (result[0] > result[2]) {temp = result[0], result[0] = result[2], result[2] = temp;}
    if (result[1] > result[2]) {temp = result[1], result[1] = result[2], result[2] = temp;}

    return result;
}

vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    int length = nums.size(), max_sum = 0, test_timer = 0;
    vector<int> k_sum(length - k + 1, 0);

    cout << "what?!\n";

    int sum = 0;
    for (int i = 0; i < k; i++) {sum += nums[i];}

    k_sum[0] = sum;
    for (int i = 1; i < length - k + 1; i++) {
        sum -= nums[i - 1], sum += nums[i + k - 1];
        k_sum[i] = sum;
    }

    if (test_timer >= 0) {
        cout << "k_sum: ";
        for (int i = 0; i < k_sum.size(); i++) {
            cout << k_sum[i] << " ";
        }
        cout << "\n\n";
    }

    int first = 0, second = k, third = k * 2;
    int curr_sum = k_sum[first] + k_sum[second] + k_sum[third];
    max_sum = curr_sum;
    int the_rest = 0;

    int idx1 = first, idx2 = second, idx3 = third, idx1_right_wall = first, idx2_right_wall = second;
    idx3++;
    //are these useful?



    for (; idx3 <= length - k; idx3++) {
        idx1_right_wall++, idx2_right_wall++;
        the_rest = curr_sum - k_sum[idx3];

        if (test_timer >= 0) {
            cout << "\nidx1_right_wall = " << idx1_right_wall << "\n";
            cout << "idx2_right_wall = " << idx2_right_wall << "\n";
            cout << "curr_sum = " << curr_sum << "\n";
            cout << "the_rest = " << the_rest << "\n";
            cout << "first = " << first << "\n";
            cout << "second = " << second << "\n";
            cout << "third = " << third << "\n\n";
        }

        if (k_sum[idx1_right_wall] + k_sum[idx2_right_wall] > the_rest) {
            if (test_timer >= 0) {
                cout << "~1\n";
            }

            idx1 = idx1_right_wall, idx2 = idx2_right_wall;
            first = idx1, second = idx2;
            third = idx3;
            curr_sum = k_sum[first] + k_sum[second] + k_sum[third];
        }
        else if (k_sum[idx1] + k_sum[idx2_right_wall] > the_rest) {
            if (test_timer >= 0) {
                cout << "~2\n";
            }
            idx2 = idx2_right_wall;
            second = idx2;
            third = idx3;
            curr_sum = k_sum[first] + k_sum[second] + k_sum[third];
        }

        else if (k_sum[idx3] > k_sum[third]) {
            if (test_timer >= 0) {
                cout << "~3\n";
            }
            third = idx3;
            curr_sum = k_sum[first] + k_sum[second] + k_sum[third];
        }
    }

    vector<int> result = {first, second, third};

    return result;
}

vector<int> maxSumOfThreeSubarrays_1(vector<int>& nums, int k) {
    int length = nums.size();if (length < 3) {return vector<int> ();}
    int max_sum = 0, test_timer = -1;
    vector<int> k_sum(length - k + 1, 0);

    int sum = 0;for (int i = 0; i < k; i++) {sum += nums[i];}

    k_sum[0] = sum;
    for (int i = 1; i < length - k + 1; i++) {sum -= nums[i - 1], sum += nums[i + k - 1], k_sum[i] = sum;}

    if (test_timer >= 0) {
        cout << "k_sum: ";
        for (int i = 0; i < k_sum.size(); i++) {
            cout << k_sum[i] << " ";
        }
        cout << "\n\n";
    }

    int first = 0, second = k, third = k * 2;
    queue<int> idx1_candidates;
    queue<int> idx2_candidates;
    queue<int> idx3_candidates;
    int there_are_still_idx3_candidates = 0;

    //this can be improved, well, let's work on other issues for the moment
    for (int i = k * 2 + 1; i <= length - k; i++) {
        if (k_sum[i] > k_sum[third]) {
            third = i;
            while (!idx3_candidates.empty()) {idx3_candidates.pop();}
            there_are_still_idx3_candidates = 0;
        }
        else if (k_sum[i] == k_sum[third]) {
            idx3_candidates.push(i);
            there_are_still_idx3_candidates = 1;
        }
    }
    for (int i = k + 1; i <= third - k; i++) {
        if (k_sum[i] > k_sum[second]) {
            second = i;
        }
    }
    for (int i = 1; i <= second - k; i++) {
        if (k_sum[i] > k_sum[first]) {
            first = i;
        }
    }

    int curr_sum = k_sum[first] + k_sum[second] + k_sum[third];
    max_sum = curr_sum;
    int the_rest = 0, idx2_right_wall;

    int idx1 = first + 1, idx2 = second + 1, idx3 = third + 1;

    if (test_timer >= 0) {
        cout << "before processing:\n";
        cout << "first = " << first << ", second = " << second << ", third = " << third << "\n";
        cout << "idx1 = " << idx1 << ", idx2 = " << idx2 << ", idx3 = " << idx3 << "\n";
        //cout << "idx1_right_wall = " << idx1_right_wall << ", idx2_right_wall = " << idx2_right_wall << "\n";
        cout << "curr_sum = " << curr_sum << "\n\n";
    }

    for (int idx1_compare_val, idx2_compare_val; idx3 < length - k;) {
        if (there_are_still_idx3_candidates == 0) {idx3++;}
        else {
            idx3 = idx3_candidates.front();
            idx3_candidates.pop();
            if (idx3_candidates.empty()) {there_are_still_idx3_candidates = 0;}
        }

        if (test_timer >= 0) {cout << "idx3 = " << idx3 << "\n";}

        idx2_right_wall = idx3 - k + 1;

        the_rest = curr_sum - k_sum[idx3];

        /*if (test_timer >= 0) {
            cout << "\nidx1_right_wall = " << idx1_right_wall << "\n";
            cout << "idx2_right_wall = " << idx2_right_wall << "\n";
            cout << "curr_sum = " << curr_sum << "\n";
            cout << "the_rest = " << the_rest << "\n";
            cout << "first = " << first << "\n";
            cout << "second = " << second << "\n";
            cout << "third = " << third << "\n\n";
        }*/

        for (int i = idx2; i < idx2_right_wall; i++) {
            if (test_timer >= 0) {cout << "i = " << i << "\n";}

            if (k_sum[i] >= k_sum[second]) {
                if (idx2_candidates.empty()){
                    idx2_candidates.push(i);
                    if (test_timer >= 0) {cout << "idx2_candidates pushed " << i << "\n";}
                }

                else if ((!idx2_candidates.empty())&&(k_sum[i] >= idx2_candidates.front())) {
                    if (k_sum[i] > k_sum[idx2_candidates.front()]) {
                        while (!idx2_candidates.empty()) {
                            if (test_timer >= 0) {cout << "idx2_candidates poped " << idx2_candidates.front() << "\n";}
                            idx2_candidates.pop();
                        }
                    }
                    idx2_candidates.push(i);
                    if (test_timer >= 0) {cout << "idx2_candidates pushed " << i << "\n";}
                }
            }

            if (k_sum[i - k] >= k_sum[first]) {
                if (idx1_candidates.empty()){
                    idx1_candidates.push(i - k);
                    if (test_timer >= 0) {cout << "idx1_candidates pushed " << i - k << "\n";}
                }

                else if ((!idx1_candidates.empty())&&(k_sum[i - k] >= idx1_candidates.front())) {
                    if (k_sum[i - k] > k_sum[idx1_candidates.front()]) {
                        while (!idx1_candidates.empty()) {
                            if (test_timer >= 0) {cout << "idx1_candidates poped " << idx1_candidates.front() << "\n";}
                            idx1_candidates.pop();
                        }
                    }
                    idx1_candidates.push(i - k);
                    if (test_timer >= 0) {cout << "idx1_candidates pushed " << i - k << "\n";}
                }
            }

            if (idx1_candidates.empty()) {
                idx1_compare_val = k_sum[first];
                idx1 = first;
            }
            else {
                idx1_compare_val = k_sum[idx1_candidates.front()];
                idx1 = idx1_candidates.front();
            }

            if (idx2_candidates.empty()) {
                idx2_compare_val = k_sum[second];
                idx2 = second;
            }
            else {
                idx2_compare_val = k_sum[idx2_candidates.front()];
                idx2 = idx2_candidates.front();
            }

            //idx1_compare_val = (idx1_candidates.empty())? k_sum[first]: k_sum[idx1_candidates.front()];
            //idx2_compare_val = (idx2_candidates.empty())? k_sum[second]: k_sum[idx2_candidates.front()];

            if ((idx1_compare_val + idx2_compare_val > the_rest)&&(idx1 + k <= idx2)) {
                if (!idx1_candidates.empty()) {
                    first = idx1_candidates.front();
                    idx1_candidates.pop();
                }
                if (!idx2_candidates.empty()) {
                    second = idx2_candidates.front();
                    idx2_candidates.pop();
                }
                third = idx3;
                curr_sum = k_sum[first] + k_sum[second] + k_sum[third];
                if (test_timer >= 0) {cout << "first = " << first << ", second = " << second << ", third = " << third << "\n";}

            }
        }

        idx2 = idx2_right_wall;

        if (test_timer >= 0) {
            cout << "after this step:\n";
            if (!idx1_candidates.empty()) {cout << "idx1_candidates.front() = " << idx1_candidates.front() << "\n";}
            if (!idx2_candidates.empty()) {cout << "idx2_candidates.front() = " << idx2_candidates.front() << "\n";}
            cout << "first = " << first << ", second = " << second << ", third = " << third << "\n";
            cout << "idx1 = " << idx1 << ", idx2 = " << idx2 << ", idx3 = " << idx3 << "\n";
            //cout << "idx1_right_wall = " << idx1_right_wall << ", idx2_right_wall = " << idx2_right_wall << "\n";
            cout << "curr_sum = " << curr_sum << "\n\n";
        }

    }

    vector<int> result = {first, second, third};

    return result;
}

vector<int> maxSumOfThreeSubarrays_2(vector<int>& nums, int k) {
    int length = nums.size();if (length < 3) {return vector<int> ();}
    int max_sum = 0, first = 0, second = k, third = k * 2, test_timer = -1;
    vector<int> k_sum(length - k + 1, 0);

    int sum = 0;for (int i = 0; i < k; i++) {sum += nums[i];}

    k_sum[0] = sum;
    for (int i = 1; i < length - k + 1; i++) {sum -= nums[i - 1], sum += nums[i + k - 1], k_sum[i] = sum;}

    if (test_timer >= 0) {
        cout << "\n\nhere we go again.\n\nk_sum:\n";
        for (int i = 0; i < k_sum.size(); i++) {
            cout << "idx " << i << " --- " << k_sum[i] << "\n";
        }
        cout << "\n\n";
    }

    max_sum = k_sum[first] + k_sum[second] + k_sum[third];
    int idx1 = first, idx2 = second, the_rest = 0;

    if (test_timer >= 0) {
        cout << "before processing:\n";
        cout << "first = " << first << ", second = " << second << ", third = " << third << "\n";
        cout << "idx1 = " << idx1 << ", idx2 = " << idx2 << "\n";
        cout << "max_sum = " << max_sum << "\n\n";
    }

    int max_idx_so_far[length - k * 3 + 1];max_idx_so_far[0] = 0;
    for (int i = 1; i <= length - k * 3; i++) {
        if (k_sum[i] > k_sum[max_idx_so_far[i - 1]]) {max_idx_so_far[i] = i;}

        else {max_idx_so_far[i] = max_idx_so_far[i - 1];}
    }

    if (test_timer >= 0) {
        cout << "\nmax_idx_so_far:\n";
        for (int i = 0; i <= length - k * 3; i++) {
            cout << max_idx_so_far[i] << " ";
        }
        cout << "\n\n";
    }

    for (int i = third + 1; i <= length - k; i++) {
        if (test_timer >= 0) {cout << "i = " << i << "\n";}

        if (k_sum[i] > k_sum[third]) {third = i;}

        the_rest = max_sum - k_sum[i];

        /*if (test_timer >= 0) {
            cout << "\nidx1_right_wall = " << idx1_right_wall << "\n";
            cout << "idx2_right_wall = " << idx2_right_wall << "\n";
            cout << "curr_sum = " << curr_sum << "\n";
            cout << "the_rest = " << the_rest << "\n";
            cout << "first = " << first << "\n";
            cout << "second = " << second << "\n";
            cout << "third = " << third << "\n\n";
        }*/

        if (k_sum[i - k] > k_sum[idx2]) {if (test_timer >= 0) {cout << "~1\n";}
            /*if (k_sum[i - k * 2] > k_sum[idx1]) {if (test_timer >= 0) {cout << "~1.1\n";}
                idx1 = i - k * 2;
            }
            if (k_sum[idx2] > k_sum[idx1]) {if (test_timer >= 0) {cout << "~1.2\n";}
                idx1 = idx2;
            }*/
            idx2 = i - k;
            idx1 = max_idx_so_far[idx2 - k];
        }

        if (k_sum[i - k] + k_sum[max_idx_so_far[i - k * 2]] > k_sum[idx1] + k_sum[idx2]) {if (test_timer >= 0) {cout << "~2\n";}
            idx1 = max_idx_so_far[i - k * 2], idx2 = i - k;
        }

        if (k_sum[idx1] + k_sum[idx2] > the_rest) {if (test_timer >= 0) {cout << "~3\n";}
            first = idx1, second = idx2, third = i;
            max_sum = k_sum[first] + k_sum[second] + k_sum[third];
        }

        if (test_timer >= 0) {
            cout << "after this step:\n";
            cout << "the_rest = " << the_rest << "\n";
            cout << "first = " << first << ", second = " << second << ", third = " << third << "\n";
            cout << "idx1 = " << idx1 << ", idx2 = " << idx2 << "\n";
            cout << "max_sum = " << max_sum << "\n\n";
        }
    }

    vector<int> result = {first, second, third};

    return result;
}


//significant execution time reduction with vector be replaced by equivalent array
vector<int> maxSumOfThreeSubarrays_2_1(vector<int>& nums, int k) {
    int length = nums.size();
    if (length < 3) {return vector<int> ();}
    int max_sum = 0, first = 0, second = k, third = k * 2;

    int sum = 0;
    for (int i = 0; i < k; i++) {sum += nums[i];}

    int k_sum[length - k + 1];
    k_sum[0] = sum;
    for (int i = 1; i < length - k + 1; i++) {
        sum -= nums[i - 1], sum += nums[i + k - 1], k_sum[i] = sum;
    }

    max_sum = k_sum[first] + k_sum[second] + k_sum[third];
    int idx1 = first, idx2 = second, the_rest = 0;

    int first_idx_cache_length = length - k * 3 + 1;
    int max_idx_so_far[first_idx_cache_length];
    max_idx_so_far[0] = 0;
    for (int i = 1; i < first_idx_cache_length; i++) {
        if (k_sum[i] > k_sum[max_idx_so_far[i - 1]]) {max_idx_so_far[i] = i;}

        else {max_idx_so_far[i] = max_idx_so_far[i - 1];}
    }

    for (int i = third + 1; i <= length - k; i++) {
        if (k_sum[i] > k_sum[third]) {third = i;}

        the_rest = max_sum - k_sum[i];

        if (k_sum[i - k] > k_sum[idx2]) {
            idx2 = i - k, idx1 = max_idx_so_far[idx2 - k];
        }

        if (k_sum[i - k] + k_sum[max_idx_so_far[i - k * 2]] > k_sum[idx1] + k_sum[idx2]) {
            idx1 = max_idx_so_far[i - k * 2], idx2 = i - k;
        }

        if (k_sum[idx1] + k_sum[idx2] > the_rest) {
            first = idx1, second = idx2, third = i;
            max_sum = k_sum[first] + k_sum[second] + k_sum[third];
        }
    }

    vector<int> result = {first, second, third};

    return result;
}


int main(){
    int k = 3, length = 20000, lower_range = 1, upper_range = 60000;srand(time(0));
    int mass_testing = 1, display = 0, input = 1;
    vector<int> wtf;
    //cout << "shitshit\n";
/*
something is wrong with input
 = {3, 2, 1, 2, 3, 3, 1, 2, 1, 1};
k = 3

 = {2, 3, 1, 3, 1, 2, 3, 1, 1, 2, };
k = 3

*/
auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;
auto start_point_4 = chrono::steady_clock::now();auto end_point_4 = chrono::steady_clock::now();auto diff_4 = end_point_4 - start_point_4;

for (int m = 1; m <= 10000; m++) {if (m % 100 == 0){cout << "m = " << m << "\n";}
    if (input == 1){
        wtf.reserve(length);
        for(int i = 0; i < length; i++){
            wtf.push_back(rand()%(upper_range - lower_range + 1) + lower_range);
        }
        k = rand()%((length / 3) - 1 + 1) + 1;
    }
    if (display == 1){
        cout << "k = " << k << "\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i] << ", ";
            if ((i + 1) % 20 == 0) {cout << "\n";}
        }
        cout << "}\n";
    }
    vector<int> wtf1 (wtf);vector<int> wtf2 (wtf);vector<int> wtf3 (wtf);

    /*start_point_1 = chrono::steady_clock::now();
    vector<int> shit = maxSumOfThreeSubarrays_brute(wtf, k);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;
    if (mass_testing == 0) {for (int i = 0; i < shit.size(); i++) {cout << shit[i] << ", ";}cout << "\n";}*/
    /*start_point_2 = chrono::steady_clock::now();
    vector<int> a = maxSumOfThreeSubarrays_brute_1(wtf1, k);
    end_point_2 = chrono::steady_clock::now();
    //diff_2 += end_point_2 - start_point_2;
    diff_2 += end_point_2 - start_point_2;
    if (mass_testing == 0){for (int i = 0; i < a.size(); i++) {cout << a[i] << ", ";}cout << "\n";}
    cout << duration <double, milli> (end_point_2 - start_point_2).count() << " ms" << "\n";*/

    start_point_3 = chrono::steady_clock::now();
    vector<int> aa = maxSumOfThreeSubarrays_2(wtf2, k);
    end_point_3 = chrono::steady_clock::now();
    //diff_3 += end_point_3 - start_point_3;
    diff_3 += end_point_3 - start_point_3;
    if (mass_testing == 0){cout << "\n\n";for (int i = 0; i < aa.size(); i++) {cout << aa[i] << ", ";}cout << "\n";}
    auto dont_know_what_this_should_be = duration <double, milli> (end_point_3 - start_point_3).count();
    //cout << duration <double, milli> (end_point_3 - start_point_3).count() << " ms" << "\n";
    //cout << dont_know_what_this_should_be << " ms" << "\n";

    //cout << "\n\nnow to new algo:\n";

    /*if (dont_know_what_this_should_be > 1000) {
        int what_the_fuck = dont_know_what_this_should_be;
        cout << "file output.\n";
        ofstream intriguing_input;
        string name = "m = " + to_string(m) + ", k = " + to_string(k) + ", " + to_string(what_the_fuck) + " ms.txt";
        intriguing_input.open(name);
        if (intriguing_input.is_open()) {
            for (int i = 0; i < wtf.size(); i++) {
                intriguing_input << wtf[i] << ", ";
            }
            intriguing_input.close();
        }
    }*/

    start_point_4 = chrono::steady_clock::now();
    vector<int> aaa = maxSumOfThreeSubarrays_2_1(wtf3, k);
    end_point_4 = chrono::steady_clock::now();
    //diff_3 += end_point_3 - start_point_3;
    diff_4 += end_point_4 - start_point_4;
    if (mass_testing == 0){for (int i = 0; i < aaa.size(); i++) {cout << aaa[i] << ", ";}cout << "\n";}
    //cout << duration <double, milli> (end_point_4 - start_point_4).count() << " ms" << "\n\n";

    /*int sum3 = 0;
    for (int i = 0; i < shitshitshit.size(); i++) {
        for (int j = shitshitshit[i]; j < shitshitshit[i] + k; j++) {
            sum3 += wtf2[j];
        }
    }

    //if ((shit[0] != shitshit[0])||(shit[1] != shitshit[1])||(shit[2] != shitshit[2])) {
    //if ((sum1 != sum2)||(sum1 != sum3)) {

    if ((sum2 != sum3)) {
        cout << "something is wrong.\n";
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i] << ", ";
            if ((i + 1) % 20 == 0) {cout << "\n";}
        }
        cout << "};\n";

        cout << "k = " << k << "\n";
        //cout << "shit: " << shit[0] << " " << shit[1] << " " << shit[2] << "\n";
        //cout << "1st sum = " << sum1 << "\n";
        cout << "shitshit: " << shitshit[0] << " " << shitshit[1] << " " << shitshit[2] << "\n";
        cout << "2nd sum = " << sum2 << "\n";
        cout << "shitshitshit: " << shitshitshit[0] << " " << shitshitshit[1] << " " << shitshitshit[2] << "\n";
        cout << "3rd sum = " << sum3 << "\n";

        break;
    }
*/

    //if ((a[0] != aa[0])||(a[1] != aa[1])||(a[2] != aa[2])||(aa[0] != aaa[0])||(aa[1] != aaa[1])||(aa[2] != aaa[2])) {
    if ((aa[0] != aaa[0])||(aa[1] != aaa[1])||(aa[2] != aaa[2])) {
        cout << "something is wrong.\n";
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i] << ", ";
            if ((i + 1) % 20 == 0) {cout << "\n";}
        }
        cout << "};\n";

        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < aa.size(); i++) {
            for (int j = aa[i]; j < aa[i] + k; j++) {
                sum1 += wtf[j];
            }
        }

        for (int i = 0; i < aaa.size(); i++) {
            for (int j = aaa[i]; j < aaa[i] + k; j++) {
                sum2 += wtf1[j];
            }
        }

        cout << "k = " << k << "\n";
        //cout << "a: " << a[0] << " " << a[1] << " " << a[2] << "\n";
        cout << "aa: " << aa[0] << " " << aa[1] << " " << aa[2] << "\t";
        cout << "sum of aa = " << sum1 << "\n";

        cout << "aaa: " << aaa[0] << " " << aaa[1] << " " << aaa[2] << "\t";
        cout << "sum of aaa = " << sum2 << "\n";

        break;
    }

wtf.clear();
}

//cout << duration <double, milli> (diff_1).count() << " ms" << "\n";
//cout << duration <double, milli> (diff_2).count() << " ms" << "\n";
cout << duration <double, milli> (diff_3).count() << " ms" << "\n";
cout << duration <double, milli> (diff_4).count() << " ms" << "\n\n";

    return 0;
}




/*{50004, 7110, 8594, 16706, 6959, 11260, 19689, 55273, 10545, 40416, 45426, 38581, 39028, 4328, 28238, 24136, 56637, 57972, 40113, 17383,
63434, 15370, 44818, 54322, 58161, 23567, 41269, 28877, 23661, 1679, 5467, 15931, 62488, 57825, 53048, 11474, 15668, 61462, 391, 27580,
3131, 34351, 20694, 48700, 37146, 3490, 52223, 17495, 9725, 16006, 29100, 54414, 24819, 24719, 56401, 16883, 4052, 46365, 30434, 23870,
17243, 63706, 30260, 23332, 56085, 7907, 57811, 18841, 56107, 27701, 21975, 5283, 11339, 33543, 62356, 61996, 15960, 57713, 22082, 44405,
39809, 55143, 45622, 172, 25617, 46204, 26349, 5210, 6496, 41006, 14559, 56974, 19373, 44683, 12991, 54113, 28684, 60479, 37015, 61828,
23049, 39099, 24837, 59085, 56810, 19729, 31455, 53465, 58080, 47234, 8202, 18842, 35983, 43558, 42639, 30312, 15007, 25296, 49020, 39318,
29626, 15631, 28871, 49812, 12057, 62667, 43122, 21267, 22626, 25280, 30049, 16488, 30802, 10275, 47031, 6923, 42565, 18940, 55420, 26317,
4148, 623, 60598, 8067, 49149, 14708, 64363, 62344, 44950, 55552, 39700, 48953, 25259, 10900, 12965, 45809, 39766, 39945, 433, 47923,
1272, 59603, 17205, 30884, 1699, 41359, 45997, 59298, 55024, 19578, 21557, 42182, 22509, 13758, 20176, 2593, 46694, 609, 17549, 11823,
47428, 26523, 35343, 15070, 54973, 50429, 65176, 6574, 44367, 16165, 63797, 6987, 19479, 48865, 24598, 27228, 18348, 54783, 48397, 18004,
3764, 55325, 59300, 11513, 20976, 28470, 39240, 53598, 27334, 15571, 843, 25154, 33268, 26327, 29554, 57122, 48237, 62346, 40575, 16645,
9192, 54027, 39739, 56038, 3723, 59065, 3844, 17154, 49604, 41591, 9383, 8100, 48387, 31593, 27066, 22950, 32158, 58185, 15365, 2622,
37184, 27537, 27181, 59479, 58895, 6021, 52275, 29968, 53880, 41577, 10100, 64164, 49103, 10195, 21174, 21096, 59061, 36364, 29422, 37386,
50289, 17095, 41435, 38441, 32563, 22836, 14038, 22924, 11217, 7092, 16548, 35256, 17605, 518, 30143, 28002, 38977, 3057, 48801, 38510,
3088, 42371, 38916, 42449, 8306, 28346, 30643, 13979, 20750, 3316, 23485, 54922, 44945, 22911, 25997, 55075, 21276, 36582, 18289, 56871,
35499, 35953, 22272, 43787, 60639, 50792, 47840, 33539, 55673, 53499, 7324, 29034, 44887, 4699, 40587, 47596, 40857, 29838, 42463, 36599,
4526, 24848, 49705, 8997, 10203, 58768, 60519, 52083, 8582, 29304, 17156, 54819, 1780, 64952, 2781, 31207, 31077, 11627, 16638, 48055,
54735, 46298, 22285, 34636, 11271, 54262, 37334, 6129, 17764, 30071, 56700, 5510, 25971, 2440, 53133, 8135, 15792, 31024, 50684, 9616,
15539, 28634, 20149, 6439, 48100, 46105, 31024, 24157, 1187, 40755, 17682, 29795, 13430, 50910, 41696, 31957, 9691, 24871, 53697, 33783,
50817, 9077, 613, 19848, 8095, 64950, 39727, 43909, 43996, 36106, 24314, 46447, 32868, 39558, 12486, 57944, 3196, 46608, 11281, 38814,
11863, 23269, 56164, 24417, 50352, 17155, 37782, 40827, 50633, 52635, 37583, 39358, 13846, 48318, 20413, 44507, 58599, 8159, 7195, 40867,
5611, 4705, 7549, 46341, 9744, 42581, 42251, 58796, 5539, 100, 6472, 62040, 52191, 51331, 58340, 2939, 49602, 54075, 32667, 31109,
60060, 31452, 44625, 50637, 57886, 48459, 293, 22418, 46625, 9188, 249, 64020, 41916, 28796, 56521, 65182, 20120, 56635, 15578, 29383,
47704, 53189, 4194, 10384, 20064, 11167, 35043, 64616, 26141, 21228, 47725, 13188, 36706, 41533, 38942, 48903, 8404, 33399, 50944, 32877,
50239, 51069, 40974, 11898, 59278, 6030, 52474, 11414, 44237, 60798, 7926, 3210, 50488, 48766, 48785, 37747, 33907, 64765, 42262, 30223,
17224, 20138, 1985, 60297, 24869, 32699, 23904, 10534, 36168, 13888, 23666, 50195, 51905, 50562, 54968, 29577, 17787, 8883, 45932, 26863,
12644, 40509, 30466, 25408, 3794, 47474, 7004, 25959, 39533, 21805, 5147, 41822, 39769, 29341, 60303, 6507, 45090, 61434, 25470, 16236,
7720, 3745, 53171, 9210, 55193, 16890, 26062, 47141, 54458, 1375, 22822, 12935, 9034, 39734, 27876, 46702, 51794, 63534, 24634, 57502,
59095, 56152, 15840, 31443, 8542, 31708, 33259, 28330, 43056, 17580, 55744, 61677, 7817, 13473, 55265, 33625, 35042, 17256, 27821, 25879,
59934, 14578, 9045, 42934, 31184, 8201, 2681, 42349, 550, 25510, 63686, 5418, 33359, 10124, 3313, 15297, 35661, 3554, 29686, 27958,
53176, 57096, 45955, 59964, 53063, 41667, 49486, 22964, 22564, 6335, 62146, 24247, 40695, 65188, 25168, 13548, 36998, 46245, 61498, 49966,
27220, 51645, 58500, 46049, 54129, 26766, 26576, 58254, 55136, 14476, 10636, 57682, 29320, 810, 35604, 59765, 40958, 41975, 1768, 9685,
4004, 4386, 64983, 5981, 30195, 36492, 2893, 63877, 19352, 34453, 31649, 59297, 14826, 51580, 10760, 47172, 12066, 46490, 50406, 35183,
20318, 11166, 58141, 60242, 9495, 25552, 25832, 39967, 47706, 40857, 41902, 20653, 19707, 32293, 31525, 30673, 63719, 3463, 51632, 39271,
46854, 24190, 53249, 16318, 28455, 27597, 47047, 39320, 26791, 62814, 15169, 41857, 40454, 57723, 6927, 12022, 15802, 31925, 7107, 29761,
4366, 63634, 39551, 4596, 34817, 58838, 58861, 45286, 50602, 15438, 24312, 3060, 27682, 31821, 20412, 40576, 47564, 17406, 53597, 46640,
19599, 22870, 10220, 26417, 22815, 5187, 44298, 53280, 29565, 2056, 20204, 39205, 65103, 34522, 1524, 28231, 40506, 21917, 39319, 64862,
30674, 11418, 6581, 4805, 65522, 23440, 57092, 46908, 49032, 1681, 57971, 43282, 51851, 16080, 15646, 44766, 45401, 49422, 37278, 12889,
50325, 41368, 54788, 61984, 56219, 35633, 16330, 5668, 63667, 30099, 33153, 1765, 26427, 14740, 23993, 8418, 13868, 54599, 1084, 14612,
52378, 62811, 57493, 26377, 7869, 61125, 19090, 10473, 20828, 26201, 11305, 13617, 32783, 52409, 59146, 41822, 2093, 50484, 48863, 13381,
4364, 8964, 7954, 53323, 6065, 63817, 19133, 65361, 61343, 10589, 41627, 12231, 42363, 20196, 52828, 46594, 63102, 9839, 57725, 15475,
16351, 8251, 7047, 47216, 33083, 52800, 55969, 23382, 6485, 1033, 5962, 60308, 3407, 7186, 63879, 7138, 35338, 24735, 27350, 24657,
15857, 6078, 2814, 53196, 29248, 6568, 49513, 2527, 53712, 48281, 5477, 41808, 34211, 42349, 14681, 46322, 28812, 53506, 2115, 24102,
28206, 15048, 19059, 55984, 22083, 41626, 51142, 39861, 8839, 43161, 54603, 49813, 37741, 46569, 46598, 52801, 42534, 29979, 12591, 9581,
52191, 834, 36847, 48326, 29375, 31308, 45585, 44194, 17551, 58345, 18835, 3705, 11218, 59410, 53772, 36285, 62919, 45946, 10203, 53479,
62907, 52380, 20794, 15843, 32778, 56186, 4271, 40811, 56876, 8668, 30268, 25951, 52609, 5062, 53898, 46917, 30830, 451, 24094, 12946,
58879, 40075, 55511, 17966, 18996, 41310, 6797, 1466, 9601, 59291, 49649, 50585, 37561, 39097, 43207, 22858, 25171, 63146, 7809, 47363,
16905, 31714, 35521, 4894, 59696, 35182, 55438, 23216, 60680, 43402, 18569, 1468, 43884, 8412, 34627, 45029, 50446, 47968, 26155, 47797,
50404, 17083, 56055, 8156, 38560, 26211, 14553, 33959, 10179, 10587, 57709, 40850, 10784, 27820, 17984, 23701, 26004, 52719, 63697, 13287,
65438, 18211, 704, 17069, 24368, 2465, 64936, 24247, 59512, 1211, 63856, 33416, 53108, 3272, 11183, 23628, 8037, 60388, 45564, 12256,
12797, 15699, 52337, 61109, 22075, 1173, 36764, 7729, 28279, 45850, 21054, 12369, 28015, 46565, 18963, 23982, 34708, 29989, 36253, 33607,
63724, 57597, 54041, 2000, 5685, 52831, 32244, 41033, 10870, 60056, 44670, 23690, 61290, 2813, 22468, 28393, 27489, 41363, 37959, 12592,
33304, 29572, 49546, 538, 29678, 1919, 40359, 1976, 37322, 43261, 24542, 16895, 64148, 34513, 8920, 75, 53316, 22104, 14688, 46041,
48599, 48506, 20617, 38019, 33578, 50353, 48431, 45529, 56030, 40255, 52899, 9523, 61736, 35451, 33650, 10090, 21560, 40695, 28018, 55240,
19293, 10660, 42435, 14166, 8262, 4313, 21062, 36110, 15728, 46796, 63453, 47884, 8174, 51663, 21175, 24056, 1937, 35838, 16838, 31593,
20834, 6584, 30732, 40126, 41906, 59759, 16978, 7394, 38371, 5302, 10707, 10031, 60535, 17277, 5208, 42757, 57652, 35117, 29925, 13675,
58651, 13467, 46577, 4614, 45428, 7082, 18696, 61072, 45940, 7364, 30472, 65022, 16048, 11089, 50965, 43118, 48300, 55554, 60285, 5137,
62711, 8071, 53490, 50959, 40248, 52174, 22865, 65348, 33538, 25540, 59380, 10620, 11753, 26698, 30972, 16586, 54374, 28868, 24828, 229,
12530, 14963, 34754, 28111, 25835, 37629, 51868, 28657, 4638, 59608, 29572, 25708, 46226, 48646, 58896, 25537, 27275, 55481, 54470, 50483,
32383, 18013, 47665, 59757, 23435, 60687, 24418, 598, 7443, 29806, 44518, 20784, 17889, 556, 32453, 60020, 17917, 45194, 65017, 8848,
5820, 22373, 44623, 45192, 5644, 45403, 20960, 52170, 57788, 27566, 15498, 55495, 32436, 13711, 16867, 24510, 29124, 46629, 10137, 52183,
40846, 36905, 15967, 55490, 13687, 1665, 39437, 43041, 43106, 4452, 7422, 22132, 41747, 33173, 22179, 19197, 61234, 42765, 10865, 48608,
8624, 6887, 61162, 57330, 14551, 32742, 36677, 45495, 21574, 63961, 10893, 14729, 5335, 39279, 13816, 6702, 52208, 18644, 31991, 27106,
45331, 7025, 50534, 36365, 3849, 5017, 21292, 32697, 41027, 19645, 18284, 30186, 45333, 21998, 5065, 6369, 35198, 35588, 17551, 46683,
29263, 46108, 40049, 3155, 49899, 3851, 64309, 18201, 22518, 49554, 7870, 18951, 47006, 60276, 24883, 14365, 25751, 52921, 64437, 18607,
8706, 10194, 62732, 39187, 14997, 33188, 41055, 28552, 6622, 59744, 59883, 57002, 65240, 33181, 22309, 36464, 4893, 7248, 30346, 56539,
37601, 57460, 25080, 44294, 31336, 4902, 1627, 431, 50832, 56346, 22294, 54174, 31286, 62205, 3427, 19745, 59232, 56696, 13613, 46135,
41170, 29685, 7275, 52007, 3629, 47884, 5202, 14563, 15592, 26306, 54088, 1514, 43336, 16986, 17487, 33223, 46424, 51323, 16232, 14433,
44466, 43722, 33536, 5313, 12513, 4933, 37845, 41294, 42772, 7558, 958, 7246, 38618, 27074, 7445, 16212, 42207, 48252, 34675, 20192,
20893, 17614, 18859, 26282, 40588, 32827, 47215, 14414, 17764, 27916, 16196, 23653, 17221, 9224, 45422, 12963, 23169, 19321, 40590, 33251,
26552, 51399, 6927, 27904, 51558, 61913, 38598, 36499, 14086, 53859, 23231, 51099, 20251, 12770, 61013, 37827, 4206, 35168, 34190, 47284,
5134, 59573, 30795, 6978, 14671, 9866, 23291, 46814, 64842, 25687, 43342, 57103, 39445, 7867, 31861, 64370, 53369, 23940, 47646, 5694,
35204, 45717, 46227, 60520, 45553, 64680, 24074, 6763, 58433, 49676, 1496, 63031, 58828, 23235, 31832, 60801, 23104, 56365, 40071, 45887,
1642, 32951, 41274, 16991, 11259, 51743, 61919, 33504, 20535, 19627, 12577, 3840, 33986, 28752, 42217, 61740, 58641, 32144, 1382, 58026,
14882, 61787, 6100, 12606, 3243, 18814, 38001, 1821, 2818, 52279, 7531, 54177, 38757, 1256, 30628, 46922, 30014, 16067, 57486, 50340,
11694, 32609, 64692, 8809, 48100, 5669, 24718, 42493, 23224, 55, 61784, 12581, 38726, 5798, 14200, 31505, 2837, 55151, 63378, 50210,
8988, 23282, 18935, 18879, 46596, 36625, 58861, 63462, 34716, 62920, 50880, 4417, 36366, 1032, 55349, 56566, 26176, 63976, 25094, 40320,
38553, 27963, 1236, 15477, 7653, 37347, 44343, 39476, 22021, 61567, 33553, 34283, 61562, 52077, 39825, 35078, 31995, 7670, 5652, 44457,
64155, 37691, 51998, 14782, 753, 39483, 17911, 23323, 30645, 57100, 31559, 35615, 10871, 32619, 2310, 8844, 45407, 16769, 44552, 20431,
11453, 41086, 9171, 49329, 40218, 48079, 44448, 25259, 39792, 28172, 6740, 2886, 25014, 46084, 49225, 38941, 60657, 64704, 32384, 7380,
51364, 12858, 51877, 54764, 20876, 64200, 36253, 56398, 49454, 46976, 16397, 54955, 32928, 55990, 9884, 41772, 50481, 11060, 29596, 17710,
56844, 14762, 35375, 18837, 55196, 5236, 34494, 45976, 54424, 25084, 11758, 12878, 63328, 4932, 36224, 8986, 60419, 21537, 27659, 30564,
63692, 55203, 9228, 16502, 1147, 60560, 22285, 48157, 23155, 40795, 43063, 22839, 19654, 5564, 37298, 23419, 30830, 28430, 28803, 9562,
61294, 36379, 41598, 9920, 29158, 50697, 42773, 45798, 4279, 2824, 22293, 48964, 60407, 5746, 57949, 43688, 58632, 11986, 19754, 58157,
2307, 28424, 64663, 50495, 41665, 60845, 25308, 61514, 63024, 492, 57772, 32470, 7703, 20269, 7308, 25320, 40329, 42339, 21937, 31192,
18391, 9309, 44599, 60427, 53155, 41080, 29715, 28373, 14947, 45940, 38227, 16249, 14792, 60512, 41420, 65063, 59902, 58583, 34351, 5413,
3795, 54661, 60292, 4666, 38012, 41776, 10153, 56816, 33422, 2644, 13828, 38428, 42376, 36740, 45736, 38623, 40869, 52545, 60904, 9301,
35249, 51923, 31392, 13724, 7045, 27701, 24123, 59827, 19573, 22771, 50704, 44137, 14809, 15969, 40816, 11514, 7107, 8621, 36613, 1415,
25449, 1233, 24994, 42985, 57399, 55539, 14208, 7173, 58562, 30232, 281, 63972, 54037, 63594, 38649, 20322, 48755, 58851, 3798, 28989,
23611, 16036, 39457, 13841, 14701, 13621, 23897, 15970, 476, 25156, 24165, 63727, 13209, 28967, 3463, 47547, 49198, 28285, 44077, 22079,
36584, 46297, 43255, 52980, 38752, 7743, 17486, 25319, 50313, 41521, 50674, 7966, 21648, 21927, 46633, 32902, 50591, 9750, 32181, 44644,
1650, 36325, 20038, 45345, 5918, 39573, 81, 56524, 21032, 25974, 48318, 59289, 60957, 39783, 35150, 6503, 51426, 52408, 64760, 21195,
44099, 49605, 5667, 53037, 9773, 27826, 63895, 26783, 20863, 46422, 27937, 1381, 58551, 63348, 39745, 29092, 6445, 43204, 21481, 62326,
23520, 34542, 57381, 17577, 64502, 16156, 18017, 40180, 56261, 40627, 62922, 19778, 58131, 3274, 8042, 59422, 33706, 38389, 48598, 10890,
21237, 1254, 51850, 64085, 34256, 58702, 2851, 6145, 42351, 50524, 27512, 23047, 35832, 27044, 60429, 20316, 47823, 34426, 9435, 24563,
43342, 31848, 42283, 2914, 17361, 63779, 30083, 4630, 21588, 53523, 56096, 43868, 55058, 6010, 8353, 59473, 19556, 10132, 36140, 38327,
22576, 3734, 56829, 51323, 318, 45319, 31091, 27582, 40903, 55650, 28944, 56485, 37837, 53046, 50437, 48479, 5598, 19115, 17958, 53597,
2431, 55778, 28400, 25121, 44857, 34881, 4223, 39174, 61900, 41407, 42997, 62270, 12194, 19827, 9326, 44878, 22924, 60208, 55284, 20014,
56781, 57501, 36502, 12751, 9198, 49983, 32070, 19991, 63909, 52354, 14284, 41728, 59347, 14428, 47130, 21502, 60062, 42033, 23528, 35108,
59068, 23444, 4190, 38671, 9367, 33495, 58796, 4664, 30945, 6050, 32816, 61774, 54916, 1332, 53470, 16518, 22510, 56144, 12255, 24813,
45477, 24196, 20367, 55610, 33606, 55890, 25570, 32125, 59855, 20588, 24974, 29239, 19162, 9431, 21715, 38352, 10505, 63736, 36640, 43179,
40219, 17458, 1090, 3555, 16807, 15587, 41805, 61905, 35067, 47869, 56628, 13780, 2365, 52918, 43065, 27419, 57277, 63237, 35505, 5665,
43354, 35258, 41173, 41657, 40791, 11594, 21747, 43710, 1701, 55724, 1495, 19989, 25213, 50784, 48720, 52958, 38076, 38914, 33360, 40307,
8991, 17952, 28612, 17649, 3429, 59789, 24895, 7154, 28958, 41423, 2186, 28042, 64119, 25158, 29237, 24020, 42161, 17868, 57972, 16725,
61196, 31531, 1426, 39024, 14229, 21080, 5337, 2363, 42411, 29968, 5794, 7321, 29026, 11083, 31036, 59724, 9075, 64488, 10028, 42852,
8906, 31013, 25619, 31079, 55865, 19002, 63203, 54781, 6613, 23395, 24408, 23682, 57214, 56387, 34489, 18770, 61000, 9465, 58307, 1688,
4227, 31706, 2744, 64627, 46858, 720, 32463, 24812, 34080, 4121, 5708, 54137, 14689, 56872, 30063, 20825, 25593, 2129, 6887, 17270,
48393, 14666, 39442, 26965, 41312, 62290, 57809, 46410, 20750, 46717, 43782, 55978, 43526, 46497, 60446, 39814, 6475, 18681, 60683, 15945,
52069, 14169, 9869, 53188, 47087, 4813, 26404, 61396, 39172, 682, 8739, 54949, 30250, 41915, 5467, 20395, 27168, 29503, 63874, 31004,
48378, 52086, 12363, 1025, 3731, 52548, 4167, 51463, 42844, 19987, 4141, 52844, 20754, 21828, 58754, 52118, 46319, 41477, 11336, 44692,
11454, 51913, 57531, 4033, 51645, 32122, 37696, 48232, 30715, 17697, 13950, 36673, 19762, 29602, 23268, 28569, 11143, 20428, 2489, 52354,
104, 5008, 26064, 19193, 49254, 29034, 53287, 35832, 54308, 24765, 57278, 31452, 20354, 61574, 44336, 55094, 57183, 3269, 4050, 7134,
34278, 22864, 11330, 6384, 41940, 62027, 380, 26646, 49299, 20081, 26152, 36415, 14482, 42163, 36506, 26239, 49701, 46378, 26898, 4696,
65141, 60106, 64300, 22882, 37608, 10111, 52474, 10000, 51723, 13365, 28148, 32281, 28947, 33699, 42823, 6495, 46295, 52493, 62029, 3960,
36775, 46956, 9469, 7101, 48781, 13393, 60332, 6194, 15742, 1034, 60892, 43725, 49811, 13823, 7817, 28381, 44249, 56600, 25194, 4405,
47948, 52611, 2211, 60236, 43779, 50095, 15811, 52316, 5037, 29163, 21897, 53353, 6663, 11770, 30828, 31351, 5822, 21607, 25236, 21732,
17870, 1665, 5064, 32492, 27923, 52332, 16129, 9153, 22618, 63514, 63464, 9107, 123, 39732, 20411, 41074, 5000, 24919, 49728, 62545,
45984, 28261, 57770, 42489, 32079, 32078, 57723, 39345, 59288, 8853, 38445, 18052, 56447, 38881, 21128, 15541, 21146, 11177, 57721, 64073,
48036, 45308, 12421, 37010, 9805, 47378, 29225, 47331, 10775, 48028, 4115, 20731, 9523, 10255, 1371, 53823, 17221, 41142, 9674, 11458,
40426, 52952, 7663, 16552, 63238, 28538, 37511, 52240, 49842, 59064, 49810, 34578, 23979, 65116, 39303, 9434, 26205, 8739, 37796, 27139,
53418, 54742, 18587, 10722, 34634, 15531, 20271, 54364, 3655, 4094, 54715, 454, 25828, 23452, 46222, 59413, 51241, 2651, 7767, 31114,
50655, 55682, 5769, 59837, 31690, 28976, 53728, 49677, 4832, 44585, 1800, 54222, 59653, 63779, 19880, 34584, 30940, 35962, 46461, 51420,
11534, 49987, 47401, 65323, 50682, 30282, 56336, 34693, 44601, 59604, 6783, 5423, 22195, 53406, 10281, 11907, 63005, 31926, 18189, 9939,
49161, 27329, 40547, 55535, 151, 17704, 15485, 26692, 47280, 36820, 2875, 45395, 46101, 20810, 32498, 49731, 30558, 50177, 8762, 53178,
32996, 23868, 32626, 3360, 41923, 20432, 23683, 59430, 45733, 43168, 36013, 34626, 40840, 45493, 59455, 48212, 9746, 62468, 48397, 40203,
61864, 3589, 33907, 48842, 20421, 27290, 30680, 26199, 46908, 30709, 12288, 29603, 65121, 31388, 47443, 37327, 38869, 26100, 38361, 34767,
65261, 8964, 64094, 45593, 6958, 42939, 15909, 20112, 9063, 14211, 49275, 12200, 20253, 55033, 30913, 65404, 48403, 59250, 2565, 26426,
15021, 37528, 13228, 6507, 53924, 14632, 11324, 37194, 37048, 61685, 4356, 62273, 39023, 4230, 56025, 3028, 58273, 15606, 63399, 37533,
55603, 19537, 48712, 18554, 23023, 33791, 65048, 26428, 45727, 47414, 21822, 20495, 44831, 42374, 36487, 33551, 2925, 62268, 25976, 39520,
13436, 10556, 13029, 8661, 2234, 57561, 40222, 19891, 41169, 52320, 54266, 36621, 48341, 16065, 9001, 46139, 16065, 743, 13088, 36821,
50018, 38385, 22597, 4377, 28557, 8642, 38609, 12385, 38820, 47511, 64379, 41270, 13384, 50703, 53120, 13495, 14295, 32576, 37559, 22291,
36764, 50537, 44891, 9188, 29871, 20383, 53098, 3935, 13268, 58781, 24834, 57527, 15043, 18120, 37707, 28621, 14700, 55400, 40855, 4850,
64813, 34755, 50579, 25279, 19636, 50369, 28822, 47978, 7733, 29372, 30353, 52644, 25819, 44177, 31752, 35303, 35717, 19757, 16960, 14817,
15384, 53456, 413, 8768, 24673, 17774, 31084, 19365, 57397, 46720, 292, 57368, 44976, 3539, 17897, 8667, 46982, 10627, 26640, 58688,
49529, 55159, 52008, 27059, 60977, 42327, 54967, 20871, 56944, 48375, 28721, 41248, 50678, 3257, 14841, 52281, 43661, 11843, 2184, 55080,
30572, 8347, 56951, 6940, 25663, 46229, 38529, 35792, 25987, 18053, 34934, 3108, 33605, 55780, 33717, 30885, 53010, 16023, 479, 22316,
53770, 29403, 15463, 17193, 34819, 64795, 460, 44277, 8075, 30126, 9491, 2288, 21731, 22356, 27973, 41105, 13010, 32148, 53860, 51019,
28227, 55493, 40572, 184, 58182, 45873, 51163, 29195, 21539, 34037, 21665, 28041, 39362, 28647, 32749, 36983, 55315, 47671, 121, 10531,
15621, 14368, 50505, 5399, 12031, 41431, 31251, 45834, 4879, 32199, 4424, 45988, 48511, 29876, 38309, 44059, 2427, 63815, 45544, 22539,
47133, 23241, 48231, 45227, 4629, 18010, 37844, 20785, 25922, 5418, 14500, 20733, 21269, 28760, 17938, 33445, 20197, 6853, 48784, 60866,
19008, 17832, 43684, 37389, 24238, 59210, 26020, 12761, 26155, 53388, 36616, 53592, 16475, 8876, 22185, 57622, 47781, 39199, 57466, 8948,
40152, 50132, 58054, 38480, 3159, 53262, 6238, 10019, 11103, 65217, 2579, 64510, 28963, 46820, 14058, 47891, 34010, 25325, 5316, 52266,
42156, 19051, 9908, 25427, 40268, 53762, 27310, 27700, 2596, 43314, 27261, 54978, 63060, 52622, 46683, 30355, 18999, 59127, 16356, 60488,
7734, 31804, 12352, 30648, 46910, 27216, 9527, 32973, 27021, 60517, 1647, 30496, 59642, 40156, 51872, 28, 65490, 57683, 18557, 63231,
18530, 59241, 47311, 14181, 23007, 8125, 19757, 37261, 4061, 27661, 65465, 15519, 35587, 1004, 20403, 3640, 30711, 442, 62609, 51211,
57278, 14956, 25790, 41517, 31582, 54864, 37788, 58506, 46501, 61510, 26479, 18884, 37108, 60245, 59621, 25610, 42417, 33117, 4602, 32158,
38022, 39882, 2334, 36696, 26331, 59982, 63496, 16918, 7760, 12110, 24023, 15023, 46858, 64018, 45881, 22970, 2786, 55099, 1423, 13604,
62448, 33381, 64527, 43383, 39703, 20789, 48358, 39593, 61497, 63329, 63755, 21301, 34617, 4981, 10540, 8004, 48850, 24, 42478, 46,
7537, 59059, 62501, 26279, 16207, 37393, 50876, 15860, 9029, 56910, 44904, 30852, 50049, 19916, 226, 11702, 23785, 14996, 8461, 54015,
62688, 13742, 46440, 31145, 32799, 31001, 63474, 17577, 48445, 56014, 44211, 24239, 15959, 5167, 4175, 48352, 32017, 9232, 46311, 59770,
33960, 30103, 43688, 40405, 62258, 8269, 6863, 41684, 10966, 22864, 47764, 3876, 43283, 47879, 59631, 59408, 28039, 56, 18032, 34344,
28274, 29405, 22825, 56616, 50010, 51925, 64735, 57553, 37853, 51372, 11228, 34819, 22554, 6269, 11458, 25560, 31731, 62023, 63374, 20605,
24497, 35475, 27826, 12067, 7897, 15951, 34962, 50, 43326, 58863, 54826, 4558, 30786, 23193, 30625, 53061, 7443, 20090, 23667, 36809,
34381, 25598, 35060, 56850, 36532, 43210, 43741, 10363, 16426, 62847, 37712, 20558, 13943, 8791, 40052, 5116, 16588, 59434, 9201, 52219,
11063, 17721, 29637, 6546, 10938, 23404, 1553, 20655, 46245, 12191, 63043, 26371, 38654, 20689, 53490, 44948, 21722, 6568, 36799, 16979,
32119, 13423, 47822, 36566, 18826, 21183, 22303, 25072, 50153, 16816, 63975, 20568, 31205, 26818, 42475, 2136, 15603, 21745, 44299, 25164,
26701, 19108, 13185, 22840, 47140, 12760, 41603, 16390, 51921, 28688, 4041, 60421, 23517, 18308, 13659, 27751, 20669, 20662, 32355, 51565,
11844, 12205, 25932, 41953, 55572, 38539, 2691, 54383, 9792, 2191, 53235, 14249, 15446, 34922, 12716, 17619, 60673, 16608, 37325, 5810,
40781, 29655, 1659, 65369, 2861, 5882, 2582, 45205, 15209, 56501, 2646, 29636, 55012, 61498, 53670, 23207, 5260, 34805, 4309, 2195,
49153, 60187, 64480, 13804, 61782, 56930, 23314, 17839, 34075, 18542, 43884, 29793, 54348, 22268, 198, 26396, 36404, 56582, 17335, 48596,
13993, 12384, 15899, 15356, 49904, 51426, 10464, 5347, 41503, 5763, 7052, 58820, 41830, 40644, 9897, 42272, 29578, 48131, 33862, 56257,
26832, 49717, 10763, 55642, 32504, 37196, 16351, 24386, 55455, 7526, 30892, 63502, 31329, 37959, 49675, 11630, 38837, 11602, 60723, 509,
7933, 27753, 31261, 21241, 14594, 26194, 16038, 20539, 61616, 20422, 51405, 37605, 37782, 10923, 64538, 19517, 11426, 12943, 58821, 10415,
56405, 41914, 47271, 1429, 5732, 31922, 8513, 6783, 10523, 36712, 10461, 9351, 64912, 59289, 53396, 17045, 24927, 346, 14655, 39467,
57265, 45838, 64016, 50815, 11063, 29768, 26062, 23334, 27468, 3561, 37166, 48039, 5828, 21347, 29469, 55593, 33206, 28075, 54808, 3862,
63010, 17977, 51805, 33870, 53916, 22012, 36648, 50291, 18211, 15096, 60116, 41259, 4847, 51377, 12436, 57735, 43703, 22176, 37835, 46020,
50543, 1309, 34222, 29284, 56501, 17737, 18480, 58365, 47427, 43594, 61509, 34845, 29787, 1011, 61696, 1959, 37461, 27310, 33452, 56878,
55246, 60413, 16124, 25447, 24351, 38863, 39989, 30714, 10451, 40950, 61257, 61257, 10456, 49374, 17743, 24080, 25347, 32285, 44016, 16407,
55403, 23759, 45843, 53234, 6856, 32362, 54258, 65436, 31261, 9128, 64941, 61232, 31486, 47917, 54781, 29866, 8806, 12639, 18210, 17089,
40599, 58083, 63075, 9613, 13039, 13541, 32688, 16396, 53541, 7485, 34738, 51725, 29227, 29999, 54727, 8871, 6282, 56508, 7017, 22370,
7891, 51462, 8832, 56133, 13687, 49448, 11977, 8845, 34867, 4337, 25985, 22677, 43809, 52652, 34601, 9009, 45742, 9339, 45229, 7412,
43651, 50484, 23323, 42120, 59039, 50853, 11226, 40896, 17033, 40302, 34525, 30910, 59910, 62762, 29198, 2502, 24765, 27011, 26690, 51845,
55197, 11429, 57638, 18247, 25719, 45300, 38926, 64959, 33696, 47467, 57364, 36160, 245, 5835, 12481, 34952, 44859, 36878, 8295, 28955,
59439, 45646, 61223, 57014, 50759, 20142, 26222, 60016, 32074, 52780, 63581, 36297, 46251, 31613, 43370, 59731, 29210, 11069, 44704, 60896,
58058, 20363, 22690, 56483, 59378, 30916, 51446, 51133, 27196, 36961, 49808, 3757, 57434, 25671, 32427, 5299, 62204, 64727, 396, 47971,
42536, 14139, 42594, 43072, 16651, 42360, 60602, 50735, 38253, 16588, 46110, 30965, 52514, 37555, 58848, 1949, 18499, 12481, 44741, 36609,
1263, 31929, 35621, 4038, 55487, 63202, 46779, 32741, 38519, 2802, 43787, 802, 42881, 65462, 20798, 49014, 8764, 8530, 32399, 28041,
55545, 40238, 15024, 5317, 26732, 3063, 35153, 23530, 44155, 49343, 31450, 24569, 59223, 15660, 21355, 28595, 65270, 32922, 3487, 1558,
12105, 1153, 52067, 43640, 64937, 23266, 14025, 46176, 17771, 31053, 5346, 53338, 59345, 1012, 63056, 9710, 10933, 3765, 50386, 56488,
62679, 48034, 7664, 34629, 48268, 42359, 43355, 49646, 25337, 25589, 63852, 33837, 17720, 16187, 61161, 49870, 7089, 2406, 36004, 62888,
1932, 60336, 7513, 51002, 28775, 41661, 46707, 2522, 58426, 33694, 38445, 61563, 17315, 23895, 64825, 8218, 34029, 46074, 48944, 17113,
34269, 27435, 39337, 47812, 35951, 43926, 15742, 43363, 2937, 53660, 28738, 11828, 29953, 11160, 47220, 65032, 46535, 50654, 29179, 59176,
17779, 52767, 48493, 54673, 20435, 65463, 55952, 26832, 7115, 55402, 12105, 36641, 11441, 45629, 25260, 43381, 63446, 56787, 9270, 20618,
54838, 27079, 10002, 26552, 3399, 65269, 13767, 20422, 29583, 15285, 41280, 4231, 27327, 34517, 7482, 10191, 18659, 39829, 47692, 54929,
26996, 7263, 40228, 24022, 48491, 16371, 61849, 45393, 40296, 61016, 2064, 24713, 51391, 37968, 6616, 47218, 711, 30022, 6762, 52927,
23878, 38242, 57668, 21540, 17487, 42599, 44513, 22336, 31017, 15047, 36748, 28638, 8364, 46709, 26574, 52240, 56088, 280, 8420, 31759,
31030, 32321, 32324, 22309, 65472, 2960, 43141, 45543, 62334, 49899, 15802, 54317, 26582, 41875, 61833, 45522, 55161, 39031, 63211, 7386,
15372, 48294, 62895, 32539, 63077, 22313, 57692, 14919, 26792, 25804, 20852, 55354, 26075, 63971, 5931, 22388, 43289, 38930, 30206, 56856,
2677, 62285, 3158, 41995, 36853, 33548, 36508, 33551, 52335, 503, 19320, 43092, 50089, 52921, 47017, 17594, 1817, 38267, 2387, 34506,
11298, 3443, 36189, 40829, 34093, 64470, 40085, 24914, 18309, 34919, 9305, 7769, 28696, 30152, 32046, 32246, 3988, 46755, 4005, 10281,
11210, 52975, 50190, 9488, 46777, 59052, 62180, 4229, 40808, 10643, 27313, 4918, 51755, 26787, 33274, 49400, 25088, 14505, 27757, 7369,
29551, 59684, 16765, 19526, 45048, 63471, 11681, 21735, 27731, 30642, 43877, 62898, 40896, 59132, 16529, 46318, 45503, 29949, 42120, 36609,
5488, 44757, 33752, 26947, 63319, 51301, 14981, 49543, 40903, 62504, 24662, 26232, 38441, 18698, 38050, 20012, 42463, 8843, 21395, 45186,
42110, 65383, 30335, 18930, 20466, 36408, 5167, 42243, 9365, 4458, 15426, 16003, 24775, 22805, 60557, 25086, 31444, 41282, 47088, 8136,
458, 53195, 36842, 51405, 32080, 33061, 61020, 37425, 54345, 27032, 48321, 61106, 11357, 51060, 24961, 11974, 59632, 17474, 24909, 53399,
36361, 25152, 55142, 57197, 4892, 55920, 14632, 18359, 64813, 57115, 33316, 62189, 11897, 39304, 51575, 5660, 17456, 64117, 26806, 57640,
15265, 46765, 23059, 24798, 47728, 30677, 23070, 61847, 40026, 56343, 55208, 37706, 26265, 35455, 23226, 52111, 60354, 54276, 38952, 7533,
41176, 60368, 5714, 15986, 41968, 53178, 2910, 26939, 23074, 58874, 63161, 27220, 9961, 13027, 49893, 35865, 20209, 24989, 3959, 53589,
53205, 63635, 30074, 39918, 765, 49727, 56230, 25239, 2501, 31965, 61496, 39308, 5636, 50789, 53264, 781, 16614, 6034, 48977, 34157,
44601, 43115, 25845, 8259, 63767, 23455, 50213, 32997, 10896, 42241, 28489, 25625, 42388, 55587, 31755, 22590, 36667, 24783, 27880, 55975,
50130, 20583, 31234, 47494, 15477, 39021, 24820, 44795, 7172, 50268, 64989, 60188, 272, 57953, 27752, 30489, 8778, 25276, 47338, 6600,
62561, 4043, 33131, 61775, 2964, 13033, 18296, 25668, 7908, 607, 29600, 48106, 21764, 4634, 58191, 53044, 63425, 53921, 21864, 37807,
18871, 46183, 55152, 1103, 62229, 51628, 3828, 38168, 63159, 47543, 20667, 45960, 58829, 41151, 39914, 51437, 24571, 4807, 35334, 50081,
56378, 34871, 54854, 4377, 25640, 65066, 63455, 64063, 49181, 40398, 2197, 19342, 2706, 18962, 35347, 19753, 37385, 6057, 3585, 39048,
6959, 31374, 55679, 45348, 31652, 47548, 57171, 41847, 32207, 6675, 20034, 25984, 49647, 10250, 14616, 39548, 29175, 35701, 47078, 34000,
51849, 29157, 34317, 28390, 19356, 182, 2056, 28518, 57638, 46299, 42457, 35518, 16515, 60855, 16034, 33393, 9361, 60017, 8326, 3206,
48573, 39666, 481, 35414, 15879, 10175, 31359, 35587, 43188, 3239, 25375, 24732, 36401, 36606, 36087, 26359, 17249, 58460, 5383, 1801,
47253, 5905, 41532, 62988, 40803, 62508, 13321, 45310, 51939, 12540, 21801, 23761, 20852, 34111, 36164, 46073, 21977, 44957, 19948, 55010,
53397, 23747, 39068, 61852, 56210, 58123, 25685, 22115, 60218, 34292, 7325, 61930, 5996, 62739, 5697, 27517, 32381, 30393, 11623, 34713,
3264, 4000, 6743, 32982, 20355, 42829, 64415, 10704, 22057, 21189, 40601, 10466, 45412, 60258, 1312, 24682, 21128, 49188, 29633, 27524,
57614, 60638, 13997, 39880, 23710, 52284, 55472, 47528, 11552, 21837, 59795, 21151, 50869, 50520, 22179, 12922, 30681, 44540, 45179, 46516,
31759, 17116, 6854, 30600, 565, 25461, 38421, 22346, 58328, 30149, 32110, 37329, 23875, 113, 21912, 54743, 38813, 34880, 58399, 16783,
33745, 32808, 17374, 25858, 23442, 54261, 44017, 7996, 27570, 18193, 62356, 27600, 5640, 7481, 13181, 22000, 35070, 46317, 1891, 57531,
9339, 43048, 40775, 5227, 52340, 32129, 21098, 53208, 56452, 20792, 374, 23408, 38590, 51745, 13790, 13382, 53102, 14584, 49527, 35851,
34947, 20122, 47532, 3739, 34978, 55212, 51025, 50607, 65449, 26046, 61226, 52424, 62253, 14545, 61569, 194, 5725, 4967, 910, 2237,
21638, 35184, 1107, 51428, 31739, 29203, 57399, 8234, 62148, 34522, 21920, 64749, 50425, 62858, 29386, 40138, 5026, 30011, 28282, 18974,
53834, 13834, 3698, 18601, 22352, 48676, 1950, 39844, 46397, 46165, 42129, 34820, 31517, 39599, 51728, 22926, 1862, 46825, 10417, 28376,
47389, 10263, 61266, 12674, 42491, 14257, 33522, 60073, 22939, 61911, 6794, 33476, 24720, 64907, 8919, 26619, 36567, 20401, 8842, 24880,
60754, 43750, 59065, 64034, 32122, 43915, 32108, 56449, 54004, 4056, 36525, 38502, 38483, 63337, 60527, 1349, 10271, 48850, 15673, 40826,
13051, 24618, 52106, 14009, 18133, 30920, 41488, 53063, 34954, 8586, 9213, 16432, 13519, 34072, 57752, 2463, 61389, 35816, 28475, 30407,
22361, 17092, 49868, 32389, 29920, 22235, 45330, 36184, 23720, 25699, 40250, 16730, 42084, 3886, 62551, 64416, 51370, 27849, 1424, 50369,
17282, 34642, 25906, 29310, 22337, 38438, 3732, 60431, 32228, 3470, 28067, 20028, 12111, 35758, 51247, 98, 32921, 1256, 48323, 53183,
46637, 18949, 23750, 39036, 4343, 30724, 2533, 2641, 9578, 12388, 16900, 5135, 59729, 15261, 14403, 54876, 33311, 12173, 1061, 39196,
176, 35351, 35627, 35298, 24838, 17690, 65259, 18459, 27825, 52889, 49416, 2526, 38539, 56359, 4191, 23096, 62998, 44751, 35351, 30365,
49592, 16478, 50486, 37299, 43052, 26289, 63937, 28986, 45077, 48768, 60387, 42425, 42680, 64585, 64041, 22062, 23077, 65009, 52183, 3059,
59019, 7060, 44476, 32105, 2781, 11088, 34169, 37156, 10880, 10742, 57543, 4576, 5174, 59765, 6498, 41389, 2012, 14683, 52319, 40450,
19476, 37847, 64216, 21138, 22194, 25473, 23711, 8157, 6988, 4752, 45085, 44482, 17179, 47367, 41628, 32170, 40453, 30517, 22724, 22628,
287, 39051, 42244, 51681, 11025, 37803, 47437, 45430, 2280, 4879, 5413, 1839, 19463, 48332, 50743, 44754, 42038, 9817, 56457, 22663,
58868, 56112, 3398, 14882, 7727, 53665, 31408, 3566, 21642, 11199, 14472, 26820, 27646, 35392, 10708, 13556, 7040, 63033, 56080, 61417,
7795, 60425, 20889, 60669, 149, 63288, 56089, 31255, 62201, 40844, 55269, 37897, 12941, 9519, 35751, 55501, 64465, 40803, 24615, 32924,
17002, 2970, 65310, 62523, 23776, 43849, 11982, 30370, 41100, 31339, 58173, 37253, 61959, 48215, 16577, 16218, 64831, 56689, 48819, 53550,
11412, 5072, 31966, 34303, 3148, 42808, 55427, 61702, 41057, 54554, 2609, 35023, 50135, 20587, 37714, 53941, 5687, 33109, 12718, 53788,
56637, 15451, 25630, 1003, 20322, 43033, 34110, 34561, 29166, 8107, 27984, 63303, 24117, 7683, 5602, 27492, 30733, 42372, 25990, 42598,
10131, 33434, 47706, 41279, 57367, 21010, 23543, 59822, 4309, 19787, 39922, 28605, 11711, 54522, 48746, 1235, 17051, 29230, 23282, 20805,
60856, 21529, 18430, 61978, 52934, 22221, 21612, 57841, 2892, 62446, 7705, 35669, 32099, 30163, 38670, 23771, 34145, 49290, 65467, 10999,
1178, 2856, 51415, 29627, 59923, 31895, 2289, 55274, 9648, 15887, 2707, 41729, 35728, 62010, 37485, 16991, 37927, 57233, 34923, 35291,
34486, 61519, 10463, 9660, 52622, 59575, 31688, 31324, 54881, 25250, 31006, 9372, 53698, 39135, 36629, 32723, 45375, 18569, 15368, 27002,
42175, 65211, 33954, 11767, 60018, 56629, 37649, 32715, 17738, 34959, 34174, 18580, 739, 25918, 31563, 11430, 23697, 37042, 59480, 24759,
42502, 22786, 1816, 42954, 25492, 1840, 23188, 54512, 64254, 64552, 52725, 38282, 23598, 12129, 53034, 14227, 2613, 26867, 48111, 43851,
64340, 53131, 48856, 56876, 5629, 33597, 18190, 37780, 46361, 55075, 33564, 1764, 41223, 60708, 33133, 24464, 63410, 32862, 56693, 61226,
42737, 40354, 18537, 51862, 62259, 13964, 28015, 62506, 65017, 59361, 1086, 13524, 60417, 60020, 34852, 56634, 33443, 11456, 5951, 44155,
21571, 17732, 50753, 17653, 5772, 32065, 30548, 29644, 7037, 17097, 30694, 61478, 29887, 39706, 29638, 19230, 27105, 26588, 32822, 61599,
564, 51817, 61814, 33331, 13640, 24157, 29106, 21829, 28917, 42021, 55535, 32658, 60669, 1985, 6519, 40126, 381, 17609, 57555, 31457,
39453, 61268, 47368, 12851, 41309, 35132, 60337, 64116, 57206, 14464, 39287, 34544, 589, 36536, 14860, 64468, 40192, 36141, 15357, 4612,
65534, 29224, 2866, 52884, 54553, 39445, 60952, 32552, 36242, 37226, 60717, 35017, 54005, 28999, 22891, 29370, 15789, 43715, 19917, 63518,
12365, 9046, 3238, 10241, 33609, 54359, 34346, 42403, 24300, 55689, 24366, 59636, 11404, 50041, 42586, 61208, 21014, 29754, 38378, 37884,
34461, 40827, 40859, 23256, 8546, 29895, 3697, 6128, 59417, 51877, 42889, 55692, 6716, 24346, 60840, 60059, 62467, 57689, 19865, 60392,
8842, 48368, 2992, 43709, 54612, 2824, 58056, 61390, 32105, 423, 45147, 42336, 31046, 35732, 56952, 53719, 24471, 26149, 23019, 28441,
48673, 45434, 12980, 2933, 64796, 37294, 479, 25613, 39200, 6398, 64643, 32899, 3914, 26237, 35470, 38240, 2967, 13903, 4925, 20058,
36495, 37994, 51512, 48906, 4879, 37107, 34507, 1942, 15253, 61104, 12424, 50257, 34470, 6970, 30416, 41929, 22584, 61128, 23027, 64956,};
*/
