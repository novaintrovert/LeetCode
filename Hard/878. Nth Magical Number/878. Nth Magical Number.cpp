/*878. Nth Magical Number
Hard

A positive integer is magical if it is divisible by either A or B.

Return the N-th magical number.
Since the answer may be very large, return it modulo 10^9 + 7.

Input: N = 1, A = 2, B = 3
Output: 2

Input: N = 4, A = 2, B = 3
Output: 6

Input: N = 5, A = 2, B = 4
Output: 10

Input: N = 3, A = 6, B = 4
Output: 8

Note:
    1 <= N <= 10^9
    2 <= A <= 40000
    2 <= B <= 40000
*/

/*
class Solution {
public:
    int nthMagicalNumber(int N, int A, int B) {

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

//CAREFUL! DO NOT GET OVERFLOW!
vector<int> nthMagicalNumber_brute(int N, int restraint, int A, int B) {
    vector<int> dump;
    dump.reserve(N * 2);
    unordered_set<int> already_there;
    unordered_set<int>::iterator check_if_existed;
    for (int i = 0, temp; i < N; i++) {
        temp = A * (i + 1);
        check_if_existed = already_there.find(temp);
        if (check_if_existed == already_there.end()) {
            dump.push_back(temp);
            already_there.insert(temp);
        }
        temp = B * (i + 1);
        check_if_existed = already_there.find(temp);
        if (check_if_existed == already_there.end()) {
            dump.push_back(temp);
            already_there.insert(temp);
        }
    }
    sort(dump.begin(), dump.end());
    dump.resize(restraint);
    //for (int i = 1; i <= dump.size(); i++) {cout << dump[i - 1] << "\t";if (i % 10 == 0) {cout << "\n";}}
    //cout << dump[23] << ", " << dump[24] << ", " << dump[25] << ", " << dump[26];
    //cout << "\n\n\n\n";
    return dump;
}

int nthMagicalNumber_basic(int N, int P, int Q) {
    int MCD, A, B, test_timer = -1;

    if (P != Q) {
        int temp0 = P, temp1 = Q;

        while ((temp0 > 0)&&(temp1 > 0)) {
            if (temp0 > temp1) {temp0 -= temp1;}

            else {temp1 -= temp0;}
        }

        MCD = (temp0 > 0)? temp0: temp1;
    }

    if (P != Q) {A = P / MCD, B = Q / MCD;}

    else {A = P, B = 1;}

    int left = 2, right = 1000000007, mid = (left + right) / 2;

    if (test_timer >= 0) {cout << "N = " << N << "\n\n";}

    int  AB = A * B, count_A, mod_A, count_B, mod_B, count_AB;
    while (left < right) {
        count_A = mid / A, count_B = mid / B, count_AB = mid / AB;
        mod_A = mid - A * count_A, mod_B = mid - B * count_B;

        if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
            left = mid;
            break;
        }

        if (count_A + count_B - count_AB >= N) {right = mid;}

        else {left = mid + 1;}

        mid = (left + right) / 2;

        if (test_timer >= 0) {
            cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
            cout << "count_A = " << count_A << ", count_B = " << count_B << ", count_AB = " << count_AB << "\n\n";
            test_timer++;
        }
        //if (test_timer >= 30) {break;}
    }

    return left * MCD;
}

int nthMagicalNumber_entirely_wrong(int N, int A, int B) {
    int result, MCD, left, right, mid;
    int P, Q, PQ, MOD = 100, test_timer = -1;
    int count_A, mod_A, count_B, mod_B, count_AB;

    if (A != B) {
        int temp0 = A, temp1 = B;

        while ((temp0 > 0)&&(temp1 > 0)) {
            if (temp0 > temp1) {temp0 -= temp1;}

            else {temp1 -= temp0;}
        }

        MCD = (temp0 > 0)? temp0: temp1;

        P = A / MCD, Q = B / MCD;
    }
    else {P = A, Q = 1;}
    PQ = P * Q;

    int criteria = MOD / P + MOD / Q - MOD / (P * Q);

    if (test_timer >= 0) {cout << "criteria = " << criteria << "\n\n";}

    if (criteria < N) {
        if (test_timer >= 0) {cout << "now started determine max_num_below_MOD\n\n";}

        int offset = 0, mod, max_num_below_MOD = 1;
        left = MOD / 2, right = MOD, mid = (left + right) / 2;

        //find the largest "magical number" below MOD, which will be used to calculate mod.
        while (left < right) {
            count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
            mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

            if ((count_A + count_B - count_AB == criteria)&&(mod_A == 0)&&(mod_B == 0)) {
                left = mid;
                break;
            }

            if (count_A + count_B - count_AB >= criteria) {right = mid;}

            else {left = mid + 1;}

            mid = (left + right) / 2;

            if (test_timer >= 0) {
                cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                cout << "count_A = " << count_A << ", count_B = " << count_B << ", count_AB = " << count_AB << "\n\n";
                test_timer++;
            }
            //if (test_timer >= 30) {break;}
        }

        max_num_below_MOD = left * MCD;
        mod = MOD - max_num_below_MOD;

        int how_many_big_MOD_it_gets = N / criteria;

        if (test_timer >= 0) {
            cout << "max_num_below_MOD = " << max_num_below_MOD << "\n";
            cout << "mod = " << mod << "\n";
            cout << "how_many_big_MOD_it_gets = " << how_many_big_MOD_it_gets << "\n\n";
        }

        //MOD/mod < N/criteria -> (MOD/mod)*criteria < N
        //due to MOD > N, this will only happen if criteria < mod
        //and criteria < mod can happen
        //so many little mods that even big MOD is not enough to hold them back
        if (MOD / mod < how_many_big_MOD_it_gets) {
            offset = mod * (how_many_big_MOD_it_gets / (MOD / mod))//how many big MOD those swarm of small mods surpass
             + (MOD % mod) * (how_many_big_MOD_it_gets / (MOD / mod));

            if (test_timer >= 0) {
                cout << "MOD / mod < how_many_big_MOD_it_gets\n";
                cout << "offset = " << offset << "\n";
            }
        }
        else {
            offset = mod * how_many_big_MOD_it_gets;
            if (test_timer >= 0) {
                cout << "MOD / mod >= how_many_big_MOD_it_gets\n";
                cout << "offset = " << offset << "\n";
            }
        }

        int how_many_more_after_big_MODs = N - how_many_big_MOD_it_gets * criteria - how_many_big_MOD_it_gets / (MOD / mod);

        if (test_timer >= 0) {
            cout << "how_many_more_after_big_MODs = " << how_many_more_after_big_MODs << "\n\n";
        }

        if (how_many_more_after_big_MODs <= 0) {
            how_many_big_MOD_it_gets -= 1;

            offset = mod * (how_many_big_MOD_it_gets / (MOD / mod))//how many big MOD those swarm of small mods surpass
             + (MOD % mod) * (how_many_big_MOD_it_gets / (MOD / mod));

            how_many_more_after_big_MODs = N - how_many_big_MOD_it_gets * criteria - how_many_big_MOD_it_gets / (MOD / mod);

            if (test_timer >= 0) {
                cout << "how_many_more_after_big_MODs <= 0\n";
                cout << "how_many_big_MOD_it_gets = " << how_many_big_MOD_it_gets << "\n";
                cout << "offset = " << offset << "\n";
                cout << "how_many_more_after_big_MODs = " << how_many_more_after_big_MODs << "\n\n";
            }
        }

        if (test_timer >= 0) {
            cout << "initially:\n";
            cout << "left = " << offset << ", right = " << MOD << ", mid = " << (offset + MOD) / 2 << "\n\n";
        }

        left = offset, right = MOD, mid = (left + right) / 2;
        while (left < right) {
            count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
            mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

            if ((count_A + count_B - count_AB == how_many_more_after_big_MODs)&&(mod_A == 0)&&(mod_B == 0)) {
                left = mid;
                break;
            }

            if (count_A + count_B - count_AB >= how_many_more_after_big_MODs) {right = mid;}

            else {left = mid + 1;}

            mid = (left + right) / 2;

            if (test_timer >= 0) {
                cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                cout << "count_A = " << count_A << ", count_B = " << count_B << ", count_AB = " << count_AB << "\n\n";
                test_timer++;
            }
            //if (test_timer >= 30) {break;}
        }

        result = left * MCD;
    }

    else {
        left = 1, right = MOD, mid = (left + right) / 2;

        if (test_timer >= 0) {cout << "N = " << N << "\n\n";}

        while (left < right) {
            count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
            mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

            if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                left = mid;
                break;
            }

            if (count_A + count_B - count_AB >= N) {right = mid;}

            else {left = mid + 1;}

            mid = (left + right) / 2;

            if (test_timer >= 0) {
                cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                cout << "count_A = " << count_A << ", count_B = " << count_B << ", count_AB = " << count_AB << "\n\n";
                test_timer++;
            }
            //if (test_timer >= 30) {break;}
        }

        result = left * MCD;
    }

    return result;
}

int nthMagicalNumber_half_built(int N, int A, int B) {
    int result, MCD, left, right, mid;
    int P, Q, PQ, MOD = 400, mod, test_timer = -1;
    int count_A, mod_A, count_B, mod_B, count_AB;

    if (A != B) {
        int temp0 = A, temp1 = B;

        while ((temp0 > 0)&&(temp1 > 0)) {
            if (temp0 > temp1) {temp0 -= temp1;}

            else {temp1 -= temp0;}
        }

        MCD = (temp0 > 0)? temp0: temp1;

        P = A / MCD, Q = B / MCD;
    }
    else {P = A, Q = 1;}
    PQ = P * Q;//which is the (P + Q - 1)-th smallest number

    int criteria = MOD / P + MOD / Q - MOD / (P * Q);
    if (test_timer >= 0) {cout << "N = " << N << "\n\ncriteria = " << criteria << "\n\n";}

    if (criteria < N) {
        if (test_timer >= 0) {cout << "criteria < N\n\n";}

        int offset = 0, first_multiple_of_PQ_that_is_no_more_than_MOD = 0;

        /*feels so relieved to see that restriction of this problems means that PQ is roughly of the same order as MOD,
        or this problem will be harder to deal with*/

        //find the first multiple of PQ that is no less than MOD
        if (PQ <= MOD) {first_multiple_of_PQ_that_is_no_more_than_MOD = PQ * (MOD / PQ);}

        if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD = " << first_multiple_of_PQ_that_is_no_more_than_MOD << "\n\n";}

        if (first_multiple_of_PQ_that_is_no_more_than_MOD == 0) {
            if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD == 0\n\n";}

            if (P + Q - 1 < N) {
                if (test_timer >= 0) {cout << "P + Q - 2 < N\n\n";}

                int part_1 = N / (P + Q - 2), part_2 = N % (P + Q - 2);

                //calculate offset using part_1
                mod = PQ % MOD;

                /*this "larger, smaller...offset = " part will probably only work
                when 1, both larger & smaller are way smaller than MOD, 2, (larger * smaller) is roughly of the same order as MOD
                or it will fail miserably, causing overflow (compared to MOD) kind of trouble*/
                int larger, smaller;
                if (mod > part_1) {larger = mod, smaller = part_1;}
                else {larger = part_1, smaller = mod;}

                int smaller_part_1 = MOD / smaller;
                int smaller_part_2 = MOD % smaller;

                /*larger * smaller =
                fraction_of_larger * smaller
                 + (close_to_MODs * smaller + smaller_part_2 * whatever_that_is)//this line is multiplies of MOD
                 - smaller_part_2 * whatever_that_is;

                =
                (larger % smaller_part_1) * smaller
                 + (smaller_part_1 * (larger / smaller_part_1) * smaller + smaller_part_2 * (larger / smaller_part_1))//this line is multiplies of MOD
                 - smaller_part_2 * (larger / smaller_part_1);*/

                if (test_timer >= 0) {
                    cout << "we need to find the " << part_2 << "th one\n";
                    cout << "(larger % smaller_part_1) * smaller = " << (larger % smaller_part_1) * smaller << "\n";
                    cout << "smaller_part_2 * (larger / smaller_part_1) = " << smaller_part_2 * (larger / smaller_part_1) << "\n\n";

                }

                offset = (larger % smaller_part_1) * smaller - smaller_part_2 * (larger / smaller_part_1);
                offset = offset % MOD;

                if (test_timer >= 0) {cout << "offset = " << offset << "\n\n";}

                //find the (part_2 - 1)-th number
                left = 0, right = PQ, mid = (left + right) / 2;
                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == part_2 - 1)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= part_2 - 1) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                if (test_timer >= 0) {cout << "left = " << left << "\n\n";}

                result = (left + offset) % MOD;
            }

            else if (P + Q - 1 > N) {//easy~
                if (test_timer >= 0) {cout << "P + Q - 2 > N\n\n";}

                left = MOD, right = PQ, mid = (left + right) / 2;
                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= N) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                result = left % MOD;
            }

            else if (P + Q - 1 == N) {//easiest~
                if (P >= Q) {result = (PQ - Q) % MOD;}
                else {result = (PQ - P) % MOD;}
            }
        }

        else {
            if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD > 0\n\n";}

            mod = MOD - first_multiple_of_PQ_that_is_no_more_than_MOD;

            int how_many_multiples_of_PQ_within_MOD = MOD / PQ;
            int how_many_close_to_MOD_number_which_is_multiples_of_PQ = N / (how_many_multiples_of_PQ_within_MOD * (P + Q - 2));

            int larger, smaller;
            if (mod > how_many_close_to_MOD_number_which_is_multiples_of_PQ) {
                larger = mod;
                smaller = how_many_close_to_MOD_number_which_is_multiples_of_PQ;
            }
            else {
                larger = how_many_close_to_MOD_number_which_is_multiples_of_PQ;
                smaller = mod;
            }

            int smaller_part_1 = first_multiple_of_PQ_that_is_no_more_than_MOD / smaller;
            int smaller_part_2 = first_multiple_of_PQ_that_is_no_more_than_MOD % smaller;

            /*larger * smaller =
            fraction_of_larger * smaller
             + (close_to_MODs * smaller + smaller_part_2 * whatever_that_is)//this line is multiplies of MOD
             - smaller_part_2 * whatever_that_is;

            =
            (larger % smaller_part_1) * smaller
             + (smaller_part_1 * (larger / smaller_part_1) * smaller + smaller_part_2 * (larger / smaller_part_1))//this line is multiplies of MOD
             - smaller_part_2 * (larger / smaller_part_1);*/

            if (test_timer >= 0) {
                cout << "larger = " << larger << "\n";
                cout << "smaller = " << smaller << "\n";
                cout << "(MOD / PQ)*(P + Q - 2) = " << ((MOD / PQ)*(P + Q - 1)) << "\n";
                cout << "(N / ((MOD / PQ)*(P + Q - 2))) = " << (N / ((MOD / PQ)*(P + Q - 1))) << "\n";
                cout << "(larger / smaller_part_1) = " << (larger / smaller_part_1) << "\n\n";
            }

            int need_to_find_this_th_one = N - ((MOD / PQ)*(P + Q - 1))*(N / ((MOD / PQ)*(P + Q - 1))) - (larger / smaller_part_1);

            if (test_timer >= 0) {
                cout << "need_to_find_this_th_one = " << need_to_find_this_th_one << "\n";
                cout << "(larger % smaller_part_1) * smaller = " << (larger % smaller_part_1) * smaller << "\n";
                cout << "smaller_part_2 * (larger / smaller_part_1) = " << smaller_part_2 * (larger / smaller_part_1) << "\n\n";
            }

            offset = (larger % smaller_part_1) * smaller - smaller_part_2 * (larger / smaller_part_1);

            if (test_timer >= 0) {cout << "offset = " << offset << "\n\n";}

            if (need_to_find_this_th_one > 0) {
                if (test_timer >= 0) {cout << "need_to_find_this_th_one > 0\n\n";}

                //find that
                left = 0, right = MOD, mid = (left + right) / 2;

                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == need_to_find_this_th_one)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= need_to_find_this_th_one) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                if (test_timer >= 0) {cout << "left = " << left << "\n\n";}
                result = (left - offset) % MOD;
            }

            else if (need_to_find_this_th_one < 0) {
                if (test_timer >= 0) {cout << "need_to_find_this_th_one < 0\n\n";}

                //find that

                int reversed = need_to_find_this_th_one * (-1);

                left = 0, right = MOD, mid = (left + right) / 2;

                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == reversed)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= reversed) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                result = offset - left;
                if (result < 0) {
                    result += MOD;
                }
            }

            else {
                if (test_timer >= 0) {cout << "what?!\n\n";}
                result = offset;
            }

        }
    }

    else {
        left = 1, right = MOD, mid = (left + right) / 2;

        if (test_timer >= 0) {cout << "N = " << N << "\n\n";}

        while (left < right) {
            count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
            mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

            if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                left = mid;
                break;
            }

            if (count_A + count_B - count_AB >= N) {right = mid;}

            else {left = mid + 1;}

            mid = (left + right) / 2;

            if (test_timer >= 0) {
                cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                cout << "count_A = " << count_A << ", count_B = " << count_B << ", count_AB = " << count_AB << "\n\n";
                test_timer++;
            }
            //if (test_timer >= 30) {break;}
        }

        result = left * MCD;
    }

    return result;
}

