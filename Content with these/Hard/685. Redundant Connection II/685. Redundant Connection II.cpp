/*685. Redundant Connection II
Hard

In this problem, a rooted tree is a directed graph such that,
there is exactly one node (the root) for which all other nodes are descendants of this node,
plus every node has exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with n nodes
(with distinct values from 1 to n),
with one additional directed edge added.
The added edge has two different vertices chosen from 1 to n,
and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges.
Each element of edges is a pair [ui, vi] that represents a directed edge connecting nodes ui and vi,
where ui is a parent of child vi.

Return an edge that can be removed so that the resulting graph is a rooted tree of n nodes.
If there are multiple answers, return the answer that occurs last in the given 2D-array.

Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]

Input: edges = [[1,2],[2,3],[3,4],[4,1],[1,5]]
Output: [4,1]

Constraints:
    n == edges.length
    3 <= n <= 1000
    edges[i].length == 2
    1 <= ui, vi <= n
*/

/*
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {

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

using namespace std;
using namespace chrono;


/*vector<int> findRedundantDirectedConnection_draft(vector<vector<int>>& edges) {
    int length = edges.size();
    unordered_map<int, vector<int>> occurence_idx;
    for (int i = 0; i < length; i++) {
        auto find_it = occurence_idx.find(edges[i][0]);
        if (find_it == occurence_idx.end()) {
            occurence_idx.insert({edges[i][0], vector<int>()});
        }
        occurence_idx[edges[i][0]].push_back(i);
    }

    int visited[length]; for (int i = 0; i < length; i++) {visited[i] = 0;}

    vector<int> result (2, 0);

    stack<int> past_steps_start_val;
    stack<int> steps_size;
    stack<int> idx_within_steps;

    int anchor_idx = 0, roaming_idx = 0, count_visited = 0;
    while (count_visited < length) {
        if (visited[roaming_idx] == 0) {
            auto find_next = occurence_idx.find(edges[roaming_idx][1]);

            if (find_next == occurence_idx.end()) {
                if (steps_size.top() - 1 > idx_within_steps.top()) {
                    //roaming_idx =
                }

                else {

                }
            }

            else {
                past_steps_start_val.push(edges[roaming_idx][0]);
                //steps_size???
                //idx_within_steps




                visited[roaming_idx] = 1;
                count_visited++;
            }
        }

        else {
            if (roaming_idx != anchor_idx) {
                //if () {result[0] = edges[roaming_idx][0], result[1] = edges[roaming_idx][1];break;}

                //else {}
            }

            else {
                anchor_idx++;
                roaming_idx = anchor_idx;
            }
        }
    }

    return result;
}*/

/*vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
    int length = edges.size();

    unordered_map<int, vector<int>> occurence_idx;
    for (int i = 0; i < length; i++) {
        auto find_it = occurence_idx.find(edges[i][0]);

        if (find_it == occurence_idx.end()) {occurence_idx.insert({edges[i][0], vector<int>()});}

        occurence_idx[edges[i][0]].push_back(i);
    }

    bool visited[length];
    for (int i = 0; i < length; i++) {visited[i] = 0;}

    vector<int> result (2, -1);

    int cache_idx = -1;
    int cache[length][3];//stack<int> steps_start_val;stack<int> steps_size;stack<int> idx_within_steps;

    for (int i = 0; i < length; i++) {//if cache_idx is controlled well, this part won't be needed.
        cache[i][0] = -1;//steps_start_val
        cache[i][1] = -1;//steps_size
        cache[i][2] = -1;//idx_within_steps
    }

    int anchor_idx = 0, roaming_idx = 0, count_visited = 0;
    int temp, local_idx;
    //i think count_visited is redundant, anyway, put it here just in case
    while (count_visited < length) {
        //check if next value is visited
        //auto check_if_next_val_is_visited = visited_val.find(edges[roaming_idx][1]);
        if (visited[roaming_idx] == 0) {//(check_if_visited == visited_val.end())
            visited[roaming_idx] = 1;
            count_visited++;

            auto if_next_existed = occurence_idx.find(edges[roaming_idx][1]);

            if (if_next_existed == occurence_idx.end()) {

                if (cache_idx >= 0) {
                    //steps_size.top() - 1 > idx_within_steps.top()

                    //shit, i'm not finding the last one in the array
                    if (cache[cache_idx][1] - 1 > cache[cache_idx][2]) {
                        roaming_idx = occurence_idx[cache[cache_idx][0]][cache[cache_idx][2] + 1];
                        cache[cache_idx][2]++;
                    }

                    else {
                        while ((cache_idx >= 0)&&(cache[cache_idx][1] - 1 > cache[cache_idx][2])) {
                            cache_idx--;
                        }

                        if (cache_idx >= 0) {
                            roaming_idx = occurence_idx[cache[cache_idx][0]][cache[cache_idx][2] + 1];
                            cache[cache_idx][2]++;
                        }

                        else {
                            anchor_idx++;
                            roaming_idx = anchor_idx;
                        }
                    }
                }

                else {anchor_idx++, roaming_idx = anchor_idx;}
            }

            else {
                cache_idx++;
                cache[cache_idx][0] = edges[roaming_idx][0];
                cache[cache_idx][1] = occurence_idx[edges[roaming_idx][0]].size();
                cache[cache_idx][2] = 0;

                roaming_idx = occurence_idx[edges[roaming_idx][1]][0];
            }
        }

        else {
            if (roaming_idx != anchor_idx) {
                result[0] = edges[roaming_idx][0], result[1] = edges[roaming_idx][1];
                break;
            }

            else {anchor_idx++, roaming_idx = anchor_idx;}
        }
    }

    return result;
}*/

