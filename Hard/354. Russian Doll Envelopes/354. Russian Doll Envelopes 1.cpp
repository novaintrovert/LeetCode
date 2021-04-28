/*

*/

/*

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

void merge_sort_1 (int a[][2], int length) {//20201206
    int b[length][2];
    for (int i = 0; i < length; i++) {b[i][0] = a[i][0], b[i][1] = a[i][1];}

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        b[k][0] = a[i][0], b[k][1] = a[i][1];
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
                            b[k][0] = a[i][0], b[k][1] = a[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j][0], b[k][1] = a[j][1];
                        j++, j_step++;
                    }

                    else if (a[i][0] <= a[j][0]) {
                        b[k][0] = a[i][0], b[k][1] = a[i][1];
                        i++, i_step++;
                    }

                    else if (a[i][0] > a[j][0]) {
                        b[k][0] = a[j][0], b[k][1] = a[j][1];
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
                        a[k][0] = b[i][0], a[k][1] = b[i][1];
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
                            a[k][0] = b[i][0], a[k][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k][0] = b[j][0], a[k][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][0] <= b[j][0]) {
                        a[k][0] = b[i][0], a[k][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][0] > b[j][0]) {
                        a[k][0] = b[j][0], a[k][1] = b[j][1];
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
            a[i][0] = b[i][0], a[i][1] = b[i][1];
        }
    }
}
void merge_sort_2nd_idx_1 (int a[][2], int left, int right) {//20201206
    int range_length = right - left + 1;
    int b[range_length][2];
    for (int i = 0; i < range_length; i++) {b[i][0] = a[i + left][0], b[i][1] = a[i + left][1];}

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < range_length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < range_length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= range_length) {
                    for (int k = i; k < range_length; k++) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                        i++;
                    }
                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= range_length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) {
                            break;
                        }

                        else {
                            b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
                        j++, j_step++;
                    }

                    else if (a[i + left][1] <= a[j + left][1]) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                        i++, i_step++;
                    }

                    else if (a[i + left][1] > a[j + left][1]) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 0;
        }

        else if (from_a_to_b == 0) {
            for (int i = 0, j = i + double_this_long_after_merge; i < range_length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= range_length) {
                    for (int k = i; k < range_length; k++) {
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                        i++;
                    }
                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= range_length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) {
                            break;
                        }

                        else {
                            a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][1] <= b[j][1]) {
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][1] > b[j][1]) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 1;
        }
    }

    if (from_a_to_b == 0) {
        for (int i = 0; i < range_length; i++) {
            a[i + left][0] = b[i][0], a[i + left][1] = b[i][1];
        }
    }
}
void brute_probe (int dolls[][2], int length, int distinct_width_starting_idx[], int count_dif_width,
                int width, int height, int &maximum, int count_curr, int curr_idx) {

    if (count_curr + curr_idx + 1 > maximum) {
        //with current doll, if possible
        if (width < 0) {
            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            brute_probe (dolls, length, distinct_width_starting_idx, count_dif_width,
                        dolls[distinct_width_starting_idx[curr_idx]][0],
                        dolls[distinct_width_starting_idx[curr_idx]][1],
                        maximum, count_curr + 1, curr_idx - 1);
        }

        else {
            int next_idx_of_dolls = (curr_idx > 0)? distinct_width_starting_idx[curr_idx - 1] + 1: 0;

            if (dolls[next_idx_of_dolls][1] < height) {
                int left, right, mid;

                if (dolls[distinct_width_starting_idx[curr_idx]][1] < height) {
                    left = distinct_width_starting_idx[curr_idx];
                }

                else {
                    left = next_idx_of_dolls, right = distinct_width_starting_idx[curr_idx];

                    while (left < right) {
                        if (left + 1 == right) {break;}

                        mid = (left + right) / 2;

                        if (dolls[mid][1] < height) {left = mid;}

                        else {right = mid;}
                    }
                }


                if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

                brute_probe (dolls, length, distinct_width_starting_idx, count_dif_width,
                        dolls[left][0], dolls[left][1], maximum, count_curr + 1, curr_idx - 1);

            }
        }

        //without current doll
        brute_probe (dolls, length, distinct_width_starting_idx, count_dif_width,
                    width, height, maximum, count_curr, curr_idx - 1);
    }
}
int maxEnvelopes_brute(vector<vector<int>>& envelopes) {
    int length = envelopes.size();
    if (length <= 0) {return 0;}
    if (length == 1) {return 1;}

    int dolls[length][2];
    for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    merge_sort_1(dolls, length);

    int count_dif_width = 1, temp = dolls[length - 1][0];
    stack<int> dif_idx;
    dif_idx.push(length - 1);
    for (int i = length - 2; i >= 0; i--) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    int distinct_width_starting_idx[count_dif_width];
    for (int i = 0; i < count_dif_width; i++) {
        distinct_width_starting_idx[i] = dif_idx.top();
        dif_idx.pop();
    }

    int left, right, mid;
    for (int i = count_dif_width - 1; i >= 0; i--) {
        left = (i > 0)? distinct_width_starting_idx[i - 1] + 1: 0;
        right = distinct_width_starting_idx[i];

        merge_sort_2nd_idx_1(dolls, left, right);
    }

    int maximum = 0, count_curr = 0, curr_idx = count_dif_width - 1;
    int width = -1, height = -1;

    brute_probe (dolls, length, distinct_width_starting_idx, count_dif_width,
                    -1, -1, maximum, count_curr, curr_idx);

    return maximum;
}


/*//i must slice it clean//stack<int> &curr_path,
void probe_here (int dolls[][2], int max_length_starting_from_this_idx[], int length,
               int distinct_width_left_idx[], int count_dif_width,
               int &remaining_path_size,
               int width, int height,
               int &maximum, int count_curr, int last_idx, int curr_stage_idx) {

    //((curr_stage_idx < count_dif_width)&&(count_dif_width - curr_stage_idx + count_curr > maximum))
    //(count_dif_width - curr_stage_idx + count_curr > maximum)
    if (curr_stage_idx < count_dif_width) {
        int right = (curr_stage_idx < count_dif_width - 1)? distinct_width_left_idx[curr_stage_idx + 1] - 1: length - 1;

        if (dolls[right][1] > height) {
            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            int left = distinct_width_left_idx[curr_stage_idx];

            if (dolls[left][1] <= height) {
                int mid, one_more = 1;
                while (left <= right) {
                    mid = (left + right) / 2;

                    if (dolls[mid][1] <= height) {left = mid + 1;}

                    else {right = mid;}

                    if (one_more == 0) {break;}
                    if (left + 1 >= right) {one_more = 0;}
                }
            }

            if (max_length_starting_from_this_idx[left] < 0) {
                //curr_path.push(left);
                probe_here (dolls, max_length_starting_from_this_idx, length,
                        distinct_width_left_idx, count_dif_width,
                        curr_path, remaining_path,
                        dolls[left][0], dolls[left][1],
                        maximum, count_curr + 1, left, curr_stage_idx + 1);

                remaining_path_size++;
                //curr_path.pop();
                if (remaining_path_size > max_length_starting_from_this_idx[left]) {
                    max_length_starting_from_this_idx[left] = remaining_path_size;
                }

                remaining_path_size = 0;

                probe_here (dolls, max_length_starting_from_this_idx, length,
                        distinct_width_left_idx, count_dif_width,
                        remaining_path_size,//curr_path,
                        width, height,
                        maximum, count_curr, last_idx, curr_stage_idx + 1);

            }

            else {
                if (count_curr + max_length_starting_from_this_idx[left] > maximum) {
                    maximum = count_curr + max_length_starting_from_this_idx[left];
                }

                remaining_path_size = max_length_starting_from_this_idx[left];
            }
        }
    }
}

