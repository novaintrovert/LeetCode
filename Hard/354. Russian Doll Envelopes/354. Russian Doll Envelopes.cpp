/*354. Russian Doll Envelopes
Hard

You have a number of envelopes with widths and heights given as a pair of integers (w, h).
One envelope can fit into another if and only if
both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Note:
Rotation is not allowed.

Input: [[5,4],[6,4],[6,7],[2,3]]
Output: 3
Explanation:
The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
*/

/*
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {

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

    /*while (count_dif_width > 1) {
        count_curr = 1;

        curr_width = dolls[distinct_width_starting_idx[count_dif_width - 1]][0];
        curr_height = dolls[distinct_width_starting_idx[count_dif_width - 1]][1];
        for (int i = count_dif_width - 1; i > 0; i--) {
            curr_idx = distinct_width_starting_idx[i];
            next_idx = distinct_width_starting_idx[i - 1];

            if (dolls[next_idx][1] < dolls[curr_idx][1]) {
                curr_width = dolls[next_idx][0];
                curr_height = dolls[next_idx][1];
                count_curr++;
            }

            else if (((next_idx > 0)&&(dolls[distinct_width_starting_idx[next_idx - 1] + 1][1] >= curr_height))
                    ||(dolls[0][1] >= curr_height)) {
                continue;
            }

            else {
                left = distinct_width_starting_idx[next_idx - 1] + 1, right = curr_idx, mid;
                while (left < right) {
                    if (left + 1 == right) {break;}
                    mid = (left + right) / 2;
                    if (dolls[mid][1] < curr_height) {left = mid;}
                    else {right = mid;}
                }
                curr_width = dolls[left][0];
                curr_height = dolls[left][1];
                count_curr++;
            }
        }

        if (count_curr > maximum) {maximum = count_curr;}

        count_dif_width--;
    }*/



void merge_sort (vector<vector<int>> &a) {//20201206
    int length = a.size();
    vector<vector<int>> b(a);
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

                    else if (a[i][0] <= a[j][0]) {
                        b[k][0] = a[i][0], b[k][1] = a[i][1];
                        i++, i_step++;
                    }

                    else if (a[i][0] > a[j][0]) {
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

                    else if (b[i][0] <= b[j][0]) {
                        a[k][0] = b[i][0], a[k][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][0] > b[j][0]) {
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
void merge_sort_2nd_idx (vector<vector<int>> &a, int left, int right) {//20201206
    int range_length = right - left + 1;
    int b[range_length][2];
    for (int i = 0; i < range_length; i++) {b[i][0] = a[i + left][0], b[i][1] = a[i + left][1];}

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < range_length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < range_length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= range_length) {
                    for (int k = i; k < range_length; k++) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
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
                            b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
                        j++, j_step++;
                    }

                    else if (a[i + left][1] <= a[j + left][1]) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                        i++, i_step++;
                    }

                    else if (a[i + left][1] > a[j + left][1]) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
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
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
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
                            a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][1] <= b[j][1]) {
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][1] > b[j][1]) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
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
void probe_this (vector<vector<int>> &dolls, vector<int> &distinct_width_starting_idx,
                int width, int height, int &maximum, int count_curr, int curr_idx) {

    if (count_curr + curr_idx + 1 > maximum) {
        if (width < 0) {
            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            probe_this (dolls, distinct_width_starting_idx,
                    dolls[distinct_width_starting_idx[curr_idx]][0],
                    dolls[distinct_width_starting_idx[curr_idx]][1],
                    maximum, count_curr + 1, curr_idx - 1);
        }

        else {
            int next_idx_in_doll = (curr_idx > 0)? distinct_width_starting_idx[curr_idx - 1] + 1: 0;

            if (dolls[next_idx_in_doll][1] < height) {
                int left = next_idx_in_doll, right = distinct_width_starting_idx[curr_idx], mid;

                if (dolls[right][1] < height) {left = right;}

                else {
                    while (left < right) {
                        if (left + 1 == right) {break;}

                        mid = (left + right) / 2;

                        if (dolls[mid][1] < height) {left = mid;}

                        else {right = mid;}
                    }
                }

                if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

                probe_this (dolls, distinct_width_starting_idx,
                    dolls[left][0], dolls[left][1], maximum, count_curr + 1, curr_idx - 1);
            }
        }

        probe_this (dolls, distinct_width_starting_idx,
            width, height, maximum, count_curr, curr_idx - 1);
    }
}
int maxEnvelopes(vector<vector<int>>& envelopes) {
    int length = envelopes.size();
    if (length <= 0) {return 0;}
    if (length == 1) {return 1;}

    //int test_timer = -1;

    vector<vector<int>> dolls (length, vector<int> (2, 0));
    for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    merge_sort(dolls);

    /*if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n";
    }*/

    int count_dif_width = 1, temp = dolls[length - 1][0];
    stack<int> dif_idx;
    dif_idx.push(length - 1);
    for (int i = length - 2; i >= 0; i--) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
            //if (test_timer >= 0) {cout << "pushed " << i << "\n";}
        }
    }

    //if (test_timer >= 0) {cout << "\ncount_dif_width = " << count_dif_width << "\n\n";}

    vector<int> distinct_width_starting_idx(count_dif_width, 0);
    for (int i = 0; i < count_dif_width; i++) {
        distinct_width_starting_idx[i] = dif_idx.top();
        dif_idx.pop();
    }

    int left, right, mid;
    for (int i = count_dif_width - 1; i >= 0; i--) {
        left = (i > 0)? distinct_width_starting_idx[i - 1] + 1: 0;
        right = distinct_width_starting_idx[i];

        merge_sort_2nd_idx(dolls, left, right);
    }

    /*if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << distinct_width_starting_idx[i] << ", ";
        }
        cout << "\n\n";
        for (int i = 0; i < length; i++) {
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n";
    }*/

    int maximum = 0, count_curr = 0, curr_idx = count_dif_width - 1;
    int width = -1, height = -1;

    probe_this (dolls, distinct_width_starting_idx,
                width, height, maximum, count_curr, curr_idx);

    return maximum;
}



void merge_sort_1 (int a[][2], int length) {//20201206
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

                    else if (a[i][0] <= a[j][0]) {
                        b[k][0] = a[i][0], b[k][1] = a[i][1];
                        i++, i_step++;
                    }

                    else if (a[i][0] > a[j][0]) {
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

                    else if (b[i][0] <= b[j][0]) {
                        a[k][0] = b[i][0], a[k][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][0] > b[j][0]) {
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
void merge_sort_2nd_idx_1 (int a[][2], int left, int right) {//20201206
    int range_length = right - left + 1;
    int b[range_length][2];
    for (int i = 0; i < range_length; i++) {b[i][0] = a[i + left][0], b[i][1] = a[i + left][1];}

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < range_length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < range_length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= range_length) {
                    for (int k = i; k < range_length; k++) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
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
                            b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
                        j++, j_step++;
                    }

                    else if (a[i + left][1] <= a[j + left][1]) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                        i++, i_step++;
                    }

                    else if (a[i + left][1] > a[j + left][1]) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
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
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
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
                            a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][1] <= b[j][1]) {
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][1] > b[j][1]) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
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
void brute_probe (int dolls[][2], int length, int distinct_width_starting_idx[], int count_dif_width,
                int width, int height, int &maximum, int count_curr, int curr_idx) {

    if (count_curr + curr_idx + 1 > maximum) {
        //with current doll, if possible
        if (width < 0) {
            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            brute_probe (dolls, length, distinct_width_starting_idx, count_dif_width,
                        dolls[distinct_width_starting_idx[curr_idx]][0],
                        dolls[distinct_width_starting_idx[curr_idx]][1],
                        maximum, count_curr + 1, curr_idx - 1);
        }

        else {
            int next_idx_of_dolls = (curr_idx > 0)? distinct_width_starting_idx[curr_idx - 1] + 1: 0;

            if (dolls[next_idx_of_dolls][1] < height) {
                int left, right, mid;

                if (dolls[distinct_width_starting_idx[curr_idx]][1] < height) {
                    left = distinct_width_starting_idx[curr_idx];
                }

                else {
                    left = next_idx_of_dolls, right = distinct_width_starting_idx[curr_idx];

                    while (left < right) {
                        if (left + 1 == right) {break;}

                        mid = (left + right) / 2;

                        if (dolls[mid][1] < height) {left = mid;}

                        else {right = mid;}
                    }
                }


                if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

                brute_probe (dolls, length, distinct_width_starting_idx, count_dif_width,
                        dolls[left][0], dolls[left][1], maximum, count_curr + 1, curr_idx - 1);

            }
        }

        //without current doll
        brute_probe (dolls, length, distinct_width_starting_idx, count_dif_width,
                    width, height, maximum, count_curr, curr_idx - 1);
    }
}
int maxEnvelopes_brute(vector<vector<int>>& envelopes) {
    int length = envelopes.size();
    if (length <= 0) {return 0;}
    if (length == 1) {return 1;}

    int dolls[length][2];
    for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    merge_sort_1(dolls, length);

    int count_dif_width = 1, temp = dolls[length - 1][0];
    stack<int> dif_idx;
    dif_idx.push(length - 1);
    for (int i = length - 2; i >= 0; i--) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    int distinct_width_starting_idx[count_dif_width];
    for (int i = 0; i < count_dif_width; i++) {
        distinct_width_starting_idx[i] = dif_idx.top();
        dif_idx.pop();
    }

    int left, right, mid;
    for (int i = count_dif_width - 1; i >= 0; i--) {
        left = (i > 0)? distinct_width_starting_idx[i - 1] + 1: 0;
        right = distinct_width_starting_idx[i];

        merge_sort_2nd_idx_1(dolls, left, right);
    }

    int maximum = 0, count_curr = 0, curr_idx = count_dif_width - 1;
    int width = -1, height = -1;

    brute_probe (dolls, length, distinct_width_starting_idx, count_dif_width,
                    -1, -1, maximum, count_curr, curr_idx);

    return maximum;
}



