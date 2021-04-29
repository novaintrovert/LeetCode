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


void merge_sort_1 (int a[], int length) {//20201206
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
                        if (i_step == double_this_long_after_merge) {break;}

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
                        if (i_step == double_this_long_after_merge) {break;}

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
        for (int i = 0; i < length; i++) {a[i] = b[i];}
    }
}
void merge_sort_2 (int a[][2], int length) {//20201206
    int b[length][2];for (int i = 0; i < length; i++) {b[i][0] = a[i][0], b[i][1] = a[i][1];}

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
int maxEnvelopes_step_1 (vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int test_timer = -1;

    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}
    merge_sort_2(dolls, length);

    stack<int> dif_idx;int count_dif_width = 1;int temp = dolls[0][0];dif_idx.push(0);
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            dif_idx.push(i);
            count_dif_width++;
        }
    }
    if (count_dif_width == 1) {return 1;}

    int distinct_range_left_idx[count_dif_width];
    for (int i = count_dif_width - 1; i >= 0; i--) {distinct_range_left_idx[i] = dif_idx.top();dif_idx.pop();}

    int left, right;
    for (int i = 0; i < count_dif_width; i++) {
        left = distinct_range_left_idx[i];
        right = (i < count_dif_width - 1)? distinct_range_left_idx[i + 1] - 1: length - 1;
        merge_sort_2nd_idx_2(dolls, left, right);
    }

    if (test_timer >= 0) {
        cout << "\n";
        //for (int i = 0; i < count_dif_width; i++) {cout << distinct_width_left_idx[i] << ", ";}cout << "\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_range_left_idx[j])&&(j < count_dif_width)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n\n";
    }

    int max_length_starting_from_this_idx[length];
    for (int i = 0; i < distinct_range_left_idx[count_dif_width - 1]; i++) {max_length_starting_from_this_idx[i] = 0;}
    for (int i = distinct_range_left_idx[count_dif_width - 1]; i < length; i++) {max_length_starting_from_this_idx[i] = 1;}

    int maximum = 0, width = -1, height = -1, count_curr = 0, last_idx = -1, curr_stage_idx = 0;
    int curr_max_height = 0;
    multimap<int, int> max_len_to_idx;
    for (int i = distinct_range_left_idx[count_dif_width - 1]; i < length; i++) {
        max_len_to_idx.insert({1, i});
        if (dolls[i][1] > curr_max_height) {
            curr_max_height = dolls[i][1];
        }
    }

    for (int i = count_dif_width - 2; i >= 0; i--) {
        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            if (dolls[j][1] < curr_max_height) {
                for (auto k = max_len_to_idx.rbegin(); k != max_len_to_idx.rend(); ++k) {
                    if (dolls[k->second][1] > dolls[j][1]) {
                        max_length_starting_from_this_idx[j] = k->first + 1;
                        break;
                    }
                }
            }

            else {
                for (int k = j; k < distinct_range_left_idx[i + 1]; k++) {
                    max_length_starting_from_this_idx[k] = 1;
                }
                break;
            }
        }

        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            max_len_to_idx.insert({max_length_starting_from_this_idx[j], j});
            if (dolls[j][1] > curr_max_height) {
               curr_max_height = dolls[j][1];
            }
        }
    }

    maximum = max_length_starting_from_this_idx[0];
    for (int i = 1; i < length; i++) {
        if (max_length_starting_from_this_idx[i] > maximum) {
            maximum = max_length_starting_from_this_idx[i];
        }
    }

    return maximum;
}

