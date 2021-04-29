/*962. Maximum Width Ramp
Medium

Given an array A of integers, a ramp is a tuple (i, j) for which i < j and A[i] <= A[j].
The width of such a ramp is j - i.

Find the maximum width of a ramp in A.

If one doesn't exist, return 0.

Input: [6,0,8,2,1,5]
Output: 4
Explanation:
The maximum width ramp is achieved at (i, j) = (1, 5): A[1] = 0 and A[5] = 5.

Input: [9,8,1,0,1,9,4,0,4,1]
Output: 7
Explanation:
The maximum width ramp is achieved at (i, j) = (2, 9): A[2] = 1 and A[9] = 1.

Note:
    2 <= A.length <= 50000
    0 <= A[i] <= 50000
*/

/*
class Solution {
public:
    int maxWidthRamp(vector<int>& A) {

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

int maxWidthRamp_other_people(vector<int>& A) {

    /*how to think??:-
    If we observe carefully , then there is sort of trade off between smallest element and it's distance
    So 2 factors to be considered are:-
    1) Distance
    2) Value
    */

    //std::ios::sync_with_stdio(false);
    //cin.tie(NULL);
    //cout.tie(NULL);

     int n = A.size();

    int suff[n] ;

     suff[n - 1] = A[n - 1];


     for(int i = n - 2 ; i>=0 ;i--){

         suff[i] = max(suff[i + 1] , A[i]);
     }


     int left = 0 ,right = 0 , ans = 0;


     while(right < n){

         while(left < right && A[left] > suff[right])left++;

         ans = max(ans , right - left);

         right++;
     }


    return ans;

}

int maxWidthRamp_other_people_2(vector<int>& A) {
    int n=A.size();
    vector<int> leftMin(n);
    vector<int> rightMax(n);
    int minm=INT_MAX;
    for(int i=0;i<A.size();i++){
        minm=min(minm,A[i]);
        leftMin[i]=minm;
    }
    int maxm=INT_MIN;
    for(int i=A.size()-1;i>=0;i--){
        maxm=max(maxm,A[i]);
        rightMax[i]=maxm;
    }

    int i=0,j=0;
    int maxWidth=0;
    while(i<n and j<n){

        if(leftMin[i]<=rightMax[j])
        {
            maxWidth=max(maxWidth,j-i);
            j++;
        }
        else i++;
    }
    return maxWidth;
}

int maxWidthRamp_other_people_3(vector<int>& A) {
  vector<int>starts;
  starts.push_back(0);
  for (int i=1; i<A.size(); i++) {
    if (A[i]<A[starts.back()]) starts.push_back(i);
  }
  int maxRamp=0;
  for (int i=A.size()-1; i>=0 && !starts.empty(); i--) {
    while (!starts.empty() && A[starts.back()]<=A[i]) {
      maxRamp=max(maxRamp,i-starts.back());
      starts.pop_back();
    }
  }
  return maxRamp;
}

int maxWidthRamp_other_people_4(vector<int>& A) {
    int n=A.size(), res=0;
    stack<int> s;
    for(int i=0; i<n; ++i) {
        if(s.empty() || A[s.top()]>A[i]) s.push(i);
    }
    for(int i=n-1; i>=0; --i) {
        while(!s.empty() && A[s.top()]<=A[i]) {
            res = max(res, i-s.top()); s.pop();
        }
    }
    return res;
}

int maxWidthRamp_other_people_5(vector<int>& A) {
    int ACount = A.size();
    stack<int> AVallueDeascendingIndexStack;
    for (int i = 0; i < ACount; ++i) {
        if (AVallueDeascendingIndexStack.empty() || A[AVallueDeascendingIndexStack.top()] >= A[i]) {
            AVallueDeascendingIndexStack.push(i);
        }
    }
    int answerForMaxRamp = 0;
    for (int i = ACount - 1; i >= 0; --i) {
        while (!AVallueDeascendingIndexStack.empty() && A[AVallueDeascendingIndexStack.top()] <= A[i]) {
            answerForMaxRamp = max(answerForMaxRamp, i - AVallueDeascendingIndexStack.top());
            AVallueDeascendingIndexStack.pop();
        }
    }
    return answerForMaxRamp;
}