void brute_probe_1 (int dolls[][2], int length, int distinct_width_starting_idx[], int count_dif_width,
                int already_contained_largest[], int width, int height, int &maximum, int count_curr, int curr_idx) {

    if ((count_curr + curr_idx + 1 > maximum)&&(maximum < count_dif_width)) {
        //with current doll, if possible
        already_contained_largest[curr_idx] == 1;
        if (width >= 0) {
            int next_idx_of_dolls = (curr_idx > 0)? distinct_width_starting_idx[curr_idx - 1] + 1: 0;

            if (dolls[next_idx_of_dolls][1] < height) {
                int left, right, mid;

                if (dolls[distinct_width_starting_idx[curr_idx]][1] < height) {
                    left = distinct_width_starting_idx[curr_idx];
                    already_contained_largest[curr_idx - 1] = 1;
                }

                else {
                    left = next_idx_of_dolls, right = distinct_width_starting_idx[curr_idx];

                    while (left < right) {
                        if (left + 1 == right) {break;}

                        mid = (left + right) / 2;

                        if (dolls[mid][1] < height) {left = mid;}

                        else {right = mid;}
                    }
                }

                if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

                brute_probe_1 (dolls, length, distinct_width_starting_idx, count_dif_width,
                        already_contained_largest, dolls[left][0], dolls[left][1],
                        maximum, count_curr + 1, curr_idx - 1);

            }
        }

        else {
            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            brute_probe_1 (dolls, length, distinct_width_starting_idx, count_dif_width,
                        already_contained_largest,
                        dolls[distinct_width_starting_idx[curr_idx]][0],
                        dolls[distinct_width_starting_idx[curr_idx]][1],
                        maximum, count_curr + 1, curr_idx - 1);
        }

        if (count_curr + curr_idx > maximum) {
            //without current doll
            brute_probe_1 (dolls, length, distinct_width_starting_idx, count_dif_width,
                        already_contained_largest, width, height, maximum, count_curr, curr_idx - 1);
        }
    }
}
void brute_probe_2 (int dolls[][2], int length, int distinct_width_left_idx[], int count_dif_width,
                int already_included[], int width, int height, int &maximum, int count_curr, int curr_idx) {

    int test_timer = -1;
    if (test_timer >= 0) {
        cout << "\nwidth = " << width << ", height = " << height << ", maximum = " << maximum << ", count_curr = " << count_curr;
        cout << ", curr_idx = " << curr_idx << ", distinct_width_left_idx[curr_idx] = " << distinct_width_left_idx[curr_idx] << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << already_included[i] << ", ";
        }
        cout << "\n";
    }

    if ((curr_idx < count_dif_width)&&(count_dif_width - 1 - curr_idx + 1 + count_curr > maximum)){
        //with current doll, if possible
        if (width >= 0) {
            int next_idx_of_dolls = (curr_idx < count_dif_width - 1)? distinct_width_left_idx[curr_idx + 1] - 1: length - 1;

            if (dolls[next_idx_of_dolls][1] > height) {
                int left, right, mid;

                if (dolls[distinct_width_left_idx[curr_idx]][1] > height) {
                    left = distinct_width_left_idx[curr_idx];
                    already_included[curr_idx] = 1;
                }

                else {
                    left = distinct_width_left_idx[curr_idx], right = next_idx_of_dolls;

                    int one_more = 1;
                    while (left <= right) {
                        mid = (left + right) / 2;

                        if (dolls[mid][1] <= height) {left = mid + 1;}

                        else {right = mid;}

                        if (one_more == 0) {break;}
                        if (left + 1 >= right) {one_more = 0;}
                    }
                }

                if (test_timer >= 0) {cout << "left = " << left << "\n";}

                if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

                brute_probe_2 (dolls, length, distinct_width_left_idx, count_dif_width,
                        already_included, dolls[left][0], dolls[left][1],
                        maximum, count_curr + 1, curr_idx + 1);
            }
        }

        else {
            already_included[curr_idx] = 1;

            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            brute_probe_2 (dolls, length, distinct_width_left_idx, count_dif_width,
                        already_included,
                        dolls[distinct_width_left_idx[curr_idx]][0],
                        dolls[distinct_width_left_idx[curr_idx]][1],
                        maximum, count_curr + 1, curr_idx + 1);

            brute_probe_2 (dolls, length, distinct_width_left_idx, count_dif_width,
                        already_included, width, height, maximum, count_curr, curr_idx + 1);
        }

        if (test_timer >= 0) {
            cout << "\ncurr_idx = " << curr_idx << ", count_curr = " << count_curr << "\n";
            cout << "count_dif_width - 1 - curr_idx - 1 + 1 + count_curr = " << count_dif_width - 1 - curr_idx - 1 + 1 + count_curr << "\n";
        }

        //if ((already_included[curr_idx + 1] == 0)&&(count_dif_width - 1 - curr_idx - 1 + 1 + count_curr > maximum)) {
        //without current doll
        brute_probe_2 (dolls, length, distinct_width_left_idx, count_dif_width,
                    already_included, width, height, maximum, count_curr, curr_idx + 1);

    }
}
//failure. too slow
int maxEnvelopes_brute_1(vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int test_timer = -1;
    int dolls[length][2];
    for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    merge_sort_1(dolls, length);

    /*if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n";
    }*/

    int count_dif_width = 1;
    //int temp = dolls[length - 1][0];
    stack<int> dif_idx;
    /*dif_idx.push(length - 1);
    for (int i = length - 2; i >= 0; i--) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }*/

    int temp = dolls[0][0];
    dif_idx.push(0);
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    if (test_timer >= 0) {cout << "\ncount_dif_width = " << count_dif_width << "\n\n";}

    if (count_dif_width == 1) {return 1;}

    /*int distinct_width_starting_idx[count_dif_width];
    for (int i = 0; i < count_dif_width; i++) {
        distinct_width_starting_idx[i] = dif_idx.top();
        dif_idx.pop();
    }*/

    int distinct_width_left_idx[count_dif_width];
    for (int i = count_dif_width - 1; i >= 0; i--) {
        distinct_width_left_idx[i] = dif_idx.top();
        dif_idx.pop();
    }

    int left, right, mid;
    /*for (int i = count_dif_width - 1; i >= 0; i--) {
        left = (i > 0)? distinct_width_starting_idx[i - 1] + 1: 0;
        right = distinct_width_starting_idx[i];

        merge_sort_2nd_idx_1(dolls, left, right);
    }*/

    for (int i = 0; i < count_dif_width; i++) {
        left = distinct_width_left_idx[i];
        right = (i < count_dif_width - 1)? distinct_width_left_idx[i + 1] - 1: length - 1;

        merge_sort_2nd_idx_1(dolls, left, right);
    }

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << distinct_width_left_idx[i] << ", ";
        }
        cout << "\n";
        for (int i = 0, j = 0; (i < length)&&(j < count_dif_width); i++) {
            if (i == distinct_width_left_idx[j]) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n";
    }

    //int already_contained_largest[count_dif_width];
    //for (int i = 0; i < count_dif_width; i++) {already_contained_largest[i] = 0;}

    int already_included[count_dif_width];
    for (int i = 0; i < count_dif_width; i++) {already_included[i] = 0;}

    int maximum = 0;
    //int width = -1, height = -1, count_curr = 0, curr_idx = count_dif_width - 1;

    /*brute_probe_1 (dolls, length, distinct_width_starting_idx, count_dif_width,
                   already_contained_largest, -1, -1, maximum, 0, count_dif_width - 1);*/

    //already_included[0] = 1;
    brute_probe_2 (dolls, length, distinct_width_left_idx, count_dif_width,
                already_included, -1, -1, maximum, 0, 0);

    return maximum;
}