int maxEnvelopes_try_this (vector<vector<int>>& envelopes) {//envelopes[n][0] is width, envelopes[n][1] is height
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int test_timer = 0;
    /*After several attempts, i think,
    what matters here, is NOT the exact value of the widths or heights,
    but the relative order of these numbers.

    So it probably will be helpful to turn all these values into their relative order,
    for example,
        width 6, 45, 3, 91 will be turned into 2, 3, 1, 4;
        because they are relatively the #2, #3, #1, #4 among these 4.

    By turning all these values into 1 2 3 4, it makes it way easier to search,
    no longer has to search "the 1st one that is larger than what we currently have",
    just search "what we currently have" + 1 --- which is way easier & way more straight forward (thus fast).
    */

    int distinct_heights = 1, distinct_widths = 1, temp;
    int temp_array[length];

    unordered_map<int, int> map_width_to_rank;
    for (int i = 0; i < length; i++) {temp_array[i] = envelopes[i][0];}
    merge_sort_1(temp_array, length);
    temp = temp_array[0], map_width_to_rank.insert({temp, 1});
    for (int i = 1; i < length; i++) {
        if (temp_array[i] != temp) {
            distinct_widths++, temp = temp_array[i];
            map_width_to_rank.insert({temp, distinct_widths});
        }
    }

    if (distinct_widths == 1) {return 1;}

    unordered_map<int, int> map_height_to_rank;
    for (int i = 0; i < length; i++) {temp_array[i] = envelopes[i][1];}
    merge_sort_1(temp_array, length);
    temp = temp_array[0], map_height_to_rank.insert({temp, 1});
    for (int i = 1; i < length; i++) {
        if (temp_array[i] != temp) {
            distinct_heights++, temp = temp_array[i];
            map_height_to_rank.insert({temp, distinct_heights});
        }
    }

    if (test_timer >= 0) {
        cout << "distinct_widths = " << distinct_widths;
        cout << ", distinct_heights = " << distinct_heights << "\n\n";
    }

    int dolls[length][2];
    for (int i = 0; i < length; i++) {
        dolls[i][0] = map_width_to_rank[envelopes[i][0]];
        dolls[i][1] = map_height_to_rank[envelopes[i][1]];
    }

    merge_sort_2(dolls, length);

    if (test_timer >= 0) {
        cout << "\n";
        for (int j = 0; j < length; j++) {
            cout << dolls[j][0] << ", " << dolls[j][1] << "\n";
        }
        cout << "\n\n";
    }

    int distinct_range_left_idx[distinct_widths];
    distinct_range_left_idx[0] = 0, temp = dolls[0][0];
    for (int i = 1, j = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            distinct_range_left_idx[j] = i;
            j++;
        }
    }

/*1, 1;
2, 6;
3, 6;
4, 3; 4, 6;
5, 1; 5, 4;
6, 1; 6, 2; 6, 5;*/

    /*vector<vector<int>> idx_of_particular_height(height, vector<int> (1, -1));

    idx_of_particular_height[dolls[0][1]][0] = 0;
    for (i = 1; i < length; i++) {
        if (idx_of_particular_height[dolls[i][1]][0] >= 0) {idx_of_particular_height[dolls[i][1]].push_back(i);}

        else {idx_of_particular_height[dolls[i][1]][0] = i;}
    }*/

    if (test_timer >= 0) {
        cout << "\n";
        //for (i = 0; i < distinct_widths; i++) {}
        cout << "\n";
        for (int j = 0; j < length; j++) {
            cout << j << " --- " << dolls[j][0] << ", " << dolls[j][1] << "\n";
        }
        cout << "\n\n";

        for (int j = 0; j < distinct_widths; j++) {
            cout << distinct_range_left_idx[j] << ", ";
        }
        cout << "\n\n";
    }

    map<int, int> height_to_idx;
    map<int, int>::iterator a_handy_iterator;

    int curr_max_height = dolls[length - 1][1];
    int max_length_starting_from_this_idx[length];
    temp = dolls[length - 1][0];
    for (int i = length - 1; i >= 0; i--) {
        if (dolls[i][0] < temp) {
            temp = i;
            break;
        }

        max_length_starting_from_this_idx[i] = 1;
        height_to_idx.insert({dolls[i][1], i});
        if (dolls[i][1] > curr_max_height) {
            curr_max_height = dolls[i][1];
        }
    }

    for (int i = temp; i >= 0; i--) {max_length_starting_from_this_idx[i] = 0;}

    int left, right;
    for (int i = distinct_widths - 2; i >= 0; i--) {
        left = distinct_range_left_idx[i];
        right = distinct_range_left_idx[i + 1] - 1;
        for (int j = right; j >= left; j--) {
            if (test_timer >= 0) {
                cout << "i = " << i << ", curr_max_height = " << curr_max_height << "\nheight_to_idx:\n";
                for (auto m = height_to_idx.begin(); m != height_to_idx.end(); ++m) {
                    cout << m->first << ", " << m->second << "; ";
                }
                cout << "\n\n";
            }

            if (dolls[j][1] >= curr_max_height) {
                max_length_starting_from_this_idx[j] = 1;
            }

            else {
                a_handy_iterator = height_to_idx.upper_bound(dolls[j][1]);
                max_length_starting_from_this_idx[j] = max_length_starting_from_this_idx[a_handy_iterator->second] + 1;
            }
        }

        for (int j = right; j >= left; j--) {
            if (dolls[j][1] >= curr_max_height) {
                curr_max_height = dolls[j][1];
                height_to_idx.insert({curr_max_height, j});
            }

            else {
                a_handy_iterator = height_to_idx.find(dolls[j][1]);
                if (a_handy_iterator != height_to_idx.end()) {
                    height_to_idx.erase(a_handy_iterator);
                }
                height_to_idx.insert({dolls[j][1], j});
            }
        }

        if (test_timer >= 0) {
            //cout << "\n";
            //cout << "\n";
            for (int j = 0; j < length; j++) {
                cout << max_length_starting_from_this_idx[j] << ", ";
            }
            cout << "\n\n";
        }
    }

    int maximum = max_length_starting_from_this_idx[0];
    for (int i = 1; i < length; i++) {
        if (max_length_starting_from_this_idx[i] > maximum) {
            maximum = max_length_starting_from_this_idx[i];
        }
    }

    return maximum;
}