int maxWidthRamp_other_people_6(vector<int>& A) {
    stack<int>s;
    s.push(0);
    int res=0,n=A.size();
    for(int i=1;i<n-1;i++)
    {
        if(A[i]<A[s.top()])
            s.push(i);
    }
    for(int i=n-1;i>=1;i--)
    {
        if(!s.size())
            break;
        while(s.size()&&A[s.top()]<=A[i])
        {
            res=max(res,i-s.top());
            s.pop();
        }
    }
    return res;
}

void merge_sort (int a[], int index[], int length) {
    int b[length]; for (int i = 0; i < length; i++) { b[i] = a[i]; }
    int index_1[length]; for (int i = 0; i < length; i++) { index_1[i] = index[i]; }

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        b[k] = a[i];
                        index_1[k] = index[i];
                        i++;
                    }

                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) { break; }

                        else {
                            b[k] = a[i];
                            index_1[k] = index[i];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k] = a[j];
                        index_1[k] = index[j];
                        j++, j_step++;
                    }

                    else if (a[i] <= a[j]) {
                        b[k] = a[i];
                        index_1[k] = index[i];
                        i++, i_step++;
                    }

                    else if (a[i] > a[j]) {
                        b[k] = a[j];
                        index_1[k] = index[j];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 0;
        }

        else if (from_a_to_b == 0) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        a[k] = b[i];
                        index[k] = index_1[i];
                        i++;
                    }

                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) {
                            break;
                        }

                        else {
                            a[k] = b[i];
                            index[k] = index_1[i];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k] = b[j];
                        index[k] = index_1[j];
                        j++, j_step++;
                    }

                    else if (b[i] <= b[j]) {
                        a[k] = b[i];
                        index[k] = index_1[i];
                        i++, i_step++;
                    }

                    else if (b[i] > b[j]) {
                        a[k] = b[j];
                        index[k] = index_1[j];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 1;
        }
    }

    if (from_a_to_b == 0) {
        for (int i = 0; i < length; i++) {
            a[i] = b[i];
            index[i] = index_1[i];
        }
    }
}


//    2 <= A.length <= 50000
//    0 <= A[i] <= 50000

int maxWidthRamp_1_0(vector<int>& A) {
    int length = A.size();
    int a_array[length];
    int index[length];
    for (int i = 0; i < length; i++) { a_array[i] = A[i], index[i] = i; }

    merge_sort(a_array, index, length);

    //  for (int i = 0; i < length; i++) { cout << index[i] << " "; } cout << "\n";

    int min_idx = index[0];
    int min_so_far[length - 1];// min_so_far[0] = -1;

    for (int i = 0; i < length - 1; i++) {
        if (index[i] < min_idx) { min_idx = index[i]; }
        min_so_far[i] = min_idx;
    }

    //  for (int i = 0; i < length; i++) { cout << min_so_far[i] << " "; } cout << "\n";

    int result = (index[1] - min_so_far[0] > 0)? index[1] - min_so_far[0]: 0;
    for (int i = 2, temp; i < length; i++) {
        temp = index[i] - min_so_far[i - 1];
        if (temp > result) { result = temp; }
    }

    return result;
    }

int maxWidthRamp_1_1(vector<int>& A) {
    int length = A.size();
    int a_array[length];
    int index[length];
    for (int i = 0; i < length; i++) { a_array[i] = A[i], index[i] = i; }

    merge_sort(a_array, index, length);

    int min_idx = index[0];
    int result = (index[1] - index[0] > 0)? index[1] - index[0]: 0;

    for (int i = 1, temp; i < length - 1; i++) {
        if (index[i] < min_idx) { min_idx = index[i]; }
        temp = index[i + 1] - min_idx;
        if (temp > result) { result = temp; }
    }

    return result;
}



