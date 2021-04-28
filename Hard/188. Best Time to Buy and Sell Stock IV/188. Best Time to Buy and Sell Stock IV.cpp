/*188. Best Time to Buy and Sell Stock IV
Hard

You are given an integer array prices where prices[i] is the price of a given stock on the ith day,
and an integer k.

Find the maximum profit you can achieve.
You may complete at most k transactions.

Note:
You may not engage in multiple transactions simultaneously
(i.e., you must sell the stock before you buy again).

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.

Constraints:
    0 <= k <= 100
    0 <= prices.length <= 1000
    0 <= prices[i] <= 1000
*/

/*
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {

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

int maxProfit_brute_k_equals_to_four(int k, vector<int>& prices) {
    if (k == 0 || prices.size() == 0) { return 0; }
    int length = prices.size(), left = 0, right = -1;
    int test = 0;

    vector<vector<int>> zig_zag;// record ONLY LOCAL MAXIMA & MINIMA
    for (int i = 1; i < length; i++) {
        if (right > 0) {
            if (prices[i] >= prices[right]) {
                right = i;
                zig_zag[zig_zag.size() - 1][1] = prices[right];
            }

            else { left = i, right = -1; }
        }

        else {
            if (prices[i] <= prices[left]) { left = i; }

            else {
                right = i;

                zig_zag.push_back(vector<int> {prices[left], prices[right]});
            }
        }
    }

    // equals to zig_zag.size() == 0
    if (zig_zag.size() == 0) { return 0; }

    int result = 0;

    if (k >= zig_zag.size()) {
        for (int i = 0; i < zig_zag.size(); i++) { result += zig_zag[i][1] - zig_zag[i][0]; }
        return result;
    }
    else {
        for (int i = 0; i < k; i++) { result += zig_zag[i][1] - zig_zag[i][0]; }
    }

    if (test > 0) {
        cout << "the initial result = " << result << "\n\n";
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][1] << "\t";
        }
        cout << "\n";
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][0] << "\t";
        }
        cout << "\n";
    }

    int zig_zag_size = zig_zag.size();
    /*  zig_zag[cache[i][j][0]][0] is minimum price in range {i, j}, inclusuve
        zig_zag[cache[i][j][1]][1] is maximum price in range {i, j}, inclusive*/
    int cache[zig_zag_size][zig_zag_size][2]; // initialization might not be necessary, anyway it does not hurt
    for (int i = 0; i < zig_zag_size; i++) { for (int j = 0; j < zig_zag_size; j++) { cache[i][j][0] = -1, cache[i][j][1] = -1; } }

    int last_min_idx, last_max_idx;

    for (int i = 0; i < zig_zag_size; i++) {
        last_min_idx = i, last_max_idx = i;
        cache[i][i][0] = i, cache[i][i][1] = i;

        for (int j = i + 1; j < zig_zag_size; j++) {
            if (zig_zag[j][0] <= zig_zag[last_min_idx][0]) { last_min_idx = j; }

            if (zig_zag[j][1] >= zig_zag[last_max_idx][1]) { last_max_idx = j; }

            cache[i][j][0] = last_min_idx, cache[i][j][1] = last_max_idx;
        }
    }


    if (test > 0) {
        cout << "\n";
        for (int i = 0; i < zig_zag_size; i++) {
            for (int j = 0; j < zig_zag_size; j++) {
                cout << cache[i][j][1] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";

        for (int i = 0; i < zig_zag_size; i++) {
            for (int j = 0; j < zig_zag_size; j++) {
                cout << cache[i][j][0] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
    }


    int curr_idx[k][2]; for (int i = 0; i < k; i++) { curr_idx[i][0] = i, curr_idx[i][1] = i; }

    int curr_sum;
    for (int i = 0; i <= zig_zag_size - k; i++) {
        if (test > 0) { cout << "i = " << i << "\n"; }

        for (int j = i + 1; j <= zig_zag_size - k + 1; j++) {
            if (test > 0) { cout << "\tj = " << j << "\n"; }

            for (int l = j + 1; l <= zig_zag_size - k + 2; l++) {
                if (test > 0) { cout << "\t\tl = " << l << "\n"; }

                for (int m = l + 1; m <= zig_zag_size - k + 3; m++) {
                    if (test > 0) { cout << "\t\t\tm = " << m << "\n"; }


                    curr_sum = 0;
                    /*curr_sum += zig_zag[cache[0][i][1]][1] - zig_zag[cache[0][cache[0][i][1]][0]][0];
                    curr_sum += zig_zag[cache[i + 1][j][1]][1] - zig_zag[cache[i + 1][cache[i + 1][j][0]][0]][0];
                    curr_sum += zig_zag[cache[j + 1][l][1]][1] - zig_zag[cache[j + 1][cache[j + 1][l][0]][0]][0];
                    curr_sum += zig_zag[cache[l + 1][zig_zag_size - 1][1]][1] - zig_zag[cache[l + 1][cache[l + 1][zig_zag_size - 1][1]][0]][0];*/
                    curr_sum += zig_zag[cache[i][j - 1][1]][1] - zig_zag[cache[i][cache[i][j - 1][1]][0]][0];
                    curr_sum += zig_zag[cache[j][l - 1][1]][1] - zig_zag[cache[j][cache[j][l - 1][1]][0]][0];
                    curr_sum += zig_zag[cache[l][m - 1][1]][1] - zig_zag[cache[l][cache[l][m - 1][1]][0]][0];
                    curr_sum += zig_zag[cache[m][zig_zag_size - 1][1]][1] - zig_zag[cache[m][cache[m][zig_zag_size - 1][1]][0]][0];

                    if (curr_sum > result) {
                        result = curr_sum;
                        if (test > 0) {
                            cout << "duang~!\n";

                            /*cout << "curr_sum += " << zig_zag[cache[0][i][1]][1] - zig_zag[cache[0][cache[0][i][1]][0]][0] << "\n";
                            cout << "curr_sum += " << zig_zag[cache[i + 1][j][1]][1] - zig_zag[cache[i + 1][cache[i + 1][j][0]][0]][0] << "\n";
                            cout << "curr_sum += " << zig_zag[cache[j + 1][l][1]][1] - zig_zag[cache[j + 1][cache[j + 1][l][0]][0]][0] << "\n";
                            cout << "curr_sum += " << zig_zag[cache[l + 1][zig_zag_size - 1][1]][1] - zig_zag[cache[l + 1][cache[l + 1][zig_zag_size - 1][1]][0]][0] << "\n";*/
                            cout << "curr_sum += " << zig_zag[cache[i][j - 1][1]][1] - zig_zag[cache[i][cache[i][j - 1][1]][0]][0] << "\n";
                            cout << "curr_sum += " << zig_zag[cache[j][l - 1][1]][1] - zig_zag[cache[j][cache[j][l - 1][1]][0]][0] << "\n";
                            cout << "curr_sum += " << zig_zag[cache[l][m - 1][1]][1] - zig_zag[cache[l][cache[l][m - 1][1]][0]][0] << "\n";
                            cout << "curr_sum += " << zig_zag[cache[m][zig_zag_size - 1][1]][1] - zig_zag[cache[m][cache[m][zig_zag_size - 1][1]][0]][0] << "\n";
                        }
                    }
                }

            }
        }
    }

    if (test > 0) { cout << "\n\n\n"; }

    return result;
}



int maxProfit_does_not_work(int k, vector<int>& prices) {
    if (k == 0 || prices.size() == 0) { return 0; }
    int length = prices.size(), left = 0, right = -1;
    int test = 1;

    //cout << "~0\n";

    vector<vector<int>> zig_zag;// record ONLY LOCAL MAXIMA & MINIMA
    for (int i = 1; i < length; i++) {
        if (right > 0) {
            if (prices[i] >= prices[right]) {
                right = i;
                zig_zag[zig_zag.size() - 1][1] = prices[right];
            }

            else { left = i, right = -1; }
        }

        else {
            if (prices[i] <= prices[left]) { left = i; }

            else {
                right = i;

                zig_zag.push_back(vector<int> {prices[left], prices[right]});
            }
        }
    }

    //cout << "~1\n";

    // equals to zig_zag.size() == 0
    if (zig_zag.size() == 0) { return 0; }

    if (test > 0) {
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][1] << "\t";
        }
        cout << "\n";
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][0] << "\t";
        }
        cout << "\n";
    }

    //cout << "~2\n";

    int result = 0;

    if (k >= zig_zag.size()) { for (int i = 0; i < zig_zag.size(); i++) { result += zig_zag[i][1] - zig_zag[i][0]; } }

    //cout << "~3\n";

    else {
        for (int i = 0; i < k; i++) { result += zig_zag[i][1] - zig_zag[i][0]; }

        int zig_zag_size = zig_zag.size();
        // zig_zag[cache[i][j][0]][0] is minimum price in range {i, j}, inclusuve
        // zig_zag[cache[i][j][1]][1] is maximum price in range {i, j}, inclusive
        int cache[zig_zag_size][zig_zag_size][2];

        // initialization might not be necessary, anyway it does not hurt
        for (int i = 0; i < zig_zag_size; i++) {
            for (int j = 0; j < zig_zag_size; j++) { cache[i][j][0] = -1, cache[i][j][1] = -1; }
        }

        int last_min_idx, last_max_idx;
        for (int i = 0; i < zig_zag_size; i++) {
            last_min_idx = i, last_max_idx = i;
            cache[i][i][0] = i, cache[i][i][1] = i;

            for (int j = i + 1; j < zig_zag_size; j++) {
                if (zig_zag[j][0] <= zig_zag[last_min_idx][0]) { last_min_idx = j; }

                if (zig_zag[j][1] >= zig_zag[last_max_idx][1]) { last_max_idx = j; }

                cache[i][j][0] = last_min_idx, cache[i][j][1] = last_max_idx;
            }
        }

        if (test > 0) {
            cout << "\n";
            for (int i = 0; i < zig_zag_size; i++) {
                for (int j = 0; j < zig_zag_size; j++) {
                    cout << cache[i][j][1] << "\t";
                }
                cout << "\n";
            }
            cout << "\n";

            for (int i = 0; i < zig_zag_size; i++) {
                for (int j = 0; j < zig_zag_size; j++) {
                    cout << cache[i][j][0] << "\t";
                }
                cout << "\n";
            }
            cout << "\n";
        }

        int curr_idx[k][2]; for (int i = 0; i < k; i++) { curr_idx[i][0] = i, curr_idx[i][1] = i; }
        int curr_max = result;

        if (test > 0) { cout << "initial result = " << result << "\n\n"; }

        while (curr_idx[0][0] < zig_zag_size - k) {
            //curr_max = result;

            //cout << "curr_idx[0][0] = " << curr_idx[0][0] << "\n";

            for (int i = k - 1; i >= 0; i--) {
                if (test > 0) { cout << "i = " << i << "\n"; }

                last_max_idx = curr_idx[i][1], last_min_idx = curr_idx[i][0];

                if (i < k - 1) {
                    if (test > 0) { cout << "i < k - 1\n";}
                    curr_idx[i][1] = cache[last_max_idx + 1][curr_idx[i + 1][0] - 1][1];

                    curr_max += zig_zag[curr_idx[i][1]][1] - zig_zag[last_max_idx][1];
                    if (test > 0) { cout << "curr_max = " << curr_max << "\n"; }

                    if (curr_max > result) {
                        result = curr_max;
                        if (test > 0) { cout << "result = curr_max\n"; }
                    }

                    curr_idx[i][0] = cache[last_min_idx + 1][curr_idx[i][1]][0];

                    curr_max += zig_zag[last_min_idx][0] - zig_zag[curr_idx[i][0]][0];
                    if (test > 0) { cout << "curr_max = " << curr_max << "\n"; }

                    if (curr_max > result) {
                        result = curr_max;
                        if (test > 0) { cout << "result = curr_max\n"; }
                    }
                }

                else if (curr_idx[i][1] < zig_zag_size - 1) {
                    if (test > 0) { cout << "curr_idx[i][1] < zig_zag_size - 1\n"; }

                    curr_idx[i][1] = cache[last_max_idx + 1][zig_zag_size - 1][1];

                    curr_max += zig_zag[curr_idx[i][1]][1] - zig_zag[last_max_idx][1];
                    if (test > 0) { cout << "curr_max = " << curr_max << "\n"; }

                    if (curr_max > result) {
                        result = curr_max;
                        if (test > 0) { cout << "result = curr_max\n"; }
                    }

                    curr_idx[i][0] = cache[last_min_idx + 1][curr_idx[i][1]][0];

                    curr_max += zig_zag[last_min_idx][0] - zig_zag[curr_idx[i][0]][0];
                    if (test > 0) { cout << "curr_max = " << curr_max << "\n"; }

                    if (curr_max > result) {
                        result = curr_max;
                        if (test > 0) { cout << "result = curr_max\n"; }
                    }
                }

                else if (curr_idx[i][0] < curr_idx[i][1]) {
                    if (test > 0) { cout << "curr_idx[i][0] < curr_idx[i][1]\n"; }

                    curr_idx[i][0] = cache[last_min_idx + 1][curr_idx[i][1]][0];

                    curr_max += zig_zag[last_min_idx][0] - zig_zag[curr_idx[i][0]][0];
                    if (test > 0) { cout << "curr_max = " << curr_max << "\n"; }

                    if (curr_max > result) {
                        result = curr_max;
                        if (test > 0) { cout << "result = curr_max\n"; }
                    }
                }

                if (test > 0) { cout << "\n"; }
            }

            if (test > 0) { cout << "\n"; }
        }
    }

    return result;
}