int nthMagicalNumber_still_got_some_problems(int N, int A, int B) {
    int result, MCD, left, right, mid;
    int P, Q, PQ, MOD = 400, mod, test_timer = 0;
    int count_A, mod_A, count_B, mod_B, count_AB;

    if (A != B) {
        int temp0 = A, temp1 = B;
        while ((temp0 > 0)&&(temp1 > 0)) {
            if (temp0 > temp1) {temp0 -= temp1;}
            else {temp1 -= temp0;}
        }
        MCD = (temp0 > 0)? temp0: temp1;
        P = A / MCD, Q = B / MCD;
    }
    else {P = A, Q = 1;}
    PQ = P * Q;//which is the (P + Q - 1)-th smallest number, there are (P + Q - 2) numbers before it

    int criteria = MOD / P + MOD / Q - MOD / (P * Q);
    if (test_timer >= 0) {
        cout << "N = " << N << "\n";
        cout << "P = " << P << ", Q = " << Q << ", MCD = " << MCD << "\n";
        cout << "criteria = " << criteria << "\n\n";}

    if (criteria < N) {
        if (test_timer >= 0) {cout << "criteria < N\n\n";}

        int offset = 0, first_multiple_of_PQ_that_is_no_more_than_MOD = 0;
        /*feels so relieved to see that restriction of this problems means
        that PQ is roughly of the same order as MOD,
        or this problem will be harder to deal with*/
        //find the first multiple of PQ that is no less than MOD
        if (PQ * MCD <= MOD) {first_multiple_of_PQ_that_is_no_more_than_MOD = (PQ * MCD) * (MOD / PQ);}
        if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD = " << first_multiple_of_PQ_that_is_no_more_than_MOD << "\n\n";}

        if (first_multiple_of_PQ_that_is_no_more_than_MOD == 0) {
            if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD == 0\n\n";}

            if (P + Q - 1 < N) {//IM NOT ENTIRELY SURE M.C.D. IN THE END OF THIS PART IS CORRECT.
                if (test_timer >= 0) {cout << "P + Q - 1 < N\n\n";}

                int part_1 = N / (P + Q - 1), part_2 = N % (P + Q - 1);

                //calculate offset using part_1
                mod = PQ % MOD;

                /*this "larger, smaller...offset = " part will probably only work
                when 1, both larger & smaller are way smaller than MOD, 2, (larger * smaller) is roughly of the same order as MOD
                or it will fail miserably, causing overflow (compared to MOD) kind of trouble*/
                int larger, smaller;
                if (mod > part_1) {larger = mod, smaller = part_1;}
                else {larger = part_1, smaller = mod;}

                int smaller_part_1 = MOD / smaller;
                int smaller_part_2 = MOD % smaller;

                /*larger * smaller =
                fraction_of_larger * smaller
                 + (close_to_MODs * smaller + smaller_part_2 * whatever_that_is)//this line is multiplies of MOD
                 - smaller_part_2 * whatever_that_is;

                =
                (larger % smaller_part_1) * smaller
                 + (smaller_part_1 * (larger / smaller_part_1) * smaller + smaller_part_2 * (larger / smaller_part_1))//this line is multiplies of MOD
                 - smaller_part_2 * (larger / smaller_part_1);*/

                if (test_timer >= 0) {
                    cout << "we need to find the " << part_2 << "th one\n";
                    cout << "(larger % smaller_part_1) * smaller = " << (larger % smaller_part_1) * smaller << "\n";
                    cout << "smaller_part_2 * (larger / smaller_part_1) = " << smaller_part_2 * (larger / smaller_part_1) << "\n\n";

                }

                offset = (larger % smaller_part_1) * smaller - smaller_part_2 * (larger / smaller_part_1);
                offset = offset % MOD;

                if (test_timer >= 0) {cout << "offset = " << offset << "\n\n";}

                //find the part_2-th number
                left = 0, right = PQ, mid = (left + right) / 2;
                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == part_2)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= part_2) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                if (test_timer >= 0) {cout << "left = " << left << "\n\n";}

                result = ((left + offset)* MCD) % MOD;
            }

            else if (P + Q - 1 > N) {//easy~, the same as criteria >= N
                if (test_timer >= 0) {cout << "P + Q - 1 > N\n\n";}

                left = MOD, right = PQ, mid = (left + right) / 2;
                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= N) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                result = (left * MCD) % MOD;
            }

            else if (P + Q - 1 == N) {//easiest~
                result = (PQ * MCD) % MOD;
            }
        }

        else {
            if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD > 0\n\n";}

            mod = MOD - first_multiple_of_PQ_that_is_no_more_than_MOD;

            int how_many_multiples_of_PQ_within_MOD = MOD / (PQ * MCD);
            int how_many_close_to_MOD_number_which_is_multiples_of_PQ = N / criteria;
            //int how_many_close_to_MOD_number_which_is_multiples_of_PQ = N / (how_many_multiples_of_PQ_within_MOD * (P + Q - 1));

            if (test_timer >= 0) {
                cout << "how_many_multiples_of_PQ_within_MOD = " << how_many_multiples_of_PQ_within_MOD << "\n";
                cout << "how_many_close_to_MOD_number_which_is_multiples_of_PQ = " << how_many_close_to_MOD_number_which_is_multiples_of_PQ << "\n\n";
            }

            int need_to_find_this_th_one;

            int larger, smaller;
            if (mod > how_many_close_to_MOD_number_which_is_multiples_of_PQ) {
                larger = mod;
                smaller = how_many_close_to_MOD_number_which_is_multiples_of_PQ;
            }
            else {
                larger = how_many_close_to_MOD_number_which_is_multiples_of_PQ;
                smaller = mod;
            }

            if (MOD/smaller <= larger){
                int smaller_part_1 = first_multiple_of_PQ_that_is_no_more_than_MOD / smaller;
                int smaller_part_2 = first_multiple_of_PQ_that_is_no_more_than_MOD % smaller;

                /*larger * smaller =
                fraction_of_larger * smaller
                 + (close_to_MODs * smaller + smaller_part_2 * whatever_that_is)//this line is multiplies of MOD
                 - smaller_part_2 * whatever_that_is;

                =
                (larger % smaller_part_1) * smaller
                 + (smaller_part_1 * (larger / smaller_part_1) * smaller + smaller_part_2 * (larger / smaller_part_1))//this line is multiplies of MOD
                 - smaller_part_2 * (larger / smaller_part_1);*/


                need_to_find_this_th_one = N - ((MOD / (PQ * MCD))*(P + Q - 1))*(N / ((MOD / (PQ * MCD))*(P + Q - 1))) - (larger / smaller_part_1);

                if (test_timer >= 0) {
                    cout << "need_to_find_this_th_one = " << need_to_find_this_th_one << "\n";
                    cout << "(larger % smaller_part_1) * smaller = " << (larger % smaller_part_1) * smaller << "\n";
                    cout << "smaller_part_2 * (larger / smaller_part_1) = " << smaller_part_2 * (larger / smaller_part_1) << "\n\n";
                }

                offset = (larger % smaller_part_1) * smaller - smaller_part_2 * (larger / smaller_part_1);
            }
            else {
                need_to_find_this_th_one = N - ((MOD / (PQ * MCD))*(P + Q - 1))*(N / ((MOD / (PQ * MCD))*(P + Q - 1)));
                offset = larger * smaller;
            }

            if (test_timer >= 0) {
                cout << "larger = " << larger << "\n";
                cout << "smaller = " << smaller << "\n";
                cout << "(MOD / PQ)*(P + Q - 1) = " << ((MOD / PQ)*(P + Q - 1)) << "\n";
                cout << "(N / ((MOD / PQ)*(P + Q - 1))) = " << (N / ((MOD / PQ)*(P + Q - 1))) << "\n";
                cout << "offset = " << offset << "\n\n";
            }

            if (need_to_find_this_th_one > 0) {
                if (test_timer >= 0) {cout << "need_to_find_this_th_one > 0\n\n";}

                //find that
                left = 0, right = MOD, mid = (left + right) / 2;

                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == need_to_find_this_th_one)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= need_to_find_this_th_one) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                if (test_timer >= 0) {
                    cout << "left = " << left << "\n";
                    cout << "left * MCD - offset = " << left * MCD - offset << "\n\n";
                }
                result = (left * MCD - offset) % MOD;
                if (result < 0) {result += MOD;}
            }



            else if (need_to_find_this_th_one <= 0) {
                if (test_timer >= 0) {cout << "need_to_find_this_th_one < 0\n\n";}

                /*what we have here, is:
                1. a big negative sum which is probably larger than MOD
                2. remaining N

                what we gonna do here is:
                1. find how many (P + Q - 1) be within N
                2. add *that many PQ* to that big negative sum (thus make it closer to 0), while remaining N become (*remaining N*) % PQ
                3. find that (remaining N)-th number in range 1 to PQ
                4. add this (remaining N)-th number to that smaller negative sum, then find its 1st positive module relative to MOD
                */

                need_to_find_this_th_one = N - ((MOD / PQ)*(P + Q - 1))*(N / ((MOD / PQ)*(P + Q - 1)));
                int how_many_PQ_within = need_to_find_this_th_one / (P + Q - 1);
                need_to_find_this_th_one %= (P + Q - 1);

                //first_part < PQ
                int first_part = mod;
                int second_part = (N / ((MOD / PQ)*(P + Q - 1)));

                //that big sum is NEGATIVE first_part * second_part
                //the big sum now becomes NEGATIVE (first_part * second_part) -
                /*
                J = PQ - first_part
                ? = second_part - PQ

                (first_part * second_part) = (PQ - J) * (PQ + ?) = PQ (PQ - J + ?) - J * ?

                so, (first_part * second_part) is practically

                (PQ - J + ?) = (-J + second_part) = (second_part - PQ + first_part) times PQ

                - J * (second_part - PQ) = - (PQ - first_part) * (second_part - PQ)
                */

                left = 0, right = PQ, mid = (left + right) / 2;
                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == need_to_find_this_th_one)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= need_to_find_this_th_one) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                //now calculate POSITIVE
                //((how_many_PQ_within * PQ) - (first_part * second_part) + left) % MOD
                //while trying to make it positive

                /*
                (how_many_PQ_within * PQ) - (first_part * second_part) + left
                (how_many_PQ_within * PQ) - ((second_part - PQ + first_part) * PQ - (PQ - first_part) * (second_part - PQ)) + left
                (how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left
                */

                result = ((how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left;
                result *= MCD;
                result %= MOD;
                if (result < 0) {result += MOD;}
            }

            /*else {
                if (test_timer >= 0) {cout << "what?!\n\n";}
                result = offset;
            }*/

        }
    }

    else {
        left = 1, right = MOD, mid = (left + right) / 2;

        if (test_timer >= 0) {cout << "N = " << N << "\n\n";}

        while (left < right) {
            count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
            mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

            if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                left = mid;
                break;
            }

            if (count_A + count_B - count_AB >= N) {right = mid;}

            else {left = mid + 1;}

            mid = (left + right) / 2;

            if (test_timer >= 0) {
                cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                cout << "count_A = " << count_A << ", count_B = " << count_B << ", count_AB = " << count_AB << "\n\n";
                test_timer++;
            }
            //if (test_timer >= 30) {break;}
        }

        result = (left * MCD) % MOD;
    }

    return result;
}