/*if (steps_size.top() - 1 > idx_within_steps.top()) {
        roaming_idx = occurence_idx[steps_start_val.top()][idx_within_steps.top() + 1];

        temp = idx_within_steps.top();
        idx_within_steps.pop();
        idx_within_steps.push(temp + 1);

        past_steps_start_val.pop();
        past_steps_start_val.push(edges[roaming_idx][0]);
    }

    else {
        while ((steps_size.size() > 0)&&(steps_size.top() - 1 == idx_within_steps.top())) {
            past_steps_start_val.pop();
            steps_size.pop();
            idx_within_steps.pop();
        }

        if (steps_size.size() > 0) {
            roaming_idx = occurence_idx[steps_start_val.top()][idx_within_steps.top() + 1];

            temp = idx_within_steps.top();
            idx_within_steps.pop();
            idx_within_steps.push(temp + 1);

            past_steps_start_val.pop();
            past_steps_start_val.push(edges[roaming_idx][0]);
        }

        else {
            anchor_idx++;
            roaming_idx = anchor_idx;
        }
    }
*/

vector<int> findRedundantDirectedConnection_FATALLY_FLAWED(vector<vector<int>>& edges) {
    int length = edges.size();

    bool been_pointed_to[length + 1];//nodes that are already been pointed
    for (int i = 0; i <= length; i++) {been_pointed_to[i] = 0;}
    bool pointing_to[length + 1];//nodes that are already pointing to other nodes
    for (int i = 0; i <= length; i++) {pointing_to[i] = 0;}

    vector<int> result(2, -1);

    for (int i = 0; i < length; i++) {
        if (been_pointed_to[edges[i][1]] == 0) {
            if ((pointing_to[edges[i][1]] != 0)&&(been_pointed_to[edges[i][0]] != 0)) {
                result[0] = edges[i][0], result[1] = edges[i][1];
                break;
            }

            else {
                been_pointed_to[edges[i][1]] = 1;
                pointing_to[edges[i][0]] = 1;
            }
        }

        else {result[0] = edges[i][0], result[1] = edges[i][1];break;}
    }

    return result;
}