int maxProfit_the_first_draft_that_might_work(int k, vector<int>& prices) {
    if (k == 0 || prices.size() == 0) { return 0; }
    int length = prices.size(), left = 0, right = -1;
    int test = 0;

    vector<vector<int>> zig_zag;// record ONLY LOCAL MAXIMA & MINIMA
    for (int i = 1; i < length; i++) {
        if (right > 0) {
            if (prices[i] >= prices[right]) {
                right = i;
                zig_zag[zig_zag.size() - 1][1] = prices[right];
            }

            else { left = i, right = -1; }
        }

        else {
            if (prices[i] <= prices[left]) { left = i; }

            else {
                right = i;

                zig_zag.push_back(vector<int> {prices[left], prices[right]});
            }
        }
    }

    // equals to zig_zag.size() == 0
    if (zig_zag.size() == 0) { return 0; }

    if (test > 0) {
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][1] << "\t";
        }
        cout << "\n";
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][0] << "\t";
        }
        cout << "\n";
    }

    int result = 0;
    if (k >= zig_zag.size()) { for (int i = 0; i < zig_zag.size(); i++) { result += zig_zag[i][1] - zig_zag[i][0]; } }

    else {
        int zig_zag_size = zig_zag.size();
        // zig_zag[cache[i][j][0]][0] is minimum price in range {i, j}, inclusive
        // zig_zag[cache[i][j][1]][1] is maximum price in range {i, j}, inclusive
        int cache[zig_zag_size][zig_zag_size][2];

        // initialization might not be necessary, anyway it does not hurt
        for (int i = 0; i < zig_zag_size; i++) {
            for (int j = 0; j < zig_zag_size; j++) { cache[i][j][0] = -1, cache[i][j][1] = -1; }
        }

        int last_min_idx, last_max_idx;
        for (int i = 0; i < zig_zag_size; i++) {
            last_min_idx = i, last_max_idx = i;
            cache[i][i][0] = i, cache[i][i][1] = i;

            for (int j = i + 1; j < zig_zag_size; j++) {
                if (zig_zag[j][0] <= zig_zag[last_min_idx][0]) { last_min_idx = j; }

                if (zig_zag[j][1] >= zig_zag[last_max_idx][1]) { last_max_idx = j; }

                cache[i][j][0] = last_min_idx, cache[i][j][1] = last_max_idx;
            }
        }

        if (test > 1) {
            cout << "\n";
            for (int i = 0; i < zig_zag_size; i++) {
                for (int j = 0; j < zig_zag_size; j++) {
                    cout << cache[i][j][1] << "\t";
                }
                cout << "\n";
            }
            cout << "\n";

            for (int i = 0; i < zig_zag_size; i++) {
                for (int j = 0; j < zig_zag_size; j++) {
                    cout << cache[i][j][0] << "\t";
                }
                cout << "\n";
            }
            cout << "\n";
        }

        int window_1[zig_zag_size - k + 1];// k
        int window_2[zig_zag_size - k + 1];// k
        int candidate_idx_of_sum; // in window
        int candidate_idx_of_min; // in zig_zag
        int temp, curr_max, max_sum_idx, min_idx_after_max;
        for (int i = 0; i < zig_zag_size - k + 1; i++) { window_1[i] = zig_zag[i][1] - zig_zag[cache[0][i][0]][0]; }

        if (test > 0) {
            cout << "\n";
            for (int i = 0; i < zig_zag_size - k + 1; i++) {
                cout << window_1[i] << " ";
            }
            cout << "\n\n";
        }

        int from_1_to_2 = 1;
        for (int i = 1; i < k; i++) {// zig_zag_size - k
            if (test > 0) { cout << "i = " << i << "\n"; }

            if (from_1_to_2 == 1) {
                candidate_idx_of_sum = 0, candidate_idx_of_min = i;

                max_sum_idx = 0, min_idx_after_max = i;

                window_2[0] = window_1[0] - zig_zag[i][0] + zig_zag[i][1];

                for (int j = 1; j < zig_zag_size - k + 1; j++) {
                    if (window_1[j] > window_1[max_sum_idx]) {
                        max_sum_idx = j;
                        min_idx_after_max = i + j;
                    }

                    else if (zig_zag[min_idx_after_max][0] >= zig_zag[i + j][0]) {
                        min_idx_after_max = i + j;
                    }

                    if (zig_zag[candidate_idx_of_min][0] >= zig_zag[i + j][0]) {
                        candidate_idx_of_min = i + j;
                    }

                    if (test > 0) {
                        cout << "\tj = " << j << "\n";
                        cout << "\twindow_1[" << candidate_idx_of_sum << "] = " << window_1[candidate_idx_of_sum];
                        cout << ", zig_zag[" << candidate_idx_of_min << "][0] = " << zig_zag[candidate_idx_of_min][0];
                        cout << "\n\twindow_1[" << max_sum_idx << "] = " << window_1[max_sum_idx];
                        cout << ", zig_zag[" << min_idx_after_max << "][0] = " << zig_zag[min_idx_after_max][0] << "\n\n";

                    }

                    /*if (window_1[candidate_idx_of_sum] >= window_1[j]) {
                        if (test > 0) { cout << "\twindow_1[candidate_idx_of_sum] >= window_1[j]\n"; }

                        if (zig_zag[i + j][0] >= zig_zag[candidate_idx_of_min][0]) {
                            if (test > 0) { cout << "\tzig_zag[i + j][0] >= zig_zag[" << candidate_idx_of_min << "][0]\n"; }

                            window_2[j] = window_1[candidate_idx_of_sum] + zig_zag[i + j][1] - zig_zag[candidate_idx_of_min][0];
                        }

                        else {
                            if (test > 0) { cout << "\tzig_zag[i + j][0] < zig_zag[" << candidate_idx_of_min << "][0]\n"; }

                            candidate_idx_of_min = i + j;
                            window_2[j] = window_1[candidate_idx_of_sum] + zig_zag[i + j][1] - zig_zag[i + j][0];
                        }
                    }

                    else {
                        if (test > 0) { cout << "\twindow_1[candidate_idx_of_sum] < window_1[j]\n"; }

                        if (window_1[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0] >= window_1[max_sum_idx] - zig_zag[i + j][0]) {
                            if (test > 0) { cout << "\twindow_1[candidate_idx_of_sum] - zig_zag[" << candidate_idx_of_min << "][0] >= window_1[" << max_sum_idx << "] - zig_zag[i + j][0]\n"; }

                            window_2[j] = window_1[candidate_idx_of_sum] + zig_zag[i + j][1] - zig_zag[candidate_idx_of_min][0];
                        }

                        else {// including (zig_zag[i + j][0] <= zig_zag[candidate_idx_of_min][0])
                            if (test > 0) { cout << "\twindow_1[candidate_idx_of_sum] - zig_zag[" << candidate_idx_of_min << "][0] < window_1[" << max_sum_idx << "] - zig_zag[i + j][0]\n"; }

                            window_2[j] = window_1[max_sum_idx] + zig_zag[i + j][1] - zig_zag[i + j][0];
                            candidate_idx_of_sum = max_sum_idx;
                            candidate_idx_of_min = i + j;
                        }
                    }*/

                    if (window_1[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0]
                        < window_1[max_sum_idx] - zig_zag[min_idx_after_max][0]) {

                        candidate_idx_of_sum = max_sum_idx;
                        candidate_idx_of_min = min_idx_after_max;
                        window_2[j] = window_1[max_sum_idx] - zig_zag[min_idx_after_max][0] + zig_zag[i + j][1];

                        if (test > 0) {
                            cout << "\twindow_1[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] < window_1[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_2[" << j << "] = " << window_1[max_sum_idx] << " - " << zig_zag[min_idx_after_max][0] << " + " << zig_zag[i + j][1] << "\n";
                        }
                    }

                    else {
                        window_2[j] = window_1[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0] + zig_zag[i + j][1];

                        if (test > 0) {
                            cout << "\twindow_1[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] >= window_1[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_2[" << j << "] = " << window_1[candidate_idx_of_sum] << " - " << zig_zag[candidate_idx_of_min][0] << " + " << zig_zag[i + j][1] << "\n";
                        }
                    }

                    if (test > 0) { cout << "\n"; }
                }

                from_1_to_2 = 0;

                if (test > 0) {
                    cout << "window_2\n";
                    for (int i = 0; i < zig_zag_size - k + 1; i++) {
                        cout << window_2[i] << " ";
                    }
                    cout << "\n\n";
                }
            }

            else {
                /*candidate_idx_of_sum = 0;
                candidate_idx_of_min = i;
                max_sum_idx = 0;
                window_1[0] = window_2[0] - zig_zag[i][0] + zig_zag[i][1];*/

                /*for (int j = 1; j < zig_zag_size - k + 1; j++) {
                    temp = window_2[j] - zig_zag[i + j][0];
                    if (test > 0) {
                        cout << "\tj = " << j << "\n";
                        cout << "\ttemp = " << temp << "\n";
                        cout << "\tcurr_max = " << curr_max << "\n";
                    }

                    if (temp > curr_max) {
                        if (test > 0) { cout << "\ttemp > curr_max\n"; }
                        curr_max = temp;
                        candidate_idx_of_sum = j;
                        candidate_idx_of_min = i + j;
                    }

                    else if (zig_zag[i + j][0] < zig_zag[candidate_idx_of_min][0]) {
                        if (test > 0) { cout << "\tzig_zag[i + j][0] < zig_zag[candidate_idx_of_min][0]\n"; }
                        curr_max += zig_zag[candidate_idx_of_min][0] - zig_zag[i + j][0];
                        candidate_idx_of_min = i + j;
                    }

                    //else { curr_max = zig_zag[i + j][1] - zig_zag[candidate_idx_of_min][0] + window_2[candidate_idx_of_sum]; }

                    window_1[j] = curr_max + zig_zag[i + j][1];

                    if (test > 0) { cout << "\n"; }
                }*/

                /*for (int j = 1; j < zig_zag_size - k + 1; j++) {
                    if (window_2[j] > window_2[max_sum_idx]) { max_sum_idx = j; }
                    if (zig_zag[candidate_idx_of_min][0] > zig_zag[j][0]) { candidate_idx_of_min = j; }

                    if (test > 0) {
                        cout << "\tj = " << j << "\n";
                        cout << "\twindow_2[" << candidate_idx_of_sum << "] = " << window_2[candidate_idx_of_sum];
                        cout << ", window_2[" << j << "] = " << window_2[j] << "\n";
                        cout << "\twindow_2[max_sum_idx] = " << window_2[max_sum_idx] << "\n";
                    }



                    if (window_2[candidate_idx_of_sum] >= window_2[j]) {
                        if (test > 0) { cout << "\twindow_2[candidate_idx_of_sum] >= window_2[j]\n"; }

                        if (zig_zag[i + j][0] >= zig_zag[candidate_idx_of_min][0]) {
                            if (test > 0) { cout << "\tzig_zag[i + j][0] >= zig_zag[" << candidate_idx_of_min << "][0]\n"; }

                            window_1[j] = window_2[candidate_idx_of_sum] + zig_zag[i + j][1] - zig_zag[candidate_idx_of_min][0];
                        }

                        else {
                            if (test > 0) { cout << "\tzig_zag[i + j][0] < zig_zag[" << candidate_idx_of_min << "][0]\n"; }

                            candidate_idx_of_min = i + j;
                            window_1[j] = window_2[candidate_idx_of_sum] + zig_zag[i + j][1] - zig_zag[i + j][0];
                        }
                    }

                    else {
                        if (test > 0) { cout << "\twindow_2[candidate_idx_of_sum] < window_2[j]\n"; }

                        if (window_2[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0] >= window_2[max_sum_idx] - zig_zag[i + j][0]) {
                            if (test > 0) { cout << "\twindow_2[candidate_idx_of_sum] - zig_zag[" << candidate_idx_of_min << "][0] >= window_2[" << max_sum_idx << "] - zig_zag[i + j][0]\n"; }

                            window_1[j] = window_2[candidate_idx_of_sum] + zig_zag[i + j][1] - zig_zag[candidate_idx_of_min][0];
                        }

                        else {// including (zig_zag[i + j][0] <= zig_zag[candidate_idx_of_min][0])
                            if (test > 0) { cout << "\twindow_2[candidate_idx_of_sum] - zig_zag[" << candidate_idx_of_min << "][0] < window_2[" << max_sum_idx << "] - zig_zag[i + j][0]\n"; }

                            window_1[j] = window_2[max_sum_idx] + zig_zag[i + j][1] - zig_zag[i + j][0];
                            candidate_idx_of_sum = max_sum_idx;
                            candidate_idx_of_min = i + j;
                        }
                    }

                    if (test > 0) { cout << "\n"; }
                }
                */


                candidate_idx_of_sum = 0, candidate_idx_of_min = i;

                max_sum_idx = 0, min_idx_after_max = i;

                window_1[0] = window_2[0] - zig_zag[i][0] + zig_zag[i][1];

                for (int j = 1; j < zig_zag_size - k + 1; j++) {
                    if (window_2[j] > window_2[max_sum_idx]) {
                        max_sum_idx = j;
                        min_idx_after_max = i + j;
                    }

                    else if (zig_zag[min_idx_after_max][0] >= zig_zag[i + j][0]) {
                        min_idx_after_max = i + j;
                    }

                    if (zig_zag[candidate_idx_of_min][0] >= zig_zag[i + j][0]) {
                        candidate_idx_of_min = i + j;
                    }

                    if (test > 0) {
                        cout << "\tj = " << j << "\n";
                        cout << "\twindow_2[" << candidate_idx_of_sum << "] = " << window_2[candidate_idx_of_sum];
                        cout << ", zig_zag[" << candidate_idx_of_min << "][0] = " << zig_zag[candidate_idx_of_min][0];
                        cout << "\n\twindow_2[" << max_sum_idx << "] = " << window_2[max_sum_idx];
                        cout << ", zig_zag[" << min_idx_after_max << "][0] = " << zig_zag[min_idx_after_max][0] << "\n\n";

                    }

                    if (window_2[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0]
                        < window_2[max_sum_idx] - zig_zag[min_idx_after_max][0]) {

                        candidate_idx_of_sum = max_sum_idx;
                        candidate_idx_of_min = min_idx_after_max;
                        window_1[j] = window_2[max_sum_idx] - zig_zag[min_idx_after_max][0] + zig_zag[i + j][1];

                        if (test > 0) {
                            cout << "\twindow_2[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] < window_2[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_1[" << j << "] = " << window_2[max_sum_idx] << " - " << zig_zag[min_idx_after_max][0] << " + " << zig_zag[i + j][1] << "\n";
                        }
                    }

                    else {
                        window_1[j] = window_2[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0] + zig_zag[i + j][1];

                        if (test > 0) {
                            cout << "\twindow_2[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] < window_2[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_1[" << j << "] = " << window_2[candidate_idx_of_sum] << " - " << zig_zag[candidate_idx_of_min][0] << " + " << zig_zag[i + j][1] << "\n";
                        }
                    }

                    if (test > 0) { cout << "\n"; }
                }

                from_1_to_2 = 1;

                if (test > 0) {
                    cout << "window_1\n";
                    for (int i = 0; i < zig_zag_size - k + 1; i++) {
                        cout << window_1[i] << " ";
                    }
                    cout << "\n\n";
                }
            }
        }

        if (from_1_to_2 == 1) {
            for (int i = 0; i < zig_zag_size - k + 1; i++) {
                if (window_1[i] > result) {
                    result = window_1[i];
                }
            }
        }

        else {
            for (int i = 0; i < zig_zag_size - k + 1; i++) {
                if (window_2[i] > result) {
                    result = window_2[i];
                }
            }
        }
    }

    return result;
}


