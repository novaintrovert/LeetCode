/*793. Preimage Size of Factorial Zeroes Function
Hard

Let f(x) be the number of zeroes at the end of x!.
(Recall that x! = 1 * 2 * 3 * ... * x, and by convention, 0! = 1.)

For example, f(3) = 0 because 3! = 6 has no zeroes at the end,
while f(11) = 2 because 11! = 39916800 has 2 zeroes at the end.

Given K, find how many non-negative integers x have the property that f(x) = K.

Input: K = 0
Output: 5
Explanation: 0!, 1!, 2!, 3!, and 4! end with K = 0 zeroes.

Input: K = 5
Output: 0
Explanation: There is no x such that x! ends in K = 5 zeroes.

Note:
    K will be an integer in the range [0, 10^9].
*/

/*
class Solution {
public:
    int preimageSizeFZF(int K) {

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

int preimageSizeFZF_brute(int K) {

}


//vector<long long int>
int preimageSizeFZF(int K) {
    if (K == 0) {return 5;}
    if (K < 0) {return 0;}
    if (K > 1000000000) {cout << "Invalid range.\n";return 0;}

/*long long int N = 0, temp = 0;
int this_many_zeros = 0;

for (int m = 1; m <= 1; m++) {//m = 15 MAX, or this_many_zeros will overflow
    this_many_zeros = 0;
    //N = pow(5, m) - 1;
    //N = 2147483647;
    N = 4000000015;
    for (int i = 1; i < 15; i++) {
        temp = pow(5, i);
        if (temp < N) {this_many_zeros += N / temp;}

        else {
            cout << "N = " << N << ", this_many_zeros = " << this_many_zeros << "\n";
            break;
        }
    }
}*/

/*5 ^ 14 = 6,103,515,625
5 ^ 13 = 1,220,703,125

given that N is in range (5 ^ p)(INCLUSIVE) & 5 ^ q(EXCLUSIVE),
there will be...
int this_many_zeros = 0;
for (int i = 1; i <= p; i++) {this_many_zeros += N / (5 ^ i);}
there will be "this_many_zeros".

largest 32 bit integer = 2,147,483,647
N = 2147483647, this_many_zeros = 536870902
N = 4000000019, this_many_zeros = 1000000000

N = 4, this_many_zeros = 0
N = 24, this_many_zeros = 4
N = 124, this_many_zeros = 28
N = 624, this_many_zeros = 152
N = 3124, this_many_zeros = 776
N = 15624, this_many_zeros = 3900
N = 78124, this_many_zeros = 19524
N = 390624, this_many_zeros = 97648
N = 1953124, this_many_zeros = 488272
N = 9765624, this_many_zeros = 2441396
N = 48828124, this_many_zeros = 12207020
N = 244140624, this_many_zeros = 61035144
N = 1220703124, this_many_zeros = 305175768
N = 6103515624, this_many_zeros = 1525878892
*/

    long long int pin_range[14][2];
    pin_range[0][0] = 0, pin_range[0][1] = 4;
    pin_range[1][0] = 4, pin_range[1][1] = 24;
    pin_range[2][0] = 28, pin_range[2][1] = 124;
    pin_range[3][0] = 152, pin_range[3][1] = 624;
    pin_range[4][0] = 776, pin_range[4][1] = 3124;
    pin_range[5][0] = 3900, pin_range[5][1] = 15624;
    pin_range[6][0] = 19524, pin_range[6][1] = 78124;
    pin_range[7][0] = 97648, pin_range[7][1] = 390624;
    pin_range[8][0] = 488272, pin_range[8][1] = 1953124;
    pin_range[9][0] = 2441396, pin_range[9][1] = 9765624;
    pin_range[10][0] = 12207020, pin_range[10][1] = 48828124;
    pin_range[11][0] = 61035144, pin_range[11][1] = 244140624;
    pin_range[12][0] = 305175768, pin_range[12][1] = 1220703124;
    pin_range[13][0] = 1000000000, pin_range[13][1] = 4000000019;

    int pow_5[13];
    pow_5[0] = 5, pow_5[1] = 25, pow_5[2] = 125, pow_5[3] = 625, pow_5[4] = 3125, pow_5[5] = 15625;
    pow_5[6] = 78125, pow_5[7] = 390625, pow_5[8] = 1953125, pow_5[9] = 9765625, pow_5[10] = 48828125;
    pow_5[11] = 244140625, pow_5[12] = 1220703125;

    long long int left = 0, right = 0, mid, temp = 0;

    for (int i = 1; i < 14; i++) {
        if ((K > pin_range[i - 1][0])&&(K <= pin_range[i][0])) {
            left = pin_range[i - 1][1] + 1, right = pin_range[i][1];
            break;
        }
    }

    int found = 0, counter = 0;

    while (left < right) {
        mid = left + (right - left) / 2;
        counter = 0;
        for (int i = 1; i < 14; i++) {
            //temp = pow(5, i);
            if (pow_5[i - 1] <= mid) {counter += mid / pow_5[i - 1];}
            else {break;}
        }

        //cout << "left = " << left << ", mid = " << mid << ", right = " << right << ". counter = " << counter << "\n";

        if (counter < K) {left = mid + 1;}

        else if (counter == K) {found = 1;break;}

        else {right = mid;}
    }

    //long long int original_return_value = (found == 0)? 0: 5;

    //return vector<long long int> {original_return_value, mid};

    return (found == 0)? 0: 5;
}



int main(){
    srand(time(0));int K = 2, lower_range = 100000000, upper_range = 1000000000, display = 0, input = 0;

    auto start_point_1 = chrono::steady_clock::now();
    auto end_point_1 = chrono::steady_clock::now();
    auto diff_1 = end_point_1 - start_point_1;

for (int m = 0; m <= 10; m++) {if (m % 1 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){K = rand()%(upper_range - lower_range + 1) + lower_range;}
    if (display == 1){cout << "K = " << K << "\n";}

    //cout << "\n:\n";
    start_point_1 = chrono::steady_clock::now();
    //vector<long long int> shit = preimageSizeFZF(K);
    int shit = preimageSizeFZF(m);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    cout << "shit = " << shit << "\n\n\n";

    /*long long int N = 0, temp = 0;
    int found = 0, this_many_zeros = 0;

    long long int pow_5[14];
    pow_5[0] = 5, pow_5[1] = 25, pow_5[2] = 125, pow_5[3] = 625, pow_5[4] = 3125, pow_5[5] = 15625;
    pow_5[6] = 78125, pow_5[7] = 390625, pow_5[8] = 1953125, pow_5[9] = 9765625, pow_5[10] = 48828125;
    pow_5[11] = 244140625, pow_5[12] = 1220703125, pow_5[13] = 6103515625;

    if (shit[0] != 0) {
        this_many_zeros = 0;
        N = shit[1];
        for (int i = 1; i < 15; i++) {
            //temp = pow_5[i - 1];
            if (pow_5[i - 1] <= N) {this_many_zeros += N / pow_5[i - 1];}

            else {
                //cout << "N = " << N << ", this_many_zeros = " << this_many_zeros << "\n";
                break;
            }
        }
    }

    if ((shit[0] != 0)&&(this_many_zeros != K)) {
        cout << "K = " << K << "\n";
        break;
    }*/

}
cout << duration <double, milli> (diff_1).count() << " ms" << "\n";

    return 0;
}




