/*
Implementation that first find the first interval that contains all the words. Then slide this
interval along the words and try to reduce if possible to find the minimum.
*/

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <limits.h>


using namespace std;


void search_snippets() {
    int n; cin >> n;

    struct {
        bool operator()(pair<long, long> a, pair<long, long> b) {
            return a.first < b.first;
        }
    } Cmp;

    vector<long> word_occurrences(n);
    vector<pair<long, long> > words;

    for (int i = 0; i < n; i++) {
        cin >> word_occurrences[i];
    }

    long total_nb_words = 0;
    for (long i = 0; i < n; i++) {
        for (int j = 0; j < word_occurrences[i]; j++) {
            long position; cin >> position;
            words.push_back(pair<long, long>(position, i));
        }
        total_nb_words += word_occurrences[i];
    }

    sort(words.begin(), words.end(), Cmp);

    vector<int> a(n, 0);
    long start = 0, end = 0;
    long min_distance = LONG_MAX;
    a[words[start].second]++;
    while (start < total_nb_words && end < total_nb_words-1) {
        if (find(a.begin(), a.end(), 0) == a.end()) {
            if (a[words[start].second] > 1) {
                a[words[start++].second]--;
            } else {
                long distance = words[end].first - words[start].first + 1;
                min_distance = min(min_distance, distance);
                a[words[start++].second]--;
                a[words[++end].second]++;
            }
        } else {
            a[words[++end].second]++;
        }
    }
    cout << min_distance << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        search_snippets();
    }
}
