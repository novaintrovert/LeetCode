/*4. Median of Two Sorted Arrays
Hard

Given two sorted arrays nums1 and nums2 of size m and n respectively,
return the median of the two sorted arrays.

Follow up: The overall run time complexity should be O(log (m+n)).

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000

Input: nums1 = [], nums2 = [1]
Output: 1.00000

Input: nums1 = [2], nums2 = []
Output: 2.00000

Constraints:
    nums1.length == m
    nums2.length == n
    0 <= m <= 1000
    0 <= n <= 1000
    1 <= m + n <= 2000
    -106 <= nums1[i], nums2[i] <= 106
*/

/*
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

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

/*tried 2 ways: search by value, search by index
so far, only 2 search by value algo worked - which is messy to get it work too, others are ALL MESSY & BUGGY*/



double findMedianSortedArrays_brute (vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    vector<int> shit;shit.reserve(length_1 + length_2);
    for (int i = 0; i < length_1; i++) {shit.push_back(nums1[i]);}
    for (int i = 0; i < length_2; i++) {shit.push_back(nums2[i]);}
    sort(shit.begin(), shit.end());
    double part_1, part_2;
    part_1 = shit[(length_1 + length_2 - 1) / 2];
    part_2 = shit[(length_1 + length_2) / 2];
    //cout << "part_1 = " << part_1 << ", part_2 = " << part_2 << "\n";
    return (part_1 + part_2) / 2;
}


/*double findMedianSortedArrays_NOT_NEAT (vector<int>& nums1, vector<int>& nums2) {
    int 1_length = nums1.size(), 2_length = nums2.size();
    double part_1 = -1, part_2 = -1;

    if ((1_length == 0)||(2_length == 0)) {
        if ((1_length == 0)&&(2_length > 0)) {
            part_1 = nums2[(2_length - 1) / 2], part_2 = nums2[2_length / 2];
        }
        if ((1_length > 0)&&(2_length == 0)) {
            part_1 = nums1[(1_length - 1) / 2], part_2 = nums1[1_length / 2];
        }
        return (part_1 + part_2) / 2;
    }

    double result = 0;
    int found = 0, temp, criteria = (1_length + 2_length - 1) / 2;

    //search according to index
    int 1_left = 0, 1_right = 1_length - 1, 1_mid = 1_left + (1_right - 1_left) / 2;
    int 2_left = 0, 2_right = 2_length - 1, 2_mid = 2_left + (2_right - 2_left) / 2;
    int mid_1s_loc_in_2 = -1, mid_2s_loc_in_1 = -1;

    int front_weight_from_1 = 0, front_weight_from_2 = 0;//, back_weight_from_1 = 0, back_weight_from_2 = 0;



    while (found == 0) {
        if (1_left <= 1_right) {
            1_mid = 1_left + (1_right - 1_left) / 2;
            mid_1s_loc_in_2 = find_position (nums2, nums1[1_mid]);

            temp = 1_mid + mid_1s_loc_in_2 + front_weight_from_2;

            if (temp == (1_length + 2_length) / 2) {

                break;
            }

            if (temp < (1_length + 2_length) / 2) {
                1_left = 1_mid + 1;

                if (1_left > 1_right) {front_weight_from_1 = 1_length;}
            }

            else {1_right = 1_mid - 1;}
        }

        if (2_left <= 2_right) {
            2_mid = 2_left + (2_right - 2_left) / 2;
            mid_2s_loc_in_1 = find_position (nums1, nums2[2_mid]);

            temp = 1_mid + mid_1s_loc_in_2 + front_weight_from_1;

            if (temp == (1_length + 2_length) / 2) {

                break;
            }

            if (temp < (1_length + 2_length) / 2) {
                2_left = 2_mid + 1;

                if (2_left > 2_right) {front_weight_from_2 = 2_length;}
            }

            else {2_right = 2_mid - 1;}
        }
    }

    return (part_1 + part_2) / 2;
}
*/

//search towards the left, or to the right
//this function is used to find the 1st element within vector,
//among a swarm of duplications in a SORTED NON-DECREASING vector
int find_1st_among_duplications(vector<int> &a, int idx, int direction){
    int length = a.size(), index = 0;
    if((idx >= 0)&&(idx < length)){
        int num = a[idx], left = idx, right = idx, scale = 1;
        if (direction < 0){
            while(true){
                if(left - scale >= 0){
                    if(a[left] < num){
                        left = (left + right)/2;
                        scale = right - left;
                    }
                    else if(a[left] >= num){
                        right = left;
                        left -= scale;
                        scale = scale*2;
                    }
                }
                else if(left - scale < 0){
                    if(a[0] == num){
                        index = 0;
                        break;
                    }
                    else if(a[0] < num){
                        scale = scale/2;
                    }
                }
                if((left + 1 == right)&&(a[left] < num)&&(a[right] >= num)){
                    index = right;
                    break;
                }
            }
        }
        else if (direction > 0){
            while(true){
                if(right + scale < length){
                    if(a[right] > num){
                        right = (left + right)/2;
                        scale = right - left;
                    }
                    else if(a[right] <= num){
                        left = right;
                        right += scale;
                        scale = scale*2;
                    }
                }
                else if(right + scale >= length){
                    if(a[length - 1] == num){
                        index = length - 1;
                        break;
                    }
                    else if(a[length - 1] > num){
                        scale = scale/2;
                    }
                }
                if((left + 1 == right)&&(a[left] <= num)&&(a[right] > num)){
                    index = left;
                    break;
                }
            }
        }
    }
    return index;
}

void find_position(vector<int>& nums, int search_val, int &count_smaller, int &count_identical) {
    int length = nums.size();
    int test_timer = -1;
    if ((length == 0)||(search_val < nums[0])) {
        if (test_timer >= 0) {cout << "1\n";}
        count_smaller = 0, count_identical = 0;
    }
    else if (search_val > nums[length - 1]) {
        if (test_timer >= 0) {cout << "2\n";}
        count_smaller = length, count_identical = 0;
    }
    else if ((length == 1)&&(search_val == nums[0])) {
        if (test_timer >= 0) {cout << "3\n";}
        count_smaller = 0, count_identical = 1;
    }
    else {
        int left = 0, right = length - 1, mid, one_more = 1;
        if (test_timer >= 0) {cout << "left = " << left << ", right = " << right << "\n";}
        while (left <= right) {
            mid = left + (right - left) / 2;

            if (nums[mid] < search_val) {left = mid + 1;}

            else if (nums[mid] >= search_val) {right = mid;}

            //else {break;}

            if (one_more == 0) {break;}
            if (left == right) {one_more = 0;}

            if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";}
        }

        if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";}

        if (nums[left] == search_val) {
            int left_boundary;//1st element that is NO LARGER than search_val
            int right_boundary;//last element that is NO LARGER than search_val

            if ((left == 0)||(nums[left - 1] < search_val)) {
                left_boundary = left;
            }
            else {
                left_boundary = find_1st_among_duplications(nums, left, -1);
            }

            if ((left == length - 1)||(nums[left + 1] > search_val)) {
                right_boundary = left;
            }
            else {
                right_boundary = find_1st_among_duplications(nums, left, 1);
            }

            count_smaller = left_boundary, count_identical = right_boundary - left_boundary + 1;
        }

        else {
            count_smaller = left, count_identical = 0;
        }

        /*int left = 0, right = 1, scale = 1;

        //crawling to the right, find the 1st element that is no larger than search_val
        if (nums[left] == search_val) {left_boundary = left;}
        else if (nums[right] >= search_val){left_boundary = right;}
        else {
            while (true) {
                if (nums[right + scale] ){//then nums[left] < search_val

                }
            }

            if () {}
            else {

            }
        }*/
    }
}