void brute_probe_3 (int dolls[][2], int length, int distinct_width_left_idx[], int count_dif_width,
                int already_included[][2], int width, int height, int &maximum, int count_curr, int curr_idx) {

    int test_timer = -1;
    if (test_timer >= 0) {
        cout << "\nwidth = " << width << ", height = " << height << ", maximum = " << maximum << ", count_curr = " << count_curr;
        cout << ", curr_idx = " << curr_idx << ", distinct_width_left_idx[curr_idx] = " << distinct_width_left_idx[curr_idx] << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << already_included[i] << ", ";
        }
        cout << "\n";
    }

    if ((curr_idx < count_dif_width)&&(count_dif_width - 1 - curr_idx + 1 + count_curr > maximum)){
        //with current doll, if possible
        if (width >= 0) {
            int next_idx_of_dolls = (curr_idx < count_dif_width - 1)? distinct_width_left_idx[curr_idx + 1] - 1: length - 1;

            if (dolls[next_idx_of_dolls][1] > height) {
                int left, right, mid;

                if (dolls[distinct_width_left_idx[curr_idx]][1] > height) {
                    left = distinct_width_left_idx[curr_idx];
                    //already_included[curr_idx] = 1;
                }

                else {
                    left = distinct_width_left_idx[curr_idx], right = next_idx_of_dolls;

                    int one_more = 1;
                    while (left <= right) {
                        mid = (left + right) / 2;

                        if (dolls[mid][1] <= height) {left = mid + 1;}

                        else {right = mid;}

                        if (one_more == 0) {break;}
                        if (left + 1 >= right) {one_more = 0;}
                    }
                }

                if (test_timer >= 0) {cout << "left = " << left << "\n";}

                if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

                brute_probe_3 (dolls, length, distinct_width_left_idx, count_dif_width,
                        already_included, dolls[left][0], dolls[left][1],
                        maximum, count_curr + 1, curr_idx + 1);
            }
        }

        else {
            already_included[curr_idx][0] = 1;

            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            brute_probe_3 (dolls, length, distinct_width_left_idx, count_dif_width,
                        already_included,
                        dolls[distinct_width_left_idx[curr_idx]][0],
                        dolls[distinct_width_left_idx[curr_idx]][1],
                        maximum, count_curr + 1, curr_idx + 1);

            brute_probe_3 (dolls, length, distinct_width_left_idx, count_dif_width,
                        already_included, width, height, maximum, count_curr, curr_idx + 1);
        }

        if (test_timer >= 0) {
            cout << "\ncurr_idx = " << curr_idx << ", count_curr = " << count_curr << "\n";
            cout << "count_dif_width - 1 - curr_idx - 1 + 1 + count_curr = " << count_dif_width - 1 - curr_idx - 1 + 1 + count_curr << "\n";
        }

        if (((already_included[curr_idx + 1][0] == 0)||((already_included[curr_idx + 1][0] != 0)&&(already_included[curr_idx + 1][1] < count_curr + 1)))
            &&(count_dif_width - 1 - curr_idx - 1 + 1 + count_curr > maximum)) {
        //without current doll
            brute_probe_3 (dolls, length, distinct_width_left_idx, count_dif_width,
                        already_included, width, height, maximum, count_curr, curr_idx + 1);
        }
    }
}
//failure. too slow
int maxEnvelopes_brute_2(vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int test_timer = -1;
    int dolls[length][2];
    for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    merge_sort_1(dolls, length);

    /*if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n";
    }*/

    int count_dif_width = 1;
    //int temp = dolls[length - 1][0];
    stack<int> dif_idx;
    /*dif_idx.push(length - 1);
    for (int i = length - 2; i >= 0; i--) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }*/

    int temp = dolls[0][0];
    dif_idx.push(0);
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    if (test_timer >= 0) {cout << "\ncount_dif_width = " << count_dif_width << "\n\n";}

    if (count_dif_width == 1) {return 1;}

    /*int distinct_width_starting_idx[count_dif_width];
    for (int i = 0; i < count_dif_width; i++) {
        distinct_width_starting_idx[i] = dif_idx.top();
        dif_idx.pop();
    }*/

    int distinct_width_left_idx[count_dif_width];
    for (int i = count_dif_width - 1; i >= 0; i--) {
        distinct_width_left_idx[i] = dif_idx.top();
        dif_idx.pop();
    }

    int left, right, mid;
    /*for (int i = count_dif_width - 1; i >= 0; i--) {
        left = (i > 0)? distinct_width_starting_idx[i - 1] + 1: 0;
        right = distinct_width_starting_idx[i];

        merge_sort_2nd_idx_1(dolls, left, right);
    }*/

    for (int i = 0; i < count_dif_width; i++) {
        left = distinct_width_left_idx[i];
        right = (i < count_dif_width - 1)? distinct_width_left_idx[i + 1] - 1: length - 1;

        merge_sort_2nd_idx_1(dolls, left, right);
    }

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << distinct_width_left_idx[i] << ", ";
        }
        cout << "\n";
        for (int i = 0, j = 0; (i < length)&&(j < count_dif_width); i++) {
            if (i == distinct_width_left_idx[j]) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n";
    }

    //int already_contained_largest[count_dif_width];
    //for (int i = 0; i < count_dif_width; i++) {already_contained_largest[i] = 0;}

    int already_included[count_dif_width][2];
    for (int i = 0; i < count_dif_width; i++) {already_included[i][0] = 0, already_included[i][1] = 0;}

    int maximum = 0;
    //int width = -1, height = -1, count_curr = 0, curr_idx = count_dif_width - 1;

    /*brute_probe_1 (dolls, length, distinct_width_starting_idx, count_dif_width,
                   already_contained_largest, -1, -1, maximum, 0, count_dif_width - 1);*/

    //already_included[0] = 1;
    brute_probe_3 (dolls, length, distinct_width_left_idx, count_dif_width,
                already_included, -1, -1, maximum, 0, 0);

    return maximum;
}