int nthMagicalNumber_roughly_worked(int N, int A, int B) {
    int result, MCD, left, right, mid;
    int P, Q, PQ, MOD = 1000, mod, test_timer = -1;
    int count_A, mod_A, count_B, mod_B, count_AB;

    if (A == B) {
        int how_many_A_in_MOD = MOD / A;
        int remaining_N = N - (N / how_many_A_in_MOD)* how_many_A_in_MOD;

        /*
        (N / how_many_A_in_MOD) * (MOD - (how_many_A_in_MOD * A))
        (A*(first/A) + first%A) * (A*(second/A) + second%A)
        A*((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A)) + (first%A) * (second%A)
        */
        int first = N / how_many_A_in_MOD, second = MOD - (how_many_A_in_MOD * A);
        remaining_N -= ((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A));
        int offset = (first%A) * (second%A);
        result = (remaining_N * A - offset) % MOD;
        if (result < 0) {result += MOD;}
    }

    else {
        int temp0 = A, temp1 = B;
        while ((temp0 > 0)&&(temp1 > 0)) {
            if (temp0 > temp1) {temp0 -= temp1;}
            else {temp1 -= temp0;}
        }
        MCD = (temp0 > 0)? temp0: temp1;
        P = A / MCD, Q = B / MCD;
        PQ = P * Q;

        //PQ is the (P + Q - 1)-th smallest number, there are (P + Q - 2) numbers before it

        int criteria = MOD / P + MOD / Q - MOD / (P * Q);
        if (test_timer >= 0) {
            cout << "N = " << N << "\n";
            cout << "P = " << P << ", Q = " << Q << ", MCD = " << MCD << "\n";
            cout << "criteria = " << criteria << "\n\n";}

        if (criteria < N) {
            if (test_timer >= 0) {cout << "criteria < N\n\n";}

            int offset = 0, first_multiple_of_PQ_that_is_no_more_than_MOD = 0;
            /*feels so relieved to see that restriction of this problems means
            that PQ is roughly of the same order as MOD,
            or this problem will be harder to deal with*/
            //find the first multiple of PQ that is no less than MOD
            if (PQ * MCD <= MOD) {first_multiple_of_PQ_that_is_no_more_than_MOD = PQ * (MOD / PQ);}
            if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD = " << first_multiple_of_PQ_that_is_no_more_than_MOD << "\n\n";}

            if (first_multiple_of_PQ_that_is_no_more_than_MOD == 0) {
                if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD == 0\n\n";}

                if (P + Q - 1 < N) {//IM NOT ENTIRELY SURE M.C.D. IN THE END OF THIS PART IS CORRECT.
                    if (test_timer >= 0) {cout << "P + Q - 1 < N\n\n";}

                    int part_1 = N / (P + Q - 1), part_2 = N % (P + Q - 1);

                    //calculate offset using part_1
                    mod = PQ % MOD;

                    /*this "larger, smaller...offset = " part will probably only work
                    when 1, both larger & smaller are way smaller than MOD, 2, (larger * smaller) is roughly of the same order as MOD
                    or it will fail miserably, causing overflow (compared to MOD) kind of trouble*/
                    int larger, smaller;
                    if (mod > part_1) {larger = mod, smaller = part_1;}
                    else {larger = part_1, smaller = mod;}

                    int smaller_part_1 = MOD / smaller;
                    int smaller_part_2 = MOD % smaller;

                    /*larger * smaller =
                    fraction_of_larger * smaller
                     + (close_to_MODs * smaller + smaller_part_2 * whatever_that_is)//this line is multiplies of MOD
                     - smaller_part_2 * whatever_that_is;

                    =
                    (larger % smaller_part_1) * smaller
                     + (smaller_part_1 * (larger / smaller_part_1) * smaller + smaller_part_2 * (larger / smaller_part_1))//this line is multiplies of MOD
                     - smaller_part_2 * (larger / smaller_part_1);*/

                    if (test_timer >= 0) {
                        cout << "we need to find the " << part_2 << "th one\n";
                        cout << "(larger % smaller_part_1) * smaller = " << (larger % smaller_part_1) * smaller << "\n";
                        cout << "smaller_part_2 * (larger / smaller_part_1) = " << smaller_part_2 * (larger / smaller_part_1) << "\n\n";

                    }

                    offset = (larger % smaller_part_1) * smaller - smaller_part_2 * (larger / smaller_part_1);
                    offset = offset % MOD;

                    if (test_timer >= 0) {cout << "offset = " << offset << "\n\n";}

                    //find the part_2-th number
                    left = 0, right = PQ, mid = (left + right) / 2;
                    while (left < right) {
                        count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                        mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                        if ((count_A + count_B - count_AB == part_2)&&(mod_A == 0)&&(mod_B == 0)) {
                            left = mid;
                            break;
                        }

                        if (count_A + count_B - count_AB >= part_2) {right = mid;}

                        else {left = mid + 1;}

                        mid = (left + right) / 2;
                    }

                    if (test_timer >= 0) {cout << "left = " << left << "\n\n";}

                    result = ((left + offset)* MCD) % MOD;
                }

                else if (P + Q - 1 > N) {//easy~, the same as criteria >= N
                    if (test_timer >= 0) {cout << "P + Q - 1 > N\n\n";}

                    left = MOD, right = PQ, mid = (left + right) / 2;
                    while (left < right) {
                        count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                        mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                        if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                            left = mid;
                            break;
                        }

                        if (count_A + count_B - count_AB >= N) {right = mid;}

                        else {left = mid + 1;}

                        mid = (left + right) / 2;
                    }

                    result = (left * MCD) % MOD;
                }

                else if (P + Q - 1 == N) {//easiest~
                    result = (PQ * MCD) % MOD;
                }
            }

            else {
                if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD > 0\n\n";}

                mod = MOD - first_multiple_of_PQ_that_is_no_more_than_MOD;

                /*what we have here, is:
                1. a big negative sum which is probably larger than MOD
                2. remaining N

                what we gonna do here is:
                1. find how many (P + Q - 1) be within N
                2. add *that many PQ* to that big negative sum (thus make it closer to 0), while remaining N become (*remaining N*) % PQ
                3. find that (remaining N)-th number in range 1 to PQ
                4. add this (remaining N)-th number to that smaller negative sum, then find its 1st positive module relative to MOD
                */

                int remaining_N = N - ((MOD / PQ)*(P + Q - 1))*(N / ((MOD / PQ)*(P + Q - 1)));

                if (test_timer >= 0) {cout << "remaining_N = " << remaining_N << "\n\n";}

                int how_many_PQ_within = remaining_N / (P + Q - 1);
                remaining_N %= (P + Q - 1);

                if (test_timer >= 0) {
                    cout << "how_many_PQ_within = " << how_many_PQ_within << "\n";
                    cout << "remaining_N = " << remaining_N << "\n\n";
                }

                //first_part < PQ
                int first_part = mod;
                int second_part = (N / ((MOD / PQ)*(P + Q - 1)));

                if (test_timer >= 0) {
                    cout << "first_part = " << first_part << "\n";
                    cout << "second_part = " << second_part << "\n";
                }

                //that big sum is NEGATIVE first_part * second_part
                //the big sum now becomes NEGATIVE (first_part * second_part) -
                /*
                J = PQ - first_part
                ? = second_part - PQ

                (first_part * second_part) = (PQ - J) * (PQ + ?) = PQ (PQ - J + ?) - J * ?

                so, (first_part * second_part) is practically

                (PQ - J + ?) = (-J + second_part) = (second_part - PQ + first_part) times PQ

                - J * (second_part - PQ) = - (PQ - first_part) * (second_part - PQ)
                */

                left = 0, right = PQ, mid = (left + right) / 2;
                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == remaining_N)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= remaining_N) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                //now calculate POSITIVE
                //((how_many_PQ_within * PQ) - (first_part * second_part) + left) % MOD
                //while trying to make it positive

                /*
                (how_many_PQ_within * PQ) - (first_part * second_part) + left
                (how_many_PQ_within * PQ) - ((second_part - PQ + first_part) * PQ - (PQ - first_part) * (second_part - PQ)) + left
                (how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left
                */

                if (test_timer >= 0) {
                    cout << "that big offset = " << ((how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) << "\n";
                    cout << "left = " << left << "\n";
                }

                result = ((how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left;
                result *= MCD;
                result %= MOD;
                if (result < 0) {result += MOD;}
            }
        }

        else {
            left = 1, right = MOD, mid = (left + right) / 2;

            if (test_timer >= 0) {cout << "N = " << N << "\n\n";}

            while (left < right) {
                count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                    left = mid;
                    break;
                }

                if (count_A + count_B - count_AB >= N) {right = mid;}

                else {left = mid + 1;}

                mid = (left + right) / 2;

                if (test_timer >= 0) {
                    cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                    cout << "count_A = " << count_A << ", count_B = " << count_B << ", count_AB = " << count_AB << "\n\n";
                    test_timer++;
                }
                //if (test_timer >= 30) {break;}
            }

            result = (left * MCD) % MOD;
        }
    }
    return result;
}


/*
82230.3 ms

brute:
389640 ms
*/
int nthMagicalNumber_pretty_sure_it_will_work(int N, int A, int B) {
    int result, MCD, left, right, mid;
    int P, Q, PQ, MOD = 10007, mod, test_timer = -1;
    int count_A, mod_A, count_B, mod_B, count_AB;

    if (A == B) {
        int how_many_A_in_MOD = MOD / A;
        int remaining_N = N - (N / how_many_A_in_MOD)* how_many_A_in_MOD;

        /*
        (N / how_many_A_in_MOD) * (MOD - (how_many_A_in_MOD * A))
        (A*(first/A) + first%A) * (A*(second/A) + second%A)
        A*((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A)) + (first%A) * (second%A)
        */
        int first = N / how_many_A_in_MOD, second = MOD - (how_many_A_in_MOD * A);
        remaining_N -= ((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A));
        int offset = (first%A) * (second%A);
        result = (remaining_N * A - offset) % MOD;
        if (result < 0) {result += MOD;}
    }

    else {
        int temp0 = A, temp1 = B;
        while ((temp0 > 0)&&(temp1 > 0)) {
            if (temp0 > temp1) {temp0 -= temp1;}
            else {temp1 -= temp0;}
        }
        MCD = (temp0 > 0)? temp0: temp1;
        P = A / MCD, Q = B / MCD;
        PQ = P * Q;//PQ is the (P + Q - 1)-th smallest number, there are (P + Q - 2) numbers before it

        int criteria = MOD / P + MOD / Q - MOD / (P * Q);
        if (test_timer >= 0) {
            cout << "N = " << N << ", MOD = " << MOD << "\n";
            cout << "P = " << P << ", Q = " << Q << ", MCD = " << MCD << "\n";
            cout << "criteria = " << criteria << "\n\n";}

        if (criteria < N) {
            if (test_timer >= 0) {cout << "criteria < N\n\n";}

            int offset = 0, first_multiple_of_PQ_that_is_no_more_than_MOD = 0;
            /*feels so relieved to see that restriction of this problems means
            that PQ is roughly of the same order as MOD,
            or this problem will be harder to deal with*/
            //find the first multiple of PQ that is no less than MOD
            if (PQ * MCD <= MOD) {first_multiple_of_PQ_that_is_no_more_than_MOD = PQ * (MOD / PQ);}
            if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD = " << first_multiple_of_PQ_that_is_no_more_than_MOD << "\n\n";}

            if (first_multiple_of_PQ_that_is_no_more_than_MOD == 0) {
                if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD == 0\n\n";}

                if (P + Q - 1 < N) {//IM NOT ENTIRELY SURE M.C.D. IN THE END OF THIS PART IS CORRECT.
                    if (test_timer >= 0) {cout << "P + Q - 1 < N\n\n";}

                    int part_1 = N / (P + Q - 1), part_2 = N % (P + Q - 1);

                    //calculate offset using part_1
                    mod = PQ % MOD;

                    /*this "larger, smaller...offset = " part will probably only work
                    when 1, both larger & smaller are way smaller than MOD, 2, (larger * smaller) is roughly of the same order as MOD
                    or it will fail miserably, causing overflow (compared to MOD) kind of trouble*/
                    int larger, smaller;
                    if (mod > part_1) {larger = mod, smaller = part_1;}
                    else {larger = part_1, smaller = mod;}

                    int smaller_part_1 = MOD / smaller;
                    int smaller_part_2 = MOD % smaller;

                    /*larger * smaller =
                    fraction_of_larger * smaller
                     + (close_to_MODs * smaller + smaller_part_2 * whatever_that_is)//this line is multiplies of MOD
                     - smaller_part_2 * whatever_that_is;

                    =
                    (larger % smaller_part_1) * smaller
                     + (smaller_part_1 * (larger / smaller_part_1) * smaller + smaller_part_2 * (larger / smaller_part_1))//this line is multiplies of MOD
                     - smaller_part_2 * (larger / smaller_part_1);*/

                    if (test_timer >= 0) {
                        cout << "we need to find the " << part_2 << "th one\n";
                        cout << "(larger % smaller_part_1) * smaller = " << (larger % smaller_part_1) * smaller << "\n";
                        cout << "smaller_part_2 * (larger / smaller_part_1) = " << smaller_part_2 * (larger / smaller_part_1) << "\n\n";

                    }

                    offset = (larger % smaller_part_1) * smaller - smaller_part_2 * (larger / smaller_part_1);
                    offset = offset % MOD;

                    if (test_timer >= 0) {cout << "offset = " << offset << "\n\n";}

                    //find the part_2-th number
                    left = 0, right = PQ, mid = (left + right) / 2;
                    while (left < right) {
                        count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                        mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                        if ((count_A + count_B - count_AB == part_2)&&(mod_A == 0)&&(mod_B == 0)) {
                            left = mid;
                            break;
                        }

                        if (count_A + count_B - count_AB >= part_2) {right = mid;}

                        else {left = mid + 1;}

                        mid = (left + right) / 2;
                    }

                    if (test_timer >= 0) {cout << "left = " << left << "\n\n";}

                    //result = ((left + offset) * MCD) % MOD;

                    if (result < 0) {result += MOD;}
                }

                else if (P + Q - 1 > N) {//easy~, the same as criteria >= N
                    if (test_timer >= 0) {cout << "P + Q - 1 > N\n\n";}

                    left = MOD, right = PQ, mid = (left + right) / 2;
                    while (left < right) {
                        count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                        mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                        if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                            left = mid;
                            break;
                        }

                        if (count_A + count_B - count_AB >= N) {right = mid;}

                        else {left = mid + 1;}

                        mid = (left + right) / 2;
                    }

                    result = (left * MCD) % MOD;
                }

                else if (P + Q - 1 == N) {//easiest~
                    result = (PQ * MCD) % MOD;
                }
            }

            else {
                if (test_timer >= 0) {cout << "first_multiple_of_PQ_that_is_no_more_than_MOD > 0\n\n";}

                mod = MOD - first_multiple_of_PQ_that_is_no_more_than_MOD;

                /*what we have here, is:
                1. a big negative sum which is probably larger than MOD
                2. remaining N

                what we gonna do here is:
                1. find how many (P + Q - 1) be within N
                2. add *that many PQ* to that big negative sum (thus make it closer to 0), while remaining N become (*remaining N*) % PQ
                3. find that (remaining N)-th number in range 1 to PQ
                4. add this (remaining N)-th number to that smaller negative sum, then find its 1st positive module relative to MOD
                */

                int remaining_N = N - ((MOD / PQ)*(P + Q - 1))*(N / ((MOD / PQ)*(P + Q - 1)));

                if (test_timer >= 0) {cout << "remaining_N = " << remaining_N << "\n\n";}

                int how_many_PQ_within = remaining_N / (P + Q - 1);
                remaining_N %= (P + Q - 1);

                if (test_timer >= 0) {
                    cout << "how_many_PQ_within = " << how_many_PQ_within << "\n";
                    cout << "remaining_N = " << remaining_N << "\n\n";
                }

                //first_part < PQ
                int first_part = mod;
                int second_part = (N / ((MOD / PQ)*(P + Q - 1)));

                if (test_timer >= 0) {
                    cout << "first_part = " << first_part << "\n";
                    cout << "second_part = " << second_part << "\n";
                }

                //that big sum is NEGATIVE first_part * second_part
                //the big sum now becomes NEGATIVE (first_part * second_part) -
                /*
                J = PQ - first_part
                ? = second_part - PQ

                (first_part * second_part) = (PQ - J) * (PQ + ?) = PQ (PQ - J + ?) - J * ?

                so, (first_part * second_part) is practically

                (PQ - J + ?) = (-J + second_part) = (second_part - PQ + first_part) times PQ

                - J * (second_part - PQ) = - (PQ - first_part) * (second_part - PQ)
                */

                left = 0, right = PQ, mid = (left + right) / 2;
                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == remaining_N)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= remaining_N) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                //now calculate POSITIVE
                //((how_many_PQ_within * PQ) - (first_part * second_part) + left) % MOD
                //while trying to make it positive

                /*
                (how_many_PQ_within * PQ) - (first_part * second_part) + left
                (how_many_PQ_within * PQ) - ((second_part - PQ + first_part) * PQ - (PQ - first_part) * (second_part - PQ)) + left
                (how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left
                */

                if (test_timer >= 0) {
                    cout << "that big offset = " << ((how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) << "\n";
                    cout << "left = " << left << "\n";
                }

                //result = ((how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left;
                result = ((how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left;

                result *= MCD;
                result %= MOD;
                if (result < 0) {result += MOD;}
            }
        }

        else {
            left = 1, right = MOD, mid = (left + right) / 2;

            if (test_timer >= 0) {cout << "N = " << N << "\n\n";}

            while (left < right) {
                count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                    left = mid;
                    break;
                }

                if (count_A + count_B - count_AB >= N) {right = mid;}

                else {left = mid + 1;}

                mid = (left + right) / 2;

                if (test_timer >= 0) {
                    cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                    cout << "count_A = " << count_A << ", count_B = " << count_B << ", count_AB = " << count_AB << "\n\n";
                    test_timer++;
                }
                //if (test_timer >= 30) {break;}
            }

            result = (left * MCD) % MOD;
        }
    }
    return result;
}

