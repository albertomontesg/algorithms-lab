
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

long find_minimum_time(vector<long> &t, long pos) {
    if (pos == 0) {
        return t[pos];
    }
    long upper_pos = (pos % 2 == 1) ? (pos - 1) / 2 : (pos - 2) / 2;
    long next_pos = (pos % 2 == 1) ? pos + 1 : pos - 1;
    long min_upper_pos = find_minimum_time(t, upper_pos);
    // Check if the time limit of the pair bomb is more limiting or not.
    if (t[next_pos] <= min_upper_pos - 2) {
        return min(t[pos], min_upper_pos - 1);
    } else {
        return min(t[pos], min_upper_pos - 2);
    }
}

void octopussy() {
    int n; cin >> n;

    vector<long> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    vector<bool> disarmed(n, false);

    auto cmp = [&t](pair<long, long> left, pair<long, long> right) {
        if ( left.second > right.second ) { return true; }
        else if ( left.second == right.second ) { return t[left.first] > t[right.first]; }
        else { return false; }
    };
    priority_queue<pair<long, long>, vector<pair<long, long> >, decltype(cmp)> bombs_queue(cmp);

    for (long j = (n-3)/2+1; j < n; j++) {
        long min_time = find_minimum_time(t, j);
        bombs_queue.push(pair<long, long>(j, min_time));
    }

    long t_time = 0;
    while( !bombs_queue.empty() ) {
        auto p_bomb = bombs_queue.top();
        bombs_queue.pop();
        // The most priority bomb has expired its time...BOOOM!
        long b_index = p_bomb.first;
        if (t[b_index] <= t_time) { break; }
        // Marked the bomb as disarmed
        disarmed[b_index] = true;
        t_time++;
        /* Now see if the bomb next to it has been desarmed to let the bomb standing over them to
        enter the priority queue. If not...too late...BOOOOOM!! */
        if (b_index == 0) { continue; } // The bomb at index 0 has no bomb standing over it.
        long next_b_index = (b_index % 2 == 1) ? b_index + 1 : b_index - 1;
        if ( disarmed[next_b_index] ) {
            long std_b_index = (b_index % 2 == 1) ? (b_index - 1) / 2 : (b_index - 2) / 2;
            bombs_queue.push(pair<long, long>(std_b_index, find_minimum_time(t, std_b_index)));
        }
    }

    bool all_disarmed = all_of(disarmed.begin(), disarmed.end(), [](bool v){return v;});
    string response = (all_disarmed) ? "yes" : "no";
    cout << response << endl;
}


int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        octopussy();
    }
}
