/*483. Smallest Good Base
Hard

For an integer n, we call k>=2 a good base of n,
if all digits of n base k are 1.

Now given a string representing n,
you should return the smallest good base of n in string format.

Input: "13"
Output: "3"
Explanation: 13 base 3 is 111.

Input: "4681"
Output: "8"
Explanation: 4681 base 8 is 11111.

Input: "1000000000000000000"
Output: "999999999999999999"
Explanation: 1000000000000000000 base 999999999999999999 is 11.

Note:
    The range of n is [3, 10^18].
    The string representing n is always valid and will not have leading zeros.
*/

/*
class Solution {
public:
    string smallestGoodBase(string n) {

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

/*for any number n, if it CAN be represented in base ? in a "good base" way, then this will hold:
there exists a number m, which satisfies condition (? ^ m - 1 = n * (? - 1))
(? ^ m - 1 = n * (? - 1)) is just another form of (n = (? ^ m - 1) / (? - 1))

? ^ m = n * (? - 1) + 1

m = 1 is always a good starting step.

this problems is equivalent to finding the largest integer m which satisfies that relation

*/



int find_root() {}

//long long int!!!
int smallestGoodBase_what_a_mess(int n) {
    int base = n - 1, base_2_limit;

    //find the max base 2 limit
    for (int i = 1; i < 31; i++) {
        if (pow(2, i) > n) {
            base_2_limit = i;
            break;
        }
    }

    int roots[base_2_limit];
    //find the m-th root
    //CAREFUL! DON'T GET OVERFLOW!
    /*DANGER! OVERFLOW! - shit, this bunch does NOT work at all, back to...

    mid = sqrt(left * right)

    mid * mid = left * right

    ------- PROBABLY WILL NOT WORK ------
    mid = left + ?
    (left + ?) * (left + ?) = left * right
    left * left + 2 * left * ? + ? * ? = left * right
    ? * ? + 2 * left * ? + left * (left - right) = 0
    ? * (? + 2 * left) = left * (right - left)
    ? = (left * (right - left)) / (? + 2 * left)
    ------- PROBABLY WILL NOT WORK ------

    ------- PROBABLY WILL NOT WORK TOO ------
    1 + a + a ^ 2 + a ^ 3 + ... = S with a != 1
    a * S = S - 1
    if a < 1, S = 1 / (1 - a)
    ------- PROBABLY WILL NOT WORK TOO ------

    -------try taylor expansion, this should work----and it didnt
    mid = (left * right) ^ (1/2)
    f(x) = x ^ (1/2)
    f(x) = a + f' * (x - a) + f'' * (x - a) ^ 2, where f' & f'' are VALUEs (if the 1st/2nd derivative) at a,
    //f(x) = a + ((1/2) * (x - a)) / (x ^ (1/2)) - ((1/4) * (x - a) ^ 2) / (x ^ (3/2)) - not apparently helpful

    let a = left
    mid = left + f' * (x - left) + f'' * (x - a) ^ 2, where 2nd order might well be discarded
    then we need fucking 1/(left ^ (1/2))

    -------try taylor expansion, this should work----and it didnt





    */

    for (int i = 0; i < base_2_limit; i++) {
        //roots[i] = find_root(n, i);
    }

    //CAREFUL! DON'T GET OVERFLOW!
    //in every case, here it is searching for potential representation of (m + 1) digits
    for (int m = 2, left; m <= base_2_limit; m++) {
        //CAREFUL! DON'T GET OVERFLOW!
        //for the p-th root, value of its "GoodBase" representation is
        //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1
        //for () {}
    }

    return base;
}

