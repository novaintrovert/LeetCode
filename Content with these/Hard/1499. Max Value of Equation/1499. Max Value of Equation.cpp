/*1499. Max Value of Equation
Hard

Given an array points containing the coordinates of points on a 2D plane,
sorted by the x-values,
where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length.
You are also given an integer k.

Find the maximum value of the equation yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length.
It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.

Input: points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
Output: 4
Explanation: The first two points satisfy the condition |xi - xj| <= 1 and if we calculate the equation we get 3 + 0 + |1 - 2| = 4. Third and fourth points also satisfy the condition and give a value of 10 + -10 + |5 - 6| = 1.
No other pairs satisfy the condition, so we return the max of 4 and 1.

Input: points = [[0,0],[3,0],[9,2]], k = 3
Output: 3
Explanation: Only the first two points have an absolute difference of 3 or less in the x-values, and give the value of 0 + 0 + |0 - 3| = 3.

Constraints:
    2 <= points.length <= 10^5
    points[i].length == 2
    -10^8 <= points[i][0], points[i][1] <= 10^8
    0 <= k <= 2 * 10^8
    points[i][0] < points[j][0] for all 1 <= i < j <= points.length
    xi form a strictly increasing sequence.
*/

/*
class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {

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

using namespace std;
using namespace chrono;

int findMaxValueOfEquation_brute(vector<vector<int>>& points, int k) {
    int length = points.size();
    int sum[length], dif[length];
    for (int i = 0; i < length; i++) {
        sum[i] = points[i][0] + points[i][1];
        dif[i] = points[i][1] - points[i][0];
    }

    int result = -2147483648, curr_max_val;

    for (int i = length - 1; i > 0; i--) {
        if (points[i][0] - points[i - 1][0] <= k) {//(curr_max_idx >= 0)&&(curr_max_idx < i)
            curr_max_val = sum[i] + dif[i - 1];
            for (int j = i - 1; (j >= 0)&&(points[i][0] - points[j][0] <= k); j--) {
                if (sum[i] + dif[j] > curr_max_val) {curr_max_val = sum[i] + dif[j];}
            }
            result = (curr_max_val > result)? curr_max_val: result;
        }
    }

    return result;
}




//CURRENT BEST
//it seems that this short code beat almost all submissions in leetcode
//almost equal performance compared to brute IN RANDOM INPUT! this is embarrassing...
int findMaxValueOfEquation_1(vector<vector<int>>& points, int k) {
    int length = points.size();int test_timer = -1;
    int sum[length], dif[length];
    for (int i = 0; i < length; i++) {
        sum[i] = points[i][0] + points[i][1];
        dif[i] = points[i][1] - points[i][0];
    }

    if (test_timer >= 0) {
        cout << "\nsum: ";
        for (int i = 0; i < length; i++) {cout << sum[i] << ", ";}
        cout << "\ndif: ";
        for (int i = 0; i < length; i++) {cout << dif[i] << ", ";}
    }

    int result = -2147483648, temp;
    int already_scanned_to = length - 1, curr_max_idx = -1, curr_max_val = dif[already_scanned_to];

    for (int i = length - 1; i > 0; i--) {
        if ((i <= curr_max_idx)||(curr_max_idx < 0)) {
            if (points[i][0] - points[i - 1][0] > k) {curr_max_idx = -1;}

            else {
                curr_max_idx = i - 1, curr_max_val = dif[curr_max_idx];
                for (int j = i - 1; (j >= 0)&&(points[i][0] - points[j][0] <= k); j--) {
                    if (dif[j] >= curr_max_val) {curr_max_val = dif[j];curr_max_idx = j;}
                    already_scanned_to = j;
                }
            }
        }

        else if ((already_scanned_to > 0)&&(points[i][0] - points[already_scanned_to - 1][0] <= k)) {//(curr_max_idx >= 0)&&(curr_max_idx < i)
            for (int j = already_scanned_to - 1; (j >= 0)&&(points[i][0] - points[j][0] <= k); j--) {
                if (dif[j] >= curr_max_val) {curr_max_val = dif[j];curr_max_idx = j;}
                already_scanned_to = j;
            }
        }

        if (curr_max_idx < 0) {continue;}

        temp = sum[i] + curr_max_val;
        if (temp > result) {result = temp;}
    }

    return result;
}






//almost equal performance compared to brute! this is embarrassing...
int findMaxValueOfEquation_1_1(vector<vector<int>>& points, int k) {
    int length = points.size();int test_timer = -1;
    int sum[length], dif[length];
    for (int i = 0; i < length; i++) {
        sum[i] = points[i][0] + points[i][1];
        dif[i] = points[i][1] - points[i][0];
    }

    if (test_timer >= 0) {
        cout << "\nsum: ";
        for (int i = 0; i < length; i++) {cout << sum[i] << ", ";}
        cout << "\ndif: ";
        for (int i = 0; i < length; i++) {cout << dif[i] << ", ";}
    }

    int result = -2147483648, temp;
    multiset<int> cache;
    multiset<int>::iterator find_value;
    int already_scanned_to = length - 1;

    for (int i = length - 1; i > 0; i--) {
        if (i <= already_scanned_to) {
            already_scanned_to = i;
            while ((already_scanned_to > 0)&&(points[i][0] - points[already_scanned_to - 1][0] <= k)) {
                cache.insert(dif[already_scanned_to - 1]);
                already_scanned_to--;
            }
        }

        if (i > already_scanned_to) {
            while ((already_scanned_to > 0)&&(points[i][0] - points[already_scanned_to - 1][0] <= k)) {
                cache.insert(dif[already_scanned_to - 1]);
                already_scanned_to--;
            }

            find_value = prev(cache.end());

            temp = sum[i] + *find_value;
            if (temp > result) {result = temp;}

            find_value = cache.find(dif[i - 1]);
            cache.erase(find_value);
        }
    }

    return result;
}

/*yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length.
It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.

? = xj - xi + yi + yj
? = yj + xj + yi - xi

*/

