/*1074. Number of Submatrices That Sum to Target
Hard

Given a matrix and a target,
return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different,
if they have some coordinate that is different: for example, if x1 != x1'.

Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.

Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.

Input: matrix = [[904]], target = 0
Output: 0

Constraints:
    1 <= matrix.length <= 100
    1 <= matrix[0].length <= 100
    -1000 <= matrix[i] <= 1000
    -10^8 <= target <= 10^8
*/

/*
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {

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



int numSubmatrixSumTarget_brute (vector<vector<int>>& matrix, int target) {
    int matrix_height = matrix.size(), matrix_width = matrix[0].size();
    int counter = 0, sum;
    for (int top0 = 0; top0 < matrix_height; top0++) {
        for (int top1 = 0; top1 < matrix_width; top1++) {
            for (int i = top0; i < matrix_height; i++) {
                for (int j = top1; j < matrix_width; j++) {
                    sum = 0;
                    for (int m = top0; m <= i; m++) {
                        for (int n = top1; n <= j; n++) {
                            sum += matrix[m][n];
                        }
                    }

                    if (sum == target) {counter++;}
                }
            }
        }
    }
    return counter;
}



//1st passed
//decent, but got room for improvement, let me try to work something out
int numSubmatrixSumTarget_1(vector<vector<int>>& matrix, int target) {
    int matrix_height = matrix.size(), matrix_width = matrix[0].size();
    int height, width = 1, counter = 0, i, j;

    int cache[matrix_height][matrix_width];//store current progress
    int operate_this[matrix_height][matrix_width];
    for (i = 0; i < matrix_height; i++) {
        for (j = 0; j < matrix_width; j++) {
            cache[i][j] = 0, operate_this[i][j] = 0;
        }
    }

    for (width = 1; width <= matrix_width; width++) {
        for (i = 0; i < matrix_height; i++) {
            for (j = 0; j <= matrix_width - width; j++) {
                cache[i][j] += matrix[i][j + width - 1];
                operate_this[i][j] = cache[i][j];

                if (operate_this[i][j] == target) {counter++;}
            }
        }

        for (height = 2; height <= matrix_height; height++) {
            for (i = 0; i <= matrix_height - height; i++) {
                for (j = 0; j <= matrix_width - width; j++) {
                    operate_this[i][j] += cache[i + height - 1][j];

                    if (operate_this[i][j] == target) {counter++;}
                }
            }
        }
    }

    return counter;
}



//inspired by the preprocessing of other people's code
//still need some work
int numSubmatrixSumTarget_2(vector<vector<int>>& matrix, int target) {//version 2.0
    int matrix_height = matrix.size(), matrix_width = matrix[0].size();
    int height, width, temp, counter = 0;

    int cache[matrix_height][matrix_width + 1];
    for (int i = 0; i < matrix_height; i++) {
        cache[i][0] = 0;
        for (int j = 0; j < matrix_width; j++) {
            cache[i][j + 1] = cache[i][j] + matrix[i][j];
        }
    }

    int curr_column[matrix_height + 1];

    for (width = 1; width <= matrix_width; width++) {
        for (int column_idx = 0; column_idx <= matrix_width - width; column_idx++) {
            curr_column[0] = 0;
            for (int i = 0; i < matrix_height; i++) {
                curr_column[i + 1] = cache[i][column_idx + width] - cache[i][column_idx];

                if (curr_column[i + 1] == target) {counter++;}
            }

            for (int i = 0; i < matrix_height; i++) {
                curr_column[i + 1] += curr_column[i];
            }

            for (int i = 0; i < matrix_height; i++) {
                for (int j = i + 1; j <= matrix_height; j++) {
                    temp = curr_column[j] - curr_column[i];

                    if (temp == target) {counter++;}
                }
            }
        }
    }

    return counter;
}



//inspired by the preprocessing of other people's code
//still need some work
//better, but still need some work
//too slow & sometimes problems occur
int numSubmatrixSumTarget_2_2(vector<vector<int>>& matrix, int target) {
    int matrix_height = matrix.size(), matrix_width = matrix[0].size();
    int counter = 0;

    int cache[matrix_height + 1][matrix_width + 1];
    for (int i = 0; i <= matrix_height; i++) {cache[0][i] = 0;}
    for (int i = 0; i < matrix_height; i++) {
        cache[i + 1][0] = 0;
        for (int j = 0; j < matrix_width; j++) {
            cache[i + 1][j + 1] = cache[i + 1][j] + cache[i][j + 1] + matrix[i][j];
        }
    }

    int curr_column[matrix_height + 1];

    /*for (int width = 1; width <= matrix_width; width++) {
        for (int column_idx = 0; column_idx <= matrix_width - width; column_idx++) {
            curr_column[0] = 0;
            for (int i = 0; i < matrix_height; i++) {
                curr_column[i + 1] = cache[i][column_idx + width] - cache[i][column_idx];

                if (curr_column[i + 1] == target) {counter++;}

                curr_column[i + 1] += curr_column[i];
            }

            for (int i = 0; i < matrix_height; i++) {
                for (int j = i + 1; j <= matrix_height; j++) {
                    if (curr_column[j] - curr_column[i] == target) {counter++;}
                }
            }
        }
    }*/


    for (int i = 0; i < matrix_height; i++) {
        for (int j = 0; j < matrix_width; j++) {
            for (int k = i; k < matrix_height; k++) {
                for (int l = j; l < matrix_width; l++) {
                    if (cache[k + 1][l + 1] - cache[k + 1][j] + cache[i][j] - cache[i][l + 1] == target) {counter++;}
                }
            }
        }
    }

    return counter;
}