vector<int> findRedundantDirectedConnection___ah(vector<vector<int>>& edges) {
    int length = edges.size();

    unordered_map<int, vector<int>> occurence_idx;
    for (int i = 0; i < length; i++) {
        auto find_it = occurence_idx.find(edges[i][0]);

        if (find_it == occurence_idx.end()) {occurence_idx.insert({edges[i][0], vector<int>()});}

        occurence_idx[edges[i][0]].push_back(i);
    }

    bool visited[length];
    for (int i = 0; i < length; i++) {visited[i] = 0;}

    vector<int> result (2, -1);

    int cache_idx = -1;
    int cache[length][3];//stack<int> steps_start_val;stack<int> steps_size;stack<int> idx_within_steps;

    for (int i = 0; i < length; i++) {//if cache_idx is controlled well, this part won't be needed.
        cache[i][0] = -1;//steps_start_val
        cache[i][1] = -1;//steps_size
        cache[i][2] = -1;//idx_within_steps
    }

    int anchor_idx = 0, roaming_idx = 0, count_visited = 0;
    int temp, local_idx;
    //i think count_visited is redundant, anyway, put it here just in case
    while (count_visited < length) {
        //check if next value is visited
        //auto check_if_next_val_is_visited = visited_val.find(edges[roaming_idx][1]);
        if (visited[roaming_idx] == 0) {//(check_if_visited == visited_val.end())
            visited[roaming_idx] = 1;
            count_visited++;

            auto if_next_existed = occurence_idx.find(edges[roaming_idx][1]);

            if (if_next_existed == occurence_idx.end()) {

                if (cache_idx >= 0) {
                    //steps_size.top() - 1 > idx_within_steps.top()

                    //shit, i'm not finding the last one in the array
                    if (cache[cache_idx][1] - 1 > cache[cache_idx][2]) {
                        roaming_idx = occurence_idx[cache[cache_idx][0]][cache[cache_idx][2] + 1];
                        cache[cache_idx][2]++;
                    }

                    else {
                        while ((cache_idx >= 0)&&(cache[cache_idx][1] - 1 > cache[cache_idx][2])) {
                            cache_idx--;
                        }

                        if (cache_idx >= 0) {
                            roaming_idx = occurence_idx[cache[cache_idx][0]][cache[cache_idx][2] + 1];
                            cache[cache_idx][2]++;
                        }

                        else {
                            anchor_idx++;
                            roaming_idx = anchor_idx;
                        }
                    }
                }

                else {anchor_idx++, roaming_idx = anchor_idx;}
            }

            else {
                cache_idx++;
                cache[cache_idx][0] = edges[roaming_idx][0];
                cache[cache_idx][1] = occurence_idx[edges[roaming_idx][0]].size();
                cache[cache_idx][2] = 0;

                roaming_idx = occurence_idx[edges[roaming_idx][1]][0];
            }
        }

        else {
            if (roaming_idx != anchor_idx) {
                result[0] = edges[roaming_idx][0], result[1] = edges[roaming_idx][1];
                break;
            }

            else {anchor_idx++, roaming_idx = anchor_idx;}
        }
    }

    return result;
}


vector<int> findRedundantDirectedConnection_try_fix_it(vector<vector<int>>& edges) {//by Nova Introvert
    int length = edges.size();

    int prev[length + 1];for (int i = 0; i <= length; i++) {prev[i] = 0;}
    for (int i = 0; i < length; i++) {prev[edges[i][1]] = edges[i][0];}

    int we_have_a_clear_root = 0;
    for (int i = 1; i <= length; i++) {
        if (prev[i] == 0) {
            we_have_a_clear_root = 1;
            break;
        }
    }

    vector<int> result(2, -1);

    /*if the redundant edge IS NOT connected to the root,
    for that, there is ONE & ONLY ONE redundant edge & it is NOT connected to the root,
    then, there MUST BE ONE & ONLY ONE edge which is pointed to by 2 nodes.

    what we need to do is:
        sequentially scan it, find the first edge which is pointed to by 2 nodes*/
    if (we_have_a_clear_root != 0) {
        //cout << "we have a clear root\n";
        bool been_pointed_to[length + 1];//nodes that are already been pointed
        for (int i = 0; i <= length; i++) {been_pointed_to[i] = 0;}

        for (int i = 0; i < length; i++) {
            if (been_pointed_to[edges[i][1]] != 0) {
                result[0] = edges[i][0];
                result[1] = edges[i][1];
                break;
            }

            else {been_pointed_to[edges[i][1]] = 1;}
        }
    }


    else {
        //cout << "we don't have a clear root\n";

        int temp, found = 0;
        int reverse_edges_so_far[length + 1];for (int i = 0; i <= length; i++) {reverse_edges_so_far[i] = 0;}

        for (int i = 0; (i < length)&&(found == 0); i++) {
            //cout << "i = " << i << "\n";

            reverse_edges_so_far[edges[i][1]] = edges[i][0];

            if (reverse_edges_so_far[edges[i][0]] != 0) {
                temp = reverse_edges_so_far[edges[i][0]];

                while (reverse_edges_so_far[temp] != 0) {
                    //cout << "temp = " << temp << "\n";
                    temp = reverse_edges_so_far[temp];

                    if (temp == edges[i][1]) {
                        result[0] = edges[i][0], result[1] = edges[i][1];
                        found = 1;
                        break;
                    }
                }
            }
        }
    }

    return result;
}


/*if the redundant edge IS connected to the root,

    To find the result:
        1. scan input from 0th to the end,
        2. update head & tail of every path recorded,
        3. return the 1st edge that form a loop ().

    this algo critically relies on the property that this graph is "a tree + 1 redundant connection",
    it might break otherwise.
    */

