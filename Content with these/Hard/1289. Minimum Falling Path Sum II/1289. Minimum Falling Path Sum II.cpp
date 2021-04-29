/*1289. Minimum Falling Path Sum II
Hard

Given a square grid of integers arr,
a falling path with non-zero shifts is a choice of exactly one element from each row of arr,
such that no two elements chosen in adjacent rows are in the same column.

Return the minimum sum of a falling path with non-zero shifts.

Input: arr = [[1,2,3],[4,5,6],[7,8,9]]
Output: 13
Explanation:
The possible falling paths are:
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
The falling path with the smallest sum is [1,5,7],
so the answer is 13.

Constraints:
    1 <= arr.length == arr[i].length <= 200
    -99 <= arr[i][j] <= 99
*/

/*
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& arr) {

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

int minFallingPathSum_brute(vector<vector<int>>& arr) {
    int height = arr.size(), width = arr[0].size(), test_timer = 0;

    int curr_min, second_smallest;
    for (int i = 1; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {curr_min = arr[i - 1][1];}
            else {curr_min = arr[i - 1][0];}

            for (int k = 0; k < width; k++) {
                if (k == j) {continue;}

                else if (curr_min > arr[i - 1][k]) {curr_min = arr[i - 1][k];}
            }

            arr[i][j] += curr_min;
        }
    }

    curr_min = arr[height - 1][0];
    for (int i = 1; i < width; i++) {
        if (arr[height - 1][i] < curr_min) {
            curr_min = arr[height - 1][i];
        }
    }

    return curr_min;
}




//shit, at first, i completely misunderstood one crucial part of this problem
//it's a square grid i see
int minFallingPathSum_1(vector<vector<int>>& arr) {
    int height = arr.size(), width = arr[0].size();
    if (height == 1) {return arr[0][0];}

    //int test_timer = 0;

    /*int sweeping_row_a[width];
    int sweeping_row_b[width];
    for (int i = 0; i < width; i++) {
        sweeping_row_a[i] = arr[0][i];
        sweeping_row_b[i] = arr[0][i];
    }*/

    //int from_a_to_b = 1;
    int smallest, second_smallest, smallest_idx;
    for (int i = 1; i < height; i++) {
        //if (test_timer >= 0) {cout << "\ni = " << i << "\n";}

        if (arr[i - 1][0] <= arr[i - 1][1]) {
            smallest = arr[i - 1][0];
            second_smallest = arr[i - 1][1];
            smallest_idx = 0;
        }
        else {
            smallest = arr[i - 1][1];
            second_smallest = arr[i - 1][0];
            smallest_idx = 1;
        }
        for (int j = 2; j < width; j++) {
            if (arr[i - 1][j] < smallest) {
                second_smallest = smallest;
                smallest = arr[i - 1][j];
                smallest_idx = j;
            }

            else if (arr[i - 1][j] <= second_smallest) {
                second_smallest = arr[i - 1][j];
            }
        }

        /*if (test_timer >= 0) {
            cout << "\nfrom_a_to_b > 0, a:\n";
            for (int j = 0; j < width; j++) {cout << sweeping_row_a[j] << ", ";}
            cout << "\ncurrent line in arr:\n";
            for (int j = 0; j < width; j++) {cout << arr[i][j] << ", ";}
            cout << "\n";
        }*/

        for (int j = 0; j < width; j++) {
            if (j != smallest_idx) {
                arr[i][j] += smallest;
            }

            else {
                arr[i][j] += second_smallest;
            }
        }

        /*if (test_timer >= 0) {
            cout << "\nafter processing b:\n";
            for (int j = 0; j < width; j++) {cout << sweeping_row_b[j] << ", ";}
            cout << "\n";
        }*/

        /*if (from_a_to_b > 0) {
            if (test_timer >= 0) {
                cout << "\nfrom_a_to_b > 0, a:\n";
                for (int j = 0; j < width; j++) {cout << sweeping_row_a[j] << ", ";}
                cout << "\ncurrent line in arr:\n";
                for (int j = 0; j < width; j++) {cout << arr[i][j] << ", ";}
                cout << "\n";
            }

            for (int j = 0; j < width; j++) {
                if (j == smallest_idx) {
                    sweeping_row_b[j] = sweeping_row_a[j] + second_smallest;
                }

                else {
                    sweeping_row_b[j] = sweeping_row_a[j] + smallest;
                }
            }
            from_a_to_b = 0;

            if (test_timer >= 0) {
                cout << "\nafter processing b:\n";
                for (int j = 0; j < width; j++) {cout << sweeping_row_b[j] << ", ";}
                cout << "\n";
            }
        }

        else {
            if (test_timer >= 0) {
                cout << "\nfrom_a_to_b == 0, b:\n";
                for (int j = 0; j < width; j++) {cout << sweeping_row_b[j] << ", ";}
                cout << "\ncurrent line in arr:\n";
                for (int j = 0; j < width; j++) {cout << arr[i][j] << ", ";}
                cout << "\n";
            }

            for (int j = 0; j < width; j++) {
                if (j == smallest_idx) {
                    sweeping_row_a[j] = sweeping_row_b[j] + second_smallest;
                }

                else {
                    sweeping_row_a[j] = sweeping_row_b[j] + smallest;
                }
            }
            from_a_to_b = 1;

            if (test_timer >= 0) {
                cout << "\nafter processing a:\n";
                for (int j = 0; j < width; j++) {cout << sweeping_row_a[j] << ", ";}
                cout << "\n";
            }
        }*/
    }

    int minimum = arr[height - 1][0];
    for (int i = 1; i < width; i++) {
        if (arr[height - 1][i] < minimum) {
            minimum = arr[height - 1][i];
        }
    }


    /*if (from_a_to_b > 0) {
        minimum = sweeping_row_a[0];
        for (int i = 1; i < width; i++) {
            if (sweeping_row_a[i] < minimum) {
                minimum = sweeping_row_a[i];
            }
        }
    }
    else {
        minimum = sweeping_row_b[0];
        for (int i = 1; i < width; i++) {
            if (sweeping_row_b[i] < minimum) {
                minimum = sweeping_row_b[i];
            }
        }
    }
*/
    return minimum;
}