//along with many others, this code is in 0ms cluster
int maxProfit_this_one_works_well(int k, vector<int>& prices) {
    if (k == 0 || prices.size() == 0) { return 0; }
    int length = prices.size(), left = 0, right = -1;
    int test = 0;

    vector<vector<int>> zig_zag;// record ONLY LOCAL MAXIMA & MINIMA
    for (int i = 1; i < length; i++) {
        if (right > 0) {
            if (prices[i] >= prices[right]) {
                right = i;
                zig_zag[zig_zag.size() - 1][1] = prices[right];
            }

            else { left = i, right = -1; }
        }

        else {
            if (prices[i] <= prices[left]) { left = i; }

            else {
                right = i;

                zig_zag.push_back(vector<int> {prices[left], prices[right]});
            }
        }
    }

    // equals to zig_zag.size() == 0
    if (zig_zag.size() == 0) { return 0; }

    if (test > 0) {
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][1] << "\t";
        }
        cout << "\n";
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][0] << "\t";
        }
        cout << "\n";
    }

    int result = 0;
    if (k >= zig_zag.size()) { for (int i = 0; i < zig_zag.size(); i++) { result += zig_zag[i][1] - zig_zag[i][0]; } }

    else {
        int zig_zag_size = zig_zag.size();
        // zig_zag[cache[i][j][0]][0] is minimum price in range {i, j}, inclusive
        // zig_zag[cache[i][j][1]][1] is maximum price in range {i, j}, inclusive
        int cache[zig_zag_size][zig_zag_size][2];

        // initialization might not be necessary, anyway it does not hurt
        /*for (int i = 0; i < zig_zag_size; i++) {
            for (int j = 0; j < zig_zag_size; j++) { cache[i][j][0] = -1, cache[i][j][1] = -1; }
        }*/

        int last_min_idx, last_max_idx;
        for (int i = 0; i < zig_zag_size; i++) {
            last_min_idx = i, last_max_idx = i;
            cache[i][i][0] = i, cache[i][i][1] = i;

            for (int j = i + 1; j < zig_zag_size; j++) {
                if (zig_zag[j][0] <= zig_zag[last_min_idx][0]) { last_min_idx = j; }

                if (zig_zag[j][1] >= zig_zag[last_max_idx][1]) { last_max_idx = j; }

                cache[i][j][0] = last_min_idx, cache[i][j][1] = last_max_idx;
            }
        }

        if (test > 1) {
            cout << "\n";
            for (int i = 0; i < zig_zag_size; i++) {
                for (int j = 0; j < zig_zag_size; j++) {
                    cout << cache[i][j][1] << "\t";
                }
                cout << "\n";
            }
            cout << "\n";

            for (int i = 0; i < zig_zag_size; i++) {
                for (int j = 0; j < zig_zag_size; j++) {
                    cout << cache[i][j][0] << "\t";
                }
                cout << "\n";
            }
            cout << "\n";
        }

        int window_1[zig_zag_size - k + 1];// k
        int window_2[zig_zag_size - k + 1];// k
        int candidate_idx_of_sum; // in window
        int candidate_idx_of_min; // in zig_zag
        int temp, curr_max, max_sum_idx, min_idx_after_max;
        for (int i = 0; i < zig_zag_size - k + 1; i++) { window_1[i] = zig_zag[i][1] - zig_zag[cache[0][i][0]][0]; }

        if (test > 0) {
            cout << "\n";
            for (int i = 0; i < zig_zag_size - k + 1; i++) {
                cout << window_1[i] << " ";
            }
            cout << "\n\n";
        }

        int from_1_to_2 = 1;
        for (int i = 1; i < k; i++) {// zig_zag_size - k
            if (test > 0) { cout << "i = " << i << "\n"; }

            if (from_1_to_2 == 1) {
                candidate_idx_of_sum = 0, candidate_idx_of_min = i;

                max_sum_idx = 0, min_idx_after_max = i;

                window_2[0] = window_1[0] - zig_zag[i][0] + zig_zag[i][1];

                for (int j = 1; j < zig_zag_size - k + 1; j++) {
                    if (window_1[j] > window_1[max_sum_idx]) {
                        max_sum_idx = j;
                        min_idx_after_max = i + j;
                    }

                    else if (zig_zag[min_idx_after_max][0] >= zig_zag[i + j][0]) {
                        min_idx_after_max = i + j;
                    }

                    if (zig_zag[candidate_idx_of_min][0] >= zig_zag[i + j][0]) {
                        candidate_idx_of_min = i + j;
                    }

                    if (test > 0) {
                        cout << "\tj = " << j << "\n";
                        cout << "\twindow_1[" << candidate_idx_of_sum << "] = " << window_1[candidate_idx_of_sum];
                        cout << ", zig_zag[" << candidate_idx_of_min << "][0] = " << zig_zag[candidate_idx_of_min][0];
                        cout << "\n\twindow_1[" << max_sum_idx << "] = " << window_1[max_sum_idx];
                        cout << ", zig_zag[" << min_idx_after_max << "][0] = " << zig_zag[min_idx_after_max][0] << "\n\n";

                    }

                    if (window_1[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0]
                        < window_1[max_sum_idx] - zig_zag[min_idx_after_max][0]) {

                        candidate_idx_of_sum = max_sum_idx;
                        candidate_idx_of_min = min_idx_after_max;
                        window_2[j] = window_1[max_sum_idx] - zig_zag[min_idx_after_max][0] + zig_zag[i + j][1];

                        if (test > 0) {
                            cout << "\twindow_1[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] < window_1[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_2[" << j << "] = " << window_1[max_sum_idx] << " - " << zig_zag[min_idx_after_max][0] << " + " << zig_zag[i + j][1] << "\n";
                        }
                    }

                    else {
                        window_2[j] = window_1[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0] + zig_zag[i + j][1];

                        if (test > 0) {
                            cout << "\twindow_1[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] >= window_1[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_2[" << j << "] = " << window_1[candidate_idx_of_sum] << " - " << zig_zag[candidate_idx_of_min][0] << " + " << zig_zag[i + j][1] << "\n";
                        }
                    }

                    if (test > 0) { cout << "\n"; }
                }

                from_1_to_2 = 0;

                if (test > 0) {
                    cout << "window_2\n";
                    for (int i = 0; i < zig_zag_size - k + 1; i++) {
                        cout << window_2[i] << " ";
                    }
                    cout << "\n\n";
                }
            }

            else {
                candidate_idx_of_sum = 0, candidate_idx_of_min = i;

                max_sum_idx = 0, min_idx_after_max = i;

                window_1[0] = window_2[0] - zig_zag[i][0] + zig_zag[i][1];

                for (int j = 1; j < zig_zag_size - k + 1; j++) {
                    if (window_2[j] > window_2[max_sum_idx]) {
                        max_sum_idx = j;
                        min_idx_after_max = i + j;
                    }

                    else if (zig_zag[min_idx_after_max][0] >= zig_zag[i + j][0]) {
                        min_idx_after_max = i + j;
                    }

                    if (zig_zag[candidate_idx_of_min][0] >= zig_zag[i + j][0]) {
                        candidate_idx_of_min = i + j;
                    }

                    if (test > 0) {
                        cout << "\tj = " << j << "\n";
                        cout << "\twindow_2[" << candidate_idx_of_sum << "] = " << window_2[candidate_idx_of_sum];
                        cout << ", zig_zag[" << candidate_idx_of_min << "][0] = " << zig_zag[candidate_idx_of_min][0];
                        cout << "\n\twindow_2[" << max_sum_idx << "] = " << window_2[max_sum_idx];
                        cout << ", zig_zag[" << min_idx_after_max << "][0] = " << zig_zag[min_idx_after_max][0] << "\n\n";

                    }

                    if (window_2[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0]
                        < window_2[max_sum_idx] - zig_zag[min_idx_after_max][0]) {

                        candidate_idx_of_sum = max_sum_idx;
                        candidate_idx_of_min = min_idx_after_max;
                        window_1[j] = window_2[max_sum_idx] - zig_zag[min_idx_after_max][0] + zig_zag[i + j][1];

                        if (test > 0) {
                            cout << "\twindow_2[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] < window_2[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_1[" << j << "] = " << window_2[max_sum_idx] << " - " << zig_zag[min_idx_after_max][0] << " + " << zig_zag[i + j][1] << "\n";
                        }
                    }

                    else {
                        window_1[j] = window_2[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0] + zig_zag[i + j][1];

                        if (test > 0) {
                            cout << "\twindow_2[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] < window_2[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_1[" << j << "] = " << window_2[candidate_idx_of_sum] << " - " << zig_zag[candidate_idx_of_min][0] << " + " << zig_zag[i + j][1] << "\n";
                        }
                    }

                    if (test > 0) { cout << "\n"; }
                }

                from_1_to_2 = 1;

                if (test > 0) {
                    cout << "window_1\n";
                    for (int i = 0; i < zig_zag_size - k + 1; i++) {
                        cout << window_1[i] << " ";
                    }
                    cout << "\n\n";
                }
            }
        }

        if (from_1_to_2 == 1) {
            for (int i = 0; i < zig_zag_size - k + 1; i++) {
                if (window_1[i] > result) {
                    result = window_1[i];
                }
            }
        }

        else {
            for (int i = 0; i < zig_zag_size - k + 1; i++) {
                if (window_2[i] > result) {
                    result = window_2[i];
                }
            }
        }
    }

    return result;
}


