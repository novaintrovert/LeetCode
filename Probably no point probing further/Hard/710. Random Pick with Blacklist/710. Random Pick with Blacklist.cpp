/*710. Random Pick with Blacklist
Hard

Given a blacklist B containing unique integers from [0, N),
write a function to return a uniform random integer from [0, N) which is NOT in B.

Optimize it such that it minimizes the call to system’s Math.random().

Note:
    1 <= N <= 1000000000
    0 <= B.length < min(100000, N)
    [0, N) does NOT include N. See interval notation.

["Solution","pick","pick","pick"]
[[1,[]],[],[],[]]
Output: [null,0,0,0]

["Solution","pick","pick","pick"]
[[2,[]],[],[],[]]
Output: [null,1,1,1]

["Solution","pick","pick","pick"]
[[3,[1]],[],[],[]]
Output: [null,0,0,2]

["Solution","pick","pick","pick"]
[[4,[2]],[],[],[]]
Output: [null,1,3,1]

Explanation of Input Syntax:

The input is two lists: the subroutines called and their arguments.
Solution's constructor has two arguments, N and the blacklist B. pick has no arguments.
Arguments are always wrapped with a list, even if there aren't any.
*/

/*

class Solution {
public:
    Solution(int N, vector<int>& blacklist) {

    }

    int pick() {

    }
};

*/

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(N, blacklist);
 * int param_1 = obj->pick();
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

//too costly
class Solution_1 {
public:


    vector<int> blacklist_steps;
    vector<int> sorted_blacklist;
    int upper_range;
    int curr_step, result, temp;

    Solution(int N, vector<int>& blacklist) {
        int length = blacklist.size();
        upper_range = N - length - 1;

        sorted_blacklist.reserve(blacklist.size());
        for (int i = 0; i < blacklist.size(); i++) {
            sorted_blacklist.push_back(blacklist[i]);
        }
        if (sorted_blacklist.size() > 1) {
            sort(sorted_blacklist.begin(), sorted_blacklist.end());
        }

        blacklist_steps.reserve(N);
        cout << "~1\n";

        int j = 0;

        if (sorted_blacklist.size() > 0) {
            if (sorted_blacklist[0] == 0) {
                blacklist_steps.push_back(1);
                j++;
            }
            else {
                blacklist_steps.push_back(0);
            }
        }
        else {
            blacklist_steps[0] = 0;
        }

        cout << "~2\n";

        for (int i = 1; i < N; i++) {
            if ((i + 1)%10000000 == 0) {cout << "i = " << i << "\n";}
            if ((j < sorted_blacklist.size())&&(i == sorted_blacklist[j])){
                blacklist_steps.push_back(blacklist_steps[i - 1] + 1);
                j++;
            }
            else {
                blacklist_steps.push_back(blacklist_steps[i - 1]);
            }
        }

        /*cout << "blacklist_steps:\n";
        for (int i = 0; i < blacklist_steps.size(); i++) {cout << blacklist_steps[i] << " ";}
        cout << "\n";*/

        srand(time(0));
    }

    int pick() {
        curr_step = 0;
        result = rand()%(upper_range + 1);
        if (blacklist_steps[0] == 1) {
            result++;
        }
        while ((result < blacklist_steps.size())&&(blacklist_steps[result] > blacklist_steps[curr_step])) {
            temp = curr_step;
            curr_step = result;
            result += blacklist_steps[result] - blacklist_steps[temp];
        }
        return result;
    }




};

class Solution_1_1 {
public:

    vector<int> sorted_blacklist;
    int upper_range;
    int curr_step, result, temp;

    Solution(int N, vector<int>& blacklist) {
        int length = blacklist.size();
        upper_range = N - length - 1;
        sorted_blacklist.reserve(length);
        for (int i = 0; i < blacklist.size(); i++) {sorted_blacklist.push_back(blacklist[i]);}
        sort(sorted_blacklist.begin(), sorted_blacklist.end());
        srand(time(0));
    }

    int pick() {
        curr_step = 0;
        result = rand()%(upper_range + 1);
        if ((sorted_blacklist.size() > 0)&&(result >= sorted_blacklist[0])) {
            curr_step = 0;
        }
        return result;
    }

