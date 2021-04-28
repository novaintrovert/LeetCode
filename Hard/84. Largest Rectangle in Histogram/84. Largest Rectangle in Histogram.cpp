/*84. Largest Rectangle in Histogram
Hard

Given n non-negative integers representing the histogram's bar height
where the width of each bar is 1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
The largest rectangle is shown in the shaded area, which has area = 10 unit.

Input: [2,1,5,6,2,3]
Output: 10
*/

/*
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {

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

//draft days ago, don't work so far
int largestRectangleArea_utterly_unfinished(vector<int>& heights) {
    int length = heights.size(), max_area = 0;
    deque<int> idxes;
    int left = 0, curr_lowest, curr_area;
    while (true) {
        if (heights[left] == 0) {
            left++;
            continue;
        }

        while ((!idxes.empty())&&(idxes.front() <= left)) {
            idxes.pop_front();
        }

        if (idxes.empty()) {
            curr_lowest = heights[left];
            for (int i = left + 1; (i < length)&&(heights[i] > 0); i++) {
                if (heights[i] < curr_lowest) {
                    idxes.push_back(i);

                    curr_area = (i - left) * curr_lowest;
                    if (curr_area > max_area) {
                        max_area = curr_area;
                    }

                    curr_lowest = heights[i];
                }
            }
        }

        else {
            curr_lowest = heights[left];
            for (int i = left + 1; i < idxes.front(); i++) {
                if (heights[i] < curr_lowest) {}
            }

            left = idxes.front();
            idxes.pop_front();
        }

        if (left == length - 1) {break;}
    }

    return max_area;
}


void merge_sort (int a[][2], int length) {//20201206
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
            a[i][0] = b[i][0], b[i][1] = a[i][1];
        }
    }
}


int largestRectangleArea_brute(vector<int>& heights) {
    int length = heights.size(), max_area = 0;

    for (int i = 0, left, right, curr_area; i < length; i++) {
        left = i, right = i;

        while ((left > 0)&&(heights[left - 1] >= heights[i])) {left--;}

        while ((right < length - 1)&&(heights[right + 1] >= heights[i])) {right++;}

        curr_area = (right - left + 1) * heights[i];
        if (curr_area > max_area) {
            max_area = curr_area;
        }
    }

    return max_area;
}

int largestRectangleArea(vector<int>& heights) {
    int length = heights.size();
    if (length == 0) {return 0;}
    if (length == 1) {return heights[0];}

    int max_area = 0, temp;
    int test = -1;

    /*int test_it[length][2];
    for (int i = 0; i < length; i++) {test_it[i][0] = heights[i], test_it[i][1] = i;}
    merge_sort(test_it, length);

    int test_it_test[length];
    for (int i = 0; i < length; i++) {
        test_it_test[test_it[i][1]] = i;
    }

    if (test >= 0) {
        cout << "\n\n";
        for (int i = 0; i < length; i++) {
            cout << test_it[i][0] << " " << test_it[i][1] << ", ";
        }
        cout << "\n\n";
        for (int i = 0; i < length; i++) {
            cout << test_it_test[i] << ", ";
        }
        cout << "\n\n";
    }*/

    //the first idx, to the left of i, that is no smaller than current idx
    int left[length];left[0] = 0;
    for (int i = 1; i < length; i++) {
        if (heights[i] > heights[i - 1]) {left[i] = i;}

        else {
            temp = left[i - 1];
            while ((temp > 0)&&(heights[temp - 1] >= heights[i])) {
                temp = left[left[temp - 1]];
            }
            left[i] = temp;
        }
    }

    //the first idx, to the right of i, that is no smaller than current idx
    int right[length];right[length - 1] = length - 1;

    for (int i = length - 2; i >= 0; i--) {
        if (heights[i] > heights[i + 1]) {right[i] = i;}

        else {
            temp = right[i + 1];
            while ((temp < length - 1)&&(heights[temp + 1] >= heights[i])) {
                temp = right[right[temp + 1]];
            }
            right[i] = temp;
        }
    }

    /*if (test >= 0) {
        cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << left[i] << "\t";
        }
        cout << "\n\n";
        for (int i = 0; i < length; i++) {
            cout << right[i] << "\t";
        }
        cout << "\n\n";
    }*/

    int left_idx = -1, right_idx = -1;

    for (int i = 0, temp; i < length; i++) {
        if (heights[i] > 0) {
            temp = (right[i] - left[i] + 1) * heights[i];
            if (temp > max_area) {
                max_area = temp;
                if (test >= 0) {
                    left_idx = left[i], right_idx = right[i];
                }
            }
        }
    }

    if (test >= 0) {
        cout << "\nleft_idx = " << left_idx << ", right_idx = " << right_idx << "\n";
    }

    return max_area;
}


//blazing fast!
int largestRectangleArea_no_testing_part(vector<int>& heights) {
    int length = heights.size();
    if (length == 0) {return 0;}
    if (length == 1) {return heights[0];}

    int max_area = 0, temp;

    //the first idx, to the left of i, that is no smaller than current idx
    int left[length];left[0] = 0;
    for (int i = 1; i < length; i++) {
        if (heights[i] > heights[i - 1]) {left[i] = i;}

        else {
            temp = left[i - 1];
            while ((temp > 0)&&(heights[temp - 1] >= heights[i])) {
                temp = left[left[temp - 1]];
            }
            left[i] = temp;
        }
    }

    //the first idx, to the right of i, that is no smaller than current idx
    int right[length];right[length - 1] = length - 1;

    for (int i = length - 2; i >= 0; i--) {
        if (heights[i] > heights[i + 1]) {right[i] = i;}

        else {
            temp = right[i + 1];
            while ((temp < length - 1)&&(heights[temp + 1] >= heights[i])) {
                temp = right[right[temp + 1]];
            }
            right[i] = temp;
        }
    }

    for (int i = 0, temp; i < length; i++) {
        if (heights[i] > 0) {
            temp = (right[i] - left[i] + 1) * heights[i];

            if (temp > max_area) {max_area = temp;}
        }
    }

    return max_area;
}



int main(){
    srand(time(0));int length = 200000, lower_range = 0, upper_range = 200000, display = 0, input = 1;
    vector<int> wtf;

    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;

for (int m = 1; m <= 1000; m++) {if (m % 10 == 0) {cout << "m = " << m << "\n";}
    if (input == 1){
        wtf.reserve(length);
        for(int i = 0; i < length; i++){
            wtf.push_back(rand()%(upper_range - lower_range + 1) + lower_range);
        }
    }
    if (display == 1){
        /*for (int i = 0; i < wtf.size(); i++) {
            cout << i;if (i < wtf.size() - 1) {cout << "\t";}
        }*/

        cout << "\n\n = \n";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "\n";
    }

    start_point_1 = chrono::steady_clock::now();
    int shit = largestRectangleArea(wtf);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    //cout << "shit = " << shit << "\n";

    start_point_2 = chrono::steady_clock::now();
    int shitshit = largestRectangleArea_brute(wtf);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    //cout << "shitshit = " << shitshit << "\n\n";

    if (shit != shitshit) {
        cout << "something is wrong.\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
        cout << "shit = " << shit << "\n";
        cout << "shitshit = " << shitshit << "\n";
        break;
    }

wtf.clear();}

cout << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << duration <double, milli> (diff_2).count() << " ms" << "\n";
    return 0;
}