void merge_sort_2 (int a[][2], int length) {//20201206
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

                    else if (a[i][0] <= a[j][0]) {
                        b[k][0] = a[i][0], b[k][1] = a[i][1];
                        i++, i_step++;
                    }

                    else if (a[i][0] > a[j][0]) {
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

                    else if (b[i][0] <= b[j][0]) {
                        a[k][0] = b[i][0], a[k][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][0] > b[j][0]) {
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
void merge_sort_2nd_idx_2 (int a[][2], int left, int right) {//20201206
    int range_length = right - left + 1;
    int b[range_length][2];
    for (int i = 0; i < range_length; i++) {b[i][0] = a[i + left][0], b[i][1] = a[i + left][1];}

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < range_length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < range_length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= range_length) {
                    for (int k = i; k < range_length; k++) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
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
                            b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
                        j++, j_step++;
                    }

                    else if (a[i + left][1] <= a[j + left][1]) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                        i++, i_step++;
                    }

                    else if (a[i + left][1] > a[j + left][1]) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
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
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
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
                            a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][1] <= b[j][1]) {
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][1] > b[j][1]) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
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
//max_length_starting_from_this_idx, -1 means have not probed yet
void probe_it (int dolls[][2], int max_length_starting_from_this_idx[], int length,
               int distinct_width_left_idx[], int count_dif_width,
               stack<int> &curr_path, stack<int> &remaining_path,
               int width, int height,
               int &maximum, int count_curr, int last_idx, int curr_stage_idx) {

    /*stack<int> temp;
    int test_timer = 0;
    if (test_timer >= 0) {
        cout << "\nwidth = " << width << ", height = " << height << ", maximum = " << maximum;
        cout << ", count_curr = " << count_curr << ", last_idx = " << last_idx;
        cout << "\ncurr_stage_idx = " << curr_stage_idx << ", distinct_width_left_idx[last_idx] = " << distinct_width_left_idx[last_idx] << "\n";
        for (int i = 0; i < length; i++) {
            cout << max_length_starting_from_this_idx[i] << ", ";
        }
        cout << "\n";
        if (curr_path.size() > 0) {
            cout << "curr_path:\n";
            for (int i = 0; i < curr_path.size(); i++) {
                temp.push(curr_path.top());
                curr_path.pop();
            }
            for (int i = 0; i < temp.size(); i++) {
                curr_path.push(temp.top());
                cout << curr_path.top() << ", ";
                temp.pop();
            }
        }
        else {cout << "curr_path is empty.\n";}
        cout << "\n";
    }*/

    if (curr_stage_idx < count_dif_width) {
    //if (count_dif_width - curr_stage_idx + count_curr >= maximum)

        int test_timer = -1;
        if (test_timer >= 0) {
            cout << "\nwidth = " << width << ", height = " << height << ", maximum = " << maximum;
            cout << ", count_curr = " << count_curr << ", last_idx = " << last_idx;
            cout << "\ncurr_stage_idx = " << curr_stage_idx;
            if (last_idx >= 0) {
                cout << ", distinct_width_left_idx[" << last_idx << "] = " << distinct_width_left_idx[last_idx] << "\n";
            }
            else {
                cout << ", last_idx = 0\n";
            }
            for (int i = 0; i < length; i++) {
                cout << max_length_starting_from_this_idx[i] << ", ";
            }
            cout << "\n";
            stack<int> temp;
            if (curr_path.size() > 0) {
                cout << "curr_path.size() = " << curr_path.size() << "\n";
                cout << "curr_path:\n";

                while (curr_path.size() > 0) {
                    temp.push(curr_path.top());
                    curr_path.pop();
                }
                /*for (int i = 0; i < ; i++) {
                    cout << "fuck\n";
                    temp.push(curr_path.top());
                    curr_path.pop();
                }*/
                while (temp.size() > 0) {
                    curr_path.push(temp.top());
                    cout << temp.top() << ", ";
                    temp.pop();
                }

                /*for (int i = 0; i < temp.size(); i++) {
                    curr_path.push(temp.top());
                    cout << "fuck\n";
                    cout << temp.top() << ", ";
                    temp.pop();
                }*/
                cout << "\n";
            }
            else {cout << "curr_path is empty.\n";}
            if (remaining_path.size() > 0) {
                cout << "remaining_path.size() = " << remaining_path.size() << "\n";
                cout << "remaining_path:\n";
                while (remaining_path.size() > 0) {
                    temp.push(remaining_path.top());
                    remaining_path.pop();
                }
                while (temp.size() > 0) {
                    remaining_path.push(temp.top());
                    cout << temp.top() << ", ";
                    temp.pop();
                }
                cout << "\n";
            }
            else {cout << "remaining_path is empty.\n";}
            cout << "\n";
        }


        if (width >= 0) {
            if (test_timer >= 0) {cout << "width >= 0\n";}
            int next_idx = (curr_stage_idx < count_dif_width - 1)? distinct_width_left_idx[curr_stage_idx + 1] - 1: length - 1;

            if (dolls[next_idx][1] > height) {
                while(remaining_path.size() > 0) {remaining_path.pop();}

                if (dolls[distinct_width_left_idx[curr_stage_idx]][1] > height) {
                    curr_path.push(distinct_width_left_idx[curr_stage_idx]);
                }

                else {
                    int left = distinct_width_left_idx[curr_stage_idx], right = next_idx, mid;
                    int one_more = 1;
                    while (left <= right) {
                        mid = (left + right) / 2;

                        if (dolls[mid][1] <= height) {left = mid + 1;}

                        else {right = mid;}

                        if (one_more == 0) {break;}
                        if (left + 1 >= right) {one_more = 0;}
                    }

                    curr_path.push(left);
                }

                if (test_timer >= 0) {
                    cout << "found index = " << curr_path.top() << "\n";
                }

                if (max_length_starting_from_this_idx[curr_path.top()] < 0) {
                    if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[curr_path.top()] < 0\n";}
                    if (count_curr + 1 > maximum) {
                        maximum = count_curr + 1;
                        if (test_timer >= 0) {cout << "maximum = " << maximum << "\n";}
                    }

                    if (test_timer >= 0) {
                        cout << "check here:\n";
                        stack<int> temp;
                        if (curr_path.size() > 0) {
                            cout << "curr_path.size() = " << curr_path.size() << "\n";
                            cout << "curr_path:\n";

                            while (curr_path.size() > 0) {
                                temp.push(curr_path.top());
                                curr_path.pop();
                            }

                            while (temp.size() > 0) {
                                curr_path.push(temp.top());
                                cout << temp.top() << ", ";
                                temp.pop();
                            }


                            cout << "\n";
                        }
                        else {
                            cout << "curr_path is empty.\n";}
                        if (remaining_path.size() > 0) {
                            cout << "remaining_path.size() = " << remaining_path.size() << "\n";
                            cout << "remaining_path:\n";
                            while (remaining_path.size() > 0) {
                                temp.push(remaining_path.top());
                                remaining_path.pop();
                            }
                            while (temp.size() > 0) {
                                remaining_path.push(temp.top());
                                cout << temp.top() << ", ";
                                temp.pop();
                            }
                            cout << "\n";
                        }
                        else {cout << "remaining_path is empty.\n";}
                        cout << "\n";
                    }

                    probe_it (dolls, max_length_starting_from_this_idx, length,
                       distinct_width_left_idx, count_dif_width,
                       curr_path, remaining_path,
                       dolls[curr_path.top()][0], dolls[curr_path.top()][1],
                       maximum, count_curr + 1, curr_path.top(), curr_stage_idx + 1);

                    if (test_timer >= 0) {
                        cout << "curr_path.top() = " << curr_path.top() << "\n";
                        if (remaining_path.size() == 0) {cout << "remaining_path is empty.\n";}
                        else {cout << "remaining_path.top() = " << remaining_path.top() << "\n";}
                    }
                    //int temp = remaining_path.top();
                    remaining_path.push(curr_path.top());
                    //if (test_timer >= 0) {cout << "remaining_path.top() = " << remaining_path.top() << "\n";}
                    curr_path.pop();

                    int remaining_path_size = remaining_path.size();

                    if (remaining_path_size > max_length_starting_from_this_idx[remaining_path.top()]) {
                        max_length_starting_from_this_idx[remaining_path.top()] = remaining_path_size;
                    }

                    if (test_timer >= 0) {
                        cout << "max_length_starting_from_this_idx[" << remaining_path.top() << "] = " << max_length_starting_from_this_idx[remaining_path.top()] << "\n";
                    }
                }
/*
3, 3;
4, 1; 4, 6;
7, 2; 7, 7;
8, 5;
9, 7;
10, 2; 10, 4; 10, 8;
*/
                else {
                    if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[" << curr_path.top() << "] >= 0\n";}

                    if (count_curr + max_length_starting_from_this_idx[curr_path.top()] > maximum) {
                        maximum = count_curr + max_length_starting_from_this_idx[curr_path.top()];

                        while(remaining_path.size() > 0) {remaining_path.pop();}

                        if (test_timer >= 0) {cout << "maximum = " << maximum << "\n";}
                    }

                    remaining_path.push(curr_path.top());
                    curr_path.pop();


                    if (test_timer >= 0) {
                        cout << "curr_path.top() = " << curr_path.top() << "\n";
                        if (remaining_path.size() == 0) {cout << "remaining_path is empty.\n";}
                        else {cout << "remaining_path.top() = " << remaining_path.top() << "\n";}
                        cout << "shit\n";
                    }

                    max_length_starting_from_this_idx[curr_path.top()] =
                    max_length_starting_from_this_idx[remaining_path.top()] + 1;
                }
            }

            //while(remaining_path.size() > 0) {remaining_path.pop();}

            probe_it (dolls, max_length_starting_from_this_idx, length,
                   distinct_width_left_idx, count_dif_width,
                   curr_path, remaining_path,
                   width, height,
                   maximum, count_curr, last_idx, curr_stage_idx + 1);
        }

        else {
            if (test_timer >= 0) {cout << "width < 0\n";}
            if (count_curr + 1 > maximum) {
                maximum = count_curr + 1;
                if (test_timer >= 0) {cout << "maximum = " << maximum << "\n";}
            }

            curr_path.push(distinct_width_left_idx[curr_stage_idx]);

            probe_it (dolls, max_length_starting_from_this_idx, length,
                   distinct_width_left_idx, count_dif_width,
                   curr_path, remaining_path,
                   dolls[distinct_width_left_idx[curr_stage_idx]][0], dolls[distinct_width_left_idx[curr_stage_idx]][1],
                   maximum, count_curr + 1, distinct_width_left_idx[curr_stage_idx], curr_stage_idx + 1);

            remaining_path.push(curr_path.top());

            curr_path.pop();

            max_length_starting_from_this_idx[remaining_path.top()] = remaining_path.size();

            while(curr_path.size() > 0) {curr_path.pop();}
            while(remaining_path.size() > 0) {remaining_path.pop();}

            probe_it (dolls, max_length_starting_from_this_idx, length,
                   distinct_width_left_idx, count_dif_width,
                   curr_path, remaining_path,
                   width, height,
                   maximum, count_curr, last_idx, curr_stage_idx + 1);

        }

    }
}
int maxEnvelopes_try_again(vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    int test_timer = -1;

    if (test_timer >= 0) {cout << "\nlength = " << length << "\n";}
    merge_sort_2(dolls, length);

    if (test_timer >= 0) {
        cout << "after 1st sort:\n";
        for (int i = 0; i < length; i++) {
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n\n";
    }

    stack<int> dif_idx;int count_dif_width = 1;int temp = dolls[0][0];dif_idx.push(0);
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    if (test_timer >= 0) {cout << "\ncount_dif_width = " << count_dif_width << "\n";}
    if (count_dif_width == 1) {return 1;}

    int distinct_width_left_idx[count_dif_width];
    for (int i = count_dif_width - 1; i >= 0; i--) {distinct_width_left_idx[i] = dif_idx.top();dif_idx.pop();}

    int left, right;
    for (int i = 0; i < count_dif_width; i++) {
        left = distinct_width_left_idx[i];
        right = (i < count_dif_width - 1)? distinct_width_left_idx[i + 1] - 1: length - 1;
        merge_sort_2nd_idx_2(dolls, left, right);
    }

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << distinct_width_left_idx[i] << ", ";
        }
        cout << "\n\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_width_left_idx[j])&&(j < count_dif_width)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";

        }
        cout << "\n";
    }

    int max_length_starting_from_this_idx[length];for (int i = 0; i < length; i++) {max_length_starting_from_this_idx[i] = -1;}
    //int curr_path[count_dif_width];for (int i = 0; i < count_dif_width; i++) {curr_path[i] = -1;}
    stack<int> curr_path;
    stack<int> remaining_path;

    int maximum = 0;//, left, right, mid;
    int width = -1, height = -1, count_curr = 0, last_idx = -1, curr_stage_idx = 0;

    probe_it (dolls, max_length_starting_from_this_idx, length,
                   distinct_width_left_idx, count_dif_width,
                   curr_path, remaining_path,
                   width, height,
                   maximum, count_curr, last_idx, curr_stage_idx);

    return maximum;
}