//checkpoint
int smallestGoodBase_decent_start(int n) {
    int base = n - 1, base_2_limit, test_timer = -1, sqrt_counter = 1;
    long long int temp = n;//wonderful temp always come in handy

    //count digits in base 2.
    for (int i = 0; i < 64; i++) {
        temp = temp >> 1;
        if (temp == 0) {
            base_2_limit = i + 1;
            break;
        }
    }

    if (test_timer >= 0) {
        cout << "wtf?!\n";
        cout << "base_2_limit = " << base_2_limit << "\n";
    }

    long long int left, right, mid;
    //CAREFUL! DON'T GET OVERFLOW!
    //in every case, here it is searching for potential representation of (m + 1) digits
    for (int m = 1, one_more = 1; m < base_2_limit; m++) {
        if (test_timer >= 0) {cout << "\n\nm = " << m << "\n\n";}

        //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1

        //determine left, right & mid
        left = 2, right = sqrt(n);
        sqrt_counter = 1;
        if (test_timer >= 0) {cout << "right = " << right << "\n";}

        for (int i = (m + 1)/2; i > 1; i = i/2) {
            right = sqrt(right);
            sqrt_counter++;
            if (test_timer >= 0) {cout << "right = " << right << "\n";}
        }

        mid = left + (right - left) / 2;//mid = sqrt(left * right);//?

        if (test_timer >= 0) {
            cout << "left = " << left << "\n";
            cout << "mid = " << mid << "\n";
            cout << "right = " << right << "\n\n";

            cout << "sqrt_counter = " << sqrt_counter << "\n\n";
            //test_timer++;
        }

        if (left > right) {continue;}//just in case

        one_more = 1;
        //then enter the loop
        while (left <= right) {
            temp = 0;
            for (int i = 0; i <= m; i++) {temp += pow(mid, i + 1);}
            temp++;

            if (test_timer >= 0) {
                cout << "left = " << left << "\n";
                cout << "mid = " << mid << "\n";
                cout << "right = " << right << "\n\n";
                cout << "temp = " << temp << "\n\n";
            }

            if (temp > n) {right = mid;}

            else if (temp == n) {
                base = mid;
                break;
            }

            else {left = mid + 1;}

            if ((one_more == 0)||(left > right)) {break;}
            if (left == right) {one_more = 0;}//just in case

            //mid = sqrt(left * right);
            mid = left + (right - left) / 2;

            if (test_timer >= 0) {}
            //if (test_timer >= 20) {break;}//test_timer++;
        }

        //if (test_timer >= 50) {break;}
    }

    return base;
}

//OVERFLOW checkpoint
//9223372036854775807
//3853052505964431
int smallestGoodBase_OVERFLOW_checkpoint(long long int n) {
    long long int base = n - 1;
    int base_2_limit, criteria, test_timer = 0, sqrt_counter = 1;
    long long int temp = n;//wonderful temp always come in handy

    //count digits in base 2.
    for (int i = 0; i < 64; i++) {
        temp = temp >> 1;
        if (temp == 0) {
            base_2_limit = i + 1;
            break;
        }
    }

    if (test_timer >= 0) {cout << "base_2_limit = " << base_2_limit << "\n";}

    long long int left, right, mid;
    //CAREFUL! DON'T GET OVERFLOW!
    //in every case, here it is searching for potential representation of (m + 1) digits
    for (int m = 1, one_more = 1; m < base_2_limit; m++) {
        if (test_timer >= 0) {cout << "\nm = " << m << "\n\n";}

        criteria = log(9223372036854775807) / log (m);
        //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1

        //determine left, right & mid
        left = 2, right = sqrt(n);
        sqrt_counter = 1;
        if (test_timer >= 0) {cout << "right = " << right << "\n";}

        /*
        353,814,783,205,469,041
        */

        for (int i = (m + 1)/2; i > 1; i = i/2) {
            right = sqrt(right);
            sqrt_counter++;
            if (test_timer >= 0) {cout << "right = " << right << "\n";}
        }

        mid = left + (right - left) / 2;//mid = sqrt(left * right);//?

        if (test_timer >= 0) {
            cout << "left = " << left << "\n";
            cout << "mid = " << mid << "\n";
            cout << "right = " << right << "\n\n";
            cout << "sqrt_counter = " << sqrt_counter << "\n\n";
            //test_timer++;
        }

        if (left > right) {continue;}//just in case

        one_more = 1;
        //then enter the loop
        while (left <= right) {
            temp = 0;
            for (int i = 0; i <= m; i++) {temp += pow(mid, i + 1);}
            temp++;

            if (test_timer >= 0) {
                cout << "left = " << left << "\n";
                cout << "mid = " << mid << "\n";
                cout << "right = " << right << "\n\n";
                cout << "temp = " << temp << "\n\n";
            }

            if (temp > n) {right = mid;}

            else if (temp == n) {
                base = mid;
                break;
            }

            else {left = mid + 1;}

            if ((one_more == 0)||(left > right)) {break;}
            if (left == right) {one_more = 0;}//just in case

            //mid = sqrt(left * right);
            mid = left + (right - left) / 2;

            if (test_timer >= 0) {}
            //if (test_timer >= 20) {break;}//test_timer++;
        }

        //if (test_timer >= 50) {break;}
    }

    return base;
}