//2nd passed
//inspired by the preprocessing of other people's code
//still need some work
//better, but still need some work
int numSubmatrixSumTarget_2_1(vector<vector<int>>& matrix, int target) {//version 2.1
    int matrix_height = matrix.size(), matrix_width = matrix[0].size();
    int counter = 0;

    int cache[matrix_height][matrix_width + 1];
    for (int i = 0; i < matrix_height; i++) {
        cache[i][0] = 0;
        for (int j = 0; j < matrix_width; j++) {
            cache[i][j + 1] = cache[i][j] + matrix[i][j];
        }
    }

    int curr_column[matrix_height + 1];

    for (int width = 1; width <= matrix_width; width++) {
        for (int column_idx = 0; column_idx <= matrix_width - width; column_idx++) {
            curr_column[0] = 0;
            for (int i = 0; i < matrix_height; i++) {
                curr_column[i + 1] = cache[i][column_idx + width] - cache[i][column_idx];
                //if (curr_column[i + 1] == target) {counter++;}
                curr_column[i + 1] += curr_column[i];
            }

            for (int i = 0; i < matrix_height; i++) {
                for (int j = i + 1; j <= matrix_height; j++) {
                    if (curr_column[j] - curr_column[i] == target) {counter++;}
                }
            }
        }
    }

    return counter;
}



//inspired by the preprocessing of other people's code
//still need some work
//better, but still need some work
int numSubmatrixSumTarget_2_1_1(vector<vector<int>>& matrix, int target) {
    int matrix_height = matrix.size(), matrix_width = matrix[0].size(), counter = 0;

    int cache[matrix_height][matrix_width + 1];
    for (int i = 0; i < matrix_height; i++) {
        cache[i][0] = 0;
        for (int j = 0; j < matrix_width; j++) {
            cache[i][j + 1] = cache[i][j] + matrix[i][j];
        }
    }

    int curr_column[matrix_height + 1];

    for (int width = 1; width <= matrix_width; width++) {
        for (int column_idx = 0; column_idx <= matrix_width - width; column_idx++) {
            curr_column[0] = 0;
            for (int i = 1; i <= matrix_height; i++) {
                curr_column[i] = cache[i - 1][column_idx + width] - cache[i - 1][column_idx];
                //if (curr_column[i] == target) {counter++;}
                curr_column[i] += curr_column[i - 1];
            }

            for (int i = 0; i < matrix_height; i++) {
                for (int j = i + 1; j <= matrix_height; j++) {
                    if (curr_column[j] - curr_column[i] == target) {counter++;}
                }
            }
        }
    }

    return counter;
}