int maxEnvelopes_step_2 (vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    int test_timer = -1;

    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}
    merge_sort_2(dolls, length);

    vector<int> distinct_range_left_idx;
    distinct_range_left_idx.reserve(length);
    distinct_range_left_idx.push_back(0);
    int temp = dolls[0][0];
    for (int i = 1, j = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            distinct_range_left_idx.push_back(i);
            j++;
        }
    }
    distinct_range_left_idx.shrink_to_fit();

    int distinct_widths = distinct_range_left_idx.size();
    if (distinct_widths == 1) {return 1;}

    /*int left, right;
    for (int i = 0; i < distinct_widths; i++) {
        left = distinct_range_left_idx[i];
        right = (i < distinct_widths - 1)? distinct_range_left_idx[i + 1] - 1: length - 1;
        merge_sort_2nd_idx_2(dolls, left, right);
    }*/

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_range_left_idx[j])&&(j < distinct_widths)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n\n";
    }

    int max_length_starting_from_this_idx[length];
    for (int i = 0; i < distinct_range_left_idx[distinct_widths - 1]; i++) {max_length_starting_from_this_idx[i] = 0;}
    for (int i = distinct_range_left_idx[distinct_widths - 1]; i < length; i++) {max_length_starting_from_this_idx[i] = 1;}

    int curr_max_height = 0;
    map<int, map<int, int>> max_len_to_height_to_idx;
    for (int i = distinct_range_left_idx[distinct_widths - 1]; i < length; i++) {
        max_len_to_height_to_idx.insert({1, map<int, int>()});
        max_len_to_height_to_idx[1].insert({dolls[i][1], i});
        if (dolls[i][1] > curr_max_height) {
            curr_max_height = dolls[i][1];
        }
    }

    if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < distinct_widths; i++) {
            cout << distinct_range_left_idx[i] << ", ";
        }
        cout << "\n\n";
    }

    for (int i = distinct_widths - 2; i >= 0; i--) {
        if (test_timer >= 0) {
            cout << "i = " << i << ", curr_max_height = " << curr_max_height << "\n\n";
        }

        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            if (dolls[j][1] < curr_max_height) {
                for (auto k = max_len_to_height_to_idx.rbegin(); k != max_len_to_height_to_idx.rend(); ++k) {
                    if (k->second.rbegin()->first > dolls[j][1]) {
                        max_length_starting_from_this_idx[j] = k->first + 1;
                        break;
                    }
                }
            }

            else {
                max_length_starting_from_this_idx[j] = 1;
            }
        }

        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            auto find_it = max_len_to_height_to_idx.find(max_length_starting_from_this_idx[j]);
            if (find_it == max_len_to_height_to_idx.end()) {
                max_len_to_height_to_idx.insert({max_length_starting_from_this_idx[j], map<int, int> ()});
            }
            max_len_to_height_to_idx[max_length_starting_from_this_idx[j]].insert({dolls[j][1], j});

            if (dolls[j][1] > curr_max_height) {
               curr_max_height = dolls[j][1];
            }
        }

        if (test_timer >= 0) {
            cout << "\nmax_length_starting_from_this_idx:\n";
            for (int m = 0; m < length; m++) {
                cout << max_length_starting_from_this_idx[m] << ", ";
            }
            cout << "\nmax_len_to_height_to_idx:\n";
            for (auto m = max_len_to_height_to_idx.begin(); m != max_len_to_height_to_idx.end(); ++m) {
                for (auto n = m->second.begin(); n != m->second.end(); ++n) {
                    cout << n->first << ", " << n->second << "; ";
                }
                cout << "\n";
            }
            cout << "\n\n";
        }
    }

    int maximum = max_length_starting_from_this_idx[0];
    for (int i = 1; i < length; i++) {
        if (max_length_starting_from_this_idx[i] > maximum) {
            maximum = max_length_starting_from_this_idx[i];
        }
    }

    return maximum;
}