//OVERFLOW DANGER!!! -- appeared to be tamed -- checkpoint
int smallestGoodBase_fixed_some_overflow_issues(long long int n) {
    long long int base = n - 1;
    int base_2_limit, test_timer = -1, sqrt_counter = 1;
    long long int temp = n;//wonderful temp always come in handy
    double root, criteria;

    //count digits in base 2.
    for (int i = 0; i < 64; i++) {
        temp = temp >> 1;
        if (temp == 0) {
            base_2_limit = i + 1;
            break;
        }
    }

    if (test_timer >= 0) {cout << "base_2_limit = " << base_2_limit << "\n";}

    long long int left, right, mid;
    //CAREFUL! DON'T GET OVERFLOW!
    //in every case, here it is searching for potential representation of (m + 1) digits
    for (int m = 1, one_more = 1; m < base_2_limit; m++) {
        if (test_timer >= 0) {cout << "\nm = " << m << "\n\n";}
        root = 1;
        root /= (m + 1);
        criteria = pow(9223372036854775807, root);

        if (test_timer >= 0) {
            cout << "root = " << root << "\n";
            cout << "criteria = " << criteria << "\n\n";
        }

        //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1

        //determine left, right & mid
        left = 2;
        root = 1;
        root /= m;
        right = pow(n, root);
        if (test_timer >= 0) {
            cout << "right = " << right << "\n";
            cout << "root = " << root << "\n";
        }

        if (right > criteria) {right = criteria;}

        mid = left + (right - left) / 2;//mid = sqrt(left * right);//?

        if (test_timer >= 0) {
            cout << "left = " << left << "\n";
            cout << "mid = " << mid << "\n";
            cout << "right = " << right << "\n\n";
            cout << "sqrt_counter = " << sqrt_counter << "\n\n";
            //test_timer++;
        }

        if (left > right) {continue;}//just in case

        one_more = 1;
        //then enter the loop
        while (left <= right) {
            temp = 0;
            for (int i = 0; i <= m; i++) {temp += pow(mid, i);}

            if (test_timer >= 0) {
                cout << "left = " << left << "\n";
                cout << "mid = " << mid << "\n";
                cout << "right = " << right << "\n\n";
                cout << "temp = " << temp << "\n\n";
            }

            if (temp > n) {right = mid;}

            else if (temp == n) {
                base = mid;
                break;
            }

            else {left = mid + 1;}

            if ((one_more == 0)||(left > right)) {break;}
            if (left == right) {one_more = 0;}//just in case

            //mid = sqrt(left * right);
            mid = left + (right - left) / 2;

            if (test_timer >= 0) {}
            //if (test_timer >= 20) {break;}//test_timer++;
        }

        //if (test_timer >= 50) {break;}
    }

    return base;
}


