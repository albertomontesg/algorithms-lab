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

    if (sum == K) intervals.push_back(make_pair(e, b));

    do {
      sum -= values[b++];
    } while(b < e && sum > K);
  }

  if (intervals.size() < M) {
    cout << "fail" << endl;
    return;
  }

  sort(intervals.begin(), intervals.end());

  // Now DP to find the set of N intervals that do not overlap each other
  vector<vector<int> > T(M+1, vector<int>(N, -1));
  for (int i = 0; i < N; i++) T[0][i] = 0;

  for (int n = 0; n < N; n++) {
    for (int m = 1; m <= M; m++) {
      pair<int,int> interval = *lower_bound(intervals.begin(), intervals.end(), make_pair(n,-1));

      // In case there is no interval ending at position n
      if (interval.first != n) {
        // In case being at the first interval
        if (n == 0) T[m][n] = T[m-1][n];
        else T[m][n] = max(T[m-1][n], T[m][n-1]);
        continue;
      }

      // There is a interval that ends at n
      int num = interval.first - interval.second + 1;

      if (m == 1 || interval.second-1 < 0) T[m][n] = max(num, T[m][n-1]);
      else T[m][n] = max(num+T[m-1][interval.second-1], T[m][n-1]);
    }
  }

  cout << T[M][N-1] << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int T; cin >> T;
  for (int t = 0; t < T; t++) defensive_line();
}
