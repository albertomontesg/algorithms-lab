#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <limits.h>

using namespace std;

bool at_least_one(vector<long> &a) {
    bool response = true;
    for (auto elem: a) {
        if (elem == 0) {
            response = false;
        }
    }
    return response;
}

void search_snippets() {
    int n; cin >> n;

    vector<long> word_occurrences(n);
    for (int i = 0; i < n; i++) {
        long occ; cin >> occ;
        word_occurrences[i] = occ;
    }

    vector<pair<long, long> > word_appearance(0);
    long count = 0;
    for (long i = 0; i < n; i++) {
        for (int j = 0; j < word_occurrences[i]; j++) {
            long position; cin >> position;
            word_appearance.push_back(pair<long, long>(position, i));
            count++;
        }
    }

    sort(word_appearance.begin(), word_appearance.end(), [](pair<long, long> a, pair<long, long> b) {
        return a.first < b.first;
    });

    vector<long> appearance(n, 0);
    long min_distance = LONG_MAX;
    long start = 0, end = 0;
    appearance[word_appearance[0].second]++;
    while (start < count) {
        while ( !at_least_one(appearance) && end < count - 1) {
            appearance[word_appearance[++end].second]++;
        }
        while ( appearance[word_appearance[start].second] > 1) {
            appearance[word_appearance[start++].second]--;
        }
        long distance = word_appearance[end].first - word_appearance[start].first;
        if ( at_least_one(appearance) )
            min_distance = min(distance, min_distance);
        appearance[word_appearance[start].second]--;
        start++;
    }

    cout << min_distance + 1 << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        search_snippets();
    }
}
