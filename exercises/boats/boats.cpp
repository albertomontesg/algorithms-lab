/*
Implementation using two fors to iterate

Correct
*/
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

    long current_last_position = boats[0].first;
    long number_boats = 1;
    long i = 1;
    while (i < n) {
        if (current_last_position > boats[i].first) {
            i++;
        } else if (boats[i].first - current_last_position > boats[i].second) {
            number_boats++;
            current_last_position = boats[i].first;
            i++;
        } else {
            long first_end = boats[i].second + current_last_position;
            long min_position = i;
            for (long j = i+1; j < n; j++) {
                long end_position;
                if (boats[j].first - current_last_position > boats[j].second) {
                    end_position = boats[j].first;
                } else {
                    end_position = current_last_position + boats[j].second;
                }
                if (end_position < first_end) {
                    first_end = end_position;
                    min_position = j;
                }
            }
            number_boats++;
            current_last_position = first_end;
            i = min_position + 1;
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