//checkpoint
//so far so good. minor performance improvement by significantly increased initial "left" value
int smallestGoodBase_probably_almost_ready(long long int n) {
    long long int base = n - 1, temp = n;//wonderful temp always come in handy
    int base_2_limit, test_timer = -1;
    double root, criteria;

    //count digits in base 2.
    for (int i = 0; i < 64; i++) {
        temp = temp >> 1;
        if (temp == 0) {
            base_2_limit = i + 1;
            break;
        }
    }

    if (test_timer >= 0) {cout << "base_2_limit = " << base_2_limit << "\n";}

    long long int left, right, mid;
    //CAREFUL! DON'T GET OVERFLOW!
    //in every case, here it is searching for potential representation of (m + 1) digits
    for (int m = 2, one_more = 1; m < base_2_limit; m++) {
        if (test_timer >= 0) {cout << "\nm = " << m << "\n";}

        //need to criteria to prevent overflow
        root = 1, root /= (m + 1);
        criteria = pow(9223372036854775807, root);

        if (test_timer >= 0) {
            cout << "root = " << root << "\n";
            cout << "criteria = " << criteria << "\n\n";
        }

        //determine left, right & mid, that repeated exp in while loop is highly costly, better narrow left & right down
        root = 1, root /= (m + 1);
        left = pow(n, root);

        root = 1, root /= m;
        right = pow(n, root);

        //if (right > criteria) {right = criteria;}

        mid = left + (right - left) / 2;//mid = sqrt(left * right);//?

        if (test_timer >= 0) {
            cout << "left = " << left << "\n";
            cout << "mid = " << mid << "\n";
            cout << "right = " << right << "\n\n";
        }

        if (left > right) {continue;}//just in case

        one_more = 1;
        while (left <= right) {
            //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1
            temp = 0;
            for (int i = 0; i <= m; i++) {temp += pow(mid, i);}

            if (test_timer >= 0) {
                cout << "left = " << left << "\n";
                cout << "mid = " << mid << "\n";
                cout << "right = " << right << "\n\n";
                cout << "temp = " << temp << "\n\n";
            }

            if (temp == n) {
                base = mid;
                break;
            }

            else if (temp > n) {right = mid;}

            else {left = mid + 1;}

            if ((one_more == 0)||(left > right)) {break;}
            if (left == right) {one_more = 0;}//just in case

            //mid = sqrt(left * right);
            mid = left + (right - left) / 2;
        }

    }

    return base;
}



long long int smallestGoodBase(long long int n) {
    long long int base = n - 1, temp = n, temp1, temp2;//wonderful temp always come in handy
    int base_2_limit, test_timer = -1;
    double root;

    //count digits in base 2.
    for (int i = 0; i < 64; i++) {
        temp = temp >> 1;
        if (temp == 0) {
            base_2_limit = i + 1;
            break;
        }
    }

    if (test_timer >= 0) {cout << "base_2_limit = " << base_2_limit << "\n";}

    long long int left, right, mid;

    //searching for potential representation of (m + 1) digits,
    //(n - 1) is always the 2 digits representation
    //starting from m = 2 -> 3 digits representation
    for (int m = 2, one_more = 1; m < base_2_limit; m++) {
        if (test_timer >= 0) {cout << "\nm = " << m << "\n";}

        //determine left, right & mid, that repeated exp in while loop is highly costly, better narrow left & right down
        root = 1, root /= (m + 1);
        left = pow(n, root);

        root = 1, root /= m;
        right = pow(n, root);

        mid = left + (right - left) / 2;

        if (test_timer >= 0) {cout << "left = " << left << "\nmid = " << mid << "\nright = " << right << "\n\n";}

        if (left > right) {continue;}

        one_more = 1;
        while (left <= right) {
            //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1
            temp = mid + 1;
            for (int i = 2; i <= m; i++) {
                temp1 = mid;
                for (int j = 1; j < i; j++) {temp1 *= mid;}
                temp += temp1;

                //temp += pow(mid, i);

                //temp1 = pow(mid, i);
                //temp += temp1;
            }

            if (test_timer >= 0) {
                cout << "left = " << left << "\nmid = " << mid << "\n";
                cout << "right = " << right << "\n\ntemp = " << temp << "\n\n";
            }

            if (temp == n) {
                base = mid;

                if (test_timer >= 0) {cout << "base = " << base << "\n";}

                break;
            }

            else if (temp > n) {right = mid;}

            else {left = mid + 1;}

            if ((one_more == 0)||(left > right)) {break;}
            if (left == right) {one_more = 0;}

            mid = left + (right - left) / 2;
        }

    }

    return base;
}