int nthMagicalNumber_pretty_sure(int N, int A, int B) {
    int result, MCD, left, right, mid, test_timer = -1;
    int P, Q, PQ, MOD = 1000000007, mod;
    int count_A, mod_A, count_B, mod_B, count_AB;

    if (A == B) {
        int how_many_A_in_MOD = MOD / A;
        int remaining_N = N - (N / how_many_A_in_MOD)* how_many_A_in_MOD;

        /*
        (N / how_many_A_in_MOD) * (MOD - (how_many_A_in_MOD * A))
        (A*(first/A) + first%A) * (A*(second/A) + second%A)
        A*((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A)) + (first%A) * (second%A)
        */
        int first = N / how_many_A_in_MOD, second = MOD - (how_many_A_in_MOD * A);
        remaining_N -= ((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A));
        int offset = (first%A) * (second%A);
        result = (remaining_N * A - offset) % MOD;
        if (result < 0) {result += MOD;}
    }

    else {
        int temp0 = A, temp1 = B;
        while ((temp0 > 0)&&(temp1 > 0)) {
            if (temp0 > temp1) {temp0 -= temp1;}
            else {temp1 -= temp0;}
        }
        MCD = (temp0 > 0)? temp0: temp1;
        P = A / MCD, Q = B / MCD;
        PQ = P * Q;

        //PQ is the (P + Q - 1)-th smallest number, there are (P + Q - 2) numbers before it

        int criteria = MOD / P + MOD / Q - MOD / (P * Q);

        if (criteria < N) {
            int offset = 0, first_multiple_of_PQ_that_is_no_more_than_MOD = 0;
            /*feels so relieved to see that restriction of this problems means
            that PQ is roughly of the same order as MOD,
            or this problem will be harder to deal with*/
            //find the first multiple of PQ that is no less than MOD
            if (PQ * MCD <= MOD) {first_multiple_of_PQ_that_is_no_more_than_MOD = PQ * (MOD / PQ);}

            if (first_multiple_of_PQ_that_is_no_more_than_MOD == 0) {
                if (P + Q - 1 < N) {//IM NOT ENTIRELY SURE M.C.D. IN THE END OF THIS PART IS CORRECT.
                    int part_1 = N / (P + Q - 1), part_2 = N % (P + Q - 1);

                    //calculate offset using part_1
                    mod = PQ % MOD;

                    /*this "larger, smaller...offset = " part will probably only work
                    when 1, both larger & smaller are way smaller than MOD, 2, (larger * smaller) is roughly of the same order as MOD
                    or it will fail miserably, causing overflow (compared to MOD) kind of trouble*/
                    int larger, smaller;
                    if (mod > part_1) {larger = mod, smaller = part_1;}
                    else {larger = part_1, smaller = mod;}

                    int smaller_part_1 = MOD / smaller;
                    int smaller_part_2 = MOD % smaller;

                    /*larger * smaller =
                    fraction_of_larger * smaller
                     + (close_to_MODs * smaller + smaller_part_2 * whatever_that_is)//this line is multiplies of MOD
                     - smaller_part_2 * whatever_that_is;

                    =
                    (larger % smaller_part_1) * smaller
                     + (smaller_part_1 * (larger / smaller_part_1) * smaller + smaller_part_2 * (larger / smaller_part_1))//this line is multiplies of MOD
                     - smaller_part_2 * (larger / smaller_part_1);*/

                    offset = (larger % smaller_part_1) * smaller - smaller_part_2 * (larger / smaller_part_1);
                    offset = offset % MOD;

                    //find the part_2-th number
                    left = 0, right = PQ, mid = (left + right) / 2;
                    while (left < right) {
                        count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                        mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                        if ((count_A + count_B - count_AB == part_2)&&(mod_A == 0)&&(mod_B == 0)) {
                            left = mid;
                            break;
                        }

                        if (count_A + count_B - count_AB >= part_2) {right = mid;}

                        else {left = mid + 1;}

                        mid = (left + right) / 2;
                    }

                    result = ((left + offset)* MCD) % MOD;
                    if (result < 0) {result += MOD;}
                }

                else if (P + Q - 1 > N) {//easy~, the same as criteria >= N
                    left = MOD, right = PQ, mid = (left + right) / 2;
                    while (left < right) {
                        count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                        mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                        if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                            left = mid;
                            break;
                        }

                        if (count_A + count_B - count_AB >= N) {right = mid;}

                        else {left = mid + 1;}

                        mid = (left + right) / 2;
                    }

                    result = (left * MCD) % MOD;
                }

                else if (P + Q - 1 == N) {//easiest~
                    result = (PQ * MCD) % MOD;
                }
            }

            else {
                mod = MOD - first_multiple_of_PQ_that_is_no_more_than_MOD;

                /*what we have here, is:
                1. a big negative sum which is probably larger than MOD
                2. remaining N

                what we gonna do here is:
                1. find how many (P + Q - 1) be within N
                2. add *that many PQ* to that big negative sum (thus make it closer to 0), while remaining N become (*remaining N*) % PQ
                3. find that (remaining N)-th number in range 1 to PQ
                4. add this (remaining N)-th number to that smaller negative sum, then find its 1st positive module relative to MOD
                */

                int remaining_N = N - ((MOD / PQ)*(P + Q - 1))*(N / ((MOD / PQ)*(P + Q - 1)));

                int how_many_PQ_within = remaining_N / (P + Q - 1);
                remaining_N %= (P + Q - 1);

                //first_part < PQ
                int first_part = mod;
                int second_part = (N / ((MOD / PQ)*(P + Q - 1)));

                //that big sum is NEGATIVE first_part * second_part
                //the big sum now becomes NEGATIVE (first_part * second_part) -
                /*
                J = PQ - first_part
                ? = second_part - PQ

                (first_part * second_part) = (PQ - J) * (PQ + ?) = PQ (PQ - J + ?) - J * ?

                so, (first_part * second_part) is practically

                (PQ - J + ?) = (-J + second_part) = (second_part - PQ + first_part) times PQ

                - J * (second_part - PQ) = - (PQ - first_part) * (second_part - PQ)
                */

                left = 0, right = PQ, mid = (left + right) / 2;
                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == remaining_N)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= remaining_N) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                //now calculate POSITIVE
                //((how_many_PQ_within * PQ) - (first_part * second_part) + left) % MOD
                //while trying to make it positive

                /*
                (how_many_PQ_within * PQ) - (first_part * second_part) + left
                (how_many_PQ_within * PQ) - ((second_part - PQ + first_part) * PQ - (PQ - first_part) * (second_part - PQ)) + left
                (how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left
                */

                if (test_timer >= 0) {
                    cout << "that big offset = " << ((how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) << "\n";
                    cout << "left = " << left << "\n";
                }

                result = ((how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left;
                result *= MCD;
                result %= MOD;
                if (result < 0) {result += MOD;}
            }
        }

        else {
            left = 1, right = MOD, mid = (left + right) / 2;

            if (test_timer >= 0) {cout << "N = " << N << "\n\n";}

            while (left < right) {
                count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                    left = mid;
                    break;
                }

                if (count_A + count_B - count_AB >= N) {right = mid;}

                else {left = mid + 1;}

                mid = (left + right) / 2;

                if (test_timer >= 0) {
                    cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                    cout << "count_A = " << count_A << ", count_B = " << count_B << ", count_AB = " << count_AB << "\n\n";
                    test_timer++;
                }
                //if (test_timer >= 30) {break;}
            }

            result = (left * MCD) % MOD;
        }
    }
    return result;
}



