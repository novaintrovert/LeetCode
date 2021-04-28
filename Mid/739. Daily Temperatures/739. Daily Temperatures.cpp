/*739. Daily Temperatures
Medium

Given a list of daily temperatures T,
return a list such that,
for each day in the T,
tells you how many days you would have to wait until a warmer temperature.

If there is no future day for which this is possible,
put 0 instead.

For example,
given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73],
your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note:
The length of temperatures will be in the range [1, 30000].
Each temperature will be an integer in the range [30, 100].
*/

/*
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {

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
#include<cstring>

using namespace std;
using namespace chrono;

vector<int> dailyTemperatures_others(vector<int>& T) {
    vector<int> res(T.size());
    for (int i=T.size()-1;i>=0;i--)
    {
        int j=i+1;
        while(j<T.size() && T[i] >= T[j])
        {
            if (res[j] > 0) j += res[j];
            else j = T.size();
        }
        if (j < T.size()) res[i] = j - i;
    }
    return res;
}

vector<int> dailyTemperatures_brute(vector<int>& T) {
    int length = T.size();
    vector<int> result (length, 0);
    result[length - 1] = 0;
    for (int i = 0, found, counter; i < length - 1; i++) {
        found = 0, counter = 0;

        for (int j = i + 1; j < length; j++) {
            counter++;
            if (T[j] > T[i]) {
                found = 1;
                result[i] = counter;
                break;
            }
        }

        if (found == 0) { result[i] = 0; }
    }
    return result;
}

vector<int> dailyTemperatures_slow(vector<int>& T) {
    int length = T.size();

    multimap<int, int> unfinished_business;
    vector<int> processing(length, -1);

    for (int i = 0; i < length; i++) {
        //cout << "i = " << i << "\n";
        ///cout << "T[i] = " << T[i] << "\n";
        if (i == length - 1) {processing[i] == 0;}
        else {
            if (T[i] < T[i + 1]){
                processing[i] = i + 1;

                if (unfinished_business.size() > 0) {
                    auto find_it = unfinished_business.lower_bound(T[i + 1]);

                    if (find_it != unfinished_business.begin()) {
                        for (auto j = unfinished_business.begin(), k = j; j != find_it; ) {
                            //cout << j->first << " " << j->second << "\n";
                            processing[j->second] = i + 1;
                            //cout << "processing[" << j->second << "] = " << processing[j->second] << "\n";
                            ++j;
                            unfinished_business.erase(k);
                            k = j;
                        }
                    }
                }
            }

            else {
                unfinished_business.insert({T[i], i});
                //cout << "\nunfinished_business.insert({" << T[i] << ", " << i <<"})";
            }
        }
        /*cout << "\nunfinished_business: ";
        for (auto m = unfinished_business.begin(); m != unfinished_business.end(); ++m) {
            cout << m->first << " " << m->second << ", ";
        }
        cout << "\n\n";*/
    }

    vector<int> result (length, -1);

    for (int i = 0; i < length; i++) {
        if (processing[i] >= 0) { result[i] = processing[i] - i; }
        else { result[i] = 0; }
    }

    return result;
}

vector<int> dailyTemperatures_1_0(vector<int>& T) {
    int length = T.size();
    vector<int> result (length, 0);
    stack<int> irregularity;

    for (int i = 0; i < length - 1; i++) {
        if (T[i] < T[i + 1]){
            result[i] = 1;

            while (!irregularity.empty() && T[i + 1] > T[irregularity.top()]) {
                result[irregularity.top()] = i - irregularity.top() + 1;

                //cout << "result[" << irregularity.top() << "] = " << i - irregularity.top() + 1<< "\n";
                irregularity.pop();
            }
        }

        else { irregularity.push(i); }

        //for (int j = 0; j < length; j++) { cout << result[j] << " "; } cout << "\n";
    }

    if (irregularity.size() > 0) {
        while (!irregularity.empty() && T[length - 1] > T[irregularity.top()]) {
            result[irregularity.top()] = length - 1 - irregularity.top();
            irregularity.pop();
        }
    }
    //for (int j = 0; j < length; j++) { cout << result[j] << " "; } cout << "\n";

    return result;
}

vector<int> dailyTemperatures_1_1(vector<int>& T) {
    int length = T.size();
    stack<int> irregularity;

    for (int i = 0; i < length - 1; i++) {
        if (T[i] < T[i + 1]){
            T[i] = 1;

            while (!irregularity.empty() && T[i + 1] > T[irregularity.top()]) {
                T[irregularity.top()] = i - irregularity.top() + 1;

                //cout << "result[" << irregularity.top() << "] = " << i - irregularity.top() + 1<< "\n";
                irregularity.pop();
            }
        }

        else { irregularity.push(i); }

        //for (int j = 0; j < length; j++) { cout << result[j] << " "; } cout << "\n";
    }

    if (irregularity.size() > 0) {
        while (!irregularity.empty()) {
            if (T[length - 1] > T[irregularity.top()]) {
                T[irregularity.top()] = length - 1 - irregularity.top();
            }

            else { T[irregularity.top()] = 0; }

            irregularity.pop();
        }
    }

    T[length - 1] = 0;
    //for (int j = 0; j < length; j++) { cout << result[j] << " "; } cout << "\n";

    return T;
}