int maxWidthRamp_1_1_1(vector<int>& A) {
    int length = A.size();
    if (A[0] <= A[length - 1]) { return length - 1; }
    int a_array[length];
    int index[length];
    for (int i = 0; i < length; i++) { a_array[i] = A[i], index[i] = i; }

    merge_sort(a_array, index, length);

    int min_idx = index[0];
    int result = (index[1] - index[0] > 0)? index[1] - index[0]: 0;

    for (int i = 1, temp; i < length - 1; i++) {
        if (index[i] < min_idx) { min_idx = index[i]; }
        temp = index[i + 1] - min_idx;
        if (temp > result) { result = temp;}
    }

    return result;
}

// too slow in extreme cases
int maxWidthRamp_2(vector<int>& A) {
    int length = A.size(), curr_length = length - 1, right_wall;
    bool found = 0;

    while ((found == 0) && (curr_length > 0)) {
        right_wall = length - curr_length;

        for (int i = 0; i < right_wall; i++) {
            if (A[i] <= A[i + curr_length]) {
                found = 1; break;
            }
        }

        curr_length--;
    }

    if (found == 1) { curr_length++; }

    return curr_length;
}



// improved binary search. decent, but not fast enough
//  no, this is fast enough
int maxWidthRamp_2_1(vector<int>& A) {
    int length = A.size();
    if (A[0] <= A[length - 1]) { return length - 1; }
    //int test = 0;

    int left, right;
    int max_val_so_far_from_right_to_left[length];
    int min_val_so_far_from_left_to_right[length];

    left = A[0];
    for (int i = 0; i < length - 1; i++) {
        if (A[i] < left) { left = A[i]; }
        min_val_so_far_from_left_to_right[i] = left;
    }
    //min_val_so_far_from_left_to_right[length - 1] = -1;

    right = A[length - 1];
    for (int i = length - 1; i > 0; i--) {
        if (A[i] > right) { right = A[i]; }
        max_val_so_far_from_right_to_left[i] = right;
    }
    //max_val_so_far_from_right_to_left[0] = -1;

    int mid, right_wall;
    left = 0, right = length - 1;
    bool found;

    /*if (test > 0) {
        cout << "\nmin_val_so_far_from_left_to_right:\n";
        for (int i = 0; i < length; i++) {
            cout << min_val_so_far_from_left_to_right[i] << " ";
        }
        cout << "\nmax_val_so_far_from_right_to_left\n";
        for (int i = 0; i < length; i++) {
            cout << max_val_so_far_from_right_to_left[i] << " ";
        }

        cout << "\n\nleft = " << left << ", right = " << right << "\n";
    }*/

    while (left < right) {
        mid = left + (right - left) / 2;
        right_wall = length - mid;
        found = 0;

        //if (test > 0) { cout << "\nmid = " << mid << ", right_wall = " << right_wall << "\n"; }
        for (int i = 0; i < right_wall; i++) {
            if (min_val_so_far_from_left_to_right[i] <= max_val_so_far_from_right_to_left[i + mid]) {
                found = 1;
                break;
            }
        }

        if (found == 1) { left = mid + 1; }
        else { right = mid; }

        /*if (test > 0) {
            cout << "found = " << found;
            cout << "\nleft = " << left << ", right = " << right << "\n";
            if (test > 10) { cout << "done\n"; break; }
            test++;
        }*/
    }

    return left - 1;
}



int maxWidthRamp_3(vector<int>& A) {
    int length = A.size();
    map<int, int> val_to_idx;
    val_to_idx.insert({A[length - 1], length - 1});
    int curr_max = 0;

    for (int i = length - 2; i >= 0; i--) {
        auto find_val = val_to_idx.find(A[i]);
    }

    return curr_max;
}