int maxEnvelopes_step_3 (vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    //int test_timer = -1;

    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}
    merge_sort_2(dolls, length);

    int distinct_widths = 1, temp = dolls[0][0];
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            distinct_widths++;
        }
    }

    if (distinct_widths == 1) {return 1;}

    int distinct_range_left_idx[distinct_widths];
    distinct_range_left_idx[0] = 0;
    temp = dolls[0][0];
    for (int i = 1, j = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            distinct_range_left_idx[j] = i;
            j++;
        }
    }

    /*if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_range_left_idx[j])&&(j < distinct_widths)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n\n";
    }*/

    int max_length_starting_from_this_idx[length];
    for (int i = 0; i < distinct_range_left_idx[distinct_widths - 1]; i++) {max_length_starting_from_this_idx[i] = 0;}
    for (int i = distinct_range_left_idx[distinct_widths - 1]; i < length; i++) {max_length_starting_from_this_idx[i] = 1;}

    int curr_max_height = 0;
    map<int, map<int, int>> max_len_to_height_to_idx;
    for (int i = distinct_range_left_idx[distinct_widths - 1]; i < length; i++) {
        max_len_to_height_to_idx.insert({1, map<int, int>()});
        max_len_to_height_to_idx[1].insert({dolls[i][1], i});
        if (dolls[i][1] > curr_max_height) {
            curr_max_height = dolls[i][1];
        }
    }

    /*if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0; i < distinct_widths; i++) {
            cout << distinct_range_left_idx[i] << ", ";
        }
        cout << "\n\n";
    }*/

    for (int i = distinct_widths - 2; i >= 0; i--) {
        //if (test_timer >= 0) {cout << "i = " << i << ", curr_max_height = " << curr_max_height << "\n\n";}

        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            if (dolls[j][1] < curr_max_height) {
                for (auto k = max_len_to_height_to_idx.rbegin(); k != max_len_to_height_to_idx.rend(); ++k) {
                    if (k->second.rbegin()->first > dolls[j][1]) {
                        max_length_starting_from_this_idx[j] = k->first + 1;
                        break;
                    }
                }
            }

            else {max_length_starting_from_this_idx[j] = 1;}
        }

        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            auto find_it = max_len_to_height_to_idx.find(max_length_starting_from_this_idx[j]);

            if (find_it == max_len_to_height_to_idx.end()) {
                max_len_to_height_to_idx.insert({max_length_starting_from_this_idx[j], map<int, int> ()});
            }

            max_len_to_height_to_idx[max_length_starting_from_this_idx[j]].insert({dolls[j][1], j});

            if (dolls[j][1] > curr_max_height) {
               curr_max_height = dolls[j][1];
            }
        }

        /*if (test_timer >= 0) {
            cout << "\nmax_length_starting_from_this_idx:\n";
            for (int m = 0; m < length; m++) {
                cout << max_length_starting_from_this_idx[m] << ", ";
            }
            cout << "\nmax_len_to_height_to_idx:\n";
            for (auto m = max_len_to_height_to_idx.begin(); m != max_len_to_height_to_idx.end(); ++m) {
                for (auto n = m->second.begin(); n != m->second.end(); ++n) {
                    cout << n->first << ", " << n->second << "; ";
                }
                cout << "\n";
            }
            cout << "\n\n";
        }*/
    }

    int maximum = max_length_starting_from_this_idx[0];
    for (int i = 1; i < length; i++) {
        if (max_length_starting_from_this_idx[i] > maximum) {
            maximum = max_length_starting_from_this_idx[i];
        }
    }

    return maximum;
}


