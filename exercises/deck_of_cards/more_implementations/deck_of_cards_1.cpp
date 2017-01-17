
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

// Implementation in O(n log n)

int search_closest_value(vector<long> &array, int start, int end, long value) {
    int middle = (start + end) / 2;

    if (middle == start || middle == end) {
        int d1 = abs(value-array[start]);
        int d2 = abs(value-array[end]);
        if (d1 <= d2) {
            return start;
        } else {
            return end;
        }
    } else if (value < array[middle]) {
        return search_closest_value(array, start, middle, value);
    } else if (value > array[middle]) {
        return search_closest_value(array, middle, end, value);
    } else {
        return middle;
    }
}

void deck_of_cards(){
    long n; cin >> n;
    long k; cin >> k;

    vector<long> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    // precompute Sum
    vector<long> sum_values(n);
    sum_values[0] = values[0];
    for (int i = 1; i < n; i++) {
        sum_values[i] = sum_values[i-1] + values[i];
    }

    long i_r = 0, j_r = 0;
    long min_val = numeric_limits<long>::max();

    long prev_sum_values = 0;
    for (int i = 0; i < n; i++) {
        long pre_sum = k + prev_sum_values;
        int j_pos = search_closest_value(sum_values, i, n, pre_sum);
        long val = abs(pre_sum - sum_values[j_pos]);
        if (val < min_val) {
            min_val = val;
            i_r = i;
            j_r = j_pos;
        }
        prev_sum_values = sum_values[i];
    }

    cout << i_r << ' ' << j_r << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        deck_of_cards();
    }
}
