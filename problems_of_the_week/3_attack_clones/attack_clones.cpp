
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void find_subsets(long m, long last_position, vector<pair<long, long> >& start) {
    auto it = find_if(start.begin(), start.begin(),
        [last_position](const pair<long, long>& element) {return element.first == last_position;});

    if (it == start.end()) {
        return;
    }
    
}


void compute_jedis() {
    long n, m; cin >> n >> m;

    vector<pair<long, long> > jedis_positions(n);
    vector<pair<long, long> > jedis_start(n);
    vector<pair<long, long> > jedis_end(n);
    vector<pair<long, long> > jedis_wide(n);
    for (int i = 0; i < n; i++) {
        long start, end;
        cin >> start >> end;
        jedis_positions[i] = pair<long, long>(start, end);
        jedis_start[i] = pair<long, long>(start, i);
        jedis_end[i] = pair<long, long>(end, i);

        long wide = end > start ? end - start : end + m - start;
        jedis_wide[i] = pair<long, long>(wide, i);
    }

    // Sorting vectors
    struct {
        bool operator()(pair<long, long> a, pair<long, long> b) {
            return a.first < b.first;
        }
    } pairLess;
    sort(jedis_start.begin(), jedis_start.end(), pairLess);
    sort(jedis_end.begin(), jedis_end.end(), pairLess);
    sort(jedis_wide.begin(), jedis_wide.end(), pairLess);

    vector<bool> segment_protected(m, false);

    vector<bool> jedi_used(n, false);


}


int main() {
    int t; cin >> t;

    for (int i = 0; i < t; i++) {
        compute_jedis();
    }
    return 0;
}