//max_length_starting_from_this_idx, -1 means have not probed yet
void probe_it_1 (int dolls[][2], int max_length_starting_from_this_idx[], int length,
               int distinct_width_left_idx[], int count_dif_width,
               stack<int> &curr_path, stack<int> &remaining_path,
               int width, int height,
               int &maximum, int count_curr, int last_idx, int curr_stage_idx) {

    if (curr_stage_idx < count_dif_width) {//count_dif_width - curr_stage_idx + count_curr >= maximum

        int test_timer = -1;
        if (test_timer >= 0) {
            cout << "\nwidth = " << width << ", height = " << height << ", maximum = " << maximum;
            cout << ", count_curr = " << count_curr << ", last_idx = " << last_idx;
            cout << "\ncurr_stage_idx = " << curr_stage_idx;
            if (last_idx >= 0) {
                cout << ", distinct_width_left_idx[" << last_idx << "] = " << distinct_width_left_idx[last_idx] << "\n";
            }
            else {cout << ", last_idx = 0\n";}
            for (int i = 0; i < length; i++) {cout << max_length_starting_from_this_idx[i] << ", ";}
            cout << "\n";
            stack<int> temp;
            if (curr_path.size() > 0) {
                cout << "curr_path.size() = " << curr_path.size() << "\n";
                cout << "curr_path:\n";

                while (curr_path.size() > 0) {
                    temp.push(curr_path.top());
                    curr_path.pop();
                }

                while (temp.size() > 0) {
                    curr_path.push(temp.top());
                    cout << temp.top() << ", ";
                    temp.pop();
                }

                cout << "\n";
            }
            else {cout << "curr_path is empty.\n";}
            if (remaining_path.size() > 0) {
                cout << "remaining_path.size() = " << remaining_path.size() << "\n";
                cout << "remaining_path:\n";
                while (remaining_path.size() > 0) {
                    temp.push(remaining_path.top());
                    remaining_path.pop();
                }
                while (temp.size() > 0) {
                    remaining_path.push(temp.top());
                    cout << temp.top() << ", ";
                    temp.pop();
                }
                cout << "\n";
            }
            else {cout << "remaining_path is empty.\n";}
            cout << "\n";
        }

        if (width >= 0) {
            if (test_timer >= 0) {cout << "width >= 0\n";}
            int next_idx = (curr_stage_idx < count_dif_width - 1)? distinct_width_left_idx[curr_stage_idx + 1] - 1: length - 1;

            if (dolls[next_idx][1] > height) {
                while(remaining_path.size() > 0) {remaining_path.pop();}

                if (dolls[distinct_width_left_idx[curr_stage_idx]][1] > height) {
                    curr_path.push(distinct_width_left_idx[curr_stage_idx]);
                }

                else {
                    int left = distinct_width_left_idx[curr_stage_idx], right = next_idx, mid;
                    int one_more = 1;
                    while (left <= right) {
                        mid = (left + right) / 2;

                        if (dolls[mid][1] <= height) {left = mid + 1;}

                        else {right = mid;}

                        if (one_more == 0) {break;}
                        if (left + 1 >= right) {one_more = 0;}
                    }

                    curr_path.push(left);
                }

                if (test_timer >= 0) {cout << "found index = " << curr_path.top() << "\n";}

                if (max_length_starting_from_this_idx[curr_path.top()] < 0) {
                    if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[curr_path.top()] < 0\n";}
                    if (count_curr + 1 > maximum) {
                        maximum = count_curr + 1;
                        if (test_timer >= 0) {cout << "maximum = " << maximum << "\n";}
                    }

                    if (test_timer >= 0) {
                        cout << "check here:\n";
                        stack<int> temp;
                        if (curr_path.size() > 0) {
                            cout << "curr_path.size() = " << curr_path.size() << "\n";
                            cout << "curr_path:\n";

                            while (curr_path.size() > 0) {
                                temp.push(curr_path.top());
                                curr_path.pop();
                            }

                            while (temp.size() > 0) {
                                curr_path.push(temp.top());
                                cout << temp.top() << ", ";
                                temp.pop();
                            }


                            cout << "\n";
                        }
                        else {cout << "curr_path is empty.\n";}
                        if (remaining_path.size() > 0) {
                            cout << "remaining_path.size() = " << remaining_path.size() << "\n";
                            cout << "remaining_path:\n";
                            while (remaining_path.size() > 0) {
                                temp.push(remaining_path.top());
                                remaining_path.pop();
                            }
                            while (temp.size() > 0) {
                                remaining_path.push(temp.top());
                                cout << temp.top() << ", ";
                                temp.pop();
                            }
                            cout << "\n";
                        }
                        else {cout << "remaining_path is empty.\n";}
                        cout << "\n";
                    }

                    probe_it_1 (dolls, max_length_starting_from_this_idx, length,
                       distinct_width_left_idx, count_dif_width,
                       curr_path, remaining_path,
                       dolls[curr_path.top()][0], dolls[curr_path.top()][1],
                       maximum, count_curr + 1, curr_path.top(), curr_stage_idx + 1);

                    if (test_timer >= 0) {
                        cout << "curr_path.top() = " << curr_path.top() << "\n";
                        if (remaining_path.size() == 0) {cout << "remaining_path is empty.\n";}
                        else {cout << "remaining_path.top() = " << remaining_path.top() << "\n";}
                    }
                    remaining_path.push(curr_path.top());
                    curr_path.pop();
                    if (test_timer >= 0) {
                        if (curr_path.size() == 0) {cout << "curr_path is empty\n";}
                        else {
                            cout << "curr_path.size() = " << curr_path.size() << "\n";
                            cout << "curr_path.top() = " << curr_path.top() << "\n";
                        }
                        if (remaining_path.size() == 0) {cout << "remaining_path is empty.\n";}
                        else {
                            cout << "remaining_path.size() = " << remaining_path.size() << "\n";
                            cout << "remaining_path.top() = " << remaining_path.top() << "\n";
                        }
                    }

                    int remaining_path_size = remaining_path.size();
                    //cout << "\nremaining_path.size() = " << remaining_path.size() << "\n";
                    //cout << "max_length_starting_from_this_idx[remaining_path.top()] = " << max_length_starting_from_this_idx[remaining_path.top()] << "\n";

                    if (remaining_path_size > max_length_starting_from_this_idx[remaining_path.top()]) {
                        //cout << "what?!\n";
                        max_length_starting_from_this_idx[remaining_path.top()] = remaining_path_size;
                    }

                    if (test_timer >= 0) {
                        //cout << "why?!\n";
                        cout << "max_length_starting_from_this_idx[" << remaining_path.top() << "] = "
                        << max_length_starting_from_this_idx[remaining_path.top()] << "\n";
                    }
                }
/*
2, 4; 2, 6;
3, 3;
4, 2; 4, 4;
6, 6; 6, 7;
7, 2; 7, 8;
10, 9;
*/
                else {
                    if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[" << curr_path.top() << "] >= 0\n";}

                    if (count_curr + max_length_starting_from_this_idx[curr_path.top()] > maximum) {
                        maximum = count_curr + max_length_starting_from_this_idx[curr_path.top()];

                        while(remaining_path.size() > 0) {remaining_path.pop();}

                        if (test_timer >= 0) {cout << "maximum = " << maximum << "\n";}
                    }

                    remaining_path.push(curr_path.top());
                    curr_path.pop();


                    if (test_timer >= 0) {
                        cout << "curr_path.top() = " << curr_path.top() << "\n";
                        if (remaining_path.size() == 0) {cout << "remaining_path is empty.\n";}
                        else {cout << "remaining_path.top() = " << remaining_path.top() << "\n";}
                        cout << "shit\n";
                    }

                    max_length_starting_from_this_idx[curr_path.top()] =
                    max_length_starting_from_this_idx[remaining_path.top()] + 1;
                }
            }

            //while(remaining_path.size() > 0) {remaining_path.pop();}

            probe_it_1 (dolls, max_length_starting_from_this_idx, length,
                   distinct_width_left_idx, count_dif_width,
                   curr_path, remaining_path,
                   width, height,
                   maximum, count_curr, last_idx, curr_stage_idx + 1);
        }

        else {
            if (test_timer >= 0) {cout << "width < 0\n";}
            if (count_curr + 1 > maximum) {
                maximum = count_curr + 1;
                if (test_timer >= 0) {cout << "maximum = " << maximum << "\n";}
            }

            curr_path.push(distinct_width_left_idx[curr_stage_idx]);

            probe_it_1 (dolls, max_length_starting_from_this_idx, length,
                   distinct_width_left_idx, count_dif_width,
                   curr_path, remaining_path,
                   dolls[distinct_width_left_idx[curr_stage_idx]][0], dolls[distinct_width_left_idx[curr_stage_idx]][1],
                   maximum, count_curr + 1, distinct_width_left_idx[curr_stage_idx], curr_stage_idx + 1);

            remaining_path.push(curr_path.top());

            curr_path.pop();

            max_length_starting_from_this_idx[remaining_path.top()] = remaining_path.size();

            while(curr_path.size() > 0) {curr_path.pop();}
            while(remaining_path.size() > 0) {remaining_path.pop();}

            probe_it_1 (dolls, max_length_starting_from_this_idx, length,
                   distinct_width_left_idx, count_dif_width,
                   curr_path, remaining_path,
                   width, height,
                   maximum, count_curr, last_idx, curr_stage_idx + 1);

        }

    }
}