int maxEnvelopes_try_again_2(vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    int test_timer = 0;

    merge_sort_2(dolls, length);

    stack<int> dif_idx;int count_dif_width = 1;int temp = dolls[0][0];dif_idx.push(0);
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    if (test_timer >= 0) {cout << "\ncount_dif_width = " << count_dif_width << "\n";}
    if (count_dif_width == 1) {return 1;}

    int distinct_width_left_idx[count_dif_width];
    for (int i = count_dif_width - 1; i >= 0; i--) {distinct_width_left_idx[i] = dif_idx.top();dif_idx.pop();}

    int left, right;
    for (int i = 0; i < count_dif_width; i++) {
        left = distinct_width_left_idx[i];
        right = (i < count_dif_width - 1)? distinct_width_left_idx[i + 1] - 1: length - 1;
        merge_sort_2nd_idx_2(dolls, left, right);
    }

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << distinct_width_left_idx[i] << ", ";
        }
        cout << "\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_width_left_idx[j])&&(j < count_dif_width)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";

        }
        cout << "\n\n";
    }

    int max_length_starting_from_this_idx[length];for (int i = 0; i < length; i++) {max_length_starting_from_this_idx[i] = -1;}
    //stack<int> curr_path;
    int remaining_path_size = 0;

    int maximum = 0;
    int width = -1, height = -1, count_curr = 0, last_idx = -1, curr_stage_idx = 0;

    probe_here (dolls, max_length_starting_from_this_idx, length,
                distinct_width_left_idx, count_dif_width,
                remaining_path_size,//curr_path,
                width, height,
                maximum, count_curr, last_idx, curr_stage_idx);

    return maximum;
}