int maxEnvelopes_step_4 (vector<vector<int>>& envelopes) {
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    //int test_timer = -1;

    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}
    merge_sort_2(dolls, length);

    int distinct_widths = 1, temp = dolls[0][0];
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            distinct_widths++;
        }
    }

    if (distinct_widths == 1) {return 1;}

    int distinct_range_left_idx[distinct_widths];
    distinct_range_left_idx[0] = 0;
    temp = dolls[0][0];
    for (int i = 1, j = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            distinct_range_left_idx[j] = i;
            j++;
        }
    }

    /*if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_range_left_idx[j])&&(j < distinct_widths)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n\n";
    }*/

    int max_length_starting_from_this_idx[length];
    for (int i = 0; i < distinct_range_left_idx[distinct_widths - 1]; i++) {max_length_starting_from_this_idx[i] = 0;}
    for (int i = distinct_range_left_idx[distinct_widths - 1]; i < length; i++) {max_length_starting_from_this_idx[i] = 1;}

    int curr_max_height = 0;
    map<int, int> max_len_to_max_height;
    for (int i = distinct_range_left_idx[distinct_widths - 1]; i < length; i++) {
        if (dolls[i][1] > curr_max_height) {
            curr_max_height = dolls[i][1];
        }
    }
    max_len_to_max_height.insert({1, curr_max_height});

    for (int i = distinct_widths - 2; i >= 0; i--) {
        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            if (dolls[j][1] < curr_max_height) {
                for (auto k = max_len_to_max_height.rbegin(); k != max_len_to_max_height.rend(); ++k) {
                    if (k->second > dolls[j][1]) {
                        max_length_starting_from_this_idx[j] = k->first + 1;
                        break;
                    }
                }
            }

            else {max_length_starting_from_this_idx[j] = 1;}
        }

        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            auto find_it = max_len_to_max_height.find(max_length_starting_from_this_idx[j]);

            if (find_it == max_len_to_max_height.end()) {
                max_len_to_max_height.insert({max_length_starting_from_this_idx[j], dolls[j][1]});
            }

            else if (dolls[j][1] > find_it->second) {
                max_len_to_max_height.erase(find_it);
                max_len_to_max_height.insert({max_length_starting_from_this_idx[j], dolls[j][1]});
            }
            if (dolls[j][1] > curr_max_height) {
               curr_max_height = dolls[j][1];
            }
        }

    }

    int maximum = max_length_starting_from_this_idx[0];
    for (int i = 1; i < length; i++) {
        if (max_length_starting_from_this_idx[i] > maximum) {
            maximum = max_length_starting_from_this_idx[i];
        }
    }

    return maximum;
}



//WARNING!!! BLAZING FAST CODE!!!

//i don't get why this code of mine, which is entirely hand-crafted by myself, is MERELY top 5%.
//i think it is supposed to be top 1% or top 2%.

//copied some of the fastest code there are, run hundreds of millions of random number tests on my machine,
//in EVERY TEST set, my code ALWAYS CRUSHES the best of those 2.
//ton of short inputs, a lot of mid inputs, quite some really long inputs
//my code is significantly faster.

//only in really long tests my code is not that fast, only 1.5 times faster (used 2/3 of the time) than best of those 2
//in mid or small tests, my code is on average 4-6 times faster than best of those 2 - it is NOT EVEN a competition!!!

//and leetcode said this code of mine is merely top 5%?
//i think my code is ON AVERAGE top 2%

//I'm good at what i do.

//WARNING!!! BLAZING FAST CODE!!!