    int find_position(vector<int> &a, int num, int &existed){
        int length = a.size(), index;
        if(num < a[0]){
            index = -1, existed = 0;
        }
        else if(num >= a[length - 1]){
            index = length - 1;
            existed = (num > a[length - 1])? 0: 1;
        }
        else{
            for(int left = 0, right = length - 1, mid = (left + right)/2;;){
                if(num == a[left]){
                    index = left, existed = 1;
                    break;
                }
                else if(num == a[right]){
                    index = right, existed = 1;
                    break;
                }
                else if((left + 1 == right)&&(num > a[left])&&(num < a[right])){
                    index = left, existed = 0;
                    break;
                }
                if(a[mid] >= num){
                    right = mid;
                }
                else if(a[mid] < num){
                    left = mid;
                }
                mid = (left + right)/2;
            }
        }
        return index;
    }

};


class Solution_1_2 {
public:

    vector<int> sorted_blacklist;
    vector<pair<int, int>> available_ranges;
    int upper_range;
    int remains, result, temp;

    Solution(int N, vector<int>& blacklist) {
        int length = blacklist.size();
        upper_range = N - length - 1;

        sorted_blacklist.reserve(length);
        for (int i = 0; i < blacklist.size(); i++) {sorted_blacklist.push_back(blacklist[i]);}
        sort(sorted_blacklist.begin(), sorted_blacklist.end());

        if (sorted_blacklist.size() == 0) {
            available_ranges.push_back({0, N - 1});
        }
        else {
            for (int i = 0, j = 0; j < sorted_blacklist.size(); j++) {
                //cout << "i = " << i << ", j = " << j << "\n";
                if (sorted_blacklist[j] > i) {
                    available_ranges.push_back({i, sorted_blacklist[j] - 1});
                    i = sorted_blacklist[j] + 1;
                }
                else {
                    i++;
                }
            }
            if (sorted_blacklist[sorted_blacklist.size() - 1] < N - 1) {
                available_ranges.push_back({sorted_blacklist[sorted_blacklist.size() - 1] + 1, N - 1});
            }
            /*for (int i = 0; i < available_ranges.size(); i++) {
                cout << available_ranges[i].first << " " << available_ranges[i].second << "\n";
            }*/
        }

        srand(time(0));
    }

    int pick() {
        remains = 0;
        result = rand()%(upper_range + 1);
        if (((available_ranges[0].first == 0)&&(result >= available_ranges[0].second))||(available_ranges[0].first > 0)) {
            result -= available_ranges[0].first;
            for (int i = 0; i < available_ranges.size(); i++){}
        }
        return result;
    }

    int find_position(vector<int> &a, int num, int &existed){
        int length = a.size(), index;
        if(num < a[0]){
            index = -1, existed = 0;
        }
        else if(num >= a[length - 1]){
            index = length - 1;
            existed = (num > a[length - 1])? 0: 1;
        }
        else{
            for(int left = 0, right = length - 1, mid = (left + right)/2;;){
                if(num == a[left]){
                    index = left, existed = 1;
                    break;
                }
                else if(num == a[right]){
                    index = right, existed = 1;
                    break;
                }
                else if((left + 1 == right)&&(num > a[left])&&(num < a[right])){
                    index = left, existed = 0;
                    break;
                }
                if(a[mid] >= num){
                    right = mid;
                }
                else if(a[mid] < num){
                    left = mid;
                }
                mid = (left + right)/2;
            }
        }
        return index;
    }

};


// NO, performance of this is FAR FROM GOOD ENOUGH
//good job!!! use little memory while being some of the fastest!!!
/*Explanation:

record, from the back of the range, available ranges

generate normal random numbers with ranges same as total available numbers

if rand hit blacklist items,
say, hit the n-th (counted from 0th) of sorted_blacklist,
(if counted from 1st then this will be (n+1)th)

then count, in projected_ranges,
from backward to forward, to the n-th number in AVAILABLE RANGES
return this number

*/

class Solution {
public:

    vector<int> sorted_blacklist;
    vector<pair<int, int>> projected_ranges;
    int upper_range;
    int result, index, existed, remains;