/*int temp;
unordered_map<int, int> tail_to_head;
unordered_map<int, int> head_to_tail;
//for (int i = 0; i <= length; i++) {paths_tail_to_head[i] = 0, paths_head_to_tail[i] = 0;}

//bc every node got ONLY ONE ancestor, while it might have multiple children
//paths_tail_to_head plays major role,
//paths_head_to_tail will be assisting
for (int i = 0; i < length; i++) {
    auto find_it = tail_to_head.find(edges[i][0]);
    if ((find_it != tail_to_head.end())&&(find_it->first == edges[i][1])) {
        result[0] = edges[i][0], result[1] = edges[i][1];
        break;
    }

    if (find_it == tail_to_head.end()) {tail_to_head.insert({edges[i][1], edges[i][0]});}

    temp = tail_to_head[edges[i][0]];
    while (find_it != tail_to_head.end()) {

    }

    //if (paths_tail_to_head[edges[i][0]] == edges[i][1]) {result[0] = edges[i][0], result[1] = edges[i][1];break;}
    //else {paths_tail_to_head[edges[i][0]] = edges[i][1];
    //temp = edges[i][1];while () {}paths_head_to_tail[edges[i][1]] = edges[i][0];}
}*/

/*bool first_path[length + 1];
for (int i = 0; i <= length; i++) {path[i] = 0;}

int starting_val = edges[0][0], curr_idx = 0;
while (first_path[curr_idx] == 0) {//going backwards, mark all nodes
    first_path[edges[curr_idx][0]] = 1;
    curr_idx = prev[edges[curr_idx][0]];
}

//now we find the start of the loop,
//going back even more to mark the entire loop
bool loop[length + 1];
for (int i = 0; i <= length; i++) {loop[i] = 0;}
while (loop[curr_idx] == 0) {//going backwards, mark all nodes
    loop[edges[curr_idx][0]] = 1;
    curr_idx = prev[edges[curr_idx][0]];
}

//now curr_idx is reused, entirely different from prev
curr_idx = 0;
while (loop[edges[curr_idx][0]] == 0) {
    curr_idx = prev[edges[curr_idx][0]];
}

//now curr_idx is the root
result[1] = edges[curr_idx][1], result[0] = edges[curr_idx][0];*/



//Currently my best. No bullshit, probably this is as fast as it can get

/* EXPLANATION - mindfully built by Nova Introvert.

4 cases in total:

1. NOT connected to root.
    There MUST BE a node which is pointed to by 2 others, result MUST BE one of these 2 edges.

    1.1 connected to its ancestors
    1.2 connected to other branches

        mark these 2 edges (including who comes second), trace any of them back to root.

        if the path come across itself, then 1.1, the beginning of current path is the result.

        else return the other edge.

2. IS connected to root.
    There is NO node that is pointed to by 2 others.

    2.1 the entire graph forms a SINGLE ring.
    2.2 that ring is only PART of the whole graph

        starting from any node, tracing back, recording every node, it will cross its path

        remember that particular "hit" node, reset old record

        trace back again, starting from this hit node, record the whole ring, also ring_length

        if ring_length == length, then 2.1, the entire graph forms a SINGLE ring, return the last edge

        else 2.2 - the edge WITHIN the ring that appears latest, is the result

about those "length + 1" thing.
i intent to speed up a little bit (do less "edges[i][k] - 1" operation) in exchange for a bit more memory.
*/

vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {//mindfully built by Nova Introvert
    int length = edges.size(), temp;

    int another_reversed_edge[2];//this holds the edge that comes second, if existed
    another_reversed_edge[0] = 0, another_reversed_edge[1] = 0;

    int reverse_edges[length + 1]; for (int i = 1; i <= length; i++) { reverse_edges[i] = 0; }
    for (int i = 0; i < length; i++) {
        if (reverse_edges[edges[i][1]] == 0) {// no one has already pointed to this node
            reverse_edges[edges[i][1]] = edges[i][0];
        }

        else {// if someone has already pointed to this node, then record the 2nd node
            another_reversed_edge[0] = edges[i][1];
            another_reversed_edge[1] = edges[i][0];
        }
    }

    vector<int> result(2, -1);

    //NOT connected to root. There MUST BE a node which is pointed to by 2 others, result MUST BE one of these 2 edges.
    if (another_reversed_edge[0] != 0) {
        // either connected to its ancestors, or connected to other branches
        // the 2 REVERSED edges are
        //      another_reversed_edge[0], reverse_edges[another_reversed_edge[0]]
        //      another_reversed_edge[0] & another_reversed_edge[1]

        // trace back
        bool hit = 0; temp = another_reversed_edge[0];
        while (reverse_edges[temp] != 0) {
            if (reverse_edges[temp] != another_reversed_edge[0]) { temp = reverse_edges[temp]; }

            //if the path come across itself, then 1.1, the beginning of current path is the result.
            else {
                result[0] = reverse_edges[another_reversed_edge[0]];
                result[1] = another_reversed_edge[0];
                hit = 1;
                break;
            }
        }

        if (hit == 0) {// if no hit, then the other edge MUST BE the result
            result[0] = another_reversed_edge[1];
            result[1] = another_reversed_edge[0];
        }
    }

    // IS connected to root, there is NO node that is pointed to by 2 others
    else {
        // either 2.1 the entire graph forms a SINGLE ring, or 2.2 that ring is only PART of the whole graph

        bool record_val[length + 1];
        for (int i = 1; i <= length; i++) { record_val[i] = 0; }// starting from 1 bc edges do not contain "0" node

        // starting from any node (1st, for example), tracing back, recording every node, it will cross its path
        temp = 1;
        while (true) {
            // it will ended up in a ring - hit a node that has been recorded
            if (record_val[reverse_edges[temp]] == 1) { break; }

            else {
                record_val[reverse_edges[temp]] = 1;
                temp = reverse_edges[temp];
            }
        }

        //remember that particular "hit" node - temp, reset old record
        for (int i = 1; i <= length; i++) { record_val[i] = 0; }// reuse record_val

        //trace back again, starting from this hit node, record every node + ring length, till it bit its head
        int ring_length = 0;
        while (true) {
            if (record_val[reverse_edges[temp]] == 1) { break; }

            else {
                ring_length++;
                record_val[reverse_edges[temp]] = 1;
                temp = reverse_edges[temp];
            }
        }

        //if ring_length == length, then 2.1, the entire graph forms a SINGLE ring, return the last edge
        if (ring_length == length) {
            result[0] = edges[length - 1][0];
            result[1] = edges[length - 1][1];
        }

        //else 2.2 - the edge WITHIN the ring that appears latest, is the result
        else {
            for (int i = 0, counter = 0; i < length; i++) {
                if (record_val[edges[i][1]] != 0) { counter++; }

                if (counter == ring_length) {
                    result[0] = edges[i][0];
                    result[1] = edges[i][1];
                    break;
                }
            }
        }
    }

    return result;
}



int main(){
    int k = 5;srand(time(0));int display = 0, input = 0;

    // to root single ring, the last in edges
    vector<vector<int>> wtf0 = {{3, 4}, {1, 2}, {2, 3}, {5, 6}, {6, 1}, {4, 5}};

    // to root NOT single ring, ring whoever comes last
    vector<vector<int>> wtf1 = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {5, 1}};

    // NOT to root, other branch, 1,3 or 5,3 whoever comes last
    vector<vector<int>> wtf2 = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {5, 3}};

    // NOT to root, ancestor, 5,2
    vector<vector<int>> wtf3 = {{1, 2}, {5, 2}, {1, 3}, {2, 4}, {4, 5}};

    // = {{3,4},{4,1},{1,2},{2,3},{5,1}};
    // = {{2,1},{3,1},{4,2},{1,4}};
    // = {{1,2},{2,3},{3,4},{4,1},{1,5}};
    // = {{1,2},{1,3},{2,3}};

//for (int m = 0; m < 50; m++) {
    /*if ((m + 1)%100 == 0) {cout << "m = " << m << "\n";}*/

    /*for(int i = 0; i < total_length; i++){
        wtf.push_back(rand()%(upper_range - lower_range + 1) + lower_range);
    }*/

    if (input == 1){
        for(int i = 0; i < k; i++){
            //wtf.push_back({rand()%(upper_range - lower_range + 1) + lower_range, rand()%(upper_range - lower_range + 1) + lower_range});
        }
    }


    auto start_point_1 = chrono::steady_clock::now();
    vector<int> shit = findRedundantDirectedConnection(wtf3);
    auto end_point_1 = chrono::steady_clock::now();
    auto diff_1 = end_point_1 - start_point_1;
    cout << duration <double, milli> (diff_1).count() << " ms" << "\n";

    for (int i = 0; i < shit.size(); i++) {
        cout << shit[i] << ", ";
    }
    cout << "\n";


//wtf.clear();}

    return 0;
}