*/




void merge_sort_2 (int a[][2], int length) {//20201206
    int b[length][2];
    for (int i = 0; i < length; i++) {b[i][0] = a[i][0], b[i][1] = a[i][1];}

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= length) {
                    for (int k = i; k < length; k++) {
                        b[k][0] = a[i][0], b[k][1] = a[i][1];
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
                            b[k][0] = a[i][0], b[k][1] = a[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j][0], b[k][1] = a[j][1];
                        j++, j_step++;
                    }

                    else if (a[i][0] <= a[j][0]) {
                        b[k][0] = a[i][0], b[k][1] = a[i][1];
                        i++, i_step++;
                    }

                    else if (a[i][0] > a[j][0]) {
                        b[k][0] = a[j][0], b[k][1] = a[j][1];
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
                        a[k][0] = b[i][0], a[k][1] = b[i][1];
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
                            a[k][0] = b[i][0], a[k][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k][0] = b[j][0], a[k][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][0] <= b[j][0]) {
                        a[k][0] = b[i][0], a[k][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][0] > b[j][0]) {
                        a[k][0] = b[j][0], a[k][1] = b[j][1];
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
            a[i][0] = b[i][0], a[i][1] = b[i][1];
        }
    }
}
void merge_sort_2nd_idx_2 (int a[][2], int left, int right) {//20201206
    int range_length = right - left + 1;
    int b[range_length][2];
    for (int i = 0; i < range_length; i++) {b[i][0] = a[i + left][0], b[i][1] = a[i + left][1];}

    int from_a_to_b = 1, double_this_long_after_merge = 1;

    while (double_this_long_after_merge < range_length) {
        if (from_a_to_b == 1) {
            for (int i = 0, j = i + double_this_long_after_merge; i < range_length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= range_length) {
                    for (int k = i; k < range_length; k++) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                        i++;
                    }
                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= range_length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) {
                            break;
                        }

                        else {
                            b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
                        j++, j_step++;
                    }

                    else if (a[i + left][1] <= a[j + left][1]) {
                        b[k][0] = a[i + left][0], b[k][1] = a[i + left][1];
                        i++, i_step++;
                    }

                    else if (a[i + left][1] > a[j + left][1]) {
                        b[k][0] = a[j + left][0], b[k][1] = a[j + left][1];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 0;
        }

        else if (from_a_to_b == 0) {
            for (int i = 0, j = i + double_this_long_after_merge; i < range_length - 1; i += double_this_long_after_merge, j += double_this_long_after_merge) {
                if (j >= range_length) {
                    for (int k = i; k < range_length; k++) {
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                        i++;
                    }
                    break;
                }

                for (int k = i, i_step = 0, j_step = 0; ; k++) {
                    if ((j >= range_length)||(j_step == double_this_long_after_merge)) {
                        if (i_step == double_this_long_after_merge) {
                            break;
                        }

                        else {
                            a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                            i++, i_step++;
                        }
                    }

                    else if (i_step == double_this_long_after_merge) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
                        j++, j_step++;
                    }

                    else if (b[i][1] <= b[j][1]) {
                        a[k + left][0] = b[i][0], a[k + left][1] = b[i][1];
                        i++, i_step++;
                    }

                    else if (b[i][1] > b[j][1]) {
                        a[k + left][0] = b[j][0], a[k + left][1] = b[j][1];
                        j++, j_step++;
                    }
                }
            }

            double_this_long_after_merge *= 2;
            from_a_to_b = 1;
        }
    }

    if (from_a_to_b == 0) {
        for (int i = 0; i < range_length; i++) {
            a[i + left][0] = b[i][0], a[i + left][1] = b[i][1];
        }
    }
}