//NEED merge_sort_2() TO RUN!!!
int maxEnvelopes_step_5 (vector<vector<int>>& envelopes) {
    //version 2.4, hand-crafted by Nova Introvert
    int length = envelopes.size();if (length <= 0) {return 0;}if (length == 1) {return 1;}
    //int test_timer = -1;

    int dolls[length][2];for (int i = 0; i < length; i++) {dolls[i][0] = envelopes[i][0], dolls[i][1] = envelopes[i][1];}
    merge_sort_2(dolls, length);

    int distinct_widths = 1, temp = dolls[0][0];
    for (int i = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            distinct_widths++;
        }
    }

    if (distinct_widths == 1) {return 1;}

    int distinct_range_left_idx[distinct_widths];
    distinct_range_left_idx[0] = 0;
    temp = dolls[0][0];
    for (int i = 1, j = 1; i < length; i++) {
        if (dolls[i][0] != temp) {
            temp = dolls[i][0];
            distinct_range_left_idx[j] = i;
            j++;
        }
    }

    /*if (test_timer >= 0) {
        cout << "\n";
        for (int i = 0, j = 0; (i < length); i++) {
            if ((i == distinct_range_left_idx[j])&&(j < distinct_widths)) {cout << "\n";j++;}
            cout << dolls[i][0] << ", " << dolls[i][1] << "; ";
        }
        cout << "\n\n";
    }*/

    int max_length_starting_from_this_idx[length];
    for (int i = 0; i < distinct_range_left_idx[distinct_widths - 1]; i++) {max_length_starting_from_this_idx[i] = 0;}
    for (int i = distinct_range_left_idx[distinct_widths - 1]; i < length; i++) {max_length_starting_from_this_idx[i] = 1;}

    int curr_max_height = 0, map_idx = 0;
    int max_len_n_max_height[length];
    for (int i = 0; i < length; i++) {max_len_n_max_height[i] = 0;}
    for (int i = distinct_range_left_idx[distinct_widths - 1]; i < length; i++) {
        if (dolls[i][1] > curr_max_height) {
            curr_max_height = dolls[i][1];
        }
    }
    max_len_n_max_height[0] = curr_max_height;

    for (int i = distinct_widths - 2; i >= 0; i--) {
        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            if (dolls[j][1] < curr_max_height) {
                for (int k = map_idx; k >= 0; k--) {
                    if (max_len_n_max_height[k] > dolls[j][1]) {
                        max_length_starting_from_this_idx[j] = k + 2;
                        break;
                    }
                }
            }

            else {max_length_starting_from_this_idx[j] = 1;}
        }

        for (int j = distinct_range_left_idx[i]; j < distinct_range_left_idx[i + 1]; j++) {
            if (max_length_starting_from_this_idx[j] > map_idx + 1) {
                max_len_n_max_height[max_length_starting_from_this_idx[j] - 1] = dolls[j][1];
                map_idx = max_length_starting_from_this_idx[j] - 1;
            }

            else if (dolls[j][1] > max_len_n_max_height[max_length_starting_from_this_idx[j] - 1]) {
                max_len_n_max_height[max_length_starting_from_this_idx[j] - 1] = dolls[j][1];
            }

            if (dolls[j][1] > curr_max_height) {
               curr_max_height = dolls[j][1];
            }
        }

    }

    int maximum = max_length_starting_from_this_idx[0];
    for (int i = 1; i < length; i++) {
        if (max_length_starting_from_this_idx[i] > maximum) {
            maximum = max_length_starting_from_this_idx[i];
        }
    }

    return maximum;
}




int maxEnvelopes_other_people_1(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), [](auto& lhs, auto& rhs){
            return lhs[0] == rhs[0] ? lhs[1] > rhs[1] : lhs[0] < rhs[0];
        });

        int n = envelopes.size();
        vector<int> dp;
        for(int i = 0; i < n; ++i){
            if(dp.empty() || dp.back() < envelopes[i][1]){
                dp.push_back(envelopes[i][1]);
            }
            else{
                auto it = lower_bound(dp.begin(), dp.end(), envelopes[i][1]);
                *it = envelopes[i][1];
            }
        }
        return dp.size();
    }

int maxEnvelopes_other_people_2(vector<vector<int>>& envelopes) {

        sort(envelopes.begin() , envelopes.end() , [](vector<int>&a , vector<int> &b)
             {
                 if(a[0] == b[0])
                     return a[1] > b[1];
                 return a[0] < b[0];
             });
            vector<int>tail;
        int n = envelopes.size();
        if(n <= 1)
            return n;
        tail.push_back(envelopes[0][1]);
        int len = 1;
        for(int i = 1 ; i < envelopes.size() ; i++)
        {
            if(envelopes[i][1] > tail[len-1])
            {
                tail.push_back(envelopes[i][1]);
                len++;
            }
            else
            {
                int idx = lower_bound(tail.begin() , tail.end() , envelopes[i][1])  - tail.begin();
                tail[idx] = envelopes[i][1] ;
            }
        }

        return len;
    }