//passed, decent but NOT EXCELLENT
string smallestGoodBase_base_line(string n) {
    int length = n.size(), base_counter, test_timer = 0;
    long long int N = 0, good_base, temp, temp1;
    for (int i = 0; i < length; i++) {
        temp = n[i] - 48;

        if (temp > 0) {
            for (int j = 0; j < length - i - 1; j++) {temp *= 10;}

            N += temp;
        }
    }

    if (test_timer >= 0) {cout << "N = " << N << "\n\n\n";}

    good_base = N - 1, temp = N;//wonderful temp always come in handy
    double root;//, criteria

    //count digits in BASE 2.
    for (int i = 0; i < 64; i++) {
        temp = temp >> 1;
        if (temp == 0) {
            base_counter = i + 1;
            break;
        }
    }

    if (test_timer >= 0) {cout << "base_counter = " << base_counter << "\n";}

    long long int left, right, mid;
    //CAREFUL! DON'T GET OVERFLOW!
    //in every case, here it is searching for potential representation of (m + 1) digits
    for (int m = 2, one_more = 1; m < base_counter; m++) {
        if (test_timer >= 0) {cout << "\nm = " << m << "\n";}

        //determine left, right & mid, that repeated exp in while loop is highly costly, better narrow left & right down
        root = 1, root /= (m + 1);
        left = pow(N, root);

        root = 1, root /= m;
        right = pow(N, root);

        //if (right > criteria) {right = criteria;}

        mid = left + (right - left) / 2;

        if (test_timer >= 0) {
            cout << "left = " << left << "\n";
            cout << "mid = " << mid << "\n";
            cout << "right = " << right << "\n\n";
        }

        if (left > right) {continue;}//just in case

        one_more = 1;
        while (left <= right) {
            //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1
            temp = mid + 1;
            for (int i = 2; i <= m; i++) {
                temp1 = mid;
                for (int j = 1; j < i; j++) {temp1 *= mid;}
                temp += temp1;
            }

            if (test_timer >= 0) {
                cout << "left = " << left << "\n";
                cout << "mid = " << mid << "\n";
                cout << "right = " << right << "\n\n";
                cout << "temp = " << temp << "\n\n";
            }

            if (temp == N) {
                good_base = mid;
                if (test_timer >= 0) {cout << "\ngood_base = " << good_base << "\n";}
                break;
            }

            else if (temp > N) {right = mid;}

            else {left = mid + 1;}

            if ((one_more == 0)||(left > right)) {break;}
            if (left == right) {one_more = 0;}//just in case

            //mid = sqrt(left * right);
            mid = left + (right - left) / 2;
        }
    }

    //output. BASE 10
    base_counter = log10(good_base);
    char characters[base_counter + 1];
    temp = good_base;
    for (int i = base_counter, mod; i >= 0; i--) {
        mod = temp % 10;
        characters[i] = mod + 48;
        temp -= mod, temp /= 10;
    }

    string result;
    for (int i = 0, started = 0; i <= base_counter; i++) {
        if (characters[i] != 48) {started = 1;}
        if (started != 0) {result.push_back(characters[i]);}
    }

    return result;
}

