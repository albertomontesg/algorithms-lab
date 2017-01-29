#include <iostream>
#include <vector>

using namespace std;

void punch(){
  int n, k; cin >> n >> k;

  vector<pair<int, int> > baverages(n);
  int c, v;
  for (int i = 0; i < n; i++) {
    cin >> c >> v;
    baverages[i] = make_pair(c, v);
  }

  vector<vector<pair<int, int> > > T(n, vector<pair<int, int> >(k, pair<int, int>(-1, -1)));

  for (int v = 0; v <= 0; v++) {
    for (int i = 0; i < n; i++) {
      if (v == 0) {
        if (i == 0 || T[i-1][v].first == -1) {
          if (baverages[i].second == v+1) T[i][v] = make_pair(baverages[i].first, 1);
        }
      }
    }
  }

  // for (int i = 0; i < n; i++) {
  //   c = baverages[i].first;
  //   v = baverages[i].second;
  //   for (int j = 0; j < k; j++) {
  //     if (i == 0) {
  //       if ((j + 1) % v != 0) continue;
  //       int nb = (j + 1) / v;
  //       T[i][j] = make_pair(nb*c, 1);
  //     }
  //
  //   }
  // }

}


int main() {
  ios_base::sync_with_stdio(false);
  int T; cin >> T;

  for (int i = 0; i < T; i++) punch();
}