//generally correct, but, those recursive overflow problems!!!
int nthMagicalNumber_those_annoying_overflows(int N, int A, int B) {
    int result = 0, MOD = 1000000, test_timer = -1;
    long long int offset = 0, offset_part_1 = 0, offset_part_2 = 0;//, offset_part_3 = 0
    int first, second, a, b, c, d, temp0, temp1;//these 1st 2nd stuff are merely temp numbers

    //cout << "N = " << N << ", A = " << A << ", B = " << B << "\n\n";
    if (test_timer >= 0) {cout << "N = " << N << ", A = " << A << ", B = " << B << "\n\n";}

    if (A == B) {
        int how_many_A_in_MOD = MOD / A;
        int remaining_N = N - (N / how_many_A_in_MOD) * how_many_A_in_MOD;

        /*we need to calculate (N / how_many_A_in_MOD) * (MOD - (how_many_A_in_MOD * A)) % MOD
        rename it -> (first * second)
        it equals to -> (A * (first / A) + first % A) * (A * (second / A) + second % A)
        A*((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A)) + (first%A) * (second%A)
        */

        first = N / how_many_A_in_MOD, second = MOD - (how_many_A_in_MOD * A);

        a = first / A, b = first % A, c = second / A, d = second % A;

        remaining_N -= a * c + b * c + a * d;
        if (remaining_N > MOD) {remaining_N %= MOD;}

        offset = b * d;

        result = (remaining_N * A - offset) % MOD;
        if (result < 0) {result += MOD;}
    }

    else {
        int remaining_N = 0, mod;

        //greatest common divisor, least common multiple,
        int GCD, LCM, P, Q, PQ;
        int count_P, mod_P, count_Q, mod_Q, count_PQ;

        //find GCD bc GCD will wreck the whole thing, deal with P & Q instead (with A = P * GCD, B = Q * GCD)
        first = A, second = B;
        while ((first > 0)&&(second > 0)) {
            if (first > second) {first %= second;}
            else {second %= first;}
        }
        GCD = (first > 0)? first: second;
        P = A / GCD, Q = B / GCD, PQ = P * Q;
        LCM = PQ * GCD;

        if (test_timer >= 0) {cout << "GCD = " << GCD << ", LCM = " << LCM << "\n\n";}

        //P plus Q minus 1
        int P_p_Q_m_1 = P + Q - 1;//note that PQ is the (P + Q - 1)-th smallest number

        //more helpers
        int left, right, mid;
        int MOD_d_A = MOD / A, MOD_d_B = MOD / B;
        int MOD_d_P = MOD / P, MOD_d_Q = MOD / Q, MOD_d_LCM = MOD / LCM;

        //how many so called magical number within MOD
        int criteria = MOD_d_A + MOD_d_B - MOD_d_LCM;

        //determine base & offset of result
        if (criteria < N) {
            if (test_timer >= 0) {cout << "criteria < N\n\n";}

            int MOD_d_LCM = MOD / LCM;
            int largest_AB_multi_no_more_than_MOD = 0, how_many_AB_multi_in_MOD = 0;
            if (LCM <= MOD) {
                largest_AB_multi_no_more_than_MOD = LCM * MOD_d_LCM;

                //note that, in one LCM, there are in total (P + Q - 1) multiples of P-multiple or Q-multiple
                how_many_AB_multi_in_MOD = MOD_d_LCM * P_p_Q_m_1;
            }

            if (test_timer >= 0) {
                cout << "largest_AB_multi_no_more_than_MOD = ";
                cout << largest_AB_multi_no_more_than_MOD << "\n\n";
            }

            if (largest_AB_multi_no_more_than_MOD == 0) {//LCM > MOD
                if (test_timer >= 0) {cout << "LCM > MOD\n\n";}

                if (P_p_Q_m_1 < N) {//IM NOT ENTIRELY SURE M.C.D. IN THE END OF THIS PART IS CORRECT.
                    if (test_timer >= 0) {cout << "P + Q - 1 < N\n\n";}

                    left = 0, right = PQ;
                    //we have to find the remaining_N-th one
                    //remaining_N = N % (P + Q - 1);
                    remaining_N = N % P_p_Q_m_1;
                    mod = LCM % MOD;

                    if (test_timer >= 0) {cout << "remaining_N = " << remaining_N << "\n\n";}

                    int how_many_LCM_in_N = N / (P + Q - 1);

                    /*calculate offset = (mod * how_many_LCM_in_N) % MOD
                    //where, (mod < MOD), (how_many_LCM_in_N < MOD), while (mod * how_many_LCM_in_N) is likely to be larger than MOD*/

                    if (mod >= how_many_LCM_in_N) {a = mod, b = how_many_LCM_in_N;}
                    else {a = how_many_LCM_in_N, b = mod;}
                    c = MOD / a, d = MOD % a;

                    //offset = a * (b % c) - d * (b / c);

                    offset_part_1 = b % c;
                    if (((a != 0)&&(MOD / a < offset_part_1))||((offset_part_1 != 0)&&(MOD / offset_part_1 < a))) {
                        if (offset_part_1 >= a) {first = offset_part_1, second = a;}
                        else {first = a, second = offset_part_1;}
                        temp0 = MOD / first, temp1 = MOD % first;
                        offset_part_1 = first * (second % temp0) - temp1 * (second / temp0);
                    }
                    else {offset_part_1 *= a;}
                    offset_part_1 %= MOD;

                    if (test_timer >= 0) {cout << "offset_part_1 = " << offset_part_1 << "\n\n";}

                    offset_part_2 = b / c;
                    if (((d != 0)&&(MOD / d < offset_part_2))||((offset_part_2 != 0)&&(MOD / offset_part_2 < d))) {
                        if (offset_part_2 >= d) {first = offset_part_2, second = d;}
                        else {first = d, second = offset_part_2;}
                        temp0 = MOD / first, temp1 = MOD % first;
                        offset_part_2 = first * (second % temp0) - temp1 * (second / temp0);
                    }
                    else {offset_part_2 *= d;}
                    offset_part_2 %= MOD;

                    if (test_timer >= 0) {cout << "offset_part_2 = " << offset_part_2 << "\n\n";}

                    offset = offset_part_1 + offset_part_2;

                    /*if (test_timer >= 0) {
                        if (((a != 0)&&(MOD / a < (b % c)))||(((b % c) != 0)&&(MOD / (b % c) < a))) {
                            cout << "overflow danger in a * (b % c)!\n";
                            cout << "a = " << a << ", (b % c) = " << (b % c) << "\n\n";
                        }

                        if (((d != 0)&&(MOD / d < a))||((a != 0)&&(MOD / a < d))) {
                            cout << "overflow danger in MOD % a!\n";
                            cout << "d = " << d << ", (b / c) = " << (b / c) << "\n\n";
                        }
                    }*/

                    if (test_timer >= 0) {cout << "offset = " << offset << "\n\n";}
                }

                else if (P_p_Q_m_1 > N) {//easy~, the same as criteria >= N, just find the N-th one, no explanation needed
                    if (test_timer >= 0) {cout << "P + Q - 1 > N\n\n";}
                    left = 1, right = PQ, remaining_N = N;
                }

                else if (P_p_Q_m_1 == N) {//the N-th one is just LCM
                    if (test_timer >= 0) {cout << "P + Q - 1 == N\n\n";}
                    left = PQ, right = 0;
                    //result = LCM % MOD;
                }
            }

            /*EXPLANATION:
            after removing big part, which is "largest_AB_multi_no_more_than_MOD * (N / how_many_AB_multi_in_MOD)",

            what we have to deal with here, is:
            1. a "big negative sum" (because we've removed a big chunk multiples of MOD),
               "- mod * (N / how_many_AB_multi_in_MOD)",
               which may be got abs() larger than MOD;
            2. remaining_N;

            what we gonna do here is:
            1. find how many (P + Q - 1) be within remaining_N;

            2.1. add *that many* LCM to that "big negative sum" (thus make abs("big negative sum") smaller),
                this will be the OFFSET;

            2.2. remaining_N become (remaining_N % (P + Q - 1)), with smaller abs() too;

            (below will be done at the end of this function)
            3. find (remaining_N)-th number in range 1 to LCM;

            4. add (remaining N)-th number to offset, then find its 1st positive module relative to MOD*/
            else {//remember that in this case, GCD <= LCM <= MOD
                if (test_timer >= 0) {cout << "LCM <= MOD\n\n";}

                //later code will bring this *left* into the mix
                left = 0, right = PQ;

                mod = MOD - largest_AB_multi_no_more_than_MOD;
                int how_many_MOD_in_N = N / how_many_AB_multi_in_MOD;

                if (test_timer >= 0) {cout << "how_many_MOD_in_N = " << how_many_MOD_in_N << "\n\n";}

                remaining_N = N - how_many_AB_multi_in_MOD * how_many_MOD_in_N;
                if (test_timer >= 0) {
                    cout << "how_many_AB_multi_in_MOD = " << how_many_AB_multi_in_MOD << "\n";
                    cout << "mod = " << mod << "\n";
                    cout << "remaining_N = " << remaining_N << "\n\n";
                }

                //1.
                int how_many_AB_multi_in_remaining_N = remaining_N / P_p_Q_m_1;

                //2.2.
                remaining_N %= P_p_Q_m_1;

                //QUESTIONABLE
                //if (remaining_N == 0) {remaining_N += P_p_Q_m_1;}

                if (remaining_N >= 0) {
                    if (test_timer >= 0) {
                        cout << "how_many_AB_multi_in_remaining_N = " << how_many_AB_multi_in_remaining_N;
                        cout << "\nremaining_N = " << remaining_N << "\n\n";
                    }

                    //2.1. also note that "first_part < LCM"
                    first = mod, second = how_many_MOD_in_N;
                    if (test_timer >= 0) {cout << "first = " << first << ", second = " << second << "\n\n";}

                    //what we want, is "- (mod * how_many_MOD_in_N) + how_many_AB_multi_in_remaining_N * LCM"

                    /*deal with (mod * how_many_MOD_in_N) = [- (first * second)] *NEGATIVE!*

                    note that *NEGATIVE* sign temporarily ignored!
                    & = LCM - first, ? = second - LCM
                    (first * second) -> (LCM - &) * (LCM + ?) -> LCM * (LCM - & + ?) - & * ?
                    (LCM - & + ?) -> (second - &) -> (second - LCM + first)
                     - & * ? -> - & * (second - LCM) -> - (LCM - first) * (second - LCM)

                    take that *NEGATIVE!* into the fold:
                    1. there are "- (second - LCM + first)" copies of LCM in that sum,
                       note that we HAVE NOT added (how_many_AB_multi_in_remaining_N * LCM)!
                    2. with module "(LCM - first) * (second - LCM)"

                    part 1 of the offset = (how_many_AB_multi_in_remaining_N - (second - LCM + first))
                    part 1 of the offset *= LCM
                    part 2 of the offset = (LCM - first) * (second - LCM)

                    offset = part 1 of the offset + part 2 of the offset
                    */

                    //offset
                    /*if (MOD / mod >= how_many_MOD_in_N) {offset = how_many_AB_multi_in_remaining_N * LCM - mod * how_many_MOD_in_N;}*/

                    //offset_part_1 = (how_many_AB_multi_in_remaining_N - (second - LCM + first)) * LCM
                    offset_part_1 = how_many_AB_multi_in_remaining_N - (second - LCM + first);
                    if (test_timer >= 0) {cout << "offset_part_1 = " << offset_part_1 << "\n";}
                    if (offset_part_1 >= MOD) {offset_part_1 %= MOD;}
                    if (((offset_part_1 != 0)&&(MOD / offset_part_1 < LCM))||((LCM != 0)&&(MOD / LCM < offset_part_1))) {
                        if (test_timer >= 0) {cout << "offset_part_1 went into more complex route.\n";}
                        /*we need (offset_part_1 * LCM) % MOD, which is larger than MOD

                        THIS MADE ME WONDER IF I SHOULD CHANGE CODE LINES ABOVE
                        CHECK AGAIN LATER

                        first < MOD, second < MOD, first * second > MOD
                        assuming (first >= second)

                        (first * second) % MOD

                        MOD / first, MOD % first
                        MOD = first * (MOD / first) + (MOD % first)

                        because (first * second) > MOD, second will be larger than (MOD / first)

                        second = (MOD / first) * (second / (MOD / first)) + second % (MOD / first)

                        first * ((MOD / first) * (second / (MOD / first)) + second % (MOD / first))

                        first * (MOD / first) * (second / (MOD / first)) --- not smaller or even way larger than MOD
                         + first * (second % (MOD / first)) --- presumably way smaller than MOD

                        first * (MOD / first) * (second / (MOD / first))
                        -> (MOD - (MOD % first)) * (second / (MOD / first))
                        removing (second / (MOD / first)) multiples of MOD
                        -> - (MOD % first) * (second / (MOD / first))

                        desired value = first * (second % (MOD / first)) - (MOD % first) * (second / (MOD / first))
                        */
                        if (offset_part_1 >= LCM) {a = offset_part_1, b = LCM;}
                        else {a = LCM, b = offset_part_1;}
                        c = MOD / a, d = MOD % a;
                        offset_part_1 = a * (b % c) - d * (b / c);
                    }
                    else {offset_part_1 *= LCM;}
                    offset_part_1 %= MOD;

                    if (test_timer >= 0) {cout << "offset_part_1 = " << offset_part_1 << "\n";}

                    //offset_part_2 = (LCM - first) * (second - LCM);
                    offset_part_2 = (LCM - first);
                    if (test_timer >= 0) {cout << "offset_part_2 = " << offset_part_2 << "\n";}
                    if (((offset_part_2 != 0)&&(MOD / offset_part_2 < second - LCM))||((second - LCM != 0)&&(MOD / (second - LCM) < offset_part_2))) {
                        if (test_timer >= 0) {cout << "offset_part_2 went into more complex route.\n";}
                        if (offset_part_2 >= second - LCM) {a = offset_part_2, b = second - LCM;}
                        else {a = second - LCM, b = offset_part_2;}
                        c = MOD / a, d = MOD % a;
                        offset_part_2 = a * (b % c) - d * (b / c);
                    }
                    else {offset_part_2 *= (second - LCM);}
                    offset_part_2 %= MOD;

                    if (test_timer >= 0) {cout << "offset_part_2 = " << offset_part_2 << "\n";}

                    //now im quite confident that offset will not overflow
                    offset = offset_part_1 + offset_part_2;
                    offset %= MOD;

                    if (test_timer >= 0) {cout << "that big offset = " << offset << "\n";}
                }

                /*else {//what we want is (how_many_AB_multi_in_remaining_N * LCM) - mod * how_many_MOD_in_N

                }*/
            }
        }

        //just find the N-th one, no explanation needed
        else {left = 1, right = MOD, remaining_N = N;}

        if (test_timer >= 0) {cout << "left = " << left << "\n";}

        //QUESTIONABLE
        if ((remaining_N == 0)&&(P_p_Q_m_1 != N)) {left = 0;}

        else {
            mid = (left + right) / 2;
            while (left < right) {
                count_P = mid / P, count_Q = mid / Q, count_PQ = mid / PQ;
                mod_P = mid - P * count_P, mod_Q = mid - Q * count_Q;

                if ((count_P + count_Q - count_PQ == remaining_N)&&(mod_P == 0)&&(mod_Q == 0)) {
                    left = mid;
                    break;
                }

                if (count_P + count_Q - count_PQ >= remaining_N) {right = mid;}

                else {left = mid + 1;}

                mid = (left + right) / 2;
            }
        }

        //result = (left * GCD + offset) % MOD;

        if (test_timer >= 0) {cout << "left = " << left << "\noffset = " << offset << "\n";}

        if (abs(left) >= MOD) {left %= MOD;}
        result = left;
        if (abs(offset) >= MOD) {offset %= MOD;}

        if ((left > 0)&&(((left < MOD)&&(MOD / left < GCD))||((GCD < MOD)&&(MOD / GCD < left)))) {
            if (left >= GCD) {a = left, b = GCD;}
            else {a = GCD, b = left;}
            c = MOD / a, d = MOD % a;

            /*if (test_timer >= 0) {
                cout << "a = " << a << ", b = " << b << "\n";
                cout << "c = " << c << ", d = " << d << "\n";
            }*/

            result = a * (b % c) - d * (b / c);
        }
        else {result = left * GCD;}

        if (result >= MOD) {result %= MOD;}
        result += offset;
        result %= MOD;
        if (result < 0) {result += MOD;}
    }

    return result;
}



//This one works
//rearrange the original chaotic thing into a less chaotic one
//by Nova Introvert

/*in multiple scenarios we need to find out (first * second) % MOD,
with (first < MOD)&&(second < MOD)&&(first * second > MOD)
while making sure in the whole process there is NO OVERFLOW

assuming (first >= second)

(first * second) % MOD

MOD / first, MOD % first
MOD = first * (MOD / first) + (MOD % first)

because (first * second) > MOD, second will be larger than (MOD / first)

second = (MOD / first) * (second / (MOD / first)) + second % (MOD / first)

first * ((MOD / first) * (second / (MOD / first)) + second % (MOD / first))

first * (MOD / first) * (second / (MOD / first)) --- not smaller or even way larger than MOD
 + first * (second % (MOD / first)) --- presumably way smaller than MOD

first * (MOD / first) * (second / (MOD / first))
-> (MOD - (MOD % first)) * (second / (MOD / first))
removing MOD
-> - (MOD % first) * (second / (MOD / first))

desired value = first * (second % (MOD / first)) - (MOD % first) * (second / (MOD / first))

CODE:
if (first >= second) {a = first, b = second;}
else {a = second, b = first;}
c = MOD / a, d = MOD % a;
desired value = (first * second) % MOD = a * (b % c) - d * (b / c);

*/

int product_mod_MOD (int first, int second, int MOD) {
    int part_1, part_2, a, b, c, d, e, f;
    if (first >= second) {a = first, b = second;}
    else {a = second, b = first;}

    c = MOD / a, d = MOD % a;
    e = b % c, f = b / c;
    //result = (first * second) % MOD = a * (b % c) - d * (b / c) = a * e - d * f;

    if (((a != 0)&&(abs(MOD / a) < e))||((e != 0)&&(abs(MOD / e) < a))) {
        part_1 = product_mod_MOD(a, e, MOD);
    }
    else {part_1 = a * e;}

    if (((d != 0)&&(abs(MOD / d) < f))||((f != 0)&&(abs(MOD / f) < d))) {
        part_2 = product_mod_MOD(d, f, MOD);
    }
    else {part_2 = d * f;}

    return (part_1 - part_2) % MOD;
}