    Solution(int N, vector<int>& blacklist) {
        int length = blacklist.size();
        upper_range = N - length - 1;

        sorted_blacklist.reserve(length);
        for (int i = 0; i < blacklist.size(); i++) {sorted_blacklist.push_back(blacklist[i]);}
        sort(sorted_blacklist.begin(), sorted_blacklist.end());

        for (int i = sorted_blacklist.size() - 1, j = N - 1, counter = 0; i >= 0; i--) {
            if (counter == sorted_blacklist.size()) {break;}
            if (sorted_blacklist[i] < j) {
                projected_ranges.push_back({sorted_blacklist[i] + 1, j});
                j = sorted_blacklist[i] - 1;
                counter += j - sorted_blacklist[i];
            }
            else {
                j--;
            }
        }

        /*cout << "projected_ranges:\n";
        for (int i = 0; (projected_ranges.size() > 0)&&(i < projected_ranges.size()); i++) {
            cout << projected_ranges[i].first << " " << projected_ranges[i].second << "\n";
        }
        cout << "\n";*/

        srand(time(0));
    }

    int pick() {
        result = rand()%(upper_range + 1);

        //cout << "original result = " << result << "\n";

        if (sorted_blacklist.size() > 0) {
            index = find_position(sorted_blacklist, result, existed);

            if (existed == 1) {
                remains = index + 1;
                //cout << "remains = " << remains << "\n";
                for (int i = 0; i < projected_ranges.size(); i++) {
                    if (projected_ranges[i].second - projected_ranges[i].first + 1 >= remains) {
                        result = projected_ranges[i].second - remains + 1;
                        break;
                    }
                    else {
                        remains -= projected_ranges[i].second - projected_ranges[i].first + 1;
                        //cout << "remains = " << remains << "\n";
                    }
                }
            }
        }

        //cout << "result = " << result << "\n\n";

        return result;
    }

    int find_position(vector<int> &a, int num, int &existed){
        int length = a.size(), index;
        if(num < a[0]){
            index = -1, existed = 0;
        }
        else if(num >= a[length - 1]){
            index = length - 1;
            existed = (num > a[length - 1])? 0: 1;
        }
        else{
            for(int left = 0, right = length - 1, mid = (left + right)/2;;){
                if(num == a[left]){
                    index = left, existed = 1;
                    break;
                }
                else if(num == a[right]){
                    index = right, existed = 1;
                    break;
                }
                else if((left + 1 == right)&&(num > a[left])&&(num < a[right])){
                    index = left, existed = 0;
                    break;
                }
                if(a[mid] >= num){
                    right = mid;
                }
                else if(a[mid] < num){
                    left = mid;
                }
                mid = (left + right)/2;
            }
        }
        return index;
    }

};



class Solution_try_new_one {
public:
    int must_be_no_larger_than, initial_rand;
    unordered_map<int, int> blacklist_map;
    vector<int> mapping_black_list_to_later_range;

    Solution_try_new_one(int N, vector<int>& blacklist) {
        must_be_no_larger_than = N - blacklist.size() - 1;
        mapping_black_list_to_later_range.reserve(blacklist.size());

        sort(blacklist.begin(), blacklist.end());

        if (blacklist.size() == 0 || (blacklist.size() > 0 && blacklist[0] > must_be_no_larger_than)) {

        }

        else {
            for (int i = 0; i < blacklist.size(); i++) { blacklist_map.insert({blacklist[i], -1}); }

            for (int i = 0, left = must_be_no_larger_than + 1; i < blacklist.size(); i++) {
                while (blacklist_map.find(left) != blacklist_map.end()) { left++; }

                blacklist_map.erase(blacklist_map.find(blacklist[i]));

                blacklist_map.insert({blacklist[i], mapping_black_list_to_later_range.size()});

                mapping_black_list_to_later_range.push_back(left);

                left++;
            }
        }
    }

    int pick() {
        initial_rand = rand() % (must_be_no_larger_than + 1);

        if (blacklist_map.find(initial_rand) != blacklist_map.end()) {
            initial_rand = mapping_black_list_to_later_range[blacklist_map[initial_rand]];
        }

        return initial_rand;
    }
};


class Solution_try_new_one_1 {
public:
    int must_be_no_larger_than, temp, i;
    unordered_map<int, int> blacklist_map;

    Solution(int N, vector<int>& blacklist) {
        must_be_no_larger_than = N - blacklist.size();

        sort(blacklist.begin(), blacklist.end());

        if (blacklist.size() > 0 && blacklist[0] < must_be_no_larger_than) {
            for (i = 0; i < blacklist.size(); i++) { blacklist_map.insert({blacklist[i], -1}); }

            for (i = 0, temp = must_be_no_larger_than; i < blacklist.size(); i++) {
                while (blacklist_map.find(temp) != blacklist_map.end()) { temp++; }

                blacklist_map.erase(blacklist_map.find(blacklist[i]));

                blacklist_map.insert({blacklist[i], temp});

                temp++;
            }
        }
    }