//i must slice it clean//stack<int> &curr_path,
void probe_here (int dolls[][2], vector<int> &max_length_starting_from_this_idx, vector<vector<int>> &next_idx, int length,
               int distinct_width_left_idx[], int count_dif_width,
               int width, int height, int &maximum, int last_idx, int count_curr, int curr_stage_idx) {//

    int test_timer = 0;
    if (test_timer >= 0) {
        cout << "\nwidth = " << width << ", height = " << height << ", last_idx = " << last_idx;
        cout << ", count_curr = " << count_curr;
        cout << ", maximum = " << maximum;
        cout << "\ncurr_stage_idx = " << curr_stage_idx << "\n";// << ", remaining_path_size = " << remaining_path_size;
        cout << "max_length_starting_from_this_idx:\n";
        for (int i = 0; i < length; i++) {
            cout << max_length_starting_from_this_idx[i] << ", ";
        }
        cout << "\nnext_idx:\n";
        for (int i = 0; i < length; i++) {
            cout << next_idx[i][0] << ", ";
        }cout << "\n";
        for (int i = 0; i < length; i++) {
            cout << next_idx[i][1] << ", ";
        }
        cout << "\n\n";
    }

    if (curr_stage_idx < count_dif_width) {
        if (test_timer >= 0) {cout << "curr_stage_idx < count_dif_width\n\n";}
        int right = (curr_stage_idx < count_dif_width - 1)? distinct_width_left_idx[curr_stage_idx + 1] - 1: length - 1;

        if (dolls[right][1] > height) {
            int left = distinct_width_left_idx[curr_stage_idx];

            if (dolls[left][1] <= height) {
                int mid, one_more = 1;
                while (left <= right) {
                    mid = (left + right) / 2;

                    if (dolls[mid][1] <= height) {left = mid + 1;}

                    else {right = mid;}

                    if (one_more == 0) {break;}
                    if (left + 1 >= right) {one_more = 0;}
                }
            }

            if (test_timer >= 0) {cout << "left = " << left << "\n";}

            if (count_curr + 1 > maximum) {maximum = count_curr + 1;}

            if (last_idx >= 0) {
                if (next_idx[last_idx][0] < 0) {next_idx[last_idx][0] = left;}

                else {next_idx[last_idx][1] = left;}
            }

            if (max_length_starting_from_this_idx[left] <= 0) {
                if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[left] < 0\n\n";}
                probe_here (dolls, max_length_starting_from_this_idx, next_idx, length,
                        distinct_width_left_idx, count_dif_width,
                        dolls[left][0], dolls[left][1],
                        maximum, left, count_curr + 1, curr_stage_idx + 1);//

                if ((last_idx >= 0)&&(next_idx[last_idx][1] >= 0)) {
                    if (max_length_starting_from_this_idx[next_idx[last_idx][1]] > max_length_starting_from_this_idx[next_idx[last_idx][0]]) {
                        next_idx[last_idx][0] = next_idx[last_idx][1];
                    }

                    next_idx[last_idx][1] = -1;
                }

                max_length_starting_from_this_idx[left] = max_length_starting_from_this_idx[next_idx[left][0]] + 1;
            }

            else {
                if (test_timer >= 0) {cout << "max_length_starting_from_this_idx[left] > 0\n\n";}

                if (count_curr + max_length_starting_from_this_idx[left] > maximum) {
                    maximum = count_curr + max_length_starting_from_this_idx[left];
                }
            }
        }
/*1, 7;
3, 5; 3, 7;
4, 2;
5, 5; 5, 9;
6, 6;
8, 10;
9, 10;
10, 1;*/
        probe_here (dolls, max_length_starting_from_this_idx, next_idx, length,
                    distinct_width_left_idx, count_dif_width,
                    width, height, maximum, last_idx, count_curr, curr_stage_idx + 1);
    }

    else {
        if (test_timer >= 0) {cout << "curr_stage_idx == count_dif_width\n\n";}

        if (last_idx >= 0) {
            cout << "what?!\n\nlast_idx = " << last_idx << "\n\n";

            max_length_starting_from_this_idx[last_idx] = 1;

            cout << "max_length_starting_from_this_idx[last_idx] = " << max_length_starting_from_this_idx[last_idx] << "\n\n";
            cout << "max_length_starting_from_this_idx:\n";
            for (int i = 0; i < length; i++) {
                cout << max_length_starting_from_this_idx[i] << ", ";
            }cout << "\n\n";
        }

        //else {cout << "last_idx < 0\n\n";}
    }
}