//literally swapped row & column, nothing new
int numSubmatrixSumTarget_2_1_1_swappped_row_n_column(vector<vector<int>>& matrix, int target) {
    int matrix_height = matrix.size(), matrix_width = matrix[0].size(), counter = 0;
    int cache[matrix_height + 1][matrix_width];
    for (int i = 0; i < matrix_width; i++) {
        cache[0][i] = 0;
        for (int j = 0; j < matrix_height; j++) {
            cache[j + 1][i] = cache[j][i] + matrix[j][i];
        }
    }
    int curr_row[matrix_width + 1];

    for (int height = 1; height <= matrix_height; height++) {
        for (int row_idx = 0; row_idx <= matrix_height - height; row_idx++) {
            curr_row[0] = 0;
            for (int i = 1; i <= matrix_width; i++) {
                curr_row[i] = cache[row_idx + height][i - 1] - cache[row_idx][i - 1];
                //if (curr_column[i] == target) {counter++;}
                curr_row[i] += curr_row[i - 1];
            }

            for (int i = 0; i < matrix_width; i++) {
                for (int j = i + 1; j <= matrix_width; j++) {
                    if (curr_row[j] - curr_row[i] == target) {counter++;}
                }
            }
        }
    }

    return counter;
}


int numSubmatrixSumTarget_2_1_1_swappped_row_n_column_see_performance_diff(vector<vector<int>>& matrix, int target) {
    int matrix_height = matrix.size(), matrix_width = matrix[0].size(), counter = 0;
    int cache[matrix_height + 1][matrix_width];
    for (int i = 0; i < matrix_width; i++) {
        cache[0][i] = 0;
        for (int j = 0; j < matrix_height; j++) {
            cache[j + 1][i] = matrix[j][i] + cache[j][i];
        }
    }
    int curr_row[matrix_width + 1];

    for (int height = 1; height <= matrix_height; height++) {
        for (int row_idx = 0; row_idx < height; row_idx++) {
            curr_row[0] = 0;
            for (int i = 1, j = i - 1; i <= matrix_width; i++, j++) {
                curr_row[i] = cache[height][j] - cache[row_idx][j];
                //if (curr_column[i] == target) {counter++;}
                curr_row[i] += curr_row[j];
            }

            /*for (int i = 0; i < matrix_width; i++) {
                for (int j = i + 1; j <= matrix_width; j++) {
                    if (curr_row[j] - curr_row[i] == target) {counter++;}
                }
            }*/

            for (int i = 1; i <= matrix_width; i++) {
                for (int j = 0; j < i; j++) {
                    if (curr_row[i] - curr_row[j] == target) {counter++;}
                }
            }
        }
    }

    return counter;
}

/*just found the reason of performance gap between this code & my code - edit, NO! PERFORMANCE IS NOT CAUSED BY THIS!!!

in my code:
height means, currently, we are searching rectangles with "height" as it's "edge's length"

in that code:
height means, currently, we are searching all rectangles with "bottom edge as height_idx = height"

*/

//i still don't understand why my code is ALWAYS SLOWER despite of being practically identical!!!
//perhaps that tiny bit performance difference DOES NOT worth my time
//besides, it is NOT FUN doing this searching gold in sand dune sort of things


//this code built by some other people, is neat!
int numSubmatrixSumTarget_other_people_1 (vector<vector<int>>& arr, int x) {
    int matrix_height = arr.size(), matrix_width = arr[0].size(), counter = 0;
    int cache[matrix_height + 1][matrix_width + 1];
    for (int j = 0; j <= matrix_width; j++) {
        for (int i = 0;i <= matrix_height; i++) {
            if ((i == 0)||(j == 0)) {cache[i][j] = 0;}
            else {
                cache[i][j] = arr[i - 1][j - 1] + cache[i - 1][j];
            }
        }
    }
    int curr_row[matrix_width + 1];
    for (int height = 1; height <= matrix_height; height++) {//for EVERY possible height
        for (int row_idx = 0; row_idx < height; row_idx++) {//with height fixed, for every possible row that is SMALLER THAN height
            for (int k = 0; k <= matrix_width; k++) {//calculate curr_row[]
                curr_row[k] = cache[height][k] - cache[row_idx][k];//notice that it is HEIGHT & NOT matrix_height!!!

                if (k != 0) {curr_row[k] += curr_row[k - 1];}
            }

            for (int k = 1; k <= matrix_width; k++) {
                for (int l = 0; l < k; l++) {
                    if (curr_row[k] - curr_row[l] == x) {counter++;}
                }
            }
        }
    }
    return counter;
}

int numSubmatrixSumTarget_other_people (vector<vector<int>>& arr, int x) {
    int n=arr.size();
    int m=arr[0].size();
    int dp1[n+1][m+1];
    for(int j=0;j<=m;j++){
        for(int i=0;i<=n;i++){
            if(i==0 || j==0)dp1[i][j]=0;
            else{
                dp1[i][j]=arr[i-1][j-1]+dp1[i-1][j];
            }
        }
    }
    int ans=0;
    int dp2[m+1];
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            for(int k=0;k<=m;k++){
                dp2[k]=dp1[i][k]-dp1[j][k];
                if(k!=0)dp2[k]+=dp2[k-1];
            }
            for(int k=1;k<=m;k++){
                for(int l=0;l<k;l++){
                    if(dp2[k]-dp2[l]==x)ans++;
                }
            }
        }
    }
    return ans;
}