//old UNFINISHED draft. probably won't work.
int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
    const int number_of_points = points.size();
    int max_val, found_1st_one = 0;
    queue<int> candidate_start_point;
    queue<int> candidate_end_point;
    for (int i = 0, j = 1; ; j++) {
        if (points[j][0] - points[i][0] > k) {
            if (candidate_start_point.size() == 0) {
                i = j;
                continue;
            }
            else {
                while ((candidate_start_point.size() == 0)&&(points[j][0] - points[i][0] >= k)) {
                    i = candidate_start_point.front();
                    candidate_start_point.pop();
                    if (candidate_end_point.size() == 0) {
                        continue;
                    }
                    else {
                        while (candidate_end_point.front() <= i) {
                            candidate_end_point.pop();
                        }
                        if (candidate_end_point.size() == 0) {
                            continue;
                        }
                        else {
                            int back_idx = candidate_end_point.back();
                            while (true) {
                                int temp_idx = candidate_end_point.front();
                                if (points[i][1] + points[temp_idx][1] + points[temp_idx][0] - points[i][0] > max_val) {
                                    max_val = points[i][1] + points[temp_idx][1] + points[temp_idx][0] - points[i][0];
                                }
                                candidate_end_point.pop();
                                candidate_end_point.push(temp_idx);
                                if (temp_idx == back_idx) {
                                    break;
                                }
                            }
                        }
                        if (points[j][0] - points[i][0] < k) {break;}
                    }
                }
                if (points[j][0] - points[i][0] < k) {
                    //go on
                }
                if (points[j][0] - points[i][0] >= k) {
                    i = j;
                    continue;
                }
            }
        }
        if ((found_1st_one == 0)&&(j != i)) {
            max_val = points[i][1] + points[j][1] + points[j][0] - points[i][0];
        }
        if (found_1st_one == 1) {
            if (points[j][1] - points[i][1] > points[j][0] - points[i][0]) {
                candidate_start_point.push(j);
            }
            if (points[i][1] + points[j][1] + points[j][0] - points[i][0] > max_val) {
                candidate_end_point.push(j);
                max_val = points[i][1] + points[j][1] + points[j][0] - points[i][0];
            }

        }
    }
    return max_val;
}


int main(){
    srand(time(0));int k = 9, length = 100000, lower_range = -100000000, upper_range = 100000000, display = 0, input = 1;
    vector<vector<int>> wtf;
// = {{-4, 7}, {-1, -1}, {3, -7}, {4, 8}, {14, 4}}k = 8
// = {{0,0},{3,0},{9,2}};k = 3
// = {{1,3},{2,0},{5,10},{6,-10}};k = 1

    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;

for (int m = 1; m <= 1000; m++) {if (m % 100 == 0) {cout << "m = " << m << "\n";}
    if (input == 1){
        wtf.push_back({rand()%(upper_range - lower_range + 1) + lower_range, rand()%(upper_range - lower_range + 1) + lower_range});
        for(int i = 1; i < length; i++){
            wtf.push_back({wtf[i - 1][0] + rand()%(upper_range - 1 + 1) + 1, rand()%(upper_range - lower_range + 1) + lower_range});
        }
        k = rand()%(100000000 - 0 + 1) + 0;
    }
    if (display == 1){
        cout << "k = " << k << "\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{" << wtf[i][0] << ", " << wtf[i][1];
            if (i < wtf.size() - 1) {cout << "}, ";}
            else {cout << "}";}
        }
        cout << "}\n";
    }

    //cout << "\nmaxNumber:\n";
    start_point_1 = chrono::steady_clock::now();
    int a = findMaxValueOfEquation_brute(wtf, k);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    if (display != 0) {cout << "brute = " << a << "\n";}

    start_point_2 = chrono::steady_clock::now();
    int aa = findMaxValueOfEquation_1(wtf, k);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    if (display != 0) {cout << "aa = " << aa << "\n";}

    start_point_3 = chrono::steady_clock::now();
    int aaa = findMaxValueOfEquation_1_1(wtf, k);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;

    if (display != 0) {cout << "aaa = " << aaa << "\n";}

    if (a != aaa) {
        cout << "k = " << k << "\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{" << wtf[i][0] << ", " << wtf[i][1] << "}, ";
        }
        cout << "}\n";
        break;
    }

wtf.clear();
}

cout << "brute: " << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << "     : " << duration <double, milli> (diff_2).count() << " ms" << "\n";
cout << " _1_1: " << duration <double, milli> (diff_3).count() << " ms" << "\n";
    return 0;
}