int maxEnvelopes_try_again_2(vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}

    int test_timer = 0;

    merge_sort_2(dolls, length);

    stack<int> dif_idx;int count_dif_width = 1;int temp = dolls[0][0];dif_idx.push(0);
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }

    if (test_timer >= 0) {cout << "\ncount_dif_width = " << count_dif_width << "\n";}
    if (count_dif_width == 1) {return 1;}

    int distinct_width_left_idx[count_dif_width];
    for (int i = count_dif_width - 1; i >= 0; i--) {distinct_width_left_idx[i] = dif_idx.top();dif_idx.pop();}

    int left, right;
    for (int i = 0; i < count_dif_width; i++) {
        left = distinct_width_left_idx[i];
        right = (i < count_dif_width - 1)? distinct_width_left_idx[i + 1] - 1: length - 1;
        merge_sort_2nd_idx_2(dolls, left, right);
    }

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < count_dif_width; i++) {
            cout << distinct_width_left_idx[i] << ", ";
        }
        cout << "\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_width_left_idx[j])&&(j < count_dif_width)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";

        }
        cout << "\n\n";
    }

    //int max_length_starting_from_this_idx[length];
    //for (int i = 0; i < length; i++) {max_length_starting_from_this_idx[i] = 0;}
    //for (int i = distinct_width_left_idx[count_dif_width - 1]; i < length; i++) {max_length_starting_from_this_idx[i] = 1;}

    vector<int> max_length_starting_from_this_idx(length, 0);

    //int next_idx[length][2];for (int i = 0; i < length; i++) {next_idx[i][0] = -1, next_idx[i][1] = -1;}
    vector<vector<int>> next_idx(length, vector<int> (2, -1));

    int maximum = 0;
    int width = -1, height = -1, count_curr = 0, last_idx = -1, curr_stage_idx = 0;

    probe_here (dolls, max_length_starting_from_this_idx, next_idx, length,
                distinct_width_left_idx, count_dif_width,
                width, height, maximum, last_idx, count_curr, curr_stage_idx);//

    return maximum;
}






int main(){
    srand(time(0));int length = 10, lower_range = 1, upper_range = 10, display = 0, input = 0;
    vector<vector<int>> wtf = {{3, 5}, {9, 10}, {3, 7}, {1, 7}, {10, 1}, {8, 10}, {6, 6}, {4, 2}, {5, 9}, {5, 5}};
    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;

for (int m = 1; m <= 1; m++) {if (m % 100 == 0) {cout << "m = " << m << "\n";}

    if (input == 1){
        wtf.reserve(length);
        for(int i = 0; i < length; i++){
            wtf.push_back({rand()%(upper_range - lower_range + 1) + lower_range,
                          rand()%(upper_range - lower_range + 1) + lower_range});
        }
    }
    if (display == 1){
        cout << " = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{" << wtf[i][0] << ", " << wtf[i][1] << "}";
            if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
    }

    start_point_1 = chrono::steady_clock::now();
    int a = maxEnvelopes_brute(wtf);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    //cout << "\nbrute = " << a << "\n\n";
    //cout << "length = " << wtf.size() << "\n";

    start_point_2 = chrono::steady_clock::now();
    int brute = maxEnvelopes_try_again_2(wtf);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    /*start_point_3 = chrono::steady_clock::now();
    int b = maxEnvelopes_try_again_1(wtf);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;*/

    //cout << "\n_try_again = " << brute << "\n";

    if (a != brute) {
        cout << "\n\n\nm = " << m << "\n\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{" << wtf[i][0] << ", " << wtf[i][1] << "}";
            if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n";
        cout << "\nbrute = " << a << "\n";
        cout << "_try_again = " << brute << "\n";
        break;
    }


wtf.clear();}

cout << "brute: " << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << "_try_again_2: " << duration <double, milli> (diff_2).count() << " ms" << "\n";
//cout << "_try_again_1: " << duration <double, milli> (diff_3).count() << " ms" << "\n";

    return 0;
}