int nthMagicalNumber_totally_works(int N, int A, int B) {
    int result = 0, MOD = 1000000007, test_timer = -1;
    int offset = 0, offset_part_1 = 0, offset_part_2 = 0;//, offset_part_3 = 0
    int first, second, a, b, c, d, e, f;//these 1st 2nd stuff are merely temp numbers

    //cout << "N = " << N << ", A = " << A << ", B = " << B << "\n\n";
    if (test_timer >= 0) {cout << "N = " << N << ", A = " << A << ", B = " << B << "\n\n";}

    if (A == B) {
        int how_many_A_in_MOD = MOD / A;
        int remaining_N = N - (N / how_many_A_in_MOD) * how_many_A_in_MOD;

        /*we need to calculate (N / how_many_A_in_MOD) * (MOD - (how_many_A_in_MOD * A)) % MOD
        rename it -> (first * second)
        it equals to -> (A * (first / A) + first % A) * (A * (second / A) + second % A)
        A*((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A)) + (first%A) * (second%A)
        */

        first = N / how_many_A_in_MOD, second = MOD - (how_many_A_in_MOD * A);

        a = first / A, b = first % A, c = second / A, d = second % A;

        remaining_N -= a * c + b * c + a * d;
        if (remaining_N > MOD) {remaining_N %= MOD;}

        offset = b * d;

        result = (remaining_N * A - offset) % MOD;
        if (result < 0) {result += MOD;}
    }

    else {
        int remaining_N = 0, mod;

        //greatest common divisor, least common multiple,
        int GCD, LCM, P, Q, PQ;
        int count_P, mod_P, count_Q, mod_Q, count_PQ;

        //find GCD bc GCD will wreck the whole thing, deal with P & Q instead (with A = P * GCD, B = Q * GCD)
        first = A, second = B;
        while ((first > 0)&&(second > 0)) {
            if (first > second) {first %= second;}
            else {second %= first;}
        }
        GCD = (first > 0)? first: second;
        P = A / GCD, Q = B / GCD, PQ = P * Q;
        LCM = PQ * GCD;

        if (test_timer >= 0) {cout << "GCD = " << GCD << ", LCM = " << LCM << ", P = " << P << ", Q = " << Q << ", PQ = " << PQ << "\n\n";}

        //P plus Q minus 1
        int P_p_Q_m_1 = P + Q - 1;//note that PQ is the (P + Q - 1)-th smallest number

        //more helpers
        long long int left, right, mid;//if not long long, in P = 35048, Q = 36489, N = 999999000, left will overflow, causing deadlock
        int MOD_d_A = MOD / A, MOD_d_B = MOD / B;
        int MOD_d_P = MOD / P, MOD_d_Q = MOD / Q, MOD_d_LCM = MOD / LCM;

        //how many so called magical number within MOD
        int criteria = MOD_d_A + MOD_d_B - MOD_d_LCM;

        //determine base & offset of result
        if (criteria < N) {
            if (test_timer >= 0) {cout << "criteria < N\n\n";}

            int MOD_d_LCM = MOD / LCM;
            int largest_AB_multi_no_more_than_MOD = 0, how_many_AB_multi_in_MOD = 0;
            if (LCM <= MOD) {
                largest_AB_multi_no_more_than_MOD = LCM * MOD_d_LCM;

                //note that, in one LCM, there are in total (P + Q - 1) multiples of P-multiple or Q-multiple
                how_many_AB_multi_in_MOD = MOD_d_LCM * P_p_Q_m_1;
            }

            if (test_timer >= 0) {
                cout << "largest_AB_multi_no_more_than_MOD = ";
                cout << largest_AB_multi_no_more_than_MOD << "\n\n";
            }

            if (largest_AB_multi_no_more_than_MOD == 0) {//LCM > MOD
                if (test_timer >= 0) {cout << "LCM > MOD\n\n";}

                if (P_p_Q_m_1 < N) {//IM NOT ENTIRELY SURE M.C.D. IN THE END OF THIS PART IS CORRECT.
                    if (test_timer >= 0) {cout << "P + Q - 1 < N\n\n";}

                    left = 0, right = PQ;
                    //we have to find the remaining_N-th one
                    //remaining_N = N % (P + Q - 1);
                    remaining_N = N % P_p_Q_m_1;//WARNING! remaining_N can still be out of range of
                    mod = LCM % MOD;

                    if (test_timer >= 0) {cout << "left = " << left << ", right = " << right << ", remaining_N = " << remaining_N << "\n\n";}

                    int how_many_LCM_in_N = N / (P + Q - 1);

                    //calculate offset = (mod * how_many_LCM_in_N) % MOD
                    //where, (mod < MOD), (how_many_LCM_in_N < MOD), while (mod * how_many_LCM_in_N) is likely to be larger than MOD

                    offset = product_mod_MOD(mod, how_many_LCM_in_N, MOD);

                    /*if (mod >= how_many_LCM_in_N) {a = mod, b = how_many_LCM_in_N;}
                    else {a = how_many_LCM_in_N, b = mod;}
                    c = MOD / a, d = MOD % a;
                    e = b % c, f = b / c;

                    //offset = a * (b % c) - d * (b / c) = a * e - d * f;

                    //offset_part_1 = product_mod_MOD(a, e, MOD);
                    offset_part_1 = b % c;
                    if (((a != 0)&&(MOD / a < offset_part_1))||((offset_part_1 != 0)&&(MOD / offset_part_1 < a))) {
                        if (offset_part_1 >= a) {first = offset_part_1, second = a;}
                        else {first = a, second = offset_part_1;}
                        temp0 = MOD / first, temp1 = MOD % first;
                        offset_part_1 = first * (second % temp0) - temp1 * (second / temp0);
                    }
                    else {offset_part_1 *= a;}
                    offset_part_1 %= MOD;

                    if (test_timer >= 0) {cout << "offset_part_1 = " << offset_part_1 << "\n\n";}

                    offset_part_2 = product_mod_MOD(d, e, MOD);
                    offset_part_2 = b / c;
                    if (((d != 0)&&(MOD / d < offset_part_2))||((offset_part_2 != 0)&&(MOD / offset_part_2 < d))) {
                        if (offset_part_2 >= d) {first = offset_part_2, second = d;}
                        else {first = d, second = offset_part_2;}
                        temp0 = MOD / first, temp1 = MOD % first;
                        offset_part_2 = first * (second % temp0) - temp1 * (second / temp0);
                    }
                    else {offset_part_2 *= d;}
                    offset_part_2 %= MOD;

                    if (test_timer >= 0) {cout << "offset_part_2 = " << offset_part_2 << "\n\n";}

                    offset = offset_part_1 + offset_part_2;*/

                    /*if (test_timer >= 0) {
                        if (((a != 0)&&(MOD / a < (b % c)))||(((b % c) != 0)&&(MOD / (b % c) < a))) {
                            cout << "overflow danger in a * (b % c)!\n";
                            cout << "a = " << a << ", (b % c) = " << (b % c) << "\n\n";
                        }

                        if (((d != 0)&&(MOD / d < a))||((a != 0)&&(MOD / a < d))) {
                            cout << "overflow danger in MOD % a!\n";
                            cout << "d = " << d << ", (b / c) = " << (b / c) << "\n\n";
                        }
                    }*/

                    if (test_timer >= 0) {cout << "offset = " << offset << "\n\n";}
                }

                else if (P_p_Q_m_1 > N) {//easy~, the same as criteria >= N, just find the N-th one, no explanation needed
                    if (test_timer >= 0) {cout << "P + Q - 1 > N\n\n";}
                    left = 1, right = PQ, remaining_N = N;
                }

                else if (P_p_Q_m_1 == N) {//the N-th one is just LCM
                    if (test_timer >= 0) {cout << "P + Q - 1 == N\n\n";}
                    left = PQ, right = 0;
                    //result = LCM % MOD;
                }
            }

            /*EXPLANATION:
            after removing big part, which is "largest_AB_multi_no_more_than_MOD * (N / how_many_AB_multi_in_MOD)",

            what we have to deal with here, is:
            1. a "big negative sum" (because we've removed a big chunk multiples of MOD),
               "- mod * (N / how_many_AB_multi_in_MOD)",
               which may be got abs() larger than MOD;
            2. remaining_N;

            what we gonna do here is:
            1. find how many (P + Q - 1) be within remaining_N;

            2.1. add *that many* LCM to that "big negative sum" (thus make abs("big negative sum") smaller),
                this will be the OFFSET;

            2.2. remaining_N become (remaining_N % (P + Q - 1)), with smaller abs() too;

            (below will be done at the end of this function)
            3. find (remaining_N)-th number in range 1 to LCM;

            4. add (remaining N)-th number to offset, then find its 1st positive module relative to MOD*/
            else {//remember that in this case, GCD <= LCM <= MOD
                if (test_timer >= 0) {cout << "LCM <= MOD\n\n";}

                //later code will bring this *left* into the mix
                left = 0, right = PQ;

                mod = MOD - largest_AB_multi_no_more_than_MOD;
                int how_many_MOD_in_N = N / how_many_AB_multi_in_MOD;

                if (test_timer >= 0) {cout << "how_many_MOD_in_N = " << how_many_MOD_in_N << "\n\n";}

                remaining_N = N - how_many_AB_multi_in_MOD * how_many_MOD_in_N;
                if (test_timer >= 0) {
                    cout << "how_many_AB_multi_in_MOD = " << how_many_AB_multi_in_MOD << "\n";
                    cout << "mod = " << mod << "\n";
                    cout << "remaining_N = " << remaining_N << "\n\n";
                }

                //1.
                int how_many_AB_multi_in_remaining_N = remaining_N / P_p_Q_m_1;

                //2.2.
                remaining_N %= P_p_Q_m_1;

                //QUESTIONABLE
                //if (remaining_N == 0) {remaining_N += P_p_Q_m_1;}

                if (remaining_N >= 0) {
                    if (test_timer >= 0) {
                        cout << "how_many_AB_multi_in_remaining_N = " << how_many_AB_multi_in_remaining_N;
                        cout << "\nremaining_N = " << remaining_N << "\n\n";
                    }

                    //2.1. also note that "first_part < LCM"
                    first = mod, second = how_many_MOD_in_N;
                    if (test_timer >= 0) {cout << "first = " << first << ", second = " << second << "\n\n";}

                    //what we want, is "- (mod * how_many_MOD_in_N) + how_many_AB_multi_in_remaining_N * LCM"

                    /*deal with (mod * how_many_MOD_in_N) = [- (first * second)] *NEGATIVE!*

                    note that *NEGATIVE* sign temporarily ignored!
                    & = LCM - first, ? = second - LCM
                    (first * second) -> (LCM - &) * (LCM + ?) -> LCM * (LCM - & + ?) - & * ?
                    (LCM - & + ?) -> (second - &) -> (second - LCM + first)
                     - & * ? -> - & * (second - LCM) -> - (LCM - first) * (second - LCM)

                    take that *NEGATIVE!* into the fold:
                    1. there are "- (second - LCM + first)" copies of LCM in that sum,
                       note that we HAVE NOT added (how_many_AB_multi_in_remaining_N * LCM)!
                    2. with module "(LCM - first) * (second - LCM)"

                    part 1 of the offset = (how_many_AB_multi_in_remaining_N - (second - LCM + first))
                    part 1 of the offset *= LCM
                    part 2 of the offset = (LCM - first) * (second - LCM)

                    offset = part 1 of the offset + part 2 of the offset
                    */

                    //offset_part_1 = (how_many_AB_multi_in_remaining_N - (second - LCM + first)) * LCM
                    offset_part_1 = product_mod_MOD(how_many_AB_multi_in_remaining_N - (second - LCM + first), LCM, MOD);
                    /*offset_part_1 = how_many_AB_multi_in_remaining_N - (second - LCM + first);
                    if (test_timer >= 0) {cout << "offset_part_1 = " << offset_part_1 << "\n";}
                    if (offset_part_1 >= MOD) {offset_part_1 %= MOD;}
                    if (((offset_part_1 != 0)&&(MOD / offset_part_1 < LCM))||((LCM != 0)&&(MOD / LCM < offset_part_1))) {
                        if (test_timer >= 0) {cout << "offset_part_1 went into more complex route.\n";}

                        if (offset_part_1 >= LCM) {a = offset_part_1, b = LCM;}
                        else {a = LCM, b = offset_part_1;}
                        c = MOD / a, d = MOD % a;
                        offset_part_1 = a * (b % c) - d * (b / c);
                    }
                    else {offset_part_1 *= LCM;}
                    offset_part_1 %= MOD;*/
                    if (test_timer >= 0) {cout << "offset_part_1 = " << offset_part_1 << "\n";}

                    //offset_part_2 = (LCM - first) * (second - LCM);
                    offset_part_2 = product_mod_MOD(LCM - first, second - LCM, MOD);
                    /*offset_part_2 = (LCM - first);
                    if (test_timer >= 0) {cout << "offset_part_2 = " << offset_part_2 << "\n";}
                    if (((offset_part_2 != 0)&&(MOD / offset_part_2 < second - LCM))||((second - LCM != 0)&&(MOD / (second - LCM) < offset_part_2))) {
                        if (test_timer >= 0) {cout << "offset_part_2 went into more complex route.\n";}
                        if (offset_part_2 >= second - LCM) {a = offset_part_2, b = second - LCM;}
                        else {a = second - LCM, b = offset_part_2;}
                        c = MOD / a, d = MOD % a;
                        offset_part_2 = a * (b % c) - d * (b / c);
                    }
                    else {offset_part_2 *= (second - LCM);}
                    offset_part_2 %= MOD;*/
                    if (test_timer >= 0) {cout << "offset_part_2 = " << offset_part_2 << "\n";}

                    //now im quite confident that offset will not overflow
                    offset = offset_part_1 + offset_part_2;
                    offset %= MOD;

                    if (test_timer >= 0) {cout << "that big offset = " << offset << "\n";}
                }
            }
        }

        //just find the N-th one, no explanation needed
        else {left = 1, right = MOD, remaining_N = N;}

        //QUESTIONABLE
        if ((remaining_N == 0)&&(P_p_Q_m_1 != N)) {left = 0;}

        else {
            if (test_timer >= 0) {cout << "remaining_N = " << remaining_N << "\n";}
            mid = (left + right) / 2;
            if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";}
            while (left < right) {

                count_P = mid / P, count_Q = mid / Q, count_PQ = mid / PQ;
                mod_P = mid - P * count_P, mod_Q = mid - Q * count_Q;

                if ((count_P + count_Q - count_PQ == remaining_N)&&(mod_P == 0)&&(mod_Q == 0)) {
                    left = mid;
                    break;
                }

                if (count_P + count_Q - count_PQ >= remaining_N) {right = mid;}

                else {left = mid + 1;}

                /*if (test_timer >= 0) {test_timer++;}
                if (test_timer >= 200) {
                    cout << "test_timer = " << test_timer << "\n";
                    cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                    cout << "count_P = " << count_P << ", count_Q = " << count_Q << ", count_PQ = " << count_PQ << "\n";
                    cout << "mid / P = " << mid / P << ", mid / Q = " << mid / Q << ", mid / PQ = " << mid / PQ << "\n";
                    cout << "mid - P * count_P = " << mid - P * count_P << ", mid - Q * count_Q = " << mid - Q * count_Q << "\n";
                    break;
                }*/

                mid = (left + right) / 2;
            }
        }

        //result = (left * GCD + offset) % MOD;

        if (test_timer >= 0) {cout << "left = " << left << "\noffset = " << offset << "\n";}

        if (abs(left) >= MOD) {left %= MOD;}

        result = product_mod_MOD(left, GCD, MOD);

        /*if ((left > 0)&&(((left < MOD)&&(MOD / left < GCD))||((GCD < MOD)&&(MOD / GCD < left)))) {
            if (left >= GCD) {a = left, b = GCD;}
            else {a = GCD, b = left;}
            c = MOD / a, d = MOD % a;

            result = a * (b % c) - d * (b / c);
        }
        else {result = left * GCD;}

        if (result >= MOD) {result %= MOD;}*/
        result += offset;
        result %= MOD;
        if (result < 0) {result += MOD;}
    }

    return result;
}


//quite content with this one. time to move on
//This one works, identical to previous one.
//rearrange the original chaotic thing into a less chaotic one
//by Nova Introvert

/*in multiple scenarios we need to find out (first * second) % MOD,
with (first < MOD)&&(second < MOD)&&(first * second > MOD)
while making sure in the whole process there is NO OVERFLOW

assuming (first >= second)

(first * second) % MOD

MOD / first, MOD % first
MOD = first * (MOD / first) + (MOD % first)

because (first * second) > MOD, second will be larger than (MOD / first)

second = (MOD / first) * (second / (MOD / first)) + second % (MOD / first)

first * ((MOD / first) * (second / (MOD / first)) + second % (MOD / first))

first * (MOD / first) * (second / (MOD / first)) --- not smaller or even way larger than MOD
 + first * (second % (MOD / first)) --- presumably way smaller than MOD

first * (MOD / first) * (second / (MOD / first))
-> (MOD - (MOD % first)) * (second / (MOD / first))
removing MOD
-> - (MOD % first) * (second / (MOD / first))

desired value = first * (second % (MOD / first)) - (MOD % first) * (second / (MOD / first))

CODE:
if (first >= second) {a = first, b = second;}
else {a = second, b = first;}
c = MOD / a, d = MOD % a;
desired value = (first * second) % MOD = a * (b % c) - d * (b / c);

*/