// FIND IT HARD TO EXLAIN
/*EXPLANATION

Step One
    Simplify the original array into an array (zig_zag) which contains ONLY LOCAL MAXIMA & MINIMA,
    starting from the 1st minima + IGNORING the 1st MAXIMA

Step Two
    Scenario Zero -- Trivial -- (zig_zag.size() == 0)
        the array is mono-descending, no profit can be reaped, return 0

    Scenario One -- Trivial -- (k >= zig_zag.size())
        add every adjacent (maxima - minima) --- this is the result

    Scenario Two -- Fun Stuff -- (k < zig_zag.size())
        IT'S LIKE A SLIDING WINDOW!

        after the trivial 0th index

        starting from the 1th index for every index i of all k indexes

            given the max profit of the previous index
                in previous window-starting index n
                window[m] is the MAX PROFIT for index m (of all k indexes) if it ended up in (m + n)th index of zig_zag

            using info of previous window, we calculate all max profit candidate for current_index
                the beginning of every window is always trivial


    shit I find it hard to explain clearly

*/
int maxProfit(int k, vector<int>& prices) {
    if (k == 0 || prices.size() == 0) { return 0; }
    int length = prices.size();
    //  int test = 0;
    int left = 0, right = -1;// helper
    vector<vector<int>> zig_zag;// record ONLY LOCAL MAXIMA & MINIMA, ignoring the 1st maxima
    /*  zig_zag[0][0] is the 1st minima, zig_zag[0][1] is the immediate maxima after zig_zag[0][0],
        zig_zag[1][0] is the 2nd minima, zig_zag[1][1] is the immediate 2nd maxima after zig_zag[1][0]
        and so on, and on*/
    for (int i = 1; i < length; i++) {
        if (right > 0) {
            if (prices[i] >= prices[right]) {
                right = i;
                zig_zag[zig_zag.size() - 1][1] = prices[right];
            }

            else { left = i, right = -1; }
        }

        else {
            if (prices[i] <= prices[left]) { left = i; }

            else {
                right = i;

                zig_zag.push_back(vector<int> {prices[left], prices[right]});
            }
        }
    }

    //  trivial Scenario Zero, (zig_zag.size() == 0) means the this array is monotonically descending, 0 benefit
    if (zig_zag.size() == 0) { return 0; }

    /*if (test > 0) {
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][1] << "\t";
        }
        cout << "\n";
        for (int i = 0; i < zig_zag.size(); i++) {
            cout << zig_zag[i][0] << "\t";
        }
        cout << "\n";
    }*/

    int result = 0;
    //  trivial Scenario One, add
    if (k >= zig_zag.size()) { for (int i = 0; i < zig_zag.size(); i++) { result += zig_zag[i][1] - zig_zag[i][0]; } }

    //  non-trivial Scenario Two - this is the fun stuff
    else {
        int zig_zag_size = zig_zag.size();// merely for convenience
        /*  zig_zag[cache[i][j][0]][0] is minimum price in range {i, j}, inclusive
            zig_zag[cache[i][j][1]][1] is maximum price in range {i, j}, inclusive*/
        int cache[zig_zag_size][zig_zag_size][2];

        int last_min_idx, last_max_idx;
        for (int i = 0; i < zig_zag_size; i++) {
            last_min_idx = i, last_max_idx = i;
            cache[i][i][0] = i, cache[i][i][1] = i;

            for (int j = i + 1; j < zig_zag_size; j++) {
                if (zig_zag[j][0] <= zig_zag[last_min_idx][0]) { last_min_idx = j; }

                if (zig_zag[j][1] >= zig_zag[last_max_idx][1]) { last_max_idx = j; }

                cache[i][j][0] = last_min_idx, cache[i][j][1] = last_max_idx;
            }
        }

        /*if (test > 1) {
            cout << "\n";
            for (int i = 0; i < zig_zag_size; i++) {
                for (int j = 0; j < zig_zag_size; j++) {
                    cout << cache[i][j][1] << "\t";
                }
                cout << "\n";
            }
            cout << "\n";

            for (int i = 0; i < zig_zag_size; i++) {
                for (int j = 0; j < zig_zag_size; j++) {
                    cout << cache[i][j][0] << "\t";
                }
                cout << "\n";
            }
            cout << "\n";
        }*/

        int window_1[zig_zag_size - k + 1];
        int window_2[zig_zag_size - k + 1];
        int candidate_idx_of_sum; // in window
        int candidate_idx_of_min; // in zig_zag
        int max_sum_idx, min_idx_after_max;

        for (int i = 0; i < zig_zag_size - k + 1; i++) { window_1[i] = zig_zag[i][1] - zig_zag[cache[0][i][0]][0]; }

        /*if (test > 0) {
            cout << "\n";
            for (int i = 0; i < zig_zag_size - k + 1; i++) {
                cout << window_1[i] << " ";
            }
            cout << "\n\n";
        }*/

        int from_1_to_2 = 1;
        for (int i = 1; i < k; i++) {
            //if (test > 0) { cout << "i = " << i << "\n"; }

            if (from_1_to_2 == 1) {
                candidate_idx_of_sum = 0, candidate_idx_of_min = i;

                max_sum_idx = 0, min_idx_after_max = i;

                window_2[0] = window_1[0] - zig_zag[i][0] + zig_zag[i][1];

                for (int j = 1; j < zig_zag_size - k + 1; j++) {
                    if (window_1[j] > window_1[max_sum_idx]) {
                        max_sum_idx = j;
                        min_idx_after_max = i + j;
                    }

                    else if (zig_zag[min_idx_after_max][0] >= zig_zag[i + j][0]) {
                        min_idx_after_max = i + j;
                    }

                    if (zig_zag[candidate_idx_of_min][0] >= zig_zag[i + j][0]) {
                        candidate_idx_of_min = i + j;
                    }

                    /*if (test > 0) {
                        cout << "\tj = " << j << "\n";
                        cout << "\twindow_1[" << candidate_idx_of_sum << "] = " << window_1[candidate_idx_of_sum];
                        cout << ", zig_zag[" << candidate_idx_of_min << "][0] = " << zig_zag[candidate_idx_of_min][0];
                        cout << "\n\twindow_1[" << max_sum_idx << "] = " << window_1[max_sum_idx];
                        cout << ", zig_zag[" << min_idx_after_max << "][0] = " << zig_zag[min_idx_after_max][0] << "\n\n";

                    }*/

                    if (window_1[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0]
                        < window_1[max_sum_idx] - zig_zag[min_idx_after_max][0]) {

                        candidate_idx_of_sum = max_sum_idx;
                        candidate_idx_of_min = min_idx_after_max;
                        window_2[j] = window_1[max_sum_idx] - zig_zag[min_idx_after_max][0] + zig_zag[i + j][1];

                        /*if (test > 0) {
                            cout << "\twindow_1[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] < window_1[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_2[" << j << "] = " << window_1[max_sum_idx] << " - " << zig_zag[min_idx_after_max][0] << " + " << zig_zag[i + j][1] << "\n";
                        }*/
                    }

                    else {
                        window_2[j] = window_1[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0] + zig_zag[i + j][1];

                        /*if (test > 0) {
                            cout << "\twindow_1[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] >= window_1[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_2[" << j << "] = " << window_1[candidate_idx_of_sum] << " - " << zig_zag[candidate_idx_of_min][0] << " + " << zig_zag[i + j][1] << "\n";
                        }*/
                    }

                    //if (test > 0) { cout << "\n"; }
                }

                from_1_to_2 = 0;

                /*if (test > 0) {
                    cout << "window_2\n";
                    for (int i = 0; i < zig_zag_size - k + 1; i++) {
                        cout << window_2[i] << " ";
                    }
                    cout << "\n\n";
                }*/
            }

            else {
                candidate_idx_of_sum = 0, candidate_idx_of_min = i;

                max_sum_idx = 0, min_idx_after_max = i;

                window_1[0] = window_2[0] - zig_zag[i][0] + zig_zag[i][1];

                for (int j = 1; j < zig_zag_size - k + 1; j++) {
                    if (window_2[j] > window_2[max_sum_idx]) {
                        max_sum_idx = j;
                        min_idx_after_max = i + j;
                    }

                    else if (zig_zag[min_idx_after_max][0] >= zig_zag[i + j][0]) {
                        min_idx_after_max = i + j;
                    }

                    if (zig_zag[candidate_idx_of_min][0] >= zig_zag[i + j][0]) {
                        candidate_idx_of_min = i + j;
                    }

                    /*if (test > 0) {
                        cout << "\tj = " << j << "\n";
                        cout << "\twindow_2[" << candidate_idx_of_sum << "] = " << window_2[candidate_idx_of_sum];
                        cout << ", zig_zag[" << candidate_idx_of_min << "][0] = " << zig_zag[candidate_idx_of_min][0];
                        cout << "\n\twindow_2[" << max_sum_idx << "] = " << window_2[max_sum_idx];
                        cout << ", zig_zag[" << min_idx_after_max << "][0] = " << zig_zag[min_idx_after_max][0] << "\n\n";

                    }*/

                    if (window_2[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0]
                        < window_2[max_sum_idx] - zig_zag[min_idx_after_max][0]) {

                        candidate_idx_of_sum = max_sum_idx;
                        candidate_idx_of_min = min_idx_after_max;
                        window_1[j] = window_2[max_sum_idx] - zig_zag[min_idx_after_max][0] + zig_zag[i + j][1];

                        /*if (test > 0) {
                            cout << "\twindow_2[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] < window_2[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_1[" << j << "] = " << window_2[max_sum_idx] << " - " << zig_zag[min_idx_after_max][0] << " + " << zig_zag[i + j][1] << "\n";
                        }*/
                    }

                    else {
                        window_1[j] = window_2[candidate_idx_of_sum] - zig_zag[candidate_idx_of_min][0] + zig_zag[i + j][1];

                        /*if (test > 0) {
                            cout << "\twindow_2[" << candidate_idx_of_sum << "] - zig_zag[" << candidate_idx_of_min << "][0] < window_2[" << max_sum_idx << "] - zig_zag[" << min_idx_after_max << "][0]\n";
                            cout << "\twindow_1[" << j << "] = " << window_2[candidate_idx_of_sum] << " - " << zig_zag[candidate_idx_of_min][0] << " + " << zig_zag[i + j][1] << "\n";
                        }*/
                    }

                    //if (test > 0) { cout << "\n"; }
                }

                from_1_to_2 = 1;

                /*if (test > 0) {
                    cout << "window_1\n";
                    for (int i = 0; i < zig_zag_size - k + 1; i++) {
                        cout << window_1[i] << " ";
                    }
                    cout << "\n\n";
                }*/
            }
        }

        if (from_1_to_2 == 1) { //  just exited from (from_1_to_2 == 0), result is the max in window_1
            for (int i = 0; i < zig_zag_size - k + 1; i++) {
                if (window_1[i] > result) { result = window_1[i]; }
            }
        }

        else { //  just exited from (from_1_to_2 == 1), result is the max in window_2
            for (int i = 0; i < zig_zag_size - k + 1; i++) {
                if (window_2[i] > result) { result = window_2[i]; }
            }
        }
    }

    return result;
}