int minFallingPathSum_1_1(vector<vector<int>>& arr) {
    int height = arr.size();
    if (height == 1) {return arr[0][0];}

    int smallest, second_smallest, smallest_idx;
    for (int i = 1; i < height; i++) {
        if (arr[i - 1][0] <= arr[i - 1][1]) {
            smallest = arr[i - 1][0];
            second_smallest = arr[i - 1][1];
            smallest_idx = 0;
        }
        else {
            smallest = arr[i - 1][1];
            second_smallest = arr[i - 1][0];
            smallest_idx = 1;
        }
        for (int j = 2; j < height; j++) {
            if (arr[i - 1][j] < smallest) {
                second_smallest = smallest;
                smallest = arr[i - 1][j];
                smallest_idx = j;
            }

            else if (arr[i - 1][j] <= second_smallest) {
                second_smallest = arr[i - 1][j];
            }
        }

        for (int j = 0; j < height; j++) {
            if (j != smallest_idx) {arr[i][j] += smallest;}

            else {arr[i][j] += second_smallest;}
        }
    }

    int minimum = arr[height - 1][0];
    for (int i = 1; i < height; i++) {
        if (arr[height - 1][i] < minimum) {
            minimum = arr[height - 1][i];
        }
    }

    return minimum;
}





int main(){
    srand(time(0));int height = 20, lower_range = -100, upper_range = 100, display = 0, input = 1;
    vector<vector<int>> wtf;
/* = {
{-73,61,43,-48,-36},
{3,30,27,57,10},
{96,-76,84,59,-15},
{5,-49,76,31,-7},
{97,91,61,-46,67}
};*/

    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;


for (int m = 1; m <= 1000000; m++) {if (m % 10000 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){
        //wtf.reserve(length);
        for (int i = 0; i < height; i++) {
            wtf.push_back(vector<int>{});
            for (int j = 0; j < height; j++) {
                wtf[i].push_back(rand()%(upper_range - lower_range + 1) + lower_range);
            }
        }
    }
    if (display == 1){
        cout << " = {\n";
        for (int i = 0; i < height; i++) {
            cout << "{";
            for (int j = 0; j < height; j++) {
                cout << wtf[i][j] << ", ";
            }
            cout << "},\n";
        }
        cout << "}\n";
    }

    //cout << "\n:\n";

    vector<vector<int>> wtf1(wtf);vector<vector<int>> wtf2(wtf);vector<vector<int>> wtf3(wtf);

    start_point_1 = chrono::steady_clock::now();
    int s = minFallingPathSum_brute(wtf1);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    //cout << "\n\nbrute = " << shit << "\n\n";

    start_point_2 = chrono::steady_clock::now();
    int ss = minFallingPathSum_1(wtf2);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    start_point_3 = chrono::steady_clock::now();
    int sss = minFallingPathSum_1_1(wtf3);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;

    //cout << "\n\nbrute = " << shit << "\n\n";
    //cout << "\n\nshit = " << shitshit << "\n\n";

    if (s != sss) {
        cout << " = {\n";
        for (int i = 0; i < height; i++) {
            cout << "{";
            for (int j = 0; j < height; j++) {
                cout << wtf[i][j] << ", ";
            }
            cout << "},\n";
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