    int pick() {
        temp = rand() % must_be_no_larger_than;

        if (blacklist_map.find(temp) != blacklist_map.end()) {
            temp = blacklist_map[temp];
        }

        return temp;
    }
};





/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(N, blacklist);
 * int param_1 = obj->pick();
 */

int main(){
    srand(time(0)); int N = 100000000, blacklist_length = 10000, temp;
    //cout << "N = " << N << ", blacklist_length = " << blacklist_length << "\n";
    vector<int> blacklist;

    auto sp1 = chrono::steady_clock::now(); auto ep1 = chrono::steady_clock::now(); auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now(); auto ep2 = chrono::steady_clock::now(); auto dif2 = ep2 - sp2;
    vector<int> counter1(N, 0); vector<int> counter2(N, 0);
    //int counter1[N]; int counter2[N]; for (int i = 0; i < N; i++) { counter1[i] = 0, counter2[i] = 0; }
//rand()%(upper_range - lower_range + 1) + lower_range
for (int m = 1; m <= 100; m++) { if (m % 10 == 0) { cout << "m = " << m << "\n"; }
    unordered_set<int> record;

    for (int i = 0; i < blacklist_length; i++) {
        temp = rand()%((N - 1) - 0 + 1) + 0;
        while (record.find(temp) != record.end()) {
            temp = rand()%((N - 1) - 0 + 1) + 0;
        }
        record.insert(temp);
        blacklist.push_back(temp);
    }
    record.clear();

    /*blacklist.push_back(0);
    for (int i = 1; i < blacklist_length; i++) {
        temp = rand()%(3 - 1 + 1) + 1;//1 to 3
        blacklist.push_back(temp + blacklist[i - 1]);
    }
    for (int i = 0; i < blacklist.size(); i++) {cout << blacklist[i] << " ";}cout << "\n";
    */
    vector<int> b1(blacklist);vector<int> b2(blacklist);

    sp1 = chrono::steady_clock::now();
    Solution* wtf1 = new Solution(N, b1);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;

    sp2 = chrono::steady_clock::now();
    Solution_try_new_one* wtf2 = new Solution_try_new_one(N, b2);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;

    for (int i = 0, s; i < 2000000; i++) {
        sp1 = chrono::steady_clock::now();
        s = wtf1->pick();
        ep1 = chrono::steady_clock::now();
        dif1 += ep1 - sp1;
        counter1[s]++;

        sp2 = chrono::steady_clock::now();
        s = wtf2->pick();
        ep2 = chrono::steady_clock::now();
        dif2 += ep2 - sp2;
        counter2[s]++;
    }

    /*cout << "\n\n";
    for (int i = 0; i < N; i++) {
        //cout << "counter1[" << i << "] = " << counter1[i] << "\n";
        cout << counter1[i] << " ";
    }
    cout << "\n\n";
    for (int i = 0; i < N; i++) {
        //cout << "counter2[" << i << "] = " << counter2[i] << "\n";
        cout << counter2[i] << " ";
    }
    cout << "\n\n";*/

    /*int anything_wrong = 0;
    for (int i = 0; i < N; i++) {
        if (counter1[i] == 0 || counter2[i] == 0) {
            if (counter1[i] != counter2[i]) {
                cout << "counter1[" << i << "] = " << counter1[i] << "\n";
                cout << "counter2[" << i << "] = " << counter2[i] << "\n";
                anything_wrong = 1;
                break;
            }
        }

        else {
            temp = counter1[i] - counter2[i];
            if (temp != 0) { temp = counter1[i] / temp; }
            if ((temp < 0 && temp > -4) || (temp > 0 && temp < 4)) {
                cout << "counter1[" << i << "] = " << counter1[i] << "\n";
                cout << "counter2[" << i << "] = " << counter2[i] << "\n";
                anything_wrong = 1; break;
            }
        }
    }

    //if (anything_wrong == 0) { cout << "good\n"; } else { cout << "something is wrong\n"; }

    if (anything_wrong != 0) { cout << "something is wrong\n"; break; }*/
blacklist.clear();}


cout << duration <double, milli> (dif1).count() << " ms" << "\n";
cout << duration <double, milli> (dif2).count() << " ms" << "\n";

    return 0;
}