int main(){
    srand(time(0));int k = 4, length = 14, lower_range = -10, upper_range = 10, input = 1;
    vector<int> wtf;
    //
    //  = {10, 1, 6, 3, 13, 5, 13, 12, 21, 20, 23, 16, 18, 15}
    // = {3,2,6,5,0,3}

    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;

for (int m = 1; m <= 1000000; m++) {if (m % 10000 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){// rand()%(upper_range - lower_range + 1) + lower_range
        wtf.reserve(length);
        wtf.push_back(10);
        for(int i = 1, increase = 0, temp; i < length; i++){
            if (increase == 1) {
                temp = wtf.back() + rand()%(upper_range - 1 + 1) + 1;
                wtf.push_back(temp);
                increase = 0;
            }

            else {
                temp = wtf.back() + rand()%(-1 - lower_range + 1) + lower_range;
                wtf.push_back(temp);
                increase = 1;
            }

        }
        //k = rand()%(upper_range - lower_range + 1) + lower_range;
    }

    //cout << " = {"; for (int i = 0; i < wtf.size(); i++) { cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";} } cout << "}\n";

    start_point_1 = chrono::steady_clock::now();
    int s = maxProfit_brute_k_equals_to_four(k, wtf);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;
    //cout << "s = " << s << "\n";

    start_point_2 = chrono::steady_clock::now();
    int ss = maxProfit(k, wtf);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    //cout << "ss = " << ss << "\n";

    if (s != ss) {
        cout << "m = " << m << "\n";
        cout << "brute = " << s << "\n";
        cout << " = " << ss << "\n";
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

    return 0;
}




