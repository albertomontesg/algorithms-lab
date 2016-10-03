/*
Implementation that first find the first interval that contains all the words. Then slide this
interval along the words and try to reduce if possible to find the minimum.
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <limits.h>

using namespace std;


void search_snippets() {
    int n; cin >> n;

    vector<long> word_occurrences(n);
    for (int i = 0; i < n; i++) {
        cin >> word_occurrences[i];
    }

    vector<pair<long, long> > word_appearance(65536);
    long count = 0;
    for (long i = 0; i < n; i++) {
        for (int j = 0; j < word_occurrences[i]; j++) {
            long position; cin >> position;
            word_appearance[count] = pair<long, long>(position, i);
            count++;
        }
    }

    sort(word_appearance.begin(), word_appearance.end(), [](pair<long, long> a, pair<long, long> b) {
        return a.first < b.first;
    });

    vector<long> appearance(n, 0);
    long start = 0, end = 0;
    appearance[word_appearance[0].second]++;
    while ( *min_element(appearance.begin(), appearance.end()) != 1 && end < count - 1) {
        appearance[word_appearance[++end].second]++;
    }
    while ( appearance[word_appearance[start].second] > 1) {
        appearance[word_appearance[start++].second]--;
    }
    long min_distance = word_appearance[end].first - word_appearance[start].first;

    while (end < count - 1) {
        appearance[word_appearance[start++].second]--;
        appearance[word_appearance[++end].second]++;
        while (appearance[word_appearance[start].second] > 1 && *min_element(appearance.begin(), appearance.end()) >= 1) {
            appearance[word_appearance[start++].second]--;
        }
        long distance = word_appearance[end].first - word_appearance[start].first;
        if (*min_element(appearance.begin(), appearance.end()) >= 1)
            min_distance = min(distance, min_distance);
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