//what?!slower?!
string smallestGoodBase(string n) {
    int length = n.size(), base_counter, test_timer = -1;
    long long int N = 0, good_base, temp, temp1;

    //input
    for (int i = 0; i < length; i++) {
        temp = n[i] - 48;

        if (temp > 0) {
            for (int j = 0; j < length - i - 1; j++) {temp *= 10;}

            N += temp;
        }
    }

    //if (test_timer >= 0) {cout << "\nN = " << N << "\n";}

    good_base = N - 1, temp = N;
    double root;

    //count digits in BASE 2.
    for (int i = 0; i < 64; i++) {
        temp = temp >> 1;
        if (temp == 0) {
            base_counter = i + 1;
            break;
        }
    }

    long long int left, right, mid;

    //searching for potential representation of (m + 1) digits
    for (int m = 2, one_more = 1; m < base_counter; m++) {
        //if (test_timer >= 0) {cout << "\nm = " << m << "\n";}

        //determine left, right & mid, that repeated exp in while loop is highly costly, better narrow left & right down
        root = 1, root /= (m + 1);
        left = pow(N, root);

        root = 1, root /= m;
        right = pow(N, root);

        mid = left + (right - left) / 2;

        //if (test_timer >= 0) {cout << "left = " << left << "\nmid = " << mid << "\nright = " << right << "\n\n";}

        if (left > right) {continue;}//just in case

        one_more = 1;
        while (left <= right) {
            //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1
            temp = mid + 1;
            for (int i = 2; i <= m; i++) {
                temp1 = mid;
                for (int j = 1; j < i; j++) {temp1 *= mid;}
                temp += temp1;
            }

            /*if (test_timer >= 0) {
                cout << "left = " << left << "\n";
                cout << "mid = " << mid << "\n";
                cout << "right = " << right << "\n\n";
                cout << "temp = " << temp << "\n\n";
            }*/

            if (temp == N) {
                good_base = mid;
                //if (test_timer >= 0) {cout << "\ngood_base = " << good_base << "\n";}
                break;
            }

            else if (temp > N) {right = mid;}

            else {left = mid + 1;}

            if ((one_more == 0)||(left > right)) {break;}
            if (left == right) {one_more = 0;}

            mid = left + (right - left) / 2;
        }
    }

    //output. BASE 10
    /*base_counter = log10(good_base);
    char characters[base_counter + 1];
    temp = good_base;
    for (int i = base_counter, mod; i >= 0; i--) {
        mod = temp % 10;
        characters[i] = mod + 48;
        temp -= mod, temp /= 10;
    }

    string result;
    for (int i = 0, started = 0; i <= base_counter; i++) {
        if (characters[i] != 48) {started = 1;}
        if (started != 0) {result.push_back(characters[i]);}
    }*/


    //output. BASE 10
    base_counter = log10(good_base);
    string result;
    result.reserve(base_counter + 1);
    for (int i = 0; i <= base_counter; i++) {result.push_back(48);}
    temp = good_base;

    if (test_timer >= 0) {cout << "\ngood_base = " << good_base << "\n";}

    for (int i = base_counter, mod; i >= 0; i--) {
        mod = temp % 10;
        result[i] = mod + 48;
        temp -= mod, temp /= 10;
    }

    int start_idx = 0;
    for (int i = 0; i <= base_counter; i++) {
        if (result[i] != 48) {
            start_idx = i;
            break;
        }
    }

    if (start_idx != 0) {
        result = result.substr(start_idx, base_counter - start_idx + 1);
    }

    return result;
}