//works well, but we really do not need to make left, mid, right long long int, just do that mid = (left + right) / 2 operation in another way!
int nthMagicalNumber_with_long_long(int N, int A, int B) {
    int result = 0, remaining_N = 0, MOD = 1000000007;//, test_timer = -1;1000000007
    int offset = 0, offset_part_1 = 0, offset_part_2 = 0;
    int first, second, a, b, c, d, e, f;//these 1st 2nd stuff are merely temp numbers

    //cout << "N = " << N << ", A = " << A << ", B = " << B << "\n\n";
    //if (test_timer >= 0) {cout << "N = " << N << ", A = " << A << ", B = " << B << "\n\n";}

    if (A == B) {
        int how_many_A_in_MOD = MOD / A;

        first = N / how_many_A_in_MOD, second = MOD - (how_many_A_in_MOD * A);

        remaining_N = N - first * how_many_A_in_MOD;

        /*we need to calculate (N / how_many_A_in_MOD) * (MOD - (how_many_A_in_MOD * A)) % MOD
        rename it -> (first * second)
        it equals to -> (A * (first / A) + first % A) * (A * (second / A) + second % A)
        -> A * ((first / A) * (second / A) + (first % A) * (second / A) + (first / A) * (second % A)) + (first % A) * (second % A)
        */

        a = first / A, b = first % A, c = second / A, d = second % A;

        remaining_N -= a * c + b * c + a * d;

        if (remaining_N > MOD) {remaining_N %= MOD;}

        offset = b * d;

        result = (remaining_N * A - offset) % MOD;
        if (result < 0) {result += MOD;}
    }

    else {
        //greatest common divisor, least common multiple,
        int mod, GCD, LCM, P, Q, PQ;
        int count_P, mod_P, count_Q, mod_Q, count_PQ;

        //find GCD. otherwise GCD will wreck the whole thing, deal with P & Q instead (with A = P * GCD, B = Q * GCD)
        first = A, second = B;
        while ((first > 0)&&(second > 0)) {
            if (first > second) {first %= second;}
            else {second %= first;}
        }
        GCD = (first > 0)? first: second;
        P = A / GCD, Q = B / GCD, PQ = P * Q;
        LCM = PQ * GCD;

        //P plus Q minus 1
        int P_p_Q_m_1 = P + Q - 1;//note that PQ is the (P + Q - 1)-th smallest number

        //more helpers
        long long int left, right, mid;//if not long long, in P = 35048, Q = 36489, N = 999999000, left will overflow, causing deadlock
        int MOD_d_A = MOD / A, MOD_d_B = MOD / B, MOD_d_LCM = MOD / LCM;

        //how many so called "magical numbers" within MOD
        int criteria = MOD_d_A + MOD_d_B - MOD_d_LCM;

        //determine base & offset of result
        if (criteria < N) {
            int largest_AB_multi_no_more_than_MOD = 0, how_many_AB_multi_in_MOD = 0;
            if (LCM <= MOD) {
                largest_AB_multi_no_more_than_MOD = LCM * MOD_d_LCM;

                //note that, in one LCM, there are in total (P + Q - 1) multiples of P-multiple or Q-multiple
                how_many_AB_multi_in_MOD = MOD_d_LCM * P_p_Q_m_1;
            }

            if (largest_AB_multi_no_more_than_MOD == 0) {//LCM > MOD
                if (P_p_Q_m_1 < N) {
                    left = 0, right = PQ;
                    remaining_N = N % P_p_Q_m_1;//remaining_N = N % (P + Q - 1);
                    mod = LCM % MOD;

                    int how_many_LCM_in_N = N / P_p_Q_m_1;//N / (P + Q - 1)

                    /*calculate offset = (mod * how_many_LCM_in_N) % MOD
                    where, (mod < MOD), (how_many_LCM_in_N < MOD),
                    while (mod * how_many_LCM_in_N) is likely to be larger than MOD*/
                    offset = product_mod_MOD(mod, how_many_LCM_in_N, MOD);
                }

                else if (P_p_Q_m_1 > N) {//easy~, the same as criteria >= N, just find the N-th one, no explanation needed
                    left = 1, right = PQ, remaining_N = N;
                }

                else if (P_p_Q_m_1 == N) {//the N-th one is just LCM
                    left = PQ, right = 0;//remaining_N does not need to be changed, it will go straight to result = left * GCD
                }
            }

            /*EXPLANATION:
            after removing big part, which is "largest_AB_multi_no_more_than_MOD * (N / how_many_AB_multi_in_MOD)",

            what we have to deal with here, is:
            1. a "big negative sum" (because we've removed a big chunk multiples of MOD),
               "- mod * (N / how_many_AB_multi_in_MOD)",
               which may be got abs() larger than MOD;
            2. remaining_N;

            what we gonna do here is:
            1. find how many (P + Q - 1) be within remaining_N;

            2.1. add *that many* LCM to that "big negative sum" (thus make abs("big negative sum") smaller),
                this will be the OFFSET;

            2.2. remaining_N become (remaining_N % (P + Q - 1)), with smaller abs() too;

            (below will be done at the end of this function)
            3. find (remaining_N)-th number in range 1 to LCM;

            4. add (remaining N)-th number to offset, then find its 1st positive module relative to MOD*/
            else {//remember that in this case, GCD <= LCM <= MOD
                //later code will bring this *left* into the mix
                left = 0, right = PQ;

                mod = MOD - largest_AB_multi_no_more_than_MOD;
                int how_many_MOD_in_N = N / how_many_AB_multi_in_MOD;

                remaining_N = N - how_many_AB_multi_in_MOD * how_many_MOD_in_N;

                //1.
                int how_many_AB_multi_in_remaining_N = remaining_N / P_p_Q_m_1;

                //2.2.
                remaining_N %= P_p_Q_m_1;

                //QUESTIONABLE
                //if (remaining_N == 0) {remaining_N += P_p_Q_m_1;}

                if (remaining_N >= 0) {
                    //2.1. also note that "first_part < LCM"
                    first = mod, second = how_many_MOD_in_N;

                    /*what we want, is "- (mod * how_many_MOD_in_N) + how_many_AB_multi_in_remaining_N * LCM"

                    deal with (mod * how_many_MOD_in_N) = [- (first * second)] *NEGATIVE!*

                    note that *NEGATIVE* sign temporarily ignored!
                    & = LCM - first, ? = second - LCM
                    (first * second) -> (LCM - &) * (LCM + ?) -> LCM * (LCM - & + ?) - & * ?
                    (LCM - & + ?) -> (second - &) -> (second - LCM + first)
                     - & * ? -> - & * (second - LCM) -> - (LCM - first) * (second - LCM)

                    take that *NEGATIVE!* into the fold:
                    1. there are "- (second - LCM + first)" copies of LCM in that sum,
                       note that we HAVE NOT added (how_many_AB_multi_in_remaining_N * LCM)!
                    2. with module "(LCM - first) * (second - LCM)"

                    part 1 of the offset = (how_many_AB_multi_in_remaining_N - (second - LCM + first))
                    part 1 of the offset *= LCM
                    part 2 of the offset = (LCM - first) * (second - LCM)

                    offset = part 1 of the offset + part 2 of the offset
                    */

                    //offset_part_1 = (how_many_AB_multi_in_remaining_N - (second - LCM + first)) * LCM
                    offset_part_1 = product_mod_MOD(how_many_AB_multi_in_remaining_N - (second - LCM + first), LCM, MOD);

                    //offset_part_2 = (LCM - first) * (second - LCM);
                    offset_part_2 = product_mod_MOD(LCM - first, second - LCM, MOD);

                    //now im quite confident that offset will not overflow
                    offset = offset_part_1 + offset_part_2;
                    offset %= MOD;
                }
            }
        }

        //just find the N-th one, no explanation needed
        else {left = 1, right = MOD, remaining_N = N;}

        //QUESTIONABLE
        if ((remaining_N == 0)&&(P_p_Q_m_1 != N)) {left = 0;}

        else {
            mid = (left + right) / 2;
            while (left < right) {
                count_P = mid / P, count_Q = mid / Q, count_PQ = mid / PQ;
                mod_P = mid - P * count_P, mod_Q = mid - Q * count_Q;

                if ((count_P + count_Q - count_PQ == remaining_N)&&(mod_P == 0)&&(mod_Q == 0)) {
                    left = mid;
                    break;
                }

                if (count_P + count_Q - count_PQ >= remaining_N) {right = mid;}

                else {left = mid + 1;}

                mid = (left + right) / 2;
            }
        }

        //result = (left * GCD + offset) % MOD;

        if (abs(left) >= MOD) {left %= MOD;}

        result = product_mod_MOD(left, GCD, MOD);

        /*if ((left > 0)&&(((left < MOD)&&(MOD / left < GCD))||((GCD < MOD)&&(MOD / GCD < left)))) {
            if (left >= GCD) {a = left, b = GCD;}
            else {a = GCD, b = left;}
            c = MOD / a, d = MOD % a;

            result = a * (b % c) - d * (b / c);
        }
        else {result = left * GCD;}

        if (result >= MOD) {result %= MOD;}*/
        result += offset;
        result %= MOD;
        if (result < 0) {result += MOD;}
    }

    return result;
}

//compared to previous, ONLY changed:
//"long long int left, mid, right" to "int left, mid, right"
//mid = (left + right) / 2 into mid = left + (right - left) / 2 to avoid overflow
//NOT YET TESTED, but i think it will not cause problems
int nthMagicalNumber(int N, int A, int B) {
    int result = 0, remaining_N = 0, MOD = 1000000007;//, test_timer = -1;1000000007
    int offset = 0, offset_part_1 = 0, offset_part_2 = 0;
    int first, second, a, b, c, d, e, f;//these 1st 2nd stuff are merely temp numbers

    //cout << "N = " << N << ", A = " << A << ", B = " << B << "\n\n";
    //if (test_timer >= 0) {cout << "N = " << N << ", A = " << A << ", B = " << B << "\n\n";}

    if (A == B) {
        int how_many_A_in_MOD = MOD / A;

        first = N / how_many_A_in_MOD, second = MOD - (how_many_A_in_MOD * A);

        remaining_N = N - first * how_many_A_in_MOD;

        /*we need to calculate (N / how_many_A_in_MOD) * (MOD - (how_many_A_in_MOD * A)) % MOD
        rename it -> (first * second)
        it equals to -> (A * (first / A) + first % A) * (A * (second / A) + second % A)
        -> A * ((first / A) * (second / A) + (first % A) * (second / A) + (first / A) * (second % A)) + (first % A) * (second % A)
        */

        a = first / A, b = first % A, c = second / A, d = second % A;

        remaining_N -= a * c + b * c + a * d;

        if (remaining_N > MOD) {remaining_N %= MOD;}

        offset = b * d;

        result = (remaining_N * A - offset) % MOD;
        if (result < 0) {result += MOD;}
    }

    else {
        //greatest common divisor, least common multiple,
        int mod, GCD, LCM, P, Q, PQ;
        int count_P, mod_P, count_Q, mod_Q, count_PQ;

        //find GCD. otherwise GCD will wreck the whole thing, deal with P & Q instead (with A = P * GCD, B = Q * GCD)
        first = A, second = B;
        while ((first > 0)&&(second > 0)) {
            if (first > second) {first %= second;}
            else {second %= first;}
        }
        GCD = (first > 0)? first: second;
        P = A / GCD, Q = B / GCD, PQ = P * Q;
        LCM = PQ * GCD;

        //P plus Q minus 1
        int P_p_Q_m_1 = P + Q - 1;//note that PQ is the (P + Q - 1)-th smallest number

        //more helpers
        int left, right, mid;//if not long long, in P = 35048, Q = 36489, N = 999999000, left will overflow, causing deadlock
        int MOD_d_A = MOD / A, MOD_d_B = MOD / B, MOD_d_LCM = MOD / LCM;

        //how many so called "magical numbers" within MOD
        int criteria = MOD_d_A + MOD_d_B - MOD_d_LCM;

        //determine base & offset of result
        if (criteria < N) {
            int largest_AB_multi_no_more_than_MOD = 0, how_many_AB_multi_in_MOD = 0;
            if (LCM <= MOD) {
                largest_AB_multi_no_more_than_MOD = LCM * MOD_d_LCM;

                //note that, in one LCM, there are in total (P + Q - 1) multiples of P-multiple or Q-multiple
                how_many_AB_multi_in_MOD = MOD_d_LCM * P_p_Q_m_1;
            }

            if (largest_AB_multi_no_more_than_MOD == 0) {//LCM > MOD
                if (P_p_Q_m_1 < N) {
                    left = 0, right = PQ;
                    remaining_N = N % P_p_Q_m_1;//remaining_N = N % (P + Q - 1);
                    mod = LCM % MOD;

                    int how_many_LCM_in_N = N / P_p_Q_m_1;//N / (P + Q - 1)

                    /*calculate offset = (mod * how_many_LCM_in_N) % MOD
                    where, (mod < MOD), (how_many_LCM_in_N < MOD),
                    while (mod * how_many_LCM_in_N) is likely to be larger than MOD*/
                    offset = product_mod_MOD(mod, how_many_LCM_in_N, MOD);
                }

                else if (P_p_Q_m_1 > N) {//easy~, the same as criteria >= N, just find the N-th one, no explanation needed
                    left = 1, right = PQ, remaining_N = N;
                }

                else if (P_p_Q_m_1 == N) {//the N-th one is just LCM
                    left = PQ, right = 0;//remaining_N does not need to be changed, it will go straight to result = left * GCD
                }
            }

            /*EXPLANATION:
            after removing big part, which is "largest_AB_multi_no_more_than_MOD * (N / how_many_AB_multi_in_MOD)",

            what we have to deal with here, is:
            1. a "big negative sum" (because we've removed a big chunk multiples of MOD),
               "- mod * (N / how_many_AB_multi_in_MOD)",
               which may be got abs() larger than MOD;
            2. remaining_N;

            what we gonna do here is:
            1. find how many (P + Q - 1) be within remaining_N;

            2.1. add *that many* LCM to that "big negative sum" (thus make abs("big negative sum") smaller),
                this will be the OFFSET;

            2.2. remaining_N become (remaining_N % (P + Q - 1)), with smaller abs() too;

            (below will be done at the end of this function)
            3. find (remaining_N)-th number in range 1 to LCM;

            4. add (remaining N)-th number to offset, then find its 1st positive module relative to MOD*/
            else {//remember that in this case, GCD <= LCM <= MOD
                //later code will bring this *left* into the mix
                left = 0, right = PQ;

                mod = MOD - largest_AB_multi_no_more_than_MOD;
                int how_many_MOD_in_N = N / how_many_AB_multi_in_MOD;

                remaining_N = N - how_many_AB_multi_in_MOD * how_many_MOD_in_N;

                //1.
                int how_many_AB_multi_in_remaining_N = remaining_N / P_p_Q_m_1;

                //2.2.
                remaining_N %= P_p_Q_m_1;

                //QUESTIONABLE
                //if (remaining_N == 0) {remaining_N += P_p_Q_m_1;}

                if (remaining_N >= 0) {
                    //2.1. also note that "first_part < LCM"
                    first = mod, second = how_many_MOD_in_N;

                    /*what we want, is "- (mod * how_many_MOD_in_N) + how_many_AB_multi_in_remaining_N * LCM"

                    deal with (mod * how_many_MOD_in_N) = [- (first * second)] *NEGATIVE!*

                    note that *NEGATIVE* sign temporarily ignored!
                    & = LCM - first, ? = second - LCM
                    (first * second) -> (LCM - &) * (LCM + ?) -> LCM * (LCM - & + ?) - & * ?
                    (LCM - & + ?) -> (second - &) -> (second - LCM + first)
                     - & * ? -> - & * (second - LCM) -> - (LCM - first) * (second - LCM)

                    take that *NEGATIVE!* into the fold:
                    1. there are "- (second - LCM + first)" copies of LCM in that sum,
                       note that we HAVE NOT added (how_many_AB_multi_in_remaining_N * LCM)!
                    2. with module "(LCM - first) * (second - LCM)"

                    part 1 of the offset = (how_many_AB_multi_in_remaining_N - (second - LCM + first))
                    part 1 of the offset *= LCM
                    part 2 of the offset = (LCM - first) * (second - LCM)

                    offset = part 1 of the offset + part 2 of the offset
                    */

                    //offset_part_1 = (how_many_AB_multi_in_remaining_N - (second - LCM + first)) * LCM
                    offset_part_1 = product_mod_MOD(how_many_AB_multi_in_remaining_N - (second - LCM + first), LCM, MOD);

                    //offset_part_2 = (LCM - first) * (second - LCM);
                    offset_part_2 = product_mod_MOD(LCM - first, second - LCM, MOD);

                    //now im quite confident that offset will not overflow
                    offset = offset_part_1 + offset_part_2;
                    offset %= MOD;
                }
            }
        }

        //just find the N-th one, no explanation needed
        else {left = 1, right = MOD, remaining_N = N;}

        //QUESTIONABLE
        if ((remaining_N == 0)&&(P_p_Q_m_1 != N)) {left = 0;}

        else {
            mid = left + (right - left) / 2;
            while (left < right) {
                count_P = mid / P, count_Q = mid / Q, count_PQ = mid / PQ;
                mod_P = mid - P * count_P, mod_Q = mid - Q * count_Q;

                if ((count_P + count_Q - count_PQ == remaining_N)&&(mod_P == 0)&&(mod_Q == 0)) {
                    left = mid;
                    break;
                }

                if (count_P + count_Q - count_PQ >= remaining_N) {right = mid;}

                else {left = mid + 1;}

                mid = left + (right - left) / 2;
            }
        }

        //result = (left * GCD + offset) % MOD;

        if (abs(left) >= MOD) {left %= MOD;}

        result = product_mod_MOD(left, GCD, MOD);

        /*if ((left > 0)&&(((left < MOD)&&(MOD / left < GCD))||((GCD < MOD)&&(MOD / GCD < left)))) {
            if (left >= GCD) {a = left, b = GCD;}
            else {a = GCD, b = left;}
            c = MOD / a, d = MOD % a;

            result = a * (b % c) - d * (b / c);
        }
        else {result = left * GCD;}

        if (result >= MOD) {result %= MOD;}*/
        result += offset;
        result %= MOD;
        if (result < 0) {result += MOD;}
    }

    return result;
}




