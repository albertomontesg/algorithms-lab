#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void defensive_line() {
  int N, M, K; cin >> N >> M >> K;

  vector<int> values(N);
  for (int i = 0; i < N; i++) cin >> values[i];

  // Sliding window to get all the intervals which values sum up K
  vector<pair<int, int> > intervals;
  int b = 0, e = 0, sum = values[b];
  while (e < N) {
    while (e < N && sum < K) sum += values[++e];

    if (sum == K) intervals.push_back(make_pair(b, e));

    do {
      sum -= values[b++];
    } while(b < e && sum > K);
  }

  if (intervals.size() < M) {
    cout << "fail" << endl;
    return;
  }

  // Now DP to find the set of N intervals that do not overlap each other

  // for (int i = 0; i < intervals.size(); i++) {
  //   cout << intervals[i].first << " " << intervals[i].second << endl;
  // }
}

int main() {
  ios_base::sync_with_stdio(false);
  int T; cin >> T;
  for (int t = 0; t < T; t++) defensive_line();
}