//no significant performance improvements
string smallestGoodBase_how_about_searching_from_smallest_to_largest(string n) {
    int length = n.size(), base_counter;
    //int test_timer = 0
    long long int N = 0, good_base, temp, temp1;
    for (int i = 0; i < length; i++) {
        temp = n[i] - 48;

        if (temp > 0) {
            for (int j = 0; j < length - i - 1; j++) {temp *= 10;}

            N += temp;
        }
    }

    //if (test_timer >= 0) {cout << "N = " << N << "\n\n\n";}

    good_base = N - 1, temp = N;//wonderful temp always come in handy
    double root;//, criteria

    //count digits in BASE 2.
    for (int i = 0; i < 64; i++) {
        temp = temp >> 1;
        if (temp == 0) {
            base_counter = i + 1;
            break;
        }
    }

    //if (test_timer >= 0) {cout << "base_counter = " << base_counter << "\n";}

    long long int left, right, mid;
    //CAREFUL! DON'T GET OVERFLOW!
    //in every case, here it is searching for potential representation of (m + 1) digits
    for (int m = base_counter - 1, one_more = 1; m >= 2; m--) {
        //if (test_timer >= 0) {cout << "\nm = " << m << "\n";}

        //determine left, right & mid, that repeated exp in while loop is highly costly, better narrow left & right down
        root = 1, root /= (m + 1);
        left = pow(N, root);

        root = 1, root /= m;
        right = pow(N, root);

        //if (right > criteria) {right = criteria;}

        mid = left + (right - left) / 2;

        //if (test_timer >= 0) {cout << "left = " << left << "\nmid = " << mid << "\nright = " << right << "\n\n";}

        if (left > right) {continue;}//just in case

        one_more = 1;
        while (left <= right) {
            //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1
            temp = mid + 1;
            for (int i = 2; i <= m; i++) {
                temp1 = mid;
                for (int j = 1; j < i; j++) {temp1 *= mid;}
                temp += temp1;
            }

            //if (test_timer >= 0) {cout << "left = " << left << "\nmid = " << mid << "\nright = " << right << "\n\ntemp = " << temp << "\n\n";}

            if (temp == N) {
                good_base = mid;
                //if (test_timer >= 0) {cout << "\ngood_base = " << good_base << "\n";}
                break;
            }

            else if (temp > N) {right = mid;}

            else {left = mid + 1;}

            if ((one_more == 0)||(left > right)) {break;}
            if (left == right) {one_more = 0;}//just in case

            //mid = sqrt(left * right);
            mid = left + (right - left) / 2;
        }
    }

    //output. BASE 10
    base_counter = log10(good_base);
    char characters[base_counter + 1];
    temp = good_base;
    for (int i = base_counter, mod; i >= 0; i--) {
        mod = temp % 10;
        characters[i] = mod + 48;
        temp -= mod, temp /= 10;
    }

    string result;
    for (int i = 0, started = 0; i <= base_counter; i++) {
        if (characters[i] != 48) {started = 1;}
        if (started != 0) {result.push_back(characters[i]);}
    }

    return result;
}