int main(){
    srand(time(0));int k = 16, height = 100, width = 1;
    int target_lower_range = -10, target_upper_range = 10;
    int lower_range = -10, upper_range = 10, display = 0, input = 1;
    vector<vector<int>> wtf;

    auto start_point_0 = chrono::steady_clock::now();auto end_point_0 = chrono::steady_clock::now();auto diff_0 = end_point_0 - start_point_0;
    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;
    auto start_point_4 = chrono::steady_clock::now();auto end_point_4 = chrono::steady_clock::now();auto diff_4 = end_point_4 - start_point_4;


for (int m = 1; m <= 100; m++) {if (m % 100 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){
        for (int i = 0; i < height; i++) {
            wtf.push_back(vector<int> {});
            for (int j = 0; j < width; j++) {
                wtf[i].push_back(rand()%(upper_range - lower_range + 1) + lower_range);
            }
        }
        k = rand()%(target_upper_range - target_lower_range + 1) + target_lower_range;
    }
    if (display == 1){
        cout << "target = " << k << "\n = {\n";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{";
            for (int j = 0; j < wtf[0].size(); j++) {
                cout << wtf[i][j];
                if (j < wtf[i].size() - 1) {cout << ", ";}
            }
            if (i < wtf.size() - 1) {cout << "},\n";}
            else {cout << "}\n";}
        }
        cout << "}\n";
    }

    start_point_0 = chrono::steady_clock::now();
    int s = numSubmatrixSumTarget_other_people(wtf, k);
    end_point_0 = chrono::steady_clock::now();
    diff_0 += end_point_0 - start_point_0;

    //cout << "s = " << s << "\n";

    start_point_1 = chrono::steady_clock::now();
    int ss = numSubmatrixSumTarget_2_1(wtf, k);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    start_point_2 = chrono::steady_clock::now();
    int sss = numSubmatrixSumTarget_brute(wtf, k);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    /*start_point_3 = chrono::steady_clock::now();
    int ssss = numSubmatrixSumTarget_other_people_1(wtf, k);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;


    start_point_4 = chrono::steady_clock::now();
    int sssss = numSubmatrixSumTarget_2_1_1_swappped_row_n_column_see_performance_diff(wtf, k);
    end_point_4 = chrono::steady_clock::now();
    diff_4 += end_point_4 - start_point_4;*/

    //cout << "ss = " << ss << "\n";

    if ((s != ss)||(sss != ss)) {
        cout << "\n\n\n\nsomething is wrong\n\n\nm = " << m << "\n\ntarget = " << k << "\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{";
            for (int j = 0; j < wtf[0].size(); j++) {
                cout << wtf[i][j];
                if (j < wtf[i].size() - 1) {cout << ", ";}
            }
            if (i < wtf.size() - 1) {cout << "},\n";}
            else {cout << "}";}
        }
        cout << "}\n";
        cout << "s = " << s << "\n";
        cout << "ss = " << ss << "\n";
        cout << "sss = " << sss << "\n";
        //cout << "ssss = " << ssss << "\n";
        //cout << "sssss = " << sssss << "\n";

        break;
    }

wtf.clear();}
cout << "\nothers:" << duration <double, milli> (diff_0).count() << " ms" << "\n";
cout << "_2_1  :" <<duration <double, milli> (diff_1).count() << " ms" << "\n";
//cout << "_2_1_1:" <<duration <double, milli> (diff_2).count() << " ms" << "\n";
//cout << "others_1:" <<duration <double, milli> (diff_3).count() << " ms" << "\n";
//cout << "     :" <<duration <double, milli> (diff_4).count() << " ms" << "\n";
    return 0;
}









    /* = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,-1,-1,-1,-1,-1,-1,0,0},
    {0,0,-1,1,1,1,1,-1,0,0},
    {0,0,-1,1,1,1,1,-1,0,0},
    {0,0,-1,1,1,1,1,-1,0,0},
    {0,0,-1,1,1,1,1,-1,0,0},
    {0,0,-1,-1,-1,-1,-1,-1,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    };*/