//i messed up something, this one does not work
int nthMagicalNumber_something_is_wrong_with_this_one(int N, int A, int B) {
    int result, MCD, left, right, mid;
    int P, Q, PQ, MOD = 10007, mod;
    int count_A, mod_A, count_B, mod_B, count_AB;

    if (A == B) {
        int how_many_A_in_MOD = MOD / A;
        int first = N / how_many_A_in_MOD, second = MOD - (how_many_A_in_MOD * A);
        //int remaining_N = N - (N / how_many_A_in_MOD) * how_many_A_in_MOD;
        int remaining_N = N - first * how_many_A_in_MOD;

        /*
        (N / how_many_A_in_MOD) * (MOD - (how_many_A_in_MOD * A))
        (A*(first/A) + first%A) * (A*(second/A) + second%A)
        A*((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A)) + (first%A) * (second%A)
        */
        int a = first / A, b = second / A, c = first % A, d = second % A;
        //remaining_N -= ((first/A)*(second/A) + (first%A)*(second/A) + (first/A)*(second%A));
        remaining_N -= (a * b + b * c + d * a);
        int offset = c * d;
        result = (remaining_N * A - offset) % MOD;
        if (result < 0) {result += MOD;}
    }

    else {
        int temp0 = A, temp1 = B;
        while ((temp0 > 0)&&(temp1 > 0)) {
            if (temp0 > temp1) {temp0 -= temp1;}
            else {temp1 -= temp0;}
        }
        MCD = (temp0 > 0)? temp0: temp1;
        P = A / MCD, Q = B / MCD;
        PQ = P * Q;//PQ is the (P + Q - 1)-th smallest number, there are (P + Q - 2) numbers before it
        int P_p_Q_m_1 = P + Q - 1;

        //int criteria = MOD / P + MOD / Q - MOD / (P * Q);
        int criteria = MOD / P + MOD / Q - MOD / PQ;

        if (criteria < N) {
            int offset = 0, first_multiple_of_PQ_that_is_no_more_than_MOD = 0;
            /*feels so relieved to see that restriction of this problems means
            that PQ is roughly of the same order as MOD,
            or this problem will be harder to deal with*/
            //find the first multiple of PQ that is no less than MOD
            if (PQ * MCD <= MOD) {first_multiple_of_PQ_that_is_no_more_than_MOD = PQ * (MOD / PQ);}

            if (first_multiple_of_PQ_that_is_no_more_than_MOD == 0) {
                if (P_p_Q_m_1 < N) {//IM NOT ENTIRELY SURE M.C.D. IN THE END OF THIS PART IS CORRECT.
                    //int part_1 = N / (P + Q - 1), part_2 = N % (P + Q - 1);
                    int part_1 = N / P_p_Q_m_1, part_2 = N % P_p_Q_m_1;

                    //calculate offset using part_1
                    mod = PQ % MOD;
                    /*this "larger, smaller...offset = " part will probably only work
                    when 1, both larger & smaller are way smaller than MOD, 2, (larger * smaller) is roughly of the same order as MOD
                    or it will fail miserably, causing overflow (compared to MOD) kind of trouble*/
                    int larger, smaller;
                    if (mod > part_1) {larger = mod, smaller = part_1;}
                    else {larger = part_1, smaller = mod;}

                    int smaller_part_1 = MOD / smaller;
                    int smaller_part_2 = MOD % smaller;

                    /*larger * smaller =
                    fraction_of_larger * smaller
                     + (close_to_MODs * smaller + smaller_part_2 * whatever_that_is)//this line is multiplies of MOD
                     - smaller_part_2 * whatever_that_is;

                    =
                    (larger % smaller_part_1) * smaller
                     + (smaller_part_1 * (larger / smaller_part_1) * smaller + smaller_part_2 * (larger / smaller_part_1))//this line is multiplies of MOD
                     - smaller_part_2 * (larger / smaller_part_1);*/

                    //offset = (larger % smaller_part_1) * smaller - smaller_part_2 * (larger / smaller_part_1);
                    //offset = offset % MOD;

                    offset = (larger % smaller_part_1) * smaller;
                    offset %= MOD;
                    offset -= smaller_part_2 * (larger / smaller_part_1);
                    offset = offset % MOD;

                    //find the part_2-th number
                    left = 0, right = PQ, mid = (left + right) / 2;
                    while (left < right) {
                        count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                        mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                        if ((count_A + count_B - count_AB == part_2)&&(mod_A == 0)&&(mod_B == 0)) {
                            left = mid;
                            break;
                        }

                        if (count_A + count_B - count_AB >= part_2) {right = mid;}

                        else {left = mid + 1;}

                        mid = (left + right) / 2;
                    }

                    //result = ((left + offset) * MCD) % MOD;
                    result = (left + offset);
                    result %= MOD;
                    result *= MCD;
                    result %= MOD;
                    if (result < 0) {result += MOD;}
                }

                else if (P_p_Q_m_1 > N) {//easy~, the same as criteria >= N
                    left = MOD, right = PQ, mid = (left + right) / 2;

                    while (left < right) {
                        count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                        mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                        if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                            left = mid;
                            break;
                        }

                        if (count_A + count_B - count_AB >= N) {right = mid;}

                        else {left = mid + 1;}

                        mid = (left + right) / 2;
                    }

                    result = (left * MCD) % MOD;
                }

                else if (P_p_Q_m_1 == N) {//easiest~
                    result = (PQ * MCD) % MOD;
                }
            }

            else {
                mod = MOD - first_multiple_of_PQ_that_is_no_more_than_MOD;

                /*what we have here, is:
                1. a big negative sum which is probably larger than MOD
                2. remaining N

                what we gonna do here is:
                1. find how many (P + Q - 1) be within N
                2. add *that many PQ* to that big negative sum (thus make it closer to 0), while remaining N become (*remaining N*) % PQ
                3. find that (remaining N)-th number in range 1 to PQ
                4. add this (remaining N)-th number to that smaller negative sum, then find its 1st positive module relative to MOD
                */

                int MOD_d_PQ = (MOD / PQ);
                //int remaining_N = N - ((MOD / PQ)*(P + Q - 1))*(N / ((MOD / PQ)*(P + Q - 1)));
                int remaining_N = N - (MOD_d_PQ * P_p_Q_m_1)*(N / (MOD_d_PQ * P_p_Q_m_1));

                int how_many_PQ_within = remaining_N / P_p_Q_m_1;
                remaining_N %= P_p_Q_m_1;

                //first_part < PQ
                int first_part = mod;
                //int second_part = (N / ((MOD / PQ)*(P + Q - 1)));
                int second_part = N / (MOD_d_PQ * P_p_Q_m_1);

                left = 0, right = PQ, mid = (left + right) / 2;
                while (left < right) {
                    count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                    mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                    if ((count_A + count_B - count_AB == remaining_N)&&(mod_A == 0)&&(mod_B == 0)) {
                        left = mid;
                        break;
                    }

                    if (count_A + count_B - count_AB >= remaining_N) {right = mid;}

                    else {left = mid + 1;}

                    mid = (left + right) / 2;
                }

                int a = second_part - PQ + first_part;
                a %= MOD;
                a = how_many_PQ_within - a;
                a %= MOD;
                a * PQ;
                //result = ((how_many_PQ_within - (second_part - PQ + first_part)) * PQ) + (PQ - first_part) * (second_part - PQ) + left;
                result = a + (PQ - first_part) * (second_part - PQ) + left;
                result %= MOD;
                result *= MCD;
                result %= MOD;
                if (result < 0) {result += MOD;}
            }
        }

        else {
            left = 1, right = MOD, mid = (left + right) / 2;

            while (left < right) {
                count_A = mid / P, count_B = mid / Q, count_AB = mid / PQ;
                mod_A = mid - P * count_A, mod_B = mid - Q * count_B;

                if ((count_A + count_B - count_AB == N)&&(mod_A == 0)&&(mod_B == 0)) {
                    left = mid;
                    break;
                }

                if (count_A + count_B - count_AB >= N) {right = mid;}

                else {left = mid + 1;}

                mid = (left + right) / 2;
            }

            result = (left * MCD) % MOD;
        }
    }
    return result;
}

/*
A = 37, B = 36

431, 863,
*/
int main(){
    srand(time(0));int lower_range = 35000, upper_range = 40000, display = 0, input = 1;
    int A = 3, B = 3;
    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;

/*
N = 151, A = 121, B = 146
N = 265, A = 121, B = 146*/

/*N = 1000000000, A = 39999, B = 40000
GCD = 1, LCM = 1599960000
criteria < N
largest_AB_multi_no_more_than_MOD = 0
LCM > MOD
P + Q - 1 < N

overflow danger in MOD % a!
d = 400040014, (b / c) = 12500

offset = -1158242456
left = 0
left = 500000000
offset = -1158242456

shit = 341757551


Input: 1000000000
39999
40000
Output: 139993
Expected: 999860007


*/
    vector<int> brute_result;// = nthMagicalNumber_brute(200, 200, A, B);
    /*for (int i = 0; i < 100; i++) {//brute_result.size()
        cout << brute_result[i] << "\t";if ((i + 1) % 10 == 0) {cout << "\n";}
    }
    cout << "\n\n\n";*/

    vector<int> result;
    vector<int> result_1;
    vector<int> wrong_idx;

    int test_range = 1000000000, MOD = 1000000007;
        /*int P = 35048, Q = 36489, PQ = P * Q, test_timer = 0;
        int left = 0, right = 1278866472, mid = (left + right) / 2;
        int count_P, count_Q, count_PQ, mod_P, mod_Q;
        while (left < right) {
            count_P = mid / P, count_Q = mid / Q, count_PQ = mid / PQ;
            mod_P = mid - P * count_P, mod_Q = mid - Q * count_Q;

            if ((count_P + count_Q - count_PQ == 68792)&&(mod_P == 0)&&(mod_Q == 0)) {
                left = mid;
                break;
            }

            if (count_P + count_Q - count_PQ >= 68792) {
                if (test_timer >= 200) {cout << ">=\n";}
                right = mid - 1;
            }

            else {
                if (test_timer >= 200) {cout << "<\n";}
                left = mid + 1;
            }


            if (test_timer >= 0) {test_timer++;}
            if (test_timer >= 200) {
                cout << "test_timer = " << test_timer << "\n";
                cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
                cout << "count_P = " << count_P << ", count_Q = " << count_Q << ", count_PQ = " << count_PQ << "\n";
                cout << "mid / P = " << mid / P << ", mid / Q = " << mid / Q << ", mid / PQ = " << mid / PQ << "\n";
                cout << "mid - P * count_P = " << mid - P * count_P << ", mid - Q * count_Q = " << mid - Q * count_Q << "\n\n";
            }

            if (test_timer >= 250) {break;}

            mid = (left + right) / 2;
        }
        cout << "left = " << left << "\n";*/
for (int p = 1, exit = 0; p <= 1000; p++) {if (p % 100 == 0) {cout << "p = " << p << "\n";}
    if (input != 0) {
        A = rand()%(upper_range - lower_range + 1) + lower_range;
        B = rand()%(upper_range - lower_range + 1) + lower_range;
    }


    /*if (input != 0) {
        if (B < upper_range) {B++;}
        else {A++, B = 2;}
    }
    if (A > upper_range) {
        cout << "A = " << A << ", B = " << B << "\n";
        cout << "already tested all candidates.\n";
        break;
    }*/

    /*start_point_2 = chrono::steady_clock::now();
    brute_result = nthMagicalNumber_brute(test_range, test_range, A, B);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;*/

    result.reserve(test_range);
    result_1.reserve(test_range);

for (int m = 999990000, shit, shit_1; m <= test_range; m++) {//if (m % 100 == 0) {cout << "m = " << m << "\n";}
    start_point_1 = chrono::steady_clock::now();
    shit = nthMagicalNumber_totally_works(m, A, B);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;
    //result.push_back(shit);

    //cout << "\nshit = " << shit << "\n";
    //cout << "while it is supposed to be " << brute_result[265] % 10000 << "\n";

    start_point_3 = chrono::steady_clock::now();
    shit_1 = nthMagicalNumber(m, A, B);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;
    result_1.push_back(shit_1);
    //cout << "\nshit_1 = " << shit_1 << "\n";

    if (shit != shit_1) {
        cout << "N = " << m << ", A = " << A << ", B = " << B << "\n";
        cout << "shit = " << shit << "\n";
        cout << "shit_1 = " << shit_1 << "\n";
        exit = 1;
        break;
    }
}

//if (exit != 0) {break;}

/*
for (int i = 0; i < brute_result.size(); i++) {
    if (brute_result[i] % MOD != result_1[i]) {
        wrong_idx.push_back(i);
    }
}
if (wrong_idx.size() == 0) {
    //cout << "good! no error detected!\n";
}
else {
    cout << "something is wrong.\n\n";
    cout << "p = " << p << "\n\n";
    cout << "A = " << A << ", B = " << B << "\n\n";
    for (int i = 0; i < wrong_idx.size(); i++) {
        cout << wrong_idx[i] << ", ";
    }
    cout << "\nwrong_idx output complete.\n\n";

    cout << "\nbrute:\n";
    for (int i = 0; i < brute_result.size(); i++) {
        cout << brute_result[i] << "\t";
        if ((i + 1) % 10 == 0) {cout << "\n";}
        if ((i + 1) % 100 == 0) {cout << "\n";}
    }
    cout << "\n\nresult:\n";
    for (int i = 0; i < result_1.size(); i++) {
        cout << result_1[i] << "\t";
        if ((i + 1) % 10 == 0) {cout << "\n";}
        if ((i + 1) % 100 == 0) {cout << "\n";}
    }
    cout << "\n";
    break;
}
*/

result.clear();
result_1.clear();
brute_result.clear();
wrong_idx.clear();
}

cout << "\n_totally_works:\n";
cout << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << "\n:\n";
cout << duration <double, milli> (diff_3).count() << " ms" << "\n";
cout << "\nbrute:\n";
cout << duration <double, milli> (diff_2).count() << " ms" << "\n";
    return 0;
}