int maxEnvelopes_try_again_1(vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    int test_timer = -1;

    merge_sort_2(dolls, length);

    stack<int> dif_idx;int count_dif_width = 1;int temp = dolls[0][0];dif_idx.push(0);
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    if (test_timer >= 0) {cout << "\ncount_dif_width = " << count_dif_width << "\n";}
    if (count_dif_width == 1) {return 1;}

    int distinct_width_left_idx[count_dif_width];
    for (int i = count_dif_width - 1; i >= 0; i--) {distinct_width_left_idx[i] = dif_idx.top();dif_idx.pop();}

    int left, right;
    for (int i = 0; i < count_dif_width; i++) {
        left = distinct_width_left_idx[i];
        right = (i < count_dif_width - 1)? distinct_width_left_idx[i + 1] - 1: length - 1;
        merge_sort_2nd_idx_2(dolls, left, right);
    }

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << distinct_width_left_idx[i] << ", ";
        }
        cout << "\n\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_width_left_idx[j])&&(j < count_dif_width)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";

        }
        cout << "\n";
    }

    int max_length_starting_from_this_idx[length];for (int i = 0; i < length; i++) {max_length_starting_from_this_idx[i] = -1;}
    //int curr_path[count_dif_width];for (int i = 0; i < count_dif_width; i++) {curr_path[i] = -1;}
    stack<int> curr_path;
    stack<int> remaining_path;

    int maximum = 0;//, left, right, mid;
    int width = -1, height = -1, count_curr = 0, last_idx = -1, curr_stage_idx = 0;

    probe_it_1 (dolls, max_length_starting_from_this_idx, length,
                   distinct_width_left_idx, count_dif_width,
                   curr_path, remaining_path,
                   width, height,
                   maximum, count_curr, last_idx, curr_stage_idx);

    return maximum;
}





//i must slice it clean//stack<int> &curr_path,
void probe_here (int dolls[][2], vector<int> &max_length_starting_from_this_idx, vector<vector<int>> &next_idx, int length,
               int distinct_width_left_idx[], int count_dif_width,
               int width, int height, int &maximum, int last_idx, int count_curr, int curr_stage_idx) {//

    int test_timer = 0;
    if (test_timer >= 0) {
        cout << "\nwidth = " << width << ", height = " << height << ", last_idx = " << last_idx;
        cout << ", count_curr = " << count_curr;
        cout << ", maximum = " << maximum;
        cout << "\ncurr_stage_idx = " << curr_stage_idx << "\n";// << ", remaining_path_size = " << remaining_path_size;
        cout << "max_length_starting_from_this_idx:\n";
        for (int i = 0; i < length; i++) {
            cout << max_length_starting_from_this_idx[i] << ", ";
        }
        cout << "\nnext_idx:\n";
        for (int i = 0; i < length; i++) {
            cout << next_idx[i][0] << ", ";
        }cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << next_idx[i][1] << ", ";
        }
        cout << "\n\n";
    }

    if (curr_stage_idx < count_dif_width) {
        if (test_timer >= 0) {cout << "curr_stage_idx < count_dif_width\n\n";}
        probe_here (dolls, max_length_starting_from_this_idx, next_idx, length,
                    distinct_width_left_idx, count_dif_width,
                    width, height, maximum, last_idx, count_curr, curr_stage_idx + 1);

        int right = (curr_stage_idx < count_dif_width - 1)? distinct_width_left_idx[curr_stage_idx + 1] - 1: length - 1;

        if (dolls[right][1] > height) {
            int left = distinct_width_left_idx[curr_stage_idx];

            if (dolls[left][1] <= height) {
                int mid, one_more = 1;
                while (left <= right) {
                    mid = (left + right) / 2;

                    if (dolls[mid][1] <= height) {left = mid + 1;}

                    else {right = mid;}

                    if (one_more == 0) {break;}
                    if (left + 1 >= right) {one_more = 0;}
                }
            }

            if (test_timer >= 0) {cout << "left = " << left << "\n";}

            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            if (last_idx >= 0) {
                //if (next_idx[last_idx][0] < 0) {next_idx[last_idx][0] = left;}

                //else {next_idx[last_idx][1] = left;}

            }

            if (max_length_starting_from_this_idx[left] <= 0) {
                if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[left] < 0\n\n";}
                probe_here (dolls, max_length_starting_from_this_idx, next_idx, length,
                        distinct_width_left_idx, count_dif_width,
                        dolls[left][0], dolls[left][1],
                        maximum, left, count_curr + 1, curr_stage_idx + 1);//

                if ((last_idx >= 0)&&(next_idx[last_idx][1] >= 0)) {
                    if (max_length_starting_from_this_idx[next_idx[last_idx][1]] > max_length_starting_from_this_idx[next_idx[last_idx][0]]) {
                        next_idx[last_idx][0] = next_idx[last_idx][1];
                    }

                    next_idx[last_idx][1] = -1;
                }

                if (test_timer >= 0) {
                    cout << "left = " << left << "\n";
                    cout << "max_length_starting_from_this_idx[left] = " << max_length_starting_from_this_idx[left] << "\n";
                    cout << "next_idx[left][0] = " << next_idx[left][0] << "\n";
                    cout << "max_length_starting_from_this_idx[next_idx[left][0]] = " << max_length_starting_from_this_idx[next_idx[left][0]] << "\n";
                }

                if (next_idx[left][0] >= 0) {
                    max_length_starting_from_this_idx[left] = max_length_starting_from_this_idx[next_idx[left][0]] + 1;
                }
            }

            else {
                if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[left] > 0\n\n";}

                if (count_curr + max_length_starting_from_this_idx[left] > maximum) {
                    maximum = count_curr + max_length_starting_from_this_idx[left];
                }
            }
        }
/*1, 2;
2, 2;
3, 1;
4, 2;
5, 3;
6, 9;
7, 4;
8, 4;
10, 3; 10, 6;*/
    }

    else {
        if (test_timer >= 0) {cout << "curr_stage_idx == count_dif_width\n\n";}

        if (last_idx >= 0) {
            max_length_starting_from_this_idx[last_idx] = 1;

            /*cout << "max_length_starting_from_this_idx[last_idx] = " << max_length_starting_from_this_idx[last_idx] << "\n\n";
            cout << "max_length_starting_from_this_idx:\n";
            for (int i = 0; i < length; i++) {
                cout << max_length_starting_from_this_idx[i] << ", ";
            }cout << "\n\n";*/
        }

        //else {cout << "last_idx < 0\n\n";}
    }
}