int main(){
    srand(time(0));int length = 50, lower_range = 0, upper_range = 10000, display = 0, input = 1;
    vector<int> wtf;

    auto sp1 = chrono::steady_clock::now();auto ep1 = chrono::steady_clock::now();auto dif1 = ep1 - sp1;
    auto sp2 = chrono::steady_clock::now();auto ep2 = chrono::steady_clock::now();auto dif2 = ep2 - sp2;
    auto sp3 = chrono::steady_clock::now();auto ep3 = chrono::steady_clock::now();auto dif3 = ep3 - sp3;
    auto sp4 = chrono::steady_clock::now();auto ep4 = chrono::steady_clock::now();auto dif4 = ep4 - sp4;
    auto sp5 = chrono::steady_clock::now();auto ep5 = chrono::steady_clock::now();auto dif5 = ep5 - sp5;
    auto sp6 = chrono::steady_clock::now();auto ep6 = chrono::steady_clock::now();auto dif6 = ep6 - sp6;
    auto sp7 = chrono::steady_clock::now();auto ep7 = chrono::steady_clock::now();auto dif7 = ep7 - sp7;
    auto sp8 = chrono::steady_clock::now();auto ep8 = chrono::steady_clock::now();auto dif8 = ep8 - sp8;

for (int m = 1; m <= 10000; m++) {if (m % 1000 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){
        wtf.reserve(length);
        for(int i = 0; i < length; i++){
            wtf.push_back(rand()%(upper_range - lower_range + 1) + lower_range);
        }
    }
    if (display == 1){
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    //cout << "wtf.size() = " << wtf.size() << "\n";
    vector<int> wtf1(wtf); vector<int> wtf2(wtf); vector<int> wtf3(wtf); vector<int> wtf4(wtf);
    vector<int> wtf5(wtf); vector<int> wtf6(wtf); vector<int> wtf7(wtf); vector<int> wtf8(wtf);

    sp1 = chrono::steady_clock::now();
    int s = maxWidthRamp_1_1_1(wtf1);
    ep1 = chrono::steady_clock::now();
    dif1 += ep1 - sp1;
    //cout << "s = " << s << "\n";

    sp2 = chrono::steady_clock::now();
    int ss = maxWidthRamp_2_1(wtf2);
    ep2 = chrono::steady_clock::now();
    dif2 += ep2 - sp2;
    //cout << "ss = " << ss << "\n";

    sp5 = chrono::steady_clock::now();
    int sssss = maxWidthRamp_other_people(wtf3);
    ep5 = chrono::steady_clock::now();
    dif5 += ep5 - sp5;

    sp3 = chrono::steady_clock::now();
    int sss = maxWidthRamp_other_people_2(wtf4);
    ep3 = chrono::steady_clock::now();
    dif3 += ep3 - sp3;
    //cout << "sss = " << sss << "\n";

    sp4 = chrono::steady_clock::now();
    int ssss = maxWidthRamp_other_people_3(wtf5);
    ep4 = chrono::steady_clock::now();
    dif4 += ep4 - sp4;
    //cout << "ssss = " << ssss << "\n";

    sp6 = chrono::steady_clock::now();
    int ssssss = maxWidthRamp_other_people_4(wtf6);
    ep6 = chrono::steady_clock::now();
    dif6 += ep6 - sp6;
    //cout << "ssss = " << ssss << "\n";

    sp7 = chrono::steady_clock::now();
    int sssssss = maxWidthRamp_other_people_5(wtf7);
    ep7 = chrono::steady_clock::now();
    dif7 += ep7 - sp7;
    //cout << "ssss = " << ssss << "\n";

    sp8 = chrono::steady_clock::now();
    int ssssssss = maxWidthRamp_other_people_6(wtf7);
    ep8 = chrono::steady_clock::now();
    dif8 += ep8 - sp8;

    if ((s != sss) || (ss != sss) || (ss != ssss)) {
        cout << "m = " << m << "\n";
        cout << "s = " << s << "\n";
        cout << "ss = " << ss << "\n";
        cout << "sss = " << sss << "\n";
        cout << "ssss = " << ssss << "\n";
        cout << "\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << wtf[i];if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
        break;
    }

wtf.clear();
}
cout << duration <double, milli> (dif1).count() << " ms" << "\n";
cout << duration <double, milli> (dif2).count() << " ms" << "\n";
cout << duration <double, milli> (dif5).count() << " ms" << "\n";
cout << duration <double, milli> (dif3).count() << " ms" << "\n";
cout << duration <double, milli> (dif4).count() << " ms" << "\n";
cout << duration <double, milli> (dif6).count() << " ms" << "\n";
cout << duration <double, milli> (dif7).count() << " ms" << "\n";
cout << duration <double, milli> (dif8).count() << " ms" << "\n";

    return 0;
}