class Solution {
#define pii pair<int,int>
    #define F first
    #define S second
public:
    static bool cmp(pii x, pii y) {
        if (x.F == y.F) return y.S < x.S;
        return x.F < y.F;
    }
    int maxEnvelopes(vector<vector<int>>& a) {
        int n=a.size();
        vector<pair<int,int> > arr;
        for(int i=0;i<n;i++){
            int x=a[i][0];
            int y=a[i][1];
            arr.push_back({x,y});
        }
        sort(arr.begin(),arr.end(),cmp);
        vector<int> dp;
        for (int i = 0;i < n;i++) {
            int v = arr[i].second;
            if (dp.empty()||v > dp.back()  ) {
                dp.push_back(v);
                continue;
            }
            auto pos = lower_bound(dp.begin(), dp.end(), v);
            *pos = v;
        }
        return dp.size();
    }
};

int main(){
    srand(time(0));int length = 100000, lower_range = 1, upper_range = 100000, display = 0, input = 1;
    vector<vector<int>> wtf;
    auto start_point_1 = chrono::steady_clock::now();auto end_point_1 = chrono::steady_clock::now();auto diff_1 = end_point_1 - start_point_1;
    auto start_point_2 = chrono::steady_clock::now();auto end_point_2 = chrono::steady_clock::now();auto diff_2 = end_point_2 - start_point_2;
    auto start_point_3 = chrono::steady_clock::now();auto end_point_3 = chrono::steady_clock::now();auto diff_3 = end_point_3 - start_point_3;
    auto start_point_4 = chrono::steady_clock::now();auto end_point_4 = chrono::steady_clock::now();auto diff_4 = end_point_4 - start_point_4;

Solution Solu;
for (int m = 1; m <= 100; m++) {if (m % 10 == 0) {cout << "m = " << m << "\n";}
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
    vector<vector<int>> wtf1(wtf);
    vector<vector<int>> wtf2(wtf);
    vector<vector<int>> wtf3(wtf);

    start_point_1 = chrono::steady_clock::now();
    int a = maxEnvelopes_step_5(wtf);
    end_point_1 = chrono::steady_clock::now();
    diff_1 += end_point_1 - start_point_1;

    start_point_2 = chrono::steady_clock::now();
    int b = maxEnvelopes_other_people_1(wtf1);
    end_point_2 = chrono::steady_clock::now();
    diff_2 += end_point_2 - start_point_2;

    start_point_4 = chrono::steady_clock::now();
    int c = Solu.maxEnvelopes(wtf2);
    end_point_4 = chrono::steady_clock::now();
    diff_4 += end_point_4 - start_point_4;

    start_point_3 = chrono::steady_clock::now();
    int d = maxEnvelopes_other_people_2(wtf3);
    end_point_3 = chrono::steady_clock::now();
    diff_3 += end_point_3 - start_point_3;

    if (c != a) {
        cout << "\n\n\nm = " << m << "\n\n = {";
        for (int i = 0; i < wtf.size(); i++) {
            cout << "{" << wtf[i][0] << ", " << wtf[i][1] << "}";
            if (i < wtf.size() - 1) {cout << ", ";}
        }
        cout << "}\n\n";
        cout << "a = " << a << "\n";
        cout << "b = " << b << "\n";
        cout << "c = " << c << "\n";
        cout << "d = " << d << "\n";
        break;
    }


wtf.clear();}

cout << "Me: " << duration <double, milli> (diff_1).count() << " ms" << "\n";
cout << "1: " << duration <double, milli> (diff_2).count() << " ms" << "\n";
cout << "2: " << duration <double, milli> (diff_4).count() << " ms" << "\n";
cout << "3: " << duration <double, milli> (diff_3).count() << " ms" << "\n";
//cout << "_try_again_1: " << duration <double, milli> (diff_3).count() << " ms" << "\n";

    return 0;
}