int maxEnvelopes_try_again_2(vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    int test_timer = 0;

    merge_sort_2(dolls, length);

    stack<int> dif_idx;int count_dif_width = 1;int temp = dolls[0][0];dif_idx.push(0);
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    if (test_timer >= 0) {cout << "\ncount_dif_width = " << count_dif_width << "\n";}
    if (count_dif_width == 1) {return 1;}

    int distinct_width_left_idx[count_dif_width];
    for (int i = count_dif_width - 1; i >= 0; i--) {distinct_width_left_idx[i] = dif_idx.top();dif_idx.pop();}

    int left, right;
    for (int i = 0; i < count_dif_width; i++) {
        left = distinct_width_left_idx[i];
        right = (i < count_dif_width - 1)? distinct_width_left_idx[i + 1] - 1: length - 1;
        merge_sort_2nd_idx_2(dolls, left, right);
    }

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << distinct_width_left_idx[i] << ", ";
        }
        cout << "\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_width_left_idx[j])&&(j < count_dif_width)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";

        }
        cout << "\n\n";
    }

    //int max_length_starting_from_this_idx[length];
    //for (int i = 0; i < length; i++) {max_length_starting_from_this_idx[i] = 0;}
    //for (int i = distinct_width_left_idx[count_dif_width - 1]; i < length; i++) {max_length_starting_from_this_idx[i] = 1;}

    vector<int> max_length_starting_from_this_idx(length, 0);

    //int next_idx[length][2];for (int i = 0; i < length; i++) {next_idx[i][0] = -1, next_idx[i][1] = -1;}
    vector<vector<int>> next_idx(length, vector<int> (2, -1));

    int maximum = 0;
    int width = -1, height = -1, count_curr = 0, last_idx = -1, curr_stage_idx = 0;

    probe_here (dolls, max_length_starting_from_this_idx, next_idx, length,
                distinct_width_left_idx, count_dif_width,
                width, height, maximum, last_idx, count_curr, curr_stage_idx);//

    return maximum;
}





//tricky to slice.
/*void probe_probe (int dolls[][2], int max_length_starting_from_this_idx[], int length,//, int next_idx
               int distinct_width_left_idx[], int count_dif_width,
               int width, int height, int &maximum, int last_idx, int count_curr, int curr_stage_idx) {//

    int test_timer = 0;
    if (test_timer >= 0) {
        cout << "\nwidth = " << width << ", height = " << height << ", last_idx = " << last_idx;
        cout << ", count_curr = " << count_curr;
        cout << ", maximum = " << maximum;
        cout << "\ncurr_stage_idx = " << curr_stage_idx << "\n";// << ", remaining_path_size = " << remaining_path_size;
        cout << "max_length_starting_from_this_idx:\n";
        for (int i = 0; i < length; i++) {
            cout << max_length_starting_from_this_idx[i] << ", ";
        }
        //cout << "\nnext_idx:\n";for (int i = 0; i < length; i++) {cout << next_idx[i] << ", ";}cout << "\n";
        cout << "\n\n";
    }

    if (curr_stage_idx < count_dif_width) {
        if (test_timer >= 0) {cout << "curr_stage_idx < count_dif_width\n\n";}
        probe_probe (dolls, max_length_starting_from_this_idx, length,// next_idx,
                    distinct_width_left_idx, count_dif_width,
                    width, height, maximum, distinct_width_left_idx[curr_stage_idx], count_curr, curr_stage_idx + 1);

        int right = (curr_stage_idx < count_dif_width - 1)? distinct_width_left_idx[curr_stage_idx + 1] - 1: length - 1;

        if (dolls[right][1] > height) {
            int left = distinct_width_left_idx[curr_stage_idx];

            if (dolls[left][1] <= height) {
                int mid, one_more = 1;
                while (left <= right) {
                    mid = (left + right) / 2;

                    if (dolls[mid][1] <= height) {left = mid + 1;}

                    else {right = mid;}

                    if (one_more == 0) {break;}
                    if (left + 1 >= right) {one_more = 0;}
                }
            }

            if (test_timer >= 0) {cout << "left = " << left << "\n";}

            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            if (last_idx >= 0) {
                //if (next_idx[last_idx][0] < 0) {next_idx[last_idx][0] = left;}

                //else {next_idx[last_idx] = left;}

            }

            if (max_length_starting_from_this_idx[left] <= 0) {
                if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[left] < 0\n\n";}
                probe_here (dolls, max_length_starting_from_this_idx, next_idx, length,
                        distinct_width_left_idx, count_dif_width,
                        dolls[left][0], dolls[left][1],
                        maximum, left, count_curr + 1, curr_stage_idx + 1);//

                if ((last_idx >= 0)&&(next_idx[last_idx][1] >= 0)) {
                    if (max_length_starting_from_this_idx[next_idx[last_idx][1]] > max_length_starting_from_this_idx[next_idx[last_idx][0]]) {
                        next_idx[last_idx][0] = next_idx[last_idx][1];
                    }

                    next_idx[last_idx][1] = -1;
                }

                if (test_timer >= 0) {
                    cout << "left = " << left << "\n";
                    cout << "max_length_starting_from_this_idx[left] = " << max_length_starting_from_this_idx[left] << "\n";
                    cout << "next_idx[left][0] = " << next_idx[left][0] << "\n";
                    cout << "max_length_starting_from_this_idx[next_idx[left][0]] = " << max_length_starting_from_this_idx[next_idx[left][0]] << "\n";
                }

                if (next_idx[left][0] >= 0) {
                    max_length_starting_from_this_idx[left] = max_length_starting_from_this_idx[next_idx[left][0]] + 1;
                }
            }

            else {
                if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[left] > 0\n\n";}

                if (count_curr + max_length_starting_from_this_idx[left] > maximum) {
                    maximum = count_curr + max_length_starting_from_this_idx[left];
                }
            }
        }
    }

    else {
        if (test_timer >= 0) {cout << "curr_stage_idx == count_dif_width\n\n";}

        if (last_idx >= 0) {
            max_length_starting_from_this_idx[last_idx] = 1;
            if (maximum < 1) {maximum = 1;}
        }
    }
}*/

int maxEnvelopes_try_again_3(vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    int test_timer = -1;

    merge_sort_2(dolls, length);

    stack<int> dif_idx;int count_dif_width = 1;int temp = dolls[0][0];dif_idx.push(0);
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    if (test_timer >= 0) {cout << "\ncount_dif_width = " << count_dif_width << "\n";}
    if (count_dif_width == 1) {return 1;}

    int distinct_width_left_idx[count_dif_width];
    for (int i = count_dif_width - 1; i >= 0; i--) {distinct_width_left_idx[i] = dif_idx.top();dif_idx.pop();}

    int left, right;
    for (int i = 0; i < count_dif_width; i++) {
        left = distinct_width_left_idx[i];
        right = (i < count_dif_width - 1)? distinct_width_left_idx[i + 1] - 1: length - 1;
        merge_sort_2nd_idx_2(dolls, left, right);
    }

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << distinct_width_left_idx[i] << ", ";
        }
        cout << "\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_width_left_idx[j])&&(j < count_dif_width)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";

        }
        cout << "\n\n";
    }

    int max_length_starting_from_this_idx[length];
    for (int i = 0; i < distinct_width_left_idx[count_dif_width - 1]; i++) {max_length_starting_from_this_idx[i] = 0;}
    for (int i = distinct_width_left_idx[count_dif_width - 1]; i < length; i++) {max_length_starting_from_this_idx[i] = 1;}

    int maximum = 0, width = -1, height = -1, count_curr = 0, last_idx = -1, curr_stage_idx = 0;
    int curr_max_height = 0;
    multimap<int, int> max_len_to_idx;
    int idx_start_from;
    for (int i = distinct_width_left_idx[count_dif_width - 1]; i < length; i++) {
        max_len_to_idx.insert({1, i});
        if (dolls[i][1] > curr_max_height) {
            curr_max_height = dolls[i][1];
        }
    }

    if (test_timer >= 0) {
        for (auto i = max_len_to_idx.begin(); i != max_len_to_idx.end(); ++i) {
            cout << i->first << ", " << i->second << "; ";
        }cout << "\n\n";
    }

    for (int i = count_dif_width - 2, this_step_found = 0; i >= 0; i--) {
        if (test_timer >= 0) {cout << "i = " << i << "\n\n";}
        for (int j = distinct_width_left_idx[i]; j < distinct_width_left_idx[i + 1]; j++) {
            if (dolls[j][1] < curr_max_height) {
                if (test_timer >= 0) {cout << "dolls[j][1] < curr_max_height\n";}
                for (auto k = max_len_to_idx.rbegin(); k != max_len_to_idx.rend(); ++k) {
                    if (test_timer >= 0) {
                        cout << "k->first = " << k->first << ", ";
                        cout << "k->second = " << k->second << "\n";
                    }
                    if (dolls[k->second][1] > dolls[j][1]) {
                        max_length_starting_from_this_idx[j] = k->first + 1;
                        if (test_timer >= 0) {
                            cout << "max_length_starting_from_this_idx[" << j << "] = " << max_length_starting_from_this_idx[j] << "\n";
                        }
                        break;
                    }
                    //if (test_timer >= 0) {test_timer++;}
                    //if (test_timer > 40) {break;}
                }
            }

            else {
                if (test_timer >= 0) {cout << "dolls[j][1] >= curr_max_height\n";}
                for (int k = j; k < distinct_width_left_idx[i + 1]; k++) {
                    max_length_starting_from_this_idx[k] = 1;
                }
                break;
            }
            //if (test_timer > 40) {break;}
        }

        if (test_timer >= 0) {cout << "insert into map\n";}
        for (int j = distinct_width_left_idx[i]; j < distinct_width_left_idx[i + 1]; j++) {
            max_len_to_idx.insert({max_length_starting_from_this_idx[j], j});
            if (dolls[j][1] > curr_max_height) {
               curr_max_height = dolls[j][1];
            }
        }

        if (test_timer >= 0) {
            cout << "distinct_width_left_idx[i] = " << distinct_width_left_idx[i] << "\n";
            cout << "distinct_width_left_idx[i + 1] = " << distinct_width_left_idx[i + 1] << "\n";
            cout << "curr_max_height = " << curr_max_height << "\n";
            for (auto i = max_len_to_idx.begin(); i != max_len_to_idx.end(); ++i) {
                cout << i->first << ", " << i->second << "; ";
            }cout << "\n\n";
        }
    }

    maximum = max_length_starting_from_this_idx[0];
    for (int i = 1; i < length; i++) {
        if (max_length_starting_from_this_idx[i] > maximum) {
            maximum = max_length_starting_from_this_idx[i];
        }
    }

    return maximum;
}







