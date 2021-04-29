/*765. Couples Holding Hands
Hard

N couples sit in 2N seats arranged in a row and want to hold hands.
We want to know the minimum number of swaps so that every couple is sitting side by side.
A swap consists of choosing any two people,
then they stand up and switch seats.

The people and seats are represented by an integer from 0 to 2N-1,
the couples are numbered in order,
the first couple being (0, 1),
the second couple being (2, 3),
and so on with the last couple being (2N-2, 2N-1).

The couples' initial seating is given by row[i] being the value of the person who is initially sitting in the i-th seat.

Input: row = [0, 2, 1, 3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.

Input: row = [3, 2, 0, 1]
Output: 0
Explanation: All couples are already seated side by side.

Note:
    len(row) is even and in the range of [4, 60].
    row is guaranteed to be a permutation of 0...len(row)-1.
*/

/*
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {

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
#include<bitset>

using namespace std;
using namespace chrono;

int minSwapsCouples_brute(vector<int>& row) {
    int length = row.size(), half_length = length / 2;
    bool even_or_odd; int test = 0, temp;

    int same_array[length];
    for (int i = 0; i < length; i++) {
        even_or_odd = row[i] & 1;

        same_array[i] = (even_or_odd == 0)? row[i] / 2: (row[i] - 1) / 2;
    }

    int counter = 0;

    if (test > 0) {
        cout << "\nsame_array: ";
        for (int j = 0; j < length; j++) {
            cout << same_array[j] << " ";
        }
        cout << "\n\n";
    }

    for (int i = 0; i < length - 2; i += 2) {
        if (same_array[i] != same_array[i + 1]) {
            for (int j = i + 2; j < length; j++) {
                if (same_array[j] == same_array[i]) {
                    same_array[j] = same_array[i + 1];
                    same_array[i + 1] = same_array[i];
                    break;
                }
            }
            counter++;

            if (test > 0) {
                for (int j = 0; j < length; j++) {
                    cout << same_array[j] << " ";
                }
                cout << "\n";
            }
        }
    }

    return counter;
}

int minSwapsCouples_1(vector<int>& row) {
    int length = row.size(), half_length = length / 2;
    bool even_or_odd; int test = 0;

    int same_array[length];
    for (int i = 0; i < length; i++) {
        even_or_odd = row[i] & 1;

        same_array[i] = (even_or_odd == 0)? row[i] / 2: (row[i] - 1) / 2;
    }

    int seat[half_length];
    for (int i = 0; i < half_length; i++) { seat[i] = -1; }

    int counter = 0;

    if (test > 0) {
        cout << "\nsame_array: ";
        for (int j = 0; j < length; j++) {
            cout << same_array[j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < length; i += 2) {
        if (test > 0) { cout << "i = " << i << "\n"; }

        if (same_array[i] != same_array[i + 1]) {
            if (seat[same_array[i]] == -1) {
                if (test > 0) { cout << "seat[same_array[i]] == -1\n"; }

                if (seat[same_array[i + 1]] == -1) {
                    if (test > 0) { cout << "seat[same_array[i + 1]] == -1\n"; }

                    seat[same_array[i]] = i + 1;
                    seat[same_array[i + 1]] = i;
                }

                else {
                    if (test > 0) { cout << "seat[same_array[i + 1]] != -1\n"; }

                    seat[same_array[i]] = seat[same_array[i + 1]];
                    seat[same_array[seat[same_array[i + 1]]]] = i;
                    counter++;

                    if (test > 0) { cout << "counter++\n"; }
                }
            }

            else {
                if (test > 0) { cout << "seat[same_array[i]] != -1\n"; }

                if (seat[same_array[i + 1]] == -1) {
                    if (test > 0) { cout << "seat[same_array[i + 1]] == -1\n"; }

                    seat[same_array[i + 1]] = seat[same_array[i]];
                    seat[same_array[seat[same_array[i]]]] = i + 1;
                    counter++;

                    if (test > 0) { cout << "counter++\n"; }
                }

                else {
                    if (test > 0) { cout << "seat[same_array[i + 1]] != -1\n"; }

                    if (same_array[seat[same_array[i]]] != same_array[i + 1]) {
                        seat[same_array[seat[same_array[i]]]] = seat[same_array[i + 1]];
                        seat[same_array[seat[same_array[i + 1]]]] = seat[same_array[i]];
                        counter += 2;

                        if (test > 0) { cout << "counter += 2\n"; }
                    }

                    else {
                        seat[same_array[seat[same_array[i]]]] = i + 1;
                        counter++;

                        if (test > 0) { cout << "counter++\n"; }
                    }
                }
            }
        }

        if (test > 0) {
            for (int j = 0; j < half_length; j++) {
                cout << seat[j] << " ";
            }
            cout << "\n\n";
        }
    }

    return counter;
}

int minSwapsCouples_1_no_test(vector<int>& row) {
    int length = row.size(), half_length = length / 2;
    bool even_or_odd;

    int same_array[length];
    for (int i = 0; i < length; i++) {
        even_or_odd = row[i] & 1;
        same_array[i] = (even_or_odd == 0)? row[i] / 2: (row[i] - 1) / 2;
    }

    int seat[half_length]; for (int i = 0; i < half_length; i++) { seat[i] = -1; }

    int counter = 0;
    for (int i = 0; i < length; i += 2) {
        if (same_array[i] != same_array[i + 1]) {
            if (seat[same_array[i]] == -1) {
                if (seat[same_array[i + 1]] == -1) {
                    seat[same_array[i]] = i + 1;
                    seat[same_array[i + 1]] = i;
                }

                else {
                    seat[same_array[i]] = seat[same_array[i + 1]];
                    seat[same_array[seat[same_array[i + 1]]]] = i;
                    counter++;
                }
            }

            else {
                if (seat[same_array[i + 1]] == -1) {
                    seat[same_array[i + 1]] = seat[same_array[i]];
                    seat[same_array[seat[same_array[i]]]] = i + 1;
                    counter++;
                }

                else {
                    if (same_array[seat[same_array[i]]] != same_array[i + 1]) {
                        seat[same_array[seat[same_array[i]]]] = seat[same_array[i + 1]];
                        seat[same_array[seat[same_array[i + 1]]]] = seat[same_array[i]];
                        counter += 2;
                    }

                    else {
                        seat[same_array[seat[same_array[i]]]] = i + 1;
                        counter++;
                    }
                }
            }
        }
    }

    return counter;
}


int minSwapsCouples_2(vector<int>& row) {
    int length = row.size(), half_length = length / 2;
    bool even_or_odd; int test = 0;

    int same_array[length];
    for (int i = 0; i < length; i++) {
        even_or_odd = row[i] & 1;

        same_array[i] = (even_or_odd == 0)? row[i] / 2: (row[i] - 1) / 2;
    }

    int first_appearance[half_length]; for (int i = 0; i < half_length; i++) { first_appearance[i] = -1; }
    for (int i = length - 1; i >= 0; i--) {
        if (first_appearance[same_array[i]] < 0) {
            first_appearance[same_array[i]] = i;
        }
    }

    int counter = 0, temp;

    if (test > 0) {
        cout << "\nsame_array: ";
        for (int j = 0; j < length; j++) {
            cout << same_array[j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < length; i += 2) {
        if (test > 0) { cout << "i = " << i << "\n"; }

        if (same_array[i] != same_array[i + 1]) {
            if (first_appearance[same_array[i + 1]] < first_appearance[same_array[i]]) {
                first_appearance[same_array[i + 1]] = first_appearance[same_array[i]];
            }

            same_array[first_appearance[same_array[i]]] = same_array[i + 1];
            same_array[i + 1] = same_array[i];

            counter++;

            if (test > 0) {
                for (int j = 0; j < length; j++) {
                    cout << same_array[j] << " ";
                }
                cout << "\n";
            }
        }
    }

    return counter;
}


int minSwapsCouples_2_no_test(vector<int>& row) {
    int length = row.size(), half_length = length / 2;
    bool even_or_odd;

    int same_array[length];//
    for (int i = 0; i < length; i++) {
        even_or_odd = row[i] & 1;
        same_array[i] = (even_or_odd == 0)? row[i] / 2: (row[i] - 1) / 2;
    }

    int first_appearance[half_length]; for (int i = 0; i < half_length; i++) { first_appearance[i] = -1; }
    for (int i = length - 1; i >= 0; i--) {
        if (first_appearance[same_array[i]] < 0) {
            first_appearance[same_array[i]] = i;
        }
    }

    int counter = 0, temp;
    for (int i = 0; i < length; i += 2) {
        if (same_array[i] != same_array[i + 1]) {
            if (first_appearance[same_array[i + 1]] < first_appearance[same_array[i]]) {
                first_appearance[same_array[i + 1]] = first_appearance[same_array[i]];
            }

            same_array[first_appearance[same_array[i]]] = same_array[i + 1];
            same_array[i + 1] = same_array[i];

            counter++;
        }
    }

    return counter;
}

// 1 3 3 2 0 0 2 1
// 1 3 3 2 0 0 2 1


int main(){
    srand(time(0));int lower_range = 0, upper_range = 1001, swap_counter = 500, display = 0, input = 1;
    vector<int> wtf;
    // = {1,6,7,3,2,4,5,0};
    // = {1,6,0,3,4,7,5,2};
    auto sp1 = chrono::steady_clock::now(); auto ep1 = chrono::steady_clock::now(); auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now(); auto ep2 = chrono::steady_clock::now(); auto dif2 = ep2 - sp2;
    auto sp3 = chrono::steady_clock::now(); auto ep3 = chrono::steady_clock::now(); auto dif3 = ep3 - sp3;
    auto sp4 = chrono::steady_clock::now(); auto ep4 = chrono::steady_clock::now(); auto dif4 = ep4 - sp4;

for (int m = 1; m <= 100000; m++) {if (m % 10000 == 0) {cout << "m = " << m << "\n";}

    if (input == 1) {//rand()%(upper_range - lower_range + 1) + lower_range
        wtf.reserve(upper_range + 1);
        for (int i = 0; i <= upper_range; i++) { wtf.push_back(i); }
        for (int i = 0, idx1, idx2, temp; i < swap_counter; i++) {
            idx1 = rand()%(upper_range - lower_range + 1) + lower_range;
            idx2 = rand()%(upper_range - lower_range + 1) + lower_range;
            while (idx2 == idx1) { idx2 = rand()%(upper_range - lower_range + 1) + lower_range; }

            temp = wtf[idx1];
            wtf[idx1] = wtf[idx2];
            wtf[idx2] = temp;
        }
    }
    if (display == 1) {
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    sp1 = chrono::steady_clock::now();
    int s = minSwapsCouples_2_no_test(wtf);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;

    //cout << "\ns = " << s << "\n";

    sp2 = chrono::steady_clock::now();
    int ss = minSwapsCouples_1(wtf);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;

    //cout << "\nss = " << ss << "\n";

    sp3 = chrono::steady_clock::now();
    int sss = minSwapsCouples_2(wtf);
    ep3 = chrono::steady_clock::now();
    dif3 += ep3 - sp3;

    sp4 = chrono::steady_clock::now();
    int ssss = minSwapsCouples_1_no_test(wtf);
    ep4 = chrono::steady_clock::now();
    dif4 += ep4 - sp4;

    if ((s != sss) || (ss != sss) || (ss != ssss)) {
        cout << "\n\nm = " << m << "\n";
        //cout << "\ns = " << s << "\n";
        cout << "\nss = " << ss << "\n";
        cout << "\nsss = " << sss << "\n\n";
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
        break;
    }

wtf.clear();}
cout << duration <double, milli> (dif1).count() << " ms" << "\n";
cout << duration <double, milli> (dif2).count() << " ms" << "\n";
cout << duration <double, milli> (dif3).count() << " ms" << "\n";
cout << duration <double, milli> (dif4).count() << " ms" << "\n";

    return 0;
}