// EXCELLENT
vector<int> dailyTemperatures_1_2(vector<int>& T) {
    int length = T.size();
    int test = 0;
    vector<int> result(length, 0);

    for (int i = length - 2, curr_idx; i >= 0; i--) {
        if (test > 0) {
            cout << "i = " << i << "\n";
            cout << "T[" << i << "] = " << T[i] << "\n";
        }
        if (T[i] < T[i + 1]) {
            if (test > 0) { cout << "~0!\n"; }
            result[i] = 1;
            //cout << "result[" << i << "] = 1\n";
        }

        else {
            if (test > 0) { cout << "~1!\n"; }
            curr_idx = i + 1;
            while (result[curr_idx] != 0 && T[i] >= T[curr_idx]) {
                curr_idx += result[curr_idx];
            }
            if (test > 0) { cout << "curr_idx = " << curr_idx << "\n"; }

            if (T[i] < T[curr_idx]) {
                if (test > 0) {  cout << "~2!\n"; }
                result[i] = curr_idx - i;
            }


            else {
                if (test > 0) { cout << "~3!\n"; }
                result[i] = 0;
            }

        }
        if (test > 0) { cout << "result[" << i << "] = " << result[i] << "\n\n"; }
    }

    return result;
}



//  I WILL MOST LIKELY TO RUN INTO ALL KINDS OF PROBLEMS IF I DO NOT BUILD A BRUTEFORCE & TEST A BIT
//  NO MATTER HOW CONFIDENT I MIGHT HAVE ON THAT ALGORITHM
int main() {
    srand(time(0));int length = 10, lower_range = 0, upper_range = 50, display = 0, input = 1;
    vector<int> wtf;
    // = {73, 74, 75, 71, 69, 72, 76, 73};h

    auto sp1 = chrono::steady_clock::now(); auto ep1 = chrono::steady_clock::now(); auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now(); auto ep2 = chrono::steady_clock::now(); auto dif2 = ep2 - sp2;
    auto sp3 = chrono::steady_clock::now(); auto ep3 = chrono::steady_clock::now(); auto dif3 = ep3 - sp3;
    auto sp4 = chrono::steady_clock::now(); auto ep4 = chrono::steady_clock::now(); auto dif4 = ep4 - sp4;

for (int m = 1, identical; m <= 1000000; m++) {if (m % 100000 == 0) {cout << "m = " << m << "\n";}

    if (input == 1) {
        wtf.reserve(length);
        for (int i = 0; i < length; i++) {
            wtf.push_back(rand() % (upper_range - lower_range + 1) + lower_range);
        }
    }
    if (display == 1) {
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    vector<int> wtf1(wtf);vector<int> wtf2(wtf);vector<int> wtf3(wtf);vector<int> wtf4(wtf);
    sp1 = chrono::steady_clock::now();
    vector<int> s = dailyTemperatures_1_0(wtf1);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;

    sp2 = chrono::steady_clock::now();
    vector<int> ss = dailyTemperatures_1_1(wtf2);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;

    sp4 = chrono::steady_clock::now();
    vector<int> ssss = dailyTemperatures_1_2(wtf4);
    ep4 = chrono::steady_clock::now();
    dif4 += ep4 - sp4;

    sp3 = chrono::steady_clock::now();
    vector<int> sss = dailyTemperatures_others(wtf3);
    ep3 = chrono::steady_clock::now();
    dif3 += ep3 - sp3;

    identical = 1;
    for (int i = 0; i < length; i++) {
        if (s[i] != ssss[i]) { identical = 0; break;}
    }

    if (identical == 0) {
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n\n1_0:\n";
        for (int i = 0; i < s.size(); i++) {
            cout << s[i] << " ";
        }
        cout << "\n\n1_1:\n";
        for (int i = 0; i < ss.size(); i++) {
            cout << ss[i] << " ";
        }
        cout << "\n\nssss:\n";
        for (int i = 0; i < ssss.size(); i++) {
            cout << ssss[i] << " ";
        }
        cout << "\n";
        break;
    }

wtf.clear();}
cout << "   1_0: " << duration <double, milli> (dif1).count() << " ms" << "\n";
cout << "   1_1: " << duration <double, milli> (dif2).count() << " ms" << "\n";
cout << "   1_2: " << duration <double, milli> (dif4).count() << " ms" << "\n";
cout << "others: " << duration <double, milli> (dif3).count() << " ms" << "\n";

    return 0;
}
