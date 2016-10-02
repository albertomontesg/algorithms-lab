// Implementation with a single for iterating

// Wrong Answer
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void boats() {
    long n; cin >> n;

    vector<pair<long, long> > boats(n);
    for (int i = 0; i < n; i++) {
        cin >> boats[i].second;
        cin >> boats[i].first;
    }

    sort(boats.begin(), boats.end(), [](pair<long, long> a, pair<long, long> b) {
        return a.first < b.first;
    });

    long number_boats = 1;
    long current_last_position = boats[0].first;
    long previous_last_position = boats[0].first - boats[1].second;

    for (int i = 0; i < n; i++) {
        if (current_last_position > boats[i].first) {
            // Check if the boat at current position will end closer
            long possible_end = (boats[i].first - previous_last_position > boats[i].second) ? boats[i].first : previous_last_position + boats[i].second;
            if (possible_end < current_last_position) {
                current_last_position = possible_end;
            }
        } else {
            number_boats++;
            previous_last_position = current_last_position;
            current_last_position = (boats[i].first - previous_last_position > boats[i].second) ? boats[i].first : previous_last_position + boats[i].second;
        }
    }

    cout << number_boats << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        boats();
    }
}
