#include <vector>
#include <iostream>

using namespace std;


// Implementation in O(n^4) time
void do_even_count_matrices(){
    int n; cin >> n;
    vector<vector<int> > bits(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> bits[i][j];

    // Precompute Si's
    vector<vector<int> > S(n+1, vector<int>(n+1));
    for (int i  = 0; i <= n; i++) {
        S[i][0] = 0;
        S[0][i] = 0;
     }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + bits[i-1][j-1];
        }
    }

    int counter = 0;
    for (int i1 = 1; i1 <= n; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            for (int i2 = i1; i2 <= n; i2++) {
                for (int j2 = j1; j2 <= n; j2++) {
                    int sum;
                    sum = S[i2][j2] - S[i2][j1-1] - S[i1-1][j2] + S[i1-1][j1-1];
                    if (sum % 2 == 0)
                        counter++;
                }
            }
        }
    }

    cout << counter << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    for (int t=0; t < T; t++){
        do_even_count_matrices();
    }
}