//Worked, but...too fat
//CAREFUL ON TRIVIAL CASES!!!
//Passed. Also passed my own 10s of millions of random number tests. Probably ABSOLUTELY correct within given restrictions.
double findMedianSortedArrays_1_0(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    double part_1 = 0, part_2 = 0;

    int is_odd = ((length_1 + length_2) & 1 == 1)? 1: 0;

    int test_timer = -1;

    if ((length_1 == 0)||(length_2 == 0)) {
        if ((length_1 == 0)&&(length_2 > 0)) {
            part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        }
        if ((length_1 > 0)&&(length_2 == 0)) {
            part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        }
        return (part_1 + part_2) / 2;
    }

    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = (length_1 + length_2) / 2;
    if (test_timer >= 0) {
        cout << "length_1 + length_2 = " << length_1 + length_2 << "\n";
        cout << "is_odd = " << is_odd << "\n";
        cout << "criteria = " << criteria << "\n\n";}

    int count_smaller_in_1, count_identical_in_1;
    int count_smaller_in_2, count_identical_in_2;
    int count_smaller, count_identical;

    int left = (nums1[0] <= nums2[0])? nums1[0]: nums2[0];
    int right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];
    int mid, one_more = 1;

    while (left <= right) {
        mid = left + (right - left) / 2;
        if (test_timer >= 0) {cout << "search val = " << mid << "\n\n";}

        if (test_timer >= 0) {cout << "find_position 1\n";}
        find_position(nums1, mid, count_smaller_in_1, count_identical_in_1);

        if (test_timer >= 0) {cout << "find_position 2\n";}
        find_position(nums2, mid, count_smaller_in_2, count_identical_in_2);

        if (test_timer >= 0) {
            cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
            cout << "count_smaller_in_1 = " << count_smaller_in_1 << ", count_identical_in_1 = " << count_identical_in_1 << "\n";
            cout << "count_smaller_in_2 = " << count_smaller_in_2 << ", count_identical_in_2 = " << count_identical_in_2 << "\n\n";
        }

        count_smaller = count_smaller_in_1 + count_smaller_in_2;
        count_identical = count_identical_in_1 + count_identical_in_2;

        if ((count_identical == 0)&&(count_smaller == criteria)) {break;}

        if ((count_identical > 0)&&(count_smaller <= criteria)&&(count_smaller + count_identical > criteria)) {break;}

        else if (count_smaller > criteria) {right = mid;}

        else {left = mid + 1;}
    }

    if (test_timer >= 0) {cout << "count_smaller = " << count_smaller << ", count_identical = " << count_identical << "\n";}

    if (is_odd == 1) {
        if (count_identical > 1) {return mid;}
        if (count_smaller_in_1 == length_1) {return nums2[count_smaller_in_2];}
        if (count_smaller_in_2 == length_2) {return nums1[count_smaller_in_1];}
        else {
            return (nums1[count_smaller_in_1] < nums2[count_smaller_in_2])? nums1[count_smaller_in_1]: nums2[count_smaller_in_2];
        }
    }

    else if ((count_smaller < criteria)&&(count_identical > 1)) {return mid;}

    else {
        int left_candidate_idx_1, right_candidate_idx_1, left_candidate_idx_2, right_candidate_idx_2;

        if (count_smaller_in_1 == 0) {
            //left_candidate_idx_1 = (count_identical_in_1 > 0)? 0: -1;
            left_candidate_idx_1 = -1;
            right_candidate_idx_1 = 0;
        }
        else {
            left_candidate_idx_1 = count_smaller_in_1 - 1;
            if (count_smaller_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {
            //left_candidate_idx_2 = (count_identical_in_2 > 0)? 0: -1;
            left_candidate_idx_2 = -1;
            right_candidate_idx_2 = 0;
        }
        else {
            left_candidate_idx_2 = count_smaller_in_2 - 1;
            if (count_smaller_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {
            cout << "part_1 = " << part_1 << "\n";
            cout << "part_2 = " << part_2 << "\n\n";
        }
    }


/*    int left_candidate_idx_1, right_candidate_idx_1, left_candidate_idx_2, right_candidate_idx_2;

    if (count_identical > 0) {
        if (test_timer >= 0) {cout << "count_identical > 0";}

        if ((count_smaller < criteria)||((count_smaller == criteria)&&(is_odd == 1))) {return mid;}

        else {
            part_2 = mid;

            if (count_smaller_in_1 == 0) {left_candidate_idx_1 = -1;}
            else {left_candidate_idx_1 = count_smaller_in_1 - 1 + is_odd;}
            if (count_smaller_in_2 == 0) {left_candidate_idx_2 = -1;}
            else {left_candidate_idx_2 = count_smaller_in_2 - 1 + is_odd;}

            if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
            else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
            else {
                part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
                nums1[left_candidate_idx_1]: nums2[left_candidate_idx_2];
            }
        }
    }

    else if (is_odd == 1) {
        return (nums1[count_smaller_in_1] < nums2[count_smaller_in_2])? nums1[count_smaller_in_1]: nums2[count_smaller_in_2];
    }

    else {
        if (count_smaller_in_1 == 0) {left_candidate_idx_1 = -1, right_candidate_idx_1 = 0;}
        else {
            left_candidate_idx_1 = count_smaller_in_1 - 1;
            if (count_smaller_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {left_candidate_idx_2 = -1, right_candidate_idx_2 = 0;}
        else {
            left_candidate_idx_2 = count_smaller_in_2 - 1;
            if (count_smaller_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] >= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }
    }
*/
    return (part_1 + part_2) / 2;
}



double findMedianSortedArrays_1_0_1(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    double part_1 = 0, part_2 = 0;

    int is_odd = ((length_1 + length_2) & 1 == 1)? 1: 0;

    int test_timer = -1;

    if ((length_1 == 0)||(length_2 == 0)) {
        if ((length_1 == 0)&&(length_2 > 0)) {
            part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        }
        if ((length_1 > 0)&&(length_2 == 0)) {
            part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        }
        return (part_1 + part_2) / 2;
    }

    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = (length_1 + length_2) / 2;
    if (test_timer >= 0) {
        cout << "length_1 + length_2 = " << length_1 + length_2 << "\n";
        cout << "is_odd = " << is_odd << "\n";
        cout << "criteria = " << criteria << "\n\n";}

    int count_smaller_in_1, count_identical_in_1;
    int count_smaller_in_2, count_identical_in_2;
    int count_smaller, count_identical;

    int left = (nums1[0] <= nums2[0])? nums1[0]: nums2[0];
    int right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];
    int mid, one_more = 1, l, m, r, temp = 0;

    while (left <= right) {
        mid = left + (right - left) / 2;
        if (test_timer >= 0) {cout << "search val = " << mid << "\n\n";}

        if (test_timer >= 0) {cout << "find_position 1\n";}

        if (mid > nums1[length_1 - 1]) {count_smaller_in_1 = length_1, count_identical_in_1 = 0;}
        else if (mid < nums1[0]) {count_smaller_in_1 = 0, count_identical_in_1 = 0;}
        else {
            l = 0, r = length_1 - 1, one_more = 1;
            while (l <= r) {
                m = l + (r - l) / 2;
                if (nums1[m] < mid) {l = m + 1;}
                else {r = m;}

                if (one_more == 0) {break;}
                if (l + 1 >= r) {one_more = 0;}
            }
            count_smaller_in_1 = l;
            if (nums1[l] == mid) {
                count_identical_in_1 = 1;
                if ((l < length_1 - 1)&&(nums1[l + 1] == mid)) {
                    r = length_1 - 1, one_more = 1;
                    while (l <= r) {
                        m = l + (r - l) / 2;
                        if (nums1[m] <= mid) {l = m;}
                        else {r = m - 1;}

                        if (one_more == 0) {break;}
                        if (l + 1 >= r) {one_more = 0;}
                    }
                    if (nums1[r] == nums1[l]) {l = r;}
                    count_identical_in_1 += l - count_smaller_in_1;
                    //cout << "r = " << r << ", temp = " << temp << "\n";
                }

            }
            else {count_identical_in_1 = 0;}
        }


        if (test_timer >= 0) {cout << "find_position 2\n";}

        if (mid > nums2[length_2 - 1]) {count_smaller_in_2 = length_2, count_identical_in_2 = 0;}
        else if (mid < nums2[0]) {count_smaller_in_2 = 0, count_identical_in_2 = 0;}
        else {
            l = 0, r = length_2 - 1, one_more = 1;
            while (l <= r) {
                m = l + (r - l) / 2;
                if (nums2[m] < mid) {l = m + 1;}
                else {r = m;}

                if (one_more == 0) {break;}
                if (l + 1 >= r) {one_more = 0;}
            }
            count_smaller_in_2 = l;
            if (nums2[l] == mid) {
                count_identical_in_2 = 1;
                if ((l < length_2 - 1)&&(nums2[l + 1] == mid)) {
                    r = length_2 - 1, one_more = 1;
                    while (l <= r) {
                        m = l + (r - l) / 2;
                        if (nums2[m] <= mid) {l = m;}
                        else {r = m - 1;}

                        if (one_more == 0) {break;}
                        if (l + 1 >= r) {one_more = 0;}
                    }
                    if (nums2[r] == nums2[l]) {l = r;}
                    count_identical_in_2 += l - count_smaller_in_2;
                    //cout << "r = " << r << ", temp = " << temp << "\n";
                }

            }
            else {count_identical_in_2 = 0;}
        }


        if (test_timer >= 0) {
            cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
            cout << "count_smaller_in_1 = " << count_smaller_in_1 << ", count_identical_in_1 = " << count_identical_in_1 << "\n";
            cout << "count_smaller_in_2 = " << count_smaller_in_2 << ", count_identical_in_2 = " << count_identical_in_2 << "\n\n";
        }

        count_smaller = count_smaller_in_1 + count_smaller_in_2;
        count_identical = count_identical_in_1 + count_identical_in_2;

        if ((count_identical == 0)&&(count_smaller == criteria)) {break;}

        if ((count_identical > 0)&&(count_smaller <= criteria)&&(count_smaller + count_identical > criteria)) {break;}

        else if (count_smaller > criteria) {right = mid;}

        else {left = mid + 1;}
    }

    if (test_timer >= 0) {cout << "count_smaller = " << count_smaller << ", count_identical = " << count_identical << "\n";}

    if (is_odd == 1) {
        if (count_identical > 1) {return mid;}
        if (count_smaller_in_1 == length_1) {return nums2[count_smaller_in_2];}
        if (count_smaller_in_2 == length_2) {return nums1[count_smaller_in_1];}
        else {
            return (nums1[count_smaller_in_1] < nums2[count_smaller_in_2])? nums1[count_smaller_in_1]: nums2[count_smaller_in_2];
        }
    }

    else if ((count_smaller < criteria)&&(count_identical > 1)) {return mid;}

    else {
        int left_candidate_idx_1, right_candidate_idx_1, left_candidate_idx_2, right_candidate_idx_2;

        if (count_smaller_in_1 == 0) {
            //left_candidate_idx_1 = (count_identical_in_1 > 0)? 0: -1;
            left_candidate_idx_1 = -1;
            right_candidate_idx_1 = 0;
        }
        else {
            left_candidate_idx_1 = count_smaller_in_1 - 1;
            if (count_smaller_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {
            //left_candidate_idx_2 = (count_identical_in_2 > 0)? 0: -1;
            left_candidate_idx_2 = -1;
            right_candidate_idx_2 = 0;
        }
        else {
            left_candidate_idx_2 = count_smaller_in_2 - 1;
            if (count_smaller_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {
            cout << "part_1 = " << part_1 << "\n";
            cout << "part_2 = " << part_2 << "\n\n";
        }
    }

    return (part_1 + part_2) / 2;
}


//SERIOUSLY?! No improvements?! Not even a bit?! Are you fucking kidding me?!
double findMedianSortedArrays_1_0_1_no_timer(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    double part_1 = 0, part_2 = 0;

    int is_odd = ((length_1 + length_2) & 1 == 1)? 1: 0;

    //int test_timer = -1;

    if ((length_1 == 0)||(length_2 == 0)) {
        if ((length_1 == 0)&&(length_2 > 0)) {
            part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        }
        if ((length_1 > 0)&&(length_2 == 0)) {
            part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        }
        return (part_1 + part_2) / 2;
    }

    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = (length_1 + length_2) / 2;

    //if (test_timer >= 0) {cout << "length_1 + length_2 = " << length_1 + length_2 << "\nis_odd = " << is_odd << "\ncriteria = " << criteria << "\n\n";}

    int count_smaller_in_1, count_identical_in_1;
    int count_smaller_in_2, count_identical_in_2;
    int count_smaller, count_identical;

    int left = (nums1[0] <= nums2[0])? nums1[0]: nums2[0];
    int right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];
    int mid, one_more = 1, l, m, r, temp = 0;

    while (left <= right) {
        mid = left + (right - left) / 2;
        //if (test_timer >= 0) {cout << "search val = " << mid << "\n\n";}

        //if (test_timer >= 0) {cout << "find_position 1\n";}

        if (mid > nums1[length_1 - 1]) {count_smaller_in_1 = length_1, count_identical_in_1 = 0;}
        else if (mid < nums1[0]) {count_smaller_in_1 = 0, count_identical_in_1 = 0;}
        else {
            l = 0, r = length_1 - 1, one_more = 1;
            while (l <= r) {
                m = l + (r - l) / 2;
                if (nums1[m] < mid) {l = m + 1;}
                else {r = m;}

                if (one_more == 0) {break;}
                if (l + 1 >= r) {one_more = 0;}
            }
            count_smaller_in_1 = l;
            if (nums1[l] == mid) {
                count_identical_in_1 = 1;
                if ((l < length_1 - 1)&&(nums1[l + 1] == mid)) {
                    r = length_1 - 1, one_more = 1;
                    while (l <= r) {
                        m = l + (r - l) / 2;
                        if (nums1[m] <= mid) {l = m;}
                        else {r = m - 1;}

                        if (one_more == 0) {break;}
                        if (l + 1 >= r) {one_more = 0;}
                    }
                    if (nums1[r] == nums1[l]) {l = r;}
                    count_identical_in_1 += l - count_smaller_in_1;
                    //cout << "r = " << r << ", temp = " << temp << "\n";
                }

            }
            else {count_identical_in_1 = 0;}
        }

        //if (test_timer >= 0) {cout << "find_position 2\n";}

        if (mid > nums2[length_2 - 1]) {count_smaller_in_2 = length_2, count_identical_in_2 = 0;}
        else if (mid < nums2[0]) {count_smaller_in_2 = 0, count_identical_in_2 = 0;}
        else {
            l = 0, r = length_2 - 1, one_more = 1;
            while (l <= r) {
                m = l + (r - l) / 2;
                if (nums2[m] < mid) {l = m + 1;}
                else {r = m;}

                if (one_more == 0) {break;}
                if (l + 1 >= r) {one_more = 0;}
            }
            count_smaller_in_2 = l;
            if (nums2[l] == mid) {
                count_identical_in_2 = 1;
                if ((l < length_2 - 1)&&(nums2[l + 1] == mid)) {
                    r = length_2 - 1, one_more = 1;
                    while (l <= r) {
                        m = l + (r - l) / 2;
                        if (nums2[m] <= mid) {l = m;}
                        else {r = m - 1;}

                        if (one_more == 0) {break;}
                        if (l + 1 >= r) {one_more = 0;}
                    }
                    if (nums2[r] == nums2[l]) {l = r;}
                    count_identical_in_2 += l - count_smaller_in_2;
                    //cout << "r = " << r << ", temp = " << temp << "\n";
                }

            }
            else {count_identical_in_2 = 0;}
        }


        /*if (test_timer >= 0) {
            cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
            cout << "count_smaller_in_1 = " << count_smaller_in_1 << ", count_identical_in_1 = " << count_identical_in_1 << "\n";
            cout << "count_smaller_in_2 = " << count_smaller_in_2 << ", count_identical_in_2 = " << count_identical_in_2 << "\n\n";
        }*/

        count_smaller = count_smaller_in_1 + count_smaller_in_2;
        count_identical = count_identical_in_1 + count_identical_in_2;

        if ((count_identical == 0)&&(count_smaller == criteria)) {break;}

        if ((count_identical > 0)&&(count_smaller <= criteria)&&(count_smaller + count_identical > criteria)) {break;}

        else if (count_smaller > criteria) {right = mid;}

        else {left = mid + 1;}
    }

    //if (test_timer >= 0) {cout << "count_smaller = " << count_smaller << ", count_identical = " << count_identical << "\n";}

    if (is_odd == 1) {
        if (count_identical > 1) {return mid;}
        if (count_smaller_in_1 == length_1) {return nums2[count_smaller_in_2];}
        if (count_smaller_in_2 == length_2) {return nums1[count_smaller_in_1];}
        else {
            return (nums1[count_smaller_in_1] < nums2[count_smaller_in_2])? nums1[count_smaller_in_1]: nums2[count_smaller_in_2];
        }
    }

    else if ((count_smaller < criteria)&&(count_identical > 1)) {return mid;}

    else {
        int left_candidate_idx_1, right_candidate_idx_1, left_candidate_idx_2, right_candidate_idx_2;

        if (count_smaller_in_1 == 0) {
            //left_candidate_idx_1 = (count_identical_in_1 > 0)? 0: -1;
            left_candidate_idx_1 = -1;
            right_candidate_idx_1 = 0;
        }
        else {
            left_candidate_idx_1 = count_smaller_in_1 - 1;
            if (count_smaller_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {
            //left_candidate_idx_2 = (count_identical_in_2 > 0)? 0: -1;
            left_candidate_idx_2 = -1;
            right_candidate_idx_2 = 0;
        }
        else {
            left_candidate_idx_2 = count_smaller_in_2 - 1;
            if (count_smaller_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        /*if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }*/

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        /*if (test_timer >= 0) {
            cout << "part_1 = " << part_1 << "\n";
            cout << "part_2 = " << part_2 << "\n\n";
        }*/
    }

    return (part_1 + part_2) / 2;
}


//SEARCH BY VALUE & NOT BY INDEX
//
//Put search function inside. With walls. Notable improvement.
//no timer resulted in little improvement, while walls on both sides helped a lot
double findMedianSortedArrays_1_0_1_no_timer_with_walls(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    double part_1 = 0, part_2 = 0;

    int is_odd = ((length_1 + length_2) & 1 == 1)? 1: 0;

    //int test_timer = -1;

    if ((length_1 == 0)||(length_2 == 0)) {
        if ((length_1 == 0)&&(length_2 > 0)) {
            part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        }
        if ((length_1 > 0)&&(length_2 == 0)) {
            part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        }
        return (part_1 + part_2) / 2;
    }

    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = (length_1 + length_2) / 2;

    //if (test_timer >= 0) {cout << "length_1 + length_2 = " << length_1 + length_2 << "\nis_odd = " << is_odd << "\ncriteria = " << criteria << "\n\n";}

    int count_smaller_in_1, count_identical_in_1;
    int count_smaller_in_2, count_identical_in_2;
    int count_smaller, count_identical;

    int left = (nums1[0] <= nums2[0])? nums1[0]: nums2[0];
    int right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];
    int mid, one_more = 1, l, m, r, temp = 0;
    int left_wall_1 = 0, right_wall_1 = length_1 - 1, left_wall_2 = 0, right_wall_2 = length_2 - 1;

    while (left <= right) {
        mid = left + (right - left) / 2;
        //if (test_timer >= 0) {cout << "search val = " << mid << "\n\n";}

        //if (test_timer >= 0) {cout << "find_position 1\n";}

        if (mid > nums1[length_1 - 1]) {count_smaller_in_1 = length_1, count_identical_in_1 = 0;}
        else if (mid < nums1[0]) {count_smaller_in_1 = 0, count_identical_in_1 = 0;}
        else {
            l = left_wall_1, r = right_wall_1, one_more = 1;
            while (l <= r) {
                m = l + (r - l) / 2;
                if (nums1[m] < mid) {l = m + 1;}
                else {r = m;}

                if (one_more == 0) {break;}
                if (l + 1 >= r) {one_more = 0;}
            }
            count_smaller_in_1 = l;
            if (nums1[l] == mid) {
                count_identical_in_1 = 1;
                if ((l < length_1 - 1)&&(nums1[l + 1] == mid)) {
                    r = right_wall_1, one_more = 1;
                    while (l <= r) {
                        m = l + (r - l) / 2;
                        if (nums1[m] <= mid) {l = m;}
                        else {r = m - 1;}

                        if (one_more == 0) {break;}
                        if (l + 1 >= r) {one_more = 0;}
                    }
                    if (nums1[r] == nums1[l]) {l = r;}
                    count_identical_in_1 += l - count_smaller_in_1;
                    //cout << "r = " << r << ", temp = " << temp << "\n";
                }

            }
            else {count_identical_in_1 = 0;}
        }

        //if (test_timer >= 0) {cout << "find_position 2\n";}

        if (mid > nums2[length_2 - 1]) {count_smaller_in_2 = length_2, count_identical_in_2 = 0;}
        else if (mid < nums2[0]) {count_smaller_in_2 = 0, count_identical_in_2 = 0;}
        else {
            l = left_wall_2, r = right_wall_2, one_more = 1;
            while (l <= r) {
                m = l + (r - l) / 2;
                if (nums2[m] < mid) {l = m + 1;}
                else {r = m;}

                if (one_more == 0) {break;}
                if (l + 1 >= r) {one_more = 0;}
            }
            count_smaller_in_2 = l;
            if (nums2[l] == mid) {
                count_identical_in_2 = 1;
                if ((l < length_2 - 1)&&(nums2[l + 1] == mid)) {
                    r = right_wall_2, one_more = 1;
                    while (l <= r) {
                        m = l + (r - l) / 2;
                        if (nums2[m] <= mid) {l = m;}
                        else {r = m - 1;}

                        if (one_more == 0) {break;}
                        if (l + 1 >= r) {one_more = 0;}
                    }
                    if (nums2[r] == nums2[l]) {l = r;}
                    count_identical_in_2 += l - count_smaller_in_2;
                    //cout << "r = " << r << ", temp = " << temp << "\n";
                }

            }
            else {count_identical_in_2 = 0;}
        }


        /*if (test_timer >= 0) {
            cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
            cout << "count_smaller_in_1 = " << count_smaller_in_1 << ", count_identical_in_1 = " << count_identical_in_1 << "\n";
            cout << "count_smaller_in_2 = " << count_smaller_in_2 << ", count_identical_in_2 = " << count_identical_in_2 << "\n\n";
        }*/

        count_smaller = count_smaller_in_1 + count_smaller_in_2;
        count_identical = count_identical_in_1 + count_identical_in_2;

        if ((count_identical == 0)&&(count_smaller == criteria)) {break;}

        if ((count_identical > 0)&&(count_smaller <= criteria)&&(count_smaller + count_identical > criteria)) {break;}

        else if (count_smaller > criteria) {
            right = mid;
            right_wall_1 = count_smaller_in_1;
            right_wall_2 = count_smaller_in_2;
        }

        else {
            left = mid + 1;
            left_wall_1 = count_smaller_in_1;
            left_wall_2 = count_smaller_in_2;
        }
    }

    //if (test_timer >= 0) {cout << "count_smaller = " << count_smaller << ", count_identical = " << count_identical << "\n";}

    if (is_odd == 1) {
        if (count_identical > 1) {return mid;}
        if (count_smaller_in_1 == length_1) {return nums2[count_smaller_in_2];}
        if (count_smaller_in_2 == length_2) {return nums1[count_smaller_in_1];}
        else {
            return (nums1[count_smaller_in_1] < nums2[count_smaller_in_2])? nums1[count_smaller_in_1]: nums2[count_smaller_in_2];
        }
    }

    else if ((count_smaller < criteria)&&(count_identical > 1)) {return mid;}

    else {
        int left_candidate_idx_1, right_candidate_idx_1, left_candidate_idx_2, right_candidate_idx_2;

        if (count_smaller_in_1 == 0) {
            //left_candidate_idx_1 = (count_identical_in_1 > 0)? 0: -1;
            left_candidate_idx_1 = -1;
            right_candidate_idx_1 = 0;
        }
        else {
            left_candidate_idx_1 = count_smaller_in_1 - 1;
            if (count_smaller_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {
            //left_candidate_idx_2 = (count_identical_in_2 > 0)? 0: -1;
            left_candidate_idx_2 = -1;
            right_candidate_idx_2 = 0;
        }
        else {
            left_candidate_idx_2 = count_smaller_in_2 - 1;
            if (count_smaller_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        /*if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }*/

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        /*if (test_timer >= 0) {
            cout << "part_1 = " << part_1 << "\n";
            cout << "part_2 = " << part_2 << "\n\n";
        }*/
    }

    return (part_1 + part_2) / 2;
}









//MESSY!!!
double findMedianSortedArrays_MESSY_NEED_FIXING(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    if ((length_1 == 0)&&(length_2 == 0)) {return 0;}
    double part_1 = 0, part_2 = 0;
    int test_timer = 0;

    if (length_1 == 0) {
        part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        return (part_1 + part_2) / 2;
    }
    if (length_2 == 0) {
        part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        return (part_1 + part_2) / 2;
    }
    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int is_odd = ((length_1 + length_2) & 1 == 1)? 1: 0;
    int criteria = (length_1 + length_2) / 2;
    if (test_timer >= 0) {
        cout << "is_odd = " << is_odd << "\n";
        cout << "length_1 + length_2 = " << (length_1 + length_2) << "\n";
        cout << "criteria = " << criteria << "\n\n";
    }

    int left, mid, right, counting_left, just_one_more, one_more, temp;//, hit_1, hit_2
    int left_idx_1, right_idx_1, mid_idx_1, left_idx_2, right_idx_2, mid_idx_2;

    left = (nums1[0] <= nums2[0])? nums1[0]: nums2[0];
    right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];

    just_one_more = 1;//, hit_1 = 0, hit_2 = 0
    while (left <= right) {
        mid = left + (right - left) / 2;

        if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";}

        //hit_1 = 0;
        //if left_idx_1 is in valid range, nums1[left_idx_1] will be the 1st that is no less than mid
        left_idx_1 = 0, right_idx_1 = length_1 - 1, one_more = 1;
        if (mid < nums1[left_idx_1]) {left_idx_1 = length_1, right_idx_1 = length_1;}
        else if (mid > nums1[right_idx_1]) {left_idx_1 = -1, right_idx_1 = -1;}
        else {
            while (left_idx_1 <= right_idx_1) {
                mid_idx_1 = left_idx_1 + (right_idx_1 - left_idx_1) / 2;
                if (nums1[mid_idx_1] < mid) {left_idx_1 = mid_idx_1 + 1;}
                else {
                    right_idx_1 = mid_idx_1;//if (mid == nums1[mid_idx_1]) {hit_1 = 1;}
                }
                if (one_more == 0) {break;}
                if (left_idx_1 == right_idx_1) {one_more = 0;}
            }
        }

        //hit_2 = 0;
        //if left_idx_2 is in valid range, nums2[left_idx_2] will be the 1st that is no less than mid
        left_idx_2 = 0, right_idx_2 = length_2 - 1, one_more = 1;
        if (mid < nums2[left_idx_2]) {left_idx_2 = length_2, right_idx_2 = length_2;}
        else if (mid > nums2[right_idx_2]) {left_idx_2 = -1, right_idx_2 = -1;}
        else {
            while (left_idx_2 <= right_idx_2) {
                mid_idx_2 = left_idx_2 + (right_idx_2 - left_idx_2) / 2;
                if (nums2[mid_idx_2] < mid) {left_idx_2 = mid_idx_2 + 1;}
                else {
                    right_idx_2 = mid_idx_2;//if (mid == nums2[mid_idx_2]) {hit_2 = 1;}
                }
                if (one_more == 0) {break;}
                if (left_idx_2 == right_idx_2) {one_more = 0;}
            }
        }

        if (test_timer >= 0) {
            cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
            cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n\n";
        }

        if (left_idx_1 >= length_1) {
            if (left_idx_2 < 0) {temp = length_2;}
            else {temp = left_idx_2;}
        }
        else if (left_idx_1 < 0) {
            if (left_idx_2 >= length_2) {temp = length_1;}
            else {temp = length_1 + left_idx_2;}
        }
        else if (left_idx_2 >= length_2) {
            if (left_idx_1 < 0) {temp = length_1;}
            else {temp = left_idx_1;}
        }
        else if (left_idx_2 < 0) {
            if (left_idx_1 >= length_1) {temp = length_2;}
            else {temp = left_idx_1 + length_2;}
        }
        else {temp = left_idx_1 + left_idx_2;}

        if (test_timer >= 0) {cout << "temp = " << temp << "\n\n";}

        if (just_one_more == 0) {break;}
        if (left + 1 == right) {just_one_more = 0;}

        if (temp <= criteria) {left = mid;}

        else if (temp > criteria) {right = mid;}
    }

    if (test_timer >= 0) {
        cout << "mid = " << mid << "\n";
        cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
        cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n";
    }

/*WHAT A FUCKING MESS!!! Now i want to rid of that mess sticking this one & previous one that worked together
    if (is_odd == 1) {
        if (left_idx_1 == -1) {
            return nums2[left_idx_2];
        }
        else if (left_idx_2 == -1) {
            return nums1[left_idx_1];
        }
        else {
            return (nums1[left_idx_1] <= nums2[left_idx_2])? nums1[left_idx_1]: nums2[left_idx_2];
        }
    }


    int count_smaller_1 = 0, count_smaller_2 = 0;
    if (left_idx_1 < 0) {count_smaller_1 = 0;}
    else if (left_idx_1 >= length_1) {count_smaller_1}

    if (left_idx_1 == length_1) {
        part_1 = nums2[left_idx_2 - 1], part_2 = nums2[left_idx_2];
    }

    else if (left_idx_1 < 0) {
        part_1 = (nums1[length_1 - 1] > nums2[left_idx_2 - 1])? nums1[length_1 - 1]: nums2[left_idx_2 - 1];
        part_2 = nums2[left_idx_2];
    }
    else if (left_idx_2 == length_2) {
        part_1 = nums1[left_idx_1 - 1], part_2 = nums1[left_idx_1];
    }
    else if (left_idx_2 < 0) {
        part_1 = (nums2[length_2 - 1] > nums1[left_idx_1 - 1])? nums2[length_2 - 1]: nums1[left_idx_1 - 1];
        part_2 = nums1[left_idx_1];
    }
    else if (nums1[left_idx_1] == nums2[left_idx_2]) {
        return nums1[left_idx_1];
    }
    else {
        //nums1[left_idx_1] is the leftmost element with potentially long duplications
        int count_smaller = left_idx_1 + left_idx_2;

        if (count_smaller == criteria) {
            if (left_idx_1 <= 0) {part_1 = nums2[left_idx_2 - 1];}
            else if (left_idx_2 <= 0) {part_1 = nums1[left_idx_1 - 1];}
            else {
                part_1 = (nums1[left_idx_1 - 1] >= nums2[left_idx_2 - 1])?
                nums1[left_idx_1 - 1]: nums2[left_idx_2 - 1];
            }

            part_2 = (nums1[left_idx_1] <= nums2[left_idx_2])? nums1[left_idx_1]: nums2[left_idx_2];
        }

        else {
            part_1 = (nums1[left_idx_1] <= nums2[left_idx_2])? nums1[left_idx_1]: nums2[left_idx_2];
            part_2 = part_1;
        }
    }
    */


    int count_smaller_in_1, count_identical_in_1 = 0;
    int count_smaller_in_2, count_identical_in_2 = 0;
    int count_smaller, count_identical;

    if (left_idx_1 < 0) {count_smaller_in_1 = length_1, count_identical_in_1 = 0;}
    else if (left_idx_1 >= length_1){count_smaller_in_1 = 0, count_identical_in_1 = 0;}
    else {
        count_smaller_in_1 = left_idx_1;

        if (nums1[left_idx_1] == mid) {
            count_identical_in_1++;

            if ((left_idx_1 < length_1 - 1)&&(nums1[left_idx_1 + 1] == mid)) {
                int left_0, mid_0, right_0;
                left_0 = left_idx_1, right_0 = length_1 - 1, one_more = 1;
                while (left_0 <= right_0) {
                    mid_0 = left_0 + (right_0 - left_0) / 2;
                    if (nums1[mid_0] <= mid) {left_0 = mid_0;}
                    else {right_0 = mid_0 - 1;}

                    if (one_more == 0) {break;}
                    if (left_0 + 1 >= right_0) {one_more = 0;}
                }
                count_identical_in_1 += right_0 - left_idx_1;
            }
        }

        else {count_identical_in_1 = 0;}
    }


    if (left_idx_2 < 0) {count_smaller_in_2 = length_2, count_identical_in_2 = 0;}
    else if (left_idx_2 >= length_2){count_smaller_in_2 = 0, count_identical_in_2 = 0;}
    else {
        count_smaller_in_2 = left_idx_2;

        if (nums2[left_idx_2] == mid) {
            count_identical_in_2++;

            if ((left_idx_2 < length_2 - 1)&&(nums2[left_idx_2 + 1] == mid)) {
                int left_0, mid_0, right_0;
                left_0 = left_idx_2, right_0 = length_2 - 1, one_more = 1;
                while (left_0 <= right_0) {
                    mid_0 = left_0 + (right_0 - left_0) / 2;
                    if (nums2[mid_0] <= mid) {left_0 = mid_0;}
                    else {right_0 = mid_0 - 1;}

                    //cout << "right_0 = " << right_0 << "\n";

                    if (one_more == 0) {break;}
                    if (left_0 + 1 >= right_0) {one_more = 0;}
                }
                count_identical_in_2 += right_0 - left_idx_2;
            }
        }

        else {count_identical_in_2 = 0;}
    }

    count_smaller = count_smaller_in_1 + count_smaller_in_2;
    count_identical = count_identical_in_1 + count_identical_in_2;

    if (test_timer >= 0) {
        cout << "\ncount_smaller_in_1 = " << count_smaller_in_1 << ", count_identical_in_1 = " << count_identical_in_1 << "\n";
        cout << "count_smaller_in_2 = " << count_smaller_in_2 << ", count_identical_in_2 = " << count_identical_in_2 << "\n";
        cout << "count_smaller = " << count_smaller << ", count_identical = " << count_identical << "\n\n";
    }

    if (is_odd == 1) {
        if (count_identical > 1) {return mid;}
        if (count_smaller_in_1 == length_1) {return nums2[count_smaller_in_2];}
        if (count_smaller_in_2 == length_2) {return nums1[count_smaller_in_1];}
        else {
            return (nums1[count_smaller_in_1] < nums2[count_smaller_in_2])? nums1[count_smaller_in_1]: nums2[count_smaller_in_2];
        }
    }

    else if ((count_smaller < criteria)&&(count_identical > 1)) {return mid;}

    else {
        int left_candidate_idx_1, right_candidate_idx_1, left_candidate_idx_2, right_candidate_idx_2;

        if (count_smaller_in_1 == 0) {
            //left_candidate_idx_1 = (count_identical_in_1 > 0)? 0: -1;
            left_candidate_idx_1 = -1;
            right_candidate_idx_1 = 0;
        }
        else {
            left_candidate_idx_1 = count_smaller_in_1 - 1;
            if (count_smaller_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {
            //left_candidate_idx_2 = (count_identical_in_2 > 0)? 0: -1;
            left_candidate_idx_2 = -1;
            right_candidate_idx_2 = 0;
        }
        else {
            left_candidate_idx_2 = count_smaller_in_2 - 1;
            if (count_smaller_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {
            cout << "part_1 = " << part_1 << "\n";
            cout << "part_2 = " << part_2 << "\n\n";
        }
    }


    //if (test_timer >= 0) {cout << "\n\npart_1 = " << part_1 << ", part_2 = " << part_2 << "\n";}
    return (part_1 + part_2) / 2;
}


//HIGHLY BUGGY
//hope this is salvagable
double findMedianSortedArrays_buggy(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    if ((length_1 == 0)&&(length_2 == 0)) {return 0;}
    double part_1 = 0, part_2 = 0;
    int test_timer = 0;

    if (length_1 == 0) {
        part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        return (part_1 + part_2) / 2;
    }
    if (length_2 == 0) {
        part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        return (part_1 + part_2) / 2;
    }
    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = length_1 + length_2;
    int is_odd = (criteria & 1 == 1)? 1: 0;
    criteria /= 2;//criteria = (length_1 + length_2) / 2, do in 2 steps so as to do 1 less addition operation

    if (test_timer >= 0) {
        cout << "is_odd = " << is_odd << "\n";
        cout << "length_1 + length_2 = " << (length_1 + length_2) << "\n";
        cout << "criteria = " << criteria << "\n\n";
    }

    int left, mid, right, just_one_more, one_more, temp;
    int left_wall_1 = 0, right_wall_1 = length_1 - 1;
    int left_wall_2 = 0, right_wall_2 = length_2 - 1;
    int left_idx_1, mid_idx_1, right_idx_1;
    int left_idx_2, mid_idx_2, right_idx_2;
    int count_smaller_in_1, count_smaller_in_2;
    int count_identical_in_1, count_identical_in_2;
    int count_smaller, count_identical;

    left = (nums1[0] <= nums2[0])? nums1[0]: nums2[0];
    right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];

    just_one_more = 1;
    while (left <= right) {
        mid = left + (right - left) / 2;

        if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";}

        //if left_idx_1 is in valid range, nums1[left_idx_1] will be the 1st that is no less than mid

        if (mid < nums1[left_wall_1]) {left_idx_1 = -1, right_idx_1 = -1;}
        else if (mid > nums1[right_wall_1]) {left_idx_1 = length_1, right_idx_1 = length_1;}
        else {
            left_idx_1 = left_wall_1, right_idx_1 = right_wall_1, one_more = 1;
            while (left_idx_1 <= right_idx_1) {
                mid_idx_1 = left_idx_1 + (right_idx_1 - left_idx_1) / 2;

                if (nums1[mid_idx_1] < mid) {left_idx_1 = mid_idx_1 + 1;}

                else {right_idx_1 = mid_idx_1;}

                if (one_more == 0) {break;}

                if (left_idx_1 == right_idx_1) {one_more = 0;}
            }
        }

        if (nums1[left_idx_1] == mid) {count_identical = 1;}

        //if left_idx_2 is in valid range, nums2[left_idx_2] will be the 1st that is no less than mid
        if (mid < nums2[left_wall_2]) {left_idx_2 = -1, right_idx_2 = -1;}
        else if (mid > nums2[right_wall_2]) {left_idx_2 = length_2, right_idx_2 = length_2;}
        else {
            left_idx_2 = left_wall_2, right_idx_2 = right_wall_2, one_more = 1;
            while (left_idx_2 <= right_idx_2) {
                mid_idx_2 = left_idx_2 + (right_idx_2 - left_idx_2) / 2;

                if (nums2[mid_idx_2] < mid) {left_idx_2 = mid_idx_2 + 1;}

                else {right_idx_2 = mid_idx_2;}

                if (one_more == 0) {break;}

                if (left_idx_2 == right_idx_2) {one_more = 0;}
            }
        }

        if (nums2[left_idx_2] == mid) {count_identical += 1;}

        if (test_timer >= 0) {
            cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
            cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n\n";
        }

        count_smaller_in_1 = (left_idx_1 > 0)? left_idx_1: 0;
        count_smaller_in_2 = (left_idx_2 > 0)? left_idx_2: 0;

        temp = count_smaller_in_1 + count_smaller_in_2;

        if (test_timer >= 0) {cout << "temp = " << temp << "\n\n";}

        if (temp <= criteria) {left = mid;}

        else {right = mid;}

        if (just_one_more == 0) {
            mid = left + (right - left) / 2;
            break;
        }
        if (left + 1 >= right) {just_one_more = 0;}
    }



    if (test_timer >= 0) {
        cout << "mid = " << mid << "\n";
        cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
        cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
        cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n";
    }

    count_smaller = count_smaller_in_1 + count_smaller_in_2;

    /*to fix problem with input
     = {4, 6, 8, 8};
     = {4, 6, 9};
    */
    if (count_smaller > criteria) {
        part_1 = (nums1[left_idx_1 - 1] >= nums2[left_idx_2 - 1])? nums1[left_idx_1 - 1]: nums2[left_idx_2 - 1];
        return part_1;
    }

    if ((left_idx_1 < 0)||(left_idx_1 >= length_1)) {count_identical_in_1 = 0;}
    else if (nums1[left_idx_1] != mid) {count_identical_in_1 = 0;}
    else {
        count_identical_in_1 = 1;

        if ((left_idx_1 < length_1 - 1)&&(nums1[left_idx_1 + 1] == mid)) {
            int left_0, mid_0, right_0;
            left_0 = left_idx_1, right_0 = length_1 - 1, one_more = 1;
            while (left_0 <= right_0) {
                mid_0 = left_0 + (right_0 - left_0) / 2;
                if (nums1[mid_0] <= mid) {left_0 = mid_0;}
                else {right_0 = mid_0 - 1;}

                if (one_more == 0) {break;}
                if (left_0 + 1 >= right_0) {one_more = 0;}
            }
            if (nums1[right_0] == mid) {left_0 = right_0;}
            count_identical_in_1 += left_0 - left_idx_1;
        }
    }

    if ((left_idx_2 < 0)||(left_idx_2 >= length_2)) {count_identical_in_2 = 0;}
    else if (nums2[left_idx_2] != mid) {count_identical_in_2 = 0;}
    else {
        count_identical_in_2 = 1;

        if ((left_idx_2 < length_2 - 1)&&(nums2[left_idx_2 + 1] == mid)) {
            int left_0, mid_0, right_0;
            left_0 = left_idx_2, right_0 = length_2 - 1, one_more = 1;
            while (left_0 <= right_0) {
                mid_0 = left_0 + (right_0 - left_0) / 2;
                if (nums2[mid_0] <= mid) {left_0 = mid_0;}
                else {right_0 = mid_0 - 1;}

                if (one_more == 0) {break;}
                if (left_0 + 1 >= right_0) {one_more = 0;}
            }
            if (nums2[right_0] == mid) {left_0 = right_0;}
            count_identical_in_2 += left_0 - left_idx_2;
        }
    }

    count_identical = count_identical_in_1 + count_identical_in_2;

    if (test_timer >= 0) {
        cout << "\ncount_smaller_in_1 = " << count_smaller_in_1 << ", count_identical_in_1 = " << count_identical_in_1 << "\n";
        cout << "count_smaller_in_2 = " << count_smaller_in_2 << ", count_identical_in_2 = " << count_identical_in_2 << "\n";
        cout << "count_smaller = " << count_smaller << ", count_identical = " << count_identical << "\n\n";
    }

    int left_candidate_idx_1, right_candidate_idx_1, left_candidate_idx_2, right_candidate_idx_2;

    if (is_odd == 1) {
        if (count_identical > 1) {return mid;}
        if (count_smaller_in_1 == length_1) {return nums2[count_smaller_in_2];}
        if (count_smaller_in_2 == length_2) {return nums1[count_smaller_in_1];}
        else if (count_smaller + count_identical > criteria){
            return (nums1[count_smaller_in_1] < nums2[count_smaller_in_2])? nums1[count_smaller_in_1]: nums2[count_smaller_in_2];
        }
        else {
            /*" + count_identical_in_1" is because "= {3} = {2, 3}"*/
            if (count_smaller_in_1 + count_identical_in_1 == 0) {left_candidate_idx_1 = -1, right_candidate_idx_1 = 0;}

            /*to fix problem with input
             = {4}
             = {2, 5, 6, 6, 6}*/
            else {
                left_candidate_idx_1 = count_smaller_in_1 + count_identical_in_1;
                if (count_smaller_in_1 + count_identical_in_1 + 1 < length_1) {right_candidate_idx_1 = count_smaller_in_1 + count_identical_in_1 + 1;}
                else {right_candidate_idx_1 = -1;}
            }

            if (count_smaller_in_2 + count_identical_in_2 == 0) {left_candidate_idx_2 = -1, right_candidate_idx_2 = 0;}

            else {
                left_candidate_idx_2 = count_smaller_in_2 + count_identical_in_2;
                if (count_smaller_in_2 + count_identical_in_2 + 1 < length_2) {right_candidate_idx_2 = count_smaller_in_2 + count_identical_in_2 + 1;}
                else {right_candidate_idx_2 = -1;}
            }

            if (test_timer >= 0) {
                cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
                cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
                cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
                cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
            }

            if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
            else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
            else {
                part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
                nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
            }

            if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
            else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
            else {
                part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
                nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
            }

            if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
        }
    }

    else if ((count_smaller < criteria)&&(count_smaller + count_identical > criteria)) {return mid;}

    /*add this branch to deal with
     = {7}
     = {2, 7, 7}
    */
    else if (count_smaller + count_identical < criteria) {
        if (count_smaller_in_1 == 0) {left_candidate_idx_1 = -1, right_candidate_idx_1 = 0;}

        /*to fix problem with input
         = {4}
         = {2, 5, 6, 6, 6}*/
        else {
            left_candidate_idx_1 = count_smaller_in_1;
            if (count_smaller_in_1 + 1 < length_1) {right_candidate_idx_1 = count_smaller_in_1 + 1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {left_candidate_idx_2 = -1, right_candidate_idx_2 = 0;}

        else {
            left_candidate_idx_2 = count_smaller_in_2;
            if (count_smaller_in_2 + 1 < length_2) {right_candidate_idx_2 = count_smaller_in_2 + 1;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
    }


    /* = {9, 12, 13, 15, 18} = {1, 6, 6, 8, 8, 9, 10, 11, 16}*/
    else if (count_smaller + count_identical > criteria){

        /* = {2, 2} = {1, 1, 1, 2}*/
        if (count_smaller_in_1 == 0) {left_candidate_idx_1 = -1, right_candidate_idx_1 = 0;}

        else {
            left_candidate_idx_1 = count_smaller_in_1 - 1;
            if (count_smaller_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {left_candidate_idx_2 = -1, right_candidate_idx_2 = 0;}

        else {
            left_candidate_idx_2 = count_smaller_in_2 - 1;
            if (count_smaller_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
    }

    else {

        /* = {2, 2} = {1, 1, 1, 2}*/
        if (count_smaller_in_1 + count_identical_in_1 == 0) {left_candidate_idx_1 = -1, right_candidate_idx_1 = 0;}

        else {
            left_candidate_idx_1 = count_smaller_in_1 + count_identical_in_1 - 1;
            if (count_smaller_in_1 + count_identical_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1 + count_identical_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 + count_identical_in_2 == 0) {left_candidate_idx_2 = -1, right_candidate_idx_2 = 0;}

        else {
            left_candidate_idx_2 = count_smaller_in_2 + count_identical_in_2 - 1;
            if (count_smaller_in_2 + count_identical_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2 + count_identical_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
    }

    //if (test_timer >= 0) {cout << "\n\npart_1 = " << part_1 << ", part_2 = " << part_2 << "\n";}
    return (part_1 + part_2) / 2;
}


//checkpoint
double findMedianSortedArrays_UNCLEAN(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    if ((length_1 == 0)&&(length_2 == 0)) {return 0;}
    double part_1 = 0, part_2 = 0;
    int test_timer = 0;

    if (length_1 == 0) {
        part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        return (part_1 + part_2) / 2;
    }
    if (length_2 == 0) {
        part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        return (part_1 + part_2) / 2;
    }
    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = length_1 + length_2;
    int is_odd = (criteria & 1 == 1)? 1: 0;
    //criteria++;
    criteria /= 2;//criteria = (length_1 + length_2) / 2, do in 2 steps so as to do 1 less addition operation

    if (test_timer >= 0) {
        cout << "is_odd = " << is_odd << "\n";
        cout << "length_1 + length_2 = " << (length_1 + length_2) << "\n";
        cout << "criteria = " << criteria << "\n\n";
    }

    int left, mid, right, just_one_more, one_more, temp;
    int left_wall_1 = 0, right_wall_1 = length_1 - 1;
    int left_wall_2 = 0, right_wall_2 = length_2 - 1;
    int left_idx_1, mid_idx_1, right_idx_1;
    int left_idx_2, mid_idx_2, right_idx_2;
    int count_smaller_in_1, count_smaller_in_2;
    int count_identical_in_1, count_identical_in_2;
    int count_smaller, count_identical;

    left = (nums1[0] <= nums2[0])? nums1[0]: nums2[0];
    right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];

    just_one_more = 1;
    while (left <= right) {
        mid = left + (right - left) / 2;

        if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";}

        //if left_idx_1 is in valid range, nums1[left_idx_1] will be the 1st that is no less than mid

        if (mid < nums1[left_wall_1]) {left_idx_1 = -1, right_idx_1 = -1;}
        else if (mid > nums1[right_wall_1]) {left_idx_1 = length_1, right_idx_1 = length_1;}
        else {
            left_idx_1 = left_wall_1, right_idx_1 = right_wall_1, one_more = 1;
            while (left_idx_1 <= right_idx_1) {
                mid_idx_1 = left_idx_1 + (right_idx_1 - left_idx_1) / 2;

                if (nums1[mid_idx_1] < mid) {left_idx_1 = mid_idx_1 + 1;}

                else {right_idx_1 = mid_idx_1;}

                if (one_more == 0) {break;}

                if (left_idx_1 == right_idx_1) {one_more = 0;}
            }
        }

        if (nums1[left_idx_1] == mid) {count_identical = 1;}

        //if left_idx_2 is in valid range, nums2[left_idx_2] will be the 1st that is no less than mid
        if (mid < nums2[left_wall_2]) {left_idx_2 = -1, right_idx_2 = -1;}
        else if (mid > nums2[right_wall_2]) {left_idx_2 = length_2, right_idx_2 = length_2;}
        else {
            left_idx_2 = left_wall_2, right_idx_2 = right_wall_2, one_more = 1;
            while (left_idx_2 <= right_idx_2) {
                mid_idx_2 = left_idx_2 + (right_idx_2 - left_idx_2) / 2;

                if (nums2[mid_idx_2] < mid) {left_idx_2 = mid_idx_2 + 1;}

                else {right_idx_2 = mid_idx_2;}

                if (one_more == 0) {break;}

                if (left_idx_2 == right_idx_2) {one_more = 0;}
            }
        }

        if (nums2[left_idx_2] == mid) {count_identical += 1;}

        if (test_timer >= 0) {
            cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
            cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n\n";
        }

        count_smaller_in_1 = (left_idx_1 > 0)? left_idx_1: 0;
        count_smaller_in_2 = (left_idx_2 > 0)? left_idx_2: 0;

        temp = count_smaller_in_1 + count_smaller_in_2;

        if (test_timer >= 0) {cout << "temp = " << temp << "\n\n";}

        if (temp <= criteria) {left = mid;}

        else {right = mid;}

        if (just_one_more == 0) {
            mid = left + (right - left) / 2;
            break;
        }
        if (left + 1 >= right) {just_one_more = 0;}
    }



    if (test_timer >= 0) {
        cout << "mid = " << mid << "\n";
        cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
        cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
        cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n";
    }

    count_smaller = count_smaller_in_1 + count_smaller_in_2;

    if ((left_idx_1 < 0)||(left_idx_1 >= length_1)) {count_identical_in_1 = 0;}
    else if (nums1[left_idx_1] != mid) {count_identical_in_1 = 0;}
    else {
        count_identical_in_1 = 1;

        if ((left_idx_1 < length_1 - 1)&&(nums1[left_idx_1 + 1] == mid)) {
            int left_0, mid_0, right_0;
            left_0 = left_idx_1, right_0 = length_1 - 1, one_more = 1;
            while (left_0 <= right_0) {
                mid_0 = left_0 + (right_0 - left_0) / 2;
                if (nums1[mid_0] <= mid) {left_0 = mid_0;}
                else {right_0 = mid_0 - 1;}

                if (one_more == 0) {break;}
                if (left_0 + 1 >= right_0) {one_more = 0;}
            }
            if (nums1[right_0] == mid) {left_0 = right_0;}
            count_identical_in_1 += left_0 - left_idx_1;
        }
    }

    if ((left_idx_2 < 0)||(left_idx_2 >= length_2)) {count_identical_in_2 = 0;}
    else if (nums2[left_idx_2] != mid) {count_identical_in_2 = 0;}
    else {
        count_identical_in_2 = 1;

        if ((left_idx_2 < length_2 - 1)&&(nums2[left_idx_2 + 1] == mid)) {
            int left_0, mid_0, right_0;
            left_0 = left_idx_2, right_0 = length_2 - 1, one_more = 1;
            while (left_0 <= right_0) {
                mid_0 = left_0 + (right_0 - left_0) / 2;
                if (nums2[mid_0] <= mid) {left_0 = mid_0;}
                else {right_0 = mid_0 - 1;}

                if (one_more == 0) {break;}
                if (left_0 + 1 >= right_0) {one_more = 0;}
            }
            if (nums2[right_0] == mid) {left_0 = right_0;}
            count_identical_in_2 += left_0 - left_idx_2;
        }
    }

    count_identical = count_identical_in_1 + count_identical_in_2;

    if (test_timer >= 0) {
        cout << "\ncount_smaller_in_1 = " << count_smaller_in_1 << ", count_identical_in_1 = " << count_identical_in_1 << "\n";
        cout << "count_smaller_in_2 = " << count_smaller_in_2 << ", count_identical_in_2 = " << count_identical_in_2 << "\n";
        cout << "count_smaller = " << count_smaller << ", count_identical = " << count_identical << "\n\n";
    }

    int left_candidate_idx_1 = -1, right_candidate_idx_1 = -1, left_candidate_idx_2 = -1, right_candidate_idx_2 = -1;


    if (is_odd == 1) {
        if (count_identical + count_smaller >= criteria) {
            if (count_identical > 1) {return mid;}
            if (left_idx_1 == length_1) {return nums2[left_idx_2];}
            if (left_idx_2 == length_2) {return nums1[left_idx_1];}
            else if (count_smaller + count_identical > criteria){
                return (nums1[left_idx_1] <= nums2[left_idx_2])? nums1[left_idx_1]: nums2[left_idx_2];
            }
        }

        else {
            if (left_idx_1 < 0) {right_candidate_idx_1 = nums1[0];}
            else if (left_idx_1 < length_1 - 1) {right_candidate_idx_1 = nums1[left_idx_1 + 1];}

            if (left_idx_2 < 0) {right_candidate_idx_2 = nums2[0];}
            else if (left_idx_2 < length_2 - 1) {right_candidate_idx_2 = nums2[left_idx_2 + 1];}

            if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
            else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
            else {
                part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
                nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
            }

            return part_2;
        }
    }

    left_candidate_idx_1 = -1, right_candidate_idx_1 = -1, left_candidate_idx_2 = -1, right_candidate_idx_2 = -1;

    if (count_identical > 0) {
        if (count_smaller < criteria) {return mid;}

        else {
            part_2 = mid;

            if ((left_idx_1 > 0)&&(left_idx_1 < length_1)) {left_candidate_idx_1 = left_idx_1 - 1;}
            if ((left_idx_2 > 0)&&(left_idx_2 < length_2)) {left_candidate_idx_2 = left_idx_2 - 1;}

            if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
            else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
            else {
                part_1 = (nums1[left_candidate_idx_1 - 1] >= nums2[left_candidate_idx_2])?
                nums1[left_candidate_idx_1]: nums2[left_candidate_idx_2];
            }
        }
    }

    else {
        if (left_idx_1 < 0) {right_candidate_idx_1 = nums1[0];}
        else if (left_idx_1 == length_1) {left_candidate_idx_1 = nums1[length_1 - 1];}
        else {
            left_candidate_idx_1 = nums1[left_idx_1 - 1];
            right_candidate_idx_1 = nums1[left_idx_1];
        }

        if (left_idx_2 < 0) {right_candidate_idx_2 = nums2[0];}
        else if (left_idx_2 == length_2) {left_candidate_idx_2 = nums2[length_2 - 1];}
        else {
            left_candidate_idx_2 = nums2[left_idx_2 - 1];
            right_candidate_idx_2 = nums2[left_idx_2];
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
    }

    /*if (is_odd == 1) {
        if (count_identical > 1) {return mid;}
        if (count_smaller_in_1 == length_1) {return nums2[count_smaller_in_2];}
        if (count_smaller_in_2 == length_2) {return nums1[count_smaller_in_1];}
        else if (count_smaller + count_identical > criteria){
            return (nums1[count_smaller_in_1] < nums2[count_smaller_in_2])? nums1[count_smaller_in_1]: nums2[count_smaller_in_2];
        }
        else {
            if (count_smaller_in_1 + count_identical_in_1 == 0) {left_candidate_idx_1 = -1, right_candidate_idx_1 = 0;}

            else {
                left_candidate_idx_1 = count_smaller_in_1 + count_identical_in_1;
                if (count_smaller_in_1 + count_identical_in_1 + 1 < length_1) {right_candidate_idx_1 = count_smaller_in_1 + count_identical_in_1 + 1;}
                else {right_candidate_idx_1 = -1;}
            }

            if (count_smaller_in_2 + count_identical_in_2 == 0) {left_candidate_idx_2 = -1, right_candidate_idx_2 = 0;}

            else {
                left_candidate_idx_2 = count_smaller_in_2 + count_identical_in_2;
                if (count_smaller_in_2 + count_identical_in_2 + 1 < length_2) {right_candidate_idx_2 = count_smaller_in_2 + count_identical_in_2 + 1;}
                else {right_candidate_idx_2 = -1;}
            }

            if (test_timer >= 0) {
                cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
                cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
                cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
                cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
            }

            if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
            else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
            else {
                part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
                nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
            }

            if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
            else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
            else {
                part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
                nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
            }

            if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
        }
    }

    else if ((count_smaller < criteria)&&(count_smaller + count_identical > criteria)) {return mid;}

    //add this branch to deal with = {7} = {2, 7, 7}
    else if (count_smaller + count_identical < criteria) {
        if (count_smaller_in_1 == 0) {left_candidate_idx_1 = -1, right_candidate_idx_1 = 0;}

        //to fix problem with input = {4}= {2, 5, 6, 6, 6}
        else {
            left_candidate_idx_1 = count_smaller_in_1;
            if (count_smaller_in_1 + 1 < length_1) {right_candidate_idx_1 = count_smaller_in_1 + 1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {left_candidate_idx_2 = -1, right_candidate_idx_2 = 0;}

        else {
            left_candidate_idx_2 = count_smaller_in_2;
            if (count_smaller_in_2 + 1 < length_2) {right_candidate_idx_2 = count_smaller_in_2 + 1;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
    }


    // = {9, 12, 13, 15, 18} = {1, 6, 6, 8, 8, 9, 10, 11, 16}
    else if (count_smaller + count_identical > criteria){

        // = {2, 2} = {1, 1, 1, 2}
        if (count_smaller_in_1 == 0) {left_candidate_idx_1 = -1, right_candidate_idx_1 = 0;}

        else {
            left_candidate_idx_1 = count_smaller_in_1 - 1;
            if (count_smaller_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 == 0) {left_candidate_idx_2 = -1, right_candidate_idx_2 = 0;}

        else {
            left_candidate_idx_2 = count_smaller_in_2 - 1;
            if (count_smaller_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
    }

    else {

        // = {2, 2} = {1, 1, 1, 2}
        if (count_smaller_in_1 + count_identical_in_1 == 0) {left_candidate_idx_1 = -1, right_candidate_idx_1 = 0;}

        else {
            left_candidate_idx_1 = count_smaller_in_1 + count_identical_in_1 - 1;
            if (count_smaller_in_1 + count_identical_in_1 < length_1) {right_candidate_idx_1 = count_smaller_in_1 + count_identical_in_1;}
            else {right_candidate_idx_1 = -1;}
        }

        if (count_smaller_in_2 + count_identical_in_2 == 0) {left_candidate_idx_2 = -1, right_candidate_idx_2 = 0;}

        else {
            left_candidate_idx_2 = count_smaller_in_2 + count_identical_in_2 - 1;
            if (count_smaller_in_2 + count_identical_in_2 < length_2) {right_candidate_idx_2 = count_smaller_in_2 + count_identical_in_2;}
            else {right_candidate_idx_2 = -1;}
        }

        if (test_timer >= 0) {
            cout << "left_candidate_idx_1 = " << left_candidate_idx_1 << "\n";
            cout << "right_candidate_idx_1 = " << right_candidate_idx_1 << "\n";
            cout << "left_candidate_idx_2 = " << left_candidate_idx_2 << "\n";
            cout << "right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
    }

    */

    //if (test_timer >= 0) {cout << "\n\npart_1 = " << part_1 << ", part_2 = " << part_2 << "\n";}
    return (part_1 + part_2) / 2;
}


//checkpoint
double findMedianSortedArrays_MESSY(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    if ((length_1 == 0)&&(length_2 == 0)) {return 0;}
    double part_1 = 0, part_2 = 0;
    int test_timer = 0;

    if (length_1 == 0) {
        part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        return (part_1 + part_2) / 2;
    }
    if (length_2 == 0) {
        part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        return (part_1 + part_2) / 2;
    }
    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = length_1 + length_2;
    int is_odd = (criteria & 1 == 1)? 1: 0;
    //criteria++;
    criteria /= 2;//criteria = (length_1 + length_2) / 2, do in 2 steps so as to do 1 less addition operation

    if (test_timer >= 0) {
        cout << "is_odd = " << is_odd << "\n";
        cout << "length_1 + length_2 = " << (length_1 + length_2) << "\n";
        cout << "criteria = " << criteria << "\n\n";
    }

    int left, mid, right, just_one_more, one_more, temp;
    int left_wall_1 = 0, right_wall_1 = length_1 - 1;
    int left_wall_2 = 0, right_wall_2 = length_2 - 1;
    int left_idx_1, mid_idx_1, right_idx_1;
    int left_idx_2, mid_idx_2, right_idx_2;
    int count_smaller_in_1, count_smaller_in_2;
    int count_identical_in_1, count_identical_in_2;
    int count_smaller, count_identical;
    int smaller_idx_1, larger_idx_1;
    int smaller_idx_2, larger_idx_2;

    left = (nums1[0] <= nums2[0])? nums1[0]: nums2[0];
    right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];


    just_one_more = 1;

    //will it work?
    while (left <= right) {
        mid = (left + smaller_idx_1) / 2;

        mid = left + (right - left) / 2;

        if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";}

        //if left_idx_1 is in valid range, nums1[left_idx_1] will be the 1st that is no less than mid

        if (mid < nums1[left_wall_1]) {left_idx_1 = -1, right_idx_1 = -1;}
        else if (mid > nums1[right_wall_1]) {left_idx_1 = length_1, right_idx_1 = length_1;}
        else {
            left_idx_1 = left_wall_1, right_idx_1 = right_wall_1, one_more = 1;
            while (left_idx_1 <= right_idx_1) {
                mid_idx_1 = left_idx_1 + (right_idx_1 - left_idx_1) / 2;

                if (nums1[mid_idx_1] < mid) {left_idx_1 = mid_idx_1 + 1;}

                else {right_idx_1 = mid_idx_1;}

                if (one_more == 0) {break;}

                if (left_idx_1 == right_idx_1) {one_more = 0;}
            }
        }

        if (nums1[left_idx_1] == mid) {count_identical = 1;}

        //if left_idx_2 is in valid range, nums2[left_idx_2] will be the 1st that is no less than mid
        if (mid < nums2[left_wall_2]) {left_idx_2 = -1, right_idx_2 = -1;}
        else if (mid > nums2[right_wall_2]) {left_idx_2 = length_2, right_idx_2 = length_2;}
        else {
            left_idx_2 = left_wall_2, right_idx_2 = right_wall_2, one_more = 1;
            while (left_idx_2 <= right_idx_2) {
                mid_idx_2 = left_idx_2 + (right_idx_2 - left_idx_2) / 2;

                if (nums2[mid_idx_2] < mid) {left_idx_2 = mid_idx_2 + 1;}

                else {right_idx_2 = mid_idx_2;}

                if (one_more == 0) {break;}

                if (left_idx_2 == right_idx_2) {one_more = 0;}
            }
        }

        if (nums2[left_idx_2] == mid) {count_identical += 1;}

        if (test_timer >= 0) {
            cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
            cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n\n";
        }

        count_smaller_in_1 = (left_idx_1 > 0)? left_idx_1: 0;
        count_smaller_in_2 = (left_idx_2 > 0)? left_idx_2: 0;

        temp = count_smaller_in_1 + count_smaller_in_2;

        if (test_timer >= 0) {cout << "temp = " << temp << "\n\n";}

        if (temp <= criteria) {left = mid;}

        else {right = mid;}

        if (just_one_more == 0) {
            mid = left + (right - left) / 2;
            break;
        }
        if (left + 1 >= right) {just_one_more = 0;}
    }





/*
    if (test_timer >= 0) {
        cout << "mid = " << mid << "\n";
        cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";
        cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
        cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n";
    }

    count_smaller = count_smaller_in_1 + count_smaller_in_2;

    if ((left_idx_1 < 0)||(left_idx_1 >= length_1)) {count_identical_in_1 = 0;}
    else if (nums1[left_idx_1] != mid) {count_identical_in_1 = 0;}
    else {
        count_identical_in_1 = 1;

        if ((left_idx_1 < length_1 - 1)&&(nums1[left_idx_1 + 1] == mid)) {
            int left_0, mid_0, right_0;
            left_0 = left_idx_1, right_0 = length_1 - 1, one_more = 1;
            while (left_0 <= right_0) {
                mid_0 = left_0 + (right_0 - left_0) / 2;
                if (nums1[mid_0] <= mid) {left_0 = mid_0;}
                else {right_0 = mid_0 - 1;}

                if (one_more == 0) {break;}
                if (left_0 + 1 >= right_0) {one_more = 0;}
            }
            if (nums1[right_0] == mid) {left_0 = right_0;}
            count_identical_in_1 += left_0 - left_idx_1;
        }
    }

    if ((left_idx_2 < 0)||(left_idx_2 >= length_2)) {count_identical_in_2 = 0;}
    else if (nums2[left_idx_2] != mid) {count_identical_in_2 = 0;}
    else {
        count_identical_in_2 = 1;

        if ((left_idx_2 < length_2 - 1)&&(nums2[left_idx_2 + 1] == mid)) {
            int left_0, mid_0, right_0;
            left_0 = left_idx_2, right_0 = length_2 - 1, one_more = 1;
            while (left_0 <= right_0) {
                mid_0 = left_0 + (right_0 - left_0) / 2;
                if (nums2[mid_0] <= mid) {left_0 = mid_0;}
                else {right_0 = mid_0 - 1;}

                if (one_more == 0) {break;}
                if (left_0 + 1 >= right_0) {one_more = 0;}
            }
            if (nums2[right_0] == mid) {left_0 = right_0;}
            count_identical_in_2 += left_0 - left_idx_2;
        }
    }

    count_identical = count_identical_in_1 + count_identical_in_2;

    if (test_timer >= 0) {
        cout << "\ncount_smaller_in_1 = " << count_smaller_in_1 << ", count_identical_in_1 = " << count_identical_in_1 << "\n";
        cout << "count_smaller_in_2 = " << count_smaller_in_2 << ", count_identical_in_2 = " << count_identical_in_2 << "\n";
        cout << "count_smaller = " << count_smaller << ", count_identical = " << count_identical << "\n\n";
    }

    int left_candidate_idx_1 = -1, right_candidate_idx_1 = -1, left_candidate_idx_2 = -1, right_candidate_idx_2 = -1;


    if (is_odd == 1) {
        if (count_identical + count_smaller >= criteria) {
            if (count_identical > 1) {return mid;}
            if (left_idx_1 == length_1) {return nums2[left_idx_2];}
            if (left_idx_2 == length_2) {return nums1[left_idx_1];}
            else if (count_smaller + count_identical > criteria){
                return (nums1[left_idx_1] <= nums2[left_idx_2])? nums1[left_idx_1]: nums2[left_idx_2];
            }
        }

        else {
            if (left_idx_1 < 0) {right_candidate_idx_1 = nums1[0];}
            else if (left_idx_1 < length_1 - 1) {right_candidate_idx_1 = nums1[left_idx_1 + 1];}

            if (left_idx_2 < 0) {right_candidate_idx_2 = nums2[0];}
            else if (left_idx_2 < length_2 - 1) {right_candidate_idx_2 = nums2[left_idx_2 + 1];}

            if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
            else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
            else {
                part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
                nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
            }

            return part_2;
        }
    }

    left_candidate_idx_1 = -1, right_candidate_idx_1 = -1, left_candidate_idx_2 = -1, right_candidate_idx_2 = -1;

    if (count_identical > 0) {
        if (count_smaller < criteria) {return mid;}

        else {
            part_2 = mid;

            if ((left_idx_1 > 0)&&(left_idx_1 < length_1)) {left_candidate_idx_1 = left_idx_1 - 1;}
            if ((left_idx_2 > 0)&&(left_idx_2 < length_2)) {left_candidate_idx_2 = left_idx_2 - 1;}

            if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
            else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
            else {
                part_1 = (nums1[left_candidate_idx_1 - 1] >= nums2[left_candidate_idx_2])?
                nums1[left_candidate_idx_1]: nums2[left_candidate_idx_2];
            }
        }
    }

    else {
        if (left_idx_1 < 0) {right_candidate_idx_1 = nums1[0];}
        else if (left_idx_1 == length_1) {left_candidate_idx_1 = nums1[length_1 - 1];}
        else {
            left_candidate_idx_1 = nums1[left_idx_1 - 1];
            right_candidate_idx_1 = nums1[left_idx_1];
        }

        if (left_idx_2 < 0) {right_candidate_idx_2 = nums2[0];}
        else if (left_idx_2 == length_2) {left_candidate_idx_2 = nums2[length_2 - 1];}
        else {
            left_candidate_idx_2 = nums2[left_idx_2 - 1];
            right_candidate_idx_2 = nums2[left_idx_2];
        }

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}
    }
*/
    //if (test_timer >= 0) {cout << "\n\npart_1 = " << part_1 << ", part_2 = " << part_2 << "\n";}
    return (part_1 + part_2) / 2;
}


//almost start anew
double findMedianSortedArrays_probably_last_search_by_val_in_this_problem(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    if ((length_1 == 0)&&(length_2 == 0)) {return 0;}
    double part_1 = 0, part_2 = 0;
    int test_timer = 0;

    if (length_1 == 0) {
        part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        return (part_1 + part_2) / 2;
    }
    if (length_2 == 0) {
        part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        return (part_1 + part_2) / 2;
    }
    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = length_1 + length_2;
    int is_odd = (criteria & 1 == 1)? 1: 0;
    criteria /= 2;//criteria = (length_1 + length_2) / 2, do in 2 steps so as to do 1 less addition operation

    if (test_timer >= 0) {
        cout << "is_odd = " << is_odd << "\n";
        cout << "length_1 + length_2 = " << (length_1 + length_2) << "\n";
        cout << "criteria = " << criteria << "\n\n";
    }

    int left, mid, right, just_one_more, one_more, temp;
    int left_idx_1_wall = 0, right_idx_1_wall = length_1 - 1;
    int left_idx_2_wall = 0, right_idx_2_wall = length_2 - 1;
    int left_idx_1, mid_idx_1, right_idx_1;
    int left_idx_2, mid_idx_2, right_idx_2;
    int count_smaller_1, count_smaller_2;
    int count_larger_1, count_larger_2;
    int count_identical_in_1, count_identical_in_2;
    int count_smaller, count_larger;
    //int smaller_idx_1, larger_idx_1;
    //int smaller_idx_2, larger_idx_2;

    int left_candidate_idx_1 = -1, right_candidate_idx_1 = -1, left_candidate_idx_2 = -1, right_candidate_idx_2 = -1;

    left = (nums1[0] <= nums2[0])? nums1[0]: nums2[0];
    right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];
    //smaller_idx_1 = right, larger_idx = left;

    if (test_timer >= 0) {cout << "first big loop\n";}

    just_one_more = 1;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";}

        if (mid < nums1[0]) {left_idx_1 = -1, right_idx_1 = -1;}
        else if (mid > nums1[length_1 - 1]) {left_idx_1 = length_1, right_idx_1 = length_1;}
        else {
            left_idx_1 = left_idx_1_wall, right_idx_1 = right_idx_1_wall, one_more = 1;
            while (left_idx_1 <= right_idx_1) {
                mid_idx_1 = left_idx_1 + (right_idx_1 - left_idx_1) / 2;

                if (nums1[mid_idx_1] < mid) {left_idx_1 = mid_idx_1;}

                else {right_idx_1 = mid_idx_1;}

                //if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";test_timer++;}
                //if (test_timer > 10) {just_one_more = 0;break;}

                if (one_more == 0) {break;}

                if (left_idx_1 + 1 >= right_idx_1) {one_more = 0;}
            }
        }

        //if left_idx_2 is in valid range, nums2[left_idx_2] will be the 1st that is no less than mid
        if (mid < nums2[0]) {left_idx_2 = -1, right_idx_2 = -1;}
        else if (mid > nums2[length_2 - 1]) {left_idx_2 = length_2, right_idx_2 = length_2;}
        else {
            left_idx_2 = left_idx_2_wall, right_idx_2 = right_idx_2_wall, one_more = 1;
            while (left_idx_2 <= right_idx_2) {
                mid_idx_2 = left_idx_2 + (right_idx_2 - left_idx_2) / 2;

                if (nums2[mid_idx_2] < mid) {left_idx_2 = mid_idx_2;}

                else {right_idx_2 = mid_idx_2;}

                if (one_more == 0) {break;}

                if (left_idx_2 + 1 >= right_idx_2) {one_more = 0;}
            }
        }

        if (test_timer >= 0) {
            cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
            cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n\n";
        }

        count_smaller_1 = ((left_idx_1 >= 0)&&(left_idx_1 < length_1 - 1))? left_idx_1 + 1: 0;
        count_smaller_2 = ((left_idx_2 >= 0)&&(left_idx_2 < length_2 - 1))? left_idx_2 + 1: 0;
        if (left_idx_1 >= length_1) {count_smaller_1 = length_1;}
        if (left_idx_2 >= length_2) {count_smaller_2 = length_2;}

        count_smaller = count_smaller_1 + count_smaller_2;

        if (test_timer >= 0) {cout << "count_smaller = " << count_smaller << "\n\n";}

        if (count_smaller < criteria) {
            left = mid;
            left_idx_1_wall = left_idx_1;
            left_idx_2_wall = left_idx_2;
        }

        else if (count_smaller == criteria) {break;}

        else {
            right = mid;
            right_idx_1_wall = right_idx_1;
            right_idx_2_wall = right_idx_2;
        }

        if (just_one_more == 0) {
            mid = left + (right - left) / 2;
            break;
        }
        if (left + 1 >= right) {just_one_more = 0;}
    }

    if ((left_idx_1 >= 0)&&(left_idx_1 < length_1)) {left_candidate_idx_1 = left_idx_1;}
    if ((left_idx_2 >= 0)&&(left_idx_2 < length_2)) {left_candidate_idx_2 = left_idx_2;}
    if (left_idx_1 == length_1) {left_candidate_idx_1 = length_1 - 1;}
    if (left_idx_2 == length_2) {left_candidate_idx_2 = length_2 - 1;}

    if (test_timer >= 0) {
        cout << "\n\nleft_candidate_idx_1 = " << left_candidate_idx_1;
        cout << "\nleft_candidate_idx_2 = " << left_candidate_idx_2 << "\n\n";
    }

    if (test_timer >= 0) {cout << "second big loop\n";}

    left_idx_1_wall = (left_idx_1 >= 0)? left_idx_1: 0;
    left_idx_2_wall = (left_idx_2 >= 0)? left_idx_2: 0;
    right_idx_1_wall = length_1 - 1;
    right_idx_2_wall = length_2 - 1;

    left = mid;
    right = (nums1[length_1 - 1] <= nums2[length_2 - 1])? nums2[length_2 - 1]: nums1[length_1 - 1];

    just_one_more = 1;
    while (left <= right) {
        mid = left + (right - left) / 2;

        if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";}

        if (mid < nums1[0]) {left_idx_1 = -1, right_idx_1 = -1;}
        else if (mid > nums1[length_1 - 1]) {left_idx_1 = length_1, right_idx_1 = length_1;}
        else {
            left_idx_1 = left_idx_1_wall, right_idx_1 = right_idx_1_wall, one_more = 1;
            while (left_idx_1 <= right_idx_1) {
                mid_idx_1 = left_idx_1 + (right_idx_1 - left_idx_1) / 2;

                //if (nums1[mid_idx_1] > mid) {right_idx_1 = mid_idx_1;}

                //else {left_idx_1 = mid_idx_1;}

                if (nums1[mid_idx_1] < mid) {left_idx_1 = mid_idx_1 + 1;}

                else if (nums1[mid_idx_1] == mid) {left_idx_1 = mid_idx_1;}

                else {right_idx_1 = mid_idx_1;}


                //if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";test_timer++;}
                //if (test_timer > 10) {just_one_more = 0;break;}

                if (one_more == 0) {break;}

                if (left_idx_1 + 1 >= right_idx_1) {one_more = 0;}
            }
        }

        //if (test_timer >= 0) {cout << "left = \n";}

        //if left_idx_2 is in valid range, nums2[left_idx_2] will be the 1st that is no less than mid
        if (mid < nums2[0]) {left_idx_2 = -1, right_idx_2 = -1;}
        else if (mid > nums2[length_2 - 1]) {left_idx_2 = length_2, right_idx_2 = length_2;}
        else {
            left_idx_2 = left_idx_2_wall, right_idx_2 = right_idx_2_wall, one_more = 1;
            while (left_idx_2 <= right_idx_2) {
                mid_idx_2 = left_idx_2 + (right_idx_2 - left_idx_2) / 2;

                if (nums2[mid_idx_2] < mid) {left_idx_2 = mid_idx_2 + 1;}

                else if (nums2[mid_idx_2] == mid) {left_idx_2 = mid_idx_2;}

                else {right_idx_2 = mid_idx_2;}

                //if (test_timer >= 0) {cout << "left_idx_2 = " << left_idx_2cout << ", mid_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n";}

                //if (test_timer >= 0) {cout << "left = " << left << ", mid = " << mid << ", right = " << right << "\n";test_timer++;}
                //if (test_timer > 10) {just_one_more = 0;break;}

                if (one_more == 0) {break;}

                if (left_idx_2 + 1 >= right_idx_2) {one_more = 0;}
            }
        }

        if (test_timer >= 0) {
            cout << "left_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
            cout << "left_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n\n";
        }

        count_larger_1 = ((left_idx_1 >= 0)&&(left_idx_1 < length_1 - 1))? (length_1 - right_idx_1): 0;
        count_larger_2 = ((left_idx_2 >= 0)&&(left_idx_2 < length_2 - 1))? (length_2 - right_idx_2): 0;

        count_larger = count_larger_1 + count_larger_2;

        if (test_timer >= 0) {cout << "count_larger = " << count_larger << "\n\n";}

        if (count_larger < criteria) {
            right = mid;
            right_idx_1_wall = (right_idx_1 < right_idx_1_wall)? right_idx_1: right_idx_1_wall;
            right_idx_2_wall = (right_idx_2 < right_idx_2_wall)? right_idx_2: right_idx_2_wall;
        }

        else if (count_larger == criteria) {break;}

        else {
            left = mid;
            left_idx_1_wall = left_idx_1;
            left_idx_2_wall = left_idx_2;
        }

        if (just_one_more == 0) {
            mid = left + (right - left) / 2;
            break;
        }
        if (left + 1 >= right) {just_one_more = 0;}
    }

    if ((right_idx_1 >= 0)&&(right_idx_1 < length_1)) {right_candidate_idx_1 = left_idx_1;}
    if ((right_idx_2 >= 0)&&(right_idx_2 < length_2)) {right_candidate_idx_2 = left_idx_2;}

    if (test_timer >= 0) {
        cout << "\n\nright_candidate_idx_1 = " << right_candidate_idx_1;
        cout << "\nright_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";

        cout << "\ncount_smaller = " << count_smaller << "\n";
        cout << "count_larger = " << count_larger << "\n\n";
    }



    if (is_odd == 0){
        while (count_smaller + count_larger + 1 < length_1 + length_2) {
            if (count_smaller < count_larger) {
                if (nums1[left_candidate_idx_1] <= nums2[left_candidate_idx_2]) {
                   left_candidate_idx_1++;
                }

                else {left_candidate_idx_1++;}



                /*if (left_candidate_idx_1 + 1 < right_candidate_idx_1) {
                    left_candidate_idx_1++;
                }
                else if (left_candidate_idx_2 + 1 < right_candidate_idx_2) {
                    left_candidate_idx_2++;
                }*/

                count_smaller++;
            }

            else if (count_smaller > count_larger) {
                if (nums1[right_candidate_idx_1] >= nums2[right_candidate_idx_2]) {
                   right_candidate_idx_1--;
                }

                else {right_candidate_idx_1--;}

                /*if (left_candidate_idx_1 + 1 < right_candidate_idx_1) {
                    right_candidate_idx_1--;
                }
                else if (left_candidate_idx_2 + 1 < right_candidate_idx_2) {
                    right_candidate_idx_2--;
                }
                */

                count_larger++;
            }

            else {
                if (nums1[left_candidate_idx_1] <= nums2[left_candidate_idx_2]) {
                   left_candidate_idx_1++;
                }
                else {left_candidate_idx_1++;}

                if (nums1[right_candidate_idx_1] >= nums2[right_candidate_idx_2]) {
                   right_candidate_idx_1--;
                }
                else {right_candidate_idx_1--;}

                /*if (left_candidate_idx_1 + 1 < right_candidate_idx_1) {
                    left_candidate_idx_1++;
                }
                if (left_candidate_idx_2 + 1 < right_candidate_idx_2) {
                    right_candidate_idx_2--;
                }*/


                count_smaller++;
                count_larger++;
            }
        }
    }

    else {
        while (count_smaller + count_larger < length_1 + length_2) {
            if (count_smaller < count_larger) {
                if (nums1[left_candidate_idx_1] <= nums2[left_candidate_idx_2]) {
                   left_candidate_idx_1++;
                }

                else {left_candidate_idx_1++;}
                /*if (left_candidate_idx_1 + 1 < right_candidate_idx_1) {
                    left_candidate_idx_1++;
                }
                else if (left_candidate_idx_2 + 1 < right_candidate_idx_2) {
                    left_candidate_idx_2++;
                }*/

                count_smaller++;
            }

            else if (count_smaller > count_larger) {
                if (nums1[right_candidate_idx_1] >= nums2[right_candidate_idx_2]) {
                   right_candidate_idx_1--;
                }

                else {right_candidate_idx_1--;}

                /*if (left_candidate_idx_1 + 1 < right_candidate_idx_1) {
                    right_candidate_idx_1--;
                }
                else if (left_candidate_idx_2 + 1 < right_candidate_idx_2) {
                    right_candidate_idx_2--;
                }*/

                count_larger++;
            }

            else {
                if (nums1[left_candidate_idx_1] <= nums2[left_candidate_idx_2]) {
                   left_candidate_idx_1++;
                }

                else {left_candidate_idx_1++;}


                if (nums1[right_candidate_idx_1] >= nums2[right_candidate_idx_2]) {
                   right_candidate_idx_1--;
                }
                else {right_candidate_idx_1--;}


                /*if (left_candidate_idx_1 + 1 < right_candidate_idx_1) {
                    left_candidate_idx_1++;
                }
                if (left_candidate_idx_2 + 1 < right_candidate_idx_2) {
                    right_candidate_idx_2--;
                }*/
                count_smaller++;
                count_larger++;
            }
        }
    }




    if (test_timer >= 0) {
        cout << "\n\nleft_candidate_idx_1 = " << left_candidate_idx_1;
        cout << "\nleft_candidate_idx_2 = " << left_candidate_idx_2;
        cout << "\nright_candidate_idx_1 = " << right_candidate_idx_1;
        cout << "\nright_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";

        cout << "\ncount_smaller = " << count_smaller << "\n";
        cout << "count_larger = " << count_larger << "\n\n";
    }

    if (left_candidate_idx_1 + 1 < right_candidate_idx_1) {return nums1[(left_candidate_idx_1 + right_candidate_idx_1) / 2];}
    if (left_candidate_idx_2 + 1 < right_candidate_idx_2) {return nums2[(left_candidate_idx_2 + right_candidate_idx_2) / 2];}

    if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
    else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
    else {
        part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
        nums1[left_candidate_idx_1] : nums2[left_candidate_idx_2];
    }

    if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
    else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
    else {
        part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
        nums1[right_candidate_idx_1] : nums2[right_candidate_idx_2];
    }



    if (test_timer >= 0) {cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";}

    //if (test_timer >= 0) {cout << "\n\npart_1 = " << part_1 << ", part_2 = " << part_2 << "\n";}
    return (part_1 + part_2) / 2;
}












/*got to admit, i really did not expect search by value turned out to be this messy

first, and so far the only algo, that worked, is to:
1. search by value
2. count identical of that value in every "search by value"
3. if crossed criteria, then bang! we got it!

later i tried to just search by value without counting identical - all ended up in failure

then i tried to search smaller + search larger to narrow down the desired value - all turned out to be messy,
so many bugs, so exhausting so laborious to fix, with little to NO PROGRESS,
just messy nasty fixing which might even bringing in new problems



i HAVE NOT tried to search by index, let's try it today

20210102
*/



//almost start anew, another anew, SEARCH BY INDEX
//if this one got it done, i'm done with this problem
//so fucking exhausting in trying to get some SEARCH BY VALUE algos work
//unfortunately all ended up in, deep bug fixing frenzy if not in failure,
//lets try it again
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    if ((length_1 == 0)&&(length_2 == 0)) {return 0;}
    double part_1 = 0, part_2 = 0;
    int test_timer = 0;

    if (length_1 == 0) {
        part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        return (part_1 + part_2) / 2;
    }
    if (length_2 == 0) {
        part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        return (part_1 + part_2) / 2;
    }
    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = length_1 + length_2;
    int is_odd = (criteria & 1 == 1)? 1: 0;
    criteria /= 2;//criteria = (length_1 + length_2) / 2, do in 2 steps so as to do 1 less addition operation

    if (test_timer >= 0) {
        cout << "is_odd = " << is_odd << "\n";
        cout << "length_1 + length_2 = " << (length_1 + length_2) << "\n";
        cout << "criteria = " << criteria << "\n\n";
    }

    int left_idx_1_wall = 0, right_idx_1_wall = length_1 - 1;
    int left_idx_2_wall = 0, right_idx_2_wall = length_2 - 1;
    int left_idx_1 = 0, search_idx_1 = length_1 / 2, right_idx_1 = length_1 - 1;
    int left_idx_2 = 0, search_idx_2 = length_2 / 2, right_idx_2 = length_2 - 1;
    int how_many_on_the_left, how_many_on_the_left_1, how_many_on_the_left_2;
    int left_candidate_idx_1 = -1, right_candidate_idx_1 = -1, left_candidate_idx_2 = -1, right_candidate_idx_2 = -1;

    int search_val, one_more;

    //find position of nums1[length_1 - 1] in nums2 & nums2[length_2 - 1] in nums1
    //use it to decide


    while (true) {
        //find nums2[mid_index_2]'s position in nums1

        if (left_idx_2_wall < 0) {search_idx_2 = 0;}
        else if (left_idx_2_wall >= length_2) {search_idx_2 = length_2 - 1;}
        else {search_idx_2 = (left_idx_2_wall + right_idx_2_wall) / 2;}

        search_val = nums2[search_idx_2];

        if (test_timer >= 0) {
            cout << "\nsearch_idx_2 = " << search_idx_2;
            cout << ", search_val = " << search_val << "\n";
        }

        if (search_val < nums1[0]) {left_idx_1 = -1, right_idx_1 = -1;}
        else if (search_val > nums1[length_1 - 1]) {left_idx_1 = length_1, right_idx_1 = length_1;}
        else {
            left_idx_1 = left_idx_1_wall, right_idx_1 = right_idx_1_wall, one_more = 1;
            while (left_idx_1 <= right_idx_1) {
                search_idx_1 = left_idx_1 + (right_idx_1 - left_idx_1) / 2;

                if (nums1[search_idx_1] < search_val) {left_idx_1 = search_idx_1 + 1;}

                else {right_idx_1 = search_idx_1;}

                if (one_more == 0) {break;}

                if (left_idx_1 + 1 >= right_idx_1) {one_more = 0;}
            }
        }

        how_many_on_the_left_1 = (left_idx_1 > 0)? left_idx_1: 0;
        how_many_on_the_left_2 = search_idx_2;
        how_many_on_the_left = how_many_on_the_left_1 + how_many_on_the_left_2;

        if (test_timer >= 0) {
            cout << "\nhow_many_on_the_left = " << how_many_on_the_left;
            cout << "\nleft_idx_1 = " << left_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
        }

        if (how_many_on_the_left == criteria) {
            left_idx_1 = search_idx_1;
            left_idx_1_wall = search_idx_1;
            //break;
        }

        else if (how_many_on_the_left < criteria) {
            left_idx_1_wall = left_idx_1 + 1;
            left_idx_2 = search_idx_2 + 1;
        }

        else {
            right_idx_1_wall = left_idx_1;
            right_idx_2 = search_idx_2;
        }



        //find nums1[mid_index_1]'s position in nums2
        if (left_idx_1_wall < 0) {search_idx_1 = 0;}
        else if (left_idx_1_wall >= length_1) {search_idx_1 = length_1 - 1;}
        else {search_idx_1 = (left_idx_1_wall + right_idx_1_wall) / 2;}

        search_val = nums1[search_idx_1];

        if (test_timer >= 0) {
            cout << "\nsearch_idx_1 = " << search_idx_1;
            cout << ", search_val = " << search_val << "\n";
        }

        if (search_val < nums2[0]) {left_idx_2 = -1, right_idx_2 = -1;}
        else if (search_val > nums2[length_2 - 1]) {left_idx_2 = length_2, right_idx_2 = length_2;}
        else {
            left_idx_2 = left_idx_2_wall, right_idx_2 = right_idx_2_wall, one_more = 1;
            while (left_idx_2 <= right_idx_2) {
                search_idx_2 = left_idx_2 + (right_idx_2 - left_idx_2) / 2;

                if (nums2[search_idx_2] < search_val) {left_idx_2 = search_idx_2 + 1;}

                else {right_idx_2 = search_idx_2;}

                if (one_more == 0) {break;}

                if (left_idx_2 + 1 >= right_idx_2) {one_more = 0;}
            }
        }

        how_many_on_the_left_1 = search_idx_1;
        how_many_on_the_left_2 = (left_idx_2 > 0)? left_idx_2: 0;
        how_many_on_the_left = how_many_on_the_left_1 + how_many_on_the_left_2;

        if (test_timer >= 0) {
            cout << "\nhow_many_on_the_left = " << how_many_on_the_left;
            cout << "\nleft_idx_2 = " << left_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n";
        }

        if (how_many_on_the_left == criteria) {
            left_idx_2 = search_idx_2;
            left_idx_2_wall = search_idx_2;
            //break;
        }

        else if (how_many_on_the_left < criteria) {
            left_idx_1 = search_idx_1 + 1;
            left_idx_2_wall = left_idx_2 + 1;
        }

        else {
            right_idx_1 = search_idx_1;
            right_idx_2_wall = left_idx_2;
        }



        if ((left_idx_1_wall + 1 >= right_idx_1_wall)&&(left_idx_2_wall + 1 >= right_idx_2_wall)) {break;}

        if (test_timer >= 0) {
            cout << "\nleft_idx_1_wall = " << left_idx_1_wall << ", right_idx_1_wall = " << right_idx_1_wall;
            cout << "\nleft_idx_2_wall = " << left_idx_2_wall << ", right_idx_2_wall = " << right_idx_2_wall << "\n\n";
            test_timer++;
        }
        if (test_timer > 15) {break;}

    }

    if (test_timer >= 0) {
        cout << "\n\nleft_idx_1 = " << left_idx_1;
        cout << "\nleft_idx_2 = " << left_idx_2 << "\n\n";
    }

    if (is_odd == 1){
        if (left_idx_1 < length_1) {right_candidate_idx_1 = left_idx_1;}
        if (left_idx_2 < length_2) {right_candidate_idx_2 = left_idx_2;}

        if (right_candidate_idx_1 < 0) {
            part_2 = nums2[right_candidate_idx_2];
        }
        else if (right_candidate_idx_2 < 0) {
            part_2 = nums1[right_candidate_idx_1];
        }
        else {
            part_2 = (nums1[right_candidate_idx_1] > nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1]: nums2[right_candidate_idx_2];
        }

        if (test_timer >= 0) {
            cout << "\nright_candidate_idx_1 = " << right_candidate_idx_1;
            cout << ", right_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";
            cout << "part_2 = " << part_2 << "\n";
        }

        return part_2;
    }

    else {
        if (left_idx_1 > 0) {left_candidate_idx_1 = left_idx_1 - 1;}
        if ((left_idx_1 >= 0)&&(left_idx_1 < length_1)) {right_candidate_idx_1 = left_idx_1;}

        if (left_idx_2 > 0) {left_candidate_idx_2 = left_idx_1 - 1;}
        if ((left_idx_2 >= 0)&&(left_idx_2 < length_2)) {right_candidate_idx_2 = left_idx_2;}

        if (left_candidate_idx_1 < 0) {part_1 = nums2[left_candidate_idx_2];}
        else if (left_candidate_idx_2 < 0) {part_1 = nums1[left_candidate_idx_1];}
        else {
            part_1 = (nums1[left_candidate_idx_1] >= nums2[left_candidate_idx_2])?
            nums1[left_candidate_idx_1]: nums2[left_candidate_idx_2];
        }

        if (right_candidate_idx_1 < 0) {part_2 = nums2[right_candidate_idx_2];}
        else if (right_candidate_idx_2 < 0) {part_2 = nums1[right_candidate_idx_1];}
        else {
            part_2 = (nums1[right_candidate_idx_1] <= nums2[right_candidate_idx_2])?
            nums1[right_candidate_idx_1]: nums2[right_candidate_idx_2];
        }
    }


    if (test_timer >= 0) {
        cout << "\n\nleft_candidate_idx_1 = " << left_candidate_idx_1;
        cout << "\nleft_candidate_idx_2 = " << left_candidate_idx_2;
        cout << "\nright_candidate_idx_1 = " << right_candidate_idx_1;
        cout << "\nright_candidate_idx_2 = " << right_candidate_idx_2 << "\n\n";

        cout << "part_1 = " << part_1 << "\npart_2 = " << part_2 << "\n\n";
    }

    //if (test_timer >= 0) {cout << "\n\npart_1 = " << part_1 << ", part_2 = " << part_2 << "\n";}
    return (part_1 + part_2) / 2;
}






//another one. used MORE MEMORY?! SERIOUSLY?!
double findMedianSortedArrays_2(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    if ((length_1 == 0)&&(length_2 == 0)) {return 0;}
    double part_1 = 0, part_2 = 0;
    int test_timer = -1;

    if (length_1 == 0) {
        part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        return (part_1 + part_2) / 2;
    }
    if (length_2 == 0) {
        part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        return (part_1 + part_2) / 2;
    }
    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = length_1 + length_2;
    int is_odd = (criteria & 1 == 1)? 1: 0;
    criteria /= 2;//criteria = (length_1 + length_2) / 2, do in 2 steps so as to do 1 less addition operation

    if (test_timer >= 0) {
        cout << "is_odd = " << is_odd << ", criteria = " << criteria << "\n";
        cout << "length_1 + length_2 = " << (length_1 + length_2) << "\n";
    }

    int left_idx_1 = 0, mid_idx_1, right_idx_1 = length_1 - 1;
    int left_idx_2 = 0, mid_idx_2, right_idx_2 = length_2 - 1;
    int how_many_on_the_left, how_many_on_the_left_1, how_many_on_the_left_2;

    int search_idx_1, search_idx_2;
    int remaining_range_1 = length_1 - 1, remaining_range_2 = length_2 - 1;

    int search_val, one_more = 1;

    while (true) {

        if (left_idx_1 < 0) {search_idx_1 = -1;}
        else if (left_idx_1 < length_1) {search_idx_1 = (left_idx_1 + right_idx_1) / 2;}
        else {search_idx_1 = length_1;}

        if (left_idx_2 < 0) {search_idx_2 = -1;}
        else if (left_idx_2 < length_2) {search_idx_2 = (left_idx_2 + right_idx_2) / 2;}
        else {search_idx_2 = length_2;}

        how_many_on_the_left = search_idx_1 + search_idx_2 + 2;

        if (test_timer >= 0) {
            cout << "\nhow_many_on_the_left = " << how_many_on_the_left << "\n";
            cout << "search_idx_1 = " << search_idx_1 << ", search_idx_2 = " << search_idx_2 << "\n";
            cout << "left_idx_1 = " << left_idx_1 << ", search_idx_1 = " << search_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
            cout << "left_idx_2 = " << left_idx_2 << ", search_idx_2 = " << search_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n\n";
        }

        if (how_many_on_the_left <= criteria) {
            //cout << "bee~~~\n";
            if ((search_idx_1 >= length_1 - 1)||(left_idx_1 == right_idx_1)) {
                if (left_idx_2 + 1 == right_idx_2) {left_idx_2 = right_idx_2;}
                else {left_idx_2 = search_idx_2;}
                //left_idx_2 = (search_idx_2 + 1 < right_idx_2)? search_idx_2 + 1: right_idx_2;
            }

            else if ((search_idx_2 >= length_2 - 1)||(left_idx_2 == right_idx_2)) {
                if (left_idx_1 + 1 == right_idx_1) {left_idx_1 = right_idx_1;}
                else {left_idx_1 = search_idx_1;}
                //left_idx_1 = (search_idx_1 + 1 < right_idx_1)? search_idx_1 + 1: right_idx_1;
            }

            else {
                if (nums1[search_idx_1] <= nums2[search_idx_2]) {
                    //left_idx_1 = search_idx_1 + 1;
                    if (left_idx_1 == length_1 - 1) {left_idx_1 = length_1;}
                    else if (left_idx_1 + 1 == right_idx_1) {left_idx_1 = right_idx_1;}
                    else {left_idx_1 = search_idx_1;}
                    //left_idx_1 = (search_idx_1 + 1 < right_idx_1)? search_idx_1 + 1: right_idx_1;
                }
                else {
                    if (left_idx_2 == length_2 - 1) {left_idx_2 = length_2;}
                    else if (left_idx_2 + 1 == right_idx_2) {left_idx_2 = right_idx_2;}
                    else {left_idx_2 = search_idx_2;}
                    //left_idx_2 = (search_idx_2 + 1 < right_idx_2)? search_idx_2 + 1: right_idx_2;
                }
            }
        }

        else {
            //cout << "dee~~~\n";

            if ((search_idx_1 >= length_1 - 1)||(left_idx_1 == right_idx_1)) {right_idx_2 = search_idx_2;}

            else if ((search_idx_2 >= length_2 - 1)||(left_idx_2 == right_idx_2)) {right_idx_1 = search_idx_1;}

            else {
                if (nums1[search_idx_1] >= nums2[search_idx_2]) {
                    if (right_idx_1 == 0) {left_idx_1 = -1, right_idx_1 = -1;}
                    else {right_idx_1 = search_idx_1;}
                }

                else {
                    if (right_idx_2 == 0) {left_idx_2 = -1, right_idx_2 = -1;}
                    else {right_idx_2 = search_idx_2;}
                }
            }
        }

        if (test_timer >= 0) {
            cout << "left_idx_1 = " << left_idx_1 << ", search_idx_1 = " << search_idx_1 << ", right_idx_1 = " << right_idx_1 << "\n";
            cout << "left_idx_2 = " << left_idx_2 << ", search_idx_2 = " << search_idx_2 << ", right_idx_2 = " << right_idx_2 << "\n\n";
        }

        //if (one_more == 0) {break;}
        if ((left_idx_1 + 2 >= right_idx_1)&&(left_idx_2 + 2 >= right_idx_2)) {
            //one_more = 0;
            break;
        }

        if (test_timer >= 0) {test_timer++;}
        if (test_timer >= 10) {break;}
    }

    priority_queue<int, vector<int>, greater<int>> push_n_pop_n_get_result;

    if (test_timer >= 0) {cout << "\n\n";}

    if (left_idx_1 >= 0) {
        for (int i = left_idx_1; i <= right_idx_1; i++) {
            push_n_pop_n_get_result.push(nums1[i]);
            if (test_timer >= 0) {cout << "pushed " << nums1[i] << ", ";}
        }
        if (right_idx_1 < length_1 - 1) {push_n_pop_n_get_result.push(nums1[right_idx_1 + 1]);}
    }

    if (test_timer >= 0) {cout << "\n\n";}

    if (left_idx_2 >= 0) {
        for (int i = left_idx_2; i <= right_idx_2; i++) {
            push_n_pop_n_get_result.push(nums2[i]);
            if (test_timer >= 0) {cout << "pushed " << nums2[i] << ", ";}
        }
        if (right_idx_2 < length_2 - 1) {push_n_pop_n_get_result.push(nums2[right_idx_2 + 1]);}
    }

    if (left_idx_1 < 0) {left_idx_1 = 0;}if (left_idx_2 < 0) {left_idx_2 = 0;}

    int remaining = criteria - left_idx_1 - left_idx_2 + is_odd;

    if (test_timer >= 0) {cout << "\nremaining = " << remaining << "\n\n";}

    int done = 0;
    while (true) {
        if (remaining == 1) {
            part_1 = push_n_pop_n_get_result.top();
            if (is_odd == 1) {part_2 = part_1;done = 1;}
        }
        else if (remaining == 0) {
            part_2 = push_n_pop_n_get_result.top();
            done = 1;
        }
        if (done != 0) {break;}
        push_n_pop_n_get_result.pop();
        remaining--;
    }

    return (part_1 + part_2) / 2;
}



//another one. used MORE MEMORY?! SERIOUSLY?!
double findMedianSortedArrays_2_1(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    if ((length_1 == 0)&&(length_2 == 0)) {return 0;}
    double part_1 = 0, part_2 = 0;
    //int test_timer = -1;

    if (length_1 == 0) {
        part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        return (part_1 + part_2) / 2;
    }
    if (length_2 == 0) {
        part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        return (part_1 + part_2) / 2;
    }
    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = length_1 + length_2;
    int is_odd = (criteria & 1 == 1)? 1: 0;
    criteria /= 2;//criteria = (length_1 + length_2) / 2, do in 2 steps so as to do 1 less addition operation

    int left_idx_1 = 0, mid_idx_1, right_idx_1 = length_1 - 1;
    int left_idx_2 = 0, mid_idx_2, right_idx_2 = length_2 - 1;
    int how_many_on_the_left, search_idx_1, search_idx_2;

    int search_val;

    while (true) {
        if (left_idx_1 < 0) {search_idx_1 = -1;}
        else if (left_idx_1 < length_1) {search_idx_1 = (left_idx_1 + right_idx_1) / 2;}
        else {search_idx_1 = length_1;}

        if (left_idx_2 < 0) {search_idx_2 = -1;}
        else if (left_idx_2 < length_2) {search_idx_2 = (left_idx_2 + right_idx_2) / 2;}
        else {search_idx_2 = length_2;}

        how_many_on_the_left = search_idx_1 + search_idx_2 + 2;

        if (how_many_on_the_left <= criteria) {
            if ((search_idx_1 >= length_1 - 1)||(left_idx_1 == right_idx_1)) {
                if (left_idx_2 + 1 == right_idx_2) {left_idx_2 = right_idx_2;}
                else {left_idx_2 = search_idx_2;}
            }

            else if ((search_idx_2 >= length_2 - 1)||(left_idx_2 == right_idx_2)) {
                if (left_idx_1 + 1 == right_idx_1) {left_idx_1 = right_idx_1;}
                else {left_idx_1 = search_idx_1;}
            }

            else {
                if (nums1[search_idx_1] <= nums2[search_idx_2]) {
                    if (left_idx_1 == length_1 - 1) {left_idx_1 = length_1;}
                    else if (left_idx_1 + 1 == right_idx_1) {left_idx_1 = right_idx_1;}
                    else {left_idx_1 = search_idx_1;}
                }
                else {
                    if (left_idx_2 == length_2 - 1) {left_idx_2 = length_2;}
                    else if (left_idx_2 + 1 == right_idx_2) {left_idx_2 = right_idx_2;}
                    else {left_idx_2 = search_idx_2;}
                }
            }
        }

        else {
            if ((search_idx_1 >= length_1 - 1)||(left_idx_1 == right_idx_1)) {right_idx_2 = search_idx_2;}

            else if ((search_idx_2 >= length_2 - 1)||(left_idx_2 == right_idx_2)) {right_idx_1 = search_idx_1;}

            else {
                if (nums1[search_idx_1] >= nums2[search_idx_2]) {
                    if (right_idx_1 == 0) {left_idx_1 = -1, right_idx_1 = -1;}
                    else {right_idx_1 = search_idx_1;}
                }

                else {
                    if (right_idx_2 == 0) {left_idx_2 = -1, right_idx_2 = -1;}
                    else {right_idx_2 = search_idx_2;}
                }
            }
        }

        if ((left_idx_1 + 2 >= right_idx_1)&&(left_idx_2 + 2 >= right_idx_2)) {
            break;
        }

    }

    priority_queue<int, vector<int>, greater<int>> push_n_pop_n_get_result;

    if (left_idx_1 >= 0) {
        for (int i = left_idx_1; i <= right_idx_1; i++) {
            push_n_pop_n_get_result.push(nums1[i]);
        }
        if (right_idx_1 < length_1 - 1) {push_n_pop_n_get_result.push(nums1[right_idx_1 + 1]);}
    }

    if (left_idx_2 >= 0) {
        for (int i = left_idx_2; i <= right_idx_2; i++) {
            push_n_pop_n_get_result.push(nums2[i]);
        }
        if (right_idx_2 < length_2 - 1) {push_n_pop_n_get_result.push(nums2[right_idx_2 + 1]);}
    }

    if (left_idx_1 < 0) {left_idx_1 = 0;}if (left_idx_2 < 0) {left_idx_2 = 0;}



    int array_length_1 = 0;
    if (left_idx_1 >= 0) {
        array_length_1 = right_idx_1 - left_idx_1 + 1;
        if (right_idx_1 < length_1 - 1) {
            array_length_1++;
            right_idx_1++;
        }
    }

    int array_length_2 = 0;
    if (left_idx_2 >= 0) {
        array_length_2 = right_idx_2 - left_idx_2 + 1;
        if (right_idx_2 < length_2 - 1) {
            array_length_2++;
            right_idx_2++;
        }
    }

    int array_length = array_length_1 + array_length_2;
    int an_array[array_length];
    int array_index = 0;
    if (left_idx_1 >= 0) {
        for (int i = left_idx_1; i <= right_idx_1; i++) {
            an_array[array_index] = nums1[i];
            array_index++;
        }
    }

    if (left_idx_2 >= 0) {
        for (int i = left_idx_2; i <= right_idx_2; i++) {
            an_array[array_index] = nums2[i];
            array_index++;
        }
    }




    int remaining = criteria - left_idx_1 - left_idx_2 + is_odd;

    int done = 0;
    while (true) {
        if (remaining == 1) {
            part_1 = push_n_pop_n_get_result.top();
            if (is_odd == 1) {part_2 = part_1;done = 1;}
        }
        else if (remaining == 0) {
            part_2 = push_n_pop_n_get_result.top();
            done = 1;
        }
        if (done != 0) {break;}
        push_n_pop_n_get_result.pop();
        remaining--;
    }

    return (part_1 + part_2) / 2;
}











void merge_sort (int a[], int length) {//20201206
    int b[length];
    for (int i = 0; i < length; i++) {b[i] = a[i];}

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        b[k] = a[i];
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
                            b[k] = a[i];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k] = a[j];
                        j++, j_step++;
                    }

                    else if (a[i] <= a[j]) {
                        b[k] = a[i];
                        i++, i_step++;
                    }

                    else if (a[i] > a[j]) {
                        b[k] = a[j];
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
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k] = b[j];
                        j++, j_step++;
                    }

                    else if (b[i] <= b[j]) {
                        a[k] = b[i];
                        i++, i_step++;
                    }

                    else if (b[i] > b[j]) {
                        a[k] = b[j];
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
        }
    }
}

//will this one be top 2?
//CURRENTLY MY BEST, version 2.1.1
//leetcode testing give less credit to this algorithm than this algorithm deserved
//in every mass test i conducted, this algo is blazing fast SECOND ONLY only to some other poeple's beautiful invention
//yet leetcode claim that my work is only faster than 2/3?
double findMedianSortedArrays_2_1_1(vector<int>& nums1, vector<int>& nums2) {
    int length_1 = nums1.size(), length_2 = nums2.size();
    if ((length_1 == 0)&&(length_2 == 0)) {return 0;}
    double part_1 = 0, part_2 = 0;

    if (length_1 == 0) {
        part_1 = nums2[(length_2 - 1) / 2], part_2 = nums2[length_2 / 2];
        return (part_1 + part_2) / 2;
    }
    if (length_2 == 0) {
        part_1 = nums1[(length_1 - 1) / 2], part_2 = nums1[length_1 / 2];
        return (part_1 + part_2) / 2;
    }
    if ((length_1 == 1)&&(length_2 == 1)) {
        part_1 = nums1[0], part_2 = nums2[0];
        return (part_1 + part_2) / 2;
    }

    int criteria = length_1 + length_2;
    int is_odd = (criteria & 1 == 1)? 1: 0;
    criteria /= 2;//criteria = (length_1 + length_2) / 2, do in 2 steps so as to do 1 less addition operation

    int left_idx_1 = 0, mid_idx_1, right_idx_1 = length_1 - 1;
    int left_idx_2 = 0, mid_idx_2, right_idx_2 = length_2 - 1;
    int how_many_on_the_left, search_idx_1, search_idx_2;

    int search_val;

    while (true) {
        if (left_idx_1 < 0) {search_idx_1 = -1;}
        else if (left_idx_1 < length_1) {search_idx_1 = left_idx_1 + (right_idx_1 - left_idx_1) / 2;}
        else {search_idx_1 = length_1;}

        if (left_idx_2 < 0) {search_idx_2 = -1;}
        else if (left_idx_2 < length_2) {search_idx_2 = left_idx_2 + (right_idx_2 - left_idx_2) / 2;}
        else {search_idx_2 = length_2;}

        how_many_on_the_left = search_idx_1 + search_idx_2 + 2;

        if (how_many_on_the_left <= criteria) {
            if ((search_idx_1 >= length_1 - 1)||(left_idx_1 == right_idx_1)) {
                if (left_idx_2 + 1 == right_idx_2) {left_idx_2 = right_idx_2;}

                else {left_idx_2 = search_idx_2;}
            }

            else if ((search_idx_2 >= length_2 - 1)||(left_idx_2 == right_idx_2)) {
                if (left_idx_1 + 1 == right_idx_1) {left_idx_1 = right_idx_1;}

                else {left_idx_1 = search_idx_1;}
            }

            else {
                if (nums1[search_idx_1] <= nums2[search_idx_2]) {
                    if (left_idx_1 == length_1 - 1) {left_idx_1 = length_1;}

                    else if (left_idx_1 + 1 == right_idx_1) {left_idx_1 = right_idx_1;}

                    else {left_idx_1 = search_idx_1;}
                }

                else {
                    if (left_idx_2 == length_2 - 1) {left_idx_2 = length_2;}

                    else if (left_idx_2 + 1 == right_idx_2) {left_idx_2 = right_idx_2;}

                    else {left_idx_2 = search_idx_2;}
                }
            }
        }

        else {
            if ((search_idx_1 >= length_1 - 1)||(left_idx_1 == right_idx_1)) {right_idx_2 = search_idx_2;}

            else if ((search_idx_2 >= length_2 - 1)||(left_idx_2 == right_idx_2)) {right_idx_1 = search_idx_1;}

            else {
                if (nums1[search_idx_1] >= nums2[search_idx_2]) {
                    if (right_idx_1 == 0) {left_idx_1 = -1, right_idx_1 = -1;}

                    else {right_idx_1 = search_idx_1;}
                }

                else {
                    if (right_idx_2 == 0) {left_idx_2 = -1, right_idx_2 = -1;}

                    else {right_idx_2 = search_idx_2;}
                }
            }
        }

        if ((left_idx_1 + 2 >= right_idx_1)&&(left_idx_2 + 2 >= right_idx_2)) {break;}
    }

    int array_length_1 = 0, array_length_2 = 0;
    if (left_idx_1 >= 0) {
        array_length_1 = right_idx_1 - left_idx_1 + 1;
        if (right_idx_1 < length_1 - 1) {
            array_length_1++;
            right_idx_1++;
        }
    }
    if (left_idx_2 >= 0) {
        array_length_2 = right_idx_2 - left_idx_2 + 1;
        if (right_idx_2 < length_2 - 1) {
            array_length_2++;
            right_idx_2++;
        }
    }

    int array_length = array_length_1 + array_length_2, array_index = 0;
    int an_array[array_length];

    if (left_idx_1 >= 0) {
        for (int i = left_idx_1; i <= right_idx_1; i++) {
            an_array[array_index] = nums1[i];
            array_index++;
        }
    }
    if (left_idx_2 >= 0) {
        for (int i = left_idx_2; i <= right_idx_2; i++) {
            an_array[array_index] = nums2[i];
            array_index++;
        }
    }

    merge_sort(an_array, array_length);

    if (left_idx_1 < 0) {left_idx_1 = 0;}if (left_idx_2 < 0) {left_idx_2 = 0;}

    int remaining = criteria - left_idx_1 - left_idx_2 + is_odd;

    if (is_odd == 1) {return an_array[remaining - 1];}

    else {part_1 = an_array[remaining - 1], part_2 = an_array[remaining];}

    return (part_1 + part_2) / 2;
}
















int findKth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
    if (i >= nums1.size()) return nums2[j + k - 1];
    if (j >= nums2.size()) return nums1[i + k - 1];
    if (k == 1) return min(nums1[i], nums2[j]);
    int midVal1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
    int midVal2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;
    if (midVal1 < midVal2) {
        return findKth(nums1, i + k / 2, nums2, j, k - k / 2);
    } else {
        return findKth(nums1, i, nums2, j + k / 2, k - k / 2);
    }
}
double findMedianSortedArrays_OTHER_PEOPLE(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size(), left = (m + n + 1) / 2, right = (m + n + 2) / 2;
    return (findKth(nums1, 0, nums2, 0, left) + findKth(nums1, 0, nums2, 0, right)) / 2.0;
}


double findMedianSortedArrays_other_people_2(vector<int>& nums1, vector<int>& nums2) {

    int len1=nums1.size();
    int len2=nums2.size();
    int *str=new int[len1+len2];
    int k=0,i=0,j=0,l=0,m=0;
    while(i<len1 && j<len2){
        if(nums1[i]<nums2[j]){
            str[k++]=nums1[i++];
        }
        else{
            str[k++]=nums2[j++];
        }
    }
    if(i<len1){
        for(l=0;l<len1-i;l++){
            str[k+l]=nums1[i+l];
        }
    }
    if(j<len2){
        for(l=0;l<len2-j;l++){
            str[k+l]=nums2[j+l];
        }
    }
    m=(len1+len2)/2;
    if((len1+len2)%2==0){
        return (double)(str[m-1]+str[m])/2;
    }
    else{
        return (double)str[m];
    }
}



double singleMedian(int*arr,int n)
{
    if(n==0)
        return -1;
    if(n&1)
    {
        return (double )arr[n/2];
    }
    else
    {
        return (double)((arr[n/2]+arr[n/2-1])/2.0);

    }

}
double mo2(int a,int b)
{
    return( double )(a+b)/2.0;

}
double mo3(int a,int b,int c)
{
    return (double)(a+b+c-min(a,min(b,c))-max(a,max(b,c)))/1.0;

}
double mo4(int a,int b,int c,int d)
{
    return (double)((a+b+c+d-min(a,min(b,min(c,d)))-max(a,max(b,max(c,d))))/2.0);

}
double findMedianUntil(int *arr1,int n,int *arr2,int m)
{
    /*cout<<"arr1 is "<<endl;
    for(int i=0;i<n;i++)
        cout<<arr1[i]<<" ";
    cout<<endl;
    cout<<"arr2 is "<<endl;
    for(int i=0;i<m;i++)
    cout<<arr2[i]<<" ";
    cout<<endl;
    cout<<"n= "<<n<<" "<<"m= "<<m<<endl;
    */
    if(n==0)
        return singleMedian(arr2,m);

    if(n==1)
    {
        if(m==1)
        {
            return mo2(arr1[0],arr2[0]);

        }
        else if(m&1)
        {
            return mo2(arr2[m/2],mo3(arr1[0],arr2[m/2-1],arr2[m/2+1]));

        }
        else
        {
           /* cout<<"sonu is "<<endl;
            cout<<"a "<<arr2[m/2]<<" b "<<arr2[m/2-1]<<" c "<<arr1[0]<<endl;
           */
            return mo3(arr2[m/2],arr2[m/2-1],arr1[0]);

        }


    }
    else if(n==2)
    {
        if(m==2)
        {
           return  mo4(arr1[0],arr1[1],arr2[0],arr2[1]);

        }
        else if(m&1)
        {
            return mo3(arr2[m/2],max(arr1[0],arr2[m/2-1]),min(arr1[1],arr2[m/2+1]));

        }
        else
        {
            return mo4(arr2[m/2],arr2[m/2-1],max(arr2[m/2-2],arr1[0]),min(arr2[m/2+1],arr1[1]));

        }
    }

    int idx1=(n-1)/2;
    int idx2=(m-1)/2;

    if(arr1[idx1]<arr2[idx2])
    {
        return findMedianUntil(arr1+idx1,n/2+1,arr2,m-idx1);

    }
    else
    {
        return findMedianUntil(arr1,n/2+1,arr2+idx1,m-idx1);

    }
}
double findMedian(int *arr1,int n,int *arr2,int m)
{
    if(n<m)
    {
        return findMedianUntil(arr1,n,arr2,m);

    }
    else
        return findMedianUntil(arr2,m,arr1,n);

}
double findMedianSortedArrays_other_people_3(vector<int>& num1, vector<int>& num2) {
    int n=num1.size();
    int m=num2.size();

    int *arr1=new int [n];
    for(int i=0;i<n;i++)
    {
        arr1[i]=num1[i];
    }
    int *arr2=new int [m];
    for(int i=0;i<m;i++)
    {
        arr2[i]=num2[i];

    }
    return findMedian(arr1,n,arr2,m);
}



/*
1 million 100 long
272.11 ms - other people's beautiful code
317.539 ms - my best so far
1644.45 ms - prev my best
628.824 ms - some other people 3

100k, 1k long
39.0409 ms
41.3729 ms
179.312 ms
360.208 ms

100k, 10k long
52.7663 ms
52.6324 ms
215.297 ms
2752.7 ms

100k 100k long
67.6809 ms
69.9912 ms
252.587 ms
9425.1 ms

10k 1million long
6.5287 ms
6.7288 ms
23.7904 ms
920.495 ms


*/

int main(){
    srand(time(0));int upper_length = 100, lower_range = 0, upper_range = 100, display = 0, input = 1;
    int length_1, length_2, temp;double s, ss, sss, ssss;
    vector<int> wtf1;
    vector<int> wtf2;

    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;
    auto start_point_4 = chrono::steady_clock::now();auto end_point_4 = chrono::steady_clock::now();auto diff_4 = end_point_4 - start_point_4;

for (int m = 1; m <= 1000000; m++) {if (m % 10000 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){
        length_1 = rand()%(upper_length - 0 + 1) + 0;
        wtf1.reserve(length_1);
        if (length_1 > 0) {wtf1.push_back(rand()%(upper_length - lower_range + 1) + lower_range);}
        for(int i = 1; i < length_1; i++){
            temp = rand()%(upper_range - lower_range + 1) + lower_range;
            temp += wtf1[i - 1];
            wtf1.push_back(temp);
        }

        if (length_1 == 0) {length_2 = rand()%(upper_length - 1 + 1) + 1;}
        else {length_2 = rand()%(upper_length - 0 + 1) + 0;}
        wtf2.reserve(length_2);
        if (length_2 > 0) {wtf2.push_back(rand()%(upper_range - lower_range + 1) + lower_range);}
        for(int i = 1; i < length_2; i++){
            temp = rand()%(upper_range - lower_range + 1) + lower_range;
            temp += wtf2[i - 1];
            wtf2.push_back(temp);
        }
    }
    if (display == 1){
        cout << " = {";
        for (int i = 0; i < wtf1.size(); i++) {
            cout << wtf1[i];if (i < wtf1.size() - 1) {cout << ", ";}
        }
        cout << "}\n = {";
        for (int i = 0; i < wtf2.size(); i++) {
            cout << wtf2[i];if (i < wtf2.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    /*start_point_1 = chrono::steady_clock::now();
    s = findMedianSortedArrays_1_0(wtf1, wtf2);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;
    //cout << "\n\ncredible result = " << shit << "\n";

    start_point_2 = chrono::steady_clock::now();
    ss = findMedianSortedArrays_1_0_1(wtf1, wtf2);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    start_point_3 = chrono::steady_clock::now();
    sss = findMedianSortedArrays_1_0_1_no_timer(wtf1, wtf2);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;

    start_point_4 = chrono::steady_clock::now();
    ssss = findMedianSortedArrays_1_0_1_no_timer_with_walls(wtf1, wtf2);
    end_point_4 = chrono::steady_clock::now();
    diff_4 += end_point_4 - start_point_4;*/

    vector<int> wtf1_1(wtf1);vector<int> wtf1_2(wtf1);vector<int> wtf1_3(wtf1);vector<int> wtf1_4(wtf1);
    vector<int> wtf2_1(wtf2);vector<int> wtf2_2(wtf2);vector<int> wtf2_3(wtf2);vector<int> wtf2_4(wtf2);


    start_point_1 = chrono::steady_clock::now();
    //s = findMedianSortedArrays_OTHER_PEOPLE(wtf1, wtf2);
    s = findMedianSortedArrays_OTHER_PEOPLE(wtf1_1, wtf2_1);//best so far
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    start_point_2 = chrono::steady_clock::now();
    ss = findMedianSortedArrays_2_1_1(wtf1_2, wtf2_2);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    start_point_3 = chrono::steady_clock::now();
    sss = findMedianSortedArrays_1_0_1_no_timer_with_walls(wtf1_3, wtf2_3);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;

    /*start_point_4 = chrono::steady_clock::now();
    ssss = findMedianSortedArrays_other_people_3(wtf1, wtf2);
    end_point_4 = chrono::steady_clock::now();
    diff_4 += end_point_4 - start_point_4;*/

    //shitshit = findMedianSortedArrays_brute(wtf1, wtf2);

    if (display == 1){cout << "\n\ncredible result = " << s << "\nss = " << ss << "\n";}

    if (s != ss) {
        cout << "\nm = " << m << "\n";
        cout << "\n = {";
        for (int i = 0; i < wtf1.size(); i++) {
            cout << wtf1[i];if (i < wtf1.size() - 1) {cout << ", ";}
        }
        cout << "}\n = {";
        for (int i = 0; i < wtf2.size(); i++) {
            cout << wtf2[i];if (i < wtf2.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
        cout << "\n\ncredible result = " << s << "\nss = " << ss << "\n";
        break;
    }


wtf1.clear();wtf2.clear();}

cout << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << duration <double, milli> (diff_2).count() << " ms" << "\n";
cout << duration <double, milli> (diff_3).count() << " ms" << "\n";
//cout << duration <double, milli> (diff_4).count() << " ms" << "\n";
    return 0;
}