//(SUPPOSED TO) perform better. Within 1st class in results.
//I temporarily see little room for improvement
//2 tricks i leaned here: stol(), which turn string into integer, & to_string, which turns integer to string
//these 2 got better performance than manual doing those stuff
string smallestGoodBase(string n) {
    int length = n.size(), base_counter;
    //int test_timer = 0
    long long int N = 0, good_base, temp, temp1;

    /*for (int i = 0; i < length; i++) {
        temp = n[i] - 48;

        if (temp > 0) {
            for (int j = 0; j < length - i - 1; j++) {temp *= 10;}

            N += temp;
        }
    }*/

    N = stol(n);

    //if (test_timer >= 0) {cout << "N = " << N << "\n\n\n";}

    good_base = N - 1, temp = N;//wonderful temp always come in handy
    double root;//, criteria

    //count digits in BASE 2.
    for (int i = 0; i < 64; i++) {
        temp = temp >> 1;
        if (temp == 0) {
            base_counter = i + 1;
            break;
        }
    }

    //if (test_timer >= 0) {cout << "base_counter = " << base_counter << "\n";}

    long long int left, right, mid;
    //CAREFUL! DON'T GET OVERFLOW!
    //in every case, here it is searching for potential representation of (m + 1) digits
    for (int m = base_counter - 1, one_more = 1; m >= 2; m--) {
        //if (test_timer >= 0) {cout << "\nm = " << m << "\n";}

        //determine left, right & mid, that repeated exp in while loop is highly costly, better narrow left & right down
        root = 1, root /= (m + 1);
        left = pow(N, root);

        root = 1, root /= m;
        right = pow(N, root);

        //if (right > criteria) {right = criteria;}

        mid = left + (right - left) / 2;

        //if (test_timer >= 0) {cout << "left = " << left << "\nmid = " << mid << "\nright = " << right << "\n\n";}

        if (left > right) {continue;}//just in case

        one_more = 1;
        while (left <= right) {
            //(root[p]) ^ (root[p]) + ... + (root[p]) ^ (3) + (root[p]) ^ (2) + root[p] + 1
            temp = mid + 1;
            for (int i = 2; i <= m; i++) {
                temp1 = mid;
                for (int j = 1; j < i; j++) {temp1 *= mid;}
                temp += temp1;
            }

            //if (test_timer >= 0) {cout << "left = " << left << "\nmid = " << mid << "\nright = " << right << "\n\ntemp = " << temp << "\n\n";}

            if (temp == N) {
                good_base = mid;
                //if (test_timer >= 0) {cout << "\ngood_base = " << good_base << "\n";}
                break;
            }

            else if (temp > N) {right = mid;}

            else {left = mid + 1;}

            if ((one_more == 0)||(left > right)) {break;}
            if (left == right) {one_more = 0;}//just in case

            //mid = sqrt(left * right);
            mid = left + (right - left) / 2;
        }
    }

    //output. BASE 10
    /*base_counter = log10(good_base);
    char characters[base_counter + 1];
    temp = good_base;
    for (int i = base_counter, mod; i >= 0; i--) {
        mod = temp % 10;
        characters[i] = mod + 48;
        temp -= mod, temp /= 10;
    }

    string result;
    for (int i = 0, started = 0; i <= base_counter; i++) {
        if (characters[i] != 48) {started = 1;}
        if (started != 0) {result.push_back(characters[i]);}
    }*/

    return to_string(good_base);
}



long long int related_to_that_base_thing (int base, int length) {
    long long int result = base + 1, temp;
    for (int i = 2; i < length; i++) {
        temp = base;
        for (int j = 1; j < i; j++) {temp *= base;}
        result += temp;
    }
    return result;
}

/*

*/
//9,223,372,036,854,775,807
//9223372036854775807
int main(){
    int k = 8190;//4681,4095,32767,55987
    srand(time(0));int length = 6, display = 1, input = 0;
    int base_lower_range = 400, base_upper_range = 600;
    int length_lower_range = 6, length_upper_range = 6;

    auto start_point_1 = chrono::steady_clock::now();
    auto end_point_1 = chrono::steady_clock::now();
    auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();
    auto end_point_2 = chrono::steady_clock::now();
    auto diff_2 = end_point_2 - start_point_2;

for (int m = 1; m <= 1; m++) {if (m % 10000 == 0) {cout << "m = " << m << "\n";}
    if (input == 1){
        k = rand()%(base_upper_range - base_lower_range + 1) + base_lower_range;
        length = rand()%(length_upper_range - length_lower_range + 1) + length_lower_range;
    }
    /*if (input == 1){
        if (length < length_upper_range) {length++;}
        else {length = 2, k++;}
    }*/

    //long long int shitshit = related_to_that_base_thing(k, 7);
    //if (display == 1){cout << "shitshit = " << shitshit << "\n";}

    start_point_1 = chrono::steady_clock::now();
    string shit = smallestGoodBase("14919921443713777");
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    if (display == 1){cout << "shit = " << shit << "\n";}

    /*start_point_2 = chrono::steady_clock::now();
    int s = smallestGoodBase_fixed_some_overflow_issues(shitshit);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;*/


    //((shit != k)&&(k != 12)&&(k != 20)&(k != 6))
    //if (shit != k) {cout << "k = " << k << ", length = " << length << "\n";break;}

    //if ((k == base_upper_range)&&(length == length_upper_range)) {break;}
}
cout << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << duration <double, milli> (diff_2).count() << " ms" << "\n";

    return 0;
}