int main(){
    srand(time(0));int length = 20, lower_range = 1, upper_range = 20, display = 0, input = 1;
    vector<vector<int>> wtf;
    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;

for (int m = 1; m <= 100000; m++) {if (m % 1000 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){
        wtf.reserve(length);
        for(int i = 0; i < length; i++){
            wtf.push_back({rand()%(upper_range - lower_range + 1) + lower_range,
                          rand()%(upper_range - lower_range + 1) + lower_range});
        }
    }
    if (display == 1){
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{" << wtf[i][0] << ", " << wtf[i][1] << "}";
            if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    start_point_1 = chrono::steady_clock::now();
    int a = maxEnvelopes_brute(wtf);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    //cout << "\nbrute = " << a << "\n\n";
    //cout << "length = " << wtf.size() << "\n";

    start_point_2 = chrono::steady_clock::now();
    int brute = maxEnvelopes_try_again_3(wtf);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    /*start_point_3 = chrono::steady_clock::now();
    int b = maxEnvelopes_try_again_1(wtf);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;*/

    //cout << "\n_try_again_3 = " << brute << "\n";

    if (a != brute) {
        cout << "\n\n\nm = " << m << "\n\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{" << wtf[i][0] << ", " << wtf[i][1] << "}";
            if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
        cout << "\nbrute = " << a << "\n";
        cout << "_try_again = " << brute << "\n";
        break;
    }


wtf.clear();}

cout << "brute: " << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << "_try_again_2: " << duration <double, milli> (diff_2).count() << " ms" << "\n";
//cout << "_try_again_1: " << duration <double, milli> (diff_3).count() << " ms" << "\n";

    return 0;
}






/* =
    {{856,533},{583,772},{980,524},{203,666},{987,151},{274,802},{982,85},{359,160},{58,823},{512,381},
{796,655},{341,427},{145,114},{76,306},{760,929},{836,751},{922,678},{128,317},{185,953},{115,845},
{829,991},{93,694},{317,434},{818,571},{352,638},{926,780},{819,995},{54,69},{191,392},{377,180},
{669,952},{588,920},{335,316},{48,769},{188,661},{916,933},{674,308},{356,556},{350,249},{686,851},
{600,178},{849,439},{597,181},{80,382},{647,105},{4,836},{901,907},{595,347},{214,335},{956,382},
{77,979},{489,365},{80,220},{859,270},{676,665},{636,46},{906,457},{522,769},{2,758},{206,586},
{444,904},{912,370},{64,871},{59,409},{599,238},{437,58},{309,767},{258,440},{922,369},{848,650},
{478,76},{84,704},{314,207},{138,823},{994,764},{604,595},{537,876},{877,253},{945,185},{623,497},
{968,633},{172,705},{577,388},{819,763},{409,905},{275,532},{729,593},{547,226},{445,495},{398,544},
{243,500},{308,24},{652,452},{93,885},{75,884},{243,113},{600,555},{756,596},{892,762},{402,653},{916,975},
{770,220},{455,579},{889,68},{306,899},{567,290},{809,653},{92,329},{370,861},{632,754},{321,689},{190,812},
{88,701},{79,310},{917,91},{751,480},{750,39},{781,978},{778,912},{946,559},{529,621},{55,295},{473,748},{646,854},
{930,913},{116,734},{647,812},{426,172},{122,14},{522,843},{88,308},{719,602},{712,928},{303,890},{973,886},
{276,354},{660,720},{708,387},{776,605},{653,815},{448,285},{549,959},{139,365},{74,952},{372,424},{642,504},
{361,901},{620,612},{313,301},{397,225},{446,716},{17,361},{160,812},{171,529},{180,482},{454,600},{228,872},
{204,492},{607,889},{86,79},{494,78},{442,404},{462,127},{935,402},{509,649},{458,941},{219,444},{306,57},
{674,617},{79,652},{73,735},{900,756},{649,294},{982,754},{521,439},{356,265},{240,533},{865,44},{744,379},
{97,454},{65,480},{544,191},{18,191},{503,38},{696,658},{61,884},{793,984},{383,364},{280,467},{888,662},
{133,643},{365,512},{610,975},{98,584},{40,177},{548,102},{80,98},{986,951},{264,258},{583,734},{353,322},
{427,551},{80,660},{273,609},{980,871},{739,802},{366,836},{55,509},{889,720},{857,661},{48,489},{119,26},
{31,180},{472,673},{960,951},{383,500},{928,351},{848,705},{969,766},{311,714},{861,230},{34,596},{38,642},
{1,955},{698,846},{784,791},{760,344},{677,239},{969,191},{539,644},{470,418},{289,357},{269,446},{668,245},
{293,719},{937,103},{575,297},{874,656},{714,257},{934,396},{109,904},{89,635},{374,545},{316,587},{158,121},
{901,969},{284,564},{666,568},{993,409},{370,637},{443,694},{576,160},{262,357},{590,729},{194,976},{743,376},
{348,80},{669,527},{338,953},{236,785},{144,460},{438,457},{517,951},{545,647},{158,556},{905,591},{793,609},
{571,643},{9,850},{581,490},{804,394},{635,483},{457,30},{42,621},{65,137},{424,864},{536,455},{59,492},
{645,734},{892,571},{762,593},{608,384},{558,257},{692,420},{973,203},{531,51},{349,861},{804,649},{3,611},
{6,468},{298,568},{651,767},{251,142},{173,974},{117,728},{326,562},{894,288},{814,555},{420,771},{20,775},
{445,247},{243,592},{186,173},{101,800},{590,876},{515,534},{73,540},{333,215},{902,394},{640,787},{596,298},
{984,712},{307,378},{540,646},{473,743},{340,387},{756,217},{139,493},{9,742},{195,25},{763,823},{451,693},
{24,298},{645,595},{224,770},{976,41},{832,78},{599,705},{487,734},{818,134},{225,431},{380,566},{395,680},
{294,320},{915,201},{553,480},{318,42},{627,94},{164,959},{92,715},{588,689},{734,983},{976,334},{846,573},
{676,521},{449,69},{745,810},{961,722},{416,409},{135,406},{234,357},{873,61},{20,521},{525,31},{659,688},
{424,554},{203,315},{16,240},{288,273},{281,623},{651,659},{939,32},{732,373},{778,728},{340,432},{335,80},
{33,835},{835,651},{317,156},{284,119},{543,159},{719,820},{961,424},{88,178},{621,146},{594,649},{659,433},
{527,441},{118,160},{92,217},{489,38},{18,359},{833,136},{470,897},{106,123},{831,674},{181,191},{892,780},
{377,779},{608,618},{618,423},{180,323},{390,803},{562,412},{107,905},{902,281},{718,540},{16,966},{678,455},
{597,135},{840,7},{886,45},{719,937},{890,173}}*/